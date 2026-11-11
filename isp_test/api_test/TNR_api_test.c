
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

static int test_TNR_TNRAttr_Enable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_ATTR_S attr;

	ret = CVI_ISP_GetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.Enable != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.Enable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.Enable = 0;
	ret = CVI_ISP_SetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "Enable", "min");
	// set maximum value
	attr.Enable = 1;
	ret = CVI_ISP_SetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "Enable", "max");
	// set random value
	attr.Enable = rand_range(0, 1);
	ret = CVI_ISP_SetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "Enable", "random");
	// restore default value
	attr.Enable = 1;
	ret = CVI_ISP_SetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRAttr_Enable(void)
{
	reg_api_test_fn(test_TNR_TNRAttr_Enable);
}

static int test_TNR_TNRAttr_UpdateInterval(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_ATTR_S attr;

	ret = CVI_ISP_GetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.UpdateInterval != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.UpdateInterval);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.UpdateInterval = 1;
	ret = CVI_ISP_SetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "UpdateInterval", "min");
	// set maximum value
	attr.UpdateInterval = 255;
	ret = CVI_ISP_SetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "UpdateInterval", "max");
	// set random value
	attr.UpdateInterval = rand_range(1, 255);
	ret = CVI_ISP_SetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "UpdateInterval", "random");
	// set abnormal value test
	attr.UpdateInterval = rand_range(0, 0);
	ret = CVI_ISP_SetTNRAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.UpdateInterval = 1;
	ret = CVI_ISP_SetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRAttr_UpdateInterval(void)
{
	reg_api_test_fn(test_TNR_TNRAttr_UpdateInterval);
}

static int test_TNR_TNRAttr_enOpType(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_ATTR_S attr;

	ret = CVI_ISP_GetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.enOpType != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.enOpType);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.enOpType = OP_TYPE_AUTO;
	ret = CVI_ISP_SetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "enOpType", "min");
	// set maximum value
	attr.enOpType = OP_TYPE_MANUAL;
	ret = CVI_ISP_SetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "enOpType", "max");
	// restore default value
	attr.enOpType = 0;
	ret = CVI_ISP_SetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRAttr_enOpType(void)
{
	reg_api_test_fn(test_TNR_TNRAttr_enOpType);
}

static int test_TNR_TNRAttr_YNREnable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_ATTR_S attr;

	ret = CVI_ISP_GetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.YNREnable != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.YNREnable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.YNREnable = 0;
	ret = CVI_ISP_SetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YNREnable", "min");
	// set maximum value
	attr.YNREnable = 1;
	ret = CVI_ISP_SetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YNREnable", "max");
	// set random value
	attr.YNREnable = rand_range(0, 1);
	ret = CVI_ISP_SetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YNREnable", "random");
	// restore default value
	attr.YNREnable = 1;
	ret = CVI_ISP_SetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRAttr_YNREnable(void)
{
	reg_api_test_fn(test_TNR_TNRAttr_YNREnable);
}

static int test_TNR_TNRAttr_CNREnable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_ATTR_S attr;

	ret = CVI_ISP_GetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.CNREnable != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.CNREnable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.CNREnable = 0;
	ret = CVI_ISP_SetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CNREnable", "min");
	// set maximum value
	attr.CNREnable = 1;
	ret = CVI_ISP_SetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CNREnable", "max");
	// set random value
	attr.CNREnable = rand_range(0, 1);
	ret = CVI_ISP_SetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CNREnable", "random");
	// restore default value
	attr.CNREnable = 1;
	ret = CVI_ISP_SetTNRAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRAttr_CNREnable(void)
{
	reg_api_test_fn(test_TNR_TNRAttr_CNREnable);
}

static int test_TNR_TNRMdAttr_DebugMoodeSel(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.DebugMoodeSel != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.DebugMoodeSel);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.DebugMoodeSel = 0;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "DebugMoodeSel", "min");
	// set maximum value
	attr.DebugMoodeSel = 3;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "DebugMoodeSel", "max");
	// set random value
	attr.DebugMoodeSel = rand_range(0, 3);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "DebugMoodeSel", "random");
	// set abnormal value test
	attr.DebugMoodeSel = rand_range(4, 255);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.DebugMoodeSel = 0;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_DebugMoodeSel(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_DebugMoodeSel);
}

static int test_TNR_TNRMdAttr_MotionFactorYLow_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.MotionFactorYLow != 8) {
		TEST_FAIL("test default value: 8 != %d\n", (int)attr.stManual.MotionFactorYLow);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.MotionFactorYLow = 0;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorYLow", "min");
	// set maximum value
	attr.stManual.MotionFactorYLow = 32;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorYLow", "max");
	// set random value
	attr.stManual.MotionFactorYLow = rand_range(0, 32);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorYLow", "random");
	// set abnormal value test
	attr.stManual.MotionFactorYLow = rand_range(33, 255);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.MotionFactorYLow = 8;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_MotionFactorYLow_manual(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_MotionFactorYLow_manual);
}

static int test_TNR_TNRMdAttr_MotionFactorYLow_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8 };
	if (memcmp(default_val_0, attr.stAuto.MotionFactorYLow, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionFactorYLow[j] = 0;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorYLow", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionFactorYLow[j] = 32;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorYLow", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionFactorYLow[j] = rand_range(0, 32);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorYLow", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionFactorYLow[j] = rand_range(33, 255);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8 };
	memcpy(attr.stAuto.MotionFactorYLow, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_MotionFactorYLow_auto(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_MotionFactorYLow_auto);
}

static int test_TNR_TNRMdAttr_MotionFactorYHigh_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.MotionFactorYHigh != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.MotionFactorYHigh);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.MotionFactorYHigh = 0;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorYHigh", "min");
	// set maximum value
	attr.stManual.MotionFactorYHigh = 32;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorYHigh", "max");
	// set random value
	attr.stManual.MotionFactorYHigh = rand_range(0, 32);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorYHigh", "random");
	// set abnormal value test
	attr.stManual.MotionFactorYHigh = rand_range(33, 255);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.MotionFactorYHigh = 16;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_MotionFactorYHigh_manual(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_MotionFactorYHigh_manual);
}

static int test_TNR_TNRMdAttr_MotionFactorYHigh_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	if (memcmp(default_val_0, attr.stAuto.MotionFactorYHigh, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionFactorYHigh[j] = 0;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorYHigh", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionFactorYHigh[j] = 32;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorYHigh", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionFactorYHigh[j] = rand_range(0, 32);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorYHigh", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionFactorYHigh[j] = rand_range(33, 255);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	memcpy(attr.stAuto.MotionFactorYHigh, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_MotionFactorYHigh_auto(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_MotionFactorYHigh_auto);
}

static int test_TNR_TNRMdAttr_MotionFactorCLow_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.MotionFactorCLow != 8) {
		TEST_FAIL("test default value: 8 != %d\n", (int)attr.stManual.MotionFactorCLow);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.MotionFactorCLow = 0;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorCLow", "min");
	// set maximum value
	attr.stManual.MotionFactorCLow = 32;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorCLow", "max");
	// set random value
	attr.stManual.MotionFactorCLow = rand_range(0, 32);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorCLow", "random");
	// set abnormal value test
	attr.stManual.MotionFactorCLow = rand_range(33, 255);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.MotionFactorCLow = 8;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_MotionFactorCLow_manual(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_MotionFactorCLow_manual);
}

static int test_TNR_TNRMdAttr_MotionFactorCLow_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8 };
	if (memcmp(default_val_0, attr.stAuto.MotionFactorCLow, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionFactorCLow[j] = 0;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorCLow", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionFactorCLow[j] = 32;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorCLow", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionFactorCLow[j] = rand_range(0, 32);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorCLow", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionFactorCLow[j] = rand_range(33, 255);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8 };
	memcpy(attr.stAuto.MotionFactorCLow, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_MotionFactorCLow_auto(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_MotionFactorCLow_auto);
}

static int test_TNR_TNRMdAttr_MotionFactorCHigh_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.MotionFactorCHigh != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.MotionFactorCHigh);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.MotionFactorCHigh = 0;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorCHigh", "min");
	// set maximum value
	attr.stManual.MotionFactorCHigh = 32;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorCHigh", "max");
	// set random value
	attr.stManual.MotionFactorCHigh = rand_range(0, 32);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorCHigh", "random");
	// set abnormal value test
	attr.stManual.MotionFactorCHigh = rand_range(33, 255);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.MotionFactorCHigh = 16;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_MotionFactorCHigh_manual(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_MotionFactorCHigh_manual);
}

static int test_TNR_TNRMdAttr_MotionFactorCHigh_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	if (memcmp(default_val_0, attr.stAuto.MotionFactorCHigh, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionFactorCHigh[j] = 0;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorCHigh", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionFactorCHigh[j] = 32;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorCHigh", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionFactorCHigh[j] = rand_range(0, 32);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionFactorCHigh", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionFactorCHigh[j] = rand_range(33, 255);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	memcpy(attr.stAuto.MotionFactorCHigh, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_MotionFactorCHigh_auto(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_MotionFactorCHigh_auto);
}

static int test_TNR_TNRMdAttr_SadBlurStrengthY_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.SadBlurStrengthY != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.stManual.SadBlurStrengthY);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.SadBlurStrengthY = 0;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "SadBlurStrengthY", "min");
	// set maximum value
	attr.stManual.SadBlurStrengthY =  2;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "SadBlurStrengthY", "max");
	// set random value
	attr.stManual.SadBlurStrengthY = rand_range(0,  2);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "SadBlurStrengthY", "random");
	// set abnormal value test
	attr.stManual.SadBlurStrengthY = rand_range(3, 255);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.SadBlurStrengthY = 1;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_SadBlurStrengthY_manual(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_SadBlurStrengthY_manual);
}

static int test_TNR_TNRMdAttr_SadBlurStrengthY_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	if (memcmp(default_val_0, attr.stAuto.SadBlurStrengthY, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SadBlurStrengthY[j] = 0;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "SadBlurStrengthY", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SadBlurStrengthY[j] = 2;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "SadBlurStrengthY", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SadBlurStrengthY[j] = rand_range(0, 2);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "SadBlurStrengthY", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SadBlurStrengthY[j] = rand_range(3, 255);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	memcpy(attr.stAuto.SadBlurStrengthY, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_SadBlurStrengthY_auto(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_SadBlurStrengthY_auto);
}

static int test_TNR_TNRMdAttr_NoiseModelYA_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.NoiseModelYA[0] != 31) {
		TEST_FAIL("test default value: 31 != %d\n", (int)attr.stManual.NoiseModelYA[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYA[1] != 31) {
		TEST_FAIL("test default value: 31 != %d\n", (int)attr.stManual.NoiseModelYA[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYA[2] != 31) {
		TEST_FAIL("test default value: 31 != %d\n", (int)attr.stManual.NoiseModelYA[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYA[3] != 31) {
		TEST_FAIL("test default value: 31 != %d\n", (int)attr.stManual.NoiseModelYA[3]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYA[4] != 31) {
		TEST_FAIL("test default value: 31 != %d\n", (int)attr.stManual.NoiseModelYA[4]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYA[5] != 31) {
		TEST_FAIL("test default value: 31 != %d\n", (int)attr.stManual.NoiseModelYA[5]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYA[6] != 31) {
		TEST_FAIL("test default value: 31 != %d\n", (int)attr.stManual.NoiseModelYA[6]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYA[7] != 28) {
		TEST_FAIL("test default value: 28 != %d\n", (int)attr.stManual.NoiseModelYA[7]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.NoiseModelYA[0] = 0;
	attr.stManual.NoiseModelYA[1] = 0;
	attr.stManual.NoiseModelYA[2] = 0;
	attr.stManual.NoiseModelYA[3] = 0;
	attr.stManual.NoiseModelYA[4] = 0;
	attr.stManual.NoiseModelYA[5] = 0;
	attr.stManual.NoiseModelYA[6] = 0;
	attr.stManual.NoiseModelYA[7] = 0;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYA", "min");
	// set maximum value
	attr.stManual.NoiseModelYA[0] = 48;
	attr.stManual.NoiseModelYA[1] = 48;
	attr.stManual.NoiseModelYA[2] = 48;
	attr.stManual.NoiseModelYA[3] = 48;
	attr.stManual.NoiseModelYA[4] = 48;
	attr.stManual.NoiseModelYA[5] = 48;
	attr.stManual.NoiseModelYA[6] = 48;
	attr.stManual.NoiseModelYA[7] = 48;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYA", "max");
	// set random value
	attr.stManual.NoiseModelYA[0] = rand_range(0, 48);
	attr.stManual.NoiseModelYA[1] = rand_range(0, 48);
	attr.stManual.NoiseModelYA[2] = rand_range(0, 48);
	attr.stManual.NoiseModelYA[3] = rand_range(0, 48);
	attr.stManual.NoiseModelYA[4] = rand_range(0, 48);
	attr.stManual.NoiseModelYA[5] = rand_range(0, 48);
	attr.stManual.NoiseModelYA[6] = rand_range(0, 48);
	attr.stManual.NoiseModelYA[7] = rand_range(0, 48);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYA", "random");
	// set abnormal value test
	attr.stManual.NoiseModelYA[0] = rand_range(49, 255);
	attr.stManual.NoiseModelYA[1] = rand_range(49, 255);
	attr.stManual.NoiseModelYA[2] = rand_range(49, 255);
	attr.stManual.NoiseModelYA[3] = rand_range(49, 255);
	attr.stManual.NoiseModelYA[4] = rand_range(49, 255);
	attr.stManual.NoiseModelYA[5] = rand_range(49, 255);
	attr.stManual.NoiseModelYA[6] = rand_range(49, 255);
	attr.stManual.NoiseModelYA[7] = rand_range(49, 255);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.NoiseModelYA[0] = 31;
	attr.stManual.NoiseModelYA[1] = 31;
	attr.stManual.NoiseModelYA[2] = 31;
	attr.stManual.NoiseModelYA[3] = 31;
	attr.stManual.NoiseModelYA[4] = 31;
	attr.stManual.NoiseModelYA[5] = 31;
	attr.stManual.NoiseModelYA[6] = 31;
	attr.stManual.NoiseModelYA[7] = 28;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_NoiseModelYA_manual(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_NoiseModelYA_manual);
}

static int test_TNR_TNRMdAttr_NoiseModelYA_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYA[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYA[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYA[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYA[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYA[j][4] != default_val_4[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYA[j][5] != default_val_5[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYA[j][6] != default_val_6[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYA[j][7] != default_val_7[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][3] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][4] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][5] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][6] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][7] = 0;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYA", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][0] = 48;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][1] = 48;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][2] = 48;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][3] = 48;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][4] = 48;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][5] = 48;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][6] = 48;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][7] = 48;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYA", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][0] = rand_range(0, 48);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][1] = rand_range(0, 48);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][2] = rand_range(0, 48);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][3] = rand_range(0, 48);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][4] = rand_range(0, 48);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][5] = rand_range(0, 48);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][6] = rand_range(0, 48);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][7] = rand_range(0, 48);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYA", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][0] = rand_range(49, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][1] = rand_range(49, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][2] = rand_range(49, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][3] = rand_range(49, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][4] = rand_range(49, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][5] = rand_range(49, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][6] = rand_range(49, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][7] = rand_range(49, 255);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][0] = restore_val_0[j];
	}
	CVI_U8 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][1] = restore_val_1[j];
	}
	CVI_U8 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][2] = restore_val_2[j];
	}
	CVI_U8 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][3] = restore_val_3[j];
	}
	CVI_U8 restore_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][4] = restore_val_4[j];
	}
	CVI_U8 restore_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][5] = restore_val_5[j];
	}
	CVI_U8 restore_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][6] = restore_val_6[j];
	}
	CVI_U8 restore_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYA[j][7] = restore_val_7[j];
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_NoiseModelYA_auto(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_NoiseModelYA_auto);
}

static int test_TNR_TNRMdAttr_NoiseModelYB_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.NoiseModelYB[0] != 698) {
		TEST_FAIL("test default value: 698 != %d\n", (int)attr.stManual.NoiseModelYB[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYB[1] != 676) {
		TEST_FAIL("test default value: 676 != %d\n", (int)attr.stManual.NoiseModelYB[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYB[2] != 744) {
		TEST_FAIL("test default value: 744 != %d\n", (int)attr.stManual.NoiseModelYB[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYB[3] != 820) {
		TEST_FAIL("test default value: 820 != %d\n", (int)attr.stManual.NoiseModelYB[3]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYB[4] != 909) {
		TEST_FAIL("test default value: 909 != %d\n", (int)attr.stManual.NoiseModelYB[4]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYB[5] != 826) {
		TEST_FAIL("test default value: 826 != %d\n", (int)attr.stManual.NoiseModelYB[5]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYB[6] != 798) {
		TEST_FAIL("test default value: 798 != %d\n", (int)attr.stManual.NoiseModelYB[6]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYB[7] != 669) {
		TEST_FAIL("test default value: 669 != %d\n", (int)attr.stManual.NoiseModelYB[7]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.NoiseModelYB[0] = 0;
	attr.stManual.NoiseModelYB[1] = 0;
	attr.stManual.NoiseModelYB[2] = 0;
	attr.stManual.NoiseModelYB[3] = 0;
	attr.stManual.NoiseModelYB[4] = 0;
	attr.stManual.NoiseModelYB[5] = 0;
	attr.stManual.NoiseModelYB[6] = 0;
	attr.stManual.NoiseModelYB[7] = 0;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYB", "min");
	// set maximum value
	attr.stManual.NoiseModelYB[0] = 16320;
	attr.stManual.NoiseModelYB[1] = 16320;
	attr.stManual.NoiseModelYB[2] = 16320;
	attr.stManual.NoiseModelYB[3] = 16320;
	attr.stManual.NoiseModelYB[4] = 16320;
	attr.stManual.NoiseModelYB[5] = 16320;
	attr.stManual.NoiseModelYB[6] = 16320;
	attr.stManual.NoiseModelYB[7] = 16320;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYB", "max");
	// set random value
	attr.stManual.NoiseModelYB[0] = rand_range(0, 16320);
	attr.stManual.NoiseModelYB[1] = rand_range(0, 16320);
	attr.stManual.NoiseModelYB[2] = rand_range(0, 16320);
	attr.stManual.NoiseModelYB[3] = rand_range(0, 16320);
	attr.stManual.NoiseModelYB[4] = rand_range(0, 16320);
	attr.stManual.NoiseModelYB[5] = rand_range(0, 16320);
	attr.stManual.NoiseModelYB[6] = rand_range(0, 16320);
	attr.stManual.NoiseModelYB[7] = rand_range(0, 16320);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYB", "random");
	// set abnormal value test
	attr.stManual.NoiseModelYB[0] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYB[1] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYB[2] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYB[3] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYB[4] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYB[5] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYB[6] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYB[7] = rand_range(16321, 65535);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.NoiseModelYB[0] = 698;
	attr.stManual.NoiseModelYB[1] = 676;
	attr.stManual.NoiseModelYB[2] = 744;
	attr.stManual.NoiseModelYB[3] = 820;
	attr.stManual.NoiseModelYB[4] = 909;
	attr.stManual.NoiseModelYB[5] = 826;
	attr.stManual.NoiseModelYB[6] = 798;
	attr.stManual.NoiseModelYB[7] = 669;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_NoiseModelYB_manual(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_NoiseModelYB_manual);
}

static int test_TNR_TNRMdAttr_NoiseModelYB_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U16 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 698,698,698,698,698,698,698,698,698,698,698,698,698,698,698,698 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYB[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 676,676,676,676,676,676,676,676,676,676,676,676,676,676,676,676 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYB[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 744,744,744,744,744,744,744,744,744,744,744,744,744,744,744,744 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYB[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 820,820,820,820,820,820,820,820,820,820,820,820,820,820,820,820 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYB[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 909,909,909,909,909,909,909,909,909,909,909,909,909,909,909,909 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYB[j][4] != default_val_4[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 826,826,826,826,826,826,826,826,826,826,826,826,826,826,826,826 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYB[j][5] != default_val_5[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 798,798,798,798,798,798,798,798,798,798,798,798,798,798,798,798 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYB[j][6] != default_val_6[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 669,669,669,669,669,669,669,669,669,669,669,669,669,669,669,669 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYB[j][7] != default_val_7[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][3] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][4] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][5] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][6] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][7] = 0;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYB", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][0] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][1] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][2] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][3] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][4] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][5] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][6] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][7] = 16320;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYB", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][0] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][1] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][2] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][3] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][4] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][5] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][6] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][7] = rand_range(0, 16320);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYB", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][0] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][1] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][2] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][3] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][4] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][5] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][6] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][7] = rand_range(16321, 65535);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U16 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 698,698,698,698,698,698,698,698,698,698,698,698,698,698,698,698 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][0] = restore_val_0[j];
	}
	CVI_U16 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 676,676,676,676,676,676,676,676,676,676,676,676,676,676,676,676 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][1] = restore_val_1[j];
	}
	CVI_U16 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 744,744,744,744,744,744,744,744,744,744,744,744,744,744,744,744 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][2] = restore_val_2[j];
	}
	CVI_U16 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 820,820,820,820,820,820,820,820,820,820,820,820,820,820,820,820 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][3] = restore_val_3[j];
	}
	CVI_U16 restore_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 909,909,909,909,909,909,909,909,909,909,909,909,909,909,909,909 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][4] = restore_val_4[j];
	}
	CVI_U16 restore_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 826,826,826,826,826,826,826,826,826,826,826,826,826,826,826,826 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][5] = restore_val_5[j];
	}
	CVI_U16 restore_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 798,798,798,798,798,798,798,798,798,798,798,798,798,798,798,798 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][6] = restore_val_6[j];
	}
	CVI_U16 restore_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 669,669,669,669,669,669,669,669,669,669,669,669,669,669,669,669 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYB[j][7] = restore_val_7[j];
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_NoiseModelYB_auto(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_NoiseModelYB_auto);
}

static int test_TNR_TNRMdAttr_NoiseModelYStd_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.NoiseModelYStd[0] != 118) {
		TEST_FAIL("test default value: 118 != %d\n", (int)attr.stManual.NoiseModelYStd[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYStd[1] != 113) {
		TEST_FAIL("test default value: 113 != %d\n", (int)attr.stManual.NoiseModelYStd[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYStd[2] != 126) {
		TEST_FAIL("test default value: 126 != %d\n", (int)attr.stManual.NoiseModelYStd[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYStd[3] != 139) {
		TEST_FAIL("test default value: 139 != %d\n", (int)attr.stManual.NoiseModelYStd[3]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYStd[4] != 133) {
		TEST_FAIL("test default value: 133 != %d\n", (int)attr.stManual.NoiseModelYStd[4]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYStd[5] != 129) {
		TEST_FAIL("test default value: 129 != %d\n", (int)attr.stManual.NoiseModelYStd[5]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYStd[6] != 121) {
		TEST_FAIL("test default value: 121 != %d\n", (int)attr.stManual.NoiseModelYStd[6]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYStd[7] != 161) {
		TEST_FAIL("test default value: 161 != %d\n", (int)attr.stManual.NoiseModelYStd[7]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.NoiseModelYStd[0] = 0;
	attr.stManual.NoiseModelYStd[1] = 0;
	attr.stManual.NoiseModelYStd[2] = 0;
	attr.stManual.NoiseModelYStd[3] = 0;
	attr.stManual.NoiseModelYStd[4] = 0;
	attr.stManual.NoiseModelYStd[5] = 0;
	attr.stManual.NoiseModelYStd[6] = 0;
	attr.stManual.NoiseModelYStd[7] = 0;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYStd", "min");
	// set maximum value
	attr.stManual.NoiseModelYStd[0] = 16320;
	attr.stManual.NoiseModelYStd[1] = 16320;
	attr.stManual.NoiseModelYStd[2] = 16320;
	attr.stManual.NoiseModelYStd[3] = 16320;
	attr.stManual.NoiseModelYStd[4] = 16320;
	attr.stManual.NoiseModelYStd[5] = 16320;
	attr.stManual.NoiseModelYStd[6] = 16320;
	attr.stManual.NoiseModelYStd[7] = 16320;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYStd", "max");
	// set random value
	attr.stManual.NoiseModelYStd[0] = rand_range(0, 16320);
	attr.stManual.NoiseModelYStd[1] = rand_range(0, 16320);
	attr.stManual.NoiseModelYStd[2] = rand_range(0, 16320);
	attr.stManual.NoiseModelYStd[3] = rand_range(0, 16320);
	attr.stManual.NoiseModelYStd[4] = rand_range(0, 16320);
	attr.stManual.NoiseModelYStd[5] = rand_range(0, 16320);
	attr.stManual.NoiseModelYStd[6] = rand_range(0, 16320);
	attr.stManual.NoiseModelYStd[7] = rand_range(0, 16320);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYStd", "random");
	// set abnormal value test
	attr.stManual.NoiseModelYStd[0] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYStd[1] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYStd[2] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYStd[3] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYStd[4] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYStd[5] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYStd[6] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYStd[7] = rand_range(16321, 65535);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.NoiseModelYStd[0] = 118;
	attr.stManual.NoiseModelYStd[1] = 113;
	attr.stManual.NoiseModelYStd[2] = 126;
	attr.stManual.NoiseModelYStd[3] = 139;
	attr.stManual.NoiseModelYStd[4] = 133;
	attr.stManual.NoiseModelYStd[5] = 129;
	attr.stManual.NoiseModelYStd[6] = 121;
	attr.stManual.NoiseModelYStd[7] = 161;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_NoiseModelYStd_manual(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_NoiseModelYStd_manual);
}

static int test_TNR_TNRMdAttr_NoiseModelYStd_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U16 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYStd[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYStd[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYStd[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 139,139,139,139,139,139,139,139,139,139,139,139,139,139,139,139 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYStd[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYStd[j][4] != default_val_4[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYStd[j][5] != default_val_5[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYStd[j][6] != default_val_6[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 161,161,161,161,161,161,161,161,161,161,161,161,161,161,161,161 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYStd[j][7] != default_val_7[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][3] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][4] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][5] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][6] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][7] = 0;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYStd", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][0] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][1] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][2] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][3] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][4] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][5] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][6] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][7] = 16320;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYStd", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][0] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][1] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][2] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][3] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][4] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][5] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][6] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][7] = rand_range(0, 16320);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYStd", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][0] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][1] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][2] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][3] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][4] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][5] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][6] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][7] = rand_range(16321, 65535);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U16 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][0] = restore_val_0[j];
	}
	CVI_U16 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][1] = restore_val_1[j];
	}
	CVI_U16 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][2] = restore_val_2[j];
	}
	CVI_U16 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 139,139,139,139,139,139,139,139,139,139,139,139,139,139,139,139 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][3] = restore_val_3[j];
	}
	CVI_U16 restore_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][4] = restore_val_4[j];
	}
	CVI_U16 restore_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 129,129,129,129,129,129,129,129,129,129,129,129,129,129,129,129 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][5] = restore_val_5[j];
	}
	CVI_U16 restore_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][6] = restore_val_6[j];
	}
	CVI_U16 restore_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 161,161,161,161,161,161,161,161,161,161,161,161,161,161,161,161 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYStd[j][7] = restore_val_7[j];
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_NoiseModelYStd_auto(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_NoiseModelYStd_auto);
}

static int test_TNR_TNRMdAttr_NoiseModelUMean_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.NoiseModelUMean[0] != 270) {
		TEST_FAIL("test default value: 270 != %d\n", (int)attr.stManual.NoiseModelUMean[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelUMean[1] != 262) {
		TEST_FAIL("test default value: 262 != %d\n", (int)attr.stManual.NoiseModelUMean[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelUMean[2] != 260) {
		TEST_FAIL("test default value: 260 != %d\n", (int)attr.stManual.NoiseModelUMean[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelUMean[3] != 242) {
		TEST_FAIL("test default value: 242 != %d\n", (int)attr.stManual.NoiseModelUMean[3]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelUMean[4] != 212) {
		TEST_FAIL("test default value: 212 != %d\n", (int)attr.stManual.NoiseModelUMean[4]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelUMean[5] != 192) {
		TEST_FAIL("test default value: 192 != %d\n", (int)attr.stManual.NoiseModelUMean[5]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelUMean[6] != 175) {
		TEST_FAIL("test default value: 175 != %d\n", (int)attr.stManual.NoiseModelUMean[6]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelUMean[7] != 175) {
		TEST_FAIL("test default value: 175 != %d\n", (int)attr.stManual.NoiseModelUMean[7]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.NoiseModelUMean[0] = 0;
	attr.stManual.NoiseModelUMean[1] = 0;
	attr.stManual.NoiseModelUMean[2] = 0;
	attr.stManual.NoiseModelUMean[3] = 0;
	attr.stManual.NoiseModelUMean[4] = 0;
	attr.stManual.NoiseModelUMean[5] = 0;
	attr.stManual.NoiseModelUMean[6] = 0;
	attr.stManual.NoiseModelUMean[7] = 0;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelUMean", "min");
	// set maximum value
	attr.stManual.NoiseModelUMean[0] = 6375;
	attr.stManual.NoiseModelUMean[1] = 6375;
	attr.stManual.NoiseModelUMean[2] = 6375;
	attr.stManual.NoiseModelUMean[3] = 6375;
	attr.stManual.NoiseModelUMean[4] = 6375;
	attr.stManual.NoiseModelUMean[5] = 6375;
	attr.stManual.NoiseModelUMean[6] = 6375;
	attr.stManual.NoiseModelUMean[7] = 6375;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelUMean", "max");
	// set random value
	attr.stManual.NoiseModelUMean[0] = rand_range(0, 6375);
	attr.stManual.NoiseModelUMean[1] = rand_range(0, 6375);
	attr.stManual.NoiseModelUMean[2] = rand_range(0, 6375);
	attr.stManual.NoiseModelUMean[3] = rand_range(0, 6375);
	attr.stManual.NoiseModelUMean[4] = rand_range(0, 6375);
	attr.stManual.NoiseModelUMean[5] = rand_range(0, 6375);
	attr.stManual.NoiseModelUMean[6] = rand_range(0, 6375);
	attr.stManual.NoiseModelUMean[7] = rand_range(0, 6375);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelUMean", "random");
	// set abnormal value test
	attr.stManual.NoiseModelUMean[0] = rand_range(6376, 65535);
	attr.stManual.NoiseModelUMean[1] = rand_range(6376, 65535);
	attr.stManual.NoiseModelUMean[2] = rand_range(6376, 65535);
	attr.stManual.NoiseModelUMean[3] = rand_range(6376, 65535);
	attr.stManual.NoiseModelUMean[4] = rand_range(6376, 65535);
	attr.stManual.NoiseModelUMean[5] = rand_range(6376, 65535);
	attr.stManual.NoiseModelUMean[6] = rand_range(6376, 65535);
	attr.stManual.NoiseModelUMean[7] = rand_range(6376, 65535);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.NoiseModelUMean[0] = 270;
	attr.stManual.NoiseModelUMean[1] = 262;
	attr.stManual.NoiseModelUMean[2] = 260;
	attr.stManual.NoiseModelUMean[3] = 242;
	attr.stManual.NoiseModelUMean[4] = 212;
	attr.stManual.NoiseModelUMean[5] = 192;
	attr.stManual.NoiseModelUMean[6] = 175;
	attr.stManual.NoiseModelUMean[7] = 175;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_NoiseModelUMean_manual(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_NoiseModelUMean_manual);
}

static int test_TNR_TNRMdAttr_NoiseModelUMean_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U16 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 270,270,270,270,270,270,270,270,270,270,270,270,270,270,270,270 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelUMean[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 262,262,262,262,262,262,262,262,262,262,262,262,262,262,262,262 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelUMean[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 260,260,260,260,260,260,260,260,260,260,260,260,260,260,260,260 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelUMean[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelUMean[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 212,212,212,212,212,212,212,212,212,212,212,212,212,212,212,212 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelUMean[j][4] != default_val_4[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelUMean[j][5] != default_val_5[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 175,175,175,175,175,175,175,175,175,175,175,175,175,175,175,175 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelUMean[j][6] != default_val_6[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 175,175,175,175,175,175,175,175,175,175,175,175,175,175,175,175 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelUMean[j][7] != default_val_7[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][3] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][4] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][5] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][6] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][7] = 0;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelUMean", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][0] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][1] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][2] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][3] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][4] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][5] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][6] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][7] = 6375;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelUMean", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][0] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][1] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][2] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][3] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][4] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][5] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][6] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][7] = rand_range(0, 6375);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelUMean", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][0] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][1] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][2] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][3] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][4] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][5] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][6] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][7] = rand_range(6376, 65535);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U16 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 270,270,270,270,270,270,270,270,270,270,270,270,270,270,270,270 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][0] = restore_val_0[j];
	}
	CVI_U16 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 262,262,262,262,262,262,262,262,262,262,262,262,262,262,262,262 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][1] = restore_val_1[j];
	}
	CVI_U16 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 260,260,260,260,260,260,260,260,260,260,260,260,260,260,260,260 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][2] = restore_val_2[j];
	}
	CVI_U16 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 242,242,242,242,242,242,242,242,242,242,242,242,242,242,242,242 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][3] = restore_val_3[j];
	}
	CVI_U16 restore_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 212,212,212,212,212,212,212,212,212,212,212,212,212,212,212,212 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][4] = restore_val_4[j];
	}
	CVI_U16 restore_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][5] = restore_val_5[j];
	}
	CVI_U16 restore_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 175,175,175,175,175,175,175,175,175,175,175,175,175,175,175,175 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][6] = restore_val_6[j];
	}
	CVI_U16 restore_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 175,175,175,175,175,175,175,175,175,175,175,175,175,175,175,175 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUMean[j][7] = restore_val_7[j];
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_NoiseModelUMean_auto(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_NoiseModelUMean_auto);
}

static int test_TNR_TNRMdAttr_NoiseModelUStd_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.NoiseModelUStd[0] != 64) {
		TEST_FAIL("test default value: 64 != %d\n", (int)attr.stManual.NoiseModelUStd[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelUStd[1] != 61) {
		TEST_FAIL("test default value: 61 != %d\n", (int)attr.stManual.NoiseModelUStd[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelUStd[2] != 62) {
		TEST_FAIL("test default value: 62 != %d\n", (int)attr.stManual.NoiseModelUStd[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelUStd[3] != 59) {
		TEST_FAIL("test default value: 59 != %d\n", (int)attr.stManual.NoiseModelUStd[3]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelUStd[4] != 54) {
		TEST_FAIL("test default value: 54 != %d\n", (int)attr.stManual.NoiseModelUStd[4]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelUStd[5] != 49) {
		TEST_FAIL("test default value: 49 != %d\n", (int)attr.stManual.NoiseModelUStd[5]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelUStd[6] != 45) {
		TEST_FAIL("test default value: 45 != %d\n", (int)attr.stManual.NoiseModelUStd[6]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelUStd[7] != 45) {
		TEST_FAIL("test default value: 45 != %d\n", (int)attr.stManual.NoiseModelUStd[7]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.NoiseModelUStd[0] = 0;
	attr.stManual.NoiseModelUStd[1] = 0;
	attr.stManual.NoiseModelUStd[2] = 0;
	attr.stManual.NoiseModelUStd[3] = 0;
	attr.stManual.NoiseModelUStd[4] = 0;
	attr.stManual.NoiseModelUStd[5] = 0;
	attr.stManual.NoiseModelUStd[6] = 0;
	attr.stManual.NoiseModelUStd[7] = 0;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelUStd", "min");
	// set maximum value
	attr.stManual.NoiseModelUStd[0] = 6375;
	attr.stManual.NoiseModelUStd[1] = 6375;
	attr.stManual.NoiseModelUStd[2] = 6375;
	attr.stManual.NoiseModelUStd[3] = 6375;
	attr.stManual.NoiseModelUStd[4] = 6375;
	attr.stManual.NoiseModelUStd[5] = 6375;
	attr.stManual.NoiseModelUStd[6] = 6375;
	attr.stManual.NoiseModelUStd[7] = 6375;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelUStd", "max");
	// set random value
	attr.stManual.NoiseModelUStd[0] = rand_range(0, 6375);
	attr.stManual.NoiseModelUStd[1] = rand_range(0, 6375);
	attr.stManual.NoiseModelUStd[2] = rand_range(0, 6375);
	attr.stManual.NoiseModelUStd[3] = rand_range(0, 6375);
	attr.stManual.NoiseModelUStd[4] = rand_range(0, 6375);
	attr.stManual.NoiseModelUStd[5] = rand_range(0, 6375);
	attr.stManual.NoiseModelUStd[6] = rand_range(0, 6375);
	attr.stManual.NoiseModelUStd[7] = rand_range(0, 6375);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelUStd", "random");
	// set abnormal value test
	attr.stManual.NoiseModelUStd[0] = rand_range(6376, 65535);
	attr.stManual.NoiseModelUStd[1] = rand_range(6376, 65535);
	attr.stManual.NoiseModelUStd[2] = rand_range(6376, 65535);
	attr.stManual.NoiseModelUStd[3] = rand_range(6376, 65535);
	attr.stManual.NoiseModelUStd[4] = rand_range(6376, 65535);
	attr.stManual.NoiseModelUStd[5] = rand_range(6376, 65535);
	attr.stManual.NoiseModelUStd[6] = rand_range(6376, 65535);
	attr.stManual.NoiseModelUStd[7] = rand_range(6376, 65535);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.NoiseModelUStd[0] = 64;
	attr.stManual.NoiseModelUStd[1] = 61;
	attr.stManual.NoiseModelUStd[2] = 62;
	attr.stManual.NoiseModelUStd[3] = 59;
	attr.stManual.NoiseModelUStd[4] = 54;
	attr.stManual.NoiseModelUStd[5] = 49;
	attr.stManual.NoiseModelUStd[6] = 45;
	attr.stManual.NoiseModelUStd[7] = 45;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_NoiseModelUStd_manual(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_NoiseModelUStd_manual);
}

static int test_TNR_TNRMdAttr_NoiseModelUStd_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U16 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelUStd[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelUStd[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelUStd[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelUStd[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelUStd[j][4] != default_val_4[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelUStd[j][5] != default_val_5[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelUStd[j][6] != default_val_6[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelUStd[j][7] != default_val_7[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][3] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][4] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][5] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][6] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][7] = 0;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelUStd", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][0] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][1] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][2] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][3] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][4] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][5] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][6] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][7] = 6375;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelUStd", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][0] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][1] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][2] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][3] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][4] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][5] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][6] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][7] = rand_range(0, 6375);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelUStd", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][0] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][1] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][2] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][3] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][4] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][5] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][6] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][7] = rand_range(6376, 65535);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U16 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][0] = restore_val_0[j];
	}
	CVI_U16 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][1] = restore_val_1[j];
	}
	CVI_U16 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][2] = restore_val_2[j];
	}
	CVI_U16 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][3] = restore_val_3[j];
	}
	CVI_U16 restore_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][4] = restore_val_4[j];
	}
	CVI_U16 restore_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][5] = restore_val_5[j];
	}
	CVI_U16 restore_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][6] = restore_val_6[j];
	}
	CVI_U16 restore_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelUStd[j][7] = restore_val_7[j];
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_NoiseModelUStd_auto(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_NoiseModelUStd_auto);
}

static int test_TNR_TNRMdAttr_NoiseModelVMean_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.NoiseModelVMean[0] != 281) {
		TEST_FAIL("test default value: 281 != %d\n", (int)attr.stManual.NoiseModelVMean[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelVMean[1] != 293) {
		TEST_FAIL("test default value: 293 != %d\n", (int)attr.stManual.NoiseModelVMean[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelVMean[2] != 288) {
		TEST_FAIL("test default value: 288 != %d\n", (int)attr.stManual.NoiseModelVMean[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelVMean[3] != 250) {
		TEST_FAIL("test default value: 250 != %d\n", (int)attr.stManual.NoiseModelVMean[3]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelVMean[4] != 243) {
		TEST_FAIL("test default value: 243 != %d\n", (int)attr.stManual.NoiseModelVMean[4]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelVMean[5] != 208) {
		TEST_FAIL("test default value: 208 != %d\n", (int)attr.stManual.NoiseModelVMean[5]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelVMean[6] != 187) {
		TEST_FAIL("test default value: 187 != %d\n", (int)attr.stManual.NoiseModelVMean[6]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelVMean[7] != 187) {
		TEST_FAIL("test default value: 187 != %d\n", (int)attr.stManual.NoiseModelVMean[7]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.NoiseModelVMean[0] = 0;
	attr.stManual.NoiseModelVMean[1] = 0;
	attr.stManual.NoiseModelVMean[2] = 0;
	attr.stManual.NoiseModelVMean[3] = 0;
	attr.stManual.NoiseModelVMean[4] = 0;
	attr.stManual.NoiseModelVMean[5] = 0;
	attr.stManual.NoiseModelVMean[6] = 0;
	attr.stManual.NoiseModelVMean[7] = 0;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelVMean", "min");
	// set maximum value
	attr.stManual.NoiseModelVMean[0] = 6375;
	attr.stManual.NoiseModelVMean[1] = 6375;
	attr.stManual.NoiseModelVMean[2] = 6375;
	attr.stManual.NoiseModelVMean[3] = 6375;
	attr.stManual.NoiseModelVMean[4] = 6375;
	attr.stManual.NoiseModelVMean[5] = 6375;
	attr.stManual.NoiseModelVMean[6] = 6375;
	attr.stManual.NoiseModelVMean[7] = 6375;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelVMean", "max");
	// set random value
	attr.stManual.NoiseModelVMean[0] = rand_range(0, 6375);
	attr.stManual.NoiseModelVMean[1] = rand_range(0, 6375);
	attr.stManual.NoiseModelVMean[2] = rand_range(0, 6375);
	attr.stManual.NoiseModelVMean[3] = rand_range(0, 6375);
	attr.stManual.NoiseModelVMean[4] = rand_range(0, 6375);
	attr.stManual.NoiseModelVMean[5] = rand_range(0, 6375);
	attr.stManual.NoiseModelVMean[6] = rand_range(0, 6375);
	attr.stManual.NoiseModelVMean[7] = rand_range(0, 6375);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelVMean", "random");
	// set abnormal value test
	attr.stManual.NoiseModelVMean[0] = rand_range(6376, 65535);
	attr.stManual.NoiseModelVMean[1] = rand_range(6376, 65535);
	attr.stManual.NoiseModelVMean[2] = rand_range(6376, 65535);
	attr.stManual.NoiseModelVMean[3] = rand_range(6376, 65535);
	attr.stManual.NoiseModelVMean[4] = rand_range(6376, 65535);
	attr.stManual.NoiseModelVMean[5] = rand_range(6376, 65535);
	attr.stManual.NoiseModelVMean[6] = rand_range(6376, 65535);
	attr.stManual.NoiseModelVMean[7] = rand_range(6376, 65535);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.NoiseModelVMean[0] = 281;
	attr.stManual.NoiseModelVMean[1] = 293;
	attr.stManual.NoiseModelVMean[2] = 288;
	attr.stManual.NoiseModelVMean[3] = 250;
	attr.stManual.NoiseModelVMean[4] = 243;
	attr.stManual.NoiseModelVMean[5] = 208;
	attr.stManual.NoiseModelVMean[6] = 187;
	attr.stManual.NoiseModelVMean[7] = 187;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_NoiseModelVMean_manual(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_NoiseModelVMean_manual);
}

static int test_TNR_TNRMdAttr_NoiseModelVMean_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U16 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelVMean[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 293,293,293,293,293,293,293,293,293,293,293,293,293,293,293,293 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelVMean[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 288,288,288,288,288,288,288,288,288,288,288,288,288,288,288,288 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelVMean[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelVMean[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 243,243,243,243,243,243,243,243,243,243,243,243,243,243,243,243 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelVMean[j][4] != default_val_4[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelVMean[j][5] != default_val_5[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelVMean[j][6] != default_val_6[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelVMean[j][7] != default_val_7[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][3] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][4] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][5] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][6] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][7] = 0;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelVMean", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][0] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][1] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][2] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][3] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][4] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][5] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][6] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][7] = 6375;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelVMean", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][0] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][1] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][2] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][3] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][4] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][5] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][6] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][7] = rand_range(0, 6375);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelVMean", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][0] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][1] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][2] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][3] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][4] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][5] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][6] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][7] = rand_range(6376, 65535);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U16 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][0] = restore_val_0[j];
	}
	CVI_U16 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 293,293,293,293,293,293,293,293,293,293,293,293,293,293,293,293 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][1] = restore_val_1[j];
	}
	CVI_U16 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 288,288,288,288,288,288,288,288,288,288,288,288,288,288,288,288 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][2] = restore_val_2[j];
	}
	CVI_U16 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][3] = restore_val_3[j];
	}
	CVI_U16 restore_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 243,243,243,243,243,243,243,243,243,243,243,243,243,243,243,243 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][4] = restore_val_4[j];
	}
	CVI_U16 restore_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 208,208,208,208,208,208,208,208,208,208,208,208,208,208,208,208 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][5] = restore_val_5[j];
	}
	CVI_U16 restore_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][6] = restore_val_6[j];
	}
	CVI_U16 restore_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 187,187,187,187,187,187,187,187,187,187,187,187,187,187,187,187 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVMean[j][7] = restore_val_7[j];
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_NoiseModelVMean_auto(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_NoiseModelVMean_auto);
}

static int test_TNR_TNRMdAttr_NoiseModelVStd_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.NoiseModelVStd[0] != 62) {
		TEST_FAIL("test default value: 62 != %d\n", (int)attr.stManual.NoiseModelVStd[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelVStd[1] != 64) {
		TEST_FAIL("test default value: 64 != %d\n", (int)attr.stManual.NoiseModelVStd[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelVStd[2] != 67) {
		TEST_FAIL("test default value: 67 != %d\n", (int)attr.stManual.NoiseModelVStd[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelVStd[3] != 60) {
		TEST_FAIL("test default value: 60 != %d\n", (int)attr.stManual.NoiseModelVStd[3]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelVStd[4] != 60) {
		TEST_FAIL("test default value: 60 != %d\n", (int)attr.stManual.NoiseModelVStd[4]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelVStd[5] != 52) {
		TEST_FAIL("test default value: 52 != %d\n", (int)attr.stManual.NoiseModelVStd[5]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelVStd[6] != 43) {
		TEST_FAIL("test default value: 43 != %d\n", (int)attr.stManual.NoiseModelVStd[6]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelVStd[7] != 43) {
		TEST_FAIL("test default value: 43 != %d\n", (int)attr.stManual.NoiseModelVStd[7]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.NoiseModelVStd[0] = 0;
	attr.stManual.NoiseModelVStd[1] = 0;
	attr.stManual.NoiseModelVStd[2] = 0;
	attr.stManual.NoiseModelVStd[3] = 0;
	attr.stManual.NoiseModelVStd[4] = 0;
	attr.stManual.NoiseModelVStd[5] = 0;
	attr.stManual.NoiseModelVStd[6] = 0;
	attr.stManual.NoiseModelVStd[7] = 0;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelVStd", "min");
	// set maximum value
	attr.stManual.NoiseModelVStd[0] = 6375;
	attr.stManual.NoiseModelVStd[1] = 6375;
	attr.stManual.NoiseModelVStd[2] = 6375;
	attr.stManual.NoiseModelVStd[3] = 6375;
	attr.stManual.NoiseModelVStd[4] = 6375;
	attr.stManual.NoiseModelVStd[5] = 6375;
	attr.stManual.NoiseModelVStd[6] = 6375;
	attr.stManual.NoiseModelVStd[7] = 6375;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelVStd", "max");
	// set random value
	attr.stManual.NoiseModelVStd[0] = rand_range(0, 6375);
	attr.stManual.NoiseModelVStd[1] = rand_range(0, 6375);
	attr.stManual.NoiseModelVStd[2] = rand_range(0, 6375);
	attr.stManual.NoiseModelVStd[3] = rand_range(0, 6375);
	attr.stManual.NoiseModelVStd[4] = rand_range(0, 6375);
	attr.stManual.NoiseModelVStd[5] = rand_range(0, 6375);
	attr.stManual.NoiseModelVStd[6] = rand_range(0, 6375);
	attr.stManual.NoiseModelVStd[7] = rand_range(0, 6375);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelVStd", "random");
	// set abnormal value test
	attr.stManual.NoiseModelVStd[0] = rand_range(6376, 65535);
	attr.stManual.NoiseModelVStd[1] = rand_range(6376, 65535);
	attr.stManual.NoiseModelVStd[2] = rand_range(6376, 65535);
	attr.stManual.NoiseModelVStd[3] = rand_range(6376, 65535);
	attr.stManual.NoiseModelVStd[4] = rand_range(6376, 65535);
	attr.stManual.NoiseModelVStd[5] = rand_range(6376, 65535);
	attr.stManual.NoiseModelVStd[6] = rand_range(6376, 65535);
	attr.stManual.NoiseModelVStd[7] = rand_range(6376, 65535);
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.NoiseModelVStd[0] = 62;
	attr.stManual.NoiseModelVStd[1] = 64;
	attr.stManual.NoiseModelVStd[2] = 67;
	attr.stManual.NoiseModelVStd[3] = 60;
	attr.stManual.NoiseModelVStd[4] = 60;
	attr.stManual.NoiseModelVStd[5] = 52;
	attr.stManual.NoiseModelVStd[6] = 43;
	attr.stManual.NoiseModelVStd[7] = 43;
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_NoiseModelVStd_manual(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_NoiseModelVStd_manual);
}

static int test_TNR_TNRMdAttr_NoiseModelVStd_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_MD_ATTR_S attr;

	ret = CVI_ISP_GetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRMdAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U16 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelVStd[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelVStd[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 67,67,67,67,67,67,67,67,67,67,67,67,67,67,67,67 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelVStd[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelVStd[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelVStd[j][4] != default_val_4[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelVStd[j][5] != default_val_5[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelVStd[j][6] != default_val_6[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelVStd[j][7] != default_val_7[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][3] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][4] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][5] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][6] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][7] = 0;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelVStd", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][0] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][1] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][2] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][3] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][4] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][5] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][6] = 6375;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][7] = 6375;
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelVStd", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][0] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][1] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][2] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][3] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][4] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][5] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][6] = rand_range(0, 6375);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][7] = rand_range(0, 6375);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelVStd", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][0] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][1] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][2] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][3] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][4] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][5] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][6] = rand_range(6376, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][7] = rand_range(6376, 65535);
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U16 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][0] = restore_val_0[j];
	}
	CVI_U16 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][1] = restore_val_1[j];
	}
	CVI_U16 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 67,67,67,67,67,67,67,67,67,67,67,67,67,67,67,67 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][2] = restore_val_2[j];
	}
	CVI_U16 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][3] = restore_val_3[j];
	}
	CVI_U16 restore_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][4] = restore_val_4[j];
	}
	CVI_U16 restore_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][5] = restore_val_5[j];
	}
	CVI_U16 restore_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][6] = restore_val_6[j];
	}
	CVI_U16 restore_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelVStd[j][7] = restore_val_7[j];
	}
	ret = CVI_ISP_SetTNRMdAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRMdAttr_NoiseModelVStd_auto(void)
{
	reg_api_test_fn(test_TNR_TNRMdAttr_NoiseModelVStd_auto);
}

static int test_TNR_TNRNrAttr_MotionDspThresholdLow_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.MotionDspThresholdLow != 2) {
		TEST_FAIL("test default value: 2 != %d\n", (int)attr.stManual.MotionDspThresholdLow);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.MotionDspThresholdLow = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionDspThresholdLow", "min");
	// set maximum value
	attr.stManual.MotionDspThresholdLow =  8;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionDspThresholdLow", "max");
	// set random value
	attr.stManual.MotionDspThresholdLow = rand_range(0,  8);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionDspThresholdLow", "random");
	// set abnormal value test
	attr.stManual.MotionDspThresholdLow = rand_range(9, 255);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.MotionDspThresholdLow = 2;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_MotionDspThresholdLow_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_MotionDspThresholdLow_manual);
}

static int test_TNR_TNRNrAttr_MotionDspThresholdLow_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 };
	if (memcmp(default_val_0, attr.stAuto.MotionDspThresholdLow, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionDspThresholdLow[j] = 0;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionDspThresholdLow", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionDspThresholdLow[j] = 8;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionDspThresholdLow", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionDspThresholdLow[j] = rand_range(0, 8);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionDspThresholdLow", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionDspThresholdLow[j] = rand_range(9, 255);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 };
	memcpy(attr.stAuto.MotionDspThresholdLow, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_MotionDspThresholdLow_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_MotionDspThresholdLow_auto);
}

static int test_TNR_TNRNrAttr_MotionDspThresholdHigh_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.MotionDspThresholdHigh != 6) {
		TEST_FAIL("test default value: 6 != %d\n", (int)attr.stManual.MotionDspThresholdHigh);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.MotionDspThresholdHigh = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionDspThresholdHigh", "min");
	// set maximum value
	attr.stManual.MotionDspThresholdHigh =  8;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionDspThresholdHigh", "max");
	// set random value
	attr.stManual.MotionDspThresholdHigh = rand_range(0,  8);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionDspThresholdHigh", "random");
	// set abnormal value test
	attr.stManual.MotionDspThresholdHigh = rand_range(9, 255);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.MotionDspThresholdHigh = 6;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_MotionDspThresholdHigh_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_MotionDspThresholdHigh_manual);
}

static int test_TNR_TNRNrAttr_MotionDspThresholdHigh_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6 };
	if (memcmp(default_val_0, attr.stAuto.MotionDspThresholdHigh, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionDspThresholdHigh[j] = 0;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionDspThresholdHigh", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionDspThresholdHigh[j] = 8;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionDspThresholdHigh", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionDspThresholdHigh[j] = rand_range(0, 8);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "MotionDspThresholdHigh", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.MotionDspThresholdHigh[j] = rand_range(9, 255);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6 };
	memcpy(attr.stAuto.MotionDspThresholdHigh, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_MotionDspThresholdHigh_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_MotionDspThresholdHigh_auto);
}

static int test_TNR_TNRNrAttr_YnrStrength3D_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.YnrStrength3D != 8) {
		TEST_FAIL("test default value: 8 != %d\n", (int)attr.stManual.YnrStrength3D);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.YnrStrength3D = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrStrength3D", "min");
	// set maximum value
	attr.stManual.YnrStrength3D =  32;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrStrength3D", "max");
	// set random value
	attr.stManual.YnrStrength3D = rand_range(0,  32);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrStrength3D", "random");
	// set abnormal value test
	attr.stManual.YnrStrength3D = rand_range(33, 255);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.YnrStrength3D = 8;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_YnrStrength3D_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_YnrStrength3D_manual);
}

static int test_TNR_TNRNrAttr_YnrStrength3D_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8 };
	if (memcmp(default_val_0, attr.stAuto.YnrStrength3D, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrStrength3D[j] = 0;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrStrength3D", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrStrength3D[j] = 32;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrStrength3D", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrStrength3D[j] = rand_range(0, 32);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrStrength3D", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrStrength3D[j] = rand_range(33, 255);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8 };
	memcpy(attr.stAuto.YnrStrength3D, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_YnrStrength3D_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_YnrStrength3D_auto);
}

static int test_TNR_TNRNrAttr_YnrStrength2D_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.YnrStrength2D != 8) {
		TEST_FAIL("test default value: 8 != %d\n", (int)attr.stManual.YnrStrength2D);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.YnrStrength2D = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrStrength2D", "min");
	// set maximum value
	attr.stManual.YnrStrength2D = 32;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrStrength2D", "max");
	// set random value
	attr.stManual.YnrStrength2D = rand_range(0, 32);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrStrength2D", "random");
	// set abnormal value test
	attr.stManual.YnrStrength2D = rand_range(33, 255);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.YnrStrength2D = 8;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_YnrStrength2D_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_YnrStrength2D_manual);
}

static int test_TNR_TNRNrAttr_YnrStrength2D_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8 };
	if (memcmp(default_val_0, attr.stAuto.YnrStrength2D, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrStrength2D[j] = 0;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrStrength2D", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrStrength2D[j] = 32;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrStrength2D", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrStrength2D[j] = rand_range(0, 32);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrStrength2D", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrStrength2D[j] = rand_range(33, 255);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8 };
	memcpy(attr.stAuto.YnrStrength2D, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_YnrStrength2D_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_YnrStrength2D_auto);
}

static int test_TNR_TNRNrAttr_CnrStrength3D_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.CnrStrength3D != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.CnrStrength3D);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.CnrStrength3D = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrStrength3D", "min");
	// set maximum value
	attr.stManual.CnrStrength3D = 32;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrStrength3D", "max");
	// set random value
	attr.stManual.CnrStrength3D = rand_range(0, 32);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrStrength3D", "random");
	// set abnormal value test
	attr.stManual.CnrStrength3D = rand_range(33, 255);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.CnrStrength3D = 16;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_CnrStrength3D_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_CnrStrength3D_manual);
}

static int test_TNR_TNRNrAttr_CnrStrength3D_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	if (memcmp(default_val_0, attr.stAuto.CnrStrength3D, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrStrength3D[j] = 0;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrStrength3D", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrStrength3D[j] = 32;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrStrength3D", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrStrength3D[j] = rand_range(0, 32);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrStrength3D", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrStrength3D[j] = rand_range(33, 255);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	memcpy(attr.stAuto.CnrStrength3D, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_CnrStrength3D_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_CnrStrength3D_auto);
}

static int test_TNR_TNRNrAttr_CnrStrength2D_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.CnrStrength2D != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.CnrStrength2D);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.CnrStrength2D = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrStrength2D", "min");
	// set maximum value
	attr.stManual.CnrStrength2D = 32;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrStrength2D", "max");
	// set random value
	attr.stManual.CnrStrength2D = rand_range(0, 32);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrStrength2D", "random");
	// set abnormal value test
	attr.stManual.CnrStrength2D = rand_range(33, 255);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.CnrStrength2D = 16;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_CnrStrength2D_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_CnrStrength2D_manual);
}

static int test_TNR_TNRNrAttr_CnrStrength2D_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	if (memcmp(default_val_0, attr.stAuto.CnrStrength2D, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrStrength2D[j] = 0;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrStrength2D", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrStrength2D[j] = 32;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrStrength2D", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrStrength2D[j] = rand_range(0, 32);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrStrength2D", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrStrength2D[j] = rand_range(33, 255);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	memcpy(attr.stAuto.CnrStrength2D, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_CnrStrength2D_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_CnrStrength2D_auto);
}

static int test_TNR_TNRNrAttr_TdWeight_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.TdWeight != 8) {
		TEST_FAIL("test default value: 8 != %d\n", (int)attr.stManual.TdWeight);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.TdWeight = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "TdWeight", "min");
	// set maximum value
	attr.stManual.TdWeight = 16;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "TdWeight", "max");
	// set random value
	attr.stManual.TdWeight = rand_range(0, 16);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "TdWeight", "random");
	// set abnormal value test
	attr.stManual.TdWeight = rand_range(17, 255);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.TdWeight = 8;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_TdWeight_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_TdWeight_manual);
}

static int test_TNR_TNRNrAttr_TdWeight_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8 };
	if (memcmp(default_val_0, attr.stAuto.TdWeight, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.TdWeight[j] = 0;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "TdWeight", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.TdWeight[j] = 16;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "TdWeight", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.TdWeight[j] = rand_range(0, 16);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "TdWeight", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.TdWeight[j] = rand_range(17, 255);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8 };
	memcpy(attr.stAuto.TdWeight, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_TdWeight_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_TdWeight_auto);
}

static int test_TNR_TNRNrAttr_NoiseModelYBase_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.NoiseModelYBase[0] != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.stManual.NoiseModelYBase[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYBase[1] != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.stManual.NoiseModelYBase[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYBase[2] != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.stManual.NoiseModelYBase[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYBase[3] != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.stManual.NoiseModelYBase[3]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYBase[4] != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.stManual.NoiseModelYBase[4]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYBase[5] != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.stManual.NoiseModelYBase[5]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYBase[6] != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.stManual.NoiseModelYBase[6]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseModelYBase[7] != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.stManual.NoiseModelYBase[7]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.NoiseModelYBase[0] = 0;
	attr.stManual.NoiseModelYBase[1] = 0;
	attr.stManual.NoiseModelYBase[2] = 0;
	attr.stManual.NoiseModelYBase[3] = 0;
	attr.stManual.NoiseModelYBase[4] = 0;
	attr.stManual.NoiseModelYBase[5] = 0;
	attr.stManual.NoiseModelYBase[6] = 0;
	attr.stManual.NoiseModelYBase[7] = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYBase", "min");
	// set maximum value
	attr.stManual.NoiseModelYBase[0] = 16320;
	attr.stManual.NoiseModelYBase[1] = 16320;
	attr.stManual.NoiseModelYBase[2] = 16320;
	attr.stManual.NoiseModelYBase[3] = 16320;
	attr.stManual.NoiseModelYBase[4] = 16320;
	attr.stManual.NoiseModelYBase[5] = 16320;
	attr.stManual.NoiseModelYBase[6] = 16320;
	attr.stManual.NoiseModelYBase[7] = 16320;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYBase", "max");
	// set random value
	attr.stManual.NoiseModelYBase[0] = rand_range(0, 16320);
	attr.stManual.NoiseModelYBase[1] = rand_range(0, 16320);
	attr.stManual.NoiseModelYBase[2] = rand_range(0, 16320);
	attr.stManual.NoiseModelYBase[3] = rand_range(0, 16320);
	attr.stManual.NoiseModelYBase[4] = rand_range(0, 16320);
	attr.stManual.NoiseModelYBase[5] = rand_range(0, 16320);
	attr.stManual.NoiseModelYBase[6] = rand_range(0, 16320);
	attr.stManual.NoiseModelYBase[7] = rand_range(0, 16320);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYBase", "random");
	// set abnormal value test
	attr.stManual.NoiseModelYBase[0] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYBase[1] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYBase[2] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYBase[3] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYBase[4] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYBase[5] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYBase[6] = rand_range(16321, 65535);
	attr.stManual.NoiseModelYBase[7] = rand_range(16321, 65535);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.NoiseModelYBase[0] = 0;
	attr.stManual.NoiseModelYBase[1] = 0;
	attr.stManual.NoiseModelYBase[2] = 0;
	attr.stManual.NoiseModelYBase[3] = 0;
	attr.stManual.NoiseModelYBase[4] = 0;
	attr.stManual.NoiseModelYBase[5] = 0;
	attr.stManual.NoiseModelYBase[6] = 0;
	attr.stManual.NoiseModelYBase[7] = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_NoiseModelYBase_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_NoiseModelYBase_manual);
}

static int test_TNR_TNRNrAttr_NoiseModelYBase_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U16 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYBase[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYBase[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYBase[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYBase[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYBase[j][4] != default_val_4[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYBase[j][5] != default_val_5[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYBase[j][6] != default_val_6[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseModelYBase[j][7] != default_val_7[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][3] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][4] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][5] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][6] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][7] = 0;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYBase", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][0] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][1] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][2] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][3] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][4] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][5] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][6] = 16320;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][7] = 16320;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYBase", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][0] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][1] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][2] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][3] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][4] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][5] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][6] = rand_range(0, 16320);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][7] = rand_range(0, 16320);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "NoiseModelYBase", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][0] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][1] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][2] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][3] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][4] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][5] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][6] = rand_range(16321, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][7] = rand_range(16321, 65535);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U16 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][0] = restore_val_0[j];
	}
	CVI_U16 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][1] = restore_val_1[j];
	}
	CVI_U16 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][2] = restore_val_2[j];
	}
	CVI_U16 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][3] = restore_val_3[j];
	}
	CVI_U16 restore_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][4] = restore_val_4[j];
	}
	CVI_U16 restore_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][5] = restore_val_5[j];
	}
	CVI_U16 restore_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][6] = restore_val_6[j];
	}
	CVI_U16 restore_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseModelYBase[j][7] = restore_val_7[j];
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_NoiseModelYBase_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_NoiseModelYBase_auto);
}

static int test_TNR_TNRNrAttr_CenterWtExcludeY2DEnable_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.CenterWtExcludeY2DEnable != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.stManual.CenterWtExcludeY2DEnable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.CenterWtExcludeY2DEnable = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CenterWtExcludeY2DEnable", "min");
	// set maximum value
	attr.stManual.CenterWtExcludeY2DEnable = 1;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CenterWtExcludeY2DEnable", "max");
	// set random value
	attr.stManual.CenterWtExcludeY2DEnable = rand_range(0, 1);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CenterWtExcludeY2DEnable", "random");
	// restore default value
	attr.stManual.CenterWtExcludeY2DEnable = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_CenterWtExcludeY2DEnable_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_CenterWtExcludeY2DEnable_manual);
}

static int test_TNR_TNRNrAttr_CenterWtExcludeY2DEnable_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_BOOL default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	if (memcmp(default_val_0, attr.stAuto.CenterWtExcludeY2DEnable, sizeof(CVI_BOOL) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CenterWtExcludeY2DEnable[j] = 0;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CenterWtExcludeY2DEnable", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CenterWtExcludeY2DEnable[j] = 1;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CenterWtExcludeY2DEnable", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CenterWtExcludeY2DEnable[j] = rand_range(0, 1);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CenterWtExcludeY2DEnable", "random");
	// restore default value
	CVI_BOOL restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	memcpy(attr.stAuto.CenterWtExcludeY2DEnable, restore_val_0, sizeof(CVI_BOOL) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_CenterWtExcludeY2DEnable_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_CenterWtExcludeY2DEnable_auto);
}

static int test_TNR_TNRNrAttr_CenterWtExcludeY3DEnable_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.CenterWtExcludeY3DEnable != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.stManual.CenterWtExcludeY3DEnable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.CenterWtExcludeY3DEnable = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CenterWtExcludeY3DEnable", "min");
	// set maximum value
	attr.stManual.CenterWtExcludeY3DEnable = 1;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CenterWtExcludeY3DEnable", "max");
	// set random value
	attr.stManual.CenterWtExcludeY3DEnable = rand_range(0, 1);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CenterWtExcludeY3DEnable", "random");
	// restore default value
	attr.stManual.CenterWtExcludeY3DEnable = 1;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_CenterWtExcludeY3DEnable_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_CenterWtExcludeY3DEnable_manual);
}

static int test_TNR_TNRNrAttr_CenterWtExcludeY3DEnable_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_BOOL default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	if (memcmp(default_val_0, attr.stAuto.CenterWtExcludeY3DEnable, sizeof(CVI_BOOL) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CenterWtExcludeY3DEnable[j] = 0;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CenterWtExcludeY3DEnable", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CenterWtExcludeY3DEnable[j] = 1;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CenterWtExcludeY3DEnable", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CenterWtExcludeY3DEnable[j] = rand_range(0, 1);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CenterWtExcludeY3DEnable", "random");
	// restore default value
	CVI_BOOL restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	memcpy(attr.stAuto.CenterWtExcludeY3DEnable, restore_val_0, sizeof(CVI_BOOL) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_CenterWtExcludeY3DEnable_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_CenterWtExcludeY3DEnable_auto);
}

static int test_TNR_TNRNrAttr_YnrGrainNoiseSuppEnable_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.YnrGrainNoiseSuppEnable != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.stManual.YnrGrainNoiseSuppEnable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.YnrGrainNoiseSuppEnable = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrGrainNoiseSuppEnable", "min");
	// set maximum value
	attr.stManual.YnrGrainNoiseSuppEnable = 1;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrGrainNoiseSuppEnable", "max");
	// set random value
	attr.stManual.YnrGrainNoiseSuppEnable = rand_range(0, 1);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrGrainNoiseSuppEnable", "random");
	// restore default value
	attr.stManual.YnrGrainNoiseSuppEnable = 1;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_YnrGrainNoiseSuppEnable_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_YnrGrainNoiseSuppEnable_manual);
}

static int test_TNR_TNRNrAttr_YnrGrainNoiseSuppEnable_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_BOOL default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	if (memcmp(default_val_0, attr.stAuto.YnrGrainNoiseSuppEnable, sizeof(CVI_BOOL) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrGrainNoiseSuppEnable[j] = 0;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrGrainNoiseSuppEnable", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrGrainNoiseSuppEnable[j] = 1;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrGrainNoiseSuppEnable", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrGrainNoiseSuppEnable[j] = rand_range(0, 1);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrGrainNoiseSuppEnable", "random");
	// restore default value
	CVI_BOOL restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	memcpy(attr.stAuto.YnrGrainNoiseSuppEnable, restore_val_0, sizeof(CVI_BOOL) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_YnrGrainNoiseSuppEnable_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_YnrGrainNoiseSuppEnable_auto);
}

static int test_TNR_TNRNrAttr_YnrResidualThreshold_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.YnrResidualThreshold != 4) {
		TEST_FAIL("test default value: 4 != %d\n", (int)attr.stManual.YnrResidualThreshold);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.YnrResidualThreshold = 1;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrResidualThreshold", "min");
	// set maximum value
	attr.stManual.YnrResidualThreshold =  4;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrResidualThreshold", "max");
	// set random value
	attr.stManual.YnrResidualThreshold = rand_range(1,  4);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrResidualThreshold", "random");
	// set abnormal value test
	attr.stManual.YnrResidualThreshold = rand_range(0, 0);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.YnrResidualThreshold = 4;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_YnrResidualThreshold_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_YnrResidualThreshold_manual);
}

static int test_TNR_TNRNrAttr_YnrResidualThreshold_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 };
	if (memcmp(default_val_0, attr.stAuto.YnrResidualThreshold, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrResidualThreshold[j] = 1;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrResidualThreshold", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrResidualThreshold[j] = 4;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrResidualThreshold", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrResidualThreshold[j] = rand_range(1, 4);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrResidualThreshold", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrResidualThreshold[j] = rand_range(0, 0);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 };
	memcpy(attr.stAuto.YnrResidualThreshold, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_YnrResidualThreshold_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_YnrResidualThreshold_auto);
}

static int test_TNR_TNRNrAttr_CnrResidualThreshold_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.CnrResidualThreshold != 4) {
		TEST_FAIL("test default value: 4 != %d\n", (int)attr.stManual.CnrResidualThreshold);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.CnrResidualThreshold = 1;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrResidualThreshold", "min");
	// set maximum value
	attr.stManual.CnrResidualThreshold =  4;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrResidualThreshold", "max");
	// set random value
	attr.stManual.CnrResidualThreshold = rand_range(1,  4);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrResidualThreshold", "random");
	// set abnormal value test
	attr.stManual.CnrResidualThreshold = rand_range(0, 0);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.CnrResidualThreshold = 4;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_CnrResidualThreshold_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_CnrResidualThreshold_manual);
}

static int test_TNR_TNRNrAttr_CnrResidualThreshold_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 };
	if (memcmp(default_val_0, attr.stAuto.CnrResidualThreshold, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrResidualThreshold[j] = 1;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrResidualThreshold", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrResidualThreshold[j] = 4;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrResidualThreshold", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrResidualThreshold[j] = rand_range(1, 4);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrResidualThreshold", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrResidualThreshold[j] = rand_range(0, 0);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 };
	memcpy(attr.stAuto.CnrResidualThreshold, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_CnrResidualThreshold_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_CnrResidualThreshold_auto);
}

static int test_TNR_TNRNrAttr_YnrFilterThr2DLut_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.YnrFilterThr2DLut[0] != 11) {
		TEST_FAIL("test default value: 11 != %d\n", (int)attr.stManual.YnrFilterThr2DLut[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YnrFilterThr2DLut[1] != 33) {
		TEST_FAIL("test default value: 33 != %d\n", (int)attr.stManual.YnrFilterThr2DLut[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YnrFilterThr2DLut[2] != 55) {
		TEST_FAIL("test default value: 55 != %d\n", (int)attr.stManual.YnrFilterThr2DLut[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YnrFilterThr2DLut[3] != 77) {
		TEST_FAIL("test default value: 77 != %d\n", (int)attr.stManual.YnrFilterThr2DLut[3]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.YnrFilterThr2DLut[0] = 0;
	attr.stManual.YnrFilterThr2DLut[1] = 0;
	attr.stManual.YnrFilterThr2DLut[2] = 0;
	attr.stManual.YnrFilterThr2DLut[3] = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrFilterThr2DLut", "min");
	// set maximum value
	attr.stManual.YnrFilterThr2DLut[0] = 127;
	attr.stManual.YnrFilterThr2DLut[1] = 127;
	attr.stManual.YnrFilterThr2DLut[2] = 127;
	attr.stManual.YnrFilterThr2DLut[3] = 127;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrFilterThr2DLut", "max");
	// set random value
	attr.stManual.YnrFilterThr2DLut[0] = rand_range(0, 127);
	attr.stManual.YnrFilterThr2DLut[1] = rand_range(0, 127);
	attr.stManual.YnrFilterThr2DLut[2] = rand_range(0, 127);
	attr.stManual.YnrFilterThr2DLut[3] = rand_range(0, 127);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrFilterThr2DLut", "random");
	// set abnormal value test
	attr.stManual.YnrFilterThr2DLut[0] = rand_range(128, 255);
	attr.stManual.YnrFilterThr2DLut[1] = rand_range(128, 255);
	attr.stManual.YnrFilterThr2DLut[2] = rand_range(128, 255);
	attr.stManual.YnrFilterThr2DLut[3] = rand_range(128, 255);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.YnrFilterThr2DLut[0] = 11;
	attr.stManual.YnrFilterThr2DLut[1] = 33;
	attr.stManual.YnrFilterThr2DLut[2] = 55;
	attr.stManual.YnrFilterThr2DLut[3] = 77;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_YnrFilterThr2DLut_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_YnrFilterThr2DLut_manual);
}

static int test_TNR_TNRNrAttr_YnrFilterThr2DLut_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YnrFilterThr2DLut[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YnrFilterThr2DLut[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YnrFilterThr2DLut[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YnrFilterThr2DLut[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr2DLut[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr2DLut[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr2DLut[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr2DLut[j][3] = 0;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrFilterThr2DLut", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr2DLut[j][0] = 127;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr2DLut[j][1] = 127;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr2DLut[j][2] = 127;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr2DLut[j][3] = 127;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrFilterThr2DLut", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr2DLut[j][0] = rand_range(0, 127);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr2DLut[j][1] = rand_range(0, 127);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr2DLut[j][2] = rand_range(0, 127);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr2DLut[j][3] = rand_range(0, 127);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrFilterThr2DLut", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr2DLut[j][0] = rand_range(128, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr2DLut[j][1] = rand_range(128, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr2DLut[j][2] = rand_range(128, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr2DLut[j][3] = rand_range(128, 255);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr2DLut[j][0] = restore_val_0[j];
	}
	CVI_U8 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr2DLut[j][1] = restore_val_1[j];
	}
	CVI_U8 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr2DLut[j][2] = restore_val_2[j];
	}
	CVI_U8 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr2DLut[j][3] = restore_val_3[j];
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_YnrFilterThr2DLut_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_YnrFilterThr2DLut_auto);
}

static int test_TNR_TNRNrAttr_YnrFilterThr3DLut0_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.YnrFilterThr3DLut0[0] != 11) {
		TEST_FAIL("test default value: 11 != %d\n", (int)attr.stManual.YnrFilterThr3DLut0[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YnrFilterThr3DLut0[1] != 33) {
		TEST_FAIL("test default value: 33 != %d\n", (int)attr.stManual.YnrFilterThr3DLut0[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YnrFilterThr3DLut0[2] != 55) {
		TEST_FAIL("test default value: 55 != %d\n", (int)attr.stManual.YnrFilterThr3DLut0[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YnrFilterThr3DLut0[3] != 77) {
		TEST_FAIL("test default value: 77 != %d\n", (int)attr.stManual.YnrFilterThr3DLut0[3]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.YnrFilterThr3DLut0[0] = 0;
	attr.stManual.YnrFilterThr3DLut0[1] = 0;
	attr.stManual.YnrFilterThr3DLut0[2] = 0;
	attr.stManual.YnrFilterThr3DLut0[3] = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrFilterThr3DLut0", "min");
	// set maximum value
	attr.stManual.YnrFilterThr3DLut0[0] = 127;
	attr.stManual.YnrFilterThr3DLut0[1] = 127;
	attr.stManual.YnrFilterThr3DLut0[2] = 127;
	attr.stManual.YnrFilterThr3DLut0[3] = 127;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrFilterThr3DLut0", "max");
	// set random value
	attr.stManual.YnrFilterThr3DLut0[0] = rand_range(0, 127);
	attr.stManual.YnrFilterThr3DLut0[1] = rand_range(0, 127);
	attr.stManual.YnrFilterThr3DLut0[2] = rand_range(0, 127);
	attr.stManual.YnrFilterThr3DLut0[3] = rand_range(0, 127);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrFilterThr3DLut0", "random");
	// set abnormal value test
	attr.stManual.YnrFilterThr3DLut0[0] = rand_range(128, 255);
	attr.stManual.YnrFilterThr3DLut0[1] = rand_range(128, 255);
	attr.stManual.YnrFilterThr3DLut0[2] = rand_range(128, 255);
	attr.stManual.YnrFilterThr3DLut0[3] = rand_range(128, 255);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.YnrFilterThr3DLut0[0] = 11;
	attr.stManual.YnrFilterThr3DLut0[1] = 33;
	attr.stManual.YnrFilterThr3DLut0[2] = 55;
	attr.stManual.YnrFilterThr3DLut0[3] = 77;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_YnrFilterThr3DLut0_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_YnrFilterThr3DLut0_manual);
}

static int test_TNR_TNRNrAttr_YnrFilterThr3DLut0_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YnrFilterThr3DLut0[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YnrFilterThr3DLut0[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YnrFilterThr3DLut0[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YnrFilterThr3DLut0[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut0[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut0[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut0[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut0[j][3] = 0;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrFilterThr3DLut0", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut0[j][0] = 127;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut0[j][1] = 127;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut0[j][2] = 127;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut0[j][3] = 127;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrFilterThr3DLut0", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut0[j][0] = rand_range(0, 127);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut0[j][1] = rand_range(0, 127);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut0[j][2] = rand_range(0, 127);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut0[j][3] = rand_range(0, 127);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrFilterThr3DLut0", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut0[j][0] = rand_range(128, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut0[j][1] = rand_range(128, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut0[j][2] = rand_range(128, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut0[j][3] = rand_range(128, 255);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut0[j][0] = restore_val_0[j];
	}
	CVI_U8 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut0[j][1] = restore_val_1[j];
	}
	CVI_U8 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut0[j][2] = restore_val_2[j];
	}
	CVI_U8 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut0[j][3] = restore_val_3[j];
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_YnrFilterThr3DLut0_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_YnrFilterThr3DLut0_auto);
}

static int test_TNR_TNRNrAttr_YnrFilterThr3DLut1_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.YnrFilterThr3DLut1[0] != 40) {
		TEST_FAIL("test default value: 40 != %d\n", (int)attr.stManual.YnrFilterThr3DLut1[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YnrFilterThr3DLut1[1] != 14) {
		TEST_FAIL("test default value: 14 != %d\n", (int)attr.stManual.YnrFilterThr3DLut1[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YnrFilterThr3DLut1[2] != 7) {
		TEST_FAIL("test default value: 7 != %d\n", (int)attr.stManual.YnrFilterThr3DLut1[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YnrFilterThr3DLut1[3] != 3) {
		TEST_FAIL("test default value: 3 != %d\n", (int)attr.stManual.YnrFilterThr3DLut1[3]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.YnrFilterThr3DLut1[0] = 0;
	attr.stManual.YnrFilterThr3DLut1[1] = 0;
	attr.stManual.YnrFilterThr3DLut1[2] = 0;
	attr.stManual.YnrFilterThr3DLut1[3] = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrFilterThr3DLut1", "min");
	// set maximum value
	attr.stManual.YnrFilterThr3DLut1[0] = 127;
	attr.stManual.YnrFilterThr3DLut1[1] = 127;
	attr.stManual.YnrFilterThr3DLut1[2] = 127;
	attr.stManual.YnrFilterThr3DLut1[3] = 127;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrFilterThr3DLut1", "max");
	// set random value
	attr.stManual.YnrFilterThr3DLut1[0] = rand_range(0, 127);
	attr.stManual.YnrFilterThr3DLut1[1] = rand_range(0, 127);
	attr.stManual.YnrFilterThr3DLut1[2] = rand_range(0, 127);
	attr.stManual.YnrFilterThr3DLut1[3] = rand_range(0, 127);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrFilterThr3DLut1", "random");
	// set abnormal value test
	attr.stManual.YnrFilterThr3DLut1[0] = rand_range(128, 255);
	attr.stManual.YnrFilterThr3DLut1[1] = rand_range(128, 255);
	attr.stManual.YnrFilterThr3DLut1[2] = rand_range(128, 255);
	attr.stManual.YnrFilterThr3DLut1[3] = rand_range(128, 255);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.YnrFilterThr3DLut1[0] = 40;
	attr.stManual.YnrFilterThr3DLut1[1] = 14;
	attr.stManual.YnrFilterThr3DLut1[2] = 7;
	attr.stManual.YnrFilterThr3DLut1[3] = 3;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_YnrFilterThr3DLut1_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_YnrFilterThr3DLut1_manual);
}

static int test_TNR_TNRNrAttr_YnrFilterThr3DLut1_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YnrFilterThr3DLut1[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YnrFilterThr3DLut1[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YnrFilterThr3DLut1[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YnrFilterThr3DLut1[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut1[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut1[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut1[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut1[j][3] = 0;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrFilterThr3DLut1", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut1[j][0] = 127;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut1[j][1] = 127;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut1[j][2] = 127;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut1[j][3] = 127;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrFilterThr3DLut1", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut1[j][0] = rand_range(0, 127);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut1[j][1] = rand_range(0, 127);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut1[j][2] = rand_range(0, 127);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut1[j][3] = rand_range(0, 127);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "YnrFilterThr3DLut1", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut1[j][0] = rand_range(128, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut1[j][1] = rand_range(128, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut1[j][2] = rand_range(128, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut1[j][3] = rand_range(128, 255);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut1[j][0] = restore_val_0[j];
	}
	CVI_U8 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut1[j][1] = restore_val_1[j];
	}
	CVI_U8 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut1[j][2] = restore_val_2[j];
	}
	CVI_U8 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YnrFilterThr3DLut1[j][3] = restore_val_3[j];
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_YnrFilterThr3DLut1_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_YnrFilterThr3DLut1_auto);
}

static int test_TNR_TNRNrAttr_CnrFilterThr2DLut_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.CnrFilterThr2DLut[0] != 11) {
		TEST_FAIL("test default value: 11 != %d\n", (int)attr.stManual.CnrFilterThr2DLut[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.CnrFilterThr2DLut[1] != 33) {
		TEST_FAIL("test default value: 33 != %d\n", (int)attr.stManual.CnrFilterThr2DLut[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.CnrFilterThr2DLut[2] != 55) {
		TEST_FAIL("test default value: 55 != %d\n", (int)attr.stManual.CnrFilterThr2DLut[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.CnrFilterThr2DLut[3] != 77) {
		TEST_FAIL("test default value: 77 != %d\n", (int)attr.stManual.CnrFilterThr2DLut[3]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.CnrFilterThr2DLut[0] = 0;
	attr.stManual.CnrFilterThr2DLut[1] = 0;
	attr.stManual.CnrFilterThr2DLut[2] = 0;
	attr.stManual.CnrFilterThr2DLut[3] = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrFilterThr2DLut", "min");
	// set maximum value
	attr.stManual.CnrFilterThr2DLut[0] = 127;
	attr.stManual.CnrFilterThr2DLut[1] = 127;
	attr.stManual.CnrFilterThr2DLut[2] = 127;
	attr.stManual.CnrFilterThr2DLut[3] = 127;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrFilterThr2DLut", "max");
	// set random value
	attr.stManual.CnrFilterThr2DLut[0] = rand_range(0, 127);
	attr.stManual.CnrFilterThr2DLut[1] = rand_range(0, 127);
	attr.stManual.CnrFilterThr2DLut[2] = rand_range(0, 127);
	attr.stManual.CnrFilterThr2DLut[3] = rand_range(0, 127);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrFilterThr2DLut", "random");
	// set abnormal value test
	attr.stManual.CnrFilterThr2DLut[0] = rand_range(128, 255);
	attr.stManual.CnrFilterThr2DLut[1] = rand_range(128, 255);
	attr.stManual.CnrFilterThr2DLut[2] = rand_range(128, 255);
	attr.stManual.CnrFilterThr2DLut[3] = rand_range(128, 255);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.CnrFilterThr2DLut[0] = 11;
	attr.stManual.CnrFilterThr2DLut[1] = 33;
	attr.stManual.CnrFilterThr2DLut[2] = 55;
	attr.stManual.CnrFilterThr2DLut[3] = 77;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_CnrFilterThr2DLut_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_CnrFilterThr2DLut_manual);
}

static int test_TNR_TNRNrAttr_CnrFilterThr2DLut_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.CnrFilterThr2DLut[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.CnrFilterThr2DLut[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.CnrFilterThr2DLut[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.CnrFilterThr2DLut[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr2DLut[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr2DLut[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr2DLut[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr2DLut[j][3] = 0;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrFilterThr2DLut", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr2DLut[j][0] = 127;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr2DLut[j][1] = 127;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr2DLut[j][2] = 127;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr2DLut[j][3] = 127;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrFilterThr2DLut", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr2DLut[j][0] = rand_range(0, 127);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr2DLut[j][1] = rand_range(0, 127);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr2DLut[j][2] = rand_range(0, 127);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr2DLut[j][3] = rand_range(0, 127);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrFilterThr2DLut", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr2DLut[j][0] = rand_range(128, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr2DLut[j][1] = rand_range(128, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr2DLut[j][2] = rand_range(128, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr2DLut[j][3] = rand_range(128, 255);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr2DLut[j][0] = restore_val_0[j];
	}
	CVI_U8 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr2DLut[j][1] = restore_val_1[j];
	}
	CVI_U8 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr2DLut[j][2] = restore_val_2[j];
	}
	CVI_U8 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr2DLut[j][3] = restore_val_3[j];
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_CnrFilterThr2DLut_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_CnrFilterThr2DLut_auto);
}

static int test_TNR_TNRNrAttr_CnrFilterThr3DLut_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.CnrFilterThr3DLut[0] != 37) {
		TEST_FAIL("test default value: 37 != %d\n", (int)attr.stManual.CnrFilterThr3DLut[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.CnrFilterThr3DLut[1] != 19) {
		TEST_FAIL("test default value: 19 != %d\n", (int)attr.stManual.CnrFilterThr3DLut[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.CnrFilterThr3DLut[2] != 11) {
		TEST_FAIL("test default value: 11 != %d\n", (int)attr.stManual.CnrFilterThr3DLut[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.CnrFilterThr3DLut[3] != 7) {
		TEST_FAIL("test default value: 7 != %d\n", (int)attr.stManual.CnrFilterThr3DLut[3]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.CnrFilterThr3DLut[0] = 0;
	attr.stManual.CnrFilterThr3DLut[1] = 0;
	attr.stManual.CnrFilterThr3DLut[2] = 0;
	attr.stManual.CnrFilterThr3DLut[3] = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrFilterThr3DLut", "min");
	// set maximum value
	attr.stManual.CnrFilterThr3DLut[0] = 127;
	attr.stManual.CnrFilterThr3DLut[1] = 127;
	attr.stManual.CnrFilterThr3DLut[2] = 127;
	attr.stManual.CnrFilterThr3DLut[3] = 127;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrFilterThr3DLut", "max");
	// set random value
	attr.stManual.CnrFilterThr3DLut[0] = rand_range(0, 127);
	attr.stManual.CnrFilterThr3DLut[1] = rand_range(0, 127);
	attr.stManual.CnrFilterThr3DLut[2] = rand_range(0, 127);
	attr.stManual.CnrFilterThr3DLut[3] = rand_range(0, 127);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrFilterThr3DLut", "random");
	// set abnormal value test
	attr.stManual.CnrFilterThr3DLut[0] = rand_range(128, 255);
	attr.stManual.CnrFilterThr3DLut[1] = rand_range(128, 255);
	attr.stManual.CnrFilterThr3DLut[2] = rand_range(128, 255);
	attr.stManual.CnrFilterThr3DLut[3] = rand_range(128, 255);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.CnrFilterThr3DLut[0] = 37;
	attr.stManual.CnrFilterThr3DLut[1] = 19;
	attr.stManual.CnrFilterThr3DLut[2] = 11;
	attr.stManual.CnrFilterThr3DLut[3] = 7;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_CnrFilterThr3DLut_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_CnrFilterThr3DLut_manual);
}

static int test_TNR_TNRNrAttr_CnrFilterThr3DLut_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.CnrFilterThr3DLut[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.CnrFilterThr3DLut[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.CnrFilterThr3DLut[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.CnrFilterThr3DLut[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr3DLut[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr3DLut[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr3DLut[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr3DLut[j][3] = 0;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrFilterThr3DLut", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr3DLut[j][0] = 127;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr3DLut[j][1] = 127;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr3DLut[j][2] = 127;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr3DLut[j][3] = 127;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrFilterThr3DLut", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr3DLut[j][0] = rand_range(0, 127);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr3DLut[j][1] = rand_range(0, 127);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr3DLut[j][2] = rand_range(0, 127);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr3DLut[j][3] = rand_range(0, 127);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "CnrFilterThr3DLut", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr3DLut[j][0] = rand_range(128, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr3DLut[j][1] = rand_range(128, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr3DLut[j][2] = rand_range(128, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr3DLut[j][3] = rand_range(128, 255);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr3DLut[j][0] = restore_val_0[j];
	}
	CVI_U8 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr3DLut[j][1] = restore_val_1[j];
	}
	CVI_U8 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr3DLut[j][2] = restore_val_2[j];
	}
	CVI_U8 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.CnrFilterThr3DLut[j][3] = restore_val_3[j];
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_CnrFilterThr3DLut_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_CnrFilterThr3DLut_auto);
}

static int test_TNR_TNRNrAttr_HiEdge2DTh1_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.HiEdge2DTh1 != 255) {
		TEST_FAIL("test default value: 255 != %d\n", (int)attr.stManual.HiEdge2DTh1);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.HiEdge2DTh1 = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DTh1", "min");
	// set maximum value
	attr.stManual.HiEdge2DTh1 =  255;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DTh1", "max");
	// set random value
	attr.stManual.HiEdge2DTh1 = rand_range(0,  255);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DTh1", "random");
	// restore default value
	attr.stManual.HiEdge2DTh1 = 255;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_HiEdge2DTh1_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_HiEdge2DTh1_manual);
}

static int test_TNR_TNRNrAttr_HiEdge2DTh1_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 };
	if (memcmp(default_val_0, attr.stAuto.HiEdge2DTh1, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HiEdge2DTh1[j] = 0;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DTh1", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HiEdge2DTh1[j] = 255;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DTh1", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HiEdge2DTh1[j] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DTh1", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 };
	memcpy(attr.stAuto.HiEdge2DTh1, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_HiEdge2DTh1_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_HiEdge2DTh1_auto);
}

static int test_TNR_TNRNrAttr_HiEdge2DTh2_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.HiEdge2DTh2 != 255) {
		TEST_FAIL("test default value: 255 != %d\n", (int)attr.stManual.HiEdge2DTh2);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.HiEdge2DTh2 = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DTh2", "min");
	// set maximum value
	attr.stManual.HiEdge2DTh2 =  255;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DTh2", "max");
	// set random value
	attr.stManual.HiEdge2DTh2 = rand_range(0,  255);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DTh2", "random");
	// restore default value
	attr.stManual.HiEdge2DTh2 = 255;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_HiEdge2DTh2_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_HiEdge2DTh2_manual);
}

static int test_TNR_TNRNrAttr_HiEdge2DTh2_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 };
	if (memcmp(default_val_0, attr.stAuto.HiEdge2DTh2, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HiEdge2DTh2[j] = 0;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DTh2", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HiEdge2DTh2[j] = 255;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DTh2", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HiEdge2DTh2[j] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DTh2", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 };
	memcpy(attr.stAuto.HiEdge2DTh2, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_HiEdge2DTh2_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_HiEdge2DTh2_auto);
}

static int test_TNR_TNRNrAttr_HiEdge2DPenalty1_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.HiEdge2DPenalty1 != 5) {
		TEST_FAIL("test default value: 5 != %d\n", (int)attr.stManual.HiEdge2DPenalty1);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.HiEdge2DPenalty1 = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DPenalty1", "min");
	// set maximum value
	attr.stManual.HiEdge2DPenalty1 =  31;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DPenalty1", "max");
	// set random value
	attr.stManual.HiEdge2DPenalty1 = rand_range(0,  31);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DPenalty1", "random");
	// set abnormal value test
	attr.stManual.HiEdge2DPenalty1 = rand_range(32, 255);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.HiEdge2DPenalty1 = 5;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_HiEdge2DPenalty1_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_HiEdge2DPenalty1_manual);
}

static int test_TNR_TNRNrAttr_HiEdge2DPenalty1_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5 };
	if (memcmp(default_val_0, attr.stAuto.HiEdge2DPenalty1, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HiEdge2DPenalty1[j] = 0;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DPenalty1", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HiEdge2DPenalty1[j] = 31;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DPenalty1", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HiEdge2DPenalty1[j] = rand_range(0, 31);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DPenalty1", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HiEdge2DPenalty1[j] = rand_range(32, 255);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5 };
	memcpy(attr.stAuto.HiEdge2DPenalty1, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_HiEdge2DPenalty1_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_HiEdge2DPenalty1_auto);
}

static int test_TNR_TNRNrAttr_HiEdge2DPenalty2_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.HiEdge2DPenalty2 != 10) {
		TEST_FAIL("test default value: 10 != %d\n", (int)attr.stManual.HiEdge2DPenalty2);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.HiEdge2DPenalty2 = 0;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DPenalty2", "min");
	// set maximum value
	attr.stManual.HiEdge2DPenalty2 =  31;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DPenalty2", "max");
	// set random value
	attr.stManual.HiEdge2DPenalty2 = rand_range(0,  31);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DPenalty2", "random");
	// set abnormal value test
	attr.stManual.HiEdge2DPenalty2 = rand_range(32, 255);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.HiEdge2DPenalty2 = 10;
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_HiEdge2DPenalty2_manual(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_HiEdge2DPenalty2_manual);
}

static int test_TNR_TNRNrAttr_HiEdge2DPenalty2_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_TNR_NR_ATTR_S attr;

	ret = CVI_ISP_GetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetTNRNrAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10 };
	if (memcmp(default_val_0, attr.stAuto.HiEdge2DPenalty2, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HiEdge2DPenalty2[j] = 0;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DPenalty2", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HiEdge2DPenalty2[j] = 31;
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DPenalty2", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HiEdge2DPenalty2[j] = rand_range(0, 31);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "TNR", "HiEdge2DPenalty2", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HiEdge2DPenalty2[j] = rand_range(32, 255);
	}
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10 };
	memcpy(attr.stAuto.HiEdge2DPenalty2, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetTNRNrAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_TNR_TNRNrAttr_HiEdge2DPenalty2_auto(void)
{
	reg_api_test_fn(test_TNR_TNRNrAttr_HiEdge2DPenalty2_auto);
}
