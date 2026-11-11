/* ISP bring-up/teardown for isp_pattern / isp_sensor — trimmed from
 * self_test/vi_ut/vi_ut_isp_helper.c (patgen path only).
 *
 * Deviations from vi_ut (deliberate, see plan):
 * - daemon2 is ALWAYS started (vi_ut skips it in patgen mode);
 * - isp_readpramfrombin() dropped (patgen never loads pqbin in vi_ut);
 * - sensor / raw-replay pub-attr paths dropped;
 * - ISP_TEST_ISP_Exit guards isp_daemon2_uninit() on g_ISPDaemon.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>	/* strncasecmp */
#include <unistd.h>
#include <pthread.h>
#include <sys/prctl.h>

#include "cvi_awb.h"
#include "cvi_ae.h"
#include "cvi_af.h"
#include "cvi_comm_sns.h"
#include "cvi_isp.h"
#include "cvi_ispd2.h"
#include "cvi_sensor.h"
#include "cvi_bin.h"

#include "isp_pattern_isp.h"

#define CVI_AE_LIB_NAME "cvi_ae_lib"
#define CVI_AWB_LIB_NAME "cvi_awb_lib"
#define CVI_AF_LIB_NAME "cvi_af_lib"

static pthread_t g_IspPid[VI_MAX_DEV_NUM];
static int g_ISPDaemon;
static int g_ISPCount;

static int isp_get_isp_attr_bypatgen(int pipe, ISP_TEST_PATGEN_CONFIG_S *patgen_config,
		ISP_PUB_ATTR_S *pub_attr);
static int isp_get_isp_attr_bysensor(int pipe, ISP_TEST_PATGEN_CONFIG_S *config,
		ISP_PUB_ATTR_S *pub_attr);
static int _getFileSize(FILE *fp, CVI_U32 *size);
static int isp_readpramfrombin(void);
static void *isp_run_thread(void *arg);
static int isp_awblib_callback(int pipe);
static int isp_aelib_callback(int pipe);
static int isp_aflib_callback(int pipe);
static int isp_awblib_uncallback(int pipe);
static int isp_aelib_uncallback(int pipe);
static int isp_aflib_uncallback(int pipe);
static int isp_start(int pipe, ISP_TEST_PATGEN_CONFIG_S *patgen_config);
static int isp_run(int pipe);
static void isp_stop(int pipe);

static const char *compress_mode_name(COMPRESS_MODE_E mode)
{
	switch (mode) {
	case COMPRESS_MODE_NONE:  return "none";
	case COMPRESS_MODE_TILE:  return "tile";
	case COMPRESS_MODE_LINE:  return "line";
	case COMPRESS_MODE_FRAME: return "frame";
	default:                  return "unknown";
	}
}

/* Map an ini value (name or 0..3) to COMPRESS_MODE_E; -1 if unrecognised. */
static int compress_mode_from_str(const char *val)
{
	if (!strncasecmp(val, "none", 5) || !strcmp(val, "0"))
		return COMPRESS_MODE_NONE;
	if (!strncasecmp(val, "tile", 5) || !strcmp(val, "1"))
		return COMPRESS_MODE_TILE;
	if (!strncasecmp(val, "line", 5) || !strcmp(val, "2"))
		return COMPRESS_MODE_LINE;
	if (!strncasecmp(val, "frame", 6) || !strcmp(val, "3"))
		return COMPRESS_MODE_FRAME;
	return -1;
}

int ISP_UT_ParseConfig(ISP_UT_CFG_S *cfg)
{
	const char *input_src = "default";
	const char *cm_src = "default";
	FILE *fp;

	/* defaults */
	cfg->is_sensor_mode = 1;
	cfg->compress_mode = COMPRESS_MODE_TILE;

	fp = fopen(ISP_UT_CFG_FILE, "r");
	if (!fp) {
		ISP_TEST_PRT("%s not found, using defaults (input=sensor, compress_mode=tile)\n",
			     ISP_UT_CFG_FILE);
		goto out;
	}

	{
		char line[256];

		while (fgets(line, sizeof(line), fp)) {
			char key[64], val[64];
			int m;

			if (sscanf(line, " %63[a-zA-Z_] = %63s", key, val) != 2)
				continue;

			if (!strcmp(key, "input")) {
				if (!strcasecmp(val, "pattern")) {
					cfg->is_sensor_mode = 0;
					input_src = ISP_UT_CFG_FILE;
				} else if (!strcasecmp(val, "sensor")) {
					cfg->is_sensor_mode = 1;
					input_src = ISP_UT_CFG_FILE;
				} else {
					ISP_TEST_PRT("[WARN] bad input='%s' in %s, using sensor\n",
						     val, ISP_UT_CFG_FILE);
				}
			} else if (!strcmp(key, "compress_mode")) {
				m = compress_mode_from_str(val);
				if (m < 0) {
					ISP_TEST_PRT("[WARN] bad compress_mode='%s' in %s, using tile\n",
						     val, ISP_UT_CFG_FILE);
				} else {
					cfg->compress_mode = (COMPRESS_MODE_E)m;
					cm_src = ISP_UT_CFG_FILE;
				}
			}
		}
		fclose(fp);
	}

out:
	ISP_TEST_PRT("config: input=%s (from %s), compress_mode=%s (from %s)\n",
		     cfg->is_sensor_mode ? "sensor" : "pattern", input_src,
		     compress_mode_name(cfg->compress_mode), cm_src);
	return 0;
}

int ISP_TEST_ISP_Init(VI_PIPE pipe, ISP_TEST_PATGEN_CONFIG_S *patgen_config)
{
	int ret = 0;

	ISP_TEST_PRT("isp init %d\n", pipe);

	ret = isp_start(pipe, patgen_config);
	if (ret != 0) {
		ISP_TEST_PRT("Error: isp start pipe: %d fail!\n", pipe);
		return -1;
	}

	/* sensor mode loads pqbin for 3A tuning; patgen output is synthetic */
	if (patgen_config->is_sensor_mode) {
		isp_readpramfrombin();
		ISP_TEST_PRT("Load the pqbin!\n");
	}

	ret = isp_run(pipe);
	if (ret != 0) {
		ISP_TEST_PRT("Error: isp run pipe: %d fail!\n", pipe);
		return -1;
	}

	g_ISPCount++;

	return 0;
}

int ISP_TEST_ISP_Exit(VI_PIPE pipe)
{
	g_ISPCount--;

	isp_stop(pipe);

	if (!g_ISPCount && g_ISPDaemon)
		isp_daemon2_uninit();

	return 0;
}

static int isp_run(int pipe)
{
	ISP_TEST_PRT("isp run\n");
	int ret = 0;
	int *arg = malloc(sizeof(*arg));
	struct sched_param param;
	pthread_attr_t attr;

	if (arg == NULL) {
		ISP_TEST_PRT("Error: malloc failed\n");
		goto out;
	}

	*arg = pipe;
	param.sched_priority = 80;

	pthread_attr_init(&attr);
	pthread_attr_setschedpolicy(&attr, SCHED_RR);
	pthread_attr_setschedparam(&attr, &param);
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);

	ret = pthread_create(&g_IspPid[pipe], &attr, isp_run_thread, arg);
	if (ret != 0) {
		ISP_TEST_PRT("Error: create isp running thread failed!, error: %d, %s\r\n",
					ret, strerror(ret));
		goto out;
	}

	/*
	 * vi_ut skips daemon2 in patgen mode (g_isPatgenMode); isp_pattern
	 * exists to serve rpcjson clients, so start it unconditionally.
	 */
	if (!g_ISPDaemon) {
		ISP_TEST_PRT("--------- isp daemon2 init (port %d)\n", JSONRPC_PORT);
		isp_daemon2_init(JSONRPC_PORT);
		g_ISPDaemon = 1;
	}
out:
	return ret;
}

static void isp_stop(int pipe)
{
	int ret;

	if (g_IspPid[pipe]) {
		ret = CVI_ISP_Exit(pipe);
		if (ret != 0) {
			ISP_TEST_PRT("Error: CVI_ISP_Exit fail with pipe: %d\n", pipe);
			return;
		}

		pthread_join(g_IspPid[pipe], NULL);
		g_IspPid[pipe] = 0;

		isp_awblib_uncallback(pipe);
		isp_aelib_uncallback(pipe);
		isp_aflib_uncallback(pipe);
	}
}

static void *isp_run_thread(void *arg)
{
	int ret = 0;
	int pipe = *(int *)arg;
	char szThreadName[20];

	free(arg);
	snprintf(szThreadName, sizeof(szThreadName), "ISP%d_RUN", pipe);
	prctl(PR_SET_NAME, szThreadName, 0, 0, 0);

	if (pipe > 0) {
		ISP_TEST_PRT("ISP Dev %d return\n", pipe);
		return NULL;
	}

	ISP_TEST_PRT("ISP Dev %d running!\n", pipe);
	ret = CVI_ISP_Run(pipe);
	ret = 0;
	if (ret != 0)
		ISP_TEST_PRT("Error: CVI_ISP_Run failed with %#x!\n", ret);

	return NULL;
}

static int isp_get_isp_attr_bypatgen(int pipe, ISP_TEST_PATGEN_CONFIG_S *patgen_config,
		ISP_PUB_ATTR_S *pub_attr)
{
	UNUSED(pipe);
	int ret = 0;

	if (patgen_config == NULL) {
		ISP_TEST_PRT("Error: no patgen information!\n");
		return -1;
	}

	pub_attr->stSnsSize.u32Width = patgen_config->width;
	pub_attr->stSnsSize.u32Height = patgen_config->height;
	pub_attr->stWndRect.u32Width = patgen_config->width;
	pub_attr->stWndRect.u32Height = patgen_config->height;

	pub_attr->enWDRMode = patgen_config->wdr_mode;

	if (patgen_config->frame_rate > 0) {
		pub_attr->f32FrameRate = patgen_config->frame_rate;
	} else {
		pub_attr->f32FrameRate = 30;
	}

	pub_attr->enBayer = patgen_config->bayer_id;

	return ret;
}

/*
 * isp_get_isp_attr_bysensor: read pub_attr from /mnt/data/sensor_cfg.ini
 * via CVI_SNS_ParseIni + CVI_SNS_GetConfigInfo. Same fields as patgen,
 * plus u8LaneNum / u8EnableMaster which only the sensor path needs.
 */
static int isp_get_isp_attr_bysensor(int pipe, ISP_TEST_PATGEN_CONFIG_S *config,
		ISP_PUB_ATTR_S *pub_attr)
{
	int ret = 0;
	SENSOR_CFG_S sensor_cfg = {0};

	UNUSED(config);

	ret = CVI_SNS_ParseIni(&sensor_cfg);
	if (ret == CVI_FAILURE)
		ISP_TEST_PRT("[WARN] parse ini failed\n");

	ret = CVI_SNS_GetConfigInfo(&sensor_cfg);
	if (ret != CVI_SUCCESS) {
		ISP_TEST_PRT("Error: CVI_SNS_GetConfigInfo failed!\n");
		return ret;
	}

	pub_attr->stSnsSize.u32Width = sensor_cfg.sns_cfg.u32ImageWigth[pipe];
	pub_attr->stSnsSize.u32Height = sensor_cfg.sns_cfg.u32ImageHeight[pipe];
	pub_attr->stWndRect.u32Width = sensor_cfg.sns_cfg.u32ImageWigth[pipe];
	pub_attr->stWndRect.u32Height = sensor_cfg.sns_cfg.u32ImageHeight[pipe];

	pub_attr->enWDRMode = sensor_cfg.sns_cfg.enWDRMode[pipe];
	pub_attr->f32FrameRate = sensor_cfg.sns_cfg.f32FrameRate[pipe];
	pub_attr->enBayer = (ISP_BAYER_FORMAT_E)sensor_cfg.sns_cfg.enBayerFormat[pipe];
	pub_attr->u8LaneNum = sensor_cfg.sns_cfg.u8LaneNumber[pipe];
	pub_attr->u8EnableMaster = sensor_cfg.sns_cfg.u8EnMasterMode[pipe];

	return ret;
}

static int isp_awblib_callback(int pipe)
{
	ALG_LIB_S stAwbLib;
	int ret = 0;

	stAwbLib.s32Id = pipe;
	strncpy(stAwbLib.acLibName, CVI_AWB_LIB_NAME, sizeof(stAwbLib.acLibName));
	ret = CVI_AWB_Register(pipe, &stAwbLib);
	if (ret != 0) {
		ISP_TEST_PRT("Error: Pipe(%d) AWB Algo register failed!, error: %d\n", pipe, ret);
		return ret;
	}
	return 0;
}

static int isp_aelib_callback(int pipe)
{
	int ret = 0;
	ALG_LIB_S stAeLib;

	stAeLib.s32Id = pipe;
	strncpy(stAeLib.acLibName, CVI_AE_LIB_NAME, sizeof(stAeLib.acLibName));
	ret = CVI_AE_Register(pipe, &stAeLib);
	if (ret != 0) {
		ISP_TEST_PRT("Error: Pipe(%d) AE Algo register failed!, error: %d\n", pipe, ret);
		return ret;
	}
	return 0;
}

static int isp_aflib_callback(int pipe)
{
	int ret = 0;
	ALG_LIB_S stAfLib;

	stAfLib.s32Id = pipe;
	strncpy(stAfLib.acLibName, CVI_AF_LIB_NAME, sizeof(stAfLib.acLibName));
	ret = CVI_AF_Register(pipe, &stAfLib);

	if (ret != 0) {
		ISP_TEST_PRT("Error: Pipe(%d) AF Algo register failed!, error: %d\n", pipe, ret);
		return ret;
	}
	return 0;
}

static int isp_awblib_uncallback(int pipe)
{
	int ret = 0;
	ALG_LIB_S stAwbLib;

	stAwbLib.s32Id = pipe;
	strncpy(stAwbLib.acLibName, CVI_AWB_LIB_NAME, sizeof(stAwbLib.acLibName));
	ret = CVI_AWB_UnRegister(pipe, &stAwbLib);
	if (ret) {
		ISP_TEST_PRT("Error: AWB Algo unRegister failed!, error: %d\n", ret);
		return ret;
	}
	return 0;
}

static int isp_aelib_uncallback(int pipe)
{
	int ret = 0;
	ALG_LIB_S stAeLib;

	stAeLib.s32Id = pipe;
	strncpy(stAeLib.acLibName, CVI_AE_LIB_NAME, sizeof(stAeLib.acLibName));
	ret = CVI_AE_UnRegister(pipe, &stAeLib);
	if (ret) {
		ISP_TEST_PRT("Error: AE Algo unRegister failed!, error: %d\n", ret);
		return ret;
	}
	return 0;
}

static int isp_aflib_uncallback(int pipe)
{
	int ret = 0;
	ALG_LIB_S stAfLib;

	stAfLib.s32Id = pipe;
	strncpy(stAfLib.acLibName, CVI_AF_LIB_NAME, sizeof(stAfLib.acLibName));
	ret = CVI_AF_UnRegister(pipe, &stAfLib);
	if (ret) {
		ISP_TEST_PRT("Error: AF Algo unRegister failed!, error: %d\n", ret);
		return ret;
	}
	return 0;
}

static int isp_start(int pipe, ISP_TEST_PATGEN_CONFIG_S *patgen_config)
{
	ISP_TEST_PRT("isp start\n");
	int ret = 0;
	ISP_PUB_ATTR_S stPubAttr = {0};
	ISP_BIND_ATTR_S stBindAttr = {0};

	isp_awblib_callback(pipe);
	isp_aelib_callback(pipe);
	isp_aflib_callback(pipe);

	snprintf(stBindAttr.stAeLib.acLibName, sizeof(CVI_AE_LIB_NAME), "%s", CVI_AE_LIB_NAME);
	stBindAttr.stAeLib.s32Id = pipe;
	stBindAttr.sensorId = pipe;
	snprintf(stBindAttr.stAwbLib.acLibName, sizeof(CVI_AWB_LIB_NAME), "%s", CVI_AWB_LIB_NAME);
	stBindAttr.stAwbLib.s32Id = pipe;
	snprintf(stBindAttr.stAfLib.acLibName, sizeof(CVI_AF_LIB_NAME), "%s", CVI_AF_LIB_NAME);
	stBindAttr.stAfLib.s32Id = pipe;

	ret = CVI_ISP_SetBindAttr(pipe, &stBindAttr);
	if (ret != 0) {
		ISP_TEST_PRT("Error: Bind Algo failed with %#x!\n", ret);
	}

	ret = CVI_ISP_MemInit(pipe);
	if (ret != CVI_SUCCESS) {
		ISP_TEST_PRT("Error: Init Ext memory failed with %#x!\n", ret);
		return ret;
	}

	if (patgen_config->is_sensor_mode) {
		ISP_TEST_PRT("isp mw start, is sensor mode\n");
		ret = isp_get_isp_attr_bysensor(pipe, patgen_config, &stPubAttr);
		if (ret != CVI_SUCCESS)
			return ret;
	} else {
		ISP_TEST_PRT("isp mw start, is patgen mode\n");
		isp_get_isp_attr_bypatgen(pipe, patgen_config, &stPubAttr);
	}

	ISP_TEST_PRT("isp mw pub attr:\n");
	ISP_TEST_PRT("width: %u\n", stPubAttr.stSnsSize.u32Width);
	ISP_TEST_PRT("height: %u\n", stPubAttr.stSnsSize.u32Height);
	ISP_TEST_PRT("enwdrmode: %d\n", stPubAttr.enWDRMode);
	ISP_TEST_PRT("framerate: %f\n", stPubAttr.f32FrameRate);
	ISP_TEST_PRT("bayerid: %d\n", stPubAttr.enBayer);

	ret = CVI_ISP_SetPubAttr(pipe, &stPubAttr);
	if (ret != CVI_SUCCESS) {
		ISP_TEST_PRT("Error: SetPubAttr failed with %#x!\n", ret);
		return ret;
	}

	ret = CVI_ISP_Init(pipe);
	if (ret != CVI_SUCCESS) {
		ISP_TEST_PRT("Error: ISP Init failed with %#x!\n", ret);
		return ret;
	}

	return ret;
}

static int _getFileSize(FILE *fp, CVI_U32 *size)
{
	CVI_S32 ret = CVI_SUCCESS;

	fseek(fp, 0L, SEEK_END);
	*size = ftell(fp);
	rewind(fp);

	return ret;
}

static int isp_readpramfrombin(void)
{
#define SDR_BIN_PATH "/mnt/sd/cvi_sdr.bin"
#define WDR_BIN_PATH "/mnt/sd/cvi_wdr.bin"
#define BIN_PATH_LEN 64
	CVI_S32 ret = CVI_SUCCESS;
	FILE *fp = NULL;
	CVI_U8 *buf = NULL;
	CVI_CHAR binName[BIN_PATH_LEN] = {0};
	CVI_U32 u32TempLen = 0, u32FileSize = 0;
	ISP_PUB_ATTR_S stPubAttr = {0};

	ret = CVI_ISP_GetPubAttr(0, &stPubAttr);
	if (ret != CVI_SUCCESS) {
		ISP_TEST_PRT("CVI_ISP_GetPubAttr failed with %#x!\n", ret);
		return ret;
	}

	if (stPubAttr.enWDRMode)
		snprintf(binName, BIN_PATH_LEN, "%s", WDR_BIN_PATH);
	else
		snprintf(binName, BIN_PATH_LEN, "%s", SDR_BIN_PATH);

	fp = fopen((const CVI_CHAR *)binName, "rb");
	if (fp == NULL) {
		ISP_TEST_PRT("Can't find bin(%s), skip pqbin load\n", binName);
		return CVI_SUCCESS;	/* not fatal — patgen/sensor may run without pqbin */
	}
	ISP_TEST_PRT("Bin exist (%s)\n", binName);
	_getFileSize(fp, &u32FileSize);

	buf = (CVI_U8 *)malloc(u32FileSize);
	if (buf == NULL) {
		ret = CVI_FAILURE;
		ISP_TEST_PRT("Allocate memory fail\n");
		goto ERROR_HANDLER;
	}
	u32TempLen = fread(buf, u32FileSize, 1, fp);
	if (u32TempLen <= 0) {
		ISP_TEST_PRT("read data to buff fail!\n");
		ret = CVI_FAILURE;
		goto ERROR_HANDLER;
	}

	ret = CVI_BIN_ImportBinData(buf, (CVI_U32)u32FileSize);
	if (ret != CVI_SUCCESS)
		ISP_TEST_PRT("CVI_BIN_ImportBinData error! value:(0x%x)\n", ret);

ERROR_HANDLER:
	if (fp != NULL)
		fclose(fp);
	if (buf != NULL)
		free(buf);

	return ret;
}
