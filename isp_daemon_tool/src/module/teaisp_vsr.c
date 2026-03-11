#include <math.h>
#include <sys/prctl.h>

#define CLOG_OUTPUT_LVL CLOG_LVL_DEBUG
#define CLOG_TAG "vsr"

#include "daemon_base.h"
#include "daemon_cfg.h"
#include "daemon_module.h"

#include "bmruntime_interface.h"
#include "cvi_isp.h"
#include "cvi_sys.h"
#include "cvi_vb.h"

#define TEAISP_VSR_QUEUE_SIZE (1)

#define VSR_IN_IMG     (0)
#define VSR_IN_PRE_IMG (1)
#define VSR_IN_NUM (2)

#define VSR_OUT_IMG (0)
#define VSR_OUT_NUM (1)

typedef struct {
	void *p_bmrt;
	const char **net_names;
	bm_tensor_t *input_tensors;
	bm_tensor_t *output_tensors;
	int input_num;
	int output_num;
	uint32_t in_img_width;
	uint32_t in_img_height;
	uint32_t out_img_width;
	uint32_t out_img_height;
	VB_POOL vb_pool;
} teaisp_vsr_ctx_t;

static int init_cnt;
static bm_handle_t bm_handle;

static void teaisp_vsr_dump_input(teaisp_vsr_ctx_t *ctx, int pipe)
{
	void *addr_tmp = NULL;
	int size = 0;
	FILE *fp = NULL;
	char path[128] = { 0 };

	snprintf(path, sizeof(path), "/tmp/vsr_input%d_img.bin", pipe);
	size = ctx->input_tensors[VSR_IN_IMG].device_mem.size;
	addr_tmp = CVI_SYS_MmapCache(
		ctx->input_tensors[VSR_IN_IMG].device_mem.u.device.device_addr,
		size);
	fp = fopen(path, "wb");
	fwrite(addr_tmp, size, 1, fp);
	fclose(fp);
	CVI_SYS_Munmap(addr_tmp, size);

	snprintf(path, sizeof(path), "/tmp/vsr_input%d_pre_img.bin", pipe);
	size = ctx->input_tensors[VSR_IN_PRE_IMG].device_mem.size;
	addr_tmp = CVI_SYS_MmapCache(
		ctx->input_tensors[VSR_IN_PRE_IMG].device_mem.u.device.device_addr,
		size);
	fp = fopen(path, "wb");
	fwrite(addr_tmp, size, 1, fp);
	fclose(fp);
	CVI_SYS_Munmap(addr_tmp, size);

	printf("Successfully written input_tensors to files!\n");
}

static void teaisp_vsr_dump_output(teaisp_vsr_ctx_t *ctx, int pipe)
{
	void *addr_tmp = NULL;
	int size = 0;
	FILE *fp = NULL;
	char path[128] = { 0 };

	snprintf(path, sizeof(path), "/tmp/vsr_output%d_img.bin", pipe);
	size = ctx->output_tensors[VSR_OUT_IMG].device_mem.size;
	addr_tmp = CVI_SYS_MmapCache(
		ctx->output_tensors[VSR_OUT_IMG].device_mem.u.device.device_addr,
		size);
	fp = fopen(path, "wb");
	fwrite(addr_tmp, size, 1, fp);
	fclose(fp);
	CVI_SYS_Munmap(addr_tmp, size);

	printf("Successfully written output_tensors to files!\n");
}

static int teaisp_vsr_unload_model(teaisp_vsr_ctx_t *ctx)
{
	if (ctx->input_tensors[VSR_IN_IMG].device_mem.u.device.device_addr != 0) {
		bm_free_device(bm_handle, ctx->input_tensors[VSR_IN_IMG].device_mem);
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

static int teaisp_vsr_load_model(teaisp_vsr_ctx_t *ctx, const char *path)
{
	const bm_net_info_t *net_info = NULL;

	ctx->p_bmrt = bmrt_create(bm_handle);
	if (ctx->p_bmrt == NULL) {
		clog_e("bmrt create fail\n");
		goto load_model_fail;
	}

	if (!bmrt_load_bmodel(ctx->p_bmrt, path)) {
		clog_e("load bmodel fail, %s\n", path);
		goto load_model_fail;
	}

	bmrt_get_network_names(ctx->p_bmrt, &ctx->net_names);

	net_info = bmrt_get_network_info(ctx->p_bmrt, ctx->net_names[0]);

	clog_i("net name: %s, in: %d, out: %d\n", ctx->net_names[0],
		   net_info->input_num, net_info->output_num);

	ctx->input_num = net_info->input_num;
	ctx->output_num = net_info->output_num;

	if (ctx->input_num != VSR_IN_NUM || ctx->output_num != VSR_OUT_NUM) {
		clog_e("model param num not match!!!! in: %d, %d, out: %d, %d\n",
			   ctx->input_num, VSR_IN_NUM, ctx->output_num,
			   VSR_OUT_NUM);
		goto load_model_fail;
	}

	ctx->input_tensors =
		(bm_tensor_t *)calloc(ctx->input_num, sizeof(bm_tensor_t));
	if (ctx->input_tensors == NULL) {
		clog_e("calloc fail, %ld\n",
			   ctx->input_num * sizeof(bm_tensor_t));
		goto load_model_fail;
	}

	ctx->output_tensors =
		(bm_tensor_t *)calloc(ctx->output_num, sizeof(bm_tensor_t));
	if (ctx->output_tensors == NULL) {
		clog_e("calloc fail, %ld\n",
			   ctx->output_num * sizeof(bm_tensor_t));
		goto load_model_fail;
	}

	// input
	for (int i = 0; i < ctx->input_num; i++) {
		ctx->input_tensors[i].dtype = net_info->input_dtypes[i];
		ctx->input_tensors[i].shape =
			net_info->stages[0].input_shapes[i];
		ctx->input_tensors[i].st_mode = BM_STORE_1N;

		memset(&ctx->input_tensors[i].device_mem, 0,
			   sizeof(bm_device_mem_t));
		ctx->input_tensors[i].device_mem.size =
			net_info->max_input_bytes[i];

		if (i == VSR_IN_IMG) {
			ctx->in_img_width = ctx->input_tensors[i].shape.dims[3];
			ctx->in_img_height = ctx->input_tensors[i].shape.dims[2];

			bm_malloc_device_byte(
				bm_handle, &ctx->input_tensors[i].device_mem,
				net_info->max_input_bytes[i]);
		}

		clog_i("in: %d, dtype: %d, shape: %dx%dx%dx%d, %d, 0x%lx, size: %d\n",
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

		memset(&ctx->output_tensors[i].device_mem, 0,
			   sizeof(bm_device_mem_t));
		ctx->output_tensors[i].device_mem.size =
			net_info->max_output_bytes[i];

		if (i == VSR_OUT_IMG) {
			ctx->out_img_width = ctx->output_tensors[i].shape.dims[3];
			ctx->out_img_height = ctx->output_tensors[i].shape.dims[2];
		}

		clog_i("out: %d, dtype: %d, shape: %dx%dx%dx%d, %d, 0x%lx, size: %d\n",
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

	teaisp_vsr_unload_model(ctx);

	return -1;
}

static int teaisp_vsr_get_vb(teaisp_vsr_ctx_t *ctx, uint64_t *vb_phy_addr)
{
	VB_BLK vb_blk = CVI_VB_GetBlock(
		ctx->vb_pool,
		ctx->output_tensors[VSR_OUT_IMG].device_mem.size);
	if (vb_blk == VB_INVALID_HANDLE) {
		clog_e("get vb_blk failed, size: %d\n",
			   ctx->output_tensors[VSR_OUT_IMG].device_mem.size);
		return -1;
	}
	*vb_phy_addr = CVI_VB_Handle2PhysAddr(vb_blk);
	return 0;
}

static int teaisp_vsr_put_vb(uint64_t vb_phy_addr)
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

static int teaisp_vsr_alloc_vb_pool(teaisp_vsr_ctx_t *ctx)
{
	VB_POOL_CONFIG_S vb_pool_cfg;

	memset(&vb_pool_cfg, 0, sizeof(VB_POOL_CONFIG_S));
	vb_pool_cfg.u32BlkSize = ctx->output_tensors[VSR_OUT_IMG].device_mem.size;
	vb_pool_cfg.u32BlkCnt = 3;
	vb_pool_cfg.enRemapMode = VB_REMAP_MODE_CACHED;
	snprintf(vb_pool_cfg.acName, MAX_VB_POOL_NAME_LEN, "teaisp_vsr_pool");
	ctx->vb_pool = CVI_VB_CreatePool(&vb_pool_cfg);
	if (ctx->vb_pool == VB_INVALID_POOLID) {
		clog_e("CVI_VB_CreatePool failed for teaisp_vsr\n");
		return -1;
	}
	return 0;
}

static int teaisp_vsr_free_vb_pool(teaisp_vsr_ctx_t *ctx)
{
	if (ctx->vb_pool != VB_INVALID_POOLID) {
		CVI_VB_DestroyPool(ctx->vb_pool);
		ctx->vb_pool = VB_INVALID_POOLID;
	}
	return 0;
}

static int init(struct module_t *thiz)
{
	int ret = 0;

	clog_i("pipe_id: %d\n", thiz->pipe_id);
	module_queue_init(&thiz->queue, TEAISP_VSR_QUEUE_SIZE);

	module_teaisp_vsr_cfg_t *vsr_cfg =
		(module_teaisp_vsr_cfg_t *)thiz->module_cfg;

	if (init_cnt == 0 && bm_handle == NULL) {
		ret = bm_dev_request(&bm_handle, 0);
		if (ret != BM_SUCCESS) {
			clog_e("bm_dev_request failed with %d\n", ret);
			return ret;
		}
	}

	init_cnt++;

	teaisp_vsr_ctx_t *ctx =
		(teaisp_vsr_ctx_t *)calloc(1, sizeof(teaisp_vsr_ctx_t));
	if (ctx == NULL) {
		clog_e("calloc failed\n");
		return -1;
	}

	thiz->module_ctx = ctx;

	if (teaisp_vsr_load_model(ctx, vsr_cfg->model_path) < 0) {
		clog_e("teaisp_vsr_load_model: %s failed\n", vsr_cfg->model_path);
		return -1;
	}

	teaisp_vsr_alloc_vb_pool(ctx);
	return 0;
}

static int deinit(struct module_t *thiz)
{
	teaisp_vsr_ctx_t *ctx = (teaisp_vsr_ctx_t *)thiz->module_ctx;

	teaisp_vsr_unload_model(ctx);
	teaisp_vsr_free_vb_pool(ctx);

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
	teaisp_vsr_ctx_t *ctx = (teaisp_vsr_ctx_t *)thiz->module_ctx;

	clog_i("run, pipe_id: %d\n", thiz->pipe_id);
	prctl(PR_SET_NAME, "teaisp_vsr", 0, 0, 0);

	VIDEO_FRAME_INFO_S *src_frame = NULL;
	VIDEO_FRAME_INFO_S *dst_frame = NULL;
	CVI_CDMA_2D_S cdma_2d_param;

	memset(&cdma_2d_param, 0, sizeof(CVI_CDMA_2D_S));

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

		uint64_t vb_phy_addr = 0;

		if (is_first_frame) {
			is_first_frame = 0;

			ret = teaisp_vsr_get_vb(ctx, &vb_phy_addr);
			if (ret != 0) {
				clog_e("teaisp_vsr_get_vb failed\n");
				continue;
			}

			void *vaddr = CVI_SYS_MmapCache(
				vb_phy_addr,
				ctx->input_tensors[VSR_IN_PRE_IMG].device_mem.size);
			if (vaddr == NULL) {
				clog_e("CVI_SYS_MmapCache failed\n");
				teaisp_vsr_put_vb(vb_phy_addr);
				continue;
			}
			memset(vaddr, 0,
				   ctx->input_tensors[VSR_IN_PRE_IMG].device_mem.size);
			CVI_SYS_Munmap(vaddr,
						   ctx->input_tensors[VSR_IN_PRE_IMG].device_mem.size);

			ctx->input_tensors[VSR_IN_PRE_IMG]
				.device_mem.u.device.device_addr = vb_phy_addr;

			ret = teaisp_vsr_get_vb(ctx, &vb_phy_addr);
			if (ret != 0) {
				clog_e("teaisp_vsr_get_vb failed\n");
				teaisp_vsr_put_vb(ctx->input_tensors[VSR_IN_PRE_IMG]
									  .device_mem.u.device.device_addr);
				continue;
			}
			ctx->output_tensors[VSR_OUT_IMG]
				.device_mem.u.device.device_addr = vb_phy_addr;
		} else {
			ctx->input_tensors[VSR_IN_PRE_IMG]
				.device_mem.u.device.device_addr =
				ctx->output_tensors[VSR_OUT_IMG]
					.device_mem.u.device.device_addr;

			ret = teaisp_vsr_get_vb(ctx, &vb_phy_addr);
			if (ret != 0) {
				clog_e("teaisp_vsr_get_vb failed\n");
				continue;
			}
			ctx->output_tensors[VSR_OUT_IMG]
				.device_mem.u.device.device_addr = vb_phy_addr;
		}

		// vpss out img has 64 byte align, need to copy to input tensor
		// addr which is not aligned
		cdma_2d_param.u64PhyAddrSrc =
			src_frame->stVFrame.u64PhyAddr[0];
		cdma_2d_param.u64PhyAddrDst =
			ctx->input_tensors[VSR_IN_IMG].device_mem.u.device.device_addr;
		cdma_2d_param.u16Width = ctx->in_img_width;
		cdma_2d_param.u16Height = ctx->in_img_height * 3;
		cdma_2d_param.u16StrideSrc = src_frame->stVFrame.u32Stride[0];
		cdma_2d_param.u16StrideDst = ctx->in_img_width;

		ret = CVI_SYS_CDMACopy2D(&cdma_2d_param);
		if (ret != 0) {
			clog_e("CVI_SYS_CDMACopy2D failed\n");
			teaisp_vsr_put_vb(
				ctx->output_tensors[VSR_OUT_IMG].device_mem.u.device.device_addr);
			teaisp_vsr_put_vb(
				ctx->input_tensors[VSR_IN_PRE_IMG].device_mem.u.device.device_addr);
			continue;
		}

		uint32_t core_id = 0;
		int pipe = thiz->pipe_id;

		if (access("/tmp/teaisp_vsr_dump", F_OK) == 0) {
			teaisp_vsr_dump_input(ctx, pipe);
			system("rm /tmp/teaisp_vsr_dump;touch /tmp/teaisp_vsr_dump_output");
		}

		bool ret = bmrt_launch_tensor_multi_cores(
			ctx->p_bmrt, ctx->net_names[0], ctx->input_tensors,
			ctx->input_num, ctx->output_tensors, ctx->output_num,
			true, false, (const int *)&core_id, 1);

		if (ret) {
			status = bm_thread_sync_from_core(bm_handle, core_id);
		}

		if (!ret || BM_SUCCESS != status) {
			clog_e("%s, inference failed...\n",
				   ctx->net_names[0]);
		}

		if (access("/tmp/teaisp_vsr_dump_output", F_OK) == 0) {
			teaisp_vsr_dump_output(ctx, pipe);
			system("rm /tmp/teaisp_vsr_dump_output");
		}

		dst_frame = (VIDEO_FRAME_INFO_S *)calloc(1, sizeof(VIDEO_FRAME_INFO_S));
		if (dst_frame == NULL) {
			clog_e("calloc dst_frame failed\n");
			teaisp_vsr_put_vb(ctx->output_tensors[VSR_OUT_IMG]
								  .device_mem.u.device.device_addr);
			continue;
		}
		//dst_frame->u32PoolId = ctx->vb_pool;
		dst_frame->stVFrame.u32Width = ctx->out_img_width;
		dst_frame->stVFrame.u32Height = ctx->out_img_height;
		dst_frame->stVFrame.enPixelFormat = PIXEL_FORMAT_RGB_888_PLANAR;
		dst_frame->stVFrame.u32Stride[0] = ctx->out_img_width;
		dst_frame->stVFrame.u32Stride[1] = ctx->out_img_width;
		dst_frame->stVFrame.u32Stride[2] = ctx->out_img_width;
		dst_frame->stVFrame.u32Length[0] =
			ctx->out_img_width * ctx->out_img_height;
		dst_frame->stVFrame.u32Length[1] =
			ctx->out_img_width * ctx->out_img_height;
		dst_frame->stVFrame.u32Length[2] =
			ctx->out_img_width * ctx->out_img_height;

		dst_frame->stVFrame.u64PhyAddr[0] =
			ctx->output_tensors[VSR_OUT_IMG].device_mem.u.device.device_addr;
		dst_frame->stVFrame.u64PhyAddr[1] =
			ctx->output_tensors[VSR_OUT_IMG].device_mem.u.device.device_addr +
			dst_frame->stVFrame.u32Length[0];
		dst_frame->stVFrame.u64PhyAddr[2] =
			ctx->output_tensors[VSR_OUT_IMG].device_mem.u.device.device_addr +
			dst_frame->stVFrame.u32Length[0] + dst_frame->stVFrame.u32Length[1];

		dst_frame->stVFrame.pu8VirAddr[0] = NULL;
		dst_frame->stVFrame.pu8VirAddr[1] = NULL;
		dst_frame->stVFrame.pu8VirAddr[2] = NULL;

		dst_frame->stVFrame.u32TimeRef = src_frame->stVFrame.u32TimeRef;
		dst_frame->stVFrame.u64PTS = src_frame->stVFrame.u64PTS;
		dst_frame->stVFrame.u64DTS = src_frame->stVFrame.u64DTS;
		dst_frame->stVFrame.s32FrameIdx = src_frame->stVFrame.s32FrameIdx;
		dst_frame->stVFrame.u32SeqenceNo = src_frame->stVFrame.u32SeqenceNo;

		ret = module_queue_push(&thiz->queue, dst_frame, DAEMON_TIMEOUT_MS);
		if (ret != 0) {
			clog_e("module_queue_push failed with %#x\n", ret);
			teaisp_vsr_put_vb(vb_phy_addr);
		}
	}

	while (module_queue_size(&thiz->queue) > 0) {
		VIDEO_FRAME_INFO_S *dst_frame = NULL;

		module_queue_pop(&thiz->queue, (void **)&dst_frame,
				 DAEMON_TIMEOUT_MS);
		teaisp_vsr_put_vb(dst_frame->stVFrame.u64PhyAddr[0]);
		free(dst_frame);
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
	VIDEO_FRAME_INFO_S *frame = (VIDEO_FRAME_INFO_S *)data;

	UNUSED(thiz);

	teaisp_vsr_put_vb(frame->stVFrame.u64PhyAddr[0]);
	free(data);
	return ret;
}

struct module_fun_t teaisp_vsr_fun = {
	.init = init,
	.deinit = deinit,
	.start = start,
	.stop = stop,
	.get = get,
	.put = put,
};
