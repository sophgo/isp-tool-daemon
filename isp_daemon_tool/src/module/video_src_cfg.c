
#include "sample_comm.h"
#include "daemon_base.h"
#include "daemon_cfg.h"
#include "video_src_cfg.h"
#include "cvi_ae_comm.h"
#include "cvi_awb_comm.h"

#define VPSS_ONLINE_GRP_0 0
#define USE_USER_SEN_DRIVER 1

#define CLOG_OUPUT_LVL CLOG_LVL_DEBUG
#undef CLOG_TAG
#define CLOG_TAG "video_src_cfg"

static SAMPLE_VI_CONFIG_S g_stViConfig;
static SENSOR_CFG_S g_stSensorCfg;

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

static CVI_S32 vpss_init(daemon_pipe_cfg_t *cfg, int vi_num, SNS_CFG_S *stSnsCfg)
{
	VPSS_GRP VpssGrp = VPSS_ONLINE_GRP_0;
	VPSS_GRP_ATTR_S stVpssGrpAttr;
	VPSS_CHN VpssChn = VPSS_CHN0;
	VPSS_CHN_ATTR_S astVpssChnAttr;
	CVI_S32 s32Ret = CVI_SUCCESS;

	UNUSED(cfg);

	memset(&stVpssGrpAttr, 0, sizeof(VPSS_GRP_ATTR_S));
	memset(&astVpssChnAttr, 0, sizeof(VPSS_CHN_ATTR_S));

	if (vi_num > VI_MAX_PIPE_NUM) {
		clog_e("vi_num is too large!\n");
		return -1;
	}

	for (int i = 0; i < vi_num; i++) {
		VpssGrp = i;

		stVpssGrpAttr.stFrameRate.s32SrcFrameRate = -1;
		stVpssGrpAttr.stFrameRate.s32DstFrameRate = -1;
		stVpssGrpAttr.enPixelFormat = SAMPLE_PIXEL_FORMAT;
		stVpssGrpAttr.u32MaxW = stSnsCfg->u32ImageWigth[i];
		stVpssGrpAttr.u32MaxH = stSnsCfg->u32ImageHeight[i];
		stVpssGrpAttr.u8VpssDev = 1;

		astVpssChnAttr.u32Width = stSnsCfg->u32ImageWigth[i];
		astVpssChnAttr.u32Height = stSnsCfg->u32ImageHeight[i];
		astVpssChnAttr.enVideoFormat = VIDEO_FORMAT_LINEAR;
		astVpssChnAttr.enPixelFormat = PIXEL_FORMAT_NV12;
		astVpssChnAttr.stFrameRate.s32SrcFrameRate = -1;
		astVpssChnAttr.stFrameRate.s32DstFrameRate = -1;
		astVpssChnAttr.u32Depth = 1;
		astVpssChnAttr.bMirror = CVI_FALSE;
		astVpssChnAttr.bFlip = CVI_FALSE;
		astVpssChnAttr.stAspectRatio.enMode =
			ASPECT_RATIO_NONE;
		astVpssChnAttr.stNormalize.bEnable = CVI_FALSE;

		s32Ret = CVI_VPSS_CreateGrp(VpssGrp, &stVpssGrpAttr);
		if (s32Ret != CVI_SUCCESS) {
			clog_e("CVI_VPSS_CreateGrp failed with %#x!\n", s32Ret);
			return s32Ret;
		}

		s32Ret = CVI_VPSS_SetChnAttr(VpssGrp, VpssChn, &astVpssChnAttr);
		if (s32Ret != CVI_SUCCESS) {
			clog_e("CVI_VPSS_SetChnAttr failed with %#x!\n", s32Ret);
			return s32Ret;
		}

		s32Ret = CVI_VPSS_EnableChn(VpssGrp, VpssChn);
		if (s32Ret != CVI_SUCCESS) {
			clog_e("CVI_VPSS_EnableChn failed with %#x!\n", s32Ret);
			return s32Ret;
		}

		s32Ret = CVI_VPSS_StartGrp(VpssGrp);
		if (s32Ret != CVI_SUCCESS) {
			clog_e("CVI_VPSS_StartGrp failed with %#x!\n", s32Ret);
			return s32Ret;
		}

		s32Ret = CVI_BIN_SetVpssGrpParams(VpssGrp);
		if (s32Ret != CVI_SUCCESS) {
			clog_e("CVI_BIN_SetVpssGrpParams failed with %#x!\n", s32Ret);
			return s32Ret;
		}
	}

	return s32Ret;
}

static CVI_S32 vpss_deinit(int vi_num)
{
	VPSS_GRP VpssGrp = VPSS_ONLINE_GRP_0;
	VPSS_CHN VpssChn = VPSS_CHN0;
	CVI_S32 s32Ret = CVI_SUCCESS;

	for (int i = 0; i < vi_num; i++) {
		VpssGrp = i;

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
	}

	return s32Ret;
}

int module_sys_vi_init(void *pipe_cfg)
{
	CVI_S32 s32Ret = CVI_SUCCESS;
	MMF_VERSION_S stVersion;
	LOG_LEVEL_CONF_S log_conf;
	VI_DEV_ATTR_S stVidevAttr;
	CVI_U32 Vb_cnt;

	memset(&stVersion, 0, sizeof(MMF_VERSION_S));
	memset(&log_conf, 0, sizeof(LOG_LEVEL_CONF_S));
	memset(&stVidevAttr, 0, sizeof(VI_DEV_ATTR_S));

	SENSOR_CFG_S *sensor_cfg = &g_stSensorCfg;

	memset(sensor_cfg, 0, sizeof(SENSOR_CFG_S));
	memset(&g_stViConfig, 0, sizeof(SAMPLE_VI_CONFIG_S));

	daemon_pipe_cfg_t *cfg = (daemon_pipe_cfg_t *)pipe_cfg;

	s32Ret = CVI_SYS_Init();
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_SYS_Init failed!\n");
		return s32Ret;
	}

	CVI_SYS_GetVersion(&stVersion);
	clog_i("MMF Version:%s\n", stVersion.version);

	log_conf.enModId = CVI_ID_LOG;
	log_conf.s32Level = CVI_DBG_INFO;
	CVI_LOG_SetLevelConf(&log_conf);

	/************************************************
	 * Parse sensor cfg ini, init vi config
	 ************************************************/
	s32Ret = CVI_SNS_SetIniPath(cfg->sns_cfg_ini);
	if (s32Ret == CVI_FAILURE) {
		clog_e("[ERROR] set ini path: %s fail\n", cfg->sns_cfg_ini);
		return s32Ret;
	}

	s32Ret = CVI_SNS_ParseIni(sensor_cfg);
	if (s32Ret == CVI_FAILURE) {
		clog_e("[ERROR] Parse fail\n");
		return s32Ret;
	}

	s32Ret = CVI_SNS_GetConfigInfo(sensor_cfg);
	if (s32Ret == CVI_FAILURE) {
		clog_e("[ERROR] get sns cfg failed\n");
		return s32Ret;
	}

	if (!cfg->video_pipe_cfg.enable_patgen) {
		s32Ret = CVI_SNS_SetSnsDrvCfg(sensor_cfg);
		if (s32Ret == CVI_FAILURE) {
			clog_e("[ERROR] set sns_drv failed\n");
			return s32Ret;
		}
	}

	VI_VPSS_MODE_E enViVpssMode = cfg->vi_vpss_mode;
	COMPRESS_MODE_E enCompressMode =
		get_compress_mode(cfg->video_pipe_cfg.compress_mode);
	SNS_INI_CFG_S *stSnsIniCfg = &sensor_cfg->sns_ini_cfg;
	SNS_CFG_S *stSnsCfg = &sensor_cfg->sns_cfg;

	for (int i = 0; i < stSnsIniCfg->devNum; i++) {
		g_stViConfig.s32ViNum = 1 + i;
		g_stViConfig.as32WorkingViId[i] = i;

		g_stViConfig.astViInfo[i].stDevInfo.ViDev = i;
		g_stViConfig.astViInfo[i].stDevInfo.enWDRMode =
			stSnsCfg->enWDRMode[i];

		for (int j = 0; j < WDR_MAX_PIPE_NUM; j++) {
			g_stViConfig.astViInfo[i].stPipeInfo.aPipe[j] =
				j == 0 ? i : -1;
		}
		g_stViConfig.astViInfo[i].stPipeInfo.enMastPipeMode =
			enViVpssMode;
		g_stViConfig.astViInfo[i].stPipeInfo.bMultiPipe = CVI_FALSE;
		g_stViConfig.astViInfo[i].stPipeInfo.bVcNumCfged = CVI_FALSE;

		g_stViConfig.astViInfo[i].stChnInfo.ViChn = 0;
		g_stViConfig.astViInfo[i].stChnInfo.enPixFormat =
			stSnsCfg->bBypassIsp[i] ? PIXEL_FORMAT_YUYV :
						  SAMPLE_PIXEL_FORMAT;
		g_stViConfig.astViInfo[i].stChnInfo.enDynamicRange =
			DYNAMIC_RANGE_SDR8;
		g_stViConfig.astViInfo[i].stChnInfo.enVideoFormat =
			VIDEO_FORMAT_LINEAR;
		g_stViConfig.astViInfo[i].stChnInfo.enCompressMode =
			enCompressMode;
	}

	g_stViConfig.stSnsCfg = *stSnsCfg;

	/************************************************
	 * Config vi vpss mode
	 ************************************************/
	VI_VPSS_MODE_S stVIVPSSMode = {0};
	VPSS_MODE_S stVPSSMode = {0};

	s32Ret = CVI_SYS_GetVIVPSSMode(&stVIVPSSMode);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_SYS_GetVIVPSSMode failed with %#x\n", s32Ret);
		return s32Ret;
	}

	for (CVI_S32 i = 0; i < g_stViConfig.s32ViNum; i++) {
		stVIVPSSMode.aenMode[i] = g_stViConfig.astViInfo[i].stPipeInfo.enMastPipeMode;
	}

	s32Ret = CVI_SYS_SetVIVPSSMode(&stVIVPSSMode);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_SYS_SetVIVPSSMode failed with %#x\n", s32Ret);
		return s32Ret;
	}

	stVPSSMode.enMode = VPSS_MODE_DUAL;
	stVPSSMode.aenInput[0] = VPSS_INPUT_MEM;
	stVPSSMode.aenInput[1] = VPSS_INPUT_ISP;
	if (cfg->vi_vpss_mode == VI_ONLINE_VPSS_ONLINE ||
		cfg->vi_vpss_mode == VI_OFFLINE_VPSS_ONLINE) {
		stVPSSMode.aenInput[1] = VPSS_INPUT_ISP;
	} else {
		stVPSSMode.aenInput[1] = VPSS_INPUT_MEM;
	}

	s32Ret = CVI_VPSS_SetMode(&stVPSSMode);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("CVI_SYS_SetVPSSModeEx failed with %#x\n", s32Ret);
		return s32Ret;
	}

	/************************************************
	 * Set VB config
	 ************************************************/
	CVI_U32 u32BlkSize;
	CVI_U32 u32BlkRotSize;
	VB_CONFIG_S stVbConf;
	SIZE_S stSize;

	memset(&stVbConf, 0, sizeof(VB_CONFIG_S));
	stVbConf.u32MaxPoolCnt = 0;

	for (int i = 0; i < stSnsIniCfg->devNum; i++) {
		Vb_cnt = 0;
		bool createNewPool = true;

		if (stSnsCfg->enFormatMode[i] == (SNS_DATA_TYPE_E) VI_DATA_TYPE_YUV) {
			if (stSnsCfg->enChnMode[i] ==
				(SNS_CHN_MODE_E) VI_WORK_MODE_2Multiplex) {
				Vb_cnt = 6;
			} else if (stSnsCfg->enChnMode[i] ==
				(SNS_CHN_MODE_E) VI_WORK_MODE_3Multiplex) {
				Vb_cnt = 9;
			} else if (stSnsCfg->enChnMode[i] ==
				(SNS_CHN_MODE_E) VI_WORK_MODE_4Multiplex) {
				Vb_cnt = 12;
			} else {
				Vb_cnt = 3;
			}
		} else {
			Vb_cnt = 3;
		}

		if (cfg->video_pipe_cfg.buf_blk_cnt > (int)Vb_cnt) {
			Vb_cnt = cfg->video_pipe_cfg.buf_blk_cnt;
		}

		stSize.u32Width = stSnsCfg->u32ImageWigth[i];
		stSize.u32Height = stSnsCfg->u32ImageHeight[i];

		if (i < cfg->dev_num) {
			cfg[i].src_width = stSize.u32Width;
			cfg[i].src_height = stSize.u32Height;
		}

		u32BlkSize = COMMON_GetPicBufferSize(
			stSize.u32Width, stSize.u32Height,
			g_stViConfig.astViInfo[i].stChnInfo.enPixFormat,
			DATA_BITWIDTH_8, COMPRESS_MODE_NONE, DEFAULT_ALIGN);
		u32BlkRotSize = COMMON_GetPicBufferSize(
			stSize.u32Height, stSize.u32Width,
			g_stViConfig.astViInfo[i].stChnInfo.enPixFormat,
			DATA_BITWIDTH_8, COMPRESS_MODE_NONE, DEFAULT_ALIGN);
		u32BlkSize =
			u32BlkSize > u32BlkRotSize ? u32BlkSize : u32BlkRotSize;

		for (CVI_U32 j = 0; j < stVbConf.u32MaxPoolCnt; j++) {
			if (stVbConf.astCommPool[j].u32BlkSize == u32BlkSize) {
				stVbConf.astCommPool[j].u32BlkCnt += Vb_cnt;
				createNewPool = false;
				break;
			}
		}

		if (createNewPool) {
			stVbConf.astCommPool[stVbConf.u32MaxPoolCnt].u32BlkSize =
				u32BlkSize;
			stVbConf.astCommPool[stVbConf.u32MaxPoolCnt].u32BlkCnt =
				Vb_cnt;
			stVbConf.astCommPool[stVbConf.u32MaxPoolCnt]
				.enRemapMode = VB_REMAP_MODE_CACHED;
			stVbConf.u32MaxPoolCnt++;
			clog_i("[INFO]  createNewPool VBpool [%d] %d:%d, BlkCnt= %d, Size = %d\n",
						stVbConf.u32MaxPoolCnt, stSnsCfg->u32ImageWigth[i],
						stSnsCfg->u32ImageHeight[i],
						stVbConf.astCommPool[stVbConf.u32MaxPoolCnt - 1].u32BlkCnt,
						stVbConf.astCommPool[stVbConf.u32MaxPoolCnt - 1].u32BlkSize);
		} else {
			clog_i("[INFO] set VBpool [%d] %d:%d, BlkCnt= %d, Size = %d\n",
						stVbConf.u32MaxPoolCnt, stSnsCfg->u32ImageWigth[i],
						stSnsCfg->u32ImageHeight[i],
						stVbConf.astCommPool[stVbConf.u32MaxPoolCnt - 1].u32BlkCnt,
						stVbConf.astCommPool[stVbConf.u32MaxPoolCnt - 1].u32BlkSize);
		}
	}

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

	/************************************************
	 * Set sns reset, probe; Set MIPI attr
	 ************************************************/
	for (int i = 0; i < stSnsIniCfg->devNum; i++) {
		s32Ret = CVI_MIPI_SetSensorReset(stSnsIniCfg->MipiDev[i], stSnsIniCfg->s32RstPort[i],
						stSnsIniCfg->s32RstPin[i], stSnsIniCfg->s32RstPol[i], 1);
		if (s32Ret != CVI_SUCCESS) {
			clog_e("[ERROR] sensor_%d reset failed!\n", i);
			return s32Ret;
		}
	}

	for (int i = 0; i < stSnsIniCfg->devNum; i++) {
		s32Ret = CVI_MIPI_SetMipiReset(stSnsIniCfg->MipiDev[i], 1);
		if (s32Ret != CVI_SUCCESS) {
			clog_e("[ERROR] mipi dev_%d reset failed!\n", i);
			return s32Ret;
		}
	}

	SNS_COMBO_DEV_ATTR_S pstRxAttr;

	memset(&pstRxAttr, 0, sizeof(SNS_COMBO_DEV_ATTR_S));
	for (int i = 0; i < stSnsIniCfg->devNum; i++) {
		if (CVI_SNS_GetSnsRxAttr(i, &pstRxAttr) != CVI_SUCCESS) {
			clog_e("[ERROR] get mipi dev_%d attr failed!\n", i);
			return CVI_FAILURE;
		}
		if (pstRxAttr.input_mode == INPUT_MODE_MIPI) {
			if (stSnsIniCfg->bHsettlen[i]) {
				pstRxAttr.mipi_attr.dphy.enable = 1;
				pstRxAttr.mipi_attr.dphy.hs_settle = stSnsIniCfg->u8Hsettle[i];
			}
		}
		if (pstRxAttr.input_mode == INPUT_MODE_MIPI ||
			pstRxAttr.input_mode == INPUT_MODE_SUBLVDS ||
			pstRxAttr.input_mode == INPUT_MODE_HISPI) {
			pstRxAttr.cif_mode = stSnsIniCfg->enSnsMode;
		}
		s32Ret = CVI_MIPI_SetMipiAttr(i, (CVI_VOID *)&pstRxAttr);
		if (s32Ret != CVI_SUCCESS) {
			clog_e("[ERROR] set mipi dev_%d attr failed!\n", i);
			return s32Ret;
		}
	}

	for (int i = 0; i < stSnsIniCfg->devNum; i++) {
		s32Ret = CVI_MIPI_SetSensorClock(stSnsIniCfg->MipiDev[i], 1);
		if (s32Ret != CVI_SUCCESS) {
			clog_e("[ERROR] sensor %d clock enable failed!\n", i);
			return s32Ret;
		}
	}

	for (int i = 0; i < stSnsIniCfg->devNum; i++) {
		s32Ret = CVI_MIPI_SetSensorReset(stSnsIniCfg->MipiDev[i], stSnsIniCfg->s32RstPort[i],
							stSnsIniCfg->s32RstPin[i], stSnsIniCfg->s32RstPol[i], 0);
		if (s32Ret != CVI_SUCCESS) {
			clog_e("[ERROR] sensor_%d unreset failed!\n", i);
			return s32Ret;
		}
	}

	for (int i = 0; i < stSnsIniCfg->devNum; i++) {
		if (CVI_SNS_SetSnsProbe(i) != CVI_SUCCESS) {
			clog_e("[ERROR] sensor_%d probe failed!\n", i);
			return CVI_FAILURE;
		}
	}

	/************************************************
	 * Set VI dev config
	 ************************************************/
	VI_DEV_ATTR_S       stViDevAttr;
	VI_DEV_BIND_PIPE_S  stViDevBindAttr;

	memset(&stViDevAttr, 0, sizeof(VI_DEV_ATTR_S));
	memset(&stViDevBindAttr, 0, sizeof(VI_DEV_BIND_PIPE_S));
	for (int i = 0; i < stSnsIniCfg->devNum; i++) {
		stViDevAttr.snrFps				= stSnsCfg->f32FrameRate[i];
		stViDevAttr.stSize.u32Width		= stSnsCfg->u32ImageWigth[i];
		stViDevAttr.stSize.u32Height	= stSnsCfg->u32ImageHeight[i];
		stViDevAttr.enIntfMode			= (VI_INTF_MODE_E)stSnsCfg->enInterFaceMode[i];
		stViDevAttr.enInputDataType		= (VI_DATA_TYPE_E)stSnsCfg->enFormatMode[i];
		stViDevAttr.enDataSeq			= (VI_YUV_DATA_SEQ_E)stSnsCfg->enYuvFormat[i];
		stViDevAttr.stWDRAttr.enWDRMode	= g_stViConfig.astViInfo[i].stDevInfo.enWDRMode;
		stViDevAttr.enWorkMode			= (VI_WORK_MODE_E)stSnsCfg->enChnMode[i];
		stViDevAttr.enBayerFormat       = (BAYER_FORMAT_E)stSnsCfg->enBayerFormat[i];
		stViDevBindAttr.PipeId[0]		= stSnsIniCfg->MipiDev[i];
		stViDevBindAttr.u32Num			= 1;
		stViDevBindAttr.MipiDev			= stSnsIniCfg->MipiDev[i];

		s32Ret = CVI_VI_SetDevAttr(g_stViConfig.astViInfo[i].stDevInfo.ViDev, &stViDevAttr);
		if (s32Ret != CVI_SUCCESS) {
			clog_e("[ERROR] CVI_VI_SetDevAttr failed with %#x!\n", s32Ret);
			return s32Ret;
		}
		s32Ret = CVI_VI_SetDevBindAttr(g_stViConfig.astViInfo[i].stDevInfo.ViDev, &stViDevBindAttr);
		if (s32Ret != CVI_SUCCESS) {
			clog_e("[ERROR] CVI_VI_SetDevBindAttr failed with %#x!\n", s32Ret);
			return s32Ret;
		}

		s32Ret = CVI_VI_EnableDev(g_stViConfig.astViInfo[i].stDevInfo.ViDev);
		if (s32Ret != CVI_SUCCESS) {
			clog_e("[ERROR] CVI_VI_EnableDev failed with %#x!\n", s32Ret);
			return s32Ret;
		}
	}

	/************************************************
	 * Set VI pipe config
	 ************************************************/
	VI_PIPE_ATTR_S stPipeAttr;

	memset(&stPipeAttr, 0, sizeof(VI_PIPE_ATTR_S));
	for (int i = 0; i < stSnsIniCfg->devNum; i++) {
		stPipeAttr.u32MaxW						= stSnsCfg->u32ImageWigth[i];
		stPipeAttr.u32MaxH						= stSnsCfg->u32ImageHeight[i];
		stPipeAttr.enPixFmt						= PIXEL_FORMAT_RGB_BAYER_12BPP;
		stPipeAttr.enBitWidth					= DATA_BITWIDTH_12;
		stPipeAttr.stFrameRate.s32SrcFrameRate	= -1;
		stPipeAttr.stFrameRate.s32DstFrameRate	= -1;
		stPipeAttr.bNrEn						= CVI_TRUE;
		stPipeAttr.bYuvBypassPath				= stSnsCfg->bBypassIsp[i];
		stPipeAttr.enCompressMode				=
							g_stViConfig.astViInfo[i].stChnInfo.enCompressMode;

		for (int j = 0; j < VI_MAX_PIPE_NUM; j++) {
			if (g_stViConfig.astViInfo[i].stPipeInfo.aPipe[j] >= 0 &&
				g_stViConfig.astViInfo[i].stPipeInfo.aPipe[j] < VI_MAX_PIPE_NUM) {
				s32Ret = CVI_VI_CreatePipe(g_stViConfig.astViInfo[i].stPipeInfo.aPipe[j], &stPipeAttr);
				if (s32Ret != CVI_SUCCESS) {
					clog_e("[ERROR] CVI_VI_CreatePipe failed with %#x!\n", s32Ret);
					return s32Ret;
				}

				s32Ret = CVI_VI_StartPipe(g_stViConfig.astViInfo[i].stPipeInfo.aPipe[j]);
				if (s32Ret != CVI_SUCCESS) {
					clog_e("[ERROR] CVI_VI_StartPipe failed with %#x!\n", s32Ret);
					return s32Ret;
				}
			}
		}
	}

	/************************************************
	 * start isp
	 ************************************************/
	s32Ret = SAMPLE_COMM_VI_CreateIsp(&g_stViConfig);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("VI_CreateIsp failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	/************************************************
	 * Set sensor init
	 ************************************************/
	for (int i = 0; i < stSnsIniCfg->devNum; i++) {
		if (cfg->video_pipe_cfg.enable_patgen) {
			break;
		}
		if (CVI_SNS_SetSnsInit(i) != CVI_SUCCESS) {
			clog_e("[ERROR] sensor_%d init failed!\n", i);
			return CVI_FAILURE;
		}
	}

	/************************************************
	 * Set VI chn config
	 ************************************************/
	VI_CHN_ATTR_S stChnAttr;

	memset(&stChnAttr, 0, sizeof(VI_CHN_ATTR_S));
	for (int i = 0; i < stSnsIniCfg->devNum; i++) {
		stChnAttr.stSize.u32Width = stSnsCfg->u32ImageWigth[i];
		stChnAttr.stSize.u32Height = stSnsCfg->u32ImageHeight[i];
		stChnAttr.enDynamicRange = g_stViConfig.astViInfo[i].stChnInfo.enDynamicRange;
		stChnAttr.enVideoFormat  = g_stViConfig.astViInfo[i].stChnInfo.enVideoFormat;
		stChnAttr.enCompressMode = g_stViConfig.astViInfo[i].stChnInfo.enCompressMode;
		stChnAttr.enPixelFormat = g_stViConfig.astViInfo[i].stChnInfo.enPixFormat;
		stChnAttr.u32Depth = 0;
		stChnAttr.u32BindVbPool = -1;

		/* fill the sensor orientation */
		stChnAttr.bMirror = false;
		stChnAttr.bFlip = false;

		s32Ret = CVI_VI_SetChnAttr(g_stViConfig.astViInfo[i].stPipeInfo.aPipe[0],
						g_stViConfig.astViInfo[i].stChnInfo.ViChn, &stChnAttr);
		if (s32Ret != CVI_SUCCESS) {
			clog_e("[ERROR] CVI_VI_SetChnAttr failed with %#x!\n", s32Ret);
			return s32Ret;
		}

		if (CVI_SNS_SetVIFlipMirrorCB(g_stViConfig.astViInfo[i].stPipeInfo.aPipe[0],
				g_stViConfig.astViInfo[i].stDevInfo.ViDev) != CVI_SUCCESS) {
			clog_e("[ERROR] CVI_SNS_SetVIFlipMirrorCB failed!\n");
		}

		s32Ret = CVI_VI_EnableChn(g_stViConfig.astViInfo[i].stPipeInfo.aPipe[0],
									g_stViConfig.astViInfo[i].stChnInfo.ViChn);
		if (s32Ret != CVI_SUCCESS) {
			clog_e("[ERROR] CVI_VI_EnableChn failed with %#x!\n", s32Ret);
			return s32Ret;
		}
	}

	/************************************************
	 *Config and init VPSS
	 ************************************************/
	s32Ret = vpss_init(cfg, stSnsIniCfg->devNum, stSnsCfg);
	if (s32Ret != CVI_SUCCESS) {
		clog_e("vpss_init failed. s32Ret: 0x%x !\n", s32Ret);
		return s32Ret;
	}

	for (CVI_S32 i = 0; i < stSnsIniCfg->devNum; i++) {
		if (cfg->vi_vpss_mode == VI_OFFLINE_VPSS_OFFLINE ||
			cfg->vi_vpss_mode == VI_ONLINE_VPSS_OFFLINE) {
			s32Ret = SAMPLE_COMM_VI_Bind_VPSS(0, i, i);
			if (s32Ret != CVI_SUCCESS) {
				clog_e("SAMPLE_COMM_VI_Bind_VPSS failed with %#x!\n", s32Ret);
				return s32Ret;
			}
		}
	}

	return stSnsIniCfg->devNum;
}

int module_sys_vi_deinit(void *pipe_cfg)
{
	CVI_S32 s32Ret = CVI_SUCCESS;
	CVI_S32 s32ViNum;
	CVI_S32 i;
	SAMPLE_VI_INFO_S stViInfo;
	VI_CHN ViChn;
	VI_PIPE ViPipe = 0;
	VI_VPSS_MODE_E enMastPipeMode;
	VI_DEV ViDev;

	daemon_pipe_cfg_t *cfg = (daemon_pipe_cfg_t *)pipe_cfg;

	for (CVI_S32 i = 0; i < g_stViConfig.s32ViNum; i++) {
		if (cfg->vi_vpss_mode == VI_OFFLINE_VPSS_OFFLINE ||
			cfg->vi_vpss_mode == VI_ONLINE_VPSS_OFFLINE) {
			s32Ret = SAMPLE_COMM_VI_UnBind_VPSS(0, i, i);
			if (s32Ret != CVI_SUCCESS) {
				clog_e("SAMPLE_COMM_VI_Unbind_VPSS failed with %#x!\n", s32Ret);
				return s32Ret;
			}
		}
	}

	vpss_deinit(g_stViConfig.s32ViNum);

	SAMPLE_COMM_VI_DestroyIsp(&g_stViConfig);

	for (i = 0; i < g_stViConfig.s32ViNum; i++) {
		s32ViNum  = g_stViConfig.as32WorkingViId[i];
		stViInfo = g_stViConfig.astViInfo[s32ViNum];

	/************************************************
	 *  VI chn stop
	 ************************************************/
		ViChn  = stViInfo.stChnInfo.ViChn;
		if (ViChn < VI_MAX_CHN_NUM) {
			enMastPipeMode = stViInfo.stPipeInfo.enMastPipeMode;

			if (enMastPipeMode == VI_OFFLINE_VPSS_OFFLINE
				|| enMastPipeMode == VI_ONLINE_VPSS_OFFLINE) {
				s32Ret = CVI_VI_DisableChn(ViPipe, ViChn);
				if (s32Ret != CVI_SUCCESS) {
					clog_e("CVI_VI_DisableChn failed with %#x!\n",
									s32Ret);
					return s32Ret;
				}
			}
		}
	/************************************************
	 *  VI pipe stop
	 ************************************************/
		for (i = 0; i < WDR_MAX_PIPE_NUM; i++) {
			if (stViInfo.stPipeInfo.aPipe[i] >= 0  && stViInfo.stPipeInfo.aPipe[i] < VI_MAX_PIPE_NUM) {
				ViPipe = stViInfo.stPipeInfo.aPipe[i];
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

			}
		}

	/************************************************
	 *  VI dev stop
	 ************************************************/
		ViDev   = stViInfo.stDevInfo.ViDev;
		s32Ret  = CVI_VI_DisableDev(ViDev);

		CVI_VI_UnRegChnFlipMirrorCallBack(0, ViDev);
		CVI_VI_UnRegPmCallBack(ViDev);

		if (s32Ret != CVI_SUCCESS) {
			clog_e("CVI_VI_DisableDev failed with %#x!\n", s32Ret);
			return s32Ret;
		}
	}

	CVI_VB_Exit();
	CVI_SYS_Exit();

	return 0;
}

