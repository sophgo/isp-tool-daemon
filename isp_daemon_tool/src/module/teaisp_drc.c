#include <math.h>
#include <sys/prctl.h>

#define CLOG_OUTPUT_LVL CLOG_LVL_DEBUG
#define CLOG_TAG "aidrc"

#include "daemon_base.h"
#include "daemon_cfg.h"
#include "daemon_module.h"

#include "bmruntime_interface.h"
#include "cvi_isp.h"
#include "cvi_sys.h"
#include "cvi_vb.h"

#define TEAISP_DRC_QUEUE_SIZE (1)

#define DRC_IN_IMG (0)
#define DRC_IN_EMA (1)
#define DRC_IN_COEFF (2)
#define DRC_IN_NUM (3)

#define DRC_OUT_IMG (0)
#define DRC_OUT_EMA (1)
#define DRC_OUT_NUM (2)

typedef struct {
	void *p_bmrt;
	const char **net_names;
	bm_tensor_t *input_tensors;
	bm_tensor_t *output_tensors;
	void **input_vaddr;
	int input_num;
	int output_num;
	/*-----------------------------------*/
	pthread_mutex_t param_lock;
	float drc_param[TEAISP_DRC_PARAM_LENGHT];
} teaisp_drc_ctx_t;

typedef struct {
	VIDEO_FRAME_INFO_S frame;
	int is_from_src;
} teaisp_drc_data_t;

static int init_cnt;
static bm_handle_t bm_handle;
static teaisp_drc_ctx_t *pdrc_ctx[VI_MAX_PIPE_NUM];

static void teaisp_drc_dump_input(teaisp_drc_ctx_t *ctx, int pipe)
{
	void *addr_tmp = NULL;
	int size = 0;
	FILE *fp = NULL;
	char path[128] = { 0 };

	snprintf(path, sizeof(path), "/tmp/drc_input%d_img.bin", pipe);
	size = ctx->input_tensors[DRC_IN_IMG].device_mem.size;
	addr_tmp = CVI_SYS_MmapCache(
		ctx->input_tensors[DRC_IN_IMG].device_mem.u.device.device_addr,
		size);
	fp = fopen(path, "wb");
	fwrite(addr_tmp, size, 1, fp);
	fclose(fp);
	CVI_SYS_Munmap(addr_tmp, size);

	snprintf(path, sizeof(path), "/tmp/drc_input%d_ema.bin", pipe);
	size = ctx->input_tensors[DRC_IN_EMA].device_mem.size;
	addr_tmp = CVI_SYS_MmapCache(
		ctx->input_tensors[DRC_IN_EMA].device_mem.u.device.device_addr,
		size);
	fp = fopen(path, "wb");
	fwrite(addr_tmp, size, 1, fp);
	fclose(fp);
	CVI_SYS_Munmap(addr_tmp, size);

	snprintf(path, sizeof(path), "/tmp/drc_input%d_coeff.bin", pipe);
	size = ctx->input_tensors[DRC_IN_COEFF].device_mem.size;
	addr_tmp = CVI_SYS_MmapCache(
		ctx->input_tensors[DRC_IN_COEFF].device_mem.u.device.device_addr,
		size);
	fp = fopen(path, "wb");
	fwrite(addr_tmp, size, 1, fp);
	fclose(fp);
	CVI_SYS_Munmap(addr_tmp, size);

	printf("Successfully written input_tensors to files!\n");
}

static void teaisp_drc_dump_output(teaisp_drc_ctx_t *ctx, int pipe)
{
	void *addr_tmp = NULL;
	int size = 0;
	FILE *fp = NULL;
	char path[128] = { 0 };

	snprintf(path, sizeof(path), "/tmp/drc_output%d_img.bin", pipe);
	size = ctx->output_tensors[DRC_OUT_IMG].device_mem.size;
	addr_tmp = CVI_SYS_MmapCache(
		ctx->output_tensors[DRC_OUT_IMG].device_mem.u.device.device_addr,
		size);
	fp = fopen(path, "wb");
	fwrite(addr_tmp, size, 1, fp);
	fclose(fp);
	CVI_SYS_Munmap(addr_tmp, size);

	snprintf(path, sizeof(path), "/tmp/drc_output%d_ema.bin", pipe);
	size = ctx->output_tensors[DRC_OUT_EMA].device_mem.size;
	addr_tmp = CVI_SYS_MmapCache(
		ctx->output_tensors[DRC_OUT_EMA].device_mem.u.device.device_addr,
		size);
	fp = fopen(path, "wb");
	fwrite(addr_tmp, size, 1, fp);
	fclose(fp);
	CVI_SYS_Munmap(addr_tmp, size);

	printf("Successfully written output_tensors to files!\n");
}

static int teaisp_drc_unload_model(teaisp_drc_ctx_t *ctx)
{
	pthread_mutex_destroy(&ctx->param_lock);

	for (int i = 0; i < ctx->input_num; i++) {
		if (i == DRC_IN_IMG) {
			continue;
		}

		if (ctx->input_vaddr && ctx->input_vaddr[i]) {
			bm_mem_unmap_device_mem(
				bm_handle, ctx->input_vaddr[i],
				(int)ctx->input_tensors[i].device_mem.size);
			ctx->input_vaddr[i] = NULL;
		}

		if (ctx->input_tensors) {
			if (ctx->input_tensors[i]
				    .device_mem.u.device.device_addr != 0) {
				bm_free_device(
					bm_handle,
					ctx->input_tensors[i].device_mem);
			}
		}
	}

	for (int i = 0; i < ctx->output_num; i++) {
		if (i == DRC_OUT_IMG) {
			continue;
		}

		if (ctx->output_tensors) {
			if (ctx->output_tensors[i]
				    .device_mem.u.device.device_addr != 0) {
				bm_free_device(
					bm_handle,
					ctx->output_tensors[i].device_mem);
			}
		}
	}

	if (ctx->input_vaddr) {
		free(ctx->input_vaddr);
		ctx->input_vaddr = NULL;
	}

	if (ctx->input_tensors) {
		free(ctx->input_tensors);
		ctx->input_tensors = NULL;
	}

	if (ctx->output_tensors) {
		free(ctx->output_tensors);
		ctx->output_tensors = NULL;
	}

	if (ctx->net_names) {
		free(ctx->net_names);
		ctx->net_names = NULL;
	}

	if (ctx->p_bmrt) {
		bmrt_destroy(ctx->p_bmrt);
		ctx->p_bmrt = NULL;
	}

	return 0;
}

static int teaisp_drc_load_model(teaisp_drc_ctx_t *ctx, const char *path)
{
	bm_status_t status = BM_SUCCESS;
	const bm_net_info_t *net_info = NULL;

	pthread_mutex_init(&ctx->param_lock, NULL);

	ctx->p_bmrt = bmrt_create(bm_handle);
	if (ctx->p_bmrt == NULL) {
		clog_e("[AIDRC] bmrt create fail\n");
		goto load_model_fail;
	}

	if (!bmrt_load_bmodel(ctx->p_bmrt, path)) {
		clog_e("[AIDRC] load bmodel fail, %s\n", path);
		goto load_model_fail;
	}

	bmrt_get_network_names(ctx->p_bmrt, &ctx->net_names);

	net_info = bmrt_get_network_info(ctx->p_bmrt, ctx->net_names[0]);

	clog_i("[AIDRC] net name: %s, in: %d, out: %d\n", ctx->net_names[0],
	       net_info->input_num, net_info->output_num);

	ctx->input_num = net_info->input_num;
	ctx->output_num = net_info->output_num;

	if (ctx->input_num != DRC_IN_NUM || ctx->output_num != DRC_OUT_NUM) {
		clog_e("model param num not match!!!! in: %d, %d, out: %d, %d\n",
		       ctx->input_num, DRC_IN_NUM, ctx->output_num,
		       DRC_OUT_NUM);
		goto load_model_fail;
	}

	ctx->input_tensors =
		(bm_tensor_t *)calloc(ctx->input_num, sizeof(bm_tensor_t));
	if (ctx->input_tensors == NULL) {
		clog_e("[AIDRC] calloc fail, %ld\n",
		       ctx->input_num * sizeof(bm_tensor_t));
		goto load_model_fail;
	}

	ctx->input_vaddr = (void **)calloc(ctx->input_num, sizeof(void *));
	if (ctx->input_vaddr == NULL) {
		clog_e("[AIDRC] calloc fail, %ld\n",
		       ctx->input_num * sizeof(void *));
		goto load_model_fail;
	}

	ctx->output_tensors =
		(bm_tensor_t *)calloc(ctx->output_num, sizeof(bm_tensor_t));
	if (ctx->output_tensors == NULL) {
		clog_e("[AIDRC] calloc fail, %ld\n",
		       ctx->output_num * sizeof(bm_tensor_t));
		goto load_model_fail;
	}

	// input
	for (int i = 0; i < ctx->input_num; i++) {
		ctx->input_tensors[i].dtype = net_info->input_dtypes[i];
		ctx->input_tensors[i].shape =
			net_info->stages[0].input_shapes[i];
		ctx->input_tensors[i].st_mode = BM_STORE_1N;

		if (i == DRC_IN_IMG) {
			memset(&ctx->input_tensors[i].device_mem, 0,
			       sizeof(bm_device_mem_t));
			ctx->input_tensors[i].device_mem.size =
				net_info->max_input_bytes[i];
		} else {
			status = bm_malloc_device_byte(
				bm_handle, &ctx->input_tensors[i].device_mem,
				net_info->max_input_bytes[i]);
			if (status != BM_SUCCESS) {
				goto load_model_fail;
			}

			unsigned long long vmem;

			bm_mem_mmap_device_mem_no_cache(
				bm_handle, &ctx->input_tensors[i].device_mem,
				&vmem);

			memset((void *)vmem, 0, net_info->max_input_bytes[i]);

			ctx->input_vaddr[i] = (void *)vmem;
		}

		clog_i("[AIDRC] in: %d, dtype: %d, shape: %dx%dx%dx%d, %d, 0x%lx, size: %d\n",
		       i, ctx->input_tensors[i].dtype,
		       ctx->input_tensors[i].shape.dims[0],
		       ctx->input_tensors[i].shape.dims[1],
		       ctx->input_tensors[i].shape.dims[2],
		       ctx->input_tensors[i].shape.dims[3],
		       ctx->input_tensors[i].shape.num_dims,
		       ctx->input_tensors[i].device_mem.u.device.device_addr,
		       (int)net_info->max_input_bytes[i]);
	}

	// output
	for (int i = 0; i < ctx->output_num; i++) {
		ctx->output_tensors[i].dtype = net_info->output_dtypes[i];
		ctx->output_tensors[i].shape =
			net_info->stages[0].output_shapes[i];
		ctx->output_tensors[i].st_mode = BM_STORE_1N;

		if (i == DRC_OUT_IMG) {
			memset(&ctx->output_tensors[i].device_mem, 0,
			       sizeof(bm_device_mem_t));
			ctx->output_tensors[i].device_mem.size =
				net_info->max_output_bytes[i];
		} else {
			status = bm_malloc_device_byte(
				bm_handle, &ctx->output_tensors[i].device_mem,
				net_info->max_output_bytes[i]);
			if (status != BM_SUCCESS) {
				goto load_model_fail;
			}

			unsigned long long vmem;

			bm_mem_mmap_device_mem(
				bm_handle, &ctx->output_tensors[i].device_mem,
				&vmem);

			memset((void *)vmem, 0, net_info->max_output_bytes[i]);

			bm_mem_flush_device_mem(
				bm_handle, &ctx->output_tensors[i].device_mem);
			bm_mem_unmap_device_mem(
				bm_handle, (void *)vmem,
				(int)net_info->max_output_bytes[i]);
		}

		clog_i("[AIDRC] out: %d, dtype: %d, shape: %dx%dx%dx%d, %d, 0x%lx, size: %d\n",
		       i, ctx->output_tensors[i].dtype,
		       ctx->output_tensors[i].shape.dims[0],
		       ctx->output_tensors[i].shape.dims[1],
		       ctx->output_tensors[i].shape.dims[2],
		       ctx->output_tensors[i].shape.dims[3],
		       ctx->output_tensors[i].shape.num_dims,
		       ctx->output_tensors[i].device_mem.u.device.device_addr,
		       (int)net_info->max_output_bytes[i]);
	}

	return 0;

load_model_fail:

	teaisp_drc_unload_model(ctx);

	return -1;
}

static int teaisp_drc_param_update_callback(int pipe, void *param)
{
	teaisp_drc_ctx_t *ctx = pdrc_ctx[pipe];

	if (ctx == NULL) {
		clog_e("ctx is NULL\n");
		return -1;
	}

	pthread_mutex_lock(&ctx->param_lock);
	memcpy(ctx->drc_param, param, sizeof(float) * TEAISP_DRC_PARAM_LENGHT);
	pthread_mutex_unlock(&ctx->param_lock);

	return 0;
}

static int teaisp_drc_get_vb(teaisp_drc_ctx_t *ctx, uint64_t *vb_phy_addr)
{
	VB_BLK vb_blk = CVI_VB_GetBlock(
		VB_INVALID_POOLID,
		ctx->output_tensors[DRC_OUT_IMG].device_mem.size);
	if (vb_blk == VB_INVALID_HANDLE) {
		clog_e("get vb_blk failed, size: %d\n",
		       ctx->output_tensors[DRC_OUT_IMG].device_mem.size);
		return -1;
	}
	*vb_phy_addr = CVI_VB_Handle2PhysAddr(vb_blk);
	return 0;
}

static int teaisp_drc_put_vb(uint64_t vb_phy_addr)
{
	VB_BLK vb_blk = CVI_VB_PhysAddr2Handle(vb_phy_addr);

	if (vb_blk == VB_INVALID_HANDLE || vb_blk == 0x00) {
		clog_e("vb_phy_addr is invalid, vb_phy_addr: %#lx, vb_blk: %#lx\n",
		       vb_phy_addr, vb_blk);
		return -1;
	}
	CVI_VB_ReleaseBlock(vb_blk);
	return 0;
}

static int init(struct module_t *thiz)
{
	int ret = 0;

	clog_i("pipe_id: %d\n", thiz->pipe_id);
	module_queue_init(&thiz->queue, TEAISP_DRC_QUEUE_SIZE);

	module_teaisp_drc_cfg_t *drc_cfg =
		(module_teaisp_drc_cfg_t *)thiz->module_cfg;

	if (init_cnt == 0 && bm_handle == NULL) {
		ret = bm_dev_request(&bm_handle, 0);
		if (ret != BM_SUCCESS) {
			clog_e("bm_dev_request failed with %d\n", ret);
			return ret;
		}
	}

	init_cnt++;

	teaisp_drc_ctx_t *ctx =
		(teaisp_drc_ctx_t *)calloc(1, sizeof(teaisp_drc_ctx_t));
	if (ctx == NULL) {
		clog_e("calloc failed\n");
		return -1;
	}

	thiz->module_ctx = ctx;
	pdrc_ctx[thiz->pipe_id] = ctx;

	CVI_TEAISP_DRC_RegParamUpdateCallback(thiz->pipe_id,
					      teaisp_drc_param_update_callback);

	if (teaisp_drc_load_model(ctx, drc_cfg->model_path) < 0) {
		clog_e("teaisp_drc_load_model: %s failed\n", drc_cfg->model_path);
		return -1;
	}

	return 0;
}

static int deinit(struct module_t *thiz)
{
	teaisp_drc_ctx_t *ctx = (teaisp_drc_ctx_t *)thiz->module_ctx;

	teaisp_drc_unload_model(ctx);
	pdrc_ctx[thiz->pipe_id] = NULL;

	init_cnt--;

	if (init_cnt == 0) {
		bm_dev_free(bm_handle);
		bm_handle = NULL;
	}

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
	bm_status_t status = BM_SUCCESS;
	struct module_t *thiz = (struct module_t *)arg;
	struct module_t *src_module =
		&(GET_MODULE_PIPE_NODE_PTR(thiz)->prev->module);

	int is_first_frame = 1;
	float drc_param[TEAISP_DRC_PARAM_LENGHT];
	teaisp_drc_ctx_t *ctx = (teaisp_drc_ctx_t *)thiz->module_ctx;

	clog_i("run, pipe_id: %d\n", thiz->pipe_id);
	prctl(PR_SET_NAME, "teaisp_drc", 0, 0, 0);

	VIDEO_FRAME_INFO_S *src_frame = NULL;

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

		pthread_mutex_lock(&ctx->param_lock);
		memcpy(drc_param, ctx->drc_param,
		       sizeof(float) * TEAISP_DRC_PARAM_LENGHT);
		pthread_mutex_unlock(&ctx->param_lock);

		if (fabs(drc_param[0] - 0.0) < 0.0001) { // teaisp drc disable
			teaisp_drc_data_t *data = (teaisp_drc_data_t *)calloc(
				1, sizeof(teaisp_drc_data_t));
			if (data == NULL) {
				clog_e("calloc failed\n");
				continue;
			}

			data->frame = *src_frame;
			data->is_from_src = 1;

			ret = module_queue_push(&thiz->queue, data,
						DAEMON_TIMEOUT_MS);
			if (ret != 0) {
				clog_e("module_queue_push failed with %#x\n",
				       ret);
				src_module->fun.put(src_module, src_frame);
				free(data);
			} else {
				free(src_frame);
			}
			src_frame = NULL;
			is_first_frame = 1;
			continue;
		}

		if (is_first_frame) {
			drc_param[0] = 1.0;
			is_first_frame = 0;
		} else {
			drc_param[0] = 0.0;
		}

		uint64_t vb_phy_addr = 0;

		ret = teaisp_drc_get_vb(ctx, &vb_phy_addr);
		if (ret != 0) {
			clog_e("teaisp_drc_get_vb failed\n");
			continue;
		}

		ctx->input_tensors[DRC_IN_IMG].device_mem.u.device.device_addr =
			src_frame->stVFrame.u64PhyAddr[0];
		ctx->output_tensors[DRC_OUT_IMG]
			.device_mem.u.device.device_addr = vb_phy_addr;

		bm_tensor_t temp;

		temp = ctx->input_tensors[DRC_IN_EMA];
		ctx->input_tensors[DRC_IN_EMA] =
			ctx->output_tensors[DRC_OUT_EMA];
		ctx->output_tensors[DRC_OUT_EMA] = temp;

		memcpy(ctx->input_vaddr[DRC_IN_COEFF], drc_param,
		       sizeof(float) * TEAISP_DRC_PARAM_LENGHT);

		uint32_t core_id = 0;
		int pipe = thiz->pipe_id;

		if (access("/tmp/teaisp_drc_dump", F_OK) == 0) {
			teaisp_drc_dump_input(ctx, pipe);
			system("rm /tmp/teaisp_drc_dump;touch /tmp/teaisp_drc_dump_output");
		}

		bool ret = bmrt_launch_tensor_multi_cores(
			ctx->p_bmrt, ctx->net_names[0], ctx->input_tensors,
			ctx->input_num, ctx->output_tensors, ctx->output_num,
			true, false, (const int *)&core_id, 1);

		if (ret) {
			status = bm_thread_sync_from_core(bm_handle, core_id);
		}

		if (!ret || BM_SUCCESS != status) {
			clog_e("[AIDRC] %s, inference failed...\n",
			       ctx->net_names[0]);
		}

		if (access("/tmp/teaisp_drc_dump_output", F_OK) == 0) {
			teaisp_drc_dump_output(ctx, pipe);
			system("rm /tmp/teaisp_drc_dump_output");
		}

		teaisp_drc_data_t *data = (teaisp_drc_data_t *)calloc(
			1, sizeof(teaisp_drc_data_t));
		if (data == NULL) {
			clog_e("calloc failed\n");
			continue;
		}

		data->frame = *src_frame;
		data->is_from_src = 0;

		data->frame.stVFrame.u64PhyAddr[0] = vb_phy_addr;
		data->frame.stVFrame.u64PhyAddr[1] =
			vb_phy_addr + src_frame->stVFrame.u32Length[0];
		data->frame.stVFrame.u64PhyAddr[2] =
			vb_phy_addr + src_frame->stVFrame.u32Length[0] +
			src_frame->stVFrame.u32Length[1];

		data->frame.stVFrame.pu8VirAddr[0] = NULL;
		data->frame.stVFrame.pu8VirAddr[1] = NULL;
		data->frame.stVFrame.pu8VirAddr[2] = NULL;

		ret = module_queue_push(&thiz->queue, data, DAEMON_TIMEOUT_MS);
		if (ret != 0) {
			clog_e("module_queue_push failed with %#x\n", ret);
			teaisp_drc_put_vb(vb_phy_addr);
			free(data);
		}
	}

	while (module_queue_size(&thiz->queue) > 0) {
		teaisp_drc_data_t *data = NULL;

		module_queue_pop(&thiz->queue, (void **)&data,
				 DAEMON_TIMEOUT_MS);
		if (data->is_from_src) {
			VIDEO_FRAME_INFO_S *frame =
				(VIDEO_FRAME_INFO_S *)calloc(
					1, sizeof(VIDEO_FRAME_INFO_S));

			if (frame == NULL) {
				clog_a("calloc failed\n");
			}
			*frame = data->frame;
			src_module->fun.put(src_module, frame);
		} else {
			teaisp_drc_put_vb(data->frame.stVFrame.u64PhyAddr[0]);
		}
		free(data);
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
	teaisp_drc_data_t *drc_data = (teaisp_drc_data_t *)data;

	if (drc_data->is_from_src) {
		struct module_t *src_module =
			&(GET_MODULE_PIPE_NODE_PTR(thiz)->prev->module);
		VIDEO_FRAME_INFO_S *frame = (VIDEO_FRAME_INFO_S *)calloc(
			1, sizeof(VIDEO_FRAME_INFO_S));

		if (frame == NULL) {
			clog_a("calloc failed\n");
		}
		*frame = drc_data->frame;
		src_module->fun.put(src_module, frame);
	} else {
		teaisp_drc_put_vb(drc_data->frame.stVFrame.u64PhyAddr[0]);
	}
	free(drc_data);
	return ret;
}

struct module_fun_t teaisp_drc_fun = {
	.init = init,
	.deinit = deinit,
	.start = start,
	.stop = stop,
	.get = get,
	.put = put,
};
