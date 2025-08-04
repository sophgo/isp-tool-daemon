
#include <sys/prctl.h>

#define CLOG_OUTPUT_LVL CLOG_LVL_INFO
#define CLOG_TAG "rtsp3"

#include "daemon_base.h"
#include "daemon_cfg.h"
#include "daemon_module.h"
#include "cvi_isp.h"
#include "cvi_venc.h"
#include "rtsp_server.h"

static void *worker(void *arg);

static void rtsp_on_play(int id, void *arg)
{
	UNUSED(arg);
	clog_i("rtsp on play, id: %d\n", id);
}

static void rtsp_on_teardown(int id, void *arg)
{
	UNUSED(arg);
	clog_i("rtsp on teardown, id: %d\n", id);
}

static int init(struct module_t *thiz)
{
	daemon_pipe_cfg_t *pipe_cfg = (daemon_pipe_cfg_t *)thiz->pipe_cfg;

	clog_i("pipe_id: %d, pipe_chn: %d\n", thiz->pipe_id,
	       thiz->pipe_chn);

	rtsp_codec_type_e codec_type = RTSP_CODEC_H264;

	if (strcmp(pipe_cfg->video_pipe_cfg.codec, "264") == 0) {
		codec_type = RTSP_CODEC_H264;
	} else if (strcmp(pipe_cfg->video_pipe_cfg.codec, "265") == 0) {
		codec_type = RTSP_CODEC_H265;
	} else if (strcmp(pipe_cfg->video_pipe_cfg.codec, "mjpeg") == 0) {
		codec_type = RTSP_CODEC_MJPEG;
	} else {
		clog_e("codec: %s not support!\n",
		       pipe_cfg->video_pipe_cfg.codec);
		return -1;
	}

	cvi_rtsp_cfg_t rtsp_cfg;

	memset(&rtsp_cfg, 0, sizeof(cvi_rtsp_cfg_t));
	rtsp_cfg.video_info.height = pipe_cfg->src_height;
	rtsp_cfg.video_info.width = pipe_cfg->src_width;
	rtsp_cfg.video_info.codec_type = codec_type;
	rtsp_cfg.event_cb.play_arg = thiz;
	rtsp_cfg.event_cb.on_play = rtsp_on_play;
	rtsp_cfg.event_cb.teardown_arg = thiz;
	rtsp_cfg.event_cb.on_teardown = rtsp_on_teardown;

	if (cvi_rtsp_init(thiz->pipe_chn, &rtsp_cfg) != 0) {
		clog_e("cvi_rtsp_init: %d failed\n", thiz->pipe_chn);
		return -1;
	}

	return 0;
}

static int deinit(struct module_t *thiz)
{
	clog_i("pipe_id: %d, pipe_chn: %d\n", thiz->pipe_id,
	       thiz->pipe_chn);

	if (cvi_rtsp_deinit(thiz->pipe_chn) != 0) {
		clog_e("cvi_rtsp_deinit: %d failed\n", thiz->pipe_chn);
		return -1;
	}

	return 0;
}

static void *worker(void *arg)
{
	int ret = 0;
	struct module_t *thiz = (struct module_t *)arg;
	struct module_t *src_module =
		&(GET_MODULE_PIPE_NODE_PTR(thiz)->prev->module);

	clog_i("run, pipe_id: %d, pipe_chn: %d\n", thiz->pipe_id,
	       thiz->pipe_chn);

	prctl(PR_SET_NAME, "rtsp", 0, 0, 0);

	VENC_STREAM_S *pstream = NULL;
	VENC_PACK_S *ppack = NULL;
	cvi_rtsp_frame_t rtsp_frame;

	while (thiz->thread_run) {
		if (pstream != NULL) {
			src_module->fun.put(src_module, pstream);
			pstream = NULL;
		}

		ret = src_module->fun.get(src_module, (void **)&pstream);
		if (ret != 0) {
			clog_e("src module get fail...\n");
			continue;
		}

		for (CVI_U32 i = 0; i < pstream->u32PackCount; i++) {
			ppack = &pstream->pstPack[i];
			clog_d("frame[%d] type: %d, pts: %llu, len: %d\n", i,
				ppack->DataType, ppack->u64PTS, ppack->u32Len);
			rtsp_frame.data = ppack->pu8Addr + ppack->u32Offset;
			rtsp_frame.size = ppack->u32Len - ppack->u32Offset;
			rtsp_frame.ts = ppack->u64PTS;
			cvi_rtsp_send_frame(thiz->pipe_chn, &rtsp_frame);
		}
	}

	if (pstream != NULL) {
		src_module->fun.put(src_module, pstream);
		pstream = NULL;
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

struct module_fun_t cvi_rtsp3_fun = {
	.init = init,
	.deinit = deinit,
	.start = start,
	.stop = stop,
	.get = NULL,
	.put = NULL,
};
