
#include <sys/prctl.h>

#define CLOG_OUPUT_LVL CLOG_LVL_DEBUG
#define CLOG_TAG "video_src"

#include <dlfcn.h>
#include "daemon_base.h"
#include "daemon_module.h"
#include "daemon_cfg.h"
#include "video_src_cfg.h"
#include "cvi_comm_vi.h"
#include "cvi_vi.h"
#include "cvi_isp.h"
#include "cvi_vpss.h"
#define VIDEO_SRC_QUEUE_SIZE (1)

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

typedef CVI_S32 (*TEAISP_INIT_FUN)(VI_PIPE ViPipe, CVI_S32 maxDev);

#define TEAISP_SO_LIB "libteaisp.so"
static void *teaisp_so_dl;
static TEAISP_INIT_FUN teaisp_init;

static int init_teaisp_bnr(int pipe, char *model_list)
{
	if (teaisp_so_dl == NULL) {
		teaisp_so_dl = dlopen(TEAISP_SO_LIB, RTLD_LAZY);
		if (!teaisp_so_dl) {
			clog_e("dlopen %s fail: %s\n", TEAISP_SO_LIB,
			       dlerror());
			return -1;
		}

		dlerror();

		teaisp_init =
			(TEAISP_INIT_FUN)dlsym(teaisp_so_dl, "CVI_TEAISP_Init");
		if (!teaisp_init) {
			clog_e("dlsym CVI_TEAISP_Init fail: %s\n", dlerror());
			return -1;
		}
	}

	teaisp_init(pipe, 1);
	return load_bnr_model(pipe, model_list);
}

static uint8_t g_video_src_init_cnt;

static int init(struct module_t *thiz)
{
	daemon_pipe_cfg_t *p_cfg = (daemon_pipe_cfg_t *)thiz->pipe_cfg;

	clog_i("pipe_id: %d, pipe_chn: %d\n", thiz->pipe_id, thiz->pipe_chn);
	module_queue_init(&thiz->queue, VIDEO_SRC_QUEUE_SIZE);
	if (g_video_src_init_cnt == 0) {
		int vi_num = 1;

		if (p_cfg->raw_replay_enable) {
			vi_num = replay_sys_vi_int(p_cfg);
		} else {
			vi_num = module_sys_vi_init(p_cfg);
		}

		if (p_cfg->dev_num > vi_num) {
			clog_e("ini dev num: %d less than json dev num: %d\n",
			       vi_num, p_cfg->dev_num);
			p_cfg->dev_num = vi_num;
		}
	}

	if (p_cfg->video_pipe_cfg.enable_teaisp_bnr) {
		if (init_teaisp_bnr(thiz->pipe_id,
				    p_cfg->video_pipe_cfg.bnr_model_list) !=
		    0) {
			clog_a("init_teaisp_bnr failed\n");
		}
	}

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

		if (teaisp_so_dl) {
			dlclose(teaisp_so_dl);
			teaisp_so_dl = NULL;
		}
	}
	module_queue_deinit(&thiz->queue);
	return 0;
}

static int get_frame(module_t *thiz, VIDEO_FRAME_INFO_S *pframe)
{
	int ret = 0;
	daemon_pipe_cfg_t *p_cfg = (daemon_pipe_cfg_t *)thiz->pipe_cfg;

	if (p_cfg->raw_replay_enable) {
		ret = CVI_VI_GetChnFrame(0, thiz->pipe_chn, pframe,
					 DAEMON_TIMEOUT_MS);
	} else {
		ret = CVI_VPSS_GetChnFrame(thiz->pipe_id, 0, pframe,
					   DAEMON_TIMEOUT_MS);
	}

	if (ret != CVI_SUCCESS) {
		clog_e("get chn frame failed with %#x\n", ret);
	}

	return ret;
}

static int put_frame(module_t *thiz, VIDEO_FRAME_INFO_S *pframe)
{
	int ret = 0;

	daemon_pipe_cfg_t *p_cfg = (daemon_pipe_cfg_t *)thiz->pipe_cfg;

	if (p_cfg->raw_replay_enable) {
		ret = CVI_VI_ReleaseChnFrame(0, thiz->pipe_chn, pframe);
	} else {
		ret = CVI_VPSS_ReleaseChnFrame(thiz->pipe_id, 0, pframe);
	}

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

		ret = module_queue_push(&thiz->queue, pframe,
					DAEMON_TIMEOUT_MS);
		if (ret != 0) {
			clog_e("module_queue_push failed with %#x\n", ret);
			put_frame(thiz, pframe);
			free(pframe);
			continue;
		}
	}

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
