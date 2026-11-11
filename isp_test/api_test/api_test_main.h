
#ifndef __API_TEST_MAIN_H__
#define __API_TEST_MAIN_H__

#include "cvi_isp.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*api_test_fn)(VI_PIPE ViPipe);

void reg_api_test_fn(api_test_fn fn);

/* Wait for ISP VD (BE_END) with retry; exit on persistent failure.
 * Used by auto-generated module API test files after each SetAttr call. */
static inline void vd_wait_with_retry_or_exit(VI_PIPE ViPipe, const char *module,
					       const char *member, const char *mode)
{
	CVI_S32 ret;
	int retry = 3;

	while (retry-- > 0) {
		ret = CVI_ISP_GetVDTimeOut(ViPipe, ISP_VD_BE_END, 200);
		if (ret == CVI_SUCCESS)
			return;
	}
	printf("[ISP_TEST_FAIL] %s,%s,%s: VD wait timeout after retries, exiting\n",
	       module, member, mode);
	exit(CVI_FAILURE);
}

#ifdef __cplusplus
}
#endif
#endif /* __API_TEST_MAIN_H__ */
