/*
 * ispd2_client — CLI driver for the rpcjson operations against
 * isp daemon2 (readall / writeall / dumpyuv / dumpraw / exportbin /
 * importbin / mmapen / mmapget). Wire behavior mirrors CviPQTool: flat
 * struct-field params for GET/SET, "Data size"-announced binary streams for
 * dumps and bin transfer (see ispd2_rpc.c header for the framing contract).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "cvi_json_object.h"
#include "cvi_json_tokener.h"

#include "ispd2_rpc.h"

#define DEFAULT_IP		"127.0.0.1"
#define DEFAULT_PORT		5566
#define DEFAULT_OUT_DIR		"/mnt/data"

#define OUT_READALL		DEFAULT_OUT_DIR "/isp_readall.json"
#define OUT_YUV			DEFAULT_OUT_DIR "/isp_dump.yuv"
#define OUT_BIN			DEFAULT_OUT_DIR "/isp_params.bin"
#define OUT_MOMAP		DEFAULT_OUT_DIR "/isp_momap.bin"

/* CVI_MMAP_STS_DATA_MAX from cvi_isp.h: 2bpp payload cap (480 * 270 / 4) */
#define MO_MAP_DATA_MAX		((480 * 270) / 4)

/* the host polls this file and unlinks it before running its teardown */
#define EXIT_TRIGGER		DEFAULT_OUT_DIR "/isp_test_ut_exit"
#define EXIT_TIMEOUT_SEC	(30)

#define MAX_MODULES		128

/* from include/cvi_common.h (standalone build does not include it) */
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x)		(sizeof(x) / sizeof((x)[0]))
#endif

/*
 * binary stream headers (daemon side:
 * cvi_ispd2_callback_funcs_apps_define.h:42-78, LP64, natural alignment)
 * — mirrored exactly so we can parse + strip them
 */
typedef struct {
	uint8_t		numFrame;
	uint16_t	width;
	uint16_t	height;
	uint16_t	stride[3];
	uint8_t		pixelFormat;
	uint8_t		curFrame;
	uint32_t	size;
} TYUVHeader;

typedef struct {
	uint8_t		numFrame;
	uint16_t	width;
	uint16_t	height;
	uint16_t	stride[3];
	uint8_t		curFrame;
	uint8_t		bayerID;
	uint8_t		compress;
	uint16_t	cropX;
	uint16_t	cropY;
	uint8_t		fusionFrame;
	uint32_t	exposure[4];
	uint32_t	ispDGain;
	uint32_t	iso;
	uint32_t	colorTemp;
	uint16_t	wbRGain;
	uint16_t	wbBGain;
	int16_t		ccm[9];
	uint16_t	blcOffset[4];
	uint16_t	blcGain[4];
	uint32_t	exposureRatio;
	uint32_t	exposureAGain;
	uint32_t	exposureDGain;
	uint16_t	cropWidth;
	uint16_t	cropHeight;
	uint32_t	size;
} TRAWHeader;

_Static_assert(sizeof(TYUVHeader) == 20, "TYUVHeader layout mismatch");
_Static_assert(sizeof(TRAWHeader) == 112, "TRAWHeader layout mismatch");

/*
 * CVI_ISP_GetMmapStsData stream header (daemon side: TISPD2MoMapStsHdr in
 * cvi_ispd2_callback_funcs_apps_define.h, same field order / size).
 * data_size counts the 2bpp payload only, not this header. The layout packs
 * to 16B with natural alignment, so no packed attribute is needed.
 */
typedef struct {
	uint16_t	map_w;		/* motion map width, ceil(W / 4) */
	uint16_t	map_h;		/* motion map height, ceil(H / 4) */
	uint16_t	stride_2bpp;	/* packed row bytes = (map_w * 2 + 7) / 8 */
	uint16_t	format;		/* 0 = 2bpp packed MoMp, LSB-first */
	uint32_t	data_size;	/* payload bytes = map_h * stride_2bpp */
	uint32_t	frame_id;	/* snapshot frame id */
} TMoMapStsHdr;

_Static_assert(sizeof(TMoMapStsHdr) == 16, "TMoMapStsHdr layout mismatch");

/* ------------------------------------------------------------------ */
/* JSON-RPC helpers */

static int _reply_check(struct cvi_json_object *reply)
{
	struct cvi_json_object *obj;

	if (!reply)
		return -1;

	if (cvi_json_object_object_get_ex(reply, "error", &obj)) {
		struct cvi_json_object *tmp;
		int code = 0;
		const char *msg = "";

		if (cvi_json_object_object_get_ex(obj, "code", &tmp))
			code = cvi_json_object_get_int(tmp);
		if (cvi_json_object_object_get_ex(obj, "message", &tmp))
			msg = cvi_json_object_get_string(tmp);
		ISPD2_CLI_PRT("rpc error %d: %s\n", code, msg);
		return -1;
	}

	if (!cvi_json_object_object_get_ex(reply, "result", &obj)) {
		ISPD2_CLI_PRT("reply has no result\n");
		return -1;
	}

	return 0;
}

/* returns NEW reply ref (caller puts) or NULL; takes params ownership */
static struct cvi_json_object *_rpc(const char *method, struct cvi_json_object *params)
{
	struct cvi_json_object *reply;

	if (ispd2_send_request(method, params) != 0)
		return NULL;

	reply = ispd2_recv_reply();
	if (_reply_check(reply) != 0) {
		if (reply)
			cvi_json_object_put(reply);
		return NULL;
	}

	return reply;
}

/* BORROWED result.params of a checked reply */
static struct cvi_json_object *_reply_params(struct cvi_json_object *reply)
{
	struct cvi_json_object *result;
	struct cvi_json_object *params = NULL;

	if (!reply)
		return NULL;

	if (!cvi_json_object_object_get_ex(reply, "result", &result))
		return NULL;

	cvi_json_object_object_get_ex(result, "params", &params);
	return params;	/* may be NULL */
}

static int _reply_int_param(struct cvi_json_object *reply, const char *key, int *val)
{
	struct cvi_json_object *params = _reply_params(reply);
	struct cvi_json_object *obj;

	if (!params || !cvi_json_object_object_get_ex(params, key, &obj))
		return -1;

	*val = cvi_json_object_get_int(obj);
	return 0;
}

/*
 * Duplicate a string-typed reply field into a malloc'd buffer (caller frees).
 * Does NOT truncate — required for fields that can be large (e.g. "Reg dump
 * log" can be ~240 KB of JSON).
 * Returns 0 on success (*out is non-NULL even for empty strings), -1 if the
 * key is missing or the field is not a string.
 */
static int _reply_str_dup(struct cvi_json_object *reply, const char *key,
			  char **out)
{
	struct cvi_json_object *params = _reply_params(reply);
	struct cvi_json_object *obj;
	const char *s;
	char *dup;

	*out = NULL;
	if (!params || !cvi_json_object_object_get_ex(params, key, &obj))
		return -1;

	s = cvi_json_object_get_string(obj);
	if (!s)
		return -1;

	dup = strdup(s);
	if (!dup)
		return -1;

	*out = dup;
	return 0;
}

/* ------------------------------------------------------------------ */
/* file helpers */

static int _read_text_file(const char *path, char **out, size_t *len)
{
	FILE *fp;
	long sz;
	char *buf;

	fp = fopen(path, "rb");
	if (!fp) {
		ISPD2_CLI_PRT("open %s failed\n", path);
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	sz = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if (sz < 0) {
		fclose(fp);
		return -1;
	}

	buf = malloc((size_t)sz + 1);
	if (!buf) {
		fclose(fp);
		return -1;
	}

	if (fread(buf, 1, (size_t)sz, fp) != (size_t)sz) {
		ISPD2_CLI_PRT("read %s failed\n", path);
		free(buf);
		fclose(fp);
		return -1;
	}
	fclose(fp);

	buf[sz] = '\0';
	*out = buf;
	*len = (size_t)sz;
	return 0;
}

static int _read_file(const char *path, unsigned char **out, size_t *len)
{
	return _read_text_file(path, (char **)out, len);
}

static int _write_file(const char *path, const unsigned char *buf, size_t len)
{
	FILE *fp;

	fp = fopen(path, "wb");
	if (!fp) {
		ISPD2_CLI_PRT("open %s for write failed\n", path);
		return -1;
	}

	if (fwrite(buf, 1, len, fp) != len) {
		ISPD2_CLI_PRT("write %s failed\n", path);
		fclose(fp);
		return -1;
	}
	fclose(fp);
	return 0;
}

/* ------------------------------------------------------------------ */
/* rpc.json module table */

struct module_entry {
	char name[64];	/* STRUCT */
	char get[64];	/* GET  */
	char set[64];	/* SET, "" = read-only */
};

static struct module_entry g_modules[MAX_MODULES];
static int g_module_cnt;

static void _modules_add(const char *name, const char *get, const char *set)
{
	if (g_module_cnt >= MAX_MODULES) {
		ISPD2_CLI_PRT("module table full (%d)\n", MAX_MODULES);
		return;
	}

	snprintf(g_modules[g_module_cnt].name, sizeof(g_modules[0].name), "%s", name);
	snprintf(g_modules[g_module_cnt].get, sizeof(g_modules[0].get), "%s", get);
	snprintf(g_modules[g_module_cnt].set, sizeof(g_modules[0].set), "%s", set ? set : "");
	g_module_cnt++;
}

static int _load_rpc_json(const char *path)
{
	char *text;
	size_t len;
	struct cvi_json_object *root;
	struct cvi_json_object *jsonrpc;
	struct cvi_json_object *method;
	size_t i;

	if (_read_text_file(path, &text, &len) != 0)
		return -1;

	root = cvi_json_tokener_parse(text);
	free(text);
	if (!root) {
		ISPD2_CLI_PRT("%s is not valid JSON\n", path);
		return -1;
	}

	if (!cvi_json_object_object_get_ex(root, "JSONRPC", &jsonrpc) ||
	    !cvi_json_object_object_get_ex(jsonrpc, "METHOD", &method) ||
	    !cvi_json_object_is_type(method, cvi_json_type_array)) {
		ISPD2_CLI_PRT("%s: unexpected rpc.json layout\n", path);
		cvi_json_object_put(root);
		return -1;
	}

	g_module_cnt = 0;
	for (i = 0; i < cvi_json_object_array_length(method); i++) {
		struct cvi_json_object *entry = cvi_json_object_array_get_idx(method, i);
		struct cvi_json_object *obj;
		const char *name = "";
		const char *get = "";
		const char *set = "";

		if (cvi_json_object_object_get_ex(entry, "STRUCT", &obj))
			name = cvi_json_object_get_string(obj);
		if (cvi_json_object_object_get_ex(entry, "GET", &obj))
			get = cvi_json_object_get_string(obj);
		if (cvi_json_object_object_get_ex(entry, "SET", &obj))
			set = cvi_json_object_get_string(obj);

		/*
		 * skip VI/VPSS entries — this UT has no VPSS and the
		 * daemon's VI handlers need a bound chn; both would only
		 * add noise
		 */
		if (strncmp(get, "CVI_VI_", 7) == 0 || strncmp(get, "CVI_VPSS_", 9) == 0) {
			ISPD2_CLI_PRT("skip non-ISP entry %s\n", get);
			continue;
		}

		_modules_add(name, get, set);
	}

	cvi_json_object_put(root);
	ISPD2_CLI_PRT("loaded %d modules from %s\n", g_module_cnt, path);
	return 0;
}

/* ------------------------------------------------------------------ */

/*
 * exit: create the trigger file the isp_test_ut host polls for (signals
 * are not usable on this board). The host unlinks the file, then runs
 * its full teardown (ISP exit → VI stop → VB/SYS exit). We wait for the
 * file to disappear as the handshake; on timeout we remove it ourselves
 * so a stale trigger cannot kill a later host run.
 */
static int _do_exit(void)
{
	int fd;
	int i;

	unlink(EXIT_TRIGGER);	/* clear any stale trigger first */
	fd = open(EXIT_TRIGGER, O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (fd < 0) {
		ISPD2_CLI_PRT("create %s failed\n", EXIT_TRIGGER);
		return 1;
	}
	close(fd);
	printf("exit: trigger created, waiting for isp_test_ut ...\n");

	for (i = 0; i < EXIT_TIMEOUT_SEC * 2; i++) {
		if (access(EXIT_TRIGGER, F_OK) != 0) {
			printf("exit: host picked up the trigger, teardown in progress\n");
			return 0;
		}
		usleep(500 * 1000);
	}

	unlink(EXIT_TRIGGER);
	ISPD2_CLI_PRT("isp_test_ut did not respond within %d s (is it running?)\n",
		EXIT_TIMEOUT_SEC);
	return 1;
}

/* ------------------------------------------------------------------ */
/* operations */

/*
 * readall: GET every module, collect result.params under the method
 * name, save the aggregate as pretty JSON
 */
static int _do_readall(void)
{
	struct cvi_json_object *all;
	int ok = 0, ng = 0;
	int i;
	const char *str;

	all = cvi_json_object_new_object();

	for (i = 0; i < g_module_cnt; i++) {
		struct cvi_json_object *reply = _rpc(g_modules[i].get, NULL);
		struct cvi_json_object *params;

		if (!reply) {
			ISPD2_CLI_PRT("get %-50s NG\n", g_modules[i].get);
			ng++;
			continue;
		}

		params = _reply_params(reply);
		if (params) {
			/*
			 * object_add steals the ref → bump so reply's
			 * put leaves the entry alive inside `all`
			 */
			cvi_json_object_get(params);
			cvi_json_object_object_add(all, g_modules[i].get, params);
			ok++;
		} else {
			ng++;
		}
		cvi_json_object_put(reply);
	}

	/* gamma curve is fetched per-type and not listed in rpc.json */
	{
		struct cvi_json_object *reply;
		struct cvi_json_object *params;
		struct cvi_json_object *curve_type;

		curve_type = cvi_json_object_new_object();
		cvi_json_object_object_add(curve_type, "curveType", cvi_json_object_new_int(0));

		reply = _rpc("CVI_ISP_GetGammaCurveByType", curve_type);
		if (reply) {
			params = _reply_params(reply);
			if (params) {
				cvi_json_object_get(params);
				cvi_json_object_object_add(all, "CVI_ISP_GetGammaCurveByType", params);
				ok++;
			} else {
				ng++;
			}
			cvi_json_object_put(reply);
		} else {
			ng++;
		}
	}

	str = cvi_json_object_to_cvi_json_string_ext(all, JSON_C_TO_STRING_PRETTY);
	if (_write_file(OUT_READALL, (const unsigned char *)str, strlen(str)) != 0) {
		cvi_json_object_put(all);
		ISPD2_CLI_PRT("readall: %d ok, %d failed (NOT saved)\n", ok, ng);
		return 1;
	}

	printf("readall: %d ok, %d failed, saved to %s\n", ok, ng, OUT_READALL);
	cvi_json_object_put(all);
	return ng ? 1 : 0;
}

/*
 * writeall: for each module GET the current params, then SET them back
 * verbatim (roundtrip). Flat GET params are byte-identical to SET params
 * on the wire — see plan fact sheet — so no transform is needed.
 */
static int _do_writeall(void)
{
	int ok = 0, ng = 0, skip = 0;
	int i;

	for (i = 0; i < g_module_cnt; i++) {
		struct cvi_json_object *reply;
		struct cvi_json_object *params;
		struct cvi_json_object *set_reply;

		if (g_modules[i].set[0] == '\0') {
			ISPD2_CLI_PRT("skip %-50s (read-only)\n", g_modules[i].get);
			skip++;
			continue;
		}

		reply = _rpc(g_modules[i].get, NULL);
		if (!reply) {
			ISPD2_CLI_PRT("get %-50s NG\n", g_modules[i].get);
			ng++;
			continue;
		}

		params = _reply_params(reply);
		if (!params) {
			ISPD2_CLI_PRT("get %-50s returned no params\n", g_modules[i].get);
			ng++;
			cvi_json_object_put(reply);
			continue;
		}

		/* bump so the SET keeps the object alive after reply's put */
		cvi_json_object_get(params);
		set_reply = _rpc(g_modules[i].set, params);
		if (set_reply) {
			ISPD2_CLI_PRT("set %-50s OK\n", g_modules[i].set);
			ok++;
			cvi_json_object_put(set_reply);
		} else {
			ISPD2_CLI_PRT("set %-50s NG\n", g_modules[i].set);
			ng++;
		}
		cvi_json_object_put(reply);
	}

	printf("writeall: %d ok, %d failed, %d skipped (read-only)\n", ok, ng, skip);
	return ng ? 1 : 0;
}

/*
 * dumpyuv: dump one NV12 frame from VI chn 0. CVI_GetMultipleYUVFrame
 * prepares the frame, then CVI_GetImageData streams [TYUVHeader][pixels]
 * with no JSON reply (-32300 path).
 *
 * out_file: explicit output file path (CLI --out). If NULL, falls back to
 *           <out_dir>/isp_dump.yuv, or the fixed OUT_YUV path when out_dir
 *           is also NULL.
 * out_dir:  directory to save YUV file into (used by dumpall). Ignored when
 *           out_file is set.
 */
static int _do_dumpyuv(const char *out_dir, const char *out_file)
{
	/* +64 so appending "/isp_dump.yuv" to a 256-byte out_dir cannot truncate */
	char yuv_path[256 + 64];
	struct cvi_json_object *params;
	struct cvi_json_object *reply;
	int data_size = 0;
	unsigned char *buf = NULL;
	TYUVHeader hdr;
	int ret;

	/*
	 * Output path precedence:
	 *   out_file (CLI --out)  > <out_dir>/isp_dump.yuv (dumpall) > OUT_YUV
	 * out_file is used verbatim, so a bare name lands in the cwd and an
	 * absolute path is honored as-is.
	 */
	if (out_file)
		snprintf(yuv_path, sizeof(yuv_path), "%s", out_file);
	else if (out_dir)
		snprintf(yuv_path, sizeof(yuv_path), "%s/isp_dump.yuv", out_dir);
	else
		snprintf(yuv_path, sizeof(yuv_path), "%s", OUT_YUV);

	params = cvi_json_object_new_object();
	cvi_json_object_object_add(params, "frames", cvi_json_object_new_int(1));
	cvi_json_object_object_add(params, "tightly", cvi_json_object_new_int(0));
	cvi_json_object_object_add(params, "from", cvi_json_object_new_int(0));

	reply = _rpc("CVI_GetMultipleYUVFrame", params);
	if (!reply)
		return 1;

	if (_reply_int_param(reply, "Data size", &data_size) != 0 || data_size <= 0) {
		ISPD2_CLI_PRT("no frame captured (Data size=%d)\n", data_size);
		cvi_json_object_put(reply);
		return 1;
	}
	cvi_json_object_put(reply);

	/* triggers the binary stream: JSON reply suppressed (-32300) */
	if (ispd2_send_request("CVI_GetImageData", NULL) != 0)
		return 1;

	ret = ispd2_recv_binary((size_t)data_size, &buf);
	if (ret != 0) {
		ISPD2_CLI_PRT("recv image data failed\n");
		return 1;
	}

	memcpy(&hdr, buf, sizeof(hdr));
	printf("yuv frame: %ux%u stride %u/%u/%u size %u curFrame %u\n",
		hdr.width, hdr.height, hdr.stride[0], hdr.stride[1], hdr.stride[2],
		hdr.size, hdr.curFrame);

	if ((uint32_t)data_size < sizeof(hdr) || hdr.size + sizeof(hdr) != (uint32_t)data_size)
		ISPD2_CLI_PRT("warn: Data size(%d) != header.size(%u)+%zu\n",
			data_size, hdr.size, sizeof(hdr));

	ret = _write_file(yuv_path, buf + sizeof(hdr), (size_t)data_size - sizeof(hdr));
	free(buf);
	if (ret != 0)
		return 1;

	printf("dumpyuv: saved %d bytes (payload) to %s\n",
		data_size - (int)sizeof(hdr), yuv_path);
	return 0;
}

/*
 * dump_cfg.ini: optional per-run knobs for dumpraw/dumpall.
 * Simple key=value (no section), # comments, missing key/file → default.
 * Only looked up under /mnt/data/ on the board.
 */
#define DUMP_CFG_PATH		DEFAULT_OUT_DIR "/dump_cfg.ini"

struct dump_cfg {
	int frames;
	int tightly;
	int dump_reg;
	int dump_raw;
	int save_raw;
	int save_log;
};

static void _dump_cfg_defaults(struct dump_cfg *c)
{
	c->frames = 1;
	c->tightly = 0;
	c->dump_reg = 1;
	c->dump_raw = 1;
	c->save_raw = 1;
	c->save_log = 1;
}

static int _parse_kv(const char *line, char *key, size_t ksz,
		     char *val, size_t vsz)
{
	const char *p, *v;
	size_t kl, vl;

	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '#' || *line == ';' || *line == '\0' || *line == '\n')
		return -1;
	p = strchr(line, '=');
	if (!p)
		return -1;
	kl = (size_t)(p - line);
	while (kl > 0 && (line[kl - 1] == ' ' || line[kl - 1] == '\t'))
		kl--;
	if (kl == 0 || kl >= ksz)
		return -1;
	memcpy(key, line, kl);
	key[kl] = '\0';

	v = p + 1;
	while (*v == ' ' || *v == '\t')
		v++;
	vl = strlen(v);
	while (vl > 0 && (v[vl - 1] == '\n' || v[vl - 1] == '\r' ||
			  v[vl - 1] == ' ' || v[vl - 1] == '\t'))
		vl--;
	if (vl >= vsz)
		return -1;
	memcpy(val, v, vl);
	val[vl] = '\0';
	return 0;
}

static void _load_dump_cfg(struct dump_cfg *c)
{
	FILE *fp;
	char line[256];
	char key[64], val[64];

	_dump_cfg_defaults(c);

	if (access(DUMP_CFG_PATH, R_OK) != 0) {
		ISPD2_CLI_PRT("dump_cfg.ini not found (%s); using defaults\n",
			DUMP_CFG_PATH);
		return;
	}

	fp = fopen(DUMP_CFG_PATH, "r");
	if (!fp) {
		ISPD2_CLI_PRT("open %s failed; using defaults\n", DUMP_CFG_PATH);
		return;
	}

	ISPD2_CLI_PRT("loading dump config from %s\n", DUMP_CFG_PATH);
	while (fgets(line, sizeof(line), fp)) {
		if (_parse_kv(line, key, sizeof(key), val, sizeof(val)) != 0)
			continue;
		if (strcmp(key, "frames") == 0)
			c->frames = atoi(val);
		else if (strcmp(key, "tightly") == 0)
			c->tightly = atoi(val);
		else if (strcmp(key, "dump_reg") == 0)
			c->dump_reg = atoi(val);
		else if (strcmp(key, "dump_raw") == 0)
			c->dump_raw = atoi(val);
		else if (strcmp(key, "save_raw") == 0)
			c->save_raw = atoi(val);
		else if (strcmp(key, "save_log") == 0)
			c->save_log = atoi(val);
		else
			ISPD2_CLI_PRT("dump_cfg: unknown key '%s', ignored\n", key);
	}
	fclose(fp);

	/* sanity bounds */
	if (c->frames < 1)
		c->frames = 1;
	if (c->frames > 256)
		c->frames = 256;
	c->tightly = c->tightly ? 1 : 0;
	c->dump_reg = c->dump_reg ? 1 : 0;
	c->dump_raw = c->dump_raw ? 1 : 0;
	c->save_raw = c->save_raw ? 1 : 0;
	c->save_log = c->save_log ? 1 : 0;

	ISPD2_CLI_PRT("dump config: frames=%d tightly=%d dump_reg=%d dump_raw=%d save_raw=%d save_log=%d\n",
		c->frames, c->tightly, c->dump_reg, c->dump_raw, c->save_raw, c->save_log);
}

/*
 * Create a timestamped dump directory under DEFAULT_OUT_DIR.
 * prefix: e.g. "dumpraw" or "dumpall".
 * out: buffer receiving the full directory path (e.g.
 *      "/mnt/data/dumpraw_20260903_154321").
 * outsz: size of out.
 * Returns 0 on success, -1 on error.
 */
static int _make_dump_dir(const char *prefix, char *out, size_t outsz)
{
	time_t t;
	struct tm tm;

	t = time(NULL);
	localtime_r(&t, &tm);
	snprintf(out, outsz, "%s/%s_%04d%02d%02d_%02d%02d%02d",
		DEFAULT_OUT_DIR, prefix,
		tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
		tm.tm_hour, tm.tm_min, tm.tm_sec);

	if (mkdir(out, 0755) != 0 && errno != EEXIST) {
		ISPD2_CLI_PRT("mkdir %s failed: %s\n", out, strerror(errno));
		return -1;
	}
	return 0;
}

/*
 * dumpraw: dump raw frames from pipe 0 + ISP register/3A log. Params driven
 * by dump_cfg.ini (frames/tightly/dump_reg/dump_raw); same binary handshake
 * as dumpyuv — prepare RPC, then CVI_GetImageData streams [header][pixels].
 *
 * out_dir: directory to save raw + log files into. If NULL, a new timestamped
 *          directory "dumpraw_<YYYYmmdd_HHMMSS>" is created under DEFAULT_OUT_DIR.
 */
static int _do_dumpraw(const char *out_dir)
{
	static const char *const keys[] = {
		"Reg dump log", "Raw info log", "AE log", "AWB log",
	};
	static const char *const log_names[] = {
		"isp_reg_dump.json", "isp_raw_info.log", "isp_ae.log", "isp_awb.log",
	};
	char dir_buf[256];
	/*
	 * log_paths / out_raw_path append to dir_buf ("/isp_dump.raw" = 13
	 * bytes), so size them strictly larger than dir_buf to silence
	 * -Werror=format-truncation= (out_dir may alias dir_buf).
	 */
	char log_paths[4][sizeof(dir_buf) + 64];
	char out_raw_path[sizeof(dir_buf) + 64];
	struct dump_cfg cfg;
	struct cvi_json_object *params;
	struct cvi_json_object *reply;
	int data_size = 0;
	unsigned char *buf = NULL;
	char *log_str = NULL;
	TRAWHeader hdr;
	size_t k;
	int ret;

	if (!out_dir) {
		if (_make_dump_dir("dumpraw", dir_buf, sizeof(dir_buf)) != 0)
			return 1;
		out_dir = dir_buf;
	}
	for (k = 0; k < ARRAY_SIZE(log_names); k++)
		snprintf(log_paths[k], sizeof(log_paths[k]), "%s/%s",
			out_dir, log_names[k]);
	snprintf(out_raw_path, sizeof(out_raw_path), "%s/isp_dump.raw", out_dir);

	_load_dump_cfg(&cfg);

	if (cfg.frames > 1 && !cfg.tightly)
		ISPD2_CLI_PRT("warn: non-tightly mode only supports 1 frame; daemon may reject\n");

	params = cvi_json_object_new_object();
	cvi_json_object_object_add(params, "frames", cvi_json_object_new_int(cfg.frames));
	cvi_json_object_object_add(params, "tightly", cvi_json_object_new_int(cfg.tightly));
	cvi_json_object_object_add(params, "dump_reg", cvi_json_object_new_int(cfg.dump_reg));
	cvi_json_object_object_add(params, "dump_raw", cvi_json_object_new_int(cfg.dump_raw));

	reply = _rpc("CVI_GetMultipleRAWFrame", params);
	if (!reply)
		return 1;

	for (k = 0; k < ARRAY_SIZE(keys); k++) {
		free(log_str);
		log_str = NULL;
		if (_reply_str_dup(reply, keys[k], &log_str) == 0 && log_str) {
			size_t log_len = strlen(log_str);

			/*
			 * Summary to console; full content to protocol log
			 * (visible on console only with -v / --verbose).
			 */
			ISPD2_CLI_PRT("--- %s --- (%zu bytes)\n", keys[k], log_len);
			ispd2_rpc_log("--- %s --- (%zu bytes)\n%s%s\n",
				keys[k], log_len,
				log_str,
				log_len && log_str[log_len - 1] != '\n' ? "\n" : "");

			/*
			 * Warn when Reg dump log looks bogus (kernel VI driver
			 * sometimes returns garbage/empty data in patgen mode).
			 */
			if (strcmp(keys[k], "Reg dump log") == 0) {
				unsigned char first = log_len ? (unsigned char)log_str[0] : 0;

				if (log_len < 16 || log_str[0] != '{')
					ISPD2_CLI_PRT("warn: bad Reg dump log (%zu B, 0x%02x)\n", log_len, first);
			}

			if (cfg.save_log) {
				if (_write_file(log_paths[k],
				    (const unsigned char *)log_str, log_len) == 0)
					ISPD2_CLI_PRT("  -> saved to %s\n", log_paths[k]);
				else
					ISPD2_CLI_PRT("  -> write %s failed\n", log_paths[k]);
			}
		} else {
			ISPD2_CLI_PRT("%s: not present in reply\n", keys[k]);
		}
	}
	free(log_str);
	log_str = NULL;

	if (_reply_int_param(reply, "Data size", &data_size) != 0 || data_size <= 0) {
		ISPD2_CLI_PRT("no raw captured (Data size=%d)\n", data_size);
		cvi_json_object_put(reply);
		return 1;
	}
	cvi_json_object_put(reply);

	if (ispd2_send_request("CVI_GetImageData", NULL) != 0)
		return 1;

	ret = ispd2_recv_binary((size_t)data_size, &buf);
	if (ret != 0) {
		ISPD2_CLI_PRT("recv image data failed\n");
		return 1;
	}

	memcpy(&hdr, buf, sizeof(hdr));
	printf("raw frame: %ux%u stride %u bayerID %u compress %u crop %ux%u+%u,%u size %u\n"
		"  iso %u colorTemp %u wbR %u wbB %u exposureRatio %u\n",
		hdr.width, hdr.height, hdr.stride[0], hdr.bayerID, hdr.compress,
		hdr.cropWidth, hdr.cropHeight, hdr.cropX, hdr.cropY, hdr.size,
		hdr.iso, hdr.colorTemp, hdr.wbRGain, hdr.wbBGain, hdr.exposureRatio);

	if ((uint32_t)data_size < sizeof(hdr) || hdr.size + sizeof(hdr) != (uint32_t)data_size)
		ISPD2_CLI_PRT("warn: Data size(%d) != header.size(%u)+%zu\n",
			data_size, hdr.size, sizeof(hdr));

	if (cfg.save_raw) {
		ret = _write_file(out_raw_path, buf + sizeof(hdr),
			(size_t)data_size - sizeof(hdr));
		if (ret != 0) {
			free(buf);
			return 1;
		}
		printf("dumpraw: saved %d bytes (payload) to %s\n",
			data_size - (int)sizeof(hdr), out_raw_path);
	} else {
		printf("dumpraw: skip write (save_raw=0); payload=%d bytes\n",
			data_size - (int)sizeof(hdr));
	}
	if (out_dir)
		printf("dumpraw: output dir: %s\n", out_dir);
	free(buf);
	return 0;
}

/*
 * exportbin: CVI_ExportBinFile (all-string params, bin_type required)
 * prepares the tuning bin, then CVI_GetBinaryData{content:3} streams it.
 */
/*
 * dumpall: CviPQTool Capture page "Dump All" — YUV dump immediately
 * followed by RAW dump (with reg dump + 3A logs). The tool's param-save
 * step is a commented-out TODO upstream, so it is not simulated here.
 *
 * ALL outputs (YUV + raw + 4 logs + optional .raw) go into a single
 * timestamped directory "dumpall_<YYYYmmdd_HHMMSS>" under DEFAULT_OUT_DIR.
 */
static int _do_dumpall(void)
{
	char dir_buf[256];
	int ret;

	if (_make_dump_dir("dumpall", dir_buf, sizeof(dir_buf)) != 0)
		return 1;
	printf("dumpall: output dir: %s\n", dir_buf);

	printf("dumpall: === YUV ===\n");
	ret = _do_dumpyuv(dir_buf, NULL);

	printf("dumpall: === RAW ===\n");
	ret |= _do_dumpraw(dir_buf);

	return ret;
}

static int _do_exportbin(void)
{
	struct cvi_json_object *params;
	struct cvi_json_object *reply;
	int data_size = 0;
	unsigned char *buf = NULL;
	char time_str[32];
	time_t t;
	int ret;

	t = time(NULL);
	strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&t));

	params = cvi_json_object_new_object();
	cvi_json_object_object_add(params, "bin_type", cvi_json_object_new_string("All"));
	cvi_json_object_object_add(params, "author", cvi_json_object_new_string("isp_test_client"));
	cvi_json_object_object_add(params, "desp", cvi_json_object_new_string("exported by isp_test_client"));
	cvi_json_object_object_add(params, "time", cvi_json_object_new_string(time_str));
	cvi_json_object_object_add(params, "version", cvi_json_object_new_string("v1.0"));

	reply = _rpc("CVI_ExportBinFile", params);
	if (!reply)
		return 1;

	if (_reply_int_param(reply, "Data size", &data_size) != 0 || data_size <= 0) {
		ISPD2_CLI_PRT("export failed (Data size=%d)\n", data_size);
		cvi_json_object_put(reply);
		return 1;
	}
	cvi_json_object_put(reply);

	params = cvi_json_object_new_object();
	cvi_json_object_object_add(params, "content", cvi_json_object_new_int(3));
	if (ispd2_send_request("CVI_GetBinaryData", params) != 0)
		return 1;

	ret = ispd2_recv_binary((size_t)data_size, &buf);
	if (ret != 0) {
		ISPD2_CLI_PRT("recv bin data failed\n");
		return 1;
	}

	ret = _write_file(OUT_BIN, buf, (size_t)data_size);
	free(buf);
	if (ret != 0)
		return 1;

	printf("exportbin: saved %d bytes to %s\n", data_size, OUT_BIN);
	return 0;
}

/*
 * importbin: two-phase upload — CVI_SetBinaryData{content,size,bin_type}
 * gets an OK, then exactly `size` raw bytes, then a final JSON reply
 * (its id is 0/null on the wire — do not enforce id matching).
 */
static int _do_importbin(void)
{
	struct cvi_json_object *params;
	struct cvi_json_object *reply;
	unsigned char *buf = NULL;
	size_t len = 0;

	if (_read_file(OUT_BIN, &buf, &len) != 0) {
		ISPD2_CLI_PRT("read %s failed (run exportbin first?)\n", OUT_BIN);
		return 1;
	}

	params = cvi_json_object_new_object();
	cvi_json_object_object_add(params, "content", cvi_json_object_new_int(3));
	cvi_json_object_object_add(params, "size", cvi_json_object_new_int((int)len));
	cvi_json_object_object_add(params, "bin_type", cvi_json_object_new_string("All"));

	reply = _rpc("CVI_SetBinaryData", params);
	if (!reply) {
		free(buf);
		return 1;
	}
	cvi_json_object_put(reply);

	if (ispd2_send_binary(buf, len) != 0) {
		free(buf);
		return 1;
	}
	free(buf);

	/* final ack for the raw upload; only check for an error object */
	reply = ispd2_recv_reply();
	if (!reply || _reply_check(reply) != 0) {
		ISPD2_CLI_PRT("import final reply NG\n");
		if (reply)
			cvi_json_object_put(reply);
		return 1;
	}
	cvi_json_object_put(reply);

	printf("importbin: applied %zu bytes from %s\n", len, OUT_BIN);
	return 0;
}

/*
 * mmapen: CVI_ISP_SetMmapSnapEnable — the libisp per-frame TNR MO motion map
 * snapshot gate (~130KB cache invalidate + copy per frame at 1080p).
 * Sticky: it stays until mmapen 0 or the daemon exits, and the daemon ORs it
 * into the telemetry MoMap switch so the telemetry self-heal cannot push it
 * back off. Fails per pipe only when that pipe is not mapped/streaming, so a
 * plain "OK" means the request was accepted, not that a snapshot exists yet.
 */
static int _do_mmapen(int enable)
{
	struct cvi_json_object *params;
	struct cvi_json_object *reply;

	params = cvi_json_object_new_object();
	cvi_json_object_object_add(params, "Enable",
				   cvi_json_object_new_int(enable ? 1 : 0));

	reply = _rpc("CVI_ISP_SetMmapSnapEnable", params);
	if (!reply)
		return 1;
	cvi_json_object_put(reply);

	printf("mmapen: mo map snapshot %s\n", enable ? "ON" : "OFF");
	if (!enable) {
		/* README documents the exact CVI_SetTelemetryAttr {"MoMap":0} call */
		printf("mmapen: note: telemetry MoMap page still ORs into this gate\n");
	}
	return 0;
}

/*
 * mmapget: two-step snapshot fetch — CVI_ISP_GetMmapSts returns the JSON
 * info and latches one snapshot, CVI_ISP_GetMmapStsData streams that same
 * latched copy as [16B TMoMapStsHdr][2bpp data] with no JSON reply (-32300).
 * The 2bpp values are MoMp motion levels: 0 still / 1 transition / 2 motion,
 * 3 reserved (render as motion), so the histogram is a quick motion check.
 * Pipe: the client never sets one, the daemon uses the session default (0).
 */
static int _do_mmapget(const char *out_file)
{
	const char *path = out_file ? out_file : OUT_MOMAP;
	struct cvi_json_object *reply;
	unsigned char *buf = NULL;
	TMoMapStsHdr hdr;
	unsigned long long hist[4] = {0, 0, 0, 0};
	unsigned long long npix;
	int map_w = 0, map_h = 0, stride = 0, format = 0;
	int data_size = 0, frame_id = 0;
	uint32_t x, y;
	int i;
	int ret;

	reply = _rpc("CVI_ISP_GetMmapSts", NULL);
	if (!reply)
		return 1;

	if (_reply_int_param(reply, "Map width", &map_w) != 0 ||
	    _reply_int_param(reply, "Map height", &map_h) != 0 ||
	    _reply_int_param(reply, "Stride 2bpp", &stride) != 0 ||
	    _reply_int_param(reply, "Format", &format) != 0 ||
	    _reply_int_param(reply, "Data size", &data_size) != 0 ||
	    _reply_int_param(reply, "Frame id", &frame_id) != 0) {
		ISPD2_CLI_PRT("mmapget: incomplete info reply\n");
		cvi_json_object_put(reply);
		return 1;
	}
	cvi_json_object_put(reply);

	printf("mo map info: %dx%d stride %d format %d size %d frame %u\n",
	       map_w, map_h, stride, format, data_size, (unsigned int)frame_id);

	if (data_size <= 0 || data_size > MO_MAP_DATA_MAX) {
		ISPD2_CLI_PRT("mmapget: bad Data size %d (1..%d)\n",
			      data_size, MO_MAP_DATA_MAX);
		return 1;
	}

	/* triggers the binary stream: JSON reply suppressed (-32300) */
	if (ispd2_send_request("CVI_ISP_GetMmapStsData", NULL) != 0)
		return 1;

	ret = ispd2_recv_binary(sizeof(hdr) + (size_t)data_size, &buf);
	if (ret != 0) {
		/* ret == 1: daemon answered "NONE" (no snapshot latched) */
		ISPD2_CLI_PRT("recv mo map data failed (ret=%d, %d bytes requested)\n",
			      ret, (int)(sizeof(hdr) + (size_t)data_size));
		return 1;
	}

	memcpy(&hdr, buf, sizeof(hdr));

	/* the info step and the data step must describe the same snapshot */
	if (hdr.data_size != (uint32_t)data_size ||
	    (uint32_t)hdr.stride_2bpp * hdr.map_h != hdr.data_size ||
	    (uint32_t)hdr.map_w > (uint32_t)hdr.stride_2bpp * 4) {
		ISPD2_CLI_PRT("mmapget: header mismatch (size %u/%d, stride %u x h %u, w %u)\n",
			      hdr.data_size, data_size, hdr.stride_2bpp,
			      hdr.map_h, hdr.map_w);
		free(buf);
		return 1;
	}

	/* 2bpp histogram over map_w x map_h pixels (row tail padding ignored) */
	npix = (unsigned long long)hdr.map_w * hdr.map_h;
	for (y = 0; y < hdr.map_h; y++) {
		const unsigned char *row = buf + sizeof(hdr) +
					   (size_t)y * hdr.stride_2bpp;

		for (x = 0; x < hdr.map_w; x++)
			hist[(row[x >> 2] >> ((x & 3) * 2)) & 0x3]++;
	}

	printf("mo map: %ux%u stride %u format %u frame %u data %u bytes\n",
	       hdr.map_w, hdr.map_h, hdr.stride_2bpp, hdr.format,
	       hdr.frame_id, hdr.data_size);
	for (i = 0; i < 4; i++) {
		printf("  value %d: %10llu (%5.1f%%)\n", i, hist[i],
		       npix ? 100.0 * (double)hist[i] / (double)npix : 0.0);
	}

	ret = _write_file(path, buf + sizeof(hdr), (size_t)data_size);
	free(buf);
	if (ret != 0)
		return 1;

	printf("mmapget: saved %d bytes (2bpp payload) to %s\n", data_size, path);
	return 0;
}

/* ------------------------------------------------------------------ */

#define LOG_PATH		DEFAULT_OUT_DIR "/ispd2.log"

static void _usage(const char *prog)
{
	printf("usage: %s [-v] <op> [--ip IP] [--port PORT] [--rpc PATH] [--out PATH]\n"
	       "  op: readall | writeall | dumpall | dumpyuv | dumpraw | exportbin | importbin\n"
	       "      | mmapen <0|1> | mmapget | exit\n"
	       "  -v / --verbose: echo >> / << protocol messages to console (default: log file only)\n"
	       "  --out PATH: dumpyuv / mmapget output file (default " OUT_YUV " / " OUT_MOMAP ");\n"
	       "              relative paths land in the cwd\n"
	       "  mmapen <0|1>: TNR MO motion map snapshot gate (sticky, costs ~130KB/frame while on)\n"
	       "  defaults: ip " DEFAULT_IP ", port %d, rpc ./rpc.json or " DEFAULT_OUT_DIR "/rpc.json\n"
	       "  protocol log: " LOG_PATH " (overwritten each run)\n"
	       "  outputs under " DEFAULT_OUT_DIR "/\n"
	       "  exit: trigger-file handshake with the isp_test_ut host (full teardown)\n",
	       prog, DEFAULT_PORT);
}

int main(int argc, char *argv[])
{
	const char *op = NULL;
	const char *ip = DEFAULT_IP;
	int port = DEFAULT_PORT;
	const char *rpc = NULL;
	const char *out = NULL;		/* dumpyuv / mmapget output file override (--out) */
	const char *op_arg = NULL;	/* mmapen positional argument (<0|1>) */
	int verbose = 0;
	int i;
	int need_rpc;
	int ret;
	int arg_start;

	if (argc < 2) {
		_usage(argv[0]);
		return 1;
	}

	/* -v / --verbose can appear before the op */
	arg_start = 1;
	while (arg_start < argc &&
	       (strcmp(argv[arg_start], "-v") == 0 ||
		strcmp(argv[arg_start], "--verbose") == 0)) {
		verbose = 1;
		arg_start++;
	}

	if (arg_start >= argc) {
		_usage(argv[0]);
		return 1;
	}
	op = argv[arg_start];
	for (i = arg_start + 1; i < argc; i++) {
		if (strcmp(argv[i], "--ip") == 0) {
			ip = argv[++i];
		} else if (strcmp(argv[i], "--port") == 0) {
			port = atoi(argv[++i]);
		} else if (strcmp(argv[i], "--rpc") == 0) {
			rpc = argv[++i];
		} else if (strcmp(argv[i], "--out") == 0) {
			out = argv[++i];
		} else if (strcmp(argv[i], "-v") == 0 ||
			   strcmp(argv[i], "--verbose") == 0) {
			verbose = 1;
		} else if (strcmp(op, "mmapen") == 0 && !op_arg) {
			op_arg = argv[i];	/* mmapen <0|1> */
		} else {
			_usage(argv[0]);
			return 1;
		}
	}

	/*
	 * Open protocol log (overwrite). Errors always go to console via
	 * ISPD2_CLI_PRT; >> / << go to this file (and console if -v).
	 */
	ispd2_open_log(LOG_PATH);
	ispd2_set_verbose(verbose);

	need_rpc = (strcmp(op, "readall") == 0) || (strcmp(op, "writeall") == 0);
	if (!need_rpc &&
	    strcmp(op, "dumpyuv") && strcmp(op, "dumpraw") &&
	    strcmp(op, "dumpall") &&
	    strcmp(op, "exportbin") && strcmp(op, "importbin") &&
	    strcmp(op, "mmapen") && strcmp(op, "mmapget") &&
	    strcmp(op, "exit")) {
		_usage(argv[0]);
		return 1;
	}

	if (strcmp(op, "mmapen") == 0) {
		/* strict: only the literals "0" / "1" are accepted */
		if (!op_arg || (strcmp(op_arg, "0") != 0 && strcmp(op_arg, "1") != 0)) {
			ISPD2_CLI_PRT("mmapen needs <0|1>\n");
			_usage(argv[0]);
			return 1;
		}
	}

	if (need_rpc && !rpc) {
		/* ./rpc.json first, then /mnt/data/rpc.json */
		if (access("./rpc.json", R_OK) == 0) {
			rpc = "./rpc.json";
		} else if (access(DEFAULT_OUT_DIR "/rpc.json", R_OK) == 0) {
			rpc = DEFAULT_OUT_DIR "/rpc.json";
		} else {
			ISPD2_CLI_PRT("rpc.json not found (./rpc.json, " DEFAULT_OUT_DIR "/rpc.json); use --rpc\n");
			return 1;
		}
	}

	if (need_rpc && _load_rpc_json(rpc) != 0)
		return 1;

	/* exit needs no TCP — it must work even when the daemon is wedged */
	if (strcmp(op, "exit") == 0)
		return _do_exit();

	if (ispd2_connect(ip, port) != 0)
		return 1;

	if (strcmp(op, "readall") == 0)
		ret = _do_readall();
	else if (strcmp(op, "writeall") == 0)
		ret = _do_writeall();
	else if (strcmp(op, "dumpyuv") == 0)
		ret = _do_dumpyuv(NULL, out);
	else if (strcmp(op, "dumpraw") == 0)
		ret = _do_dumpraw(NULL);
	else if (strcmp(op, "dumpall") == 0)
		ret = _do_dumpall();
	else if (strcmp(op, "exportbin") == 0)
		ret = _do_exportbin();
	else if (strcmp(op, "importbin") == 0)
		ret = _do_importbin();
	else if (strcmp(op, "mmapen") == 0)
		ret = _do_mmapen(op_arg[0] == '1');
	else if (strcmp(op, "mmapget") == 0)
		ret = _do_mmapget(out);
	else {
		_usage(argv[0]);
		ret = 1;
	}

	ispd2_close();
	ispd2_close_log();
	return ret;
}
