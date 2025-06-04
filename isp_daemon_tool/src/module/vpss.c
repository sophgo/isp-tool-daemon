
#include <sys/prctl.h>

#define CLOG_OUPUT_LVL CLOG_LVL_DEBUG
#define CLOG_TAG "vpss"

#include "daemon_base.h"
#include "daemon_cfg.h"
#include "daemon_module.h"

#define VPSS_QUEUE_SIZE (1)

static int init(struct module_t *thiz)
{
	int ret = 0;

	thiz->pipe_id = CVI_VPSS_GetAvailableGrp();
	if (thiz->pipe_id < 0) {
		clog_e("CVI_VPSS_GetAvailableGrp failed with %#x\n",
		       thiz->pipe_id);
		return thiz->pipe_id;
	}

	clog_i("pipe_id: %d, pipe_chn: %d\n", thiz->pipe_id, thiz->pipe_chn);
	module_queue_init(&thiz->queue, VPSS_QUEUE_SIZE);

	daemon_pipe_cfg_t *pipe_cfg = (daemon_pipe_cfg_t *)thiz->pipe_cfg;
	module_vpss_cfg_t *vpss_cfg = (module_vpss_cfg_t *)thiz->private_cfg;

	if (vpss_cfg->st_vpss_grp_attr.u32MaxW == 0 ||
	    vpss_cfg->st_vpss_grp_attr.u32MaxH == 0) {
		vpss_cfg->st_vpss_grp_attr.u32MaxW = pipe_cfg->src_width;
		vpss_cfg->st_vpss_grp_attr.u32MaxH = pipe_cfg->src_height;
	}

	ret = CVI_VPSS_CreateGrp(thiz->pipe_id, &vpss_cfg->st_vpss_grp_attr);
	if (ret != CVI_SUCCESS) {
		clog_e("CVI_VPSS_CreateGrp failed with %#x\n", ret);
		return ret;
	}

	if (vpss_cfg->st_vpss_chn_attr.u32Width == 0 ||
	    vpss_cfg->st_vpss_chn_attr.u32Height == 0) {
		vpss_cfg->st_vpss_chn_attr.u32Width = pipe_cfg->src_width;
		vpss_cfg->st_vpss_chn_attr.u32Height = pipe_cfg->src_height;
	}

	ret = CVI_VPSS_SetChnAttr(thiz->pipe_id, thiz->pipe_chn,
				  &vpss_cfg->st_vpss_chn_attr);
	if (ret != CVI_SUCCESS) {
		clog_e("CVI_VPSS_SetChnAttr failed with %#x\n", ret);
		return ret;
	}

	ret = CVI_VPSS_EnableChn(thiz->pipe_id, thiz->pipe_chn);
	if (ret != CVI_SUCCESS) {
		clog_e("CVI_VPSS_EnableChn failed with %#x\n", ret);
		return ret;
	}

	ret = CVI_VPSS_StartGrp(thiz->pipe_id);
	if (ret != CVI_SUCCESS) {
		clog_e("CVI_VPSS_StartGrp failed with %#x\n", ret);
		return ret;
	}

	ret = CVI_BIN_SetVpssGrpParams(thiz->pipe_id);
	if (ret != CVI_SUCCESS) {
		clog_e("CVI_BIN_SetVpssGrpParams failed with %#x\n", ret);
		return ret;
	}

	return ret;
}

static int deinit(struct module_t *thiz)
{
	int ret = 0;

	ret = CVI_VPSS_DisableChn(thiz->pipe_id, thiz->pipe_chn);
	if (ret != CVI_SUCCESS) {
		clog_e("CVI_VPSS_DisableChn failed with %#x\n", ret);
		return ret;
	}

	ret = CVI_VPSS_StopGrp(thiz->pipe_id);
	if (ret != CVI_SUCCESS) {
		clog_e("CVI_VPSS_StopGrp failed with %#x\n", ret);
		return ret;
	}

	ret = CVI_VPSS_DestroyGrp(thiz->pipe_id);
	if (ret != CVI_SUCCESS) {
		clog_e("CVI_VPSS_DestroyGrp failed with %#x\n", ret);
		return ret;
	}

	if (thiz->private_cfg != NULL) {
		free(thiz->private_cfg);
		thiz->private_cfg = NULL;
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

	clog_i("run, pipe_id: %d, pipe_chn: %d\n", thiz->pipe_id,
	       thiz->pipe_chn);

	prctl(PR_SET_NAME, "vpss", 0, 0, 0);

	VIDEO_FRAME_INFO_S *src_frame = NULL;
	VIDEO_FRAME_INFO_S *dst_frame = NULL;

	while (thiz->thread_run) {
		if (src_frame != NULL) {
			src_module->fun.put(src_module, src_frame);
			src_frame = NULL;
		}

		ret = src_module->fun.get(src_module, (void **)&src_frame);
		if (ret != 0) {
			clog_e("src module get fail...\n");
			continue;
		}

		ret = CVI_VPSS_SendFrame(thiz->pipe_id, src_frame,
					 DAEMON_TIMEOUT_MS);
		if (ret != CVI_SUCCESS) {
			clog_e("vpss grp %d, send frame fail...\n",
			       thiz->pipe_id);
			continue;
		}

		dst_frame = (VIDEO_FRAME_INFO_S *)calloc(
			1, sizeof(VIDEO_FRAME_INFO_S));
		if (dst_frame == NULL) {
			clog_e("calloc failed\n");
			continue;
		}

		ret = CVI_VPSS_GetChnFrame(thiz->pipe_id, thiz->pipe_chn,
					   dst_frame, DAEMON_TIMEOUT_MS);
		if (ret != CVI_SUCCESS) {
			clog_e("vpss grp %d, chn %d, get frame fail...\n",
			       thiz->pipe_id, thiz->pipe_chn);
			continue;
		}

		ret = module_queue_push(&thiz->queue, dst_frame,
					DAEMON_TIMEOUT_MS);
		if (ret != 0) {
			clog_e("module_queue_push failed with %#x\n", ret);
			CVI_VPSS_ReleaseChnFrame(thiz->pipe_id, thiz->pipe_chn,
						 dst_frame);
			continue;
		}
	}

	while (module_queue_size(&thiz->queue) > 0) {
		VIDEO_FRAME_INFO_S *dst_frame = NULL;

		module_queue_pop(&thiz->queue, (void **)&dst_frame,
				 DAEMON_TIMEOUT_MS);
		CVI_VPSS_ReleaseChnFrame(thiz->pipe_id, thiz->pipe_chn,
					 dst_frame);
		free(dst_frame);
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

	ret = module_queue_pop(&thiz->queue, data, DAEMON_TIMEOUT_MS);
	if (ret != 0) {
		clog_e("module_queue_pop failed with %#x\n", ret);
		return -1;
	}
	return 0;
}

static int put(struct module_t *thiz, void *data)
{
	int ret = 0;

	ret = CVI_VPSS_ReleaseChnFrame(thiz->pipe_id, thiz->pipe_chn,
				       (VIDEO_FRAME_INFO_S *)data);
	if (ret != CVI_SUCCESS) {
		clog_e("CVI_VPSS_ReleaseChnFrame failed with %#x\n", ret);
		return -1;
	}
	free(data);
	return 0;
}

struct module_fun_t vpss_fun = {
	.init = init,
	.deinit = deinit,
	.start = start,
	.stop = stop,
	.get = get,
	.put = put,
};
