#include <unistd.h>
#include <dlfcn.h>

#include "sample_comm.h"
#include "daemon_base.h"
#include "daemon_cfg.h"
#include "video_src_cfg.h"
#include "cvi_ae_comm.h"
#include "cvi_awb_comm.h"


//#include "raw_replay_offline.h"

#define CLOG_OUTPUT_LVL CLOG_LVL_DEBUG
#undef CLOG_TAG
#define CLOG_TAG "video_src_cfg_replay"

#define OFFLINE_REPLAY_SO "libraw_replay_offline.so"

#define GET_SO_FUNC(p_func, func_name) \
{\
	if (!p_func) {\
		char *error = NULL;\
		void *so_handle;\
		dlerror();\
		so_handle = dlopen(OFFLINE_REPLAY_SO, RTLD_LAZY);\
		error = dlerror();\
		if (error != NULL) {\
			clog_e("dlopen %s error : %s", OFFLINE_REPLAY_SO, error);\
		}\
		if (so_handle == NULL) {\
			return CVI_FAILURE;\
		}\
		dlerror();\
		p_func = dlsym(so_handle, func_name);\
		error = dlerror();\
		if (error != NULL) {\
			p_func = NULL;\
			dlclose(OFFLINE_REPLAY_SO);\
			return CVI_FAILURE;\
		}\
	}\
}

static CVI_S32 (*raw_replay_offline_init)(char *);
static CVI_S32 (*start_raw_replay_offline)(char *);

static VI_DEV_ATTR_S DEV_ATTR_SENSOR_DEFAULT = {
	VI_MODE_MIPI,
	VI_WORK_MODE_1Multiplex,
	VI_SCAN_PROGRESSIVE,
	{ -1, -1, -1, -1 },
	VI_DATA_SEQ_YUYV,
	{
		VI_VSYNC_PULSE, VI_VSYNC_NEG_LOW, VI_HSYNC_VALID_SINGNAL,
		VI_HSYNC_NEG_HIGH, VI_VSYNC_VALID_SIGNAL, VI_VSYNC_VALID_NEG_HIGH,
		{ 0, 1920, 0, 0, 1080, 0, 0, 0, 0 }
	},
	VI_DATA_TYPE_RGB,
	{ 1920, 1080 },
	{ WDR_MODE_NONE, 1080 },
	.enBayerFormat = BAYER_FORMAT_BG,
};

static VI_CHN_ATTR_S CHN_ATTR_DEFAULT = {
	{ 1920, 1080 },
	PIXEL_FORMAT_YUV_PLANAR_420,
	DYNAMIC_RANGE_SDR8,
	VIDEO_FORMAT_LINEAR,
	COMPRESS_MODE_NONE,
	CVI_FALSE, CVI_FALSE,
	0,
	{ -1, -1 },
	0,
	0
};

static ISP_PUB_ATTR_S ISP_PUB_ATTR_DEFAULT = {
	{ 0, 0, 1920, 1080 },
	{ 1920, 1080 },
	25,
	BAYER_RGGB,
	WDR_MODE_NONE,
	0,
	4,
	0
};

static COMPRESS_MODE_E get_compress_mode(const char *mode)
{
	if (strcmp(mode, "none") == 0) {
		return COMPRESS_MODE_NONE;
	} else if (strcmp(mode, "tile") == 0) {
		return COMPRESS_MODE_TILE;
	} else if (strcmp(mode, "line") == 0) {
		return COMPRESS_MODE_LINE;
	} else if (strcmp(mode, "frame") == 0) {
		return COMPRESS_MODE_FRAME;
	} else {
		return COMPRESS_MODE_NONE;
	}
}

static int replay_sys_init(daemon_pipe_cfg_t *pipe_cfg)
{
	CVI_S32 s32Ret = CVI_SUCCESS;
	SIZE_S stSize;
	VB_CONFIG_S stVbConf;
	CVI_U32 u32BlkSize;
	// TODO: check
	CVI_S32 dft_vb_cnt = 6;
	raw_replay_cfg_t *cfg = &pipe_cfg->raw_replay_cfg;
	int vb_blk_cnt = pipe_cfg->video_pipe_cfg.buf_blk_cnt;
	int vi_vpss_mode = pipe_cfg->vi_vpss_mode;

	memset(&stVbConf, 0, sizeof(VB_CONFIG_S));

	s32Ret = CVI_SYS_Init();
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_SYS_Init failed!\n");
		return s32Ret;
	}

	// vi vpss mode
	VI_VPSS_MODE_S stVIVPSSMode = {0};
	VPSS_MODE_S stVPSSMode = {0};

	s32Ret = CVI_SYS_GetVIVPSSMode(&stVIVPSSMode);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_SYS_GetVIVPSSMode failed with %#x\n", s32Ret);
		return s32Ret;
	}

	stVIVPSSMode.aenMode[0] = vi_vpss_mode;

	s32Ret = CVI_SYS_SetVIVPSSMode(&stVIVPSSMode);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_SYS_SetVIVPSSMode failed with %#x\n", s32Ret);
		return s32Ret;
	}

	if (stVIVPSSMode.aenMode[0] == VI_ONLINE_VPSS_ONLINE ||
			stVIVPSSMode.aenMode[0] == VI_OFFLINE_VPSS_ONLINE) {
		stVPSSMode.enMode = VPSS_MODE_DUAL;
		stVPSSMode.aenInput[0] = VPSS_INPUT_MEM;
		stVPSSMode.aenInput[1] = VPSS_INPUT_ISP;

		s32Ret = CVI_VPSS_SetMode(&stVPSSMode);
		if (s32Ret != CVI_SUCCESS) {
			clog_e("CVI_SYS_SetVPSSModeEx failed with %#x\n", s32Ret);
			return s32Ret;
		}
	}

	// set vb
	stVbConf.u32MaxPoolCnt = 1;

	stSize.u32Width = cfg->width;
	stSize.u32Height = cfg->height;

	PIXEL_FORMAT_E pixFomart = VI_PIXEL_FORMAT;

	if (cfg->pixel_format) {
		pixFomart = (PIXEL_FORMAT_E)cfg->pixel_format;
	}

	u32BlkSize = COMMON_GetPicBufferSize(stSize.u32Width, stSize.u32Height,
						 pixFomart, DATA_BITWIDTH_8,
						 COMPRESS_MODE_NONE, DEFAULT_ALIGN);

	stVbConf.astCommPool[0].u32BlkSize = u32BlkSize;
	stVbConf.astCommPool[0].u32BlkCnt =
		(vb_blk_cnt > dft_vb_cnt) ? vb_blk_cnt : dft_vb_cnt;
	stVbConf.astCommPool[0].enRemapMode = VB_REMAP_MODE_CACHED;

	s32Ret = CVI_VB_SetConfig(&stVbConf);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VB_SetConf failed!\n");
		CVI_SYS_Exit();
		return s32Ret;
	}

	s32Ret = CVI_VB_Init();
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VB_Init failed!\n");
		CVI_SYS_Exit();
		return s32Ret;
	}

	return CVI_SUCCESS;
}

static CVI_S32 replay_vi_start_dev(raw_replay_cfg_t *cfg)
{
	CVI_S32 s32Ret;
	VI_DEV_ATTR_S stViDevAttr;
	VI_DEV_BIND_PIPE_S  stViDevBindAttr;

	memcpy(&stViDevAttr, &DEV_ATTR_SENSOR_DEFAULT, sizeof(VI_DEV_ATTR_S));

	if (!cfg->pixel_format) {
		stViDevAttr.stSize.u32Width = cfg->width;
		stViDevAttr.stSize.u32Height = cfg->height;
		stViDevAttr.enInputDataType = VI_DATA_TYPE_RGB;
		stViDevAttr.enBayerFormat = (BAYER_FORMAT_E)cfg->bayer_format;
		if (cfg->wdr_mode) {
			stViDevAttr.stWDRAttr.enWDRMode = WDR_MODE_2To1_LINE;
			stViDevAttr.stWDRAttr.u32CacheLine = cfg->width;
		}
	} else {
		stViDevAttr.stSize.u32Width = cfg->width;
		stViDevAttr.stSize.u32Height = cfg->height;
		stViDevAttr.stWDRAttr.u32CacheLine = cfg->width;
		stViDevAttr.enDataSeq = VI_DATA_SEQ_YUYV;
		stViDevAttr.enInputDataType = VI_DATA_TYPE_YUV;
		stViDevAttr.enIntfMode = VI_MODE_MIPI_YUV422;
	}
	stViDevAttr.snrFps = cfg->frame_rate;

	// TODO: check
	stViDevBindAttr.PipeId[0]		= 0;
	stViDevBindAttr.u32Num			= 1;
	stViDevBindAttr.MipiDev			= 0;

	s32Ret = CVI_VI_SetDevAttr(0, &stViDevAttr);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VI_SetDevAttr failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_SetDevBindAttr(0, &stViDevBindAttr);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VI_SetDevBindAttr failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_EnableDev(0);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VI_EnableDev failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	return CVI_SUCCESS;
}

static CVI_S32 replay_vi_start_pipe(raw_replay_cfg_t *cfg)
{
	CVI_S32 s32Ret = 0;
	VI_PIPE_ATTR_S stPipeAttr = {0};

	stPipeAttr.bYuvSkip = CVI_FALSE;
	stPipeAttr.u32MaxW = cfg->width;
	stPipeAttr.u32MaxH = cfg->height;
	stPipeAttr.enPixFmt = PIXEL_FORMAT_RGB_BAYER_12BPP;
	stPipeAttr.enBitWidth = DATA_BITWIDTH_12;
	stPipeAttr.stFrameRate.s32SrcFrameRate = -1;
	stPipeAttr.stFrameRate.s32DstFrameRate = -1;
	stPipeAttr.bNrEn = CVI_TRUE;
	stPipeAttr.enCompressMode = get_compress_mode(cfg->compress_mode);
	stPipeAttr.bYuvBypassPath = cfg->pixel_format ? 1 : 0;

	s32Ret = CVI_VI_CreatePipe(0, &stPipeAttr);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VI_CreatePipe failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_StartPipe(0);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VI_StartPipe failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_GetPipeAttr(0, &stPipeAttr);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VI_GetPipeAttr failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	return CVI_SUCCESS;
}

static CVI_S32 replay_vi_start_isp(raw_replay_cfg_t *cfg, int enable_teaisp)
{
	CVI_S32 s32Ret = 0;
	VI_PIPE ViPipe = 0;
	ISP_PUB_ATTR_S stPubAttr;
	ISP_BIND_ATTR_S stBindAttr;

	SAMPLE_COMM_ISP_Aelib_Callback(ViPipe);
	SAMPLE_COMM_ISP_Awblib_Callback(ViPipe);
#if ENABLE_AF_LIB
	SAMPLE_COMM_ISP_Aflib_Callback(ViPipe);
#endif

	snprintf(stBindAttr.stAeLib.acLibName, sizeof(CVI_AE_LIB_NAME), "%s",
		 CVI_AE_LIB_NAME);
	stBindAttr.stAeLib.s32Id = ViPipe;
	stBindAttr.sensorId = 0;
	snprintf(stBindAttr.stAwbLib.acLibName, sizeof(CVI_AWB_LIB_NAME), "%s",
		 CVI_AWB_LIB_NAME);
	stBindAttr.stAwbLib.s32Id = ViPipe;
#if ENABLE_AF_LIB
	snprintf(stBindAttr.stAfLib.acLibName, sizeof(CVI_AF_LIB_NAME), "%s",
		 CVI_AF_LIB_NAME);
	stBindAttr.stAfLib.s32Id = ViPipe;
#endif
	s32Ret = CVI_ISP_SetBindAttr(ViPipe, &stBindAttr);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("Bind Algo failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_ISP_MemInit(ViPipe);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("Init Ext memory failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	memcpy(&stPubAttr, &ISP_PUB_ATTR_DEFAULT, sizeof(ISP_PUB_ATTR_S));
	stPubAttr.stSnsSize.u32Width = cfg->width;
	stPubAttr.stSnsSize.u32Height = cfg->height;
	stPubAttr.stWndRect.u32Width = cfg->width;
	stPubAttr.stWndRect.u32Height = cfg->height;
	stPubAttr.stWndRect.s32X = 0;
	stPubAttr.stWndRect.s32Y = 0;
	stPubAttr.enWDRMode =
		cfg->wdr_mode ? WDR_MODE_2To1_LINE : WDR_MODE_NONE;
	stPubAttr.f32FrameRate = cfg->frame_rate;
	stPubAttr.enBayer = (ISP_BAYER_FORMAT_E)cfg->bayer_format;
	s32Ret = CVI_ISP_SetPubAttr(ViPipe, &stPubAttr);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("SetPubAttr failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_ISP_Init(ViPipe);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("ISP Init failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	if (enable_teaisp) {
		//CVI_TEAISP_SetMode(ViPipe, TEAISP_BEFORE_FE_RAW_MODE);
	}

	return CVI_SUCCESS;
}

static CVI_S32 replay_vi_create_isp(raw_replay_cfg_t *cfg, int enable_teaisp)
{
	CVI_S32 s32Ret = CVI_SUCCESS;
	ISP_PUB_ATTR_S stPubAttr;

	s32Ret = replay_vi_start_isp(cfg, enable_teaisp);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("replay_startIsp failed !\n");
		return s32Ret;
	}

	s32Ret = SAMPLE_COMM_BIN_ReadParaFrombin();
	if (s32Ret != CVI_SUCCESS) {
		clog_e("read para fail: %#x,use default para!\n", s32Ret);
	}

	memcpy(&stPubAttr, &ISP_PUB_ATTR_DEFAULT, sizeof(ISP_PUB_ATTR_S));
	stPubAttr.stSnsSize.u32Width = cfg->width;
	stPubAttr.stSnsSize.u32Height = cfg->height;
	stPubAttr.stWndRect.u32Width = cfg->width;
	stPubAttr.stWndRect.u32Height = cfg->height;
	stPubAttr.stWndRect.s32X = 0;
	stPubAttr.stWndRect.s32Y = 0;
	stPubAttr.enWDRMode =
		cfg->wdr_mode ? WDR_MODE_2To1_LINE : WDR_MODE_NONE;
	stPubAttr.f32FrameRate = cfg->frame_rate;
	stPubAttr.enBayer = (ISP_BAYER_FORMAT_E)cfg->bayer_format;
	s32Ret = CVI_ISP_SetPubAttr(0, &stPubAttr);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("SetPubAttr failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = SAMPLE_COMM_ISP_Run(0);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("ISP_Run failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	return CVI_SUCCESS;
}

static CVI_S32 replay_vi_start_chn(raw_replay_cfg_t *cfg)
{
	CVI_S32 s32Ret = CVI_SUCCESS;
	VI_PIPE ViPipe = 0;
	VI_CHN ViChn = 0;
	VI_CHN_ATTR_S stChnAttr = {0};

	memcpy(&stChnAttr, &CHN_ATTR_DEFAULT, sizeof(VI_CHN_ATTR_S));
	stChnAttr.enPixelFormat = PIXEL_FORMAT_NV21;
	stChnAttr.stSize.u32Width = cfg->width;
	stChnAttr.stSize.u32Height = cfg->height;
	stChnAttr.enDynamicRange =
		cfg->wdr_mode ? DYNAMIC_RANGE_HDR10 : DYNAMIC_RANGE_SDR10;
	stChnAttr.enVideoFormat = VIDEO_FORMAT_LINEAR;
	stChnAttr.enCompressMode = get_compress_mode(cfg->compress_mode);
	stChnAttr.u32Depth = 0;
	stChnAttr.u32BindVbPool = -1;
	/* fill the sensor orientation */
	stChnAttr.bMirror = 0;
	stChnAttr.bFlip = 0;

	s32Ret = CVI_VI_SetChnAttr(ViPipe, ViChn, &stChnAttr);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VI_SetChnAttr failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_EnableChn(ViPipe, ViChn);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VI_EnableChn failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	return CVI_SUCCESS;
}

static CVI_S32 replay_vpss_init(daemon_pipe_cfg_t *pipe_cfg)
{
	VPSS_GRP_ATTR_S stVpssGrpAttr;
	VPSS_CHN VpssChn = 0;
	VPSS_CHN_ATTR_S astVpssChnAttr;
	CVI_S32 s32Ret = CVI_SUCCESS;
	raw_replay_cfg_t *cfg = &pipe_cfg->raw_replay_cfg;
	int vi_vpss_mode = pipe_cfg->vi_vpss_mode;

	memset(&stVpssGrpAttr, 0, sizeof(VPSS_GRP_ATTR_S));
	memset(&astVpssChnAttr, 0, sizeof(VPSS_CHN_ATTR_S));

	stVpssGrpAttr.stFrameRate.s32SrcFrameRate = -1;
	stVpssGrpAttr.stFrameRate.s32DstFrameRate = -1;
	stVpssGrpAttr.enPixelFormat = PIXEL_FORMAT_NV21;
	stVpssGrpAttr.u32MaxW = cfg->width;
	stVpssGrpAttr.u32MaxH = cfg->height;
	stVpssGrpAttr.u8VpssDev = 1;

	s32Ret = CVI_VPSS_CreateGrp(0, &stVpssGrpAttr);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VPSS_CreateGrp failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	astVpssChnAttr.u32Width = cfg->width;
	astVpssChnAttr.u32Height = cfg->height;
	astVpssChnAttr.enVideoFormat = VIDEO_FORMAT_LINEAR;
	astVpssChnAttr.enPixelFormat = PIXEL_FORMAT_NV12;
	astVpssChnAttr.stFrameRate.s32SrcFrameRate = 30;
	astVpssChnAttr.stFrameRate.s32DstFrameRate = 30;
	astVpssChnAttr.u32Depth = 0;
	astVpssChnAttr.bMirror = CVI_FALSE;
	astVpssChnAttr.bFlip = CVI_FALSE;
	astVpssChnAttr.stAspectRatio.enMode = ASPECT_RATIO_NONE;
	astVpssChnAttr.stNormalize.bEnable = CVI_FALSE;

	s32Ret = CVI_VPSS_SetChnAttr(0, VpssChn, &astVpssChnAttr);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VPSS_SetChnAttr failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VPSS_EnableChn(0, VpssChn);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VPSS_EnableChn failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VPSS_StartGrp(0);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VPSS_StartGrp failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_BIN_SetVpssGrpParams(0);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_BIN_SetVpssGrpParams failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	if (vi_vpss_mode == VI_ONLINE_VPSS_OFFLINE ||
		vi_vpss_mode == VI_OFFLINE_VPSS_OFFLINE) {
		MMF_CHN_S stSrcChn;
		MMF_CHN_S stDestChn;

		stSrcChn.enModId = CVI_ID_VI;
		stSrcChn.s32DevId = 0;
		stSrcChn.s32ChnId = 0;

		stDestChn.enModId = CVI_ID_VPSS;
		stDestChn.s32DevId = 0;
		stDestChn.s32ChnId = 0;

		s32Ret = CVI_SYS_Bind(&stSrcChn, &stDestChn);
		if (s32Ret != CVI_SUCCESS) {
			clog_e("CVI_BIN_SetVpssGrpParams failed with %#x!\n", s32Ret);
			return s32Ret;
		}
	}

	return s32Ret;
}


static CVI_S32 replay_vpss_deinit(daemon_pipe_cfg_t *pipe_cfg)
{
	int s32Ret = CVI_SUCCESS;
	int vi_vpss_mode = pipe_cfg->vi_vpss_mode;
	VPSS_GRP VpssGrp = 0;
	VPSS_CHN VpssChn = 0;

	s32Ret = CVI_VPSS_DisableChn(VpssGrp, VpssChn);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VPSS_DisableChn failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VPSS_StopGrp(VpssGrp);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VPSS_StopGrp failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VPSS_DestroyGrp(VpssGrp);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VPSS_DestroyGrp failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	if (vi_vpss_mode == VI_ONLINE_VPSS_OFFLINE ||
		vi_vpss_mode == VI_OFFLINE_VPSS_OFFLINE) {
		MMF_CHN_S stSrcChn;
		MMF_CHN_S stDestChn;

		stSrcChn.enModId = CVI_ID_VI;
		stSrcChn.s32DevId = 0;
		stSrcChn.s32ChnId = 0;

		stDestChn.enModId = CVI_ID_VPSS;
		stDestChn.s32DevId = 0;
		stDestChn.s32ChnId = 0;

		printf("cvi sys bind!\n");
		s32Ret = CVI_SYS_UnBind(&stSrcChn, &stDestChn);
		if (s32Ret != CVI_SUCCESS) {
			clog_e("CVI_SYS_UnBind failed with %#x!\n", s32Ret);
			return s32Ret;
		}
	}

	return s32Ret;
}

static CVI_S32 replay_offline_init(raw_replay_cfg_t *cfg)
{
	CVI_S32 s32Ret;

	printf("replay offline init! offline raw path:%s\n",
			cfg->offline_raw_dir);

	if (access(cfg->offline_raw_dir, F_OK) != 0) {
		clog_e("dump raw path: %s not exists!\n", cfg->offline_raw_dir);
		return -1;
	}

	GET_SO_FUNC(raw_replay_offline_init, "raw_replay_offline_init");
	s32Ret = raw_replay_offline_init(cfg->offline_raw_dir);
	if (s32Ret != 0) {
		clog_e("raw replay offline init fail!\n");
		return s32Ret;
	}

	GET_SO_FUNC(start_raw_replay_offline, "start_raw_replay_offline");
	s32Ret = start_raw_replay_offline(0);

	if (s32Ret != 0) {
		clog_e("raw start fail!\n");
		return s32Ret;
	}

	return CVI_SUCCESS;
}

static CVI_S32 replay_send_usr_pic(raw_replay_cfg_t *cfg)
{
	CVI_S32 s32Ret;
	VI_DEV_TIMING_ATTR_S stTimingAttr;
	VI_PIPE_FRAME_SOURCE_E frameSource = VI_PIPE_FRAME_SOURCE_DEV;

	stTimingAttr.bEnable = cfg->timing_enable;
	stTimingAttr.s32FrmRate = cfg->frame_rate;

	s32Ret = CVI_VI_SetPipeFrameSource(0, VI_PIPE_FRAME_SOURCE_USER_BE);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VI_SetPipeFrameSource failed with %#x\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_GetPipeFrameSource(0, &frameSource);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VI_SetPipeFrameSource failed with %#x\n", s32Ret);
		return s32Ret;
	}

	if (frameSource != VI_PIPE_FRAME_SOURCE_USER_BE) {
		clog_e("CVI_VI_GetPipeFrameSource failed with %d\n", frameSource);
		return CVI_FAILURE;
	}

	s32Ret = CVI_VI_SetDevTimingAttr(0, &stTimingAttr);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VI_SetDevTimingAttr failed with %#x\n", s32Ret);
		return s32Ret;
	}

	VI_PIPE PipeId[] = { 0 };
	const VIDEO_FRAME_INFO_S *pstVideoFrame[1];
	VIDEO_FRAME_INFO_S stVideoFrame;
	VB_BLK blk_le = VB_INVALID_HANDLE;
	VB_BLK blk_se = VB_INVALID_HANDLE;
	CVI_U32 u32BlkSize = 0;
	CVI_U64 u64PhyAddr_le = 0, u64PhyAddr_se = 0;
	CVI_VOID *puVirAddr_le = NULL, *puVirAddr_se = NULL;

	memset(&stVideoFrame, 0, sizeof(VIDEO_FRAME_INFO_S));

	stVideoFrame.stVFrame.enBayerFormat = (BAYER_FORMAT_E)cfg->bayer_format;
	stVideoFrame.stVFrame.enPixelFormat = (PIXEL_FORMAT_E)cfg->pixel_format;
	stVideoFrame.stVFrame.enCompressMode =
		get_compress_mode(cfg->compress_mode);
	stVideoFrame.stVFrame.enDynamicRange =
		cfg->wdr_mode ? DYNAMIC_RANGE_HDR10 : DYNAMIC_RANGE_SDR10;
	stVideoFrame.stVFrame.u32Width = cfg->width;
	stVideoFrame.stVFrame.u32Height = cfg->height;
	stVideoFrame.stVFrame.s16OffsetLeft = 0;
	stVideoFrame.stVFrame.s16OffsetTop = 0;
	stVideoFrame.stVFrame.s16OffsetRight = 0;
	stVideoFrame.stVFrame.s16OffsetBottom = 0;

	// 0: bayer, 1: yuv
	if (!stVideoFrame.stVFrame.enPixelFormat) {
		u32BlkSize = VI_GetRawBufferSize(
			stVideoFrame.stVFrame.u32Width,
			stVideoFrame.stVFrame.u32Height,
			PIXEL_FORMAT_RGB_BAYER_12BPP,
			stVideoFrame.stVFrame.enCompressMode, DEFAULT_ALIGN, 0);
	} else {
		stVideoFrame.stVFrame.enDynamicRange = DYNAMIC_RANGE_SDR10;
		u32BlkSize = COMMON_GetPicBufferSize(
			stVideoFrame.stVFrame.u32Width,
			stVideoFrame.stVFrame.u32Height, PIXEL_FORMAT_YUYV,
			DATA_BITWIDTH_8, COMPRESS_MODE_NONE, DEFAULT_ALIGN);
	}

	blk_le = CVI_VB_GetBlock(VB_INVALID_POOLID, u32BlkSize);
	if (blk_le == VB_INVALID_HANDLE) {
		clog_e("get blk_le failed\n");
		return CVI_FAILURE;
	}
	u64PhyAddr_le = CVI_VB_Handle2PhysAddr(blk_le);
	puVirAddr_le = CVI_SYS_MmapCache(u64PhyAddr_le, u32BlkSize);
	memset(puVirAddr_le, 0, u32BlkSize);
	CVI_SYS_Munmap(puVirAddr_le, u32BlkSize);

	if (cfg->wdr_mode) {
		blk_se = CVI_VB_GetBlock(VB_INVALID_POOLID, u32BlkSize);
		if (blk_se == VB_INVALID_HANDLE) {
			clog_e("get blk_se failed\n");
			return CVI_FAILURE;
		}
		u64PhyAddr_se = CVI_VB_Handle2PhysAddr(blk_se);
		puVirAddr_se =
			CVI_SYS_MmapCache(u64PhyAddr_se, u32BlkSize);
		memset(puVirAddr_se, 0, u32BlkSize);
		CVI_SYS_Munmap(puVirAddr_se, u32BlkSize);
	}

	stVideoFrame.stVFrame.u64PhyAddr[0] = u64PhyAddr_le;
	stVideoFrame.stVFrame.u64PhyAddr[1] = u64PhyAddr_se;
	pstVideoFrame[0] = &stVideoFrame;

	if (CVI_VI_SendPipeRaw(1, PipeId, pstVideoFrame, 0) != CVI_SUCCESS) {
		clog_e("Trig vsync failed\n");
		return CVI_FAILURE;
	}

	return CVI_SUCCESS;
}

int replay_sys_vi_int(daemon_pipe_cfg_t *pipe_cfg)
{
	raw_replay_cfg_t *replay_cfg = &pipe_cfg->raw_replay_cfg;
	CVI_S32 s32Ret = CVI_SUCCESS;

	s32Ret = replay_sys_init(pipe_cfg);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("replay_sys_init failed with %#x!\n", s32Ret);
		return -1;
	}

	s32Ret = replay_send_usr_pic(replay_cfg);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("replay_send_usr_pic failed with %#x!\n", s32Ret);
		return -1;
	}

	s32Ret = replay_vi_start_dev(replay_cfg);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("replay_vi_start_dev failed with %#x!\n", s32Ret);
		return -1;
	}

	s32Ret = replay_vi_start_pipe(replay_cfg);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("replay_vi_start_pipe failed with %#x!\n", s32Ret);
		return -1;
	}

	s32Ret = replay_vi_create_isp(replay_cfg,
				pipe_cfg->video_pipe_cfg.enable_teaisp_bnr);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("replay_vi_create_isp failed with %#x!\n", s32Ret);
		return -1;
	}

	s32Ret = replay_vi_start_chn(replay_cfg);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("replay_vi_start_chn failed with %#x!\n", s32Ret);
		return -1;
	}

	s32Ret = replay_vpss_init(pipe_cfg);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("replay_vpss_init failed with %#x!\n", s32Ret);
		return -1;
	}

	// ofline replay init
	if (replay_cfg->replay_scene == 0) {
		s32Ret = replay_offline_init(replay_cfg);
		if (s32Ret != CVI_SUCCESS) {
			clog_e("replay offline init failed with %#x!\n", s32Ret);
			return -1;
		}
	}

	// return the vi num, raw replay is 1
	return 1;
}

int replay_sys_vi_deinit(daemon_pipe_cfg_t *pipe_cfg)
{
	int s32Ret = CVI_SUCCESS;
	VI_DEV ViDev = 0;
	VI_PIPE ViPipe = 0;
	VI_CHN chn = 0;

	s32Ret = replay_vpss_deinit(pipe_cfg);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("replay_vpss_deinit failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_DisableChn(ViPipe, chn);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VI_DisableChn failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	SAMPLE_COMM_ISP_Stop(0);

	s32Ret = CVI_VI_StopPipe(ViPipe);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VI_StopPipe failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_DestroyPipe(ViPipe);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VI_DestroyPipe failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_DisableDev(ViDev);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_VI_DisableDev failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	CVI_VI_UnRegChnFlipMirrorCallBack(0, ViDev);
	CVI_VI_UnRegPmCallBack(ViDev);

	CVI_VB_Exit();
	CVI_SYS_Exit();

	return CVI_SUCCESS;
}

