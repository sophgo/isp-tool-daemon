#include <sys/prctl.h>

#define CLOG_OUTPUT_LVL CLOG_LVL_DEBUG
#define CLOG_TAG "sink"

#include "daemon_base.h"
#include "daemon_cfg.h"
#include "daemon_module.h"

/*
 * sink_module: A terminal module that drains frames from upstream.
 * Used when downstream modules (like RTSP) are disabled but upstream
 * modules (like VENC) still produce output that needs to be consumed.
 */

static int init(struct module_t *thiz)
{
	clog_i("pipe_id: %d\n", thiz->pipe_id);
	return 0;
}

static int deinit(struct module_t *thiz)
{
	clog_i("pipe_id: %d\n", thiz->pipe_id);

	if (thiz->module_cfg) {
		free(thiz->module_cfg);
		thiz->module_cfg = NULL;
	}

	if (thiz->module_ctx) {
		free(thiz->module_ctx);
		thiz->module_ctx = NULL;
	}
	return 0;
}

static void *worker(void *arg)
{
	int ret = 0;
	struct module_t *thiz = (struct module_t *)arg;
	struct module_t *src_module =
		&(GET_MODULE_PIPE_NODE_PTR(thiz)->prev->module);

	clog_i("run, pipe_id: %d\n", thiz->pipe_id);
	prctl(PR_SET_NAME, "sink", 0, 0, 0);

	void *data = NULL;

	while (thiz->thread_run) {
		ret = src_module->fun.get(src_module, &data);
		if (ret != 0) {
			/* timeout or error, just continue */
			continue;
		}

		if (data != NULL) {
			/* release the frame back to upstream */
			src_module->fun.put(src_module, data);
			data = NULL;
		}
	}

	return NULL;
}

static int start(struct module_t *thiz)
{
	clog_i("pipe_id: %d\n", thiz->pipe_id);
	thiz->thread_run = 1;
	pthread_create(&thiz->thread_id, NULL, worker, thiz);
	return 0;
}

static int stop(struct module_t *thiz)
{
	clog_i("pipe_id: %d\n", thiz->pipe_id);
	thiz->thread_run = 0;
	pthread_join(thiz->thread_id, NULL);
	return 0;
}

struct module_fun_t sink_module_fun = {
	.init = init,
	.deinit = deinit,
	.start = start,
	.stop = stop,
	.get = NULL,  /* terminal module, no downstream consumer */
	.put = NULL,
};
