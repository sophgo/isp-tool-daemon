/*
 * isp_sensor — device-side host for the isp daemon2 rpcjson test (sensor mode).
 *
 * Extract of vi_ut case 3 (CASE_SENSOR_FE_DRAM_POST_DRAM,
 * self_test/vi_ut/vi_ut_main.c:216): real-sensor VI + ISP pipeline
 * (VI_OFFLINE_VPSS_OFFLINE, MIPI + sensor driver, no VPSS), daemon2 on
 * 127.0.0.1:5566, one-frame self-check, then park until the exit-trigger
 * file appears (SIGINT/SIGTERM also honored).
 *
 * Sensor config (resolution, WDR, bayer, MIPI lane, etc.) comes from
 * /mnt/data/sensor_cfg.ini — the same file vi_ut and isp_pattern read.
 *
 * Mirror of isp_pattern.c's structure: sys/vb → mipi → dev → pipe → isp
 * → chn → self-check → park → teardown.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <inttypes.h>

#include "cvi_type.h"
#include "cvi_defines.h"
#include "cvi_comm_vb.h"
#include "cvi_vb.h"
#include "cvi_sys.h"
#include "cvi_vi.h"
#include "cvi_buffer.h"
#include "cvi_sensor.h"
#include "cvi_sns_ctrl.h"
#include "cvi_mipi.h"
#include "sensor_cfg.h"

#include "isp_pattern_isp.h"

/* from self_test/common/ut_comm.h (standalone build does not include it) */
#ifndef BIT
#define BIT(nr)      (UINT64_C(1) << (nr))
#endif

#define IS_WDR_SENSOR(sns_type) (((sns_type) & BIT(7)) != 0)

/* isp_test_client exit creates this file; the poll loop consumes it.
 * Same path as isp_pattern so one client exit command serves whichever
 * host is currently running (they never run concurrently — both bind
 * JSONRPC_PORT 5566).
 */
#define EXIT_TRIGGER_FILE	"/mnt/data/isp_test_ut_exit"

/* ---- sensor geometry (filled from /mnt/data/sensor_cfg.ini) ---- */
static CVI_U32 g_u32Width;
static CVI_U32 g_u32Height;
static WDR_MODE_E g_enWDRMode = WDR_MODE_NONE;
static BAYER_FORMAT_E g_enBayerFormat = BAYER_FORMAT_RG;
static SENSOR_CFG_S g_sensor_cfg;
/* VI compress mode, set from the parsed config; applied to pipe + chn. */
static COMPRESS_MODE_E g_enCompressMode = COMPRESS_MODE_TILE;

/* default is MIPI-CSI Bayer format sensor (vi_ut_comm.c:49) */
static VI_DEV_ATTR_S DEV_ATTR_SENSOR_BASE = {
	VI_MODE_MIPI,
	VI_WORK_MODE_1Multiplex,
	VI_SCAN_PROGRESSIVE,
	{-1, -1, -1, -1},
	VI_DATA_SEQ_YUYV,

	{
	/*port_vsync   port_vsync_neg     port_hsync        port_hsync_neg        */
	VI_VSYNC_PULSE, VI_VSYNC_NEG_LOW, VI_HSYNC_VALID_SINGNAL, VI_HSYNC_NEG_HIGH,
	VI_VSYNC_VALID_SIGNAL, VI_VSYNC_VALID_NEG_HIGH,

	/*hsync_hfb    hsync_act    hsync_hhb*/
	{0,            1920,        0,
	/*vsync0_vhb vsync0_act vsync0_hhb*/
	 0,            1080,        0,
	/*vsync1_vhb vsync1_act vsync1_hhb*/
	 0,            0,            0}
	},
	VI_DATA_TYPE_RGB,
	{1920, 1080},
	{
	WDR_MODE_NONE,
	1080
	},
	.enBayerFormat = BAYER_FORMAT_BG,
};

/* default is output YUV420 image (vi_ut_comm.c:78) */
static VI_CHN_ATTR_S CHN_ATTR_420_SDR8 = {
	{1920, 1080},
	PIXEL_FORMAT_YUV_PLANAR_420,
	DYNAMIC_RANGE_SDR8,
	VIDEO_FORMAT_LINEAR,
	COMPRESS_MODE_NONE,
	CVI_FALSE, CVI_FALSE,
	0,
	{ -1, -1},
	-1,
	CVI_FALSE,
};

/*
 * _isp_sensor_getconfig: fill g_u32Width/g_u32Height/g_enWDRMode/g_enBayerFormat
 * from the SNS_CFG_S that CVI_SNS_GetConfigInfo populated (same path vi_ut uses
 * in VI_SnsIni2Vicfg: resolution / WDR / bayer come from sns_cfg, not from the
 * raw enSnsType value in the ini, which on some builds is an opaque handle
 * rather than a known SAMPLE_SNS_TYPE_E enum).
 *
 * Falls back to the enSnsType switch (a la vi_patgen_getconfig) only if
 * GetConfigInfo left the resolution zero — belt-and-braces for older drivers.
 */
static CVI_S32 _isp_sensor_getconfig(SENSOR_CFG_S *sensor_cfg)
{
	SNS_INI_CFG_S *sns_ini_cfg = &sensor_cfg->sns_ini_cfg;
	SNS_CFG_S *sns_cfg = &sensor_cfg->sns_cfg;

	/* Primary: take what GetConfigInfo filled in (vi_ut's path). */
	g_u32Width  = sns_cfg->u32ImageWigth[0];
	g_u32Height = sns_cfg->u32ImageHeight[0];
	g_enWDRMode = sns_cfg->enWDRMode[0];
	g_enBayerFormat = sns_cfg->enBayerFormat[0];

	if (g_u32Width == 0 || g_u32Height == 0) {
		/* Fallback: resolve from enSnsType for known sensors. */
		switch (sns_ini_cfg->enSnsType[0]) {
		case OV_OV7251_MIPI_480P_120FPS_10BIT:
			g_u32Width = 640;  g_u32Height = 480;   break;
		case CVSENS_CV2003_MIPI_2M_1080P_30FPS_10BIT:
		case SONY_IMX327_MIPI_2M_30FPS_12BIT:
		case SONY_IMX327_MIPI_2M_30FPS_12BIT_WDR2TO1:
			g_u32Width = 1920; g_u32Height = 1080;  break;
		case BOARD_FULL_SIZE_MIPI_30FPS_12BIT:
			g_u32Width = 2880; g_u32Height = 2160;
			g_enWDRMode = WDR_MODE_2To1_LINE;        break;
		case GCORE_GC4653_MIPI_4M_30FPS_10BIT:
		case OV_OS04A10_MIPI_4M_1440P_30FPS_12BIT:
		case OV_OS04A10_MIPI_4M_1440P_30FPS_10BIT_WDR2TO1:
			g_u32Width = 2560; g_u32Height = 1440;  break;
		case GCORE_GC8613_MIPI_8M_30FPS_10BIT:
			g_u32Width = 3840; g_u32Height = 2160;  break;
		case SMS_SC500AI_MIPI_5M_30FPS_10BIT:
		case SMS_SC500AI_MIPI_5M_30FPS_10BIT_WDR2TO1:
			g_u32Width = 2880; g_u32Height = 1620;  break;
		case OV_OS04C10_MIPI_4M_30FPS_12BIT:
		case OV_OS04C10_MIPI_4M_30FPS_10BIT_WDR2TO1:
			g_u32Width = 2688; g_u32Height = 1520;  break;
		case PIXELPLUS_PR2100_2M_25FPS_8BIT:
		case PIXELPLUS_PR2100_2M_2CH_25FPS_8BIT:
		case PIXELPLUS_PR2100_2M_4CH_25FPS_8BIT:
			g_u32Width = 1920; g_u32Height = 1080;  break;
		case SMS_SC2331_1L_MIPI_2M_30FPS_10BIT:
			g_u32Width = 1920; g_u32Height = 1080;  break;
		default:
			ISP_TEST_PRT("get sns type 0x%x config failed\n", sns_ini_cfg->enSnsType[0]);
			return CVI_FAILURE;
		}
		if (IS_WDR_SENSOR(sns_ini_cfg->enSnsType[0]))
			g_enWDRMode = WDR_MODE_2To1_LINE;
	}

	ISP_TEST_PRT("sensor 0: 0x%x, %ux%u, wdr_mode(%d), bayer(%d)\n",
		sns_ini_cfg->enSnsType[0], g_u32Width, g_u32Height,
		g_enWDRMode, g_enBayerFormat);

	return CVI_SUCCESS;
}

/* ---- SYS + VB init (vi_ut_comm.c:vi_ut_sys_init:281, sensor/1-dev) ---- */
static CVI_S32 _isp_sensor_sys_init(void)
{
	CVI_S32 s32Ret;
	CVI_U32 blkcnt;
	VB_CONFIG_S stVbConf;
	CVI_U32 u32BlkSize, u32BlkRotSize;

	s32Ret = CVI_SYS_Init();
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("CVI_SYS_Init failed!\n");
		return s32Ret;
	}

	memset(&g_sensor_cfg, 0, sizeof(SENSOR_CFG_S));
	memset(&stVbConf, 0, sizeof(VB_CONFIG_S));

	/* Get config from /mnt/data/sensor_cfg.ini */
	s32Ret = CVI_SNS_ParseIni(&g_sensor_cfg);
	if (s32Ret == CVI_FAILURE)
		ISP_TEST_PRT("[WARN] parse ini failed\n");

	/* Populate driver config for a real sensor */
	s32Ret = CVI_SNS_GetConfigInfo(&g_sensor_cfg);
	if (s32Ret == CVI_FAILURE) {
		ISP_TEST_PRT("[ERROR] CVI_SNS_GetConfigInfo failed\n");
		CVI_SYS_Exit();
		return CVI_FAILURE;
	}

	s32Ret = CVI_SNS_SetSnsDrvCfg(&g_sensor_cfg);
	if (s32Ret == CVI_FAILURE) {
		ISP_TEST_PRT("[ERROR] CVI_SNS_SetSnsDrvCfg failed\n");
		CVI_SYS_Exit();
		return CVI_FAILURE;
	}

	s32Ret = _isp_sensor_getconfig(&g_sensor_cfg);
	if (s32Ret != CVI_SUCCESS || g_u32Width == 0 || g_u32Height == 0) {
		ISP_TEST_PRT("[ERROR] sensor getconfig failed (bad enSnsType in sensor_cfg.ini?)\n");
		CVI_SYS_Exit();
		return CVI_FAILURE;
	}

	/* compress mode is set by isp_ut_wrapper via isp_sensor_impl_set_compress_mode */

	/*
	 * one common pool: NV12(WxH) blocks; blk_num=2 (vi_ut)
	 * + 1 extra for raw dump (SDR; WDR adds one more)
	 */
	u32BlkSize = COMMON_GetPicBufferSize(g_u32Width, g_u32Height,
			VI_PIXEL_FORMAT, DATA_BITWIDTH_8, COMPRESS_MODE_NONE, DEFAULT_ALIGN);
	u32BlkRotSize = COMMON_GetPicBufferSize(g_u32Height, g_u32Width,
			VI_PIXEL_FORMAT, DATA_BITWIDTH_8, COMPRESS_MODE_NONE, DEFAULT_ALIGN);
	u32BlkSize = u32BlkSize > u32BlkRotSize ? u32BlkSize : u32BlkRotSize;

	blkcnt = (g_enWDRMode != WDR_MODE_NONE) ? 2 : 1;	//for dump raw
	stVbConf.astCommPool[0].u32BlkSize = u32BlkSize;
	stVbConf.astCommPool[0].u32BlkCnt = 2 + blkcnt;
	stVbConf.astCommPool[0].enRemapMode = VB_REMAP_MODE_CACHED;
	stVbConf.u32MaxPoolCnt = 1;

	ISP_TEST_PRT("Create VB Pool(0) size(%d), cnt(%d)\n",
			stVbConf.astCommPool[0].u32BlkSize, stVbConf.astCommPool[0].u32BlkCnt);

	s32Ret = CVI_VB_SetConfig(&stVbConf);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("CVI_VB_SetConfig failed!\n");
		CVI_SYS_Exit();
		return s32Ret;
	}

	s32Ret = CVI_VB_Init();
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("CVI_VB_Init failed!\n");
		CVI_SYS_Exit();
		return s32Ret;
	}

	return s32Ret;
}

static void _isp_sensor_sys_exit(void)
{
	CVI_VB_Exit();
	CVI_SYS_Exit();
}

/* ---- MIPI bring-up (vi_ut_comm.c:vi_ut_start_mipi:940) ---- */
static CVI_S32 _isp_sensor_start_mipi(void)
{
	CVI_S32 s32Ret;
	VI_DEV ViDev = 0;
	SNS_COMBO_DEV_ATTR_S stDevAttr;
	SNS_INI_CFG_S *ini = &g_sensor_cfg.sns_ini_cfg;
	CVI_S32 mipiDev = ini->MipiDev[0];

	s32Ret = CVI_MIPI_SetSensorReset(mipiDev, ini->s32RstPort[0],
					ini->s32RstPin[0], ini->s32RstPol[0], 1);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("[ERROR] sensor_%d reset failed!\n", ViDev);
		return s32Ret;
	}

	s32Ret = CVI_MIPI_SetMipiReset(mipiDev, 1);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("[ERROR] mipi dev_%d reset failed!\n", ViDev);
		return s32Ret;
	}

	if (CVI_SNS_GetSnsRxAttr(ViDev, &stDevAttr) != CVI_SUCCESS) {
		ISP_TEST_PRT("[ERROR] get mipi dev_%d attr failed!\n", ViDev);
		return CVI_FAILURE;
	}

	if (stDevAttr.input_mode == INPUT_MODE_MIPI) {
		stDevAttr.mipi_attr.dphy.enable = ini->bHsettlen[0];
		stDevAttr.mipi_attr.dphy.hs_settle = ini->u8Hsettle[0];
	}

	s32Ret = CVI_MIPI_SetMipiAttr(ViDev, (CVI_VOID *)&stDevAttr);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("[ERROR] set mipi dev_%d attr failed!\n", ViDev);
		return s32Ret;
	}

	s32Ret = CVI_MIPI_SetSensorClock(mipiDev, 1);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("[ERROR] sensor %d clock enable failed!\n", ViDev);
		return s32Ret;
	}

	/* Wait for the clock to stabilize before setting XCLR (eg. 500ns IMX327) */
	usleep(200 * 1000);

	s32Ret = CVI_MIPI_SetSensorReset(mipiDev, ini->s32RstPort[0],
					ini->s32RstPin[0], ini->s32RstPol[0], 0);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("[ERROR] sensor_%d unreset failed!\n", ViDev);
		return s32Ret;
	}

	/* Communication start after reset (eg. 20us IMX327) */
	usleep(200 * 1000);

	if (CVI_SNS_SetSnsProbe(ViDev) != CVI_SUCCESS) {
		ISP_TEST_PRT("[ERROR] sensor_%d probe failed!\n", ViDev);
		return CVI_FAILURE;
	}

	return CVI_SUCCESS;
}

/* ---- MIPI teardown (vi_ut_comm.c:vi_ut_stop_mipi:906) ---- */
static CVI_S32 _isp_sensor_stop_mipi(void)
{
	CVI_S32 s32Ret;
	VI_DEV ViDev = 0;
	SNS_INI_CFG_S *ini = &g_sensor_cfg.sns_ini_cfg;
	CVI_S32 mipiDev = ini->MipiDev[0];

	s32Ret = CVI_MIPI_SetSensorReset(mipiDev,
					ini->s32RstPort[0],
					ini->s32RstPin[0],
					ini->s32RstPol[0], 1);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("[ERROR] sensor_%d reset failed!\n", ViDev);
		return s32Ret;
	}

	s32Ret = CVI_MIPI_SetSensorClock(mipiDev, 0);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("[ERROR] sensor %d clock enable failed!\n", ViDev);
		return s32Ret;
	}

	s32Ret = CVI_MIPI_SetMipiReset(mipiDev, 1);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("[ERROR] mipi dev_%d reset failed!\n", ViDev);
		return s32Ret;
	}

	return CVI_SUCCESS;
}

/* ---- VI: dev(sensor) → pipe → ISP → chn ---- */
static CVI_S32 _isp_sensor_start_dev(void)
{
	CVI_S32 s32Ret;
	VI_DEV_ATTR_S stViDevAttr;
	VI_DEV_BIND_PIPE_S stViDevBindAttr;
	SNS_CFG_S *sns_cfg = &g_sensor_cfg.sns_cfg;

	memcpy(&stViDevAttr, &DEV_ATTR_SENSOR_BASE, sizeof(VI_DEV_ATTR_S));

	stViDevAttr.stSize.u32Width = g_u32Width;
	stViDevAttr.stSize.u32Height = g_u32Height;
	stViDevAttr.enIntfMode = (VI_INTF_MODE_E)sns_cfg->enInterFaceMode[0];
	stViDevAttr.enInputDataType = (VI_DATA_TYPE_E)sns_cfg->enFormatMode[0];
	stViDevAttr.enDataSeq = (VI_YUV_DATA_SEQ_E)sns_cfg->enYuvFormat[0];
	stViDevAttr.stWDRAttr.enWDRMode = sns_cfg->enWDRMode[0];
	stViDevAttr.enWorkMode = (VI_WORK_MODE_E)sns_cfg->enChnMode[0];
	stViDevAttr.enYuvSceneMode = VI_ISP_YUV_SCENE_ISP;
	stViDevAttr.enBayerFormat = sns_cfg->enBayerFormat[0];

	memset(&stViDevBindAttr, 0, sizeof(stViDevBindAttr));
	stViDevBindAttr.MipiDev = g_sensor_cfg.sns_ini_cfg.MipiDev[0];
	stViDevBindAttr.PipeId[0] = 0;
	stViDevBindAttr.u32Num = 1;

	s32Ret = CVI_VI_SetDevBindAttr(0, &stViDevBindAttr);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("CVI_VI_SetDevBindAttr failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	/* NO CVI_VI_EnablePatgen — real sensor drives the frontend */

	s32Ret = CVI_VI_SetDevAttr(0, &stViDevAttr);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("CVI_VI_SetDevAttr failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_EnableDev(0);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("CVI_VI_EnableDev failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	return CVI_SUCCESS;
}

static CVI_S32 _isp_sensor_start_pipe(void)
{
	CVI_S32 s32Ret;
	VI_PIPE_ATTR_S stPipeAttr;

	memset(&stPipeAttr, 0, sizeof(stPipeAttr));
	stPipeAttr.u32MaxW = g_u32Width;
	stPipeAttr.u32MaxH = g_u32Height;
	stPipeAttr.enPixFmt = PIXEL_FORMAT_RGB_BAYER_12BPP;
	stPipeAttr.enBitWidth = DATA_BITWIDTH_12;
	stPipeAttr.stFrameRate.s32SrcFrameRate = -1;
	stPipeAttr.stFrameRate.s32DstFrameRate = -1;
	stPipeAttr.bNrEn = CVI_TRUE;
	stPipeAttr.bYuvBypassPath = CVI_FALSE;
	stPipeAttr.enCompressMode = g_enCompressMode;	/* case 3: isDpcmOn=true (configurable) */

	s32Ret = CVI_VI_CreatePipe(0, &stPipeAttr);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("CVI_VI_CreatePipe failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_StartPipe(0);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("CVI_VI_StartPipe failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	return CVI_SUCCESS;
}

static CVI_S32 _isp_sensor_start_isp(void)
{
	ISP_TEST_PATGEN_CONFIG_S stSnsConfig = {
		.width = 0,
		.height = 0,
		.bayer_id = 0,
		.frame_rate = 30,
		.wdr_mode = (int)g_enWDRMode,
		.is_sensor_mode = 1,
	};

	stSnsConfig.width = (int)g_u32Width;
	stSnsConfig.height = (int)g_u32Height;
	stSnsConfig.bayer_id = (int)g_enBayerFormat;

	return ISP_TEST_ISP_Init(0, &stSnsConfig);
}

static CVI_S32 _isp_sensor_start_snsr(void)
{
	CVI_S32 s32Ret;

	s32Ret = CVI_SNS_SetVIFlipMirrorCB(0, 0);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("CVI_SNS_SetVIFlipMirrorCB failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_SNS_SetSnsInit(0);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("CVI_SNS_SetSnsInit failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	return CVI_SUCCESS;
}

static CVI_S32 _isp_sensor_start_chn(void)
{
	CVI_S32 s32Ret;
	VI_CHN_ATTR_S stChnAttr;

	memcpy(&stChnAttr, &CHN_ATTR_420_SDR8, sizeof(VI_CHN_ATTR_S));

	stChnAttr.stSize.u32Width = g_u32Width;
	stChnAttr.stSize.u32Height = g_u32Height;
	stChnAttr.enDynamicRange = (g_enWDRMode != WDR_MODE_NONE)
				   ? DYNAMIC_RANGE_HDR10 : DYNAMIC_RANGE_SDR8;
	stChnAttr.enVideoFormat = VIDEO_FORMAT_LINEAR;
	stChnAttr.enCompressMode = g_enCompressMode;	/* case 3: isDpcmOn=true (configurable) */
	stChnAttr.enPixelFormat = VI_PIXEL_FORMAT;	/* NV12 */
	stChnAttr.u32Depth = 0;
	stChnAttr.u32BindVbPool = -1;
	stChnAttr.bMirror = CVI_FALSE;
	stChnAttr.bFlip = CVI_FALSE;
	stChnAttr.bSingleVb = CVI_TRUE;

	s32Ret = CVI_VI_SetChnAttr(0, 0, &stChnAttr);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("CVI_VI_SetChnAttr failed with %#x!\n", s32Ret);
		return CVI_FAILURE;
	}

	s32Ret = CVI_VI_EnableChn(0, 0);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("CVI_VI_EnableChn failed with %#x!\n", s32Ret);
		return CVI_FAILURE;
	}

	return CVI_SUCCESS;
}

static CVI_S32 _isp_sensor_vi_init(void)
{
	CVI_S32 s32Ret;

	s32Ret = _isp_sensor_start_mipi();
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("start mipi failed. s32Ret: 0x%x !\n", s32Ret);
		return s32Ret;
	}

	s32Ret = _isp_sensor_start_dev();
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("start dev failed. s32Ret: 0x%x !\n", s32Ret);
		return s32Ret;
	}

	s32Ret = _isp_sensor_start_pipe();
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("start pipe failed. s32Ret: 0x%x !\n", s32Ret);
		return s32Ret;
	}

	s32Ret = _isp_sensor_start_isp();
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("start isp failed. s32Ret: 0x%x !\n", s32Ret);
		return s32Ret;
	}

	s32Ret = _isp_sensor_start_snsr();
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("sns init failed. s32Ret: 0x%x !\n", s32Ret);
		return s32Ret;
	}

	s32Ret = _isp_sensor_start_chn();
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("start chn failed. s32Ret: 0x%x !\n", s32Ret);
		return s32Ret;
	}

	return CVI_SUCCESS;
}

/* ---- teardown (vi_ut_vi_deinit:1421 order) ---- */
static CVI_S32 _isp_sensor_stop_chn(void)
{
	CVI_S32 s32Ret = CVI_VI_DisableChn(0, 0);

	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("CVI_VI_DisableChn failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	return CVI_SUCCESS;
}

static CVI_S32 _isp_sensor_stop_pipe(void)
{
	CVI_S32 s32Ret;

	s32Ret = CVI_VI_StopPipe(0);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("CVI_VI_StopPipe failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_DestroyPipe(0);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("CVI_VI_DestroyPipe failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	return CVI_SUCCESS;
}

static CVI_S32 _isp_sensor_stop_dev(void)
{
	CVI_S32 s32Ret = CVI_VI_DisableDev(0);

	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("CVI_VI_DisableDev failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	return CVI_SUCCESS;
}

static void _isp_sensor_vi_deinit(void)
{
	ISP_TEST_PRT("stop chn\n");
	_isp_sensor_stop_chn();
	ISP_TEST_PRT("exit the isp\n");
	ISP_TEST_ISP_Exit(0);
	ISP_TEST_PRT("stop pipe\n");
	_isp_sensor_stop_pipe();
	ISP_TEST_PRT("stop dev\n");
	_isp_sensor_stop_dev();
	ISP_TEST_PRT("stop mipi\n");
	_isp_sensor_stop_mipi();
}

static void _isp_sensor_exit(void)
{
	_isp_sensor_vi_deinit();
	_isp_sensor_sys_exit();
	ISP_TEST_PRT("isp_sensor exited cleanly\n");
}

/* ---- self-check: one frame proves the pipeline produces output ---- */
/* vi_ut_dump.c:vi_ut_get_chn_frame:277, isSave2File=false variant. */
static CVI_S32 _isp_sensor_self_check(void)
{
	CVI_S32 s32Ret;
	VIDEO_FRAME_INFO_S stVideoFrame;

	memset(&stVideoFrame, 0, sizeof(stVideoFrame));

	s32Ret = CVI_VI_GetChnFrame(0, 0, &stVideoFrame, 6000);
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("CVI_VI_GetChnFrame failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	ISP_TEST_PRT("Get frame OK %ux%u paddr(0x%#"PRIx64")\n",
			stVideoFrame.stVFrame.u32Width, stVideoFrame.stVFrame.u32Height,
			stVideoFrame.stVFrame.u64PhyAddr[0]);

	if (CVI_VI_ReleaseChnFrame(0, 0, &stVideoFrame) != 0)
		ISP_TEST_PRT("CVI_VI_ReleaseChnFrame NG\n");

	return CVI_SUCCESS;
}

/* ---- set compress mode from parsed config ---- */
void isp_sensor_impl_set_compress_mode(COMPRESS_MODE_E mode)
{
	g_enCompressMode = mode;
}

/* ---- SIGINT/SIGTERM → full teardown (vi_ut_main.c:1389) ---- */
static void _isp_sensor_handle_signal(CVI_S32 nSignal, siginfo_t *si, CVI_VOID *arg)
{
	UNUSED(nSignal);
	UNUSED(si);
	UNUSED(arg);

	_isp_sensor_exit();
	exit(0);
}

int isp_sensor_impl_main(void)
{
	CVI_S32 s32Ret;
	struct sigaction sa;

	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = _isp_sensor_handle_signal;
	sa.sa_flags = SA_SIGINFO | SA_RESETHAND;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);

	/* clear any stale trigger so it cannot kill this run at once */
	unlink(EXIT_TRIGGER_FILE);

	s32Ret = _isp_sensor_sys_init();
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("sys init failed. s32Ret: 0x%x !\n", s32Ret);
		return 1;
	}

	s32Ret = _isp_sensor_vi_init();
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("vi init failed. s32Ret: 0x%x !\n", s32Ret);
		_isp_sensor_exit();
		return 1;
	}

	s32Ret = _isp_sensor_self_check();
	if (s32Ret != CVI_SUCCESS) {
		ISP_TEST_PRT("self check failed. s32Ret: 0x%x !\n", s32Ret);
		_isp_sensor_exit();
		return 1;
	}

	ISP_TEST_PRT("isp daemon2 listening on 127.0.0.1:%d\n", JSONRPC_PORT);
	ISP_TEST_PRT("waiting for exit trigger (" EXIT_TRIGGER_FILE ") ...\n");

	while (access(EXIT_TRIGGER_FILE, F_OK) != 0)
		sleep(1);

	/* consume the trigger so a stale file cannot kill the next run */
	unlink(EXIT_TRIGGER_FILE);
	ISP_TEST_PRT("exit trigger detected\n");

	_isp_sensor_exit();
	return 0;
}
