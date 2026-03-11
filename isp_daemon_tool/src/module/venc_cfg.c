
#include "sample_comm.h"
#include "daemon_base.h"
#include "daemon_cfg.h"
#include "daemon_module.h"

static int init_chn_input_cfg(module_venc_cfg_t *cfg, chnInputCfg *pIc)
{
	if ((cfg->width % 32) != 0) {
		clog_e("error, venc width: %d must be aligned to 32...\n",
		       cfg->width);
		return -1;
	}

	pIc->width = cfg->width;
	pIc->height = cfg->height;
	strncpy(pIc->codec, cfg->codec, sizeof(pIc->codec));

	// coding param
	vc_coding_param_t *p_coding_param =
		&cfg->vc_cfg.st_coding_param;

	pIc->framerate = p_coding_param->FrmLostOpen;
	// p_coding_param->LostMode;
	pIc->frameLostBspThr = p_coding_param->FrmLostBpsThr;
	pIc->frameLostGap = p_coding_param->EncFrmGaps;
	pIc->u32IntraCost = p_coding_param->IntraCost;
	pIc->aspectRatioInfoPresentFlag =
		p_coding_param->aspectRatioInfoPresentFlag;
	pIc->overscanInfoPresentFlag = p_coding_param->overscanInfoPresentFlag;
	pIc->videoSignalTypePresentFlag =
		p_coding_param->videoSignalTypePresentFlag;
	pIc->videoFormat = p_coding_param->videoFormat;
	pIc->videoFullRangeFlag = p_coding_param->videoFullRangeFlag;
	pIc->colourDescriptionPresentFlag =
		p_coding_param->colourDescriptionPresentFlag;
	pIc->h264ChromaQpOffset = p_coding_param->ChromaQpOffset;
	pIc->h265CbQpOffset = p_coding_param->CbQpOffset;
	pIc->h265CrQpOffset = p_coding_param->CrQpOffset;

	// gop mode
	vc_gop_mode_t *p_gop_mode = &cfg->vc_cfg.st_gop_mode;

	pIc->gopMode = p_gop_mode->GopMode;
	pIc->s32IPQpDelta = p_gop_mode->IPQpDelta;
	pIc->bgInterval = p_gop_mode->BgInterval;
	// p_gop_mode->BgQpDelta;
	// p_gop_mode->ViQpDelta;

	// rc attr
	vc_rc_attr_t *p_rc_attr = &cfg->vc_cfg.st_rc_attr;

	pIc->rcMode = p_rc_attr->RcMode;
	pIc->gop = p_rc_attr->Gop;
	pIc->bVariFpsEn = p_rc_attr->VariableFPS;
	pIc->srcFramerate = p_rc_attr->SrcFrmRate;
	pIc->framerate = p_rc_attr->DstFrmRate;
	pIc->statTime = p_rc_attr->StatTime;
	pIc->bitrate = p_rc_attr->BitRate;
	pIc->maxbitrate = p_rc_attr->MaxBitrate;
	pIc->iqp = p_rc_attr->IQP;
	pIc->pqp = p_rc_attr->PQP;

	// rc param
	vc_rc_param_t *p_rc_param = &cfg->vc_cfg.st_rc_param;

	pIc->u32ThrdLv = p_rc_param->ThrdLv;
	pIc->firstFrmstartQp = p_rc_param->FirstFrameStartQp;
	pIc->initialDelay = p_rc_param->InitialDelay;
	pIc->maxQp = p_rc_param->MaxQp;
	pIc->minQp = p_rc_param->MinQp;
	pIc->maxIqp = p_rc_param->MaxIQp;
	pIc->minIqp = p_rc_param->MinIQp;
	pIc->s32ChangePos = p_rc_param->ChangePos;
	pIc->s32MinStillPercent = p_rc_param->MinStillPercent;
	pIc->u32MaxStillQP = p_rc_param->MaxStillQP;
	pIc->u32MotionSensitivity = p_rc_param->MotionSensitivity;
	pIc->s32AvbrPureStillThr = p_rc_param->PureStillThr;
	pIc->s32AvbrFrmLostOpen = p_rc_param->AvbrFrmLostOpen;
	pIc->s32AvbrFrmGap = p_rc_param->AvbrFrmGap;

	return 0;
}

PIC_SIZE_E MapSizeToPicSize(SIZE_S stSize)
{
	CVI_U32 width, height;

	width = stSize.u32Width;
	height = stSize.u32Height;

	if (width == 352 && height == 288) {
		return PIC_CIF;
	} else if (width == 720 && height == 576)
		return PIC_D1_PAL;
	else if (width == 720 && height == 480)
		return PIC_D1_NTSC;
	else if (width == 1280 && height == 720)
		return PIC_720P;
	else if (width == 1920 && height == 1080)
		return PIC_1080P;
	else if (width == 2592 && height == 1520)
		return PIC_2592x1520;
	else if (width == 2592 && height == 1536)
		return PIC_2592x1536;
	else if (width == 2592 && height == 1944)
		return PIC_2592x1944;
	else if (width == 2716 && height == 1524)
		return PIC_2716x1524;
	else if (width == 3840 && height == 2160)
		return PIC_3840x2160;
	else if (width == 4096 && height == 2160)
		return PIC_4096x2160;
	else if (width == 3000 && height == 3000)
		return PIC_3000x3000;
	else if (width == 4000 && height == 3000)
		return PIC_4000x3000;
	else if (width == 3840 && height == 8640)
		return PIC_3840x8640;
	else if (width == 640 && height == 480)
		return PIC_640x480;
	else if (width == 2688 && height == 1520)
		return PIC_2688x1520;
	else
		return PIC_CUSTOMIZE;
}

int module_venc_init(int chn_id, void *cfg)
{
	int ret = 0;
	chnInputCfg *pIc = (chnInputCfg *)malloc(sizeof(chnInputCfg));

	SAMPLE_COMM_VENC_InitChnInputCfg(pIc);
	ret = init_chn_input_cfg((module_venc_cfg_t *)cfg, pIc);
	if (ret != 0) {
		goto venc_init_fail;
	}

	VENC_GOP_ATTR_S gopAttr;
	VENC_GOP_MODE_E gopMode = (VENC_GOP_MODE_E)pIc->gopMode;

	memset(&gopAttr, 0, sizeof(VENC_GOP_ATTR_S));
	ret = SAMPLE_COMM_VENC_GetGopAttr(gopMode, &gopAttr);
	if (ret != CVI_SUCCESS) {
		clog_e("SAMPLE_COMM_VENC_GetGopAttr failed with %#x\n", ret);
		goto venc_init_fail;
	}

	PAYLOAD_TYPE_E EnPayLoad;

	if (!strcmp(pIc->codec, "mjp")) {
		EnPayLoad = PT_MJPEG;
	} else if (!strcmp(pIc->codec, "jpg")) {
		EnPayLoad = PT_JPEG;
	} else if (!strcmp(pIc->codec, "264")) {
		EnPayLoad = PT_H264;
	} else if (!strcmp(pIc->codec, "265")) {
		EnPayLoad = PT_H265;
	} else {
		clog_e("Unsupport Codec %s, only support mjp/jpg/h265/h264!\n",
		       pIc->codec);
		goto venc_init_fail;
	}

	SIZE_S stSize = { pIc->width, pIc->height };
	PIC_SIZE_E enSize = MapSizeToPicSize(stSize);
	CVI_U32 u32Profile = pIc->u32Profile;

	/* Set the pixelformat to NV21 in 182x */
	pIc->pixel_format = (SAMPLE_PIXEL_FORMAT == PIXEL_FORMAT_NV21) ? 3 : 0;
	pIc->bind_mode = VENC_BIND_DISABLE;

	commonInputCfg pCic;
	SAMPLE_RC_E enRcMode = (SAMPLE_RC_E)pIc->rcMode;

	SAMPLE_COMM_VENC_InitCommonInputCfg(&pCic);
	SAMPLE_COMM_VENC_SetModParam(&pCic);
	ret = SAMPLE_COMM_VENC_Start(pIc, chn_id, EnPayLoad, enSize, enRcMode,
				     u32Profile, CVI_FALSE, &gopAttr);
	if (ret != CVI_SUCCESS) {
		clog_e("SAMPLE_COMM_VENC_Start failed with %#x\n", ret);
		goto venc_init_fail;
	}

venc_init_fail:
	free(pIc);
	pIc = NULL;
	return ret == CVI_SUCCESS ? 0 : -1;
}

int module_venc_deinit(int chn_id)
{
	int ret = 0;

	ret = SAMPLE_COMM_VENC_Stop(chn_id);
	if (ret != CVI_SUCCESS) {
		clog_e("SAMPLE_COMM_VENC_Stop failed with %#x\n", ret);
		return -1;
	}

	return 0;
}
