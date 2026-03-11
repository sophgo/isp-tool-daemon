
#include <sys/prctl.h>

#define CLOG_OUTPUT_LVL CLOG_LVL_DEBUG
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
	int chn_id = thiz->pipe_id;
	module_venc_cfg_t *venc_cfg = (module_venc_cfg_t *)thiz->module_cfg;

	clog_i("chn_id: %d, width: %d, height: %d, codec: %s\n",
			chn_id, venc_cfg->width, venc_cfg->height, venc_cfg->codec);
	module_queue_init(&thiz->queue, VENC_QUEUE_SIZE);

	ret = module_venc_init(chn_id, thiz->module_cfg);
	if (ret != 0) {
		clog_a("module_venc_init: %d failed with %#x\n", chn_id, ret);
		return ret;
	}

	return 0;
}

static int deinit(struct module_t *thiz)
{
	int ret = 0;
	int chn_id = thiz->pipe_id;
	module_venc_cfg_t *venc_cfg = (module_venc_cfg_t *)thiz->module_cfg;

	clog_i("chn_id: %d, width: %d, height: %d, codec: %s\n",
			chn_id, venc_cfg->width, venc_cfg->height, venc_cfg->codec);
	ret = module_venc_deinit(chn_id);
	if (ret != CVI_SUCCESS) {
		clog_e("module_venc_deinit: %d failed with %#x\n", chn_id, ret);
	}

	if (thiz->module_cfg != NULL) {
		free(thiz->module_cfg);
		thiz->module_cfg = NULL;
	}

	if (thiz->module_ctx != NULL) {
		free(thiz->module_ctx);
		thiz->module_ctx = NULL;
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
	int chn = thiz->pipe_id;

	clog_i("run, chn_id: %d\n", chn);
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
	clog_i("chn_id: %d\n", thiz->pipe_id);
	thiz->thread_run = 1;
	pthread_create(&thiz->thread_id, NULL, worker, thiz);
	return 0;
}

static int stop(struct module_t *thiz)
{
	clog_i("chn_id: %d\n", thiz->pipe_id);
	thiz->thread_run = 0;
	pthread_join(thiz->thread_id, NULL);
	return 0;
}

static int get(struct module_t *thiz, void **data)
{
	int ret = 0;

	ret = module_queue_pop(&thiz->queue, data, DAEMON_TIMEOUT_MS);
	if (ret != 0) {
		clog_e("module_queue_pop failed with %#x\n", ret);
		return -1;
	}
	return 0;
}

static int put(struct module_t *thiz, void *data)
{
	CVI_VENC_ReleaseStream(thiz->pipe_id, (VENC_STREAM_S *)data);
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
