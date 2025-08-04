
#define CLOG_TAG "pipe"

#include "daemon_module.h"
#include "daemon_pipe.h"
#include "cvi_isp.h"

extern int g_main_loog_run;
static struct module_pipe_t *pdaemon_pipe;

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

		if (p_cfg->is_fastboot_mode == 0) {
			module.name = "video_src";
			module.pipe_id = i;
			module.pipe_chn = i;
			module.pipe_cfg = &p_cfg[i];
			module.fun = video_src_fun;
			module_pipe_add(&pdaemon_pipe[i], &module);
		#ifdef ENABLE_TEAISP_PQ
			if (p_cfg[i].video_pipe_cfg.enable_teaisp_pq) {
				module.name = "teaisp_pq";
				module.pipe_id = i;
				module.pipe_chn = i;
				module.fun = teaisp_pq_fun;
				module_pipe_add(&pdaemon_pipe[i], &module);
			}
		#endif
		#ifdef ENABLE_FACE_AE
			if (p_cfg[i].video_pipe_cfg.enable_face_ae) {
				module.name = "face_ae";
				module.pipe_id = i;
				module.pipe_chn = i;
				module.fun = face_ae_fun;
				module_pipe_add(&pdaemon_pipe[i], &module);
			}
		#endif

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
		} else {
			module.name = "venc_fastboot";
			module.pipe_id = i;
			module.pipe_chn = i;
			module.pipe_cfg = &p_cfg[i];
			module.fun = venc_fun_fastboot;
			module_pipe_add(&pdaemon_pipe[i], &module);
		}

		module.name = "rtsp";
		module.pipe_id = i;
		module.pipe_chn = i;

		if (p_cfg[i].rtsp_server_select == 3) {
			module.fun = cvi_rtsp3_fun;
		} else {
#ifndef ENABLE_CVI_RTSP2
			module.fun = cvi_rtsp_fun;
#else
			module.fun = cvi_rtsp2_fun;
#endif
		}

		module_pipe_add(&pdaemon_pipe[i], &module);

		ret = module_pipe_init(&pdaemon_pipe[i]);

		if (ret != 0) {
			clog_e("craete pipe: %d fail!\n", i);
			return ret;
		}
		//sleep(1); // wait for frame ready
		//module_pipe_start(&pdaemon_pipe[i]);
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
