
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

static int test_CADJ_CAdjAttr_Enable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CADJ_ATTR_S attr;

	ret = CVI_ISP_GetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAdjAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.Enable != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.Enable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.Enable = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "Enable", "min");
	// set maximum value
	attr.Enable = 1;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "Enable", "max");
	// set random value
	attr.Enable = rand_range(0, 1);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "Enable", "random");
	// restore default value
	attr.Enable = 1;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CADJ_CAdjAttr_Enable(void)
{
	reg_api_test_fn(test_CADJ_CAdjAttr_Enable);
}

static int test_CADJ_CAdjAttr_enOpType(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CADJ_ATTR_S attr;

	ret = CVI_ISP_GetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAdjAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.enOpType != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.enOpType);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.enOpType = OP_TYPE_AUTO;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "enOpType", "min");
	// set maximum value
	attr.enOpType = OP_TYPE_MANUAL;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "enOpType", "max");
	// restore default value
	attr.enOpType = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CADJ_CAdjAttr_enOpType(void)
{
	reg_api_test_fn(test_CADJ_CAdjAttr_enOpType);
}

static int test_CADJ_CAdjAttr_UpdateInterval(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CADJ_ATTR_S attr;

	ret = CVI_ISP_GetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAdjAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.UpdateInterval != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.UpdateInterval);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.UpdateInterval = 1;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "UpdateInterval", "min");
	// set maximum value
	attr.UpdateInterval = 255;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "UpdateInterval", "max");
	// set random value
	attr.UpdateInterval = rand_range(1, 255);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "UpdateInterval", "random");
	// set abnormal value test
	attr.UpdateInterval = rand_range(0, 0);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.UpdateInterval = 1;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CADJ_CAdjAttr_UpdateInterval(void)
{
	reg_api_test_fn(test_CADJ_CAdjAttr_UpdateInterval);
}

static int test_CADJ_CAdjAttr_YeeEnable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CADJ_ATTR_S attr;

	ret = CVI_ISP_GetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAdjAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.YeeEnable != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.YeeEnable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.YeeEnable = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YeeEnable", "min");
	// set maximum value
	attr.YeeEnable = 1;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YeeEnable", "max");
	// set random value
	attr.YeeEnable = rand_range(0, 1);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YeeEnable", "random");
	// restore default value
	attr.YeeEnable = 1;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CADJ_CAdjAttr_YeeEnable(void)
{
	reg_api_test_fn(test_CADJ_CAdjAttr_YeeEnable);
}

static int test_CADJ_CAdjAttr_YeePosGain(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CADJ_ATTR_S attr;

	ret = CVI_ISP_GetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAdjAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.YeePosGain != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.YeePosGain);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.YeePosGain = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YeePosGain", "min");
	// set maximum value
	attr.YeePosGain = 1023;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YeePosGain", "max");
	// set random value
	attr.YeePosGain = rand_range(0, 1023);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YeePosGain", "random");
	// set abnormal value test
	attr.YeePosGain = rand_range(1024, 65535);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.YeePosGain = 128;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CADJ_CAdjAttr_YeePosGain(void)
{
	reg_api_test_fn(test_CADJ_CAdjAttr_YeePosGain);
}

static int test_CADJ_CAdjAttr_YeeNegGain(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CADJ_ATTR_S attr;

	ret = CVI_ISP_GetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAdjAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.YeeNegGain != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.YeeNegGain);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.YeeNegGain = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YeeNegGain", "min");
	// set maximum value
	attr.YeeNegGain = 1023;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YeeNegGain", "max");
	// set random value
	attr.YeeNegGain = rand_range(0, 1023);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YeeNegGain", "random");
	// set abnormal value test
	attr.YeeNegGain = rand_range(1024, 65535);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.YeeNegGain = 128;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CADJ_CAdjAttr_YeeNegGain(void)
{
	reg_api_test_fn(test_CADJ_CAdjAttr_YeeNegGain);
}

static int test_CADJ_CAdjAttr_YeePosInvert(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CADJ_ATTR_S attr;

	ret = CVI_ISP_GetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAdjAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.YeePosInvert != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.YeePosInvert);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.YeePosInvert = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YeePosInvert", "min");
	// set maximum value
	attr.YeePosInvert = 1;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YeePosInvert", "max");
	// set random value
	attr.YeePosInvert = rand_range(0, 1);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YeePosInvert", "random");
	// restore default value
	attr.YeePosInvert = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CADJ_CAdjAttr_YeePosInvert(void)
{
	reg_api_test_fn(test_CADJ_CAdjAttr_YeePosInvert);
}

static int test_CADJ_CAdjAttr_YeeNegInvert(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CADJ_ATTR_S attr;

	ret = CVI_ISP_GetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAdjAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.YeeNegInvert != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.YeeNegInvert);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.YeeNegInvert = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YeeNegInvert", "min");
	// set maximum value
	attr.YeeNegInvert = 1;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YeeNegInvert", "max");
	// set random value
	attr.YeeNegInvert = rand_range(0, 1);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YeeNegInvert", "random");
	// restore default value
	attr.YeeNegInvert = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CADJ_CAdjAttr_YeeNegInvert(void)
{
	reg_api_test_fn(test_CADJ_CAdjAttr_YeeNegInvert);
}

static int test_CADJ_CAdjAttr_YbrtEnable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CADJ_ATTR_S attr;

	ret = CVI_ISP_GetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAdjAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.YbrtEnable != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.YbrtEnable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.YbrtEnable = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YbrtEnable", "min");
	// set maximum value
	attr.YbrtEnable = 1;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YbrtEnable", "max");
	// set random value
	attr.YbrtEnable = rand_range(0, 1);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YbrtEnable", "random");
	// restore default value
	attr.YbrtEnable = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CADJ_CAdjAttr_YbrtEnable(void)
{
	reg_api_test_fn(test_CADJ_CAdjAttr_YbrtEnable);
}

static int test_CADJ_CAdjAttr_YbrtGain(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CADJ_ATTR_S attr;

	ret = CVI_ISP_GetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAdjAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.YbrtGain != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.YbrtGain);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.YbrtGain = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YbrtGain", "min");
	// set maximum value
	attr.YbrtGain = 255;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YbrtGain", "max");
	// set random value
	attr.YbrtGain = rand_range(0, 255);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "YbrtGain", "random");
	// restore default value
	attr.YbrtGain = 128;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CADJ_CAdjAttr_YbrtGain(void)
{
	reg_api_test_fn(test_CADJ_CAdjAttr_YbrtGain);
}

static int test_CADJ_CAdjAttr_HueRotateEnable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CADJ_ATTR_S attr;

	ret = CVI_ISP_GetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAdjAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.HueRotateEnable != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.HueRotateEnable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.HueRotateEnable = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "HueRotateEnable", "min");
	// set maximum value
	attr.HueRotateEnable = 1;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "HueRotateEnable", "max");
	// set random value
	attr.HueRotateEnable = rand_range(0, 1);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "HueRotateEnable", "random");
	// restore default value
	attr.HueRotateEnable = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CADJ_CAdjAttr_HueRotateEnable(void)
{
	reg_api_test_fn(test_CADJ_CAdjAttr_HueRotateEnable);
}

static int test_CADJ_CAdjAttr_HueQuadrant(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CADJ_ATTR_S attr;

	ret = CVI_ISP_GetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAdjAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.HueQuadrant != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.HueQuadrant);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.HueQuadrant = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "HueQuadrant", "min");
	// set maximum value
	attr.HueQuadrant = 3;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "HueQuadrant", "max");
	// set random value
	attr.HueQuadrant = rand_range(0, 3);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "HueQuadrant", "random");
	// set abnormal value test
	attr.HueQuadrant = rand_range(4, 255);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.HueQuadrant = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CADJ_CAdjAttr_HueQuadrant(void)
{
	reg_api_test_fn(test_CADJ_CAdjAttr_HueQuadrant);
}

static int test_CADJ_CAdjAttr_Sat2SatEnable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CADJ_ATTR_S attr;

	ret = CVI_ISP_GetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAdjAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.Sat2SatEnable != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.Sat2SatEnable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.Sat2SatEnable = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "Sat2SatEnable", "min");
	// set maximum value
	attr.Sat2SatEnable = 1;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "Sat2SatEnable", "max");
	// set random value
	attr.Sat2SatEnable = rand_range(0, 1);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "Sat2SatEnable", "random");
	// restore default value
	attr.Sat2SatEnable = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CADJ_CAdjAttr_Sat2SatEnable(void)
{
	reg_api_test_fn(test_CADJ_CAdjAttr_Sat2SatEnable);
}

static int test_CADJ_CAdjAttr_Sat2SatGain(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CADJ_ATTR_S attr;

	ret = CVI_ISP_GetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAdjAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.Sat2SatGain != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.Sat2SatGain);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.Sat2SatGain = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "Sat2SatGain", "min");
	// set maximum value
	attr.Sat2SatGain = 255;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "Sat2SatGain", "max");
	// set random value
	attr.Sat2SatGain = rand_range(0, 255);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "Sat2SatGain", "random");
	// restore default value
	attr.Sat2SatGain = 128;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CADJ_CAdjAttr_Sat2SatGain(void)
{
	reg_api_test_fn(test_CADJ_CAdjAttr_Sat2SatGain);
}

static int test_CADJ_CAdjAttr_Sat2SatLut(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CADJ_ATTR_S attr;

	ret = CVI_ISP_GetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAdjAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val[17] = { 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128 };
	if (memcmp(default_val, attr.Sat2SatLut, sizeof(CVI_U8) * 17) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int i = 0; i < 17; ++i) {
		attr.Sat2SatLut[i] = 0;
	}
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "Sat2SatLut", "min");
	// set maximum value
	for (int i = 0; i < 17; ++i) {
		attr.Sat2SatLut[i] = 255;
	}
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "Sat2SatLut", "max");
	// set random value
	for (int i = 0; i < 17; i++) {
		attr.Sat2SatLut[i] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "Sat2SatLut", "random");
	// restore default value
	memcpy(attr.Sat2SatLut, default_val, sizeof(CVI_U8) * 17);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CADJ_CAdjAttr_Sat2SatLut(void)
{
	reg_api_test_fn(test_CADJ_CAdjAttr_Sat2SatLut);
}

static int test_CADJ_CAdjAttr_Luma2SatEnable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CADJ_ATTR_S attr;

	ret = CVI_ISP_GetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAdjAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.Luma2SatEnable != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.Luma2SatEnable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.Luma2SatEnable = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "Luma2SatEnable", "min");
	// set maximum value
	attr.Luma2SatEnable = 1;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "Luma2SatEnable", "max");
	// set random value
	attr.Luma2SatEnable = rand_range(0, 1);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "Luma2SatEnable", "random");
	// restore default value
	attr.Luma2SatEnable = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CADJ_CAdjAttr_Luma2SatEnable(void)
{
	reg_api_test_fn(test_CADJ_CAdjAttr_Luma2SatEnable);
}

static int test_CADJ_CAdjAttr_Luma2SatLut(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CADJ_ATTR_S attr;

	ret = CVI_ISP_GetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAdjAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val[17] = { 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128 };
	if (memcmp(default_val, attr.Luma2SatLut, sizeof(CVI_U8) * 17) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int i = 0; i < 17; ++i) {
		attr.Luma2SatLut[i] = 0;
	}
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "Luma2SatLut", "min");
	// set maximum value
	for (int i = 0; i < 17; ++i) {
		attr.Luma2SatLut[i] = 255;
	}
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "Luma2SatLut", "max");
	// set random value
	for (int i = 0; i < 17; i++) {
		attr.Luma2SatLut[i] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "Luma2SatLut", "random");
	// restore default value
	memcpy(attr.Luma2SatLut, default_val, sizeof(CVI_U8) * 17);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CADJ_CAdjAttr_Luma2SatLut(void)
{
	reg_api_test_fn(test_CADJ_CAdjAttr_Luma2SatLut);
}

static int test_CADJ_CAdjAttr_ColorProtectEnable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CADJ_ATTR_S attr;

	ret = CVI_ISP_GetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAdjAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.ColorProtectEnable != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.ColorProtectEnable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.ColorProtectEnable = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "ColorProtectEnable", "min");
	// set maximum value
	attr.ColorProtectEnable = 1;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "ColorProtectEnable", "max");
	// set random value
	attr.ColorProtectEnable = rand_range(0, 1);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "ColorProtectEnable", "random");
	// restore default value
	attr.ColorProtectEnable = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CADJ_CAdjAttr_ColorProtectEnable(void)
{
	reg_api_test_fn(test_CADJ_CAdjAttr_ColorProtectEnable);
}

static int test_CADJ_CAdjAttr_ColorProtectBlend(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CADJ_ATTR_S attr;

	ret = CVI_ISP_GetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAdjAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.ColorProtectBlend != 8) {
		TEST_FAIL("test default value: 8 != %d\n", (int)attr.ColorProtectBlend);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.ColorProtectBlend = 0;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "ColorProtectBlend", "min");
	// set maximum value
	attr.ColorProtectBlend = 16;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "ColorProtectBlend", "max");
	// set random value
	attr.ColorProtectBlend = rand_range(0, 16);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CADJ", "ColorProtectBlend", "random");
	// set abnormal value test
	attr.ColorProtectBlend = rand_range(17, 255);
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.ColorProtectBlend = 8;
	ret = CVI_ISP_SetCAdjAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CADJ_CAdjAttr_ColorProtectBlend(void)
{
	reg_api_test_fn(test_CADJ_CAdjAttr_ColorProtectBlend);
}
