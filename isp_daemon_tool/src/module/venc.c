
#include <sys/prctl.h>

#define CLOG_OUPUT_LVL CLOG_LVL_DEBUG
#define CLOG_TAG "venc"

#include "daemon_base.h"
#include "daemon_cfg.h"
#include "daemon_module.h"
#include "venc_cfg.h"
#include "cvi_isp.h"
#include "cvi_venc.h"

#define VENC_QUEUE_SIZE (3)

static int init(struct module_t *thiz)
{
	int ret = 0;

	clog_i("pipe_id: %d, pipe_chn: %d\n", thiz->pipe_id,
	       thiz->pipe_chn);
	module_queue_init(&thiz->queue, VENC_QUEUE_SIZE);

	daemon_pipe_cfg_t *pipe_cfg = (daemon_pipe_cfg_t *)thiz->pipe_cfg;
	int chn = thiz->pipe_chn;

	pipe_cfg->video_pipe_cfg.chn = chn;
	ret = module_venc_init(pipe_cfg);
	if (ret != 0) {
		clog_a("module_venc_init failed with %#x\n", ret);
		return ret;
	}

	return 0;
}

static int deinit(struct module_t *thiz)
{
	int ret = 0;

	clog_i("pipe_id: %d, pipe_chn: %d\n", thiz->pipe_id,
	       thiz->pipe_chn);

	ret = module_venc_deinit(thiz->pipe_cfg);
	if (ret != CVI_SUCCESS) {
		clog_e("module_venc_deinit failed with %#x\n", ret);
	}

	module_queue_deinit(&thiz->queue);
	return ret;
}

static void *worker(void *arg)
{
	int ret = 0;
	struct module_t *thiz = (struct module_t *)arg;
	struct module_t *src_module =
		&(GET_MODULE_PIPE_NODE_PTR(thiz)->prev->module);
	int chn = thiz->pipe_chn;

	clog_i("run, pipe_id: %d, pipe_chn: %d\n", thiz->pipe_id,
	       thiz->pipe_chn);

	prctl(PR_SET_NAME, "venc", 0, 0, 0);

	VENC_CHN_STATUS_S stStat;
	VIDEO_FRAME_INFO_S *pframe = NULL;

	while (thiz->thread_run) {
		if (pframe != NULL) {
			src_module->fun.put(src_module, pframe);
			pframe = NULL;
		}

		ret = src_module->fun.get(src_module, (void **)&pframe);
		if (ret != 0) {
			clog_e("src module get fail...\n");
			continue;
		}

		ret = CVI_VENC_SendFrame(chn, pframe, DAEMON_TIMEOUT_MS);
		if (ret != CVI_SUCCESS) {
			clog_e("venc chn %d, send frame fail...\n", chn);
			continue;
		}

		memset(&stStat, 0, sizeof(VENC_CHN_STATUS_S));
		ret = CVI_VENC_QueryStatus(chn, &stStat);
		if (ret != CVI_SUCCESS) {
			clog_e("venc chn: %d, query status fail...\n", chn);
			continue;
		}

		if (!stStat.u32CurPacks) {
			clog_e("venc chn: %d, u32CurPacks == 0, try again...\n",
			       chn);
			continue;
		}

		VENC_STREAM_S *pstStream =
			(VENC_STREAM_S *)calloc(1, sizeof(VENC_STREAM_S));
		if (pstStream == NULL) {
			clog_e("calloc fail...\n");
			continue;
		}

		pstStream->pstPack = (VENC_PACK_S *)calloc(stStat.u32CurPacks,
							   sizeof(VENC_PACK_S));
		if (pstStream->pstPack == NULL) {
			clog_e("calloc fail...\n");
			free(pstStream);
			continue;
		}

		ret = CVI_VENC_GetStream(chn, pstStream, DAEMON_TIMEOUT_MS);
		if (ret != CVI_SUCCESS) {
			clog_e("venc chn: %d, get stream fail...\n", chn);
			free(pstStream->pstPack);
			free(pstStream);
			continue;
		}

		ret = module_queue_push(&thiz->queue, pstStream,
					DAEMON_TIMEOUT_MS);
		if (ret != 0) {
			clog_e("module_queue_push failed with %#x\n", ret);
			CVI_VENC_ReleaseStream(chn, pstStream);
			free(pstStream->pstPack);
			free(pstStream);
			continue;
		}
	}

	if (pframe != NULL) {
		pframe->stVFrame.bSrcEnd = CVI_TRUE;
		ret = CVI_VENC_SendFrame(chn, pframe, DAEMON_TIMEOUT_MS);
		if (ret != CVI_SUCCESS) {
			clog_e("venc chn %d, send frame fail...\n", chn);
		}
		src_module->fun.put(src_module, pframe);
		pframe = NULL;
	}

	while (module_queue_size(&thiz->queue) > 0) {
		VENC_STREAM_S *pstStream = NULL;

		module_queue_pop(&thiz->queue, (void **)&pstStream,
				 DAEMON_TIMEOUT_MS);
		CVI_VENC_ReleaseStream(chn, pstStream);
		free(pstStream->pstPack);
		free(pstStream);
	}

	return NULL;
}

static int start(struct module_t *thiz)
{
	clog_i("pipe_id: %d, pipe_chn: %d\n", thiz->pipe_id,
	       thiz->pipe_chn);
	thiz->thread_run = 1;
	pthread_create(&thiz->thread_id, NULL, worker, thiz);
	return 0;
}

static int stop(struct module_t *thiz)
{
	clog_i("pipe_id: %d, pipe_chn: %d\n", thiz->pipe_id,
	       thiz->pipe_chn);
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
	CVI_VENC_ReleaseStream(thiz->pipe_chn, (VENC_STREAM_S *)data);
	free(((VENC_STREAM_S *)data)->pstPack);
	free(data);
	return 0;
}

struct module_fun_t venc_fun = {
	.init = init,
	.deinit = deinit,
	.start = start,
	.stop = stop,
	.get = get,
	.put = put,
};
