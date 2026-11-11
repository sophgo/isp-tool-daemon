
// auto generate code, don't modify
// auto generate code, don't modify
// auto generate code, don't modify

#include <stdlib.h>
#include <unistd.h>
#include "api_test_main.h"

#define TEST_FAIL(fmt, arg...) printf("[ISP_TEST_FAIL] %s,%d: " fmt, __FUNCTION__, __LINE__, ##arg)

static long long rand_range(long long a, long long b)
{
	return rand() % (b - a + 1) + a;
}

static int test_DEMOSAIC_DemosaicAttr_Enable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DEMOSAIC_ATTR_S attr;

	ret = CVI_ISP_GetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDemosaicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.Enable != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.Enable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.Enable = 0;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "Enable", "min");
	// set maximum value
	attr.Enable = 1;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "Enable", "max");
	// set random value
	attr.Enable = rand_range(0, 1);
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "Enable", "random");
	// restore default value
	attr.Enable = 1;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DEMOSAIC_DemosaicAttr_Enable(void)
{
	reg_api_test_fn(test_DEMOSAIC_DemosaicAttr_Enable);
}

static int test_DEMOSAIC_DemosaicAttr_UpdateInterval(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DEMOSAIC_ATTR_S attr;

	ret = CVI_ISP_GetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDemosaicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.UpdateInterval != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.UpdateInterval);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.UpdateInterval = 1;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "UpdateInterval", "min");
	// set maximum value
	attr.UpdateInterval = 255;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "UpdateInterval", "max");
	// set random value
	attr.UpdateInterval = rand_range(1, 255);
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "UpdateInterval", "random");
	// set abnormal value test
	attr.UpdateInterval = rand_range(0, 0);
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.UpdateInterval = 1;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DEMOSAIC_DemosaicAttr_UpdateInterval(void)
{
	reg_api_test_fn(test_DEMOSAIC_DemosaicAttr_UpdateInterval);
}

static int test_DEMOSAIC_DemosaicAttr_enOpType(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DEMOSAIC_ATTR_S attr;

	ret = CVI_ISP_GetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDemosaicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.enOpType != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.enOpType);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.enOpType = OP_TYPE_AUTO;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "enOpType", "min");
	// set maximum value
	attr.enOpType = OP_TYPE_MANUAL;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "enOpType", "max");
	// restore default value
	attr.enOpType = 0;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DEMOSAIC_DemosaicAttr_enOpType(void)
{
	reg_api_test_fn(test_DEMOSAIC_DemosaicAttr_enOpType);
}

static int test_DEMOSAIC_DemosaicAttr_CfaEdgeDth(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DEMOSAIC_ATTR_S attr;

	ret = CVI_ISP_GetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDemosaicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.CfaEdgeDth != 20) {
		TEST_FAIL("test default value: 20 != %d\n", (int)attr.CfaEdgeDth);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.CfaEdgeDth = 0;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaEdgeDth", "min");
	// set maximum value
	attr.CfaEdgeDth = 4095;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaEdgeDth", "max");
	// set random value
	attr.CfaEdgeDth = rand_range(0, 4095);
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaEdgeDth", "random");
	// set abnormal value test
	attr.CfaEdgeDth = rand_range(4096, 65535);
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.CfaEdgeDth = 20;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DEMOSAIC_DemosaicAttr_CfaEdgeDth(void)
{
	reg_api_test_fn(test_DEMOSAIC_DemosaicAttr_CfaEdgeDth);
}

static int test_DEMOSAIC_DemosaicAttr_CfaEdgeDth2(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DEMOSAIC_ATTR_S attr;

	ret = CVI_ISP_GetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDemosaicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.CfaEdgeDth2 != 80) {
		TEST_FAIL("test default value: 80 != %d\n", (int)attr.CfaEdgeDth2);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.CfaEdgeDth2 = 0;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaEdgeDth2", "min");
	// set maximum value
	attr.CfaEdgeDth2 = 4095;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaEdgeDth2", "max");
	// set random value
	attr.CfaEdgeDth2 = rand_range(0, 4095);
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaEdgeDth2", "random");
	// set abnormal value test
	attr.CfaEdgeDth2 = rand_range(4096, 65535);
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.CfaEdgeDth2 = 80;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DEMOSAIC_DemosaicAttr_CfaEdgeDth2(void)
{
	reg_api_test_fn(test_DEMOSAIC_DemosaicAttr_CfaEdgeDth2);
}

static int test_DEMOSAIC_DemosaicAttr_CfaFreqTh(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DEMOSAIC_ATTR_S attr;

	ret = CVI_ISP_GetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDemosaicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.CfaFreqTh != 320) {
		TEST_FAIL("test default value: 320 != %d\n", (int)attr.CfaFreqTh);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.CfaFreqTh = 0;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaFreqTh", "min");
	// set maximum value
	attr.CfaFreqTh = 1023;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaFreqTh", "max");
	// set random value
	attr.CfaFreqTh = rand_range(0, 1023);
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaFreqTh", "random");
	// set abnormal value test
	attr.CfaFreqTh = rand_range(1024, 65535);
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.CfaFreqTh = 320;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DEMOSAIC_DemosaicAttr_CfaFreqTh(void)
{
	reg_api_test_fn(test_DEMOSAIC_DemosaicAttr_CfaFreqTh);
}

static int test_DEMOSAIC_DemosaicAttr_CfaFreqBlend(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DEMOSAIC_ATTR_S attr;

	ret = CVI_ISP_GetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDemosaicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.CfaFreqBlend != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.CfaFreqBlend);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.CfaFreqBlend = 0;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaFreqBlend", "min");
	// set maximum value
	attr.CfaFreqBlend = 16;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaFreqBlend", "max");
	// set random value
	attr.CfaFreqBlend = rand_range(0, 16);
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaFreqBlend", "random");
	// set abnormal value test
	attr.CfaFreqBlend = rand_range(17, 255);
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.CfaFreqBlend = 16;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DEMOSAIC_DemosaicAttr_CfaFreqBlend(void)
{
	reg_api_test_fn(test_DEMOSAIC_DemosaicAttr_CfaFreqBlend);
}

static int test_DEMOSAIC_DemosaicAttr_CfaDenoiseEnable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DEMOSAIC_ATTR_S attr;

	ret = CVI_ISP_GetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDemosaicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.CfaDenoiseEnable != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.CfaDenoiseEnable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.CfaDenoiseEnable = 0;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaDenoiseEnable", "min");
	// set maximum value
	attr.CfaDenoiseEnable = 1;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaDenoiseEnable", "max");
	// set random value
	attr.CfaDenoiseEnable = rand_range(0, 1);
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaDenoiseEnable", "random");
	// restore default value
	attr.CfaDenoiseEnable = 1;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DEMOSAIC_DemosaicAttr_CfaDenoiseEnable(void)
{
	reg_api_test_fn(test_DEMOSAIC_DemosaicAttr_CfaDenoiseEnable);
}

static int test_DEMOSAIC_DemosaicAttr_CfaKfmax(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DEMOSAIC_ATTR_S attr;

	ret = CVI_ISP_GetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDemosaicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.CfaKfmax != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.CfaKfmax);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.CfaKfmax = 0;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaKfmax", "min");
	// set maximum value
	attr.CfaKfmax = 255;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaKfmax", "max");
	// set random value
	attr.CfaKfmax = rand_range(0, 255);
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaKfmax", "random");
	// restore default value
	attr.CfaKfmax = 128;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DEMOSAIC_DemosaicAttr_CfaKfmax(void)
{
	reg_api_test_fn(test_DEMOSAIC_DemosaicAttr_CfaKfmax);
}

static int test_DEMOSAIC_DemosaicAttr_CfaKfmin(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DEMOSAIC_ATTR_S attr;

	ret = CVI_ISP_GetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDemosaicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.CfaKfmin != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.CfaKfmin);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.CfaKfmin = 0;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaKfmin", "min");
	// set maximum value
	attr.CfaKfmin = 255;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaKfmin", "max");
	// set random value
	attr.CfaKfmin = rand_range(0, 255);
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaKfmin", "random");
	// restore default value
	attr.CfaKfmin = 16;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DEMOSAIC_DemosaicAttr_CfaKfmin(void)
{
	reg_api_test_fn(test_DEMOSAIC_DemosaicAttr_CfaKfmin);
}

static int test_DEMOSAIC_DemosaicAttr_CfaEth0(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DEMOSAIC_ATTR_S attr;

	ret = CVI_ISP_GetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDemosaicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.CfaEth0 != 6) {
		TEST_FAIL("test default value: 6 != %d\n", (int)attr.CfaEth0);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.CfaEth0 = 0;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaEth0", "min");
	// set maximum value
	attr.CfaEth0 = 255;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaEth0", "max");
	// set random value
	attr.CfaEth0 = rand_range(0, 255);
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaEth0", "random");
	// restore default value
	attr.CfaEth0 = 6;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DEMOSAIC_DemosaicAttr_CfaEth0(void)
{
	reg_api_test_fn(test_DEMOSAIC_DemosaicAttr_CfaEth0);
}

static int test_DEMOSAIC_DemosaicAttr_CfaEth1(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DEMOSAIC_ATTR_S attr;

	ret = CVI_ISP_GetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDemosaicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.CfaEth1 != 15) {
		TEST_FAIL("test default value: 15 != %d\n", (int)attr.CfaEth1);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.CfaEth1 = 0;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaEth1", "min");
	// set maximum value
	attr.CfaEth1 = 255;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaEth1", "max");
	// set random value
	attr.CfaEth1 = rand_range(0, 255);
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaEth1", "random");
	// restore default value
	attr.CfaEth1 = 15;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DEMOSAIC_DemosaicAttr_CfaEth1(void)
{
	reg_api_test_fn(test_DEMOSAIC_DemosaicAttr_CfaEth1);
}

static int test_DEMOSAIC_DemosaicAttr_CfaEth2(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DEMOSAIC_ATTR_S attr;

	ret = CVI_ISP_GetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDemosaicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.CfaEth2 != 10) {
		TEST_FAIL("test default value: 10 != %d\n", (int)attr.CfaEth2);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.CfaEth2 = 0;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaEth2", "min");
	// set maximum value
	attr.CfaEth2 = 255;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaEth2", "max");
	// set random value
	attr.CfaEth2 = rand_range(0, 255);
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaEth2", "random");
	// restore default value
	attr.CfaEth2 = 10;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DEMOSAIC_DemosaicAttr_CfaEth2(void)
{
	reg_api_test_fn(test_DEMOSAIC_DemosaicAttr_CfaEth2);
}

static int test_DEMOSAIC_DemosaicAttr_CfaDth(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DEMOSAIC_ATTR_S attr;

	ret = CVI_ISP_GetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDemosaicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.CfaDth != 10) {
		TEST_FAIL("test default value: 10 != %d\n", (int)attr.CfaDth);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.CfaDth = 0;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaDth", "min");
	// set maximum value
	attr.CfaDth = 255;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaDth", "max");
	// set random value
	attr.CfaDth = rand_range(0, 255);
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DEMOSAIC", "CfaDth", "random");
	// restore default value
	attr.CfaDth = 10;
	ret = CVI_ISP_SetDemosaicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DEMOSAIC_DemosaicAttr_CfaDth(void)
{
	reg_api_test_fn(test_DEMOSAIC_DemosaicAttr_CfaDth);
}
