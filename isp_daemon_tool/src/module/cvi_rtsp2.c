
#ifdef ENABLE_CVI_RTSP2
#include <sys/prctl.h>

#define CLOG_OUTPUT_LVL CLOG_LVL_DEBUG
#define CLOG_TAG "rtsp2"

#include "daemon_base.h"
#include "daemon_cfg.h"
#include "daemon_module.h"
#include "cvi_isp.h"
#include "cvi_venc.h"
#include "cvi_rtsp.h"

#define RTSP_USERNAME_STR "admin"
#define RTSP_PASSWORD_STR "admin123"

typedef struct {
	struct module_t *thiz;
	void *hdl;
	int ref_cnt;
	CVI_RTSP_INFO_S rtsp_info;
	CVI_RTSP_MEDIA_INFO_S media_info;
} cvi_rtsp_ctx_t;

static pthread_mutex_t rtsp_mutex;
#define RTSP_MAX_NUM (VI_MAX_PIPE_NUM)
static cvi_rtsp_ctx_t *prtsp_ctx[RTSP_MAX_NUM];

static void *worker(void *arg);

static void rtsp_service_start_media_by_name(char *name)
{
	if (name == NULL || strlen(name) <= 0) {
		return;
	}

	pthread_mutex_lock(&rtsp_mutex);
	for (int i = 0; i < RTSP_MAX_NUM; i++) {
		cvi_rtsp_ctx_t *c = prtsp_ctx[i];

		if (c) {
			if (strcmp(c->media_info.rtsp_name, name) == 0) {
				c->ref_cnt++;
				clog_i("session %s start play %d.\n", name, c->ref_cnt);
				break;
			}
		}
	}
	pthread_mutex_unlock(&rtsp_mutex);
}

static void rtsp_service_stop_media_by_name(char *name)
{
	if (name == NULL || strlen(name) <= 0) {
		return;
	}

	pthread_mutex_lock(&rtsp_mutex);
	for (int i = 0; i < RTSP_MAX_NUM; i++) {
		cvi_rtsp_ctx_t *c = prtsp_ctx[i];

		if (c) {
			if (strcmp(c->media_info.rtsp_name, name) == 0) {
				c->ref_cnt--;
				clog_i("session %s stop play %d.\n", name, c->ref_cnt);
				break;
			}
		}
	}
	pthread_mutex_unlock(&rtsp_mutex);
}

static void rtsp_service_event_cb(CVI_RTSP_EVENT_S *e)
{
	if (e) {
		switch (e->e) {
		case CVI_RTSP_EVENT_CLI_CONNECT: {
			clog_i("recv %s CONNECT %s Event.\n", e->rtsp_name, e->cli_ipaddr);
			rtsp_service_start_media_by_name(e->rtsp_name);
		} break;
		case CVI_RTSP_EVENT_CLI_DISCONNECT: {
			clog_i("recv %s DISCONNECT %s Event.\n", e->rtsp_name, e->cli_ipaddr);
			rtsp_service_stop_media_by_name(e->rtsp_name);
		} break;
		default:
			break;
		}
	}
}

static int init(struct module_t *thiz)
{
	daemon_pipe_cfg_t *pipe_cfg = (daemon_pipe_cfg_t *)thiz->pipe_cfg;

	clog_i("pipe_id: %d, pipe_chn: %d\n", thiz->pipe_id,
	       thiz->pipe_chn);

	cvi_rtsp_ctx_t *ctx = (cvi_rtsp_ctx_t *)calloc(1, sizeof(cvi_rtsp_ctx_t));

	if (ctx == NULL) {
		clog_e("calloc failed\n");
		return -1;
	}

	thiz->private_data = ctx;
	prtsp_ctx[thiz->pipe_chn] = ctx;
	prtsp_ctx[thiz->pipe_chn]->thiz = thiz;

	strncpy(ctx->rtsp_info.username, RTSP_USERNAME_STR,
		sizeof(ctx->rtsp_info.username));
	strncpy(ctx->rtsp_info.password, RTSP_PASSWORD_STR,
		sizeof(ctx->rtsp_info.password));
	ctx->rtsp_info.max_conn = RTSP_INSTANCE_NUM;
	ctx->rtsp_info.timeout = DAEMON_TIMEOUT_MS;
	ctx->rtsp_info.port = pipe_cfg->rtsp_port;

	ctx->media_info.id = thiz->pipe_chn;
	snprintf(ctx->media_info.rtsp_name, sizeof(ctx->media_info.rtsp_name),
		 "stream%d", thiz->pipe_chn);

	CVI_RTSP_VIDEO_FORMAT_E codec = CVI_RTSP_VIDEO_H264;

	if (strcmp(pipe_cfg->video_pipe_cfg.codec, "264") == 0) {
		codec = CVI_RTSP_VIDEO_H264;
	} else if (strcmp(pipe_cfg->video_pipe_cfg.codec, "265") == 0) {
		codec = CVI_RTSP_VIDEO_H265;
	} else if (strcmp(pipe_cfg->video_pipe_cfg.codec, "mjpeg") == 0) {
		codec = CVI_RTSP_VIDEO_MJPEG;
	} else {
		clog_e("codec: %s not support!\n",
		       pipe_cfg->video_pipe_cfg.codec);
		return -1;
	}
	ctx->media_info.video_codec = codec;
	ctx->media_info.bitrate_kbps =
		pipe_cfg->video_pipe_cfg.st_vc_cfg.st_rc_attr.BitRate * 2;
	ctx->media_info.framerate = 30.0;
	ctx->media_info.audio_channels = 1;
	ctx->media_info.audio_codec = CVI_RTSP_AUDIO_PCM;
	ctx->media_info.audio_sample_rate = 30 * 320;
	ctx->media_info.audio_pernum = 320;
	ctx->media_info.rtp_port = 10000;
	ctx->media_info.video_port = 20000;
	ctx->media_info.audio_port = 21000;
	ctx->media_info.cb = rtsp_service_event_cb;

	pthread_mutex_init(&rtsp_mutex, NULL);

	CVI_RTSP_Create(&ctx->hdl, &ctx->rtsp_info, &ctx->media_info);
	if (ctx->hdl == NULL) {
		pthread_mutex_destroy(&rtsp_mutex);
		clog_e("create rtsp server fail...\n");
		return -1;
	}

	clog_i("rtsp server created:\n\nrtsp://xxx.xxx.xxx.xxx:8554/%s\n\n", ctx->media_info.rtsp_name);

	return 0;
}

static int deinit(struct module_t *thiz)
{
	int ret = 0;

	clog_i("pipe_id: %d, pipe_chn: %d\n", thiz->pipe_id,
	       thiz->pipe_chn);

	cvi_rtsp_ctx_t *ctx = (cvi_rtsp_ctx_t *) thiz->private_data;

	if (ctx->hdl == NULL) {
		clog_e("rtsp server not created\n");
		return -1;
	}

	ret = CVI_RTSP_Destroy(ctx->hdl);
	if (ret != CVI_SUCCESS) {
		clog_e("CVI_RTSP_Destroy failed, ret = %d\n", ret);
	}

	free(thiz->private_data);
	thiz->private_data = NULL;
	pthread_mutex_destroy(&rtsp_mutex);

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

	int find_key_frame = 0;
	cvi_rtsp_ctx_t *ctx = (cvi_rtsp_ctx_t *)thiz->private_data;

	VENC_STREAM_S *pstream = NULL;
	VENC_PACK_S *ppack = NULL;
	CVI_RTSP_FRAME_S data;
	uint8_t audio_null_data[64] = {0};

	memset(audio_null_data, 0, sizeof(audio_null_data));

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

		if (ctx->ref_cnt <= 0) {
			find_key_frame = 0;
			continue;
		}

		if (pstream->u32PackCount >= MAX_RTSP_VIDEO_FRAME) {
			clog_e("out of max block count, %d\n",
			       pstream->u32PackCount);
			continue;
		}

		if (find_key_frame == 0) {
			for (CVI_U32 i = 0; i < pstream->u32PackCount; i++) {
				ppack = &pstream->pstPack[i];
				if (ctx->media_info.video_codec == CVI_RTSP_VIDEO_H264) {
					if (ppack->DataType.enH264EType > H264E_NALU_PSLICE) {
						find_key_frame = 1;
					} else {
						continue;
					}
				} else if (ctx->media_info.video_codec == CVI_RTSP_VIDEO_H265) {
					if (ppack->DataType.enH265EType > H265E_NALU_PSLICE) {
						find_key_frame = 1;
					} else {
						continue;
					}
				} else {
					find_key_frame = 1;
				}
			}
		}

		memset(&data, 0, sizeof(CVI_RTSP_FRAME_S));
		data.type = FRAME_TYPE_VIDEO;
		for (CVI_U32 i = 0; i < pstream->u32PackCount; i++) {
			data.iskey[i] = 1;
			ppack = &pstream->pstPack[i];
			data.data[i] = ppack->pu8Addr + ppack->u32Offset;
			data.len[i] = ppack->u32Len - ppack->u32Offset;
			data.vi_pts[i] = ppack->u64PTS;
		}

		ret = CVI_RTSP_SendFrame(ctx->hdl, &data);
		if (ret != CVI_SUCCESS) {
			clog_e("CVI_RTSP_WriteFrame video frame failed, ret = %d\n", ret);
		}

		memset(&data, 0, sizeof(CVI_RTSP_FRAME_S));
		data.type = FRAME_TYPE_AUDIO;
		data.iskey[0] = 1;
		data.data[0] = audio_null_data;
		data.len[0] = sizeof(audio_null_data);
		data.vi_pts[0] = pstream->pstPack[0].u64PTS;

		ret = CVI_RTSP_SendFrame(ctx->hdl, &data);
		if (ret != CVI_SUCCESS) {
			clog_e("CVI_RTSP_WriteFrame audio frame failed, ret = %d\n", ret);
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

struct module_fun_t cvi_rtsp2_fun = {
	.init = init,
	.deinit = deinit,
	.start = start,
	.stop = stop,
	.get = NULL,
	.put = NULL,
};
#endif // ENABLE_CVI_RTSP2
