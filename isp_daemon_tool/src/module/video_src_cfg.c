
#include "sample_comm.h"
#include "daemon_base.h"
#include "daemon_cfg.h"
#include "video_src_cfg.h"
#include "cvi_ae_comm.h"
#include "cvi_awb_comm.h"
#include "cvi_af_comm.h"

static SAMPLE_VI_CONFIG_S g_stViConfig;
static SAMPLE_INI_CFG_S g_stIniCfg;

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

void _PLAT_ERR_Exit(void)
{
	if (g_stViConfig.s32WorkingViNum != 0) {
		SAMPLE_COMM_VI_DestroyIsp(&g_stViConfig);
		SAMPLE_COMM_VI_DestroyVi(&g_stViConfig);
	}
	SAMPLE_COMM_SYS_Exit();
}

static CVI_S32 vpss_init(daemon_pipe_cfg_t *cfg, int vi_num, SIZE_S *sns_size)
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
		CVI_TRACE_LOG(CVI_DBG_ERR, "vi_num is too large!\n");
		return -1;
	}

	for (int i = 0; i < vi_num; i++) {
		VpssGrp = i;

		stVpssGrpAttr.stFrameRate.s32SrcFrameRate = -1;
		stVpssGrpAttr.stFrameRate.s32DstFrameRate = -1;
		stVpssGrpAttr.enPixelFormat = SAMPLE_PIXEL_FORMAT;
		stVpssGrpAttr.u32MaxW = sns_size->u32Width;
		stVpssGrpAttr.u32MaxH = sns_size->u32Height;

		astVpssChnAttr.u32Width = sns_size->u32Width;
		astVpssChnAttr.u32Height = sns_size->u32Height;
		astVpssChnAttr.enVideoFormat = VIDEO_FORMAT_LINEAR;
		if (i < cfg->dev_num) {
			if (cfg[i].video_pipe_cfg.enable_teaisp_drc) {
				astVpssChnAttr.enPixelFormat =
					PIXEL_FORMAT_RGB_888_PLANAR;
			} else {
				astVpssChnAttr.enPixelFormat = SAMPLE_PIXEL_FORMAT;
			}
		} else {
			astVpssChnAttr.enPixelFormat = SAMPLE_PIXEL_FORMAT;
		}
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
			CVI_TRACE_LOG(CVI_DBG_ERR,
				      "CVI_VPSS_CreateGrp failed with %#x!\n",
				      s32Ret);
			return s32Ret;
		}

		s32Ret = CVI_VPSS_SetChnAttr(VpssGrp, VpssChn, &astVpssChnAttr);
		if (s32Ret != CVI_SUCCESS) {
			CVI_TRACE_LOG(CVI_DBG_ERR,
				      "CVI_VPSS_SetChnAttr failed with %#x!\n",
				      s32Ret);
			return s32Ret;
		}

		s32Ret = CVI_VPSS_EnableChn(VpssGrp, VpssChn);
		if (s32Ret != CVI_SUCCESS) {
			CVI_TRACE_LOG(CVI_DBG_ERR,
				      "CVI_VPSS_EnableChn failed with %#x!\n",
				      s32Ret);
			return s32Ret;
		}

		s32Ret = CVI_VPSS_StartGrp(VpssGrp);
		if (s32Ret != CVI_SUCCESS) {
			CVI_TRACE_LOG(CVI_DBG_ERR,
				      "CVI_VPSS_StartGrp failed with %#x!\n",
				      s32Ret);
			return s32Ret;
		}

		s32Ret = CVI_VPSS_SetGrpParamfromBin(VpssGrp, VpssChn);
		if (s32Ret != CVI_SUCCESS) {
			CVI_TRACE_LOG(CVI_DBG_ERR,
				      "CVI_VPSS_SetGrpParamfromBin failed with %#x!\n",
				      s32Ret);
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
			CVI_TRACE_LOG(CVI_DBG_ERR,
				      "CVI_VPSS_DisableChn failed with %#x!\n",
				      s32Ret);
			return s32Ret;
		}

		s32Ret = CVI_VPSS_StopGrp(VpssGrp);
		if (s32Ret != CVI_SUCCESS) {
			CVI_TRACE_LOG(CVI_DBG_ERR,
				      "CVI_VPSS_StopGrp failed with %#x!\n",
				      s32Ret);
			return s32Ret;
		}

		s32Ret = CVI_VPSS_DestroyGrp(VpssGrp);
		if (s32Ret != CVI_SUCCESS) {
			CVI_TRACE_LOG(CVI_DBG_ERR,
				      "CVI_VPSS_DestroyGrp failed with %#x!\n",
				      s32Ret);
			return s32Ret;
		}
	}

	return s32Ret;
}

static CVI_S32 vi_start_dev(SAMPLE_VI_INFO_S *pstViInfo)
{
	CVI_S32 s32Ret;
	VI_DEV ViDev;
	CVI_SNS_TYPE_E enSnsType;
	VI_DEV_ATTR_S stViDevAttr;
	VI_DEV_BIND_PIPE_S stViDevBindAttr;
	ISP_PUB_ATTR_S pstPubAttr;

	ViDev = pstViInfo->stDevInfo.ViDev;
	enSnsType = pstViInfo->stSnsInfo.enSnsType;

	SAMPLE_COMM_VI_GetDevAttrBySns(enSnsType, &stViDevAttr);
	SAMPLE_COMM_ISP_GetIspAttrBySns(enSnsType, &pstPubAttr);
	stViDevAttr.stWDRAttr.enWDRMode = pstViInfo->stDevInfo.enWDRMode;
	stViDevAttr.snrFps = (CVI_U32)pstPubAttr.f32FrameRate;
	stViDevBindAttr.PipeId[0] = (CVI_S32)pstViInfo->stSnsInfo.MipiDev;
	stViDevBindAttr.u32Num = 1;
	stViDevAttr.enYuvSceneMode = VI_ISP_YUV_SCENE_ISP;

	s32Ret = CVI_VI_SetDevAttr(ViDev, &stViDevAttr);
	if (s32Ret != CVI_SUCCESS) {
		CVI_TRACE_LOG(CVI_DBG_ERR,
			      "CVI_VI_SetDevAttr failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_SetDevBindAttr(ViDev, &stViDevBindAttr);
	if (s32Ret != CVI_SUCCESS) {
		CVI_TRACE_LOG(CVI_DBG_ERR,
			      "CVI_VI_SetDevBindAttr failed with %#x!\n",
			      s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_EnableDev(ViDev);
	if (s32Ret != CVI_SUCCESS) {
		CVI_TRACE_LOG(CVI_DBG_ERR,
			      "CVI_VI_EnableDev failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	return CVI_SUCCESS;
}

static CVI_S32 vi_start_cfg(SAMPLE_VI_CONFIG_S *pstViConfig)
{
	PIC_SIZE_E enPicSize;
	SIZE_S stSize;

	VI_DEV ViDev = 0;
	VI_PIPE ViPipe = 0;
	VI_PIPE_ATTR_S stPipeAttr;

	CVI_S32 s32Ret = CVI_SUCCESS;
	CVI_S32 i = 0, j = 0;
	CVI_S32 s32DevNum;

	memcpy((void *)&g_stViConfig, (void *)pstViConfig,
	       sizeof(SAMPLE_VI_CONFIG_S));

	/************************************************
	 * step1:  Get input size
	 ************************************************/
	s32Ret = SAMPLE_COMM_VI_GetSizeBySensor(
		pstViConfig->astViInfo[ViDev].stSnsInfo.enSnsType, &enPicSize);
	if (s32Ret != CVI_SUCCESS) {
		CVI_TRACE_LOG(
			CVI_DBG_ERR,
			"SAMPLE_COMM_VI_GetSizeBySensor failed with %#x\n",
			s32Ret);
		goto error;
	}

	s32Ret = SAMPLE_COMM_SYS_GetPicSize(enPicSize, &stSize);
	if (s32Ret != CVI_SUCCESS) {
		CVI_TRACE_LOG(CVI_DBG_ERR,
			      "SAMPLE_COMM_SYS_GetPicSize failed with %#x\n",
			      s32Ret);
		goto error;
	}

	/************************************************
	 * step2:  Init VI ISP
	 ************************************************/
#if USE_USER_SEN_DRIVER
	s32Ret = SAMPLE_COMM_VI_StartSensor(pstViConfig);
	if (s32Ret != CVI_SUCCESS) {
		CVI_TRACE_LOG(CVI_DBG_ERR,
			      "system start sensor failed with %#x\n", s32Ret);
		goto error;
	}
#endif
	for (i = 0; i < pstViConfig->s32WorkingViNum; i++) {
		ViDev = i;

		s32Ret = vi_start_dev(&pstViConfig->astViInfo[ViDev]);
		if (s32Ret != CVI_SUCCESS) {
			CVI_TRACE_LOG(CVI_DBG_ERR,
				      "VI_StartDev failed with %#x!\n", s32Ret);
			goto error;
		}
	}

#if USE_USER_SEN_DRIVER
	s32Ret = SAMPLE_COMM_VI_StartMIPI(pstViConfig);
	if (s32Ret != CVI_SUCCESS) {
		CVI_TRACE_LOG(CVI_DBG_ERR,
			      "system start MIPI failed with %#x\n", s32Ret);
		goto error;
	}

	s32Ret = SAMPLE_COMM_VI_SensorProbe(pstViConfig);
	if (s32Ret != CVI_SUCCESS) {
		CVI_TRACE_LOG(CVI_DBG_ERR,
			      "system sensor probe failed with %#x\n", s32Ret);
		goto error;
	}
#endif

	stPipeAttr.bYuvSkip = CVI_FALSE;
	stPipeAttr.u32MaxW = stSize.u32Width;
	stPipeAttr.u32MaxH = stSize.u32Height;
	stPipeAttr.enPixFmt = PIXEL_FORMAT_RGB_BAYER_12BPP;
	stPipeAttr.enBitWidth = DATA_BITWIDTH_12;
	stPipeAttr.stFrameRate.s32SrcFrameRate = -1;
	stPipeAttr.stFrameRate.s32DstFrameRate = -1;
	stPipeAttr.bNrEn = CVI_TRUE;
	stPipeAttr.bYuvBypassPath = CVI_FALSE;
	stPipeAttr.enCompressMode =
		pstViConfig->astViInfo[0].stChnInfo.enCompressMode;

	for (i = 0; i < pstViConfig->s32WorkingViNum; i++) {
		SAMPLE_VI_INFO_S *pstViInfo = NULL;

		s32DevNum = pstViConfig->as32WorkingViId[i];
		pstViInfo = &pstViConfig->astViInfo[s32DevNum];
		stPipeAttr.bYuvBypassPath = SAMPLE_COMM_VI_GetYuvBypassSts(
			pstViInfo->stSnsInfo.enSnsType);

		for (j = 0; j < WDR_MAX_PIPE_NUM; j++) {
			if (pstViInfo->stPipeInfo.aPipe[j] >= 0 &&
			    pstViInfo->stPipeInfo.aPipe[j] < VI_MAX_PIPE_NUM) {
				ViPipe = pstViInfo->stPipeInfo.aPipe[j];
				s32Ret = CVI_VI_CreatePipe(ViPipe, &stPipeAttr);
				if (s32Ret != CVI_SUCCESS) {
					CVI_TRACE_LOG(
						CVI_DBG_ERR,
						"CVI_VI_CreatePipe failed with %#x!\n",
						s32Ret);
					goto error;
				}

				s32Ret = CVI_VI_StartPipe(ViPipe);
				if (s32Ret != CVI_SUCCESS) {
					CVI_TRACE_LOG(
						CVI_DBG_ERR,
						"CVI_VI_StartPipe failed with %#x!\n",
						s32Ret);
					goto error;
				}

				s32Ret =
					CVI_VI_GetPipeAttr(ViPipe, &stPipeAttr);
				if (s32Ret != CVI_SUCCESS) {
					CVI_TRACE_LOG(
						CVI_DBG_ERR,
						"CVI_VI_GetPipeAttr failed with %#x!\n",
						s32Ret);
					goto error;
				}
			}
		}
	}

	s32Ret = SAMPLE_COMM_VI_CreateIsp(pstViConfig);
	if (s32Ret != CVI_SUCCESS) {
		CVI_TRACE_LOG(CVI_DBG_ERR, "VI_CreateIsp failed with %#x!\n",
			      s32Ret);
		goto error;
	}

	s32Ret = SAMPLE_COMM_VI_StartViChn(pstViConfig);
	if (s32Ret != CVI_SUCCESS) {
		CVI_TRACE_LOG(CVI_DBG_ERR, "VI_StartViChn failed with %#x!\n",
			      s32Ret);
		goto error;
	}

	return s32Ret;
error:
	_PLAT_ERR_Exit();
	return s32Ret;
}

int module_sys_vi_init(void *pipe_cfg)
{
	CVI_S32 s32Ret = CVI_SUCCESS;
	MMF_VERSION_S stVersion;
	SAMPLE_INI_CFG_S stIniCfg;
	SAMPLE_VI_CONFIG_S stViConfig;
	LOG_LEVEL_CONF_S log_conf;
	VI_DEV_ATTR_S stVidevAttr;
	CVI_U32 Vb_cnt;

	daemon_pipe_cfg_t *cfg = (daemon_pipe_cfg_t *)pipe_cfg;

	memset(&stVersion, 0, sizeof(MMF_VERSION_S));
	memset(&stIniCfg, 0, sizeof(SAMPLE_INI_CFG_S));
	memset(&stViConfig, 0, sizeof(SAMPLE_VI_CONFIG_S));
	memset(&log_conf, 0, sizeof(LOG_LEVEL_CONF_S));
	memset(&stVidevAttr, 0, sizeof(VI_DEV_ATTR_S));

	CVI_SYS_GetVersion(&stVersion);
	SAMPLE_PRT("MMF Version:%s\n", stVersion.version);

	log_conf.enModId = CVI_ID_LOG;
	log_conf.s32Level = CVI_DBG_INFO;
	CVI_LOG_SetLevelConf(&log_conf);

	// Get config from ini if found.
	s32Ret = SAMPLE_COMM_VI_ParseIni(&stIniCfg);
	if (s32Ret != CVI_SUCCESS) {
		SAMPLE_PRT("Parse fail\n");
	} else {
		SAMPLE_PRT("Parse complete\n");
	}

	//Set sensor number
	CVI_VI_SetDevNum(stIniCfg.devNum);
	/************************************************
	 * step1:  Config VI
	 ************************************************/
	s32Ret = SAMPLE_COMM_VI_IniToViCfg(&stIniCfg, &stViConfig);
	if (s32Ret != CVI_SUCCESS)
		return s32Ret;

	COMPRESS_MODE_E enCompressMode =
		get_compress_mode(cfg->video_pipe_cfg.compress_mode);

	for (CVI_S32 i = 0; i < stViConfig.s32WorkingViNum; i++) {
		stViConfig.astViInfo[i].stChnInfo.enCompressMode =
			enCompressMode;
	}

	CVI_U32 u32TEAISPMode = TEAISP_OFF_MODE;

	if (cfg->video_pipe_cfg.enable_teaisp_bnr) {
		if (stViConfig.s32WorkingViNum > 1) {
			u32TEAISPMode = TEAISP_AFTER_FE_RAW_MODE;
		} else {
			u32TEAISPMode = TEAISP_BEFORE_FE_RAW_MODE;
		}
	}

	for (CVI_S32 i = 0; i < stViConfig.s32WorkingViNum; i++) {
		stViConfig.astViInfo[i].stPipeInfo.u32TEAISPMode =
			u32TEAISPMode;
	}

	memcpy(&g_stViConfig, &stViConfig, sizeof(SAMPLE_VI_CONFIG_S));
	memcpy(&g_stIniCfg, &stIniCfg, sizeof(SAMPLE_INI_CFG_S));

	/************************************************
	 * step2:  Get input size
	 ************************************************/
	CVI_U32 u32BlkSize;
	//CVI_U32 u32BlkRotSize;
	PIC_SIZE_E enPicSize;
	VB_CONFIG_S stVbConf;
	SIZE_S stSize;

	memset(&stVbConf, 0, sizeof(VB_CONFIG_S));
	stVbConf.u32MaxPoolCnt = 0;

	for (CVI_S32 i = 0; i < stViConfig.s32WorkingViNum; i++) {
		Vb_cnt = 0;
		bool createNewPool = true;

		s32Ret = SAMPLE_COMM_VI_GetSizeBySensor(stIniCfg.enSnsType[i],
							&enPicSize);
		if (s32Ret != CVI_SUCCESS) {
			CVI_TRACE_LOG(
				CVI_DBG_ERR,
				"SAMPLE_COMM_VI_GetSizeBySensor failed with %#x\n",
				s32Ret);
			return s32Ret;
		}

		s32Ret = SAMPLE_COMM_SYS_GetPicSize(enPicSize, &stSize);
		if (s32Ret != CVI_SUCCESS) {
			CVI_TRACE_LOG(
				CVI_DBG_ERR,
				"SAMPLE_COMM_SYS_GetPicSize failed with %#x\n",
				s32Ret);
			return s32Ret;
		}

		s32Ret = SAMPLE_COMM_VI_GetDevAttrBySns(stIniCfg.enSnsType[i],
							&stVidevAttr);
		if (s32Ret != CVI_SUCCESS) {
			CVI_TRACE_LOG(
				CVI_DBG_ERR,
				"SAMPLE_COMM_VI_GetDevAttrBySns failed with %#x\n",
				s32Ret);
			return s32Ret;
		}
		if (stVidevAttr.enInputDataType == VI_DATA_TYPE_YUV) {
			if (stVidevAttr.enWorkMode == VI_WORK_MODE_2Multiplex) {
				Vb_cnt = 6;
			} else if (stVidevAttr.enWorkMode ==
				   VI_WORK_MODE_3Multiplex) {
				Vb_cnt = 9;
			} else if (stVidevAttr.enWorkMode ==
				   VI_WORK_MODE_4Multiplex) {
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

		u32BlkSize = COMMON_GetPicBufferSize(
			stSize.u32Width, stSize.u32Height,
			stViConfig.astViInfo[i].stChnInfo.enPixFormat,
			DATA_BITWIDTH_8, COMPRESS_MODE_NONE, DEFAULT_ALIGN);
		//u32BlkRotSize = COMMON_GetPicBufferSize(
		//	stSize.u32Height, stSize.u32Width,
		//	stViConfig.astViInfo[i].stChnInfo.enPixFormat,
		//	DATA_BITWIDTH_8, COMPRESS_MODE_NONE, DEFAULT_ALIGN);
		//u32BlkSize =
		//	u32BlkSize > u32BlkRotSize ? u32BlkSize : u32BlkRotSize;

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
			SAMPLE_PRT(
				"set VBpool [%d] %d:%d, BlkCnt= %d, Size = %d\n",
				stVbConf.u32MaxPoolCnt, stSize.u32Width,
				stSize.u32Height,
				stVbConf.astCommPool[stVbConf.u32MaxPoolCnt]
					.u32BlkCnt,
				stVbConf.astCommPool[stVbConf.u32MaxPoolCnt]
					.u32BlkSize);
			stVbConf.u32MaxPoolCnt++;
		} else {
			SAMPLE_PRT(
				"set VBpool [%d] %d:%d, BlkCnt= %d, Size = %d\n",
				stVbConf.u32MaxPoolCnt, stSize.u32Width,
				stSize.u32Height,
				stVbConf.astCommPool[stVbConf.u32MaxPoolCnt]
					.u32BlkCnt,
				stVbConf.astCommPool[stVbConf.u32MaxPoolCnt]
					.u32BlkSize);
		}
	}

	for (CVI_S32 i = 0; i < stViConfig.s32WorkingViNum; i++) {
		Vb_cnt = 5;
		bool createNewPool = true;

		if (i < cfg->dev_num) {
			if (cfg[i].video_pipe_cfg.enable_teaisp_drc == 0) {
				continue;
			}
		} else {
			continue;
		}

		u32BlkSize = COMMON_GetPicBufferSize(
			cfg[i].src_width, cfg[i].src_height,
			PIXEL_FORMAT_RGB_888_PLANAR,
			DATA_BITWIDTH_8, COMPRESS_MODE_NONE, DEFAULT_ALIGN);

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
		}
	}

	/************************************************
	 * step3:  Init modules
	 ************************************************/
	s32Ret = SAMPLE_COMM_SYS_Init(&stVbConf);
	if (s32Ret != CVI_SUCCESS) {
		CVI_TRACE_LOG(CVI_DBG_ERR,
			      "system init failed. s32Ret: 0x%x !\n", s32Ret);
		return s32Ret;
	}

	/************************************************
	 * step4: Config vi vpss mode
	 ************************************************/
	VI_VPSS_MODE_S stVIVPSSMode = {};

	s32Ret = CVI_SYS_GetVIVPSSMode(&stVIVPSSMode);
	if (s32Ret != CVI_SUCCESS) {
		printf("CVI_SYS_GetVIVPSSMode failed with %#x\n", s32Ret);
		return s32Ret;
	}

	for (CVI_S32 i = 0; i < stViConfig.s32WorkingViNum; i++) {
		stVIVPSSMode.aenMode[i] = cfg->vi_vpss_mode;
	}

	s32Ret = CVI_SYS_SetVIVPSSMode(&stVIVPSSMode);
	if (s32Ret != CVI_SUCCESS) {
		printf("CVI_SYS_SetVIVPSSMode failed with %#x\n", s32Ret);
		return s32Ret;
	}


	/************************************************
	 * step5: Start vi
	 ************************************************/
	s32Ret = vi_start_cfg(&stViConfig);
	if (s32Ret != CVI_SUCCESS) {
		CVI_TRACE_LOG(CVI_DBG_ERR, "vi init failed. s32Ret: 0x%x !\n",
			      s32Ret);
		return s32Ret;
	}

	/************************************************
	 * step6: Config and init VPSS
	 ************************************************/
	s32Ret = vpss_init(cfg, stViConfig.s32WorkingViNum, &stSize);
	if (s32Ret != CVI_SUCCESS) {
		CVI_TRACE_LOG(CVI_DBG_ERR,
			      "vpss_init failed. s32Ret: 0x%x !\n", s32Ret);
		return s32Ret;
	}

	for (CVI_S32 i = 0; i < stViConfig.s32WorkingViNum; i++) {
		if (cfg->vi_vpss_mode == VI_OFFLINE_VPSS_OFFLINE ||
		    cfg->vi_vpss_mode == VI_ONLINE_VPSS_OFFLINE) {
			s32Ret = SAMPLE_COMM_VI_Bind_VPSS(0, i, i);
			if (s32Ret != CVI_SUCCESS) {
				CVI_TRACE_LOG(CVI_DBG_ERR,
					      "SAMPLE_COMM_VI_Bind_VPSS failed with %#x!\n",
					      s32Ret);
				return s32Ret;
			}
		}
	}

	return stViConfig.s32WorkingViNum;
}

int module_sys_vi_deinit(void *pipe_cfg)
{
	CVI_S32 s32Ret = CVI_SUCCESS;
	daemon_pipe_cfg_t *cfg = (daemon_pipe_cfg_t *)pipe_cfg;

	for (CVI_S32 i = 0; i < g_stViConfig.s32WorkingViNum; i++) {
		if (cfg->vi_vpss_mode == VI_OFFLINE_VPSS_OFFLINE ||
		    cfg->vi_vpss_mode == VI_ONLINE_VPSS_OFFLINE) {
			s32Ret = SAMPLE_COMM_VI_UnBind_VPSS(0, i, i);
			if (s32Ret != CVI_SUCCESS) {
				CVI_TRACE_LOG(CVI_DBG_ERR,
					      "SAMPLE_COMM_VI_Unbind_VPSS failed with %#x!\n",
					      s32Ret);
				return s32Ret;
			}
		}
	}

	vpss_deinit(g_stViConfig.s32WorkingViNum);

	SAMPLE_COMM_VI_DestroyIsp(&g_stViConfig);

	SAMPLE_COMM_VI_DestroyVi(&g_stViConfig);

	SAMPLE_COMM_SYS_Exit();

	return 0;
}

static VI_DEV_ATTR_S DEV_ATTR_SENSOR_DEFAULT = {
	VI_MODE_MIPI,
	VI_WORK_MODE_1Multiplex,
	VI_SCAN_PROGRESSIVE,
	{ -1, -1, -1, -1 },
	VI_DATA_SEQ_YUYV,
	{ VI_VSYNC_PULSE,
	  VI_VSYNC_NEG_LOW,
	  VI_HSYNC_VALID_SINGNAL,
	  VI_HSYNC_NEG_HIGH,
	  VI_VSYNC_VALID_SIGNAL,
	  VI_VSYNC_VALID_NEG_HIGH,
	  { 0, 1920, 0, 0, 1080, 0, 0, 0, 0 } },
	VI_DATA_TYPE_RGB,
	{ 1920, 1080 },
	{ WDR_MODE_NONE, 1080 },
	.enBayerFormat = BAYER_FORMAT_BG,
};

static VI_CHN_ATTR_S CHN_ATTR_DEFAULT = {
	{ 1920, 1080 },	    PIXEL_FORMAT_YUV_PLANAR_420,
	DYNAMIC_RANGE_SDR8, VIDEO_FORMAT_LINEAR,
	COMPRESS_MODE_NONE, CVI_FALSE,
	CVI_FALSE,	    0,
	{ -1, -1 },	    0
};

static ISP_PUB_ATTR_S ISP_PUB_ATTR_DEFAULT = { { 0, 0, 1920, 1080 },
					       { 1920, 1080 },
					       25,
					       BAYER_RGGB,
					       WDR_MODE_NONE,
					       0,
					       4,
					       2 };

static CVI_S32 replay_startIsp(raw_replay_cfg_t *cfg, int enable_teaisp)
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
		SAMPLE_PRT("Bind Algo failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_ISP_MemInit(ViPipe);
	if (s32Ret != CVI_SUCCESS) {
		SAMPLE_PRT("Init Ext memory failed with %#x!\n", s32Ret);
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
		SAMPLE_PRT("SetPubAttr failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_ISP_Init(ViPipe);
	if (s32Ret != CVI_SUCCESS) {
		SAMPLE_PRT("ISP Init failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	if (enable_teaisp) {
		CVI_TEAISP_SetMode(ViPipe, TEAISP_BEFORE_FE_RAW_MODE);
	}

	return CVI_SUCCESS;
}

static CVI_S32 replay_startViChn(raw_replay_cfg_t *cfg)
{
	CVI_S32 s32Ret = CVI_SUCCESS;
	VI_PIPE ViPipe = 0;
	VI_CHN ViChn = 0;
	VI_CHN_ATTR_S stChnAttr;

	memcpy(&stChnAttr, &CHN_ATTR_DEFAULT, sizeof(VI_CHN_ATTR_S));
	stChnAttr.enPixelFormat = PIXEL_FORMAT_NV21;
	stChnAttr.stSize.u32Width = cfg->width;
	stChnAttr.stSize.u32Height = cfg->height;
	stChnAttr.enDynamicRange =
		cfg->wdr_mode ? DYNAMIC_RANGE_HDR10 : DYNAMIC_RANGE_SDR10;
	stChnAttr.enVideoFormat = VIDEO_FORMAT_LINEAR;
	stChnAttr.enCompressMode = get_compress_mode(cfg->compress_mode);
	/* fill the sensor orientation */
	stChnAttr.bMirror = 0;
	stChnAttr.bFlip = 0;

	s32Ret = CVI_VI_SetChnAttr(ViPipe, ViChn, &stChnAttr);
	if (s32Ret != CVI_SUCCESS) {
		SAMPLE_PRT("CVI_VI_SetChnAttr failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_EnableChn(ViPipe, ViChn);
	if (s32Ret != CVI_SUCCESS) {
		SAMPLE_PRT("CVI_VI_EnableChn failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	return CVI_SUCCESS;
}

static CVI_S32 replay_createIsp(raw_replay_cfg_t *cfg, int enable_teaisp)
{
	CVI_S32 s32Ret = CVI_SUCCESS;
	ISP_PUB_ATTR_S stPubAttr;

	s32Ret = replay_startIsp(cfg, enable_teaisp);
	if (s32Ret != CVI_SUCCESS) {
		SAMPLE_PRT("replay_startIsp failed !\n");
		return s32Ret;
	}

	s32Ret = SAMPLE_COMM_BIN_ReadParaFrombin();
	if (s32Ret != CVI_SUCCESS) {
		SAMPLE_PRT("read para fail: %#x,use default para!\n", s32Ret);
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
		SAMPLE_PRT("SetPubAttr failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = SAMPLE_COMM_ISP_Run(0);
	if (s32Ret != CVI_SUCCESS) {
		SAMPLE_PRT("ISP_Run failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	return CVI_SUCCESS;
}

static CVI_S32 replay_vi_start_dev(raw_replay_cfg_t *cfg)
{
	CVI_S32 s32Ret;
	VI_DEV_ATTR_S stViDevAttr;
	VI_DEV_BIND_PIPE_S stViDevBindAttr;

	memcpy(&stViDevAttr, &DEV_ATTR_SENSOR_DEFAULT, sizeof(VI_DEV_ATTR_S));

	if (!cfg->pixel_format) {
		stViDevAttr.stSize.u32Width = cfg->width;
		stViDevAttr.stSize.u32Height = cfg->height;
		if (cfg->wdr_mode) {
			stViDevAttr.stWDRAttr.enWDRMode = WDR_MODE_2To1_LINE;
			stViDevAttr.stWDRAttr.u32CacheLine = cfg->width;
		}
		stViDevAttr.enInputDataType = VI_DATA_TYPE_RGB;
		stViDevAttr.enBayerFormat = (BAYER_FORMAT_E)cfg->bayer_format;
	} else {
		stViDevAttr.stSize.u32Width = cfg->width;
		stViDevAttr.stSize.u32Height = cfg->height;
		stViDevAttr.stWDRAttr.u32CacheLine = cfg->width;
		stViDevAttr.enDataSeq = VI_DATA_SEQ_YUYV;
		stViDevAttr.enInputDataType = VI_DATA_TYPE_YUV;
		stViDevAttr.enIntfMode = VI_MODE_MIPI_YUV422;
		stViDevAttr.enYuvSceneMode = VI_ISP_YUV_SCENE_ISP;
	}
	stViDevAttr.snrFps = cfg->frame_rate;
	stViDevBindAttr.PipeId[0] = 0;
	stViDevBindAttr.u32Num = 1;

	s32Ret = CVI_VI_SetDevAttr(0, &stViDevAttr);
	if (s32Ret != CVI_SUCCESS) {
		SAMPLE_PRT("CVI_VI_SetDevAttr failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_SetDevBindAttr(0, &stViDevBindAttr);
	if (s32Ret != CVI_SUCCESS) {
		SAMPLE_PRT("CVI_VI_SetDevBindAttr failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_EnableDev(0);
	if (s32Ret != CVI_SUCCESS) {
		SAMPLE_PRT("CVI_VI_EnableDev failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	return CVI_SUCCESS;
}

static CVI_S32 replay_set_mode_config(raw_replay_cfg_t *cfg)
{
	CVI_S32 s32Ret;
	VI_DEV_TIMING_ATTR_S stTimingAttr;

	stTimingAttr.bEnable = cfg->timing_enable;
	stTimingAttr.s32FrmRate = cfg->frame_rate;

	s32Ret = CVI_VI_SetPipeFrameSource(0, VI_PIPE_FRAME_SOURCE_USER_FE);
	if (s32Ret != CVI_SUCCESS) {
		printf("CVI_VI_SetPipeFrameSource failed with %#x\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_SetDevTimingAttr(0, &stTimingAttr);
	if (s32Ret != CVI_SUCCESS) {
		printf("CVI_VI_SetDevTimingAttr failed with %#x\n", s32Ret);
		return s32Ret;
	}

	return CVI_SUCCESS;
}

static CVI_S32 replay_trig_pic(raw_replay_cfg_t *cfg)
{
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

	if (cfg->timing_enable) {
		blk_le = CVI_VB_GetBlock(VB_INVALID_POOLID, u32BlkSize);
		if (blk_le == VB_INVALID_HANDLE) {
			SAMPLE_PRT("get blk_le failed\n");
			return CVI_FAILURE;
		}
		u64PhyAddr_le = CVI_VB_Handle2PhysAddr(blk_le);
		puVirAddr_le = CVI_SYS_MmapCache(u64PhyAddr_le, u32BlkSize);
		memset(puVirAddr_le, 0, u32BlkSize);
		CVI_SYS_Munmap(puVirAddr_le, u32BlkSize);

		if (stVideoFrame.stVFrame.enDynamicRange ==
			    DYNAMIC_RANGE_HDR10 ||
		    stVideoFrame.stVFrame.enPixelFormat) {
			blk_se = CVI_VB_GetBlock(VB_INVALID_POOLID, u32BlkSize);
			if (blk_se == VB_INVALID_HANDLE) {
				SAMPLE_PRT("get blk_se failed\n");
				return CVI_FAILURE;
			}
			u64PhyAddr_se = CVI_VB_Handle2PhysAddr(blk_se);
			puVirAddr_se =
				CVI_SYS_MmapCache(u64PhyAddr_se, u32BlkSize);
			memset(puVirAddr_se, 0, u32BlkSize);
			CVI_SYS_Munmap(puVirAddr_se, u32BlkSize);
		}
	}

	stVideoFrame.stVFrame.u64PhyAddr[0] = u64PhyAddr_le;
	stVideoFrame.stVFrame.u64PhyAddr[1] = u64PhyAddr_se;
	pstVideoFrame[0] = &stVideoFrame;

	if (CVI_VI_SendPipeRaw(1, PipeId, pstVideoFrame, 0) != CVI_SUCCESS) {
		SAMPLE_PRT("Trig vsync failed\n");
		return CVI_FAILURE;
	}

	return CVI_SUCCESS;
}

static int replay_sys_init(raw_replay_cfg_t *cfg, int vb_blk_cnt)
{
	CVI_S32 s32Ret = CVI_SUCCESS;
	SIZE_S stSize;
	VB_CONFIG_S stVbConf;
	CVI_U32 u32BlkSize;

	memset(&stVbConf, 0, sizeof(VB_CONFIG_S));

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
	stVbConf.astCommPool[0].u32BlkCnt = vb_blk_cnt;
	stVbConf.astCommPool[0].enRemapMode = VB_REMAP_MODE_CACHED;

	s32Ret = SAMPLE_COMM_SYS_Init(&stVbConf);
	if (s32Ret != CVI_SUCCESS) {
		printf("sys init failed. s32Ret: 0x%x !\n", s32Ret);
		return -1;
	}

	return s32Ret;
}

int replay_sys_vi_init(daemon_pipe_cfg_t *pipe_cfg)
{
	raw_replay_cfg_t *replay_cfg = &pipe_cfg->raw_replay_cfg;
	VI_PIPE ViPipe = 0;
	VI_PIPE_ATTR_S stPipeAttr;
	CVI_S32 s32Ret = CVI_SUCCESS;

	s32Ret = replay_sys_init(replay_cfg,
				 pipe_cfg->video_pipe_cfg.buf_blk_cnt);
	if (s32Ret != CVI_SUCCESS) {
		SAMPLE_PRT("replay_sys_init failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = replay_set_mode_config(replay_cfg);
	if (s32Ret != CVI_SUCCESS) {
		SAMPLE_PRT("replay_set_mode_config failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = replay_trig_pic(replay_cfg);
	if (s32Ret != CVI_SUCCESS && replay_cfg->timing_enable) {
		SAMPLE_PRT("replay_trig_pic failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = replay_vi_start_dev(replay_cfg);
	if (s32Ret != CVI_SUCCESS) {
		SAMPLE_PRT("replay_vi_start_dev failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	stPipeAttr.bYuvSkip = CVI_FALSE;
	stPipeAttr.u32MaxW = replay_cfg->width;
	stPipeAttr.u32MaxH = replay_cfg->height;
	stPipeAttr.enPixFmt = PIXEL_FORMAT_RGB_BAYER_12BPP;
	stPipeAttr.enBitWidth = DATA_BITWIDTH_12;
	stPipeAttr.stFrameRate.s32SrcFrameRate = -1;
	stPipeAttr.stFrameRate.s32DstFrameRate = -1;
	stPipeAttr.bNrEn = CVI_TRUE;
	stPipeAttr.enCompressMode =
		get_compress_mode(replay_cfg->compress_mode);
	stPipeAttr.bYuvBypassPath = replay_cfg->pixel_format ? 1 : 0;
	s32Ret = CVI_VI_CreatePipe(ViPipe, &stPipeAttr);
	if (s32Ret != CVI_SUCCESS) {
		SAMPLE_PRT("CVI_VI_CreatePipe failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_StartPipe(ViPipe);
	if (s32Ret != CVI_SUCCESS) {
		SAMPLE_PRT("CVI_VI_StartPipe failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_GetPipeAttr(ViPipe, &stPipeAttr);
	if (s32Ret != CVI_SUCCESS) {
		SAMPLE_PRT("CVI_VI_GetPipeAttr failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = replay_createIsp(replay_cfg,
				  pipe_cfg->video_pipe_cfg.enable_teaisp_bnr);
	if (s32Ret != CVI_SUCCESS) {
		SAMPLE_PRT("VI_CreateIsp failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = replay_startViChn(replay_cfg);
	if (s32Ret != CVI_SUCCESS) {
		SAMPLE_PRT("VI_StartViChn failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	return 1;
}

int replay_sys_vi_deinit(daemon_pipe_cfg_t *pipe_cfg)
{
	int s32Ret = CVI_SUCCESS;
	VI_DEV ViDev = 0;
	VI_PIPE ViPipe = 0;
	VI_CHN chn = 0;

	UNUSED(pipe_cfg);

	SAMPLE_COMM_ISP_Stop(0);

	s32Ret = CVI_VI_DisableChn(ViPipe, chn);
	if (s32Ret != CVI_SUCCESS) {
		SAMPLE_PRT("CVI_VI_DisableChn failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_StopPipe(ViPipe);
	if (s32Ret != CVI_SUCCESS) {
		CVI_TRACE_LOG(CVI_DBG_ERR, "CVI_VI_StopPipe failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret = CVI_VI_DestroyPipe(ViPipe);
	if (s32Ret != CVI_SUCCESS) {
		CVI_TRACE_LOG(CVI_DBG_ERR, "CVI_VI_DestroyPipe failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	s32Ret  = CVI_VI_DisableDev(ViDev);
	if (s32Ret != CVI_SUCCESS) {
		CVI_TRACE_LOG(CVI_DBG_ERR, "CVI_VI_DisableDev failed with %#x!\n", s32Ret);
		return s32Ret;
	}

	CVI_VI_UnRegChnFlipMirrorCallBack(0, ViDev);
	CVI_VI_UnRegPmCallBack(ViDev);

	SAMPLE_COMM_SYS_Exit();

	return 0;
}
