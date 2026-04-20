
#define CLOG_TAG "pipe"

#include "daemon_module.h"
#include "daemon_pipe.h"
#include "cvi_isp.h"
#include "raw_replay_offline.h"

#define TEAISP_VSR_REF_VIDEO_CHN (0)
#define TEAISP_VSR_SRC_VIDEO_CHN (1)
#define TEAISP_VSR_INPUT_WIDTH (480)
#define TEAISP_VSR_INPUT_HEIGHT (264)
#define TEAISP_VSR_OUTPUT_WIDTH (1920)
#define TEAISP_VSR_OUTPUT_HEIGHT (1056)
static module_t *g_teaisp_vsr_vpss_src_module;
static module_t *g_teaisp_vsr_vpss_scale_src_module;
static module_pipe_t g_teaisp_vsr_ref_pipe;
static module_pipe_t g_teaisp_vsr_pipe;
static module_pipe_t g_teaisp_vsr_vpss_scale_ref_pipe;

static uint8_t g_venc_chn_cnt;
static uint8_t g_rtsp_chn_cnt;
extern int g_main_loop_run;
static int g_raw_replay_offline_mode;
static struct module_pipe_t *pdaemon_pipe;

static int start_raw_replay_offline_mode(void)
{
	char *boardPath = getenv("REPLAY_FROM_BOARD_PATH");

	if (boardPath != NULL) {
		clog_i("Loading Raw Replay Path: %s\n", boardPath);
		if (raw_replay_offline_init(boardPath) != CVI_SUCCESS) {
			clog_i("raw_replay_offline_init failed!\n");
			raw_replay_offline_uninit();
			return CVI_FAILURE;
		}
		if (start_raw_replay_offline(0)) {
			clog_i("start_raw_replay_offline failed!\n");
			raw_replay_offline_uninit();
			return CVI_FAILURE;
		}
		clog_i("Start Raw Replay by Path: %s\n", boardPath);
	} else {
		return CVI_FAILURE;
	}

	return CVI_SUCCESS;
}

static int stop_raw_replay_offline_mode(void)
{
	raw_replay_offline_uninit();
	return CVI_SUCCESS;
}

static int insert_teaisp_drc_module(struct module_pipe_t *pipe, daemon_pipe_cfg_t *p_cfg, int pipe_id)
{
	struct module_t module;

	memset(&module, 0, sizeof(struct module_t));

	module_teaisp_drc_cfg_t *drc_cfg =
		(module_teaisp_drc_cfg_t *)calloc(1, sizeof(module_teaisp_drc_cfg_t));

	strncpy(drc_cfg->model_path, p_cfg->teaisp_drc_model_path, MAX_PATH_LEN - 1);

	module.name = "teaisp_drc";
	module.pipe_id = pipe_id;
	module.module_cfg = drc_cfg;
	module.fun = teaisp_drc_fun;
	module_pipe_add(pipe, &module);

	module_vpss_cfg_t *vpss_cfg = (module_vpss_cfg_t *)calloc(1, sizeof(module_vpss_cfg_t));

	vpss_cfg->grp_id = -1;
	vpss_cfg->chn_id = 0;
	vpss_cfg->chn_num = 1;
	vpss_cfg->enable_bypass_src_frame = 0;

	vpss_cfg->st_vpss_grp_attr.stFrameRate.s32SrcFrameRate = -1;
	vpss_cfg->st_vpss_grp_attr.stFrameRate.s32DstFrameRate = -1;
	vpss_cfg->st_vpss_grp_attr.enPixelFormat = PIXEL_FORMAT_RGB_888_PLANAR;
	vpss_cfg->st_vpss_grp_attr.u32MaxW = p_cfg->src_width;
	vpss_cfg->st_vpss_grp_attr.u32MaxH = p_cfg->src_height;

	vpss_cfg->st_vpss_chn_attr[0].u32Width = p_cfg->src_width;
	vpss_cfg->st_vpss_chn_attr[0].u32Height = p_cfg->src_height;
	vpss_cfg->st_vpss_chn_attr[0].enVideoFormat = VIDEO_FORMAT_LINEAR;
	vpss_cfg->st_vpss_chn_attr[0].enPixelFormat = VI_PIXEL_FORMAT;
	vpss_cfg->st_vpss_chn_attr[0].u32Depth = 1;
	vpss_cfg->st_vpss_chn_attr[0].bMirror = CVI_FALSE;
	vpss_cfg->st_vpss_chn_attr[0].bFlip = CVI_FALSE;
	vpss_cfg->st_vpss_chn_attr[0].stAspectRatio.enMode = ASPECT_RATIO_NONE;
	vpss_cfg->st_vpss_chn_attr[0].stNormalize.bEnable = CVI_FALSE;

	module.name = "vpss";
	module.pipe_id = pipe_id;
	module.module_cfg = vpss_cfg;
	module.fun = vpss_fun;
	module_pipe_add(pipe, &module);

	return 0;
}

static int insert_vpss_module_for_teaisp_vsr(struct module_pipe_t *pipe, daemon_pipe_cfg_t *p_cfg, int pipe_id)
{
	struct module_t module;
	module_vpss_cfg_t *vpss_cfg = (module_vpss_cfg_t *)calloc(1, sizeof(module_vpss_cfg_t));

	vpss_cfg->grp_id = -1;
	vpss_cfg->chn_id = 0;
	vpss_cfg->chn_num = 2;
	vpss_cfg->enable_bypass_src_frame = 1;

	vpss_cfg->st_vpss_grp_attr.stFrameRate.s32SrcFrameRate = -1;
	vpss_cfg->st_vpss_grp_attr.stFrameRate.s32DstFrameRate = -1;
	vpss_cfg->st_vpss_grp_attr.enPixelFormat = VI_PIXEL_FORMAT;
	vpss_cfg->st_vpss_grp_attr.u32MaxW = p_cfg->src_width;
	vpss_cfg->st_vpss_grp_attr.u32MaxH = p_cfg->src_height;

	int vpss_chn = TEAISP_VSR_REF_VIDEO_CHN;

	// for ref video
	vpss_cfg->chn_vb_cnt[vpss_chn] = 2;
	vpss_cfg->st_vpss_chn_attr[vpss_chn].u32Width = TEAISP_VSR_OUTPUT_WIDTH;
	vpss_cfg->st_vpss_chn_attr[vpss_chn].u32Height = TEAISP_VSR_OUTPUT_HEIGHT;
	vpss_cfg->st_vpss_chn_attr[vpss_chn].enVideoFormat = VIDEO_FORMAT_LINEAR;
	vpss_cfg->st_vpss_chn_attr[vpss_chn].enPixelFormat = VI_PIXEL_FORMAT;
	vpss_cfg->st_vpss_chn_attr[vpss_chn].u32Depth = 1;
	vpss_cfg->st_vpss_chn_attr[vpss_chn].bMirror = CVI_FALSE;
	vpss_cfg->st_vpss_chn_attr[vpss_chn].bFlip = CVI_FALSE;
	vpss_cfg->st_vpss_chn_attr[vpss_chn].stAspectRatio.enMode = ASPECT_RATIO_NONE;
	vpss_cfg->st_vpss_chn_attr[vpss_chn].stNormalize.bEnable = CVI_FALSE;

	vpss_chn = TEAISP_VSR_SRC_VIDEO_CHN;
	// for teaisp_vsr input
	vpss_cfg->chn_vb_cnt[vpss_chn] = 2;
	vpss_cfg->st_vpss_chn_attr[vpss_chn].u32Width = TEAISP_VSR_INPUT_WIDTH;
	vpss_cfg->st_vpss_chn_attr[vpss_chn].u32Height = TEAISP_VSR_INPUT_HEIGHT;
	vpss_cfg->st_vpss_chn_attr[vpss_chn].enVideoFormat = VIDEO_FORMAT_LINEAR;
	vpss_cfg->st_vpss_chn_attr[vpss_chn].enPixelFormat = PIXEL_FORMAT_RGB_888_PLANAR;
	vpss_cfg->st_vpss_chn_attr[vpss_chn].u32Depth = 1;
	vpss_cfg->st_vpss_chn_attr[vpss_chn].bMirror = CVI_FALSE;
	vpss_cfg->st_vpss_chn_attr[vpss_chn].bFlip = CVI_FALSE;
	vpss_cfg->st_vpss_chn_attr[vpss_chn].stAspectRatio.enMode = ASPECT_RATIO_NONE;
	vpss_cfg->st_vpss_chn_attr[vpss_chn].stNormalize.bEnable = CVI_FALSE;

	memset(&module, 0, sizeof(struct module_t));

	module.name = "vpss";
	module.pipe_id = pipe_id;
	module.module_cfg = vpss_cfg;
	module.fun = vpss_fun;
	g_teaisp_vsr_vpss_src_module = module_pipe_add(pipe, &module);

	return 0;
}

static int create_teaisp_vsr_ref_video_pipe(daemon_pipe_cfg_t *p_cfg)
{
	struct module_t module;
	module_vpss_cfg_t *vpss_cfg = (module_vpss_cfg_t *)g_teaisp_vsr_vpss_src_module->module_cfg;
	module_vpss_chn_cfg_t *vpss_chn_cfg = (module_vpss_chn_cfg_t *)calloc(1, sizeof(module_vpss_chn_cfg_t));

	memset(&module, 0, sizeof(struct module_t));
	memset(&g_teaisp_vsr_ref_pipe, 0, sizeof(module_pipe_t));
	g_teaisp_vsr_ref_pipe.pipe_cfg = p_cfg; // use private cfg is better

	vpss_chn_cfg->src_grp_id = vpss_cfg->grp_id;
	vpss_chn_cfg->chn_id = TEAISP_VSR_REF_VIDEO_CHN;
	module.name = "vpss_chn";
	module.module_cfg = vpss_chn_cfg;
	module.fun = vpss_chn_fun;
	module_pipe_add(&g_teaisp_vsr_ref_pipe, &module);

	module_venc_cfg_t *venc_cfg = (module_venc_cfg_t *)calloc(1, sizeof(module_venc_cfg_t));

	venc_cfg->width = vpss_cfg->st_vpss_chn_attr[TEAISP_VSR_REF_VIDEO_CHN].u32Width;
	venc_cfg->height = vpss_cfg->st_vpss_chn_attr[TEAISP_VSR_REF_VIDEO_CHN].u32Height;
	venc_cfg->pixel_format = VI_PIXEL_FORMAT;
	snprintf(venc_cfg->codec, MAX_CODEC_LEN, "%s", p_cfg->video_pipe_cfg.codec);
	venc_cfg->vc_cfg = p_cfg->video_pipe_cfg.st_vc_cfg;

	module.name = "venc";
	module.pipe_id = g_venc_chn_cnt++;
	module.module_cfg = venc_cfg;
	module.fun = venc_fun;
	module_pipe_add(&g_teaisp_vsr_ref_pipe, &module);

	module_rtsp_cfg_t *rtsp_cfg = (module_rtsp_cfg_t *)calloc(1, sizeof(module_rtsp_cfg_t));

	rtsp_cfg->rtsp_port = p_cfg->rtsp_port;
	rtsp_cfg->max_buf_size = p_cfg->rtsp_max_buf_size;
	rtsp_cfg->bitrate = venc_cfg->vc_cfg.st_rc_attr.BitRate;
	snprintf(rtsp_cfg->codec, MAX_CODEC_LEN, "%s", venc_cfg->codec);

	module.name = "rtsp";
	module.pipe_id = g_rtsp_chn_cnt++;
	module.module_cfg = rtsp_cfg;
	module.fun = rtsp_fun;
	module_pipe_add(&g_teaisp_vsr_ref_pipe, &module);

	module_pipe_init(&g_teaisp_vsr_ref_pipe);
	return 0;
}

static int destroy_teaisp_vsr_ref_video_pipe(void)
{
	module_pipe_stop(&g_teaisp_vsr_ref_pipe);
	module_pipe_deinit(&g_teaisp_vsr_ref_pipe);
	module_pipe_destroy(&g_teaisp_vsr_ref_pipe);
	return 0;
}

static int create_teaisp_vsr_video_pipe(daemon_pipe_cfg_t *p_cfg)
{
	struct module_t module;
	module_vpss_cfg_t *src_vpss_cfg = (module_vpss_cfg_t *)g_teaisp_vsr_vpss_src_module->module_cfg;
	module_vpss_chn_cfg_t *vpss_chn_cfg = (module_vpss_chn_cfg_t *)calloc(1, sizeof(module_vpss_chn_cfg_t));

	memset(&module, 0, sizeof(struct module_t));
	memset(&g_teaisp_vsr_pipe, 0, sizeof(module_pipe_t));
	g_teaisp_vsr_pipe.pipe_cfg = p_cfg; // use private cfg is better

	vpss_chn_cfg->src_grp_id = src_vpss_cfg->grp_id;
	vpss_chn_cfg->chn_id = TEAISP_VSR_SRC_VIDEO_CHN;
	module.name = "vpss_chn";
	module.module_cfg = vpss_chn_cfg;
	module.fun = vpss_chn_fun;
	module_pipe_add(&g_teaisp_vsr_pipe, &module);

	module_vpss_cfg_t *vsr_vpss_scale_cfg = (module_vpss_cfg_t *)calloc(1, sizeof(module_vpss_cfg_t));

	vsr_vpss_scale_cfg->grp_id = -1;
	vsr_vpss_scale_cfg->chn_id = 0;
	vsr_vpss_scale_cfg->chn_num = 1;
	vsr_vpss_scale_cfg->enable_bypass_src_frame = 1;
	vsr_vpss_scale_cfg->st_vpss_grp_attr.stFrameRate.s32SrcFrameRate = -1;
	vsr_vpss_scale_cfg->st_vpss_grp_attr.stFrameRate.s32DstFrameRate = -1;
	vsr_vpss_scale_cfg->st_vpss_grp_attr.enPixelFormat = PIXEL_FORMAT_RGB_888_PLANAR;
	vsr_vpss_scale_cfg->st_vpss_grp_attr.u32MaxW = TEAISP_VSR_INPUT_WIDTH;
	vsr_vpss_scale_cfg->st_vpss_grp_attr.u32MaxH = TEAISP_VSR_INPUT_HEIGHT;

	vsr_vpss_scale_cfg->chn_vb_cnt[0] = 2;
	vsr_vpss_scale_cfg->st_vpss_chn_attr[0].u32Width = TEAISP_VSR_OUTPUT_WIDTH;
	vsr_vpss_scale_cfg->st_vpss_chn_attr[0].u32Height = TEAISP_VSR_OUTPUT_HEIGHT;
	vsr_vpss_scale_cfg->st_vpss_chn_attr[0].enVideoFormat = VIDEO_FORMAT_LINEAR;
	vsr_vpss_scale_cfg->st_vpss_chn_attr[0].enPixelFormat = VI_PIXEL_FORMAT;
	vsr_vpss_scale_cfg->st_vpss_chn_attr[0].u32Depth = 1;
	vsr_vpss_scale_cfg->st_vpss_chn_attr[0].bMirror = CVI_FALSE;
	vsr_vpss_scale_cfg->st_vpss_chn_attr[0].bFlip = CVI_FALSE;
	vsr_vpss_scale_cfg->st_vpss_chn_attr[0].stAspectRatio.enMode = ASPECT_RATIO_NONE;
	vsr_vpss_scale_cfg->st_vpss_chn_attr[0].stNormalize.bEnable = CVI_FALSE;

	module.name = "vpss_scale";
	module.pipe_id = 0;
	module.module_cfg = vsr_vpss_scale_cfg;
	module.fun = vpss_fun;
	g_teaisp_vsr_vpss_scale_src_module = module_pipe_add(&g_teaisp_vsr_pipe, &module);

	module_teaisp_vsr_cfg_t *vsr_cfg = (module_teaisp_vsr_cfg_t *)calloc(1, sizeof(module_teaisp_vsr_cfg_t));

	snprintf(vsr_cfg->model_path, MAX_PATH_LEN, "%s", p_cfg->teaisp_vsr_model_path);
	module.name = "teaisp_vsr";
	module.pipe_id = 0;
	module.module_cfg = vsr_cfg;
	module.fun = teaisp_vsr_fun;
	module_pipe_add(&g_teaisp_vsr_pipe, &module);

	// rgb -> yuv
	module_vpss_cfg_t *vsr_out_vpss_cfg = (module_vpss_cfg_t *)calloc(1, sizeof(module_vpss_cfg_t));

	vsr_out_vpss_cfg->grp_id = -1;
	vsr_out_vpss_cfg->chn_id = 0;
	vsr_out_vpss_cfg->chn_num = 1;
	vsr_out_vpss_cfg->enable_bypass_src_frame = 0;

	vsr_out_vpss_cfg->st_vpss_grp_attr.stFrameRate.s32SrcFrameRate = -1;
	vsr_out_vpss_cfg->st_vpss_grp_attr.stFrameRate.s32DstFrameRate = -1;
	vsr_out_vpss_cfg->st_vpss_grp_attr.enPixelFormat = PIXEL_FORMAT_RGB_888_PLANAR;
	vsr_out_vpss_cfg->st_vpss_grp_attr.u32MaxW = TEAISP_VSR_OUTPUT_WIDTH;
	vsr_out_vpss_cfg->st_vpss_grp_attr.u32MaxH = TEAISP_VSR_OUTPUT_HEIGHT;

	vsr_out_vpss_cfg->chn_vb_cnt[0] = 2;
	vsr_out_vpss_cfg->st_vpss_chn_attr[0].u32Width = TEAISP_VSR_OUTPUT_WIDTH;
	vsr_out_vpss_cfg->st_vpss_chn_attr[0].u32Height = TEAISP_VSR_OUTPUT_HEIGHT;
	vsr_out_vpss_cfg->st_vpss_chn_attr[0].enVideoFormat = VIDEO_FORMAT_LINEAR;
	vsr_out_vpss_cfg->st_vpss_chn_attr[0].enPixelFormat = VI_PIXEL_FORMAT;
	vsr_out_vpss_cfg->st_vpss_chn_attr[0].u32Depth = 1;
	vsr_out_vpss_cfg->st_vpss_chn_attr[0].bMirror = CVI_FALSE;
	vsr_out_vpss_cfg->st_vpss_chn_attr[0].bFlip = CVI_FALSE;
	vsr_out_vpss_cfg->st_vpss_chn_attr[0].stAspectRatio.enMode = ASPECT_RATIO_NONE;
	vsr_out_vpss_cfg->st_vpss_chn_attr[0].stNormalize.bEnable = CVI_FALSE;

	module.name = "vpss";
	module.pipe_id = 0;
	module.module_cfg = vsr_out_vpss_cfg;
	module.fun = vpss_fun;
	module_pipe_add(&g_teaisp_vsr_pipe, &module);

	module_venc_cfg_t *venc_cfg = (module_venc_cfg_t *)calloc(1, sizeof(module_venc_cfg_t));

	venc_cfg->width = vsr_out_vpss_cfg->st_vpss_chn_attr[0].u32Width;
	venc_cfg->height = vsr_out_vpss_cfg->st_vpss_chn_attr[0].u32Height;
	venc_cfg->pixel_format = VI_PIXEL_FORMAT;
	snprintf(venc_cfg->codec, MAX_CODEC_LEN, "%s", p_cfg->video_pipe_cfg.codec);
	venc_cfg->vc_cfg = p_cfg->video_pipe_cfg.st_vc_cfg;

	module.name = "venc";
	module.pipe_id = g_venc_chn_cnt++;
	module.module_cfg = venc_cfg;
	module.fun = venc_fun;
	module_pipe_add(&g_teaisp_vsr_pipe, &module);

	module_rtsp_cfg_t *rtsp_cfg = (module_rtsp_cfg_t *)calloc(1, sizeof(module_rtsp_cfg_t));

	rtsp_cfg->rtsp_port = p_cfg->rtsp_port;
	rtsp_cfg->max_buf_size = p_cfg->rtsp_max_buf_size;
	rtsp_cfg->bitrate = venc_cfg->vc_cfg.st_rc_attr.BitRate;
	snprintf(rtsp_cfg->codec, MAX_CODEC_LEN, "%s", venc_cfg->codec);

	module.name = "rtsp";
	module.pipe_id = g_rtsp_chn_cnt++;
	module.module_cfg = rtsp_cfg;
	module.fun = rtsp_fun;
	module_pipe_add(&g_teaisp_vsr_pipe, &module);

	module_pipe_init(&g_teaisp_vsr_pipe);
	return 0;
}

static int destroy_teaisp_vsr_video_pipe(void)
{
	// teaisp_vsr video pipe
	module_pipe_stop(&g_teaisp_vsr_pipe);
	module_pipe_deinit(&g_teaisp_vsr_pipe);
	module_pipe_destroy(&g_teaisp_vsr_pipe);
	return 0;
}

static int create_teaisp_vsr_vpss_scale_ref_pipe(daemon_pipe_cfg_t *p_cfg)
{
	struct module_t module;
	module_vpss_cfg_t *vpss_cfg = (module_vpss_cfg_t *)g_teaisp_vsr_vpss_scale_src_module->module_cfg;
	module_vpss_chn_cfg_t *vpss_chn_cfg = (module_vpss_chn_cfg_t *)calloc(1, sizeof(module_vpss_chn_cfg_t));

	memset(&module, 0, sizeof(struct module_t));
	memset(&g_teaisp_vsr_vpss_scale_ref_pipe, 0, sizeof(module_pipe_t));
	g_teaisp_vsr_vpss_scale_ref_pipe.pipe_cfg = p_cfg; // use private cfg is better

	vpss_chn_cfg->src_grp_id = vpss_cfg->grp_id;
	vpss_chn_cfg->chn_id = 0;
	module.name = "vpss_chn";
	module.module_cfg = vpss_chn_cfg;
	module.fun = vpss_chn_fun;
	module_pipe_add(&g_teaisp_vsr_vpss_scale_ref_pipe, &module);

	module_venc_cfg_t *venc_cfg = (module_venc_cfg_t *)calloc(1, sizeof(module_venc_cfg_t));

	venc_cfg->width = vpss_cfg->st_vpss_chn_attr[0].u32Width;
	venc_cfg->height = vpss_cfg->st_vpss_chn_attr[0].u32Height;
	venc_cfg->pixel_format = VI_PIXEL_FORMAT;
	snprintf(venc_cfg->codec, MAX_CODEC_LEN, "%s", p_cfg->video_pipe_cfg.codec);
	venc_cfg->vc_cfg = p_cfg->video_pipe_cfg.st_vc_cfg;

	module.name = "venc";
	module.pipe_id = g_venc_chn_cnt++;
	module.module_cfg = venc_cfg;
	module.fun = venc_fun;
	module_pipe_add(&g_teaisp_vsr_vpss_scale_ref_pipe, &module);

	module_rtsp_cfg_t *rtsp_cfg = (module_rtsp_cfg_t *)calloc(1, sizeof(module_rtsp_cfg_t));

	rtsp_cfg->rtsp_port = p_cfg->rtsp_port;
	rtsp_cfg->max_buf_size = p_cfg->rtsp_max_buf_size;
	rtsp_cfg->bitrate = venc_cfg->vc_cfg.st_rc_attr.BitRate;
	snprintf(rtsp_cfg->codec, MAX_CODEC_LEN, "%s", venc_cfg->codec);

	module.name = "rtsp";
	module.pipe_id = g_rtsp_chn_cnt++;
	module.module_cfg = rtsp_cfg;
	module.fun = rtsp_fun;
	module_pipe_add(&g_teaisp_vsr_vpss_scale_ref_pipe, &module);

	module_pipe_init(&g_teaisp_vsr_vpss_scale_ref_pipe);
	return 0;
}

static int destroy_teaisp_vsr_vpss_scale_ref_pipe(void)
{
	module_pipe_stop(&g_teaisp_vsr_vpss_scale_ref_pipe);
	module_pipe_deinit(&g_teaisp_vsr_vpss_scale_ref_pipe);
	module_pipe_destroy(&g_teaisp_vsr_vpss_scale_ref_pipe);
	return 0;
}

int create_pipe(daemon_pipe_cfg_t *p_cfg)
{
	int ret = 0;
	struct module_t module;

	memset(&module, 0, sizeof(struct module_t));

	g_venc_chn_cnt = 0;
	g_rtsp_chn_cnt = 0;

	if (p_cfg->raw_replay_enable) {
		p_cfg->dev_num = 1;
	}

	pdaemon_pipe = (struct module_pipe_t *)calloc(
		p_cfg->dev_num, sizeof(struct module_pipe_t));
	for (int i = 0; i < p_cfg->dev_num; i++) {
		clog_i("create pipe: %d, %d\n", i, p_cfg[i].video_pipe_cfg.chn);
		pdaemon_pipe[i].pipe_cfg = &p_cfg[i];

		module.name = "video_src";
		module.pipe_id = i;
		module.module_cfg = &p_cfg[i];
		module.fun = video_src_fun;
		module_pipe_add(&pdaemon_pipe[i], &module);

#ifdef ENABLE_TEAISP_PQ
		if (p_cfg[i].video_pipe_cfg.enable_teaisp_pq) {
			module_teaisp_pq_cfg_t *pq_cfg =
				(module_teaisp_pq_cfg_t *)calloc(1, sizeof(module_teaisp_pq_cfg_t));

			snprintf(pq_cfg->model_path, MAX_PATH_LEN, "%s", p_cfg[i].teaisp_pq_model_path);
			module.name = "teaisp_pq";
			module.pipe_id = i;
			module.module_cfg = pq_cfg;
			module.fun = teaisp_pq_fun;
			module_pipe_add(&pdaemon_pipe[i], &module);
		}
#endif

		if (p_cfg[i].video_pipe_cfg.enable_teaisp_drc) {
			insert_teaisp_drc_module(&pdaemon_pipe[i], &p_cfg[i], i);
		}

		if (p_cfg[i].video_pipe_cfg.enable_teaisp_vsr) {
			insert_vpss_module_for_teaisp_vsr(&pdaemon_pipe[i], &p_cfg[i], i);
		}

#ifdef ENABLE_FACE_AE
		if (p_cfg[i].video_pipe_cfg.enable_face_ae) {
			module_face_ae_cfg_t *face_ae_cfg =
				(module_face_ae_cfg_t *)calloc(1, sizeof(module_face_ae_cfg_t));

			snprintf(face_ae_cfg->model_path, MAX_PATH_LEN, "%s", p_cfg[i].teaisp_faceae_model_path);
			module.name = "face_ae";
			module.pipe_id = i;
			module.module_cfg = face_ae_cfg;
			module.fun = face_ae_fun;
			module_pipe_add(&pdaemon_pipe[i], &module);
		}
#endif

		if (p_cfg[i].video_pipe_cfg.enable_isp_info_osd) {
			module.name = "osd";
			module.pipe_id = i;
			module.fun = osd_fun;
			module_pipe_add(&pdaemon_pipe[i], &module);
		}

		module_venc_cfg_t *venc_cfg = (module_venc_cfg_t *)calloc(1, sizeof(module_venc_cfg_t));

		venc_cfg->width = p_cfg[i].src_width;
		venc_cfg->height = p_cfg[i].src_height;
		venc_cfg->pixel_format = VI_PIXEL_FORMAT;
		snprintf(venc_cfg->codec, MAX_CODEC_LEN, "%s", p_cfg[i].video_pipe_cfg.codec);
		venc_cfg->vc_cfg = p_cfg[i].video_pipe_cfg.st_vc_cfg;

		module.name = "venc";
		module.pipe_id = g_venc_chn_cnt++;
		module.module_cfg = venc_cfg;
		module.fun = venc_fun;
		module_pipe_add(&pdaemon_pipe[i], &module);

		module_rtsp_cfg_t *rtsp_cfg = (module_rtsp_cfg_t *)calloc(1, sizeof(module_rtsp_cfg_t));

		rtsp_cfg->rtsp_port = p_cfg[i].rtsp_port;
		rtsp_cfg->max_buf_size = p_cfg[i].rtsp_max_buf_size;
		rtsp_cfg->bitrate = p_cfg[i].video_pipe_cfg.bitrate;
		snprintf(rtsp_cfg->codec, MAX_CODEC_LEN, "%s", p_cfg[i].video_pipe_cfg.codec);

		module.name = "rtsp";
		module.pipe_id = g_rtsp_chn_cnt++;
		module.module_cfg = rtsp_cfg;
		module.fun = rtsp_fun;
		module_pipe_add(&pdaemon_pipe[i], &module);

		module_pipe_init(&pdaemon_pipe[i]);
		//sleep(1); // wait for frame ready
		//module_pipe_start(&pdaemon_pipe[i]);
	}

	// only support pipe 0 for teaisp_vsr now
	if (p_cfg->video_pipe_cfg.enable_teaisp_vsr) {
		create_teaisp_vsr_ref_video_pipe(p_cfg);
		create_teaisp_vsr_video_pipe(p_cfg);
		create_teaisp_vsr_vpss_scale_ref_pipe(p_cfg);
	}

	if (p_cfg->raw_replay_enable) {
		if (start_raw_replay_offline_mode() == CVI_SUCCESS) {
			g_raw_replay_offline_mode = 1;
		}
	}

#define __WAIT_FRAME_MAX_CONT (30) // the bypass frame num by isp
	int wait_frame_cont = 0;

	do {
		if (g_main_loop_run == 0)
			break;
		ret = CVI_ISP_GetVDTimeOut(0, ISP_VD_BE_END,
					   DAEMON_TIMEOUT_MS * 2);
		if (ret == 0) {
			wait_frame_cont++;
		} else {
			clog_w("wait vi working timeout, go on wait...\n");
		}
	} while (wait_frame_cont < __WAIT_FRAME_MAX_CONT);

	for (int i = 0; i < p_cfg->dev_num; i++) {
		module_pipe_start(&pdaemon_pipe[i]);
	}

	// only support pipe 0 for teaisp_vsr now
	if (p_cfg->video_pipe_cfg.enable_teaisp_vsr) {
		module_pipe_start(&g_teaisp_vsr_ref_pipe);
		module_pipe_start(&g_teaisp_vsr_pipe);
		module_pipe_start(&g_teaisp_vsr_vpss_scale_ref_pipe);
	}

	return 0;
}

int destroy_pipe(daemon_pipe_cfg_t *p_cfg)
{
	if (g_raw_replay_offline_mode) {
		stop_raw_replay_offline_mode();
	}

	// only support pipe 0 for teaisp_vsr now
	if (p_cfg->video_pipe_cfg.enable_teaisp_vsr) {
		destroy_teaisp_vsr_vpss_scale_ref_pipe();
		destroy_teaisp_vsr_video_pipe();
		destroy_teaisp_vsr_ref_video_pipe();
	}

	for (int i = 0; i < p_cfg->dev_num; i++) {
		clog_i("destroy pipe: %d\n", i);
		module_pipe_stop(&pdaemon_pipe[i]);
		module_pipe_deinit(&pdaemon_pipe[i]);
		module_pipe_destroy(&pdaemon_pipe[i]);
	}

	free(pdaemon_pipe);
	pdaemon_pipe = NULL;

	return 0;
}
