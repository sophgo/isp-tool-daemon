
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

static int test_CCTRL_CCtrlAttr_Enable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CCTRL_ATTR_S attr;

	ret = CVI_ISP_GetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCCtrlAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.Enable != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.Enable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.Enable = 0;
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "Enable", "min");
	// set maximum value
	attr.Enable = 1;
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "Enable", "max");
	// set random value
	attr.Enable = rand_range(0, 1);
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "Enable", "random");
	// restore default value
	attr.Enable = 1;
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CCTRL_CCtrlAttr_Enable(void)
{
	reg_api_test_fn(test_CCTRL_CCtrlAttr_Enable);
}

static int test_CCTRL_CCtrlAttr_enOpType(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CCTRL_ATTR_S attr;

	ret = CVI_ISP_GetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCCtrlAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.enOpType != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.enOpType);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.enOpType = OP_TYPE_AUTO;
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "enOpType", "min");
	// set maximum value
	attr.enOpType = OP_TYPE_MANUAL;
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "enOpType", "max");
	// restore default value
	attr.enOpType = 0;
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CCTRL_CCtrlAttr_enOpType(void)
{
	reg_api_test_fn(test_CCTRL_CCtrlAttr_enOpType);
}

static int test_CCTRL_CCtrlAttr_UpdateInterval(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CCTRL_ATTR_S attr;

	ret = CVI_ISP_GetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCCtrlAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.UpdateInterval != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.UpdateInterval);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.UpdateInterval = 1;
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "UpdateInterval", "min");
	// set maximum value
	attr.UpdateInterval = 255;
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "UpdateInterval", "max");
	// set random value
	attr.UpdateInterval = rand_range(1, 255);
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "UpdateInterval", "random");
	// set abnormal value test
	attr.UpdateInterval = rand_range(0, 0);
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.UpdateInterval = 1;
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CCTRL_CCtrlAttr_UpdateInterval(void)
{
	reg_api_test_fn(test_CCTRL_CCtrlAttr_UpdateInterval);
}

static int test_CCTRL_CCtrlAttr_FalseColorSuppressionEnable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CCTRL_ATTR_S attr;

	ret = CVI_ISP_GetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCCtrlAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.FalseColorSuppressionEnable != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.FalseColorSuppressionEnable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.FalseColorSuppressionEnable = 0;
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "FalseColorSuppressionEnable", "min");
	// set maximum value
	attr.FalseColorSuppressionEnable = 1;
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "FalseColorSuppressionEnable", "max");
	// set random value
	attr.FalseColorSuppressionEnable = rand_range(0, 1);
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "FalseColorSuppressionEnable", "random");
	// restore default value
	attr.FalseColorSuppressionEnable = 0;
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CCTRL_CCtrlAttr_FalseColorSuppressionEnable(void)
{
	reg_api_test_fn(test_CCTRL_CCtrlAttr_FalseColorSuppressionEnable);
}

static int test_CCTRL_CCtrlAttr_EdgeGain(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CCTRL_ATTR_S attr;

	ret = CVI_ISP_GetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCCtrlAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.EdgeGain != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.EdgeGain);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.EdgeGain = 0;
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "EdgeGain", "min");
	// set maximum value
	attr.EdgeGain = 255;
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "EdgeGain", "max");
	// set random value
	attr.EdgeGain = rand_range(0, 255);
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "EdgeGain", "random");
	// restore default value
	attr.EdgeGain = 128;
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CCTRL_CCtrlAttr_EdgeGain(void)
{
	reg_api_test_fn(test_CCTRL_CCtrlAttr_EdgeGain);
}

static int test_CCTRL_CCtrlAttr_EdgeThr(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CCTRL_ATTR_S attr;

	ret = CVI_ISP_GetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCCtrlAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.EdgeThr != 32) {
		TEST_FAIL("test default value: 32 != %d\n", (int)attr.EdgeThr);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.EdgeThr = 0;
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "EdgeThr", "min");
	// set maximum value
	attr.EdgeThr = 1023;
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "EdgeThr", "max");
	// set random value
	attr.EdgeThr = rand_range(0, 1023);
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "EdgeThr", "random");
	// set abnormal value test
	attr.EdgeThr = rand_range(1024, 65535);
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.EdgeThr = 32;
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CCTRL_CCtrlAttr_EdgeThr(void)
{
	reg_api_test_fn(test_CCTRL_CCtrlAttr_EdgeThr);
}

static int test_CCTRL_CCtrlAttr_Hue2Hue(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CCTRL_ATTR_S attr;

	ret = CVI_ISP_GetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCCtrlAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val[24] = { 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128 };
	if (memcmp(default_val, attr.Hue2Hue, sizeof(CVI_U8) * 24) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int i = 0; i < 24; ++i) {
		attr.Hue2Hue[i] = 0;
	}
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "Hue2Hue", "min");
	// set maximum value
	for (int i = 0; i < 24; ++i) {
		attr.Hue2Hue[i] = 255;
	}
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "Hue2Hue", "max");
	// set random value
	for (int i = 0; i < 24; i++) {
		attr.Hue2Hue[i] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "Hue2Hue", "random");
	// restore default value
	memcpy(attr.Hue2Hue, default_val, sizeof(CVI_U8) * 24);
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CCTRL_CCtrlAttr_Hue2Hue(void)
{
	reg_api_test_fn(test_CCTRL_CCtrlAttr_Hue2Hue);
}

static int test_CCTRL_CCtrlAttr_Hue2Sat(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CCTRL_ATTR_S attr;

	ret = CVI_ISP_GetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCCtrlAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val[24] = { 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128 };
	if (memcmp(default_val, attr.Hue2Sat, sizeof(CVI_U8) * 24) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int i = 0; i < 24; ++i) {
		attr.Hue2Sat[i] = 0;
	}
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "Hue2Sat", "min");
	// set maximum value
	for (int i = 0; i < 24; ++i) {
		attr.Hue2Sat[i] = 255;
	}
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "Hue2Sat", "max");
	// set random value
	for (int i = 0; i < 24; i++) {
		attr.Hue2Sat[i] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "Hue2Sat", "random");
	// restore default value
	memcpy(attr.Hue2Sat, default_val, sizeof(CVI_U8) * 24);
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CCTRL_CCtrlAttr_Hue2Sat(void)
{
	reg_api_test_fn(test_CCTRL_CCtrlAttr_Hue2Sat);
}

static int test_CCTRL_CCtrlAttr_Hue2Int(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CCTRL_ATTR_S attr;

	ret = CVI_ISP_GetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCCtrlAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_S8 default_val[24] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	if (memcmp(default_val, attr.Hue2Int, sizeof(CVI_S8) * 24) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int i = 0; i < 24; ++i) {
		attr.Hue2Int[i] = -128;
	}
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "Hue2Int", "min");
	// set maximum value
	for (int i = 0; i < 24; ++i) {
		attr.Hue2Int[i] = 127;
	}
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "Hue2Int", "max");
	// set random value
	for (int i = 0; i < 24; i++) {
		attr.Hue2Int[i] = rand_range(-128, 127);
	}
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "Hue2Int", "random");
	// restore default value
	memcpy(attr.Hue2Int, default_val, sizeof(CVI_S8) * 24);
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CCTRL_CCtrlAttr_Hue2Int(void)
{
	reg_api_test_fn(test_CCTRL_CCtrlAttr_Hue2Int);
}

static int test_CCTRL_CCtrlAttr_Hue2Edg(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CCTRL_ATTR_S attr;

	ret = CVI_ISP_GetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCCtrlAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val[24] = { 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128 };
	if (memcmp(default_val, attr.Hue2Edg, sizeof(CVI_U8) * 24) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int i = 0; i < 24; ++i) {
		attr.Hue2Edg[i] = 0;
	}
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "Hue2Edg", "min");
	// set maximum value
	for (int i = 0; i < 24; ++i) {
		attr.Hue2Edg[i] = 255;
	}
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "Hue2Edg", "max");
	// set random value
	for (int i = 0; i < 24; i++) {
		attr.Hue2Edg[i] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "Hue2Edg", "random");
	// restore default value
	memcpy(attr.Hue2Edg, default_val, sizeof(CVI_U8) * 24);
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CCTRL_CCtrlAttr_Hue2Edg(void)
{
	reg_api_test_fn(test_CCTRL_CCtrlAttr_Hue2Edg);
}

static int test_CCTRL_CCtrlAttr_FcsHue(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CCTRL_ATTR_S attr;

	ret = CVI_ISP_GetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCCtrlAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val[24] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	if (memcmp(default_val, attr.FcsHue, sizeof(CVI_U8) * 24) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int i = 0; i < 24; ++i) {
		attr.FcsHue[i] = 0;
	}
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "FcsHue", "min");
	// set maximum value
	for (int i = 0; i < 24; ++i) {
		attr.FcsHue[i] = 255;
	}
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "FcsHue", "max");
	// set random value
	for (int i = 0; i < 24; i++) {
		attr.FcsHue[i] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "FcsHue", "random");
	// restore default value
	memcpy(attr.FcsHue, default_val, sizeof(CVI_U8) * 24);
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CCTRL_CCtrlAttr_FcsHue(void)
{
	reg_api_test_fn(test_CCTRL_CCtrlAttr_FcsHue);
}

static int test_CCTRL_CCtrlAttr_Chroma(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CCTRL_ATTR_S attr;

	ret = CVI_ISP_GetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCCtrlAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val[8] = { 32, 32, 32, 32, 32, 32, 32, 32 };
	if (memcmp(default_val, attr.Chroma, sizeof(CVI_U8) * 8) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int i = 0; i < 8; ++i) {
		attr.Chroma[i] = 0;
	}
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "Chroma", "min");
	// set maximum value
	for (int i = 0; i < 8; ++i) {
		attr.Chroma[i] = 255;
	}
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "Chroma", "max");
	// set random value
	for (int i = 0; i < 8; i++) {
		attr.Chroma[i] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CCTRL", "Chroma", "random");
	// restore default value
	memcpy(attr.Chroma, default_val, sizeof(CVI_U8) * 8);
	ret = CVI_ISP_SetCCtrlAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CCTRL_CCtrlAttr_Chroma(void)
{
	reg_api_test_fn(test_CCTRL_CCtrlAttr_Chroma);
}
