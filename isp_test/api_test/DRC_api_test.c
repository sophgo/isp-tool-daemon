
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

static int test_DRC_DRCAttr_Enable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.Enable != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.Enable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.Enable = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "Enable", "min");
	// set maximum value
	attr.Enable = 1;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "Enable", "max");
	// set random value
	attr.Enable = rand_range(0, 1);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "Enable", "random");
	// restore default value
	attr.Enable = 1;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_Enable(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_Enable);
}

static int test_DRC_DRCAttr_enOpType(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.enOpType != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.enOpType);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.enOpType = OP_TYPE_AUTO;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "enOpType", "min");
	// set maximum value
	attr.enOpType = OP_TYPE_MANUAL;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "enOpType", "max");
	// restore default value
	attr.enOpType = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_enOpType(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_enOpType);
}

static int test_DRC_DRCAttr_UpdateInterval(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.UpdateInterval != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.UpdateInterval);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.UpdateInterval = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "UpdateInterval", "min");
	// set maximum value
	attr.UpdateInterval = 255;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "UpdateInterval", "max");
	// set random value
	attr.UpdateInterval = rand_range(0, 255);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "UpdateInterval", "random");
	// restore default value
	attr.UpdateInterval = 1;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_UpdateInterval(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_UpdateInterval);
}

static int test_DRC_DRCAttr_AutoMode(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.AutoMode != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.AutoMode);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.AutoMode = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "AutoMode", "min");
	// set maximum value
	attr.AutoMode = 1;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "AutoMode", "max");
	// set random value
	attr.AutoMode = rand_range(0, 1);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "AutoMode", "random");
	// restore default value
	attr.AutoMode = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_AutoMode(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_AutoMode);
}

static int test_DRC_DRCAttr_SaturationLow(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.SaturationLow != 1024) {
		TEST_FAIL("test default value: 1024 != %d\n", (int)attr.SaturationLow);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.SaturationLow = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "SaturationLow", "min");
	// set maximum value
	attr.SaturationLow = 4095;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "SaturationLow", "max");
	// set random value
	attr.SaturationLow = rand_range(0, 4095);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "SaturationLow", "random");
	// set abnormal value test
	attr.SaturationLow = rand_range(4096, 65535);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.SaturationLow = 1024;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_SaturationLow(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_SaturationLow);
}

static int test_DRC_DRCAttr_SaturationHigh(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.SaturationHigh != 1025) {
		TEST_FAIL("test default value: 1025 != %d\n", (int)attr.SaturationHigh);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.SaturationHigh = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "SaturationHigh", "min");
	// set maximum value
	attr.SaturationHigh = 4095;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "SaturationHigh", "max");
	// set random value
	attr.SaturationHigh = rand_range(0, 4095);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "SaturationHigh", "random");
	// set abnormal value test
	attr.SaturationHigh = rand_range(4096, 65535);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.SaturationHigh = 1025;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_SaturationHigh(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_SaturationHigh);
}

static int test_DRC_DRCAttr_ContrastLow(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.ContrastLow != 4095) {
		TEST_FAIL("test default value: 4095 != %d\n", (int)attr.ContrastLow);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.ContrastLow = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "ContrastLow", "min");
	// set maximum value
	attr.ContrastLow = 4095;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "ContrastLow", "max");
	// set random value
	attr.ContrastLow = rand_range(0, 4095);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "ContrastLow", "random");
	// set abnormal value test
	attr.ContrastLow = rand_range(4096, 65535);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.ContrastLow = 4095;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_ContrastLow(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_ContrastLow);
}

static int test_DRC_DRCAttr_ContrastHigh(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.ContrastHigh != 4095) {
		TEST_FAIL("test default value: 4095 != %d\n", (int)attr.ContrastHigh);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.ContrastHigh = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "ContrastHigh", "min");
	// set maximum value
	attr.ContrastHigh = 4095;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "ContrastHigh", "max");
	// set random value
	attr.ContrastHigh = rand_range(0, 4095);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "ContrastHigh", "random");
	// set abnormal value test
	attr.ContrastHigh = rand_range(4096, 65535);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.ContrastHigh = 4095;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_ContrastHigh(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_ContrastHigh);
}

static int test_DRC_DRCAttr_BlockNumW(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.BlockNumW != 32) {
		TEST_FAIL("test default value: 32 != %d\n", (int)attr.BlockNumW);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.BlockNumW = 15;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "BlockNumW", "min");
	// set maximum value
	attr.BlockNumW = 47;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "BlockNumW", "max");
	// set random value
	attr.BlockNumW = rand_range(15, 47);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "BlockNumW", "random");
	// set abnormal value test
	attr.BlockNumW = rand_range(0, 14);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.BlockNumW = 32;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_BlockNumW(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_BlockNumW);
}

static int test_DRC_DRCAttr_GainUB(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.GainUB != 10) {
		TEST_FAIL("test default value: 10 != %d\n", (int)attr.GainUB);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.GainUB = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "GainUB", "min");
	// set maximum value
	attr.GainUB = 255;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "GainUB", "max");
	// set random value
	attr.GainUB = rand_range(0, 255);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "GainUB", "random");
	// restore default value
	attr.GainUB = 10;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_GainUB(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_GainUB);
}

static int test_DRC_DRCAttr_GainLB(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.GainLB != 5) {
		TEST_FAIL("test default value: 5 != %d\n", (int)attr.GainLB);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.GainLB = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "GainLB", "min");
	// set maximum value
	attr.GainLB = 255;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "GainLB", "max");
	// set random value
	attr.GainLB = rand_range(0, 255);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "GainLB", "random");
	// restore default value
	attr.GainLB = 5;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_GainLB(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_GainLB);
}

static int test_DRC_DRCAttr_FSBPstr(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.FSBPstr != 255) {
		TEST_FAIL("test default value: 255 != %d\n", (int)attr.FSBPstr);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.FSBPstr = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "FSBPstr", "min");
	// set maximum value
	attr.FSBPstr = 255;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "FSBPstr", "max");
	// set random value
	attr.FSBPstr = rand_range(0, 255);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "FSBPstr", "random");
	// restore default value
	attr.FSBPstr = 255;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_FSBPstr(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_FSBPstr);
}

static int test_DRC_DRCAttr_DeFlareMode(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.DeFlareMode != 2) {
		TEST_FAIL("test default value: 2 != %d\n", (int)attr.DeFlareMode);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.DeFlareMode = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "DeFlareMode", "min");
	// set maximum value
	attr.DeFlareMode = 2;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "DeFlareMode", "max");
	// set random value
	attr.DeFlareMode = rand_range(0, 2);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "DeFlareMode", "random");
	// set abnormal value test
	attr.DeFlareMode = rand_range(3, 255);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.DeFlareMode = 2;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_DeFlareMode(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_DeFlareMode);
}

static int test_DRC_DRCAttr_DeFlareRatio(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.DeFlareRatio != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.DeFlareRatio);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.DeFlareRatio = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "DeFlareRatio", "min");
	// set maximum value
	attr.DeFlareRatio = 255;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "DeFlareRatio", "max");
	// set random value
	attr.DeFlareRatio = rand_range(0, 255);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "DeFlareRatio", "random");
	// restore default value
	attr.DeFlareRatio = 128;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_DeFlareRatio(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_DeFlareRatio);
}

static int test_DRC_DRCAttr_DeFlareSlope(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.DeFlareSlope != 64) {
		TEST_FAIL("test default value: 64 != %d\n", (int)attr.DeFlareSlope);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.DeFlareSlope = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "DeFlareSlope", "min");
	// set maximum value
	attr.DeFlareSlope = 255;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "DeFlareSlope", "max");
	// set random value
	attr.DeFlareSlope = rand_range(0, 255);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "DeFlareSlope", "random");
	// restore default value
	attr.DeFlareSlope = 64;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_DeFlareSlope(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_DeFlareSlope);
}

static int test_DRC_DRCAttr_AdaptiveLowStr(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.AdaptiveLowStr != 4021) {
		TEST_FAIL("test default value: 4021 != %d\n", (int)attr.AdaptiveLowStr);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.AdaptiveLowStr = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "AdaptiveLowStr", "min");
	// set maximum value
	attr.AdaptiveLowStr = 4095;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "AdaptiveLowStr", "max");
	// set random value
	attr.AdaptiveLowStr = rand_range(0, 4095);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "AdaptiveLowStr", "random");
	// set abnormal value test
	attr.AdaptiveLowStr = rand_range(4096, 65535);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.AdaptiveLowStr = 4021;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_AdaptiveLowStr(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_AdaptiveLowStr);
}

static int test_DRC_DRCAttr_AdaptiveHighStr(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.AdaptiveHighStr != 100) {
		TEST_FAIL("test default value: 100 != %d\n", (int)attr.AdaptiveHighStr);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.AdaptiveHighStr = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "AdaptiveHighStr", "min");
	// set maximum value
	attr.AdaptiveHighStr = 4095;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "AdaptiveHighStr", "max");
	// set random value
	attr.AdaptiveHighStr = rand_range(0, 4095);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "AdaptiveHighStr", "random");
	// set abnormal value test
	attr.AdaptiveHighStr = rand_range(4096, 65535);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.AdaptiveHighStr = 100;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_AdaptiveHighStr(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_AdaptiveHighStr);
}

static int test_DRC_DRCAttr_AdaptiveRatio(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.AdaptiveRatio != 73) {
		TEST_FAIL("test default value: 73 != %d\n", (int)attr.AdaptiveRatio);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.AdaptiveRatio = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "AdaptiveRatio", "min");
	// set maximum value
	attr.AdaptiveRatio = 1000;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "AdaptiveRatio", "max");
	// set random value
	attr.AdaptiveRatio = rand_range(0, 1000);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "AdaptiveRatio", "random");
	// set abnormal value test
	attr.AdaptiveRatio = rand_range(1001, 65535);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.AdaptiveRatio = 73;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_AdaptiveRatio(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_AdaptiveRatio);
}

static int test_DRC_DRCAttr_ColorSuppStr(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.ColorSuppStr != 8) {
		TEST_FAIL("test default value: 8 != %d\n", (int)attr.ColorSuppStr);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.ColorSuppStr = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "ColorSuppStr", "min");
	// set maximum value
	attr.ColorSuppStr = 32;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "ColorSuppStr", "max");
	// set random value
	attr.ColorSuppStr = rand_range(0, 32);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "ColorSuppStr", "random");
	// set abnormal value test
	attr.ColorSuppStr = rand_range(33, 255);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.ColorSuppStr = 8;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_ColorSuppStr(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_ColorSuppStr);
}

static int test_DRC_DRCAttr_ColorSuppThr(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.ColorSuppThr != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.ColorSuppThr);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.ColorSuppThr = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "ColorSuppThr", "min");
	// set maximum value
	attr.ColorSuppThr = 64;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "ColorSuppThr", "max");
	// set random value
	attr.ColorSuppThr = rand_range(0, 64);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "ColorSuppThr", "random");
	// set abnormal value test
	attr.ColorSuppThr = rand_range(65, 255);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.ColorSuppThr = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_ColorSuppThr(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_ColorSuppThr);
}

static int test_DRC_DRCAttr_ColorSuppLow(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.ColorSuppLow != 255) {
		TEST_FAIL("test default value: 255 != %d\n", (int)attr.ColorSuppLow);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.ColorSuppLow = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "ColorSuppLow", "min");
	// set maximum value
	attr.ColorSuppLow = 255;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "ColorSuppLow", "max");
	// set random value
	attr.ColorSuppLow = rand_range(0, 255);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "ColorSuppLow", "random");
	// restore default value
	attr.ColorSuppLow = 255;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_ColorSuppLow(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_ColorSuppLow);
}

static int test_DRC_DRCAttr_Strength_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.Strength != 64) {
		TEST_FAIL("test default value: 64 != %d\n", (int)attr.stManual.Strength);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.Strength = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "Strength", "min");
	// set maximum value
	attr.stManual.Strength = 255;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "Strength", "max");
	// set random value
	attr.stManual.Strength = rand_range(0, 255);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "Strength", "random");
	// restore default value
	attr.stManual.Strength = 64;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_Strength_manual(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_Strength_manual);
}

static int test_DRC_DRCAttr_Strength_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_LV_NUM] = { 64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64 };
	if (memcmp(default_val_0, attr.stAuto.Strength, sizeof(CVI_U8) * ISP_AUTO_LV_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_LV_NUM; ++j) {
		attr.stAuto.Strength[j] = 0;
	}
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "Strength", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_LV_NUM; ++j) {
		attr.stAuto.Strength[j] = 255;
	}
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "Strength", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_LV_NUM; ++j) {
		attr.stAuto.Strength[j] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "Strength", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_LV_NUM] = { 64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64 };
	memcpy(attr.stAuto.Strength, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_LV_NUM);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_Strength_auto(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_Strength_auto);
}

static int test_DRC_DRCAttr_StrengthMin_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.StrengthMin != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.stManual.StrengthMin);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.StrengthMin = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "StrengthMin", "min");
	// set maximum value
	attr.stManual.StrengthMin = 255;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "StrengthMin", "max");
	// set random value
	attr.stManual.StrengthMin = rand_range(0, 255);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "StrengthMin", "random");
	// restore default value
	attr.stManual.StrengthMin = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_StrengthMin_manual(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_StrengthMin_manual);
}

static int test_DRC_DRCAttr_StrengthMin_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_LV_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	if (memcmp(default_val_0, attr.stAuto.StrengthMin, sizeof(CVI_U8) * ISP_AUTO_LV_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_LV_NUM; ++j) {
		attr.stAuto.StrengthMin[j] = 0;
	}
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "StrengthMin", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_LV_NUM; ++j) {
		attr.stAuto.StrengthMin[j] = 255;
	}
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "StrengthMin", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_LV_NUM; ++j) {
		attr.stAuto.StrengthMin[j] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "StrengthMin", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_LV_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	memcpy(attr.stAuto.StrengthMin, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_LV_NUM);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_StrengthMin_auto(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_StrengthMin_auto);
}

static int test_DRC_DRCAttr_StrengthMax_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.StrengthMax != 255) {
		TEST_FAIL("test default value: 255 != %d\n", (int)attr.stManual.StrengthMax);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.StrengthMax = 0;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "StrengthMax", "min");
	// set maximum value
	attr.stManual.StrengthMax = 255;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "StrengthMax", "max");
	// set random value
	attr.stManual.StrengthMax = rand_range(0, 255);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "StrengthMax", "random");
	// restore default value
	attr.stManual.StrengthMax = 255;
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_StrengthMax_manual(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_StrengthMax_manual);
}

static int test_DRC_DRCAttr_StrengthMax_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DRC_ATTR_S attr;

	ret = CVI_ISP_GetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDRCAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_LV_NUM] = { 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 };
	if (memcmp(default_val_0, attr.stAuto.StrengthMax, sizeof(CVI_U8) * ISP_AUTO_LV_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_LV_NUM; ++j) {
		attr.stAuto.StrengthMax[j] = 0;
	}
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "StrengthMax", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_LV_NUM; ++j) {
		attr.stAuto.StrengthMax[j] = 255;
	}
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "StrengthMax", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_LV_NUM; ++j) {
		attr.stAuto.StrengthMax[j] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DRC", "StrengthMax", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_LV_NUM] = { 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 };
	memcpy(attr.stAuto.StrengthMax, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_LV_NUM);
	ret = CVI_ISP_SetDRCAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DRC_DRCAttr_StrengthMax_auto(void)
{
	reg_api_test_fn(test_DRC_DRCAttr_StrengthMax_auto);
}
