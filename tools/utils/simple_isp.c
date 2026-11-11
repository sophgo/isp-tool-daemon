/*
 * simple_isp.c - Minimal software ISP pipeline: RAW→YUV
 *
 * Pipeline stages:
 *   1. BLC  (Black Level Correction): subtract offset, apply digital gain
 *   2. AWB  (White Balance): apply R/G/B channel gains
 *   3. Demosaic: bilinear interpolation on Bayer pattern
 *   4. CCM  (Color Correction Matrix): 3x3 matrix, 1024 = 1.0x
 *   5. Gamma: 256-entry LUT, 12-bit input index (>>4), 12-bit output
 *   6. CSC  (Color Space Conversion): RGB→NV21 (YUV 4:2:0)
 *
 * All parameters are parsed from the companion .txt file in the dump directory.
 * After the first parse, AWB gains are updated from awbRun results.
 *
 * Usage: #include "../utils/simple_isp.c" in awb_simulation_tool.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <glob.h>

/* ------------------------------------------------------------------ */
/* Parameter struct                                                     */
/* ------------------------------------------------------------------ */

#define SIMPLE_ISP_GAMMA_LUT_SIZE  256

typedef struct {
	/* BLC */
	int32_t  blc_offset[4];   /* R, Gr, Gb, B */
	uint32_t blc_dgain[4];    /* R, Gr, Gb, B  — 1024 = 1.0x */

	/* AWB gains — R, Gr, Gb, B  — 1024 = 1.0x (updated each frame) */
	uint32_t wb_gain[4];

	/* CCM — row-major 3x3, 1024 = 1.0x, can be negative */
	int32_t  ccm[3][3];

	/* Gamma LUT — 256 entries, 12-bit output */
	uint16_t gamma[SIMPLE_ISP_GAMMA_LUT_SIZE];

	/* Image geometry */
	uint32_t width;
	uint32_t height;

	/* Bayer order (matches ISP_BAYER_FORMAT_E: 0=BGGR,1=GBRG,2=GRBG,3=RGGB) */
	int      bayer_fmt;

	/* Set after successful parse */
	int      valid;
} SimpleIspParams;

static SimpleIspParams g_sisp_params;

/* ------------------------------------------------------------------ */
/* Helper: find .raw and .txt companion files in a directory            */
/* ------------------------------------------------------------------ */

static int sisp_find_raw_txt(const char *dir,
			     char *raw_path, size_t raw_sz,
			     char *txt_path, size_t txt_sz)
{
	glob_t gl;
	char   pattern[512];

	snprintf(pattern, sizeof(pattern), "%s/*.raw", dir);
	if (glob(pattern, 0, NULL, &gl) != 0 || gl.gl_pathc == 0) {
		globfree(&gl);
		fprintf(stderr, "simple_isp: no .raw file in %s\n", dir);
		return -1;
	}
	snprintf(raw_path, raw_sz, "%s", gl.gl_pathv[0]);
	globfree(&gl);

	snprintf(pattern, sizeof(pattern), "%s/*.txt", dir);
	if (glob(pattern, 0, NULL, &gl) != 0 || gl.gl_pathc == 0) {
		globfree(&gl);
		fprintf(stderr, "simple_isp: no .txt file in %s\n", dir);
		return -1;
	}
	/* Prefer the file that doesn't end in "awblog.txt" or "aelog.txt" */
	txt_path[0] = '\0';
	for (size_t i = 0; i < gl.gl_pathc; i++) {
		const char *p = gl.gl_pathv[i];
		size_t      l = strlen(p);

		if (l > 10 && strcmp(p + l - 10, "awblog.txt") == 0)
			continue;
		if (l > 9 && strcmp(p + l - 9, "aelog.txt") == 0)
			continue;
		snprintf(txt_path, txt_sz, "%s", p);
		break;
	}
	if (txt_path[0] == '\0')
		snprintf(txt_path, txt_sz, "%s", gl.gl_pathv[0]);
	globfree(&gl);
	return 0;
}

/* ------------------------------------------------------------------ */
/* Parse ISP parameters from the .txt companion file                    */
/* ------------------------------------------------------------------ */

static int sisp_parse_txt(const char *txt_path, SimpleIspParams *p,
			  uint32_t width, uint32_t height, int bayer_fmt)
{
	FILE *fp = fopen(txt_path, "r");

	if (!fp) {
		fprintf(stderr, "simple_isp: cannot open %s\n", txt_path);
		return -1;
	}

	/* Defaults: identity */
	memset(p, 0, sizeof(*p));
	p->width      = width;
	p->height     = height;
	p->bayer_fmt  = bayer_fmt;
	p->wb_gain[0] = 1024;
	p->wb_gain[1] = 1024;
	p->wb_gain[2] = 1024;
	p->wb_gain[3] = 1024;
	p->blc_dgain[0] = p->blc_dgain[1] = p->blc_dgain[2] = p->blc_dgain[3] = 1024;
	/* Identity CCM */
	p->ccm[0][0] = 1024; p->ccm[1][1] = 1024; p->ccm[2][2] = 1024;
	/* Linear gamma */
	for (int i = 0; i < SIMPLE_ISP_GAMMA_LUT_SIZE; i++)
		p->gamma[i] = (uint16_t)(i * 4095 / 255);

	char  line[8192];
	int   in_gamma = 0;
	int   gamma_idx = 0;

	while (fgets(line, sizeof(line), fp)) {
		/* Strip trailing newline */
		size_t len = strlen(line);

		while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r'))
			line[--len] = '\0';

		/* BLC offset */
		int32_t v32 = 0;

		if (sscanf(line, "reg_blc_offset_r = %d",  &v32) == 1) {
			p->blc_offset[0] = v32;
			continue;
		}
		if (sscanf(line, "reg_blc_offset_gr = %d", &v32) == 1) {
			p->blc_offset[1] = v32;
			continue;
		}
		if (sscanf(line, "reg_blc_offset_gb = %d", &v32) == 1) {
			p->blc_offset[2] = v32;
			continue;
		}
		if (sscanf(line, "reg_blc_offset_b = %d",  &v32) == 1) {
			p->blc_offset[3] = v32;
			continue;
		}

		/* BLC dgain */
		uint32_t u32 = 0;

		if (sscanf(line, "reg_blc_dgain_r = %u",  &u32) == 1) {
			p->blc_dgain[0] = u32;
			continue;
		}
		if (sscanf(line, "reg_blc_dgain_gr = %u", &u32) == 1) {
			p->blc_dgain[1] = u32;
			continue;
		}
		if (sscanf(line, "reg_blc_dgain_gb = %u", &u32) == 1) {
			p->blc_dgain[2] = u32;
			continue;
		}
		if (sscanf(line, "reg_blc_dgain_b = %u",  &u32) == 1) {
			p->blc_dgain[3] = u32;
			continue;
		}

		/* WB gain — initial value from txt (will be overwritten by AWB result) */
		if (sscanf(line, "reg_wbg_rgain = %u",  &u32) == 1) {
			p->wb_gain[0] = u32;
			continue;
		}
		if (sscanf(line, "reg_wbg_grgain = %u", &u32) == 1) {
			p->wb_gain[1] = u32;
			continue;
		}
		if (sscanf(line, "reg_wbg_gbgain = %u", &u32) == 1) {
			p->wb_gain[2] = u32;
			continue;
		}
		if (sscanf(line, "reg_wbg_bgain = %u",  &u32) == 1) {
			p->wb_gain[3] = u32;
			continue;
		}

		/* CCM */
		int32_t cv = 0;

		if (sscanf(line, "reg_ccm_00 = %d", &cv) == 1) {
			p->ccm[0][0] = cv;
			continue;
		}
		if (sscanf(line, "reg_ccm_01 = %d", &cv) == 1) {
			p->ccm[0][1] = cv;
			continue;
		}
		if (sscanf(line, "reg_ccm_02 = %d", &cv) == 1) {
			p->ccm[0][2] = cv;
			continue;
		}
		if (sscanf(line, "reg_ccm_10 = %d", &cv) == 1) {
			p->ccm[1][0] = cv;
			continue;
		}
		if (sscanf(line, "reg_ccm_11 = %d", &cv) == 1) {
			p->ccm[1][1] = cv;
			continue;
		}
		if (sscanf(line, "reg_ccm_12 = %d", &cv) == 1) {
			p->ccm[1][2] = cv;
			continue;
		}
		if (sscanf(line, "reg_ccm_20 = %d", &cv) == 1) {
			p->ccm[2][0] = cv;
			continue;
		}
		if (sscanf(line, "reg_ccm_21 = %d", &cv) == 1) {
			p->ccm[2][1] = cv;
			continue;
		}
		if (sscanf(line, "reg_ccm_22 = %d", &cv) == 1) {
			p->ccm[2][2] = cv;
			continue;
		}

		/* Gamma LUT — "gamma =" header followed by comma-separated values */
		if (strncmp(line, "gamma =", 7) == 0) {
			in_gamma  = 1;
			gamma_idx = 0;
			continue;
		}
		if (in_gamma && gamma_idx < SIMPLE_ISP_GAMMA_LUT_SIZE) {
			/* Lines may contain values terminated by commas */
			const char *ptr = line;
			char *end;

			while (*ptr && gamma_idx < SIMPLE_ISP_GAMMA_LUT_SIZE) {
				while (*ptr == ' ' || *ptr == '\t' || *ptr == ',')
					ptr++;
				if (*ptr == '\0' || *ptr == '\r' || *ptr == '\n')
					break;
				long val = strtol(ptr, &end, 10);

				if (end == ptr)
					break;
				p->gamma[gamma_idx++] = (uint16_t)(val < 0 ? 0 : (val > 4095 ? 4095 : val));
				ptr = end;
			}
			if (gamma_idx >= SIMPLE_ISP_GAMMA_LUT_SIZE)
				in_gamma = 0;
			/* Check for end of gamma section by next named section */
			if (strstr(line, "lsc_"))
				in_gamma = 0;
			continue;
		}
		/* Stop gamma if we hit another named section */
		if (in_gamma && (strstr(line, "_gain") || strstr(line, "_offset")))
			in_gamma = 0;
	}

	fclose(fp);
	p->valid = 1;

	printf("simple_isp: parsed params from %s\n", txt_path);
	printf("  BLC offset R/Gr/Gb/B: %d %d %d %d\n",
	       p->blc_offset[0], p->blc_offset[1], p->blc_offset[2], p->blc_offset[3]);
	printf("  BLC dgain  R/Gr/Gb/B: %u %u %u %u\n",
	       p->blc_dgain[0], p->blc_dgain[1], p->blc_dgain[2], p->blc_dgain[3]);
	printf("  WB gain    R/Gr/Gb/B: %u %u %u %u\n",
	       p->wb_gain[0], p->wb_gain[1], p->wb_gain[2], p->wb_gain[3]);
	printf("  CCM: [%d %d %d / %d %d %d / %d %d %d]\n",
	       p->ccm[0][0], p->ccm[0][1], p->ccm[0][2],
	       p->ccm[1][0], p->ccm[1][1], p->ccm[1][2],
	       p->ccm[2][0], p->ccm[2][1], p->ccm[2][2]);
	printf("  Gamma[0]=%u Gamma[128]=%u Gamma[255]=%u\n",
	       p->gamma[0], p->gamma[128], p->gamma[255]);
	return 0;
}

/* ------------------------------------------------------------------ */
/* Inline clamp helpers                                                 */
/* ------------------------------------------------------------------ */

static inline int32_t clamp0(int32_t v, int32_t lo, int32_t hi)
{
	return v < lo ? lo : (v > hi ? hi : v);
}

static inline uint8_t clamp_u8(int32_t v)
{
	return (uint8_t)(v < 0 ? 0 : (v > 255 ? 255 : v));
}

/* ------------------------------------------------------------------ */
/* Bayer channel helpers                                                */
/* For a pixel at (row, col), return which Bayer channel it belongs to:
 *   0=R, 1=Gr, 2=Gb, 3=B
 * Bayer fmt: 0=BGGR, 1=GBRG, 2=GRBG, 3=RGGB
 * Pattern layout for each fmt (2x2 tile):
 *   BGGR:  B  Gb     GBRG: Gb  B     GRBG: Gr  R     RGGB: R  Gr
 *          Gr  R            R  Gr            B  Gb           Gb  B
 */
/* ------------------------------------------------------------------ */

static inline int bayer_channel(int row, int col, int fmt)
{
	int r = row & 1;
	int c = col & 1;

	switch (fmt) {
	case 0: /* BGGR */
		if (!r && !c)
			return 3; /* B  */
		if (!r &&  c)
			return 2; /* Gb */
		if (r && !c)
			return 1; /* Gr */
		return 0; /* R  */
	case 1: /* GBRG */
		if (!r && !c)
			return 2; /* Gb */
		if (!r &&  c)
			return 3; /* B  */
		if (r && !c)
			return 0; /* R  */
		return 1; /* Gr */
	case 2: /* GRBG */
		if (!r && !c)
			return 1; /* Gr */
		if (!r &&  c)
			return 0; /* R  */
		if (r && !c)
			return 3; /* B  */
		return 2; /* Gb */
	case 3: /* RGGB */
	default:
		if (!r && !c)
			return 0; /* R  */
		if (!r &&  c)
			return 1; /* Gr */
		if (r && !c)
			return 2; /* Gb */
		return 3; /* B  */
	}
}

/* ------------------------------------------------------------------ */
/* RAW read helper                                                      */
/* ------------------------------------------------------------------ */

static inline uint16_t raw_get(const uint16_t *raw, uint32_t w, uint32_t h,
				int row, int col)
{
	if (row < 0)
		row = 0;
	if (col < 0)
		col = 0;
	if ((uint32_t)row >= h)
		row = (int)h - 1;
	if ((uint32_t)col >= w)
		col = (int)w - 1;
	return raw[(uint32_t)row * w + (uint32_t)col] & 0x0FFF;
}

/* ------------------------------------------------------------------ */
/* Main pipeline entry point                                            */
/*                                                                      */
/* raw_data  : pointer to width*height uint16_t values (LE, 12-bit)    */
/* p         : ISP parameters                                           */
/* yuv_y     : output Y  plane (width * height bytes)                  */
/* yuv_uv    : output UV plane interleaved UVUV... (width * height / 2) */
/*             → NV12 layout                                            */
/* ------------------------------------------------------------------ */

static void sisp_run(const uint16_t *raw_data, const SimpleIspParams *p,
		     uint8_t *yuv_y, uint8_t *yuv_uv)
{
	const uint32_t W = p->width;
	const uint32_t H = p->height;

	/* Allocate an intermediate integer RGB buffer: int32[W*H*3], 12-bit range. */
	int32_t *rgb = (int32_t *)malloc(W * H * 3 * sizeof(int32_t));

	if (!rgb) {
		fprintf(stderr, "simple_isp: OOM for RGB buffer\n");
		return;
	}

	/* ---- Stage 1+2: BLC + WB gain per Bayer pixel ----------------- */
	/*
	 * Build a pre-processed Bayer buffer: blc_corrected[row*W+col]
	 * = clamp((raw - offset) * blc_dgain / 1024 * wb_gain / 1024, 0, 4095)
	 * We keep 12-bit range.
	 */
	uint16_t *bayer = (uint16_t *)malloc(W * H * sizeof(uint16_t));

	if (!bayer) {
		fprintf(stderr, "simple_isp: OOM for bayer buffer\n");
		free(rgb);
		return;
	}

	for (uint32_t row = 0; row < H; row++) {
		for (uint32_t col = 0; col < W; col++) {
			int ch   = bayer_channel((int)row, (int)col, p->bayer_fmt);
			int32_t  val = (int32_t)(raw_data[row * W + col] & 0x0FFF);

			/* BLC: subtract black level */
			val -= p->blc_offset[ch];
			if (val < 0)
				val = 0;

			/* BLC dgain */
			val = (val * (int32_t)p->blc_dgain[ch] + 512) >> 10;

			/* AWB gain */
			val = (val * (int32_t)p->wb_gain[ch] + 512) >> 10;

			bayer[row * W + col] = (uint16_t)(val > 4095 ? 4095 : (uint16_t)val);
		}
	}

	/* ---- Stage 3: Demosaic (bilinear) ------------------------------ */
	/*
	 * For each output pixel we reconstruct R, G, B via bilinear
	 * interpolation from neighbouring Bayer samples of the same channel.
	 *
	 * g_avg = average of the up to 4 G neighbours (cross pattern)
	 * r_avg = average of the up to 4 R neighbours (diagonal for B pixels,
	 *         horizontal/vertical for G pixels)
	 * b_avg = symmetric to r_avg
	 */
	for (uint32_t row = 0; row < H; row++) {
		for (uint32_t col = 0; col < W; col++) {
			int     ch  = bayer_channel((int)row, (int)col, p->bayer_fmt);
			int32_t R, G, B;
			int32_t sum;
			int     cnt;

			/*
			 * Determine which of R/G/B this pixel directly measures,
			 * and interpolate the other two.
			 *
			 * ch: 0=R, 1=Gr, 2=Gb, 3=B
			 * G pixels: ch==1 or ch==2
			 */
			if (ch == 0) {
				/* R pixel: direct R */
				R = raw_get(bayer, W, H, (int)row, (int)col);

				/* G: average of 4 cross neighbours */
				sum = 0; cnt = 0;
				sum += raw_get(bayer, W, H, (int)row-1, (int)col);   cnt++;
				sum += raw_get(bayer, W, H, (int)row+1, (int)col);   cnt++;
				sum += raw_get(bayer, W, H, (int)row,   (int)col-1); cnt++;
				sum += raw_get(bayer, W, H, (int)row,   (int)col+1); cnt++;
				G = sum / cnt;

				/* B: average of 4 diagonal neighbours */
				sum = 0; cnt = 0;
				sum += raw_get(bayer, W, H, (int)row-1, (int)col-1); cnt++;
				sum += raw_get(bayer, W, H, (int)row-1, (int)col+1); cnt++;
				sum += raw_get(bayer, W, H, (int)row+1, (int)col-1); cnt++;
				sum += raw_get(bayer, W, H, (int)row+1, (int)col+1); cnt++;
				B = sum / cnt;

			} else if (ch == 3) {
				/* B pixel: direct B */
				B = raw_get(bayer, W, H, (int)row, (int)col);

				/* G: average of 4 cross neighbours */
				sum = 0; cnt = 0;
				sum += raw_get(bayer, W, H, (int)row-1, (int)col);   cnt++;
				sum += raw_get(bayer, W, H, (int)row+1, (int)col);   cnt++;
				sum += raw_get(bayer, W, H, (int)row,   (int)col-1); cnt++;
				sum += raw_get(bayer, W, H, (int)row,   (int)col+1); cnt++;
				G = sum / cnt;

				/* R: average of 4 diagonal neighbours */
				sum = 0; cnt = 0;
				sum += raw_get(bayer, W, H, (int)row-1, (int)col-1); cnt++;
				sum += raw_get(bayer, W, H, (int)row-1, (int)col+1); cnt++;
				sum += raw_get(bayer, W, H, (int)row+1, (int)col-1); cnt++;
				sum += raw_get(bayer, W, H, (int)row+1, (int)col+1); cnt++;
				R = sum / cnt;

			} else {
				/*
				 * G pixel (ch==1 Gr or ch==2 Gb):
				 * Direct G.  R and B are in the perpendicular lines.
				 */
				G = raw_get(bayer, W, H, (int)row, (int)col);

				if (ch == 1) {
					/* Gr pixel: R is on same row, B is on same col */
					sum = raw_get(bayer, W, H, (int)row, (int)col-1)
					    + raw_get(bayer, W, H, (int)row, (int)col+1);
					R = sum / 2;
					sum = raw_get(bayer, W, H, (int)row-1, (int)col)
					    + raw_get(bayer, W, H, (int)row+1, (int)col);
					B = sum / 2;
				} else {
					/* Gb pixel: B is on same row, R is on same col */
					sum = raw_get(bayer, W, H, (int)row, (int)col-1)
					    + raw_get(bayer, W, H, (int)row, (int)col+1);
					B = sum / 2;
					sum = raw_get(bayer, W, H, (int)row-1, (int)col)
					    + raw_get(bayer, W, H, (int)row+1, (int)col);
					R = sum / 2;
				}
			}

			uint32_t idx   = row * W + col;

			rgb[idx]           = R;        /* R — 12-bit */
			rgb[idx + W * H]   = G;        /* G */
			rgb[idx + W * H * 2] = B;      /* B */
		}
	}

	free(bayer);

	/* ---- Stage 4: CCM ---------------------------------------------- */
	for (uint32_t i = 0; i < W * H; i++) {
		int32_t R = rgb[i];
		int32_t G = rgb[i + W * H];
		int32_t B = rgb[i + W * H * 2];

		int32_t Ro = (p->ccm[0][0] * R + p->ccm[0][1] * G + p->ccm[0][2] * B + 512) >> 10;
		int32_t Go = (p->ccm[1][0] * R + p->ccm[1][1] * G + p->ccm[1][2] * B + 512) >> 10;
		int32_t Bo = (p->ccm[2][0] * R + p->ccm[2][1] * G + p->ccm[2][2] * B + 512) >> 10;

		rgb[i]             = clamp0(Ro, 0, 4095);
		rgb[i + W * H]     = clamp0(Go, 0, 4095);
		rgb[i + W * H * 2] = clamp0(Bo, 0, 4095);
	}

	/* ---- Stage 5: Gamma -------------------------------------------- */
	/*
	 * Input: 12-bit (0~4095).  LUT has 256 entries.
	 * Index = pixel >> 4 (0~255).  Output is 12-bit.
	 * Then convert to 8-bit for CSC: >> 4 again.
	 */
	for (uint32_t i = 0; i < W * H; i++) {
		int32_t R = rgb[i];
		int32_t G = rgb[i + W * H];
		int32_t B = rgb[i + W * H * 2];

		rgb[i]             = p->gamma[R >> 4];
		rgb[i + W * H]     = p->gamma[G >> 4];
		rgb[i + W * H * 2] = p->gamma[B >> 4];
	}

	/* ---- Stage 6: CSC RGB → NV12 ----------------------------------- */
	/*
	 * Convert 12-bit gamma output to 8-bit then apply BT.601 CSC.
	 *
	 * Y  =  0.299 R + 0.587 G + 0.114 B
	 * Cb = -0.169 R - 0.331 G + 0.500 B + 128
	 * Cr =  0.500 R - 0.419 G - 0.081 B + 128
	 *
	 * NV12: Y plane full resolution, then interleaved U,V at half resolution.
	 */
	for (uint32_t row = 0; row < H; row++) {
		for (uint32_t col = 0; col < W; col++) {
			uint32_t idx = row * W + col;
			/* 12-bit → 8-bit */
			int32_t R8 = rgb[idx]             >> 4;
			int32_t G8 = rgb[idx + W * H]     >> 4;
			int32_t B8 = rgb[idx + W * H * 2] >> 4;

			/* Y */
			int32_t Y = (77 * R8 + 150 * G8 + 29 * B8 + 128) >> 8;

			yuv_y[idx] = clamp_u8(Y);

			/* Chroma — only write for even rows and even cols (4:2:0) */
			if ((row & 1) == 0 && (col & 1) == 0) {
				uint32_t uv_idx = (row / 2) * W + col;
				/* NV12: U(Cb) first, V(Cr) second */
				/* Cb = -0.169R - 0.331G + 0.500B + 128 */
				int32_t Cb = (-43  * R8 -  85 * G8 + 128 * B8 + 128 + 32768) >> 8;
				/* Cr =  0.500R - 0.419G - 0.081B + 128 */
				int32_t Cr = (128 * R8 - 107 * G8 -  21 * B8 + 128 + 32768) >> 8;

				yuv_uv[uv_idx]     = clamp_u8(Cb); /* U */
				yuv_uv[uv_idx + 1] = clamp_u8(Cr); /* V */
			}
		}
	}

	free(rgb);
}

/* ------------------------------------------------------------------ */
/* Public API                                                           */
/* ------------------------------------------------------------------ */

/*
 * sisp_init() — load RAW and parse params from the given dump directory.
 * Must be called once before sisp_render().
 * width/height/bayer_fmt come from the dump filename parsed by the caller.
 * is_wdr: non-zero for WDR sensors.  In that case the .raw file is stored
 * with the LE and SE rows packed side-by-side in each "double-width" row
 * (file row width = 2 * width).  Only the LE half is extracted for rendering.
 */
static uint16_t *g_sisp_raw_data;   /* loaded RAW image, kept in memory */

static int sisp_init(const char *data_dir,
		     uint32_t width, uint32_t height, int bayer_fmt,
		     int is_wdr)
{
	char raw_path[512];
	char txt_path[512];

	if (sisp_find_raw_txt(data_dir, raw_path, sizeof(raw_path),
			      txt_path, sizeof(txt_path)) != 0)
		return -1;

	/* Parse ISP params */
	if (sisp_parse_txt(txt_path, &g_sisp_params, width, height, bayer_fmt) != 0)
		return -1;

	/* Load RAW data */
	FILE *fp = fopen(raw_path, "rb");

	if (!fp) {
		fprintf(stderr, "simple_isp: cannot open %s\n", raw_path);
		return -1;
	}

	free(g_sisp_raw_data);
	g_sisp_raw_data = NULL;

	if (is_wdr) {
		/*
		 * WDR layout: each row in the file is 2*width samples wide.
		 * First half = long-exposure (LE) row, second half = short-
		 * exposure (SE) row.  Extract the LE frame for rendering.
		 */
		size_t    npix_file = (size_t)(2 * width) * height;
		uint16_t *raw_full  = (uint16_t *)malloc(npix_file * sizeof(uint16_t));

		if (!raw_full) {
			fprintf(stderr, "simple_isp: OOM for WDR raw buffer\n");
			fclose(fp);
			return -1;
		}
		size_t nread = fread(raw_full, sizeof(uint16_t), npix_file, fp);

		fclose(fp);
		if (nread != npix_file) {
			fprintf(stderr,
				"simple_isp: WDR RAW size mismatch (expected %zu, got %zu)\n",
				npix_file, nread);
			free(raw_full);
			return -1;
		}

		size_t npix = (size_t)width * height;

		g_sisp_raw_data = (uint16_t *)malloc(npix * sizeof(uint16_t));
		if (!g_sisp_raw_data) {
			fprintf(stderr, "simple_isp: OOM for LE frame buffer\n");
			free(raw_full);
			return -1;
		}
		/* Extract LE frame: first width pixels of each double-wide row */
		for (uint32_t row = 0; row < height; row++) {
			for (uint32_t col = 0; col < width; col++)
				g_sisp_raw_data[row * width + col] =
					raw_full[row * 2 * width + col];
		}
		free(raw_full);
		printf("simple_isp: WDR raw %s  LE frame extracted (%ux%u)\n",
		       raw_path, width, height);
	} else {
		size_t npix = (size_t)width * height;

		g_sisp_raw_data = (uint16_t *)malloc(npix * sizeof(uint16_t));
		if (!g_sisp_raw_data) {
			fprintf(stderr, "simple_isp: OOM for RAW buffer\n");
			fclose(fp);
			return -1;
		}
		size_t nread = fread(g_sisp_raw_data, sizeof(uint16_t), npix, fp);

		fclose(fp);
		if (nread != npix) {
			fprintf(stderr, "simple_isp: RAW size mismatch (expected %zu, got %zu)\n",
				npix, nread);
			free(g_sisp_raw_data);
			g_sisp_raw_data = NULL;
			return -1;
		}
		printf("simple_isp: loaded RAW %s (%ux%u)\n", raw_path, width, height);
	}
	return 0;
}

/*
 * sisp_update_wb_gains() — called after each awbRun to apply the latest
 * AWB gains.  Gain array order: [0]=R, [1]=Gr, [2]=Gb, [3]=B, 1024=1.0x.
 */
static void sisp_update_wb_gains(const uint32_t gains[4])
{
	if (!g_sisp_params.valid)
		return;
	g_sisp_params.wb_gain[0] = gains[0];
	g_sisp_params.wb_gain[1] = gains[1];
	g_sisp_params.wb_gain[2] = gains[2];
	g_sisp_params.wb_gain[3] = gains[3];
}

/*
 * sisp_render() — run the full ISP pipeline and write into a caller-provided
 * VIDEO_FRAME_INFO_S (NV12 format).
 *
 * The frame buffer (Y + UV planes) must already be allocated by the caller.
 * Returns 0 on success.
 */
static int sisp_render(VIDEO_FRAME_INFO_S *pstFrameInfo)
{
	if (!g_sisp_params.valid || !g_sisp_raw_data) {
		fprintf(stderr, "simple_isp: not initialised\n");
		return -1;
	}

	VIDEO_FRAME_S *vf = &pstFrameInfo->stVFrame;
	uint8_t *y_plane  = vf->pu8VirAddr[0];
	uint8_t *uv_plane = vf->pu8VirAddr[1];

	if (!y_plane || !uv_plane) {
		fprintf(stderr, "simple_isp: frame buffer not allocated\n");
		return -1;
	}

	sisp_run(g_sisp_raw_data, &g_sisp_params, y_plane, uv_plane);
	return 0;
}
