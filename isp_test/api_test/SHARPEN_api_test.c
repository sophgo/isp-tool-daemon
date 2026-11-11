
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

static int test_SHARPEN_SharpenAttr_Enable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.Enable != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.Enable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.Enable = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "Enable", "min");
	// set maximum value
	attr.Enable = 1;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "Enable", "max");
	// set random value
	attr.Enable = rand_range(0, 1);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "Enable", "random");
	// restore default value
	attr.Enable = 1;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_Enable(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_Enable);
}

static int test_SHARPEN_SharpenAttr_enOpType(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.enOpType != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.enOpType);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.enOpType = OP_TYPE_AUTO;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "enOpType", "min");
	// set maximum value
	attr.enOpType = OP_TYPE_MANUAL;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "enOpType", "max");
	// restore default value
	attr.enOpType = 1;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_enOpType(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_enOpType);
}

static int test_SHARPEN_SharpenAttr_UpdateInterval(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.UpdateInterval != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.UpdateInterval);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.UpdateInterval = 1;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "UpdateInterval", "min");
	// set maximum value
	attr.UpdateInterval = 255;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "UpdateInterval", "max");
	// set random value
	attr.UpdateInterval = rand_range(1, 255);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "UpdateInterval", "random");
	// set abnormal value test
	attr.UpdateInterval = rand_range(0, 0);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.UpdateInterval = 1;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_UpdateInterval(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_UpdateInterval);
}

static int test_SHARPEN_SharpenAttr_TuningMode(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.TuningMode != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.TuningMode);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.TuningMode = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "TuningMode", "min");
	// set maximum value
	attr.TuningMode = 7;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "TuningMode", "max");
	// set random value
	attr.TuningMode = rand_range(0, 7);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "TuningMode", "random");
	// set abnormal value test
	attr.TuningMode = rand_range(8, 255);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.TuningMode = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_TuningMode(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_TuningMode);
}

static int test_SHARPEN_SharpenAttr_MotionEn(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.MotionEn != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.MotionEn);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.MotionEn = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "MotionEn", "min");
	// set maximum value
	attr.MotionEn = 1;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "MotionEn", "max");
	// set random value
	attr.MotionEn = rand_range(0, 1);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "MotionEn", "random");
	// restore default value
	attr.MotionEn = 1;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_MotionEn(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_MotionEn);
}

static int test_SHARPEN_SharpenAttr_SatShtCtrlEn(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.SatShtCtrlEn != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.SatShtCtrlEn);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.SatShtCtrlEn = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "SatShtCtrlEn", "min");
	// set maximum value
	attr.SatShtCtrlEn = 1;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "SatShtCtrlEn", "max");
	// set random value
	attr.SatShtCtrlEn = rand_range(0, 1);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "SatShtCtrlEn", "random");
	// restore default value
	attr.SatShtCtrlEn = 1;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_SatShtCtrlEn(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_SatShtCtrlEn);
}

static int test_SHARPEN_SharpenAttr_enFilterType(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.enFilterType != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.enFilterType);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.enFilterType = OP_TYPE_3x3;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "enFilterType", "min");
	// set maximum value
	attr.enFilterType = OP_TYPE_5x5;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "enFilterType", "max");
	// restore default value
	attr.enFilterType = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_enFilterType(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_enFilterType);
}

static int test_SHARPEN_SharpenAttr_EE1SrcType(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.EE1SrcType != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.EE1SrcType);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.EE1SrcType = OP_TYPE_Y;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1SrcType", "min");
	// set maximum value
	attr.EE1SrcType = OP_TYPE_DEGAMMA_Y;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1SrcType", "max");
	// restore default value
	attr.EE1SrcType = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE1SrcType(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE1SrcType);
}

static int test_SHARPEN_SharpenAttr_EE1CoringThr_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.EE1CoringThr != 2) {
		TEST_FAIL("test default value: 2 != %d\n", (int)attr.stManual.EE1CoringThr);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.EE1CoringThr = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1CoringThr", "min");
	// set maximum value
	attr.stManual.EE1CoringThr = 255;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1CoringThr", "max");
	// set random value
	attr.stManual.EE1CoringThr = rand_range(0, 255);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1CoringThr", "random");
	// restore default value
	attr.stManual.EE1CoringThr = 2;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE1CoringThr_manual(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE1CoringThr_manual);
}

static int test_SHARPEN_SharpenAttr_EE1CoringThr_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 };
	if (memcmp(default_val_0, attr.stAuto.EE1CoringThr, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1CoringThr[j] = 0;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1CoringThr", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1CoringThr[j] = 255;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1CoringThr", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1CoringThr[j] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1CoringThr", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 };
	memcpy(attr.stAuto.EE1CoringThr, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE1CoringThr_auto(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE1CoringThr_auto);
}

static int test_SHARPEN_SharpenAttr_NoiseBase_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.NoiseBase != 25) {
		TEST_FAIL("test default value: 25 != %d\n", (int)attr.stManual.NoiseBase);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.NoiseBase = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "NoiseBase", "min");
	// set maximum value
	attr.stManual.NoiseBase = 255;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "NoiseBase", "max");
	// set random value
	attr.stManual.NoiseBase = rand_range(0, 255);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "NoiseBase", "random");
	// restore default value
	attr.stManual.NoiseBase = 25;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_NoiseBase_manual(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_NoiseBase_manual);
}

static int test_SHARPEN_SharpenAttr_NoiseBase_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25 };
	if (memcmp(default_val_0, attr.stAuto.NoiseBase, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseBase[j] = 0;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "NoiseBase", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseBase[j] = 255;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "NoiseBase", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseBase[j] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "NoiseBase", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25 };
	memcpy(attr.stAuto.NoiseBase, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_NoiseBase_auto(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_NoiseBase_auto);
}

static int test_SHARPEN_SharpenAttr_EE2BalanceRatio_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.EE2BalanceRatio != 64) {
		TEST_FAIL("test default value: 64 != %d\n", (int)attr.stManual.EE2BalanceRatio);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.EE2BalanceRatio = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE2BalanceRatio", "min");
	// set maximum value
	attr.stManual.EE2BalanceRatio = 255;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE2BalanceRatio", "max");
	// set random value
	attr.stManual.EE2BalanceRatio = rand_range(0, 255);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE2BalanceRatio", "random");
	// restore default value
	attr.stManual.EE2BalanceRatio = 64;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE2BalanceRatio_manual(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE2BalanceRatio_manual);
}

static int test_SHARPEN_SharpenAttr_EE2BalanceRatio_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64 };
	if (memcmp(default_val_0, attr.stAuto.EE2BalanceRatio, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE2BalanceRatio[j] = 0;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE2BalanceRatio", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE2BalanceRatio[j] = 255;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE2BalanceRatio", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE2BalanceRatio[j] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE2BalanceRatio", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64 };
	memcpy(attr.stAuto.EE2BalanceRatio, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE2BalanceRatio_auto(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE2BalanceRatio_auto);
}

static int test_SHARPEN_SharpenAttr_EE2SharpStr_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.EE2SharpStr != 60) {
		TEST_FAIL("test default value: 60 != %d\n", (int)attr.stManual.EE2SharpStr);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.EE2SharpStr = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE2SharpStr", "min");
	// set maximum value
	attr.stManual.EE2SharpStr = 255;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE2SharpStr", "max");
	// set random value
	attr.stManual.EE2SharpStr = rand_range(0, 255);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE2SharpStr", "random");
	// restore default value
	attr.stManual.EE2SharpStr = 60;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE2SharpStr_manual(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE2SharpStr_manual);
}

static int test_SHARPEN_SharpenAttr_EE2SharpStr_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60 };
	if (memcmp(default_val_0, attr.stAuto.EE2SharpStr, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE2SharpStr[j] = 0;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE2SharpStr", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE2SharpStr[j] = 255;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE2SharpStr", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE2SharpStr[j] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE2SharpStr", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60 };
	memcpy(attr.stAuto.EE2SharpStr, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE2SharpStr_auto(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE2SharpStr_auto);
}

static int test_SHARPEN_SharpenAttr_EE2CoringThr_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.EE2CoringThr != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.stManual.EE2CoringThr);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.EE2CoringThr = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE2CoringThr", "min");
	// set maximum value
	attr.stManual.EE2CoringThr = 255;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE2CoringThr", "max");
	// set random value
	attr.stManual.EE2CoringThr = rand_range(0, 255);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE2CoringThr", "random");
	// restore default value
	attr.stManual.EE2CoringThr = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE2CoringThr_manual(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE2CoringThr_manual);
}

static int test_SHARPEN_SharpenAttr_EE2CoringThr_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	if (memcmp(default_val_0, attr.stAuto.EE2CoringThr, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE2CoringThr[j] = 0;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE2CoringThr", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE2CoringThr[j] = 255;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE2CoringThr", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE2CoringThr[j] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE2CoringThr", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	memcpy(attr.stAuto.EE2CoringThr, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE2CoringThr_auto(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE2CoringThr_auto);
}

static int test_SHARPEN_SharpenAttr_OverShootRatio_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.OverShootRatio != 32) {
		TEST_FAIL("test default value: 32 != %d\n", (int)attr.stManual.OverShootRatio);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.OverShootRatio = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "OverShootRatio", "min");
	// set maximum value
	attr.stManual.OverShootRatio = 255;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "OverShootRatio", "max");
	// set random value
	attr.stManual.OverShootRatio = rand_range(0, 255);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "OverShootRatio", "random");
	// restore default value
	attr.stManual.OverShootRatio = 32;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_OverShootRatio_manual(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_OverShootRatio_manual);
}

static int test_SHARPEN_SharpenAttr_OverShootRatio_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32 };
	if (memcmp(default_val_0, attr.stAuto.OverShootRatio, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.OverShootRatio[j] = 0;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "OverShootRatio", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.OverShootRatio[j] = 255;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "OverShootRatio", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.OverShootRatio[j] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "OverShootRatio", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32 };
	memcpy(attr.stAuto.OverShootRatio, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_OverShootRatio_auto(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_OverShootRatio_auto);
}

static int test_SHARPEN_SharpenAttr_UnderShootRatio_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.UnderShootRatio != 96) {
		TEST_FAIL("test default value: 96 != %d\n", (int)attr.stManual.UnderShootRatio);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.UnderShootRatio = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "UnderShootRatio", "min");
	// set maximum value
	attr.stManual.UnderShootRatio = 255;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "UnderShootRatio", "max");
	// set random value
	attr.stManual.UnderShootRatio = rand_range(0, 255);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "UnderShootRatio", "random");
	// restore default value
	attr.stManual.UnderShootRatio = 96;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_UnderShootRatio_manual(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_UnderShootRatio_manual);
}

static int test_SHARPEN_SharpenAttr_UnderShootRatio_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96 };
	if (memcmp(default_val_0, attr.stAuto.UnderShootRatio, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.UnderShootRatio[j] = 0;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "UnderShootRatio", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.UnderShootRatio[j] = 255;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "UnderShootRatio", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.UnderShootRatio[j] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "UnderShootRatio", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96 };
	memcpy(attr.stAuto.UnderShootRatio, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_UnderShootRatio_auto(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_UnderShootRatio_auto);
}

static int test_SHARPEN_SharpenAttr_EE1BlendWgt_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.EE1BlendWgt != 4) {
		TEST_FAIL("test default value: 4 != %d\n", (int)attr.stManual.EE1BlendWgt);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.EE1BlendWgt = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1BlendWgt", "min");
	// set maximum value
	attr.stManual.EE1BlendWgt = 8;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1BlendWgt", "max");
	// set random value
	attr.stManual.EE1BlendWgt = rand_range(0, 8);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1BlendWgt", "random");
	// set abnormal value test
	attr.stManual.EE1BlendWgt = rand_range(9, 255);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.EE1BlendWgt = 4;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE1BlendWgt_manual(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE1BlendWgt_manual);
}

static int test_SHARPEN_SharpenAttr_EE1BlendWgt_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 };
	if (memcmp(default_val_0, attr.stAuto.EE1BlendWgt, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1BlendWgt[j] = 0;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1BlendWgt", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1BlendWgt[j] = 8;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1BlendWgt", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1BlendWgt[j] = rand_range(0, 8);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1BlendWgt", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1BlendWgt[j] = rand_range(9, 255);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 };
	memcpy(attr.stAuto.EE1BlendWgt, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE1BlendWgt_auto(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE1BlendWgt_auto);
}

static int test_SHARPEN_SharpenAttr_EE1FlatThr_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.EE1FlatThr != 50) {
		TEST_FAIL("test default value: 50 != %d\n", (int)attr.stManual.EE1FlatThr);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.EE1FlatThr = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1FlatThr", "min");
	// set maximum value
	attr.stManual.EE1FlatThr = 2047;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1FlatThr", "max");
	// set random value
	attr.stManual.EE1FlatThr = rand_range(0, 2047);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1FlatThr", "random");
	// set abnormal value test
	attr.stManual.EE1FlatThr = rand_range(2048, 65535);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.EE1FlatThr = 50;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE1FlatThr_manual(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE1FlatThr_manual);
}

static int test_SHARPEN_SharpenAttr_EE1FlatThr_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U16 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50 };
	if (memcmp(default_val_0, attr.stAuto.EE1FlatThr, sizeof(CVI_U16) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1FlatThr[j] = 0;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1FlatThr", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1FlatThr[j] = 2047;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1FlatThr", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1FlatThr[j] = rand_range(0, 2047);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1FlatThr", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1FlatThr[j] = rand_range(2048, 65535);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U16 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50 };
	memcpy(attr.stAuto.EE1FlatThr, restore_val_0, sizeof(CVI_U16) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE1FlatThr_auto(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE1FlatThr_auto);
}

static int test_SHARPEN_SharpenAttr_EE1EdgeThr_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.EE1EdgeThr != 350) {
		TEST_FAIL("test default value: 350 != %d\n", (int)attr.stManual.EE1EdgeThr);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.EE1EdgeThr = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1EdgeThr", "min");
	// set maximum value
	attr.stManual.EE1EdgeThr = 2047;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1EdgeThr", "max");
	// set random value
	attr.stManual.EE1EdgeThr = rand_range(0, 2047);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1EdgeThr", "random");
	// set abnormal value test
	attr.stManual.EE1EdgeThr = rand_range(2048, 65535);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.EE1EdgeThr = 350;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE1EdgeThr_manual(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE1EdgeThr_manual);
}

static int test_SHARPEN_SharpenAttr_EE1EdgeThr_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U16 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350 };
	if (memcmp(default_val_0, attr.stAuto.EE1EdgeThr, sizeof(CVI_U16) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1EdgeThr[j] = 0;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1EdgeThr", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1EdgeThr[j] = 2047;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1EdgeThr", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1EdgeThr[j] = rand_range(0, 2047);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1EdgeThr", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1EdgeThr[j] = rand_range(2048, 65535);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U16 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350 };
	memcpy(attr.stAuto.EE1EdgeThr, restore_val_0, sizeof(CVI_U16) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE1EdgeThr_auto(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE1EdgeThr_auto);
}

static int test_SHARPEN_SharpenAttr_EE1FlatRegionStr_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.EE1FlatRegionStr != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.EE1FlatRegionStr);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.EE1FlatRegionStr = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1FlatRegionStr", "min");
	// set maximum value
	attr.stManual.EE1FlatRegionStr = 255;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1FlatRegionStr", "max");
	// set random value
	attr.stManual.EE1FlatRegionStr = rand_range(0, 255);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1FlatRegionStr", "random");
	// restore default value
	attr.stManual.EE1FlatRegionStr = 128;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE1FlatRegionStr_manual(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE1FlatRegionStr_manual);
}

static int test_SHARPEN_SharpenAttr_EE1FlatRegionStr_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	if (memcmp(default_val_0, attr.stAuto.EE1FlatRegionStr, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1FlatRegionStr[j] = 0;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1FlatRegionStr", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1FlatRegionStr[j] = 255;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1FlatRegionStr", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1FlatRegionStr[j] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1FlatRegionStr", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	memcpy(attr.stAuto.EE1FlatRegionStr, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE1FlatRegionStr_auto(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE1FlatRegionStr_auto);
}

static int test_SHARPEN_SharpenAttr_EE1EdgeRegionStr_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.EE1EdgeRegionStr != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.EE1EdgeRegionStr);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.EE1EdgeRegionStr = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1EdgeRegionStr", "min");
	// set maximum value
	attr.stManual.EE1EdgeRegionStr = 255;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1EdgeRegionStr", "max");
	// set random value
	attr.stManual.EE1EdgeRegionStr = rand_range(0, 255);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1EdgeRegionStr", "random");
	// restore default value
	attr.stManual.EE1EdgeRegionStr = 128;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE1EdgeRegionStr_manual(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE1EdgeRegionStr_manual);
}

static int test_SHARPEN_SharpenAttr_EE1EdgeRegionStr_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	if (memcmp(default_val_0, attr.stAuto.EE1EdgeRegionStr, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1EdgeRegionStr[j] = 0;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1EdgeRegionStr", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1EdgeRegionStr[j] = 255;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1EdgeRegionStr", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1EdgeRegionStr[j] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1EdgeRegionStr", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	memcpy(attr.stAuto.EE1EdgeRegionStr, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE1EdgeRegionStr_auto(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE1EdgeRegionStr_auto);
}

static int test_SHARPEN_SharpenAttr_EE1MotionStr_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.EE1MotionStr != 127) {
		TEST_FAIL("test default value: 127 != %d\n", (int)attr.stManual.EE1MotionStr);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.EE1MotionStr = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1MotionStr", "min");
	// set maximum value
	attr.stManual.EE1MotionStr = 255;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1MotionStr", "max");
	// set random value
	attr.stManual.EE1MotionStr = rand_range(0, 255);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1MotionStr", "random");
	// restore default value
	attr.stManual.EE1MotionStr = 127;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE1MotionStr_manual(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE1MotionStr_manual);
}

static int test_SHARPEN_SharpenAttr_EE1MotionStr_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127 };
	if (memcmp(default_val_0, attr.stAuto.EE1MotionStr, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1MotionStr[j] = 0;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1MotionStr", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1MotionStr[j] = 255;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1MotionStr", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1MotionStr[j] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1MotionStr", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127 };
	memcpy(attr.stAuto.EE1MotionStr, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE1MotionStr_auto(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE1MotionStr_auto);
}

static int test_SHARPEN_SharpenAttr_EE1StaticStr_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.EE1StaticStr != 255) {
		TEST_FAIL("test default value: 255 != %d\n", (int)attr.stManual.EE1StaticStr);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.EE1StaticStr = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1StaticStr", "min");
	// set maximum value
	attr.stManual.EE1StaticStr = 255;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1StaticStr", "max");
	// set random value
	attr.stManual.EE1StaticStr = rand_range(0, 255);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1StaticStr", "random");
	// restore default value
	attr.stManual.EE1StaticStr = 255;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE1StaticStr_manual(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE1StaticStr_manual);
}

static int test_SHARPEN_SharpenAttr_EE1StaticStr_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 };
	if (memcmp(default_val_0, attr.stAuto.EE1StaticStr, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1StaticStr[j] = 0;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1StaticStr", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1StaticStr[j] = 255;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1StaticStr", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1StaticStr[j] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1StaticStr", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 };
	memcpy(attr.stAuto.EE1StaticStr, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE1StaticStr_auto(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE1StaticStr_auto);
}

static int test_SHARPEN_SharpenAttr_EE1TransStr_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.EE1TransStr != 255) {
		TEST_FAIL("test default value: 255 != %d\n", (int)attr.stManual.EE1TransStr);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.EE1TransStr = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1TransStr", "min");
	// set maximum value
	attr.stManual.EE1TransStr = 255;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1TransStr", "max");
	// set random value
	attr.stManual.EE1TransStr = rand_range(0, 255);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1TransStr", "random");
	// restore default value
	attr.stManual.EE1TransStr = 255;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE1TransStr_manual(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE1TransStr_manual);
}

static int test_SHARPEN_SharpenAttr_EE1TransStr_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 };
	if (memcmp(default_val_0, attr.stAuto.EE1TransStr, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1TransStr[j] = 0;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1TransStr", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1TransStr[j] = 255;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1TransStr", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.EE1TransStr[j] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "EE1TransStr", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 };
	memcpy(attr.stAuto.EE1TransStr, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_EE1TransStr_auto(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_EE1TransStr_auto);
}

static int test_SHARPEN_SharpenAttr_NoiseLut_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.NoiseLut[0] != 20) {
		TEST_FAIL("test default value: 20 != %d\n", (int)attr.stManual.NoiseLut[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseLut[1] != 20) {
		TEST_FAIL("test default value: 20 != %d\n", (int)attr.stManual.NoiseLut[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseLut[2] != 25) {
		TEST_FAIL("test default value: 25 != %d\n", (int)attr.stManual.NoiseLut[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseLut[3] != 28) {
		TEST_FAIL("test default value: 28 != %d\n", (int)attr.stManual.NoiseLut[3]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseLut[4] != 30) {
		TEST_FAIL("test default value: 30 != %d\n", (int)attr.stManual.NoiseLut[4]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseLut[5] != 30) {
		TEST_FAIL("test default value: 30 != %d\n", (int)attr.stManual.NoiseLut[5]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseLut[6] != 35) {
		TEST_FAIL("test default value: 35 != %d\n", (int)attr.stManual.NoiseLut[6]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseLut[7] != 35) {
		TEST_FAIL("test default value: 35 != %d\n", (int)attr.stManual.NoiseLut[7]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseLut[8] != 35) {
		TEST_FAIL("test default value: 35 != %d\n", (int)attr.stManual.NoiseLut[8]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseLut[9] != 35) {
		TEST_FAIL("test default value: 35 != %d\n", (int)attr.stManual.NoiseLut[9]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseLut[10] != 35) {
		TEST_FAIL("test default value: 35 != %d\n", (int)attr.stManual.NoiseLut[10]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseLut[11] != 35) {
		TEST_FAIL("test default value: 35 != %d\n", (int)attr.stManual.NoiseLut[11]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseLut[12] != 35) {
		TEST_FAIL("test default value: 35 != %d\n", (int)attr.stManual.NoiseLut[12]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseLut[13] != 35) {
		TEST_FAIL("test default value: 35 != %d\n", (int)attr.stManual.NoiseLut[13]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseLut[14] != 35) {
		TEST_FAIL("test default value: 35 != %d\n", (int)attr.stManual.NoiseLut[14]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseLut[15] != 35) {
		TEST_FAIL("test default value: 35 != %d\n", (int)attr.stManual.NoiseLut[15]);
		return CVI_FAILURE;
	}
	if (attr.stManual.NoiseLut[16] != 35) {
		TEST_FAIL("test default value: 35 != %d\n", (int)attr.stManual.NoiseLut[16]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.NoiseLut[0] = 0;
	attr.stManual.NoiseLut[1] = 0;
	attr.stManual.NoiseLut[2] = 0;
	attr.stManual.NoiseLut[3] = 0;
	attr.stManual.NoiseLut[4] = 0;
	attr.stManual.NoiseLut[5] = 0;
	attr.stManual.NoiseLut[6] = 0;
	attr.stManual.NoiseLut[7] = 0;
	attr.stManual.NoiseLut[8] = 0;
	attr.stManual.NoiseLut[9] = 0;
	attr.stManual.NoiseLut[10] = 0;
	attr.stManual.NoiseLut[11] = 0;
	attr.stManual.NoiseLut[12] = 0;
	attr.stManual.NoiseLut[13] = 0;
	attr.stManual.NoiseLut[14] = 0;
	attr.stManual.NoiseLut[15] = 0;
	attr.stManual.NoiseLut[16] = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "NoiseLut", "min");
	// set maximum value
	attr.stManual.NoiseLut[0] = 255;
	attr.stManual.NoiseLut[1] = 255;
	attr.stManual.NoiseLut[2] = 255;
	attr.stManual.NoiseLut[3] = 255;
	attr.stManual.NoiseLut[4] = 255;
	attr.stManual.NoiseLut[5] = 255;
	attr.stManual.NoiseLut[6] = 255;
	attr.stManual.NoiseLut[7] = 255;
	attr.stManual.NoiseLut[8] = 255;
	attr.stManual.NoiseLut[9] = 255;
	attr.stManual.NoiseLut[10] = 255;
	attr.stManual.NoiseLut[11] = 255;
	attr.stManual.NoiseLut[12] = 255;
	attr.stManual.NoiseLut[13] = 255;
	attr.stManual.NoiseLut[14] = 255;
	attr.stManual.NoiseLut[15] = 255;
	attr.stManual.NoiseLut[16] = 255;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "NoiseLut", "max");
	// set random value
	attr.stManual.NoiseLut[0] = rand_range(0, 255);
	attr.stManual.NoiseLut[1] = rand_range(0, 255);
	attr.stManual.NoiseLut[2] = rand_range(0, 255);
	attr.stManual.NoiseLut[3] = rand_range(0, 255);
	attr.stManual.NoiseLut[4] = rand_range(0, 255);
	attr.stManual.NoiseLut[5] = rand_range(0, 255);
	attr.stManual.NoiseLut[6] = rand_range(0, 255);
	attr.stManual.NoiseLut[7] = rand_range(0, 255);
	attr.stManual.NoiseLut[8] = rand_range(0, 255);
	attr.stManual.NoiseLut[9] = rand_range(0, 255);
	attr.stManual.NoiseLut[10] = rand_range(0, 255);
	attr.stManual.NoiseLut[11] = rand_range(0, 255);
	attr.stManual.NoiseLut[12] = rand_range(0, 255);
	attr.stManual.NoiseLut[13] = rand_range(0, 255);
	attr.stManual.NoiseLut[14] = rand_range(0, 255);
	attr.stManual.NoiseLut[15] = rand_range(0, 255);
	attr.stManual.NoiseLut[16] = rand_range(0, 255);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "NoiseLut", "random");
	// restore default value
	attr.stManual.NoiseLut[0] = 20;
	attr.stManual.NoiseLut[1] = 20;
	attr.stManual.NoiseLut[2] = 25;
	attr.stManual.NoiseLut[3] = 28;
	attr.stManual.NoiseLut[4] = 30;
	attr.stManual.NoiseLut[5] = 30;
	attr.stManual.NoiseLut[6] = 35;
	attr.stManual.NoiseLut[7] = 35;
	attr.stManual.NoiseLut[8] = 35;
	attr.stManual.NoiseLut[9] = 35;
	attr.stManual.NoiseLut[10] = 35;
	attr.stManual.NoiseLut[11] = 35;
	attr.stManual.NoiseLut[12] = 35;
	attr.stManual.NoiseLut[13] = 35;
	attr.stManual.NoiseLut[14] = 35;
	attr.stManual.NoiseLut[15] = 35;
	attr.stManual.NoiseLut[16] = 35;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_NoiseLut_manual(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_NoiseLut_manual);
}

static int test_SHARPEN_SharpenAttr_NoiseLut_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseLut[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseLut[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseLut[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseLut[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseLut[j][4] != default_val_4[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseLut[j][5] != default_val_5[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseLut[j][6] != default_val_6[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseLut[j][7] != default_val_7[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_8[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseLut[j][8] != default_val_8[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_9[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseLut[j][9] != default_val_9[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_10[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseLut[j][10] != default_val_10[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_11[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseLut[j][11] != default_val_11[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_12[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseLut[j][12] != default_val_12[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_13[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseLut[j][13] != default_val_13[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_14[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseLut[j][14] != default_val_14[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_15[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseLut[j][15] != default_val_15[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_16[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.NoiseLut[j][16] != default_val_16[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][3] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][4] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][5] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][6] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][7] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][8] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][9] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][10] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][11] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][12] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][13] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][14] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][15] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][16] = 0;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "NoiseLut", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][0] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][1] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][2] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][3] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][4] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][5] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][6] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][7] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][8] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][9] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][10] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][11] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][12] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][13] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][14] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][15] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][16] = 255;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "NoiseLut", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][0] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][1] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][2] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][3] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][4] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][5] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][6] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][7] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][8] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][9] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][10] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][11] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][12] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][13] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][14] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][15] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][16] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "NoiseLut", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][0] = restore_val_0[j];
	}
	CVI_U8 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][1] = restore_val_1[j];
	}
	CVI_U8 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][2] = restore_val_2[j];
	}
	CVI_U8 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][3] = restore_val_3[j];
	}
	CVI_U8 restore_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][4] = restore_val_4[j];
	}
	CVI_U8 restore_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][5] = restore_val_5[j];
	}
	CVI_U8 restore_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][6] = restore_val_6[j];
	}
	CVI_U8 restore_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][7] = restore_val_7[j];
	}
	CVI_U8 restore_val_8[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][8] = restore_val_8[j];
	}
	CVI_U8 restore_val_9[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][9] = restore_val_9[j];
	}
	CVI_U8 restore_val_10[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][10] = restore_val_10[j];
	}
	CVI_U8 restore_val_11[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][11] = restore_val_11[j];
	}
	CVI_U8 restore_val_12[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][12] = restore_val_12[j];
	}
	CVI_U8 restore_val_13[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][13] = restore_val_13[j];
	}
	CVI_U8 restore_val_14[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][14] = restore_val_14[j];
	}
	CVI_U8 restore_val_15[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][15] = restore_val_15[j];
	}
	CVI_U8 restore_val_16[ISP_AUTO_ISO_STRENGTH_NUM] = { 35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.NoiseLut[j][16] = restore_val_16[j];
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_NoiseLut_auto(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_NoiseLut_auto);
}

static int test_SHARPEN_SharpenAttr_HueShtCtrl_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.HueShtCtrl[0] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[1] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[2] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[3] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[3]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[4] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[4]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[5] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[5]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[6] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[6]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[7] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[7]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[8] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[8]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[9] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[9]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[10] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[10]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[11] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[11]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[12] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[12]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[13] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[13]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[14] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[14]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[15] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[15]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[16] != 20) {
		TEST_FAIL("test default value: 20 != %d\n", (int)attr.stManual.HueShtCtrl[16]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[17] != 24) {
		TEST_FAIL("test default value: 24 != %d\n", (int)attr.stManual.HueShtCtrl[17]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[18] != 28) {
		TEST_FAIL("test default value: 28 != %d\n", (int)attr.stManual.HueShtCtrl[18]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[19] != 30) {
		TEST_FAIL("test default value: 30 != %d\n", (int)attr.stManual.HueShtCtrl[19]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[20] != 32) {
		TEST_FAIL("test default value: 32 != %d\n", (int)attr.stManual.HueShtCtrl[20]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[21] != 30) {
		TEST_FAIL("test default value: 30 != %d\n", (int)attr.stManual.HueShtCtrl[21]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[22] != 38) {
		TEST_FAIL("test default value: 38 != %d\n", (int)attr.stManual.HueShtCtrl[22]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[23] != 24) {
		TEST_FAIL("test default value: 24 != %d\n", (int)attr.stManual.HueShtCtrl[23]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[24] != 20) {
		TEST_FAIL("test default value: 20 != %d\n", (int)attr.stManual.HueShtCtrl[24]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[25] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[25]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[26] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[26]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[27] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[27]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[28] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[28]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[29] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[29]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[30] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[30]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[31] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[31]);
		return CVI_FAILURE;
	}
	if (attr.stManual.HueShtCtrl[32] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.HueShtCtrl[32]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.HueShtCtrl[0] = 0;
	attr.stManual.HueShtCtrl[1] = 0;
	attr.stManual.HueShtCtrl[2] = 0;
	attr.stManual.HueShtCtrl[3] = 0;
	attr.stManual.HueShtCtrl[4] = 0;
	attr.stManual.HueShtCtrl[5] = 0;
	attr.stManual.HueShtCtrl[6] = 0;
	attr.stManual.HueShtCtrl[7] = 0;
	attr.stManual.HueShtCtrl[8] = 0;
	attr.stManual.HueShtCtrl[9] = 0;
	attr.stManual.HueShtCtrl[10] = 0;
	attr.stManual.HueShtCtrl[11] = 0;
	attr.stManual.HueShtCtrl[12] = 0;
	attr.stManual.HueShtCtrl[13] = 0;
	attr.stManual.HueShtCtrl[14] = 0;
	attr.stManual.HueShtCtrl[15] = 0;
	attr.stManual.HueShtCtrl[16] = 0;
	attr.stManual.HueShtCtrl[17] = 0;
	attr.stManual.HueShtCtrl[18] = 0;
	attr.stManual.HueShtCtrl[19] = 0;
	attr.stManual.HueShtCtrl[20] = 0;
	attr.stManual.HueShtCtrl[21] = 0;
	attr.stManual.HueShtCtrl[22] = 0;
	attr.stManual.HueShtCtrl[23] = 0;
	attr.stManual.HueShtCtrl[24] = 0;
	attr.stManual.HueShtCtrl[25] = 0;
	attr.stManual.HueShtCtrl[26] = 0;
	attr.stManual.HueShtCtrl[27] = 0;
	attr.stManual.HueShtCtrl[28] = 0;
	attr.stManual.HueShtCtrl[29] = 0;
	attr.stManual.HueShtCtrl[30] = 0;
	attr.stManual.HueShtCtrl[31] = 0;
	attr.stManual.HueShtCtrl[32] = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "HueShtCtrl", "min");
	// set maximum value
	attr.stManual.HueShtCtrl[0] = 63;
	attr.stManual.HueShtCtrl[1] = 63;
	attr.stManual.HueShtCtrl[2] = 63;
	attr.stManual.HueShtCtrl[3] = 63;
	attr.stManual.HueShtCtrl[4] = 63;
	attr.stManual.HueShtCtrl[5] = 63;
	attr.stManual.HueShtCtrl[6] = 63;
	attr.stManual.HueShtCtrl[7] = 63;
	attr.stManual.HueShtCtrl[8] = 63;
	attr.stManual.HueShtCtrl[9] = 63;
	attr.stManual.HueShtCtrl[10] = 63;
	attr.stManual.HueShtCtrl[11] = 63;
	attr.stManual.HueShtCtrl[12] = 63;
	attr.stManual.HueShtCtrl[13] = 63;
	attr.stManual.HueShtCtrl[14] = 63;
	attr.stManual.HueShtCtrl[15] = 63;
	attr.stManual.HueShtCtrl[16] = 63;
	attr.stManual.HueShtCtrl[17] = 63;
	attr.stManual.HueShtCtrl[18] = 63;
	attr.stManual.HueShtCtrl[19] = 63;
	attr.stManual.HueShtCtrl[20] = 63;
	attr.stManual.HueShtCtrl[21] = 63;
	attr.stManual.HueShtCtrl[22] = 63;
	attr.stManual.HueShtCtrl[23] = 63;
	attr.stManual.HueShtCtrl[24] = 63;
	attr.stManual.HueShtCtrl[25] = 63;
	attr.stManual.HueShtCtrl[26] = 63;
	attr.stManual.HueShtCtrl[27] = 63;
	attr.stManual.HueShtCtrl[28] = 63;
	attr.stManual.HueShtCtrl[29] = 63;
	attr.stManual.HueShtCtrl[30] = 63;
	attr.stManual.HueShtCtrl[31] = 63;
	attr.stManual.HueShtCtrl[32] = 63;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "HueShtCtrl", "max");
	// set random value
	attr.stManual.HueShtCtrl[0] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[1] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[2] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[3] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[4] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[5] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[6] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[7] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[8] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[9] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[10] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[11] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[12] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[13] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[14] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[15] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[16] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[17] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[18] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[19] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[20] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[21] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[22] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[23] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[24] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[25] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[26] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[27] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[28] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[29] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[30] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[31] = rand_range(0, 63);
	attr.stManual.HueShtCtrl[32] = rand_range(0, 63);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "HueShtCtrl", "random");
	// set abnormal value test
	attr.stManual.HueShtCtrl[0] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[1] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[2] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[3] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[4] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[5] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[6] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[7] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[8] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[9] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[10] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[11] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[12] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[13] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[14] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[15] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[16] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[17] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[18] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[19] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[20] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[21] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[22] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[23] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[24] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[25] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[26] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[27] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[28] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[29] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[30] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[31] = rand_range(64, 255);
	attr.stManual.HueShtCtrl[32] = rand_range(64, 255);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.HueShtCtrl[0] = 16;
	attr.stManual.HueShtCtrl[1] = 16;
	attr.stManual.HueShtCtrl[2] = 16;
	attr.stManual.HueShtCtrl[3] = 16;
	attr.stManual.HueShtCtrl[4] = 16;
	attr.stManual.HueShtCtrl[5] = 16;
	attr.stManual.HueShtCtrl[6] = 16;
	attr.stManual.HueShtCtrl[7] = 16;
	attr.stManual.HueShtCtrl[8] = 16;
	attr.stManual.HueShtCtrl[9] = 16;
	attr.stManual.HueShtCtrl[10] = 16;
	attr.stManual.HueShtCtrl[11] = 16;
	attr.stManual.HueShtCtrl[12] = 16;
	attr.stManual.HueShtCtrl[13] = 16;
	attr.stManual.HueShtCtrl[14] = 16;
	attr.stManual.HueShtCtrl[15] = 16;
	attr.stManual.HueShtCtrl[16] = 20;
	attr.stManual.HueShtCtrl[17] = 24;
	attr.stManual.HueShtCtrl[18] = 28;
	attr.stManual.HueShtCtrl[19] = 30;
	attr.stManual.HueShtCtrl[20] = 32;
	attr.stManual.HueShtCtrl[21] = 30;
	attr.stManual.HueShtCtrl[22] = 38;
	attr.stManual.HueShtCtrl[23] = 24;
	attr.stManual.HueShtCtrl[24] = 20;
	attr.stManual.HueShtCtrl[25] = 16;
	attr.stManual.HueShtCtrl[26] = 16;
	attr.stManual.HueShtCtrl[27] = 16;
	attr.stManual.HueShtCtrl[28] = 16;
	attr.stManual.HueShtCtrl[29] = 16;
	attr.stManual.HueShtCtrl[30] = 16;
	attr.stManual.HueShtCtrl[31] = 16;
	attr.stManual.HueShtCtrl[32] = 16;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_HueShtCtrl_manual(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_HueShtCtrl_manual);
}

static int test_SHARPEN_SharpenAttr_HueShtCtrl_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][4] != default_val_4[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][5] != default_val_5[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][6] != default_val_6[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][7] != default_val_7[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_8[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][8] != default_val_8[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_9[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][9] != default_val_9[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_10[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][10] != default_val_10[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_11[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][11] != default_val_11[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_12[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][12] != default_val_12[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_13[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][13] != default_val_13[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_14[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][14] != default_val_14[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_15[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][15] != default_val_15[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_16[ISP_AUTO_ISO_STRENGTH_NUM] = { 20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][16] != default_val_16[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_17[ISP_AUTO_ISO_STRENGTH_NUM] = { 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][17] != default_val_17[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_18[ISP_AUTO_ISO_STRENGTH_NUM] = { 28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][18] != default_val_18[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_19[ISP_AUTO_ISO_STRENGTH_NUM] = { 30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][19] != default_val_19[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_20[ISP_AUTO_ISO_STRENGTH_NUM] = { 32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][20] != default_val_20[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_21[ISP_AUTO_ISO_STRENGTH_NUM] = { 30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][21] != default_val_21[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_22[ISP_AUTO_ISO_STRENGTH_NUM] = { 38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][22] != default_val_22[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_23[ISP_AUTO_ISO_STRENGTH_NUM] = { 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][23] != default_val_23[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_24[ISP_AUTO_ISO_STRENGTH_NUM] = { 20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][24] != default_val_24[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_25[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][25] != default_val_25[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_26[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][26] != default_val_26[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_27[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][27] != default_val_27[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_28[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][28] != default_val_28[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_29[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][29] != default_val_29[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_30[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][30] != default_val_30[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_31[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][31] != default_val_31[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_32[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.HueShtCtrl[j][32] != default_val_32[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][3] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][4] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][5] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][6] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][7] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][8] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][9] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][10] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][11] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][12] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][13] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][14] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][15] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][16] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][17] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][18] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][19] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][20] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][21] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][22] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][23] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][24] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][25] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][26] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][27] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][28] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][29] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][30] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][31] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][32] = 0;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "HueShtCtrl", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][0] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][1] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][2] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][3] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][4] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][5] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][6] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][7] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][8] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][9] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][10] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][11] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][12] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][13] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][14] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][15] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][16] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][17] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][18] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][19] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][20] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][21] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][22] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][23] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][24] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][25] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][26] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][27] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][28] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][29] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][30] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][31] = 63;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][32] = 63;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "HueShtCtrl", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][0] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][1] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][2] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][3] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][4] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][5] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][6] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][7] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][8] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][9] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][10] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][11] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][12] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][13] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][14] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][15] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][16] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][17] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][18] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][19] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][20] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][21] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][22] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][23] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][24] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][25] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][26] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][27] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][28] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][29] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][30] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][31] = rand_range(0, 63);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][32] = rand_range(0, 63);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "HueShtCtrl", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][0] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][1] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][2] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][3] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][4] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][5] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][6] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][7] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][8] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][9] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][10] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][11] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][12] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][13] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][14] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][15] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][16] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][17] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][18] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][19] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][20] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][21] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][22] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][23] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][24] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][25] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][26] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][27] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][28] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][29] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][30] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][31] = rand_range(64, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][32] = rand_range(64, 255);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][0] = restore_val_0[j];
	}
	CVI_U8 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][1] = restore_val_1[j];
	}
	CVI_U8 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][2] = restore_val_2[j];
	}
	CVI_U8 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][3] = restore_val_3[j];
	}
	CVI_U8 restore_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][4] = restore_val_4[j];
	}
	CVI_U8 restore_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][5] = restore_val_5[j];
	}
	CVI_U8 restore_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][6] = restore_val_6[j];
	}
	CVI_U8 restore_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][7] = restore_val_7[j];
	}
	CVI_U8 restore_val_8[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][8] = restore_val_8[j];
	}
	CVI_U8 restore_val_9[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][9] = restore_val_9[j];
	}
	CVI_U8 restore_val_10[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][10] = restore_val_10[j];
	}
	CVI_U8 restore_val_11[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][11] = restore_val_11[j];
	}
	CVI_U8 restore_val_12[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][12] = restore_val_12[j];
	}
	CVI_U8 restore_val_13[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][13] = restore_val_13[j];
	}
	CVI_U8 restore_val_14[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][14] = restore_val_14[j];
	}
	CVI_U8 restore_val_15[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][15] = restore_val_15[j];
	}
	CVI_U8 restore_val_16[ISP_AUTO_ISO_STRENGTH_NUM] = { 20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][16] = restore_val_16[j];
	}
	CVI_U8 restore_val_17[ISP_AUTO_ISO_STRENGTH_NUM] = { 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][17] = restore_val_17[j];
	}
	CVI_U8 restore_val_18[ISP_AUTO_ISO_STRENGTH_NUM] = { 28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][18] = restore_val_18[j];
	}
	CVI_U8 restore_val_19[ISP_AUTO_ISO_STRENGTH_NUM] = { 30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][19] = restore_val_19[j];
	}
	CVI_U8 restore_val_20[ISP_AUTO_ISO_STRENGTH_NUM] = { 32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][20] = restore_val_20[j];
	}
	CVI_U8 restore_val_21[ISP_AUTO_ISO_STRENGTH_NUM] = { 30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][21] = restore_val_21[j];
	}
	CVI_U8 restore_val_22[ISP_AUTO_ISO_STRENGTH_NUM] = { 38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][22] = restore_val_22[j];
	}
	CVI_U8 restore_val_23[ISP_AUTO_ISO_STRENGTH_NUM] = { 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][23] = restore_val_23[j];
	}
	CVI_U8 restore_val_24[ISP_AUTO_ISO_STRENGTH_NUM] = { 20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][24] = restore_val_24[j];
	}
	CVI_U8 restore_val_25[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][25] = restore_val_25[j];
	}
	CVI_U8 restore_val_26[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][26] = restore_val_26[j];
	}
	CVI_U8 restore_val_27[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][27] = restore_val_27[j];
	}
	CVI_U8 restore_val_28[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][28] = restore_val_28[j];
	}
	CVI_U8 restore_val_29[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][29] = restore_val_29[j];
	}
	CVI_U8 restore_val_30[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][30] = restore_val_30[j];
	}
	CVI_U8 restore_val_31[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][31] = restore_val_31[j];
	}
	CVI_U8 restore_val_32[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.HueShtCtrl[j][32] = restore_val_32[j];
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_HueShtCtrl_auto(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_HueShtCtrl_auto);
}

static int test_SHARPEN_SharpenAttr_SatShtGainIn_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.SatShtGainIn[0] != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.stManual.SatShtGainIn[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.SatShtGainIn[1] != 8) {
		TEST_FAIL("test default value: 8 != %d\n", (int)attr.stManual.SatShtGainIn[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.SatShtGainIn[2] != 16) {
		TEST_FAIL("test default value: 16 != %d\n", (int)attr.stManual.SatShtGainIn[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.SatShtGainIn[3] != 192) {
		TEST_FAIL("test default value: 192 != %d\n", (int)attr.stManual.SatShtGainIn[3]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.SatShtGainIn[0] = 0;
	attr.stManual.SatShtGainIn[1] = 0;
	attr.stManual.SatShtGainIn[2] = 0;
	attr.stManual.SatShtGainIn[3] = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "SatShtGainIn", "min");
	// set maximum value
	attr.stManual.SatShtGainIn[0] = 255;
	attr.stManual.SatShtGainIn[1] = 255;
	attr.stManual.SatShtGainIn[2] = 255;
	attr.stManual.SatShtGainIn[3] = 255;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "SatShtGainIn", "max");
	// set random value
	attr.stManual.SatShtGainIn[0] = rand_range(0, 255);
	attr.stManual.SatShtGainIn[1] = rand_range(0, 255);
	attr.stManual.SatShtGainIn[2] = rand_range(0, 255);
	attr.stManual.SatShtGainIn[3] = rand_range(0, 255);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "SatShtGainIn", "random");
	// restore default value
	attr.stManual.SatShtGainIn[0] = 0;
	attr.stManual.SatShtGainIn[1] = 8;
	attr.stManual.SatShtGainIn[2] = 16;
	attr.stManual.SatShtGainIn[3] = 192;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_SatShtGainIn_manual(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_SatShtGainIn_manual);
}

static int test_SHARPEN_SharpenAttr_SatShtGainIn_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.SatShtGainIn[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.SatShtGainIn[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.SatShtGainIn[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.SatShtGainIn[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainIn[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainIn[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainIn[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainIn[j][3] = 0;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "SatShtGainIn", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainIn[j][0] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainIn[j][1] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainIn[j][2] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainIn[j][3] = 255;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "SatShtGainIn", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainIn[j][0] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainIn[j][1] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainIn[j][2] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainIn[j][3] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "SatShtGainIn", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainIn[j][0] = restore_val_0[j];
	}
	CVI_U8 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainIn[j][1] = restore_val_1[j];
	}
	CVI_U8 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainIn[j][2] = restore_val_2[j];
	}
	CVI_U8 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 192,192,192,192,192,192,192,192,192,192,192,192,192,192,192,192 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainIn[j][3] = restore_val_3[j];
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_SatShtGainIn_auto(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_SatShtGainIn_auto);
}

static int test_SHARPEN_SharpenAttr_SatShtGainOut_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.SatShtGainOut[0] != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.stManual.SatShtGainOut[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.SatShtGainOut[1] != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.stManual.SatShtGainOut[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.SatShtGainOut[2] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.SatShtGainOut[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.SatShtGainOut[3] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.SatShtGainOut[3]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.SatShtGainOut[0] = 0;
	attr.stManual.SatShtGainOut[1] = 0;
	attr.stManual.SatShtGainOut[2] = 0;
	attr.stManual.SatShtGainOut[3] = 0;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "SatShtGainOut", "min");
	// set maximum value
	attr.stManual.SatShtGainOut[0] = 128;
	attr.stManual.SatShtGainOut[1] = 128;
	attr.stManual.SatShtGainOut[2] = 128;
	attr.stManual.SatShtGainOut[3] = 128;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "SatShtGainOut", "max");
	// set random value
	attr.stManual.SatShtGainOut[0] = rand_range(0, 128);
	attr.stManual.SatShtGainOut[1] = rand_range(0, 128);
	attr.stManual.SatShtGainOut[2] = rand_range(0, 128);
	attr.stManual.SatShtGainOut[3] = rand_range(0, 128);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "SatShtGainOut", "random");
	// set abnormal value test
	attr.stManual.SatShtGainOut[0] = rand_range(129, 255);
	attr.stManual.SatShtGainOut[1] = rand_range(129, 255);
	attr.stManual.SatShtGainOut[2] = rand_range(129, 255);
	attr.stManual.SatShtGainOut[3] = rand_range(129, 255);
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.SatShtGainOut[0] = 0;
	attr.stManual.SatShtGainOut[1] = 0;
	attr.stManual.SatShtGainOut[2] = 128;
	attr.stManual.SatShtGainOut[3] = 128;
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_SatShtGainOut_manual(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_SatShtGainOut_manual);
}

static int test_SHARPEN_SharpenAttr_SatShtGainOut_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SHARPEN_ATTR_S attr;

	ret = CVI_ISP_GetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSharpenAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.SatShtGainOut[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.SatShtGainOut[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.SatShtGainOut[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.SatShtGainOut[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainOut[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainOut[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainOut[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainOut[j][3] = 0;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "SatShtGainOut", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainOut[j][0] = 128;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainOut[j][1] = 128;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainOut[j][2] = 128;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainOut[j][3] = 128;
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "SatShtGainOut", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainOut[j][0] = rand_range(0, 128);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainOut[j][1] = rand_range(0, 128);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainOut[j][2] = rand_range(0, 128);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainOut[j][3] = rand_range(0, 128);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "SHARPEN", "SatShtGainOut", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainOut[j][0] = rand_range(129, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainOut[j][1] = rand_range(129, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainOut[j][2] = rand_range(129, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainOut[j][3] = rand_range(129, 255);
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainOut[j][0] = restore_val_0[j];
	}
	CVI_U8 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainOut[j][1] = restore_val_1[j];
	}
	CVI_U8 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainOut[j][2] = restore_val_2[j];
	}
	CVI_U8 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.SatShtGainOut[j][3] = restore_val_3[j];
	}
	ret = CVI_ISP_SetSharpenAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_SHARPEN_SharpenAttr_SatShtGainOut_auto(void)
{
	reg_api_test_fn(test_SHARPEN_SharpenAttr_SatShtGainOut_auto);
}
