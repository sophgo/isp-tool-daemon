
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <getopt.h>
#include <sys/types.h>
#include <dirent.h>
#include <glob.h>

#include "cvi_isp.h"
#include "cvi_comm_3a.h"
#include "cvi_awb_comm.h"
#include "cvi_awb.h"
#include "cvi_ispd2.h"
#include "awb_sim_adapter.h"

#include "../utils/simple_isp.c"

CVI_S32 awbInit(VI_PIPE ViPipe, const ISP_AWB_PARAM_S *pstAwbParam);
CVI_S32 awbRun(VI_PIPE ViPipe, const ISP_AWB_INFO_S *pstAwbInfo, ISP_AWB_RESULT_S *pstAwbResult, CVI_S32 s32Rsv);
CVI_S32 awbExit(VI_PIPE ViPipe);

#ifndef UNUSED
#define UNUSED(x) ((void)(x))
#endif

static int g_main_loop_run = 1;

#define JSONRPC_PORT     (5566)
#define DEFAULT_VI_PIPE  (0)

/* Maximum zones: AWB_ZONE_ORIG_ROW(30) * AWB_ZONE_ORIG_COLUMN(34) = 1020 */
#define AWB_SIM_MAX_ZONES  (AWB_ZONE_NUM)
/* Maximum HDR frames: ISP_CHANNEL_MAX_NUM = 2 (LE + SE) */
#define AWB_SIM_MAX_FRAMES (ISP_CHANNEL_MAX_NUM)

typedef struct {
	uint32_t frame_id;
	uint8_t  frame_num;   /* 1 = linear, 2 = WDR (from fnum in log) */
	uint16_t zone_row;
	uint16_t zone_col;

	/* AWB zone statistics [wdr_frame][zone_idx] */
	uint16_t zone_r[AWB_SIM_MAX_FRAMES][AWB_SIM_MAX_ZONES];
	uint16_t zone_g[AWB_SIM_MAX_FRAMES][AWB_SIM_MAX_ZONES];
	uint16_t zone_b[AWB_SIM_MAX_FRAMES][AWB_SIM_MAX_ZONES];

	int16_t  lv_x100;
	uint32_t iso;

	/* Calibration from CAL section (RGain, BGain, CT) */
	uint16_t calib_r[AWB_CALIB_PTS_NUM];
	uint16_t calib_b[AWB_CALIB_PTS_NUM];
	uint16_t calib_ct[AWB_CALIB_PTS_NUM];

	/* Current WB gain at capture time (CWB line) */
	uint16_t init_r_gain;
	uint16_t init_b_gain;

	/* Parsed from filename */
	uint16_t           img_width;
	uint16_t           img_height;
	ISP_BAYER_FORMAT_E bayer_fmt;

	/* ISP_WB_ATTR_S fields from log (for CVI_ISP_SetWBAttr) */
	uint8_t  has_wbattr;
	uint8_t  log_bypass;
	uint8_t  log_op_type;
	uint8_t  log_run_interval;
	uint16_t log_mwb_r, log_mwb_gr, log_mwb_gb, log_mwb_b;
	uint8_t  log_auto_en;
	uint16_t log_auto_speed;
	uint16_t log_high_ct;
	uint16_t log_low_ct;
	uint8_t  log_shift_limit_en;
	uint8_t  log_natural_cast_en;
	uint8_t  log_alg_type;
	uint16_t log_shift_limit[AWB_CURVE_BOUND_NUM];

	/* ISP_AWB_ATTR_EX_S fields from log (for CVI_ISP_SetAWBAttrEx) */
	uint8_t  has_attrex;   /* bit0=TarR parsed, bit1=CT bins parsed */
	uint16_t log_target_ct[AWB_TARGET_RATIO_NUM];
	uint8_t  log_target_r[AWB_TARGET_RATIO_NUM];
	uint8_t  log_target_b[AWB_TARGET_RATIO_NUM];
	uint16_t log_ct_bin[AWB_CT_BIN_NUM];
	uint16_t log_ct_wt[AWB_CT_BIN_NUM];
} AwbSimData;

static AwbSimData g_awb_sim_data;

static void signal_handler(int signum)
{
	UNUSED(signum);
	printf("\nReceived signal, exiting gracefully...\n");
	g_main_loop_run = 0;
}

static void print_usage(const char *program_name)
{
	printf("Usage: %s -d <data_dir> [-p port] [-h]\n", program_name);
	printf("  -d data_dir    Directory containing *-awblog.txt dump file\n");
	printf("  -p port        JSONRPC port number (default: %d)\n", JSONRPC_PORT);
	printf("  -h             Show this help message\n");
}

/* Parse image width, height and Bayer format from the log filename.
 * Expected prefix pattern: "<W>X<H>_<BAYER>_..."
 * e.g. "1920X1080_BGGR_Linear_...-awblog.txt"
 */
static void parse_filename_meta(const char *filepath, AwbSimData *data)
{
	const char *base = strrchr(filepath, '/');

	base = base ? base + 1 : filepath;

	/* Resolution: WxH before the first '_' */
	if (sscanf(base, "%huX%hu_", &data->img_width, &data->img_height) != 2) {
		fprintf(stderr, "Warning: cannot parse resolution from filename, using 1920x1080\n");
		data->img_width  = 1920;
		data->img_height = 1080;
	}

	/* Bayer pattern: token after the first '_' */
	const char *p = strchr(base, '_');

	if (p) {
		p++;
		if (strncmp(p, "BGGR", 4) == 0)
			data->bayer_fmt = BAYER_BGGR;
		else if (strncmp(p, "GBRG", 4) == 0)
			data->bayer_fmt = BAYER_GBRG;
		else if (strncmp(p, "GRBG", 4) == 0)
			data->bayer_fmt = BAYER_GRBG;
		else if (strncmp(p, "RGGB", 4) == 0)
			data->bayer_fmt = BAYER_RGGB;
		else {
			fprintf(stderr, "Warning: unknown Bayer pattern in filename, defaulting to BGGR\n");
			data->bayer_fmt = BAYER_BGGR;
		}
	} else {
		data->bayer_fmt = BAYER_BGGR;
	}

	/*
	 * WDR raw files have doubled width in the filename (e.g. 5120X1440 for
	 * a 2560x1440 sensor).  The raw data is stored with LE and SE rows
	 * interleaved: for each sensor row the first half of pixels is the
	 * long-exposure (LE) row and the second half is the short-exposure (SE)
	 * row.  Halve img_width here so the rest of the pipeline uses the real
	 * sensor dimensions.
	 */
	if (strstr(base, "_WDR_") != NULL || strstr(base, "_wdr_") != NULL)
		data->img_width /= 2;

	static const char * const bayer_names[] = { "BGGR", "GBRG", "GRBG", "RGGB" };

	printf("Filename meta: %ux%u  Bayer=%s%s\n",
	       data->img_width, data->img_height,
	       bayer_names[data->bayer_fmt],
	       (data->frame_num > 1) ? "  [WDR]" : "");
}

/* Find the *-awblog.txt file inside dir_path */
static int find_awblog_file(const char *dir_path, char *out_path, size_t out_size)
{
	char pattern[512];
	glob_t gl;

	snprintf(pattern, sizeof(pattern), "%s/*-awblog.txt", dir_path);
	if (glob(pattern, 0, NULL, &gl) != 0 || gl.gl_pathc == 0) {
		globfree(&gl);
		fprintf(stderr, "No *-awblog.txt found in: %s\n", dir_path);
		return -1;
	}
	snprintf(out_path, out_size, "%s", gl.gl_pathv[0]);
	globfree(&gl);
	return 0;
}

/* Count whitespace-separated tokens in a line */
static int count_tokens(const char *line)
{
	int count = 0;
	int in_token = 0;

	while (*line) {
		if (*line == ' ' || *line == '\t' || *line == '\r' || *line == '\n') {
			in_token = 0;
		} else {
			if (!in_token) {
				count++;
				in_token = 1;
			}
		}
		line++;
	}
	return count;
}

/* Parse one row of whitespace-separated uint16 values into buf.
 * Returns the number of values successfully parsed.
 */
static int parse_stat_row(const char *line, uint16_t *buf, int max_count)
{
	int count = 0;
	const char *p = line;
	char *endptr;

	while (*p && count < max_count) {
		while (*p == ' ' || *p == '\t')
			p++;
		if (*p == '\0' || *p == '\r' || *p == '\n')
			break;
		unsigned long val = strtoul(p, &endptr, 10);

		if (endptr == p)
			break;
		buf[count++] = (uint16_t)val;
		p = endptr;
	}
	return count;
}

/* Check if a line is blank (contains only whitespace) */
static int is_blank_line(const char *line)
{
	while (*line) {
		if (*line != ' ' && *line != '\t' && *line != '\r' && *line != '\n')
			return 0;
		line++;
	}
	return 1;
}

/*
 * Parse the *-awblog.txt file.
 *
 * File format (produced by AWB_SaveLog):
 *   fid:<frame_id> fnum:<frame_num>
 *   [for each wdr frame][for each channel R,G,B]:
 *     <zone_row> rows of <zone_col> tab-separated values
 *     <blank line>
 *     <blank line>
 *   Ver:<major>.<minor> <dbg_ver>@<release_date>
 *   AWB <r_gain> <b_gain>
 *   FWB <r_gain> <b_gain>
 *   CWB <r_gain> <b_gain>
 *   WDR_SEC:<x> GC:<gray_cnt> GR:<ratio> EC:<eff_cnt> TC:<total_cnt> K:<ct> ...
 *   LV:<lv_x100> I:<iso>
 *   <blank line>
 *   CAL
 *   <r0> <b0> <ct0>
 *   <r1> <b1> <ct1>
 *   <r2> <b2> <ct2>
 *   ...
 */
static int parse_awblog(const char *filepath, AwbSimData *data)
{
	FILE *fp = fopen(filepath, "r");

	if (!fp) {
		fprintf(stderr, "Cannot open log file: %s\n", filepath);
		return -1;
	}

	char line[4096];

	memset(data, 0, sizeof(*data));

	/* Line 1: "fid:XXXX fnum:N" */
	if (!fgets(line, sizeof(line), fp)) {
		fprintf(stderr, "Log file is empty\n");
		fclose(fp);
		return -1;
	}
	if (sscanf(line, "fid:%u fnum:%hhu", &data->frame_id, &data->frame_num) != 2) {
		fprintf(stderr, "Failed to parse fid/fnum: %s\n", line);
		fclose(fp);
		return -1;
	}
	if (data->frame_num == 0 || data->frame_num > AWB_SIM_MAX_FRAMES) {
		fprintf(stderr, "Invalid fnum=%d (max=%d)\n", data->frame_num, AWB_SIM_MAX_FRAMES);
		fclose(fp);
		return -1;
	}
	printf("Log file: fid=%u fnum=%u\n", data->frame_id, data->frame_num);

	/*
	 * Parse statistics blocks: frame_num * 3 channels (R, G, B) in order.
	 * Within each block: rows of zone values, terminated by 2+ blank lines.
	 */
	int total_blocks = data->frame_num * 3; /* R0,G0,B0[,R1,G1,B1] */

	for (int block = 0; block < total_blocks; block++) {
		int frame_idx = block / 3;
		int chan_idx  = block % 3;
		uint16_t *dst;

		if (chan_idx == 0)
			dst = data->zone_r[frame_idx];
		else if (chan_idx == 1)
			dst = data->zone_g[frame_idx];
		else
			dst = data->zone_b[frame_idx];

		int zone_idx = 0;
		int row_count = 0;
		int blank_streak = 0;
		int found_data = 0;

		while (fgets(line, sizeof(line), fp)) {
			if (is_blank_line(line)) {
				if (found_data) {
					blank_streak++;
					if (blank_streak >= 2)
						break; /* end of this channel block */
				}
				continue;
			}
			blank_streak = 0;

			/* Detect column count from the very first data line */
			if (data->zone_col == 0) {
				data->zone_col = (uint16_t)count_tokens(line);
				printf("Detected zone_col=%u\n", data->zone_col);
			}

			if (data->zone_col == 0 || zone_idx + data->zone_col > AWB_SIM_MAX_ZONES) {
				fprintf(stderr, "Zone overflow at block=%d row=%d\n", block, row_count);
				break;
			}

			int n = parse_stat_row(line, dst + zone_idx, data->zone_col);

			zone_idx += n;
			row_count++;
			found_data = 1;
		}

		/* Detect row count from the first channel block */
		if (block == 0) {
			data->zone_row = (uint16_t)row_count;
			printf("Detected zone_row=%u, total_zones=%d\n", data->zone_row, zone_idx);
		}
	}

	if (data->zone_row == 0 || data->zone_col == 0) {
		fprintf(stderr, "Failed to detect zone dimensions\n");
		fclose(fp);
		return -1;
	}

	/* Parse metadata lines after the statistics blocks */
	int calib_idx   = 0;
	int in_calib    = 0;
	int in_sft      = 0, sft_lines    = 0;
	int in_target_r = 0, target_r_idx = 0;
	int in_ct_bin   = 0, ct_bin_idx   = 0;

	while (fgets(line, sizeof(line), fp)) {
		/* Strip trailing newline */
		size_t len = strlen(line);

		while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
			line[--len] = '\0';

		if (len == 0) {
			in_calib = 0;
			continue;
		}

		if (strncmp(line, "LV:", 3) == 0) {
			if (sscanf(line, "LV:%hd I:%u", &data->lv_x100, &data->iso) == 2)
				printf("Parsed: LV=%d ISO=%u\n", data->lv_x100, data->iso);
		} else if (strncmp(line, "CWB ", 4) == 0) {
			if (sscanf(line, "CWB %hu %hu", &data->init_r_gain, &data->init_b_gain) == 2)
				printf("Parsed: CWB R=%u B=%u\n", data->init_r_gain, data->init_b_gain);
		} else if (strcmp(line, "CAL") == 0) {
			in_calib  = 1;
			calib_idx = 0;
		} else if (in_calib && calib_idx < AWB_CALIB_PTS_NUM) {
			uint16_t r = 0, b = 0, ct = 0;

			if (sscanf(line, "%hu %hu %hu", &r, &b, &ct) == 3) {
				data->calib_r[calib_idx]  = r;
				data->calib_b[calib_idx]  = b;
				data->calib_ct[calib_idx] = ct;
				calib_idx++;
				if (calib_idx == AWB_CALIB_PTS_NUM) {
					in_calib = 0;
					printf("Parsed CAL: [R=%u,B=%u,CT=%u] [R=%u,B=%u,CT=%u] [R=%u,B=%u,CT=%u]\n",
						data->calib_r[0], data->calib_b[0], data->calib_ct[0],
						data->calib_r[1], data->calib_b[1], data->calib_ct[1],
						data->calib_r[2], data->calib_b[2], data->calib_ct[2]);
				}
			}
		} else if (strcmp(line, "Sft") == 0) {
			in_sft = 1; sft_lines = 0;
		} else if (in_sft && sft_lines < 4) {
			if (++sft_lines == 4)
				in_sft = 0;
		} else if (strncmp(line, "ByP:", 4) == 0) {
			unsigned int v = 0;

			if (sscanf(line, "ByP:%u", &v) == 1)
				data->log_bypass = (uint8_t)v;
			data->has_wbattr = 1;
		} else if (strncmp(line, "OP:", 3) == 0) {
			unsigned int v = 0;

			if (sscanf(line, "OP:%u", &v) == 1)
				data->log_op_type = (uint8_t)v;
		} else if (strncmp(line, "Int:", 4) == 0) {
			unsigned int v = 0;

			if (sscanf(line, "Int:%u", &v) == 1)
				data->log_run_interval = (uint8_t)(v ? v : 1);
		} else if (strncmp(line, "MWB:", 4) == 0) {
			if (sscanf(line, "MWB:%hu %hu %hu %hu",
				   &data->log_mwb_r, &data->log_mwb_gr,
				   &data->log_mwb_gb, &data->log_mwb_b) != 4)
				fprintf(stderr, "%s: bad MWB line\n", __func__);
		} else if (strncmp(line, "aEn:", 4) == 0) {
			unsigned int en = 0, spd = 0;

			if (sscanf(line, "aEn:%u spd:%u", &en, &spd) == 2) {
				data->log_auto_en    = (uint8_t)en;
				data->log_auto_speed = (uint16_t)spd;
			}
		} else if (strcmp(line, "TarR:") == 0) {
			in_target_r  = 1;
			target_r_idx = 0;
		} else if (in_target_r && target_r_idx < AWB_TARGET_RATIO_NUM) {
			uint16_t ct = 0;
			unsigned int r = 0, b = 0;

			if (sscanf(line, "%hu: %u %u", &ct, &r, &b) == 3) {
				data->log_target_ct[target_r_idx] = ct;
				data->log_target_r[target_r_idx]  = (uint8_t)r;
				data->log_target_b[target_r_idx]  = (uint8_t)b;
				if (++target_r_idx == AWB_TARGET_RATIO_NUM) {
					in_target_r       = 0;
					data->has_attrex |= 1;
				}
			}
		} else if (strncmp(line, "HLtmp:", 6) == 0) {
			if (sscanf(line, "HLtmp:%hu %hu",
				   &data->log_high_ct, &data->log_low_ct) != 2)
				fprintf(stderr, "%s: bad HLtmp line\n", __func__);
		} else if (strncmp(line, "ShLim:", 6) == 0) {
			unsigned int sle = 0, nce = 0;

			if (sscanf(line, "ShLim:%u %u", &sle, &nce) == 2) {
				data->log_shift_limit_en  = (uint8_t)sle;
				data->log_natural_cast_en = (uint8_t)nce;
			}
		} else if (strncmp(line, "Alg:", 4) == 0) {
			unsigned int v = 0;

			if (sscanf(line, "Alg:%u", &v) == 1)
				data->log_alg_type = (uint8_t)v;
		} else if (strncmp(line, "ShLimA:", 7) == 0) {
			if (sscanf(line, "ShLimA:%hu,%hu,%hu,%hu,%hu,%hu,%hu,%hu",
				   &data->log_shift_limit[0], &data->log_shift_limit[1],
				   &data->log_shift_limit[2], &data->log_shift_limit[3],
				   &data->log_shift_limit[4], &data->log_shift_limit[5],
				   &data->log_shift_limit[6], &data->log_shift_limit[7]) != 8)
				fprintf(stderr, "%s: bad ShLimA line\n", __func__);
			in_ct_bin  = 1;
			ct_bin_idx = 0;
		} else if (in_ct_bin && ct_bin_idx < AWB_CT_BIN_NUM) {
			uint16_t bin = 0, gain = 0, wt = 0;

			if (sscanf(line, "%hu %hu %hu", &bin, &gain, &wt) == 3) {
				data->log_ct_bin[ct_bin_idx] = bin;
				data->log_ct_wt[ct_bin_idx]  = wt;
				if (++ct_bin_idx == AWB_CT_BIN_NUM) {
					in_ct_bin       = 0;
					data->has_attrex |= 2;
				}
			} else {
				in_ct_bin = 0;
			}
		}
	}

	fclose(fp);

	if (data->iso == 0) {
		fprintf(stderr, "Warning: ISO not parsed, using default 100\n");
		data->iso = 100;
	}

	/* Parse width, height and Bayer format from the filename */
	parse_filename_meta(filepath, data);

	return 0;
}

/*
 * Configure ISP statistics zone info and initialize the AWB algorithm.
 * Must be called after CVI_ISP_MemInit().
 */
static int awbsim_init(AwbSimData *data, VI_PIPE pipe)
{
	CVI_S32 ret;

	/*
	 * AWB_ConfigWin() inside awbInit() reads zone row/col from
	 * CVI_ISP_GetStatisticsConfig(). We pre-configure it here so that
	 * the correct dimensions are used.
	 */
	ISP_STATISTICS_CFG_S stStatCfg;

	memset(&stStatCfg, 0, sizeof(stStatCfg));
	CVI_ISP_GetStatisticsConfig(pipe, &stStatCfg);
	stStatCfg.stWBCfg.u16ZoneRow     = data->zone_row;
	stStatCfg.stWBCfg.u16ZoneCol     = data->zone_col;
	stStatCfg.stWBCfg.u16BlackLevel  = 0;
	stStatCfg.stWBCfg.u16WhiteLevel  = 4095;
	ret = CVI_ISP_SetStatisticsConfig(pipe, &stStatCfg);
	if (ret != CVI_SUCCESS)
		fprintf(stderr, "Warning: CVI_ISP_SetStatisticsConfig failed 0x%x\n", ret);

	/* Initialize AWB algorithm */
	ISP_AWB_PARAM_S stAwbParam;

	memset(&stAwbParam, 0, sizeof(stAwbParam));
	stAwbParam.u8WDRMode    = (data->frame_num > 1) ? 1 : 0;
	stAwbParam.u8AWBZoneRow = data->zone_row;
	stAwbParam.u8AWBZoneCol = data->zone_col;
	/* Image dimensions from filename */
	stAwbParam.u16AWBWidth  = data->img_width;
	stAwbParam.u16AWBHeight = data->img_height;

	ret = awbInit(pipe, &stAwbParam);
	if (ret != CVI_SUCCESS) {
		fprintf(stderr, "awbInit failed: 0x%x\n", ret);
		return -1;
	}
	printf("awbInit OK (WDRMode=%u, zones=%ux%u)\n",
		stAwbParam.u8WDRMode, data->zone_row, data->zone_col);

	/*
	 * Restore all AWB parameters from the log via ISP API calls so the
	 * algorithm resumes from the same state as the system that produced
	 * the log.
	 */

	/* Step 1: Get default WBAttr and overlay log-parsed fields */
	ISP_WB_ATTR_S stWbAttr;

	CVI_ISP_GetWBAttr(pipe, &stWbAttr); /* get current curve params from ISP */
	if (data->has_wbattr) {
		stWbAttr.bByPass          = data->log_bypass;
		stWbAttr.enOpType         = (ISP_OP_TYPE_E)data->log_op_type;
		stWbAttr.u8AWBRunInterval = data->log_run_interval ? data->log_run_interval : 1;
		stWbAttr.u8DebugMode      = 0; /* keep debug off in simulation */
		stWbAttr.stManual.u16Rgain  = data->log_mwb_r;
		stWbAttr.stManual.u16Grgain = data->log_mwb_gr;
		stWbAttr.stManual.u16Gbgain = data->log_mwb_gb;
		stWbAttr.stManual.u16Bgain  = data->log_mwb_b;
		stWbAttr.stAuto.bEnable          = data->log_auto_en;
		stWbAttr.stAuto.u16Speed         = data->log_auto_speed;
		stWbAttr.stAuto.u16HighColorTemp = data->log_high_ct;
		stWbAttr.stAuto.u16LowColorTemp  = data->log_low_ct;
		stWbAttr.stAuto.bShiftLimitEn    = data->log_shift_limit_en;
		stWbAttr.stAuto.bNaturalCastEn   = data->log_natural_cast_en;
		stWbAttr.enAlgType = (ISP_AWB_ALG_E)data->log_alg_type;
		for (int i = 0; i < AWB_CURVE_BOUND_NUM; i++)
			stWbAttr.stAuto.u16ShiftLimit[i] = data->log_shift_limit[i];
	}

	/* Step 2: Build curve from calibration data, then set via ISP API */
	if (data->calib_ct[0] != 0) {
		ISP_AWB_Calibration_Gain_S stCalib;

		memset(&stCalib, 0, sizeof(stCalib));
		for (int i = 0; i < AWB_CALIB_PTS_NUM; i++) {
			stCalib.u16AvgRgain[i]        = data->calib_r[i];
			stCalib.u16AvgBgain[i]        = data->calib_b[i];
			stCalib.u16ColorTemperature[i] = data->calib_ct[i];
		}
		CVI_ISP_SetWBCalibration(pipe, &stCalib);
		printf("Calibration loaded from log\n");
	}

	/* Step 3: Apply WB attributes (includes curve params updated by BuildCurve) */
	CVI_ISP_SetWBAttr(pipe, &stWbAttr);

	/* Step 4: Apply extended AWB attributes */
	if (data->has_attrex) {
		ISP_AWB_ATTR_EX_S stAttrEx;

		CVI_ISP_GetAWBAttrEx(pipe, &stAttrEx);
		if (data->has_attrex & 1) { /* TarR parsed */
			for (int i = 0; i < AWB_TARGET_RATIO_NUM; i++) {
				stAttrEx.u16TargetCT[i]       = data->log_target_ct[i];
				stAttrEx.u8TargetStrengthR[i] = data->log_target_r[i];
				stAttrEx.u8TargetStrengthB[i] = data->log_target_b[i];
			}
		}
		if (data->has_attrex & 2) { /* CT bins parsed */
			for (int i = 0; i < AWB_CT_BIN_NUM; i++) {
				stAttrEx.au16MultiCTBin[i] = data->log_ct_bin[i];
				stAttrEx.au16MultiCTWt[i]  = data->log_ct_wt[i];
			}
		}
		CVI_ISP_SetAWBAttrEx(pipe, &stAttrEx);
	}

	/*
	 * Step 5: Inject the parsed zone statistics into the simulated 3A buffers.
	 * This makes CVI_ISPD2_CBFunc_Get3AStatisticsInfo return real data to the
	 * PC analysis tool instead of zeros.  The AE and AWB zone grids are
	 * identical (30 x 34), so we reuse the same R/G/B arrays for both.
	 */
	awbsim_fill_3a_stats(data->frame_num,
			     data->zone_row, data->zone_col,
			     data->zone_r[0], data->zone_g[0], data->zone_b[0],
			     (data->frame_num > 1) ? data->zone_r[1] : NULL,
			     (data->frame_num > 1) ? data->zone_g[1] : NULL,
			     (data->frame_num > 1) ? data->zone_b[1] : NULL);
	printf("awbsim: injected %u-frame zone stats (%ux%u) into 3A buffers\n",
		data->frame_num, data->zone_row, data->zone_col);

	return 0;
}

/*
 * AWB_SIM_TICK_MS: interval between awbRun calls.
 *
 * AWB_SaveDbgBin() uses a busy-poll waiting up to 5 * u8AWBRunInterval * 80 ms
 * for awbRun to be called TWICE (400 ms window with default interval=1).
 * 100 ms gives 4 calls per window, which is a safe margin.
 */
#define AWB_SIM_TICK_MS   100
#define AWB_SIM_PRINT_EVERY (1000 / AWB_SIM_TICK_MS)

/*
 * Run one iteration of the AWB algorithm with the parsed statistics.
 * Stats are replayed each cycle so the algorithm converges from the
 * captured environment. The PC tool can adjust WB attributes via
 * JSON-RPC at any time; awbRun picks them up automatically.
 */
static void awbsim_run_once(AwbSimData *data, VI_PIPE pipe, uint32_t frame_cnt, int do_print)
{
	ISP_AWB_INFO_S   stAwbInfo;
	ISP_AWB_RESULT_S stAwbResult;

	memset(&stAwbInfo,   0, sizeof(stAwbInfo));
	memset(&stAwbResult, 0, sizeof(stAwbResult));

	stAwbInfo.u32FrameCnt = frame_cnt;
	stAwbInfo.s16LVx100   = data->lv_x100;
	stAwbInfo.u32IsoNum   = data->iso;
	stAwbInfo.fBVstep     = 1.0f;

	for (int f = 0; f < data->frame_num; f++) {
		stAwbInfo.stAwbStat2[f].pau16ZoneAvgR = data->zone_r[f];
		stAwbInfo.stAwbStat2[f].pau16ZoneAvgG = data->zone_g[f];
		stAwbInfo.stAwbStat2[f].pau16ZoneAvgB = data->zone_b[f];
	}

	CVI_S32 ret = awbRun(pipe, &stAwbInfo, &stAwbResult, 0);

	if (ret != CVI_SUCCESS) {
		fprintf(stderr, "awbRun failed: 0x%x\n", ret);
		return;
	}

	if (do_print) {
		printf("[%u] AWB: R=%u G=%u B=%u CT=%uK stable=%d, Sat=%u/%u/%u/%u CASat=%u CASatLuma=%u\n",
			frame_cnt,
			stAwbResult.au32WhiteBalanceGain[0],
			stAwbResult.au32WhiteBalanceGain[1],
			stAwbResult.au32WhiteBalanceGain[3],
			stAwbResult.u32ColorTemp,
			stAwbResult.bStable,
			stAwbResult.u8Saturation[0], stAwbResult.u8Saturation[1],
			stAwbResult.u8Saturation[2], stAwbResult.u8Saturation[3],
			stAwbResult.u8AdjCASaturation,
			stAwbResult.u8AdjCASatLuma);
	}

	/* Update simple_isp WB gains with the latest AWB result */
	sisp_update_wb_gains(stAwbResult.au32WhiteBalanceGain);
}

int main(int argc, char **argv)
{
	int         port     = JSONRPC_PORT;
	const char *data_dir = NULL;
	int         opt;

	while ((opt = getopt(argc, argv, "d:p:h")) != -1) {
		switch (opt) {
		case 'd':
			data_dir = optarg;
			break;
		case 'p':
			port = atoi(optarg);
			break;
		case 'h':
			print_usage(argv[0]);
			return 0;
		default:
			print_usage(argv[0]);
			return 1;
		}
	}

	if (!data_dir) {
		fprintf(stderr, "Error: -d <data_dir> is required\n");
		print_usage(argv[0]);
		return 1;
	}

	/* Find the *-awblog.txt in the specified directory */
	char logfile_path[512];

	if (find_awblog_file(data_dir, logfile_path, sizeof(logfile_path)) != 0) {
		fprintf(stderr, "No *-awblog.txt found in: %s\n", data_dir);
		return 1;
	}
	printf("Using log file: %s\n", logfile_path);

	/* Parse statistics and metadata from the log file */
	if (parse_awblog(logfile_path, &g_awb_sim_data) != 0) {
		fprintf(stderr, "Failed to parse AWB log file\n");
		return 1;
	}

	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);

	/* Initialize ISP subsystem (required by both daemon and AWB algo) */
	CVI_ISP_MemInit(DEFAULT_VI_PIPE);

	/* Start JSON-RPC daemon so the PC tool can read/write WB attributes */
	isp_daemon2_init(port);

	/* Initialize AWB algorithm with parsed log data */
	if (awbsim_init(&g_awb_sim_data, DEFAULT_VI_PIPE) != 0) {
		fprintf(stderr, "AWB init failed\n");
		isp_daemon2_uninit();
		return 1;
	}

	/* Initialize simple_isp: load RAW and parse ISP params from the dump dir */
	if (sisp_init(data_dir,
		      g_awb_sim_data.img_width,
		      g_awb_sim_data.img_height,
		      (int)g_awb_sim_data.bayer_fmt,
		      (g_awb_sim_data.frame_num > 1)) != 0) {
		fprintf(stderr, "simple_isp init failed (no .raw/.txt in %s)\n", data_dir);
		/* Non-fatal: GetChnFrame will just return an error */
	}

	printf("\nAWB simulation running. JSONRPC port=%d, data dir=%s\n", port, data_dir);
	printf("Connect the PC tuning tool to port %d to adjust AWB parameters.\n\n", port);

	uint32_t frame_cnt    = g_awb_sim_data.frame_id;
	uint32_t tick_counter = 0;

	g_main_loop_run = 1;
	while (g_main_loop_run) {
		int do_print = (tick_counter % AWB_SIM_PRINT_EVERY == 0);

		awbsim_run_once(&g_awb_sim_data, DEFAULT_VI_PIPE, frame_cnt, do_print);
		frame_cnt++;
		tick_counter++;
		usleep(AWB_SIM_TICK_MS * 1000);
	}

	awbExit(DEFAULT_VI_PIPE);
	isp_daemon2_uninit();
	return 0;
}

CVI_S32 CVI_VPSS_ReleaseChnFrame(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, const VIDEO_FRAME_INFO_S *pstVideoFrame)
{
	UNUSED(VpssGrp);
	UNUSED(VpssChn);
	if (!pstVideoFrame)
		return CVI_SUCCESS;

	/* Free the Y and UV plane buffers allocated in CVI_VPSS_GetChnFrame */
	if (pstVideoFrame->stVFrame.pu8VirAddr[0]) {
		free(pstVideoFrame->stVFrame.pu8VirAddr[0]);
	}
	return CVI_SUCCESS;
}

CVI_S32 CVI_VPSS_GetChnFrame(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, VIDEO_FRAME_INFO_S *pstFrameInfo,
				 CVI_S32 s32MilliSec)
{
	UNUSED(VpssGrp);
	UNUSED(VpssChn);
	UNUSED(s32MilliSec);

	if (!pstFrameInfo)
		return CVI_FAILURE;

	if (!g_sisp_params.valid || !g_sisp_raw_data) {
		fprintf(stderr, "%s: simple_isp not ready\n", __func__);
		return CVI_FAILURE;
	}

	const uint32_t W = g_sisp_params.width;
	const uint32_t H = g_sisp_params.height;

	memset(pstFrameInfo, 0, sizeof(*pstFrameInfo));

	VIDEO_FRAME_S *vf  = &pstFrameInfo->stVFrame;

	vf->u32Width       = W;
	vf->u32Height      = H;
	vf->enPixelFormat  = PIXEL_FORMAT_NV12;
	vf->u32Stride[0]   = W;
	vf->u32Stride[1]   = W;
	vf->u32Length[0]   = W * H;
	vf->u32Length[1]   = W * H / 2;

	/*
	 * Allocate Y+UV in a single contiguous block so ReleaseChnFrame only
	 * needs one free().  UV immediately follows Y.
	 */
	size_t  total = (size_t)W * H + (size_t)W * H / 2;
	uint8_t *buf  = (uint8_t *)malloc(total);

	if (!buf) {
		fprintf(stderr, "%s: OOM\n", __func__);
		return CVI_FAILURE;
	}

	vf->pu8VirAddr[0] = buf;
	vf->pu8VirAddr[1] = buf + (size_t)W * H;
	vf->u64PhyAddr[0] = (CVI_U64)(uintptr_t)vf->pu8VirAddr[0];
	vf->u64PhyAddr[1] = (CVI_U64)(uintptr_t)vf->pu8VirAddr[1];

	if (sisp_render(pstFrameInfo) != 0) {
		free(buf);
		memset(pstFrameInfo, 0, sizeof(*pstFrameInfo));
		return CVI_FAILURE;
	}

	return CVI_SUCCESS;
}
