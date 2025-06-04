
#include "daemon_utils.h"
#include "cvi_sys.h"
#include "cvi_comm_vi.h"

int dump_video_frame(FILE *fp, void *pframe)
{
	VIDEO_FRAME_INFO_S *frame = (VIDEO_FRAME_INFO_S *)pframe;

	if (fp == NULL || frame == NULL) {
		return -1;
	}

	for (int i = 0; i < 3; i++) {
		if (frame->stVFrame.u32Length[i] == 0) {
			continue;
		}
		void *vaddr = CVI_SYS_MmapCache(frame->stVFrame.u64PhyAddr[i],
					   frame->stVFrame.u32Length[i]);
		if (vaddr == NULL) {
			clog_e("CVI_SYS_Mmap:0x%x failed\n",
			       frame->stVFrame.u64PhyAddr[i]);
			return -1;
		}
		CVI_SYS_IonInvalidateCache(frame->stVFrame.u64PhyAddr[i], vaddr,
					   frame->stVFrame.u32Length[i]);
		fwrite(vaddr, 1, frame->stVFrame.u32Length[i], fp);
		fflush(fp);
		CVI_SYS_Munmap(vaddr, frame->stVFrame.u32Length[i]);
	}

	return 0;
}
