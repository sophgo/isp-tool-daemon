
#include <sys/prctl.h>

#define CLOG_OUTPUT_LVL CLOG_LVL_DEBUG
#define CLOG_TAG "video_src"

#include <dlfcn.h>
#include "daemon_base.h"
#include "daemon_module.h"
#include "daemon_cfg.h"
#include "daemon_utils.h"
#include "video_src_cfg.h"
#include "cvi_comm_vi.h"
#include "cvi_vi.h"
#include "cvi_isp.h"
#include "cvi_vpss.h"

// touch /tmp/dump_video_src
#define ENABLE_VIDEO_SRC_DUMP_DEBUG (1)
#define VIDEO_SRC_QUEUE_SIZE (1)

#ifndef CONFIG_DUAL_OS
#define ENABLE_TEAISP_BNR (1)
#endif

static uint8_t g_video_src_init_cnt;

#ifdef ENABLE_TEAISP_BNR
#define TEAISP_SO_LIB "libteaisp.so"
static void *teaisp_so_dl;
typedef CVI_S32 (*TEAISP_FUN)(VI_PIPE ViPipe, CVI_S32 param);
static TEAISP_FUN teaisp_init;
static TEAISP_FUN teaisp_bnr_set_driver_init;
static TEAISP_FUN teaisp_bnr_set_driver_deinit;

static int load_bnr_model(VI_PIPE ViPipe, char *model_path)
{
	FILE *fp = fopen(model_path, "r");

	if (fp == NULL) {
		clog_e("open model path failed, %s\n", model_path);
		return -1;
	}

	char line[1024];
	char *token;
	char *rest;

	TEAISP_BNR_MODEL_INFO_S stModelInfo;

	while (fgets(line, sizeof(line), fp) != NULL) {
		clog_i("load model, list, %s", line);

		rest = line;
		token = strtok_r(rest, " ", &rest);

		memset(&stModelInfo, 0, sizeof(TEAISP_BNR_MODEL_INFO_S));
		snprintf(stModelInfo.path, TEAISP_MODEL_PATH_LEN, "%s", token);

		clog_i("load model, path, %s\n", token);

		token = strtok_r(rest, " ", &rest);

		int iso = atoi(token);

		stModelInfo.enterISO = iso;
		stModelInfo.tolerance = iso * 10 / 100;

		clog_i("load model, iso, %d, %d\n", stModelInfo.enterISO,
		       stModelInfo.tolerance);
		CVI_TEAISP_BNR_SetModel(ViPipe, &stModelInfo);
	}

	fclose(fp);

	return 0;
}

static int init_teaisp_bnr(int pipe, daemon_pipe_cfg_t *p_cfg)
{
	if (teaisp_so_dl == NULL) {
		teaisp_so_dl = dlopen(TEAISP_SO_LIB, RTLD_LAZY);
		if (!teaisp_so_dl) {
			clog_e("dlopen %s fail: %s\n", TEAISP_SO_LIB,
			       dlerror());
			return -1;
		}

		dlerror();

		teaisp_init = (TEAISP_FUN)dlsym(teaisp_so_dl, "CVI_TEAISP_Init");
		if (!teaisp_init) {
			clog_e("dlsym CVI_TEAISP_Init fail: %s\n", dlerror());
			return -1;
		}
		teaisp_bnr_set_driver_init = (TEAISP_FUN)dlsym(teaisp_so_dl, "CVI_TEAISP_BNR_Set_Driver_Init");
		if (!teaisp_bnr_set_driver_init) {
			clog_e("dlsym CVI_TEAISP_BNR_Set_Driver_Init fail: %s\n", dlerror());
			return -1;
		}
		teaisp_bnr_set_driver_deinit = (TEAISP_FUN)dlsym(teaisp_so_dl, "CVI_TEAISP_BNR_Set_Driver_Deinit");
		if (!teaisp_bnr_set_driver_deinit) {
			clog_e("dlsym CVI_TEAISP_BNR_Set_Driver_Deinit fail: %s\n", dlerror());
			return -1;
		}
	}

	teaisp_init(pipe, p_cfg->max_use_tpu_num);
	return teaisp_bnr_set_driver_init(pipe, 0);
}

static int deinit_teaisp_bnr(int pipe)
{
	if (!teaisp_bnr_set_driver_deinit) {
		return -1;
	}
	if (teaisp_bnr_set_driver_deinit(pipe, 0) != 0) {
		clog_e("teaisp_bnr_set_driver_deinit failed\n");
		return -1;
	}
	if (g_video_src_init_cnt == 0) {
		if (teaisp_so_dl) {
			dlclose(teaisp_so_dl);
			teaisp_so_dl = NULL;
		}
	}
	return 0;
}
#endif

static int init(struct module_t *thiz)
{
	char bin_path[256] = {0};
	daemon_pipe_cfg_t *p_cfg = (daemon_pipe_cfg_t *)thiz->pipe_cfg;

	clog_i("pipe_id: %d, pipe_chn: %d\n", thiz->pipe_id, thiz->pipe_chn);
	module_queue_init(&thiz->queue, VIDEO_SRC_QUEUE_SIZE);

#ifdef ENABLE_TEAISP_BNR
	if (p_cfg->video_pipe_cfg.enable_teaisp_bnr) {
		if (init_teaisp_bnr(thiz->pipe_id, p_cfg) != 0) {
			clog_a("init_teaisp_bnr failed\n");
		}
	}
#endif

	if (g_video_src_init_cnt == 0) {
		int vi_num = 1;

		snprintf(bin_path, sizeof(bin_path), "%s/cvi_sdr_bin", p_cfg->cvi_bin_path);
		CVI_BIN_SetBinName(WDR_MODE_NONE, bin_path);
		snprintf(bin_path, sizeof(bin_path), "%s/cvi_wdr_bin", p_cfg->cvi_bin_path);
		CVI_BIN_SetBinName(WDR_MODE_2To1_LINE, bin_path);

		if (p_cfg->raw_replay_enable) {
			vi_num = replay_sys_vi_int(p_cfg);
		} else {
			vi_num = module_sys_vi_init(p_cfg);
		}

		if (vi_num < 0) {
			clog_e("sys vi init fail!\n");
			return -1;
		}

		if (p_cfg->dev_num > vi_num) {
			clog_e("ini dev num: %d less than json dev num: %d\n",
			       vi_num, p_cfg->dev_num);
			p_cfg->dev_num = vi_num;
		}
	}

#ifdef ENABLE_TEAISP_BNR
	if (p_cfg->video_pipe_cfg.enable_teaisp_bnr) {
		if (load_bnr_model(thiz->pipe_id, p_cfg->video_pipe_cfg.bnr_model_list) != 0) {
			clog_a("load_bnr_model failed\n");
		}
	}
#endif

	g_video_src_init_cnt++;
	return 0;
}

static int deinit(struct module_t *thiz)
{
	clog_i("pipe_id: %d, pipe_chn: %d\n", thiz->pipe_id, thiz->pipe_chn);
	g_video_src_init_cnt--;
	if (g_video_src_init_cnt == 0) {
		daemon_pipe_cfg_t *p_cfg = (daemon_pipe_cfg_t *)thiz->pipe_cfg;

		if (p_cfg->raw_replay_enable) {
			replay_sys_vi_deinit(p_cfg);
		} else {
			module_sys_vi_deinit(p_cfg);
		}
	}

#ifdef ENABLE_TEAISP_BNR
	deinit_teaisp_bnr(thiz->pipe_id);
#endif

	module_queue_deinit(&thiz->queue);
	return 0;
}

static int get_frame(module_t *thiz, VIDEO_FRAME_INFO_S *pframe)
{
	int ret = 0;

	ret = CVI_VPSS_GetChnFrame(thiz->pipe_id, 0, pframe,
				   DAEMON_TIMEOUT_MS);

	if (ret != CVI_SUCCESS) {
		clog_e("get chn frame failed with %#x\n", ret);
	}

	return ret;
}

static int put_frame(module_t *thiz, VIDEO_FRAME_INFO_S *pframe)
{
	int ret = 0;

	ret = CVI_VPSS_ReleaseChnFrame(thiz->pipe_id, 0, pframe);

	if (ret != CVI_SUCCESS) {
		clog_e("release chn frame failed with %#x\n", ret);
	}

	return ret;
}

static void *worker(void *arg)
{
	int ret = 0;
	struct module_t *thiz = (struct module_t *)arg;

	clog_i("run, pipe_id: %d, pipe_chn: %d\n", thiz->pipe_id,
	       thiz->pipe_chn);

	prctl(PR_SET_NAME, "video_src", 0, 0, 0);

	// for debug

	while (thiz->thread_run) {
		VIDEO_FRAME_INFO_S *pframe =
			calloc(1, sizeof(VIDEO_FRAME_INFO_S));
		if (pframe == NULL) {
			clog_e("calloc failed\n");
			return (void *)-1;
		}

		ret = get_frame(thiz, pframe);
		if (ret != CVI_SUCCESS) {
			clog_e("get vi chn frame failed with %#x\n", ret);
			free(pframe);
			continue;
		}

#ifdef ENABLE_VIDEO_SRC_DUMP_DEBUG
		if (access("/tmp/dump_video_src", F_OK) == 0) {
			char file_name[32];

			snprintf(file_name, sizeof(file_name),
				 "video_src_%d.yuv", thiz->pipe_chn);

			FILE *fp = fopen(file_name, "wb");

			dump_video_frame(fp, pframe);
			fflush(fp);
			fclose(fp);
			clog_i("dump video src frame, %s\n", file_name);
			system("sync;rm -f /tmp/dump_video_src");
		}

		ret = module_queue_push(&thiz->queue, pframe,
					DAEMON_TIMEOUT_MS);
		if (ret != 0) {
			clog_e("module_queue_push failed with %#x\n", ret);
			put_frame(thiz, pframe);
			free(pframe);
			continue;
		}
	}
#endif

	while (module_queue_size(&thiz->queue) > 0) {
		VIDEO_FRAME_INFO_S *pframe = NULL;

		module_queue_pop(&thiz->queue, (void **)&pframe,
				 DAEMON_TIMEOUT_MS);
		put_frame(thiz, pframe);
		free(pframe);
	}

	return NULL;
}

static int start(struct module_t *thiz)
{
	clog_i("pipe_id: %d, pipe_chn: %d\n", thiz->pipe_id, thiz->pipe_chn);
	thiz->thread_run = 1;
	pthread_create(&thiz->thread_id, NULL, worker, thiz);
	return 0;
}

static int stop(struct module_t *thiz)
{
	clog_i("pipe_id: %d, pipe_chn: %d\n", thiz->pipe_id, thiz->pipe_chn);
	thiz->thread_run = 0;
	pthread_join(thiz->thread_id, NULL);
	return 0;
}

static int get(struct module_t *thiz, void **data)
{
	int ret = 0;
	//clog_i("get, pipe_id: %d, pipe_chn: %d\n", thiz->pipe_id, thiz->pipe_chn);
	ret = module_queue_pop(&thiz->queue, data, DAEMON_TIMEOUT_MS);
	if (ret != 0) {
		clog_e("module_queue_pop failed with %#x\n", ret);
		return -1;
	}
	return 0;
}

static int put(struct module_t *thiz, void *data)
{
	//clog_i("put, pipe_id: %d, pipe_chn: %d\n", thiz->pipe_id, thiz->pipe_chn);
	put_frame(thiz, (VIDEO_FRAME_INFO_S *)data);
	free(data);
	return 0;
}

struct module_fun_t video_src_fun = {
	.init = init,
	.deinit = deinit,
	.start = start,
	.stop = stop,
	.get = get,
	.put = put,
};
