
#define CLOG_TAG "pipe"

#include "daemon_module.h"
#include "daemon_pipe.h"
#include "cvi_isp.h"
#include "raw_replay_offline.h"

extern int g_main_loog_run;
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

int insert_teaisp_drc_module(struct module_pipe_t *pipe, daemon_pipe_cfg_t *p_cfg, int pipe_id, int pipe_chn)
{
	struct module_t module;

	memset(&module, 0, sizeof(struct module_t));

	module.name = "teaisp_drc";
	module.pipe_id = pipe_id;
	module.pipe_chn = pipe_chn;
	module.pipe_cfg = p_cfg;
	module.fun = teaisp_drc_fun;
	module_pipe_add(pipe, &module);

	module_vpss_cfg_t *vpss_cfg = (module_vpss_cfg_t *)calloc(1, sizeof(module_vpss_cfg_t));

	vpss_cfg->st_vpss_grp_attr.stFrameRate.s32SrcFrameRate = -1;
	vpss_cfg->st_vpss_grp_attr.stFrameRate.s32DstFrameRate = -1;
	vpss_cfg->st_vpss_grp_attr.enPixelFormat = PIXEL_FORMAT_RGB_888_PLANAR;
	vpss_cfg->st_vpss_grp_attr.u32MaxW = 0; // src width
	vpss_cfg->st_vpss_grp_attr.u32MaxH = 0; // src height

	vpss_cfg->st_vpss_chn_attr.u32Width = 0; // src width
	vpss_cfg->st_vpss_chn_attr.u32Height = 0; // src height
	vpss_cfg->st_vpss_chn_attr.enVideoFormat = VIDEO_FORMAT_LINEAR;
	vpss_cfg->st_vpss_chn_attr.enPixelFormat = VI_PIXEL_FORMAT;
	vpss_cfg->st_vpss_chn_attr.u32Depth = 1;
	vpss_cfg->st_vpss_chn_attr.bMirror = CVI_FALSE;
	vpss_cfg->st_vpss_chn_attr.bFlip = CVI_FALSE;
	vpss_cfg->st_vpss_chn_attr.stAspectRatio.enMode = ASPECT_RATIO_NONE;
	vpss_cfg->st_vpss_chn_attr.stNormalize.bEnable = CVI_FALSE;

	module.name = "vpss";
	module.pipe_id = pipe_id;
	module.pipe_chn = pipe_chn;
	module.pipe_cfg = p_cfg;
	module.private_cfg = vpss_cfg;
	module.fun = vpss_fun;
	module_pipe_add(pipe, &module);

	return 0;
}

int create_pipe(daemon_pipe_cfg_t *p_cfg)
{
	int ret = 0;
	struct module_t module;

	memset(&module, 0, sizeof(struct module_t));

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
		module.pipe_chn = i;
		module.pipe_cfg = &p_cfg[i];
		module.fun = video_src_fun;
		module_pipe_add(&pdaemon_pipe[i], &module);

		if (p_cfg[i].video_pipe_cfg.enable_teaisp_pq) {
			module.name = "teaisp_pq";
			module.pipe_id = i;
			module.pipe_chn = i;
			module.fun = teaisp_pq_fun;
			module_pipe_add(&pdaemon_pipe[i], &module);
		}

		if (p_cfg[i].video_pipe_cfg.enable_teaisp_drc) {
			insert_teaisp_drc_module(&pdaemon_pipe[i], &p_cfg[i], i, i);
		}

		if (p_cfg[i].video_pipe_cfg.enable_face_ae) {
			module.name = "face_ae";
			module.pipe_id = i;
			module.pipe_chn = i;
			module.fun = face_ae_fun;
			module_pipe_add(&pdaemon_pipe[i], &module);
		}

		if (p_cfg[i].video_pipe_cfg.enable_isp_info_osd) {
			module.name = "osd";
			module.pipe_id = i;
			module.pipe_chn = i;
			module.fun = osd_fun;
			module_pipe_add(&pdaemon_pipe[i], &module);
		}

		module.name = "venc";
		module.pipe_id = i;
		module.pipe_chn = i;
		module.fun = venc_fun;
		module_pipe_add(&pdaemon_pipe[i], &module);

		module.name = "rtsp";
		module.pipe_id = i;
		module.pipe_chn = i;
		module.fun = rtsp_fun;
		module_pipe_add(&pdaemon_pipe[i], &module);

		module_pipe_init(&pdaemon_pipe[i]);
		//sleep(1); // wait for frame ready
		//module_pipe_start(&pdaemon_pipe[i]);
	}

	if (p_cfg->raw_replay_enable) {
		if (start_raw_replay_offline_mode() == CVI_SUCCESS) {
			g_raw_replay_offline_mode = 1;
		}
	}

#define __WAIT_FRAME_MAX_CONT (30) // the bypass frame num by isp
	int wait_frame_cont = 0;

	do {
		if (g_main_loog_run == 0)
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

	return 0;
}

int destroy_pipe(daemon_pipe_cfg_t *p_cfg)
{
	if (g_raw_replay_offline_mode) {
		stop_raw_replay_offline_mode();
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
