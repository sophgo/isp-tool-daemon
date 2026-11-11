
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

static int test_DPC_DPDynamicAttr_Enable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DP_DYNAMIC_ATTR_S attr;

	ret = CVI_ISP_GetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDPDynamicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.Enable != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.Enable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.Enable = 0;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "Enable", "min");
	// set maximum value
	attr.Enable = 1;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "Enable", "max");
	// set random value
	attr.Enable = rand_range(0, 1);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "Enable", "random");
	// restore default value
	attr.Enable = 1;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DPC_DPDynamicAttr_Enable(void)
{
	reg_api_test_fn(test_DPC_DPDynamicAttr_Enable);
}

static int test_DPC_DPDynamicAttr_enOpType(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DP_DYNAMIC_ATTR_S attr;

	ret = CVI_ISP_GetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDPDynamicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.enOpType != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.enOpType);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.enOpType = OP_TYPE_AUTO;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "enOpType", "min");
	// set maximum value
	attr.enOpType = OP_TYPE_MANUAL;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "enOpType", "max");
	// restore default value
	attr.enOpType = 0;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DPC_DPDynamicAttr_enOpType(void)
{
	reg_api_test_fn(test_DPC_DPDynamicAttr_enOpType);
}

static int test_DPC_DPDynamicAttr_UpdateInterval(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DP_DYNAMIC_ATTR_S attr;

	ret = CVI_ISP_GetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDPDynamicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.UpdateInterval != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.UpdateInterval);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.UpdateInterval = 0;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "UpdateInterval", "min");
	// set maximum value
	attr.UpdateInterval = 255;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "UpdateInterval", "max");
	// set random value
	attr.UpdateInterval = rand_range(0, 255);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "UpdateInterval", "random");
	// restore default value
	attr.UpdateInterval = 1;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DPC_DPDynamicAttr_UpdateInterval(void)
{
	reg_api_test_fn(test_DPC_DPDynamicAttr_UpdateInterval);
}

static int test_DPC_DPDynamicAttr_DarkDefectThresh_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DP_DYNAMIC_ATTR_S attr;

	ret = CVI_ISP_GetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDPDynamicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.DarkDefectThresh[0] != 710) {
		TEST_FAIL("test default value: 710 != %d\n", (int)attr.stManual.DarkDefectThresh[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.DarkDefectThresh[1] != 1036) {
		TEST_FAIL("test default value: 1036 != %d\n", (int)attr.stManual.DarkDefectThresh[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.DarkDefectThresh[2] != 1711) {
		TEST_FAIL("test default value: 1711 != %d\n", (int)attr.stManual.DarkDefectThresh[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.DarkDefectThresh[3] != 2365) {
		TEST_FAIL("test default value: 2365 != %d\n", (int)attr.stManual.DarkDefectThresh[3]);
		return CVI_FAILURE;
	}
	if (attr.stManual.DarkDefectThresh[4] != 3905) {
		TEST_FAIL("test default value: 3905 != %d\n", (int)attr.stManual.DarkDefectThresh[4]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.DarkDefectThresh[0] = 0;
	attr.stManual.DarkDefectThresh[1] = 0;
	attr.stManual.DarkDefectThresh[2] = 0;
	attr.stManual.DarkDefectThresh[3] = 0;
	attr.stManual.DarkDefectThresh[4] = 0;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DarkDefectThresh", "min");
	// set maximum value
	attr.stManual.DarkDefectThresh[0] = 4095;
	attr.stManual.DarkDefectThresh[1] = 4095;
	attr.stManual.DarkDefectThresh[2] = 4095;
	attr.stManual.DarkDefectThresh[3] = 4095;
	attr.stManual.DarkDefectThresh[4] = 4095;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DarkDefectThresh", "max");
	// set random value
	attr.stManual.DarkDefectThresh[0] = rand_range(0, 4095);
	attr.stManual.DarkDefectThresh[1] = rand_range(0, 4095);
	attr.stManual.DarkDefectThresh[2] = rand_range(0, 4095);
	attr.stManual.DarkDefectThresh[3] = rand_range(0, 4095);
	attr.stManual.DarkDefectThresh[4] = rand_range(0, 4095);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DarkDefectThresh", "random");
	// set abnormal value test
	attr.stManual.DarkDefectThresh[0] = rand_range(4096, 65535);
	attr.stManual.DarkDefectThresh[1] = rand_range(4096, 65535);
	attr.stManual.DarkDefectThresh[2] = rand_range(4096, 65535);
	attr.stManual.DarkDefectThresh[3] = rand_range(4096, 65535);
	attr.stManual.DarkDefectThresh[4] = rand_range(4096, 65535);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.DarkDefectThresh[0] = 710;
	attr.stManual.DarkDefectThresh[1] = 1036;
	attr.stManual.DarkDefectThresh[2] = 1711;
	attr.stManual.DarkDefectThresh[3] = 2365;
	attr.stManual.DarkDefectThresh[4] = 3905;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DPC_DPDynamicAttr_DarkDefectThresh_manual(void)
{
	reg_api_test_fn(test_DPC_DPDynamicAttr_DarkDefectThresh_manual);
}

static int test_DPC_DPDynamicAttr_DarkDefectThresh_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DP_DYNAMIC_ATTR_S attr;

	ret = CVI_ISP_GetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDPDynamicAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U16 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 710,710,710,710,710,710,710,710,710,710,710,710,710,710,710,710 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.DarkDefectThresh[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.DarkDefectThresh[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.DarkDefectThresh[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.DarkDefectThresh[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.DarkDefectThresh[j][4] != default_val_4[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][3] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][4] = 0;
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DarkDefectThresh", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][0] = 4095;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][1] = 4095;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][2] = 4095;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][3] = 4095;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][4] = 4095;
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DarkDefectThresh", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][0] = rand_range(0, 4095);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][1] = rand_range(0, 4095);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][2] = rand_range(0, 4095);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][3] = rand_range(0, 4095);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][4] = rand_range(0, 4095);
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DarkDefectThresh", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][0] = rand_range(4096, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][1] = rand_range(4096, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][2] = rand_range(4096, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][3] = rand_range(4096, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][4] = rand_range(4096, 65535);
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U16 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 710,710,710,710,710,710,710,710,710,710,710,710,710,710,710,710 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][0] = restore_val_0[j];
	}
	CVI_U16 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][1] = restore_val_1[j];
	}
	CVI_U16 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][2] = restore_val_2[j];
	}
	CVI_U16 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][3] = restore_val_3[j];
	}
	CVI_U16 restore_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DarkDefectThresh[j][4] = restore_val_4[j];
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DPC_DPDynamicAttr_DarkDefectThresh_auto(void)
{
	reg_api_test_fn(test_DPC_DPDynamicAttr_DarkDefectThresh_auto);
}

static int test_DPC_DPDynamicAttr_BrightDefectThresh_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DP_DYNAMIC_ATTR_S attr;

	ret = CVI_ISP_GetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDPDynamicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.BrightDefectThresh[0] != 710) {
		TEST_FAIL("test default value: 710 != %d\n", (int)attr.stManual.BrightDefectThresh[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.BrightDefectThresh[1] != 1036) {
		TEST_FAIL("test default value: 1036 != %d\n", (int)attr.stManual.BrightDefectThresh[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.BrightDefectThresh[2] != 1711) {
		TEST_FAIL("test default value: 1711 != %d\n", (int)attr.stManual.BrightDefectThresh[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.BrightDefectThresh[3] != 2365) {
		TEST_FAIL("test default value: 2365 != %d\n", (int)attr.stManual.BrightDefectThresh[3]);
		return CVI_FAILURE;
	}
	if (attr.stManual.BrightDefectThresh[4] != 3905) {
		TEST_FAIL("test default value: 3905 != %d\n", (int)attr.stManual.BrightDefectThresh[4]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.BrightDefectThresh[0] = 0;
	attr.stManual.BrightDefectThresh[1] = 0;
	attr.stManual.BrightDefectThresh[2] = 0;
	attr.stManual.BrightDefectThresh[3] = 0;
	attr.stManual.BrightDefectThresh[4] = 0;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "BrightDefectThresh", "min");
	// set maximum value
	attr.stManual.BrightDefectThresh[0] = 4095;
	attr.stManual.BrightDefectThresh[1] = 4095;
	attr.stManual.BrightDefectThresh[2] = 4095;
	attr.stManual.BrightDefectThresh[3] = 4095;
	attr.stManual.BrightDefectThresh[4] = 4095;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "BrightDefectThresh", "max");
	// set random value
	attr.stManual.BrightDefectThresh[0] = rand_range(0, 4095);
	attr.stManual.BrightDefectThresh[1] = rand_range(0, 4095);
	attr.stManual.BrightDefectThresh[2] = rand_range(0, 4095);
	attr.stManual.BrightDefectThresh[3] = rand_range(0, 4095);
	attr.stManual.BrightDefectThresh[4] = rand_range(0, 4095);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "BrightDefectThresh", "random");
	// set abnormal value test
	attr.stManual.BrightDefectThresh[0] = rand_range(4096, 65535);
	attr.stManual.BrightDefectThresh[1] = rand_range(4096, 65535);
	attr.stManual.BrightDefectThresh[2] = rand_range(4096, 65535);
	attr.stManual.BrightDefectThresh[3] = rand_range(4096, 65535);
	attr.stManual.BrightDefectThresh[4] = rand_range(4096, 65535);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.BrightDefectThresh[0] = 710;
	attr.stManual.BrightDefectThresh[1] = 1036;
	attr.stManual.BrightDefectThresh[2] = 1711;
	attr.stManual.BrightDefectThresh[3] = 2365;
	attr.stManual.BrightDefectThresh[4] = 3905;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DPC_DPDynamicAttr_BrightDefectThresh_manual(void)
{
	reg_api_test_fn(test_DPC_DPDynamicAttr_BrightDefectThresh_manual);
}

static int test_DPC_DPDynamicAttr_BrightDefectThresh_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DP_DYNAMIC_ATTR_S attr;

	ret = CVI_ISP_GetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDPDynamicAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U16 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 710,710,710,710,710,710,710,710,710,710,710,710,710,710,710,710 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.BrightDefectThresh[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.BrightDefectThresh[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.BrightDefectThresh[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.BrightDefectThresh[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.BrightDefectThresh[j][4] != default_val_4[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][3] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][4] = 0;
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "BrightDefectThresh", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][0] = 4095;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][1] = 4095;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][2] = 4095;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][3] = 4095;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][4] = 4095;
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "BrightDefectThresh", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][0] = rand_range(0, 4095);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][1] = rand_range(0, 4095);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][2] = rand_range(0, 4095);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][3] = rand_range(0, 4095);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][4] = rand_range(0, 4095);
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "BrightDefectThresh", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][0] = rand_range(4096, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][1] = rand_range(4096, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][2] = rand_range(4096, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][3] = rand_range(4096, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][4] = rand_range(4096, 65535);
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U16 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 710,710,710,710,710,710,710,710,710,710,710,710,710,710,710,710 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][0] = restore_val_0[j];
	}
	CVI_U16 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036,1036 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][1] = restore_val_1[j];
	}
	CVI_U16 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711,1711 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][2] = restore_val_2[j];
	}
	CVI_U16 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365,2365 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][3] = restore_val_3[j];
	}
	CVI_U16 restore_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905,3905 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.BrightDefectThresh[j][4] = restore_val_4[j];
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DPC_DPDynamicAttr_BrightDefectThresh_auto(void)
{
	reg_api_test_fn(test_DPC_DPDynamicAttr_BrightDefectThresh_auto);
}

static int test_DPC_DPDynamicAttr_DarkDefectThreshOffset(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DP_DYNAMIC_ATTR_S attr;

	ret = CVI_ISP_GetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDPDynamicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.DarkDefectThreshOffset != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.DarkDefectThreshOffset);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.DarkDefectThreshOffset = 0;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DarkDefectThreshOffset", "min");
	// set maximum value
	attr.DarkDefectThreshOffset = 4095;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DarkDefectThreshOffset", "max");
	// set random value
	attr.DarkDefectThreshOffset = rand_range(0, 4095);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DarkDefectThreshOffset", "random");
	// set abnormal value test
	attr.DarkDefectThreshOffset = rand_range(4096, 65535);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.DarkDefectThreshOffset = 0;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DPC_DPDynamicAttr_DarkDefectThreshOffset(void)
{
	reg_api_test_fn(test_DPC_DPDynamicAttr_DarkDefectThreshOffset);
}

static int test_DPC_DPDynamicAttr_BrightDefectThreshOffset(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DP_DYNAMIC_ATTR_S attr;

	ret = CVI_ISP_GetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDPDynamicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.BrightDefectThreshOffset != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.BrightDefectThreshOffset);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.BrightDefectThreshOffset = 0;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "BrightDefectThreshOffset", "min");
	// set maximum value
	attr.BrightDefectThreshOffset = 4095;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "BrightDefectThreshOffset", "max");
	// set random value
	attr.BrightDefectThreshOffset = rand_range(0, 4095);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "BrightDefectThreshOffset", "random");
	// set abnormal value test
	attr.BrightDefectThreshOffset = rand_range(4096, 65535);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.BrightDefectThreshOffset = 0;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DPC_DPDynamicAttr_BrightDefectThreshOffset(void)
{
	reg_api_test_fn(test_DPC_DPDynamicAttr_BrightDefectThreshOffset);
}

static int test_DPC_DPDynamicAttr_TransitionWeight(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DP_DYNAMIC_ATTR_S attr;

	ret = CVI_ISP_GetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDPDynamicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.TransitionWeight != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.TransitionWeight);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.TransitionWeight = 0;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "TransitionWeight", "min");
	// set maximum value
	attr.TransitionWeight = 255;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "TransitionWeight", "max");
	// set random value
	attr.TransitionWeight = rand_range(0, 255);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "TransitionWeight", "random");
	// restore default value
	attr.TransitionWeight = 0;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DPC_DPDynamicAttr_TransitionWeight(void)
{
	reg_api_test_fn(test_DPC_DPDynamicAttr_TransitionWeight);
}

static int test_DPC_DPDynamicAttr_DefectCnt1_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DP_DYNAMIC_ATTR_S attr;

	ret = CVI_ISP_GetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDPDynamicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.DefectCnt1 != 4) {
		TEST_FAIL("test default value: 4 != %d\n", (int)attr.stManual.DefectCnt1);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.DefectCnt1 = 0;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DefectCnt1", "min");
	// set maximum value
	attr.stManual.DefectCnt1 = 16;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DefectCnt1", "max");
	// set random value
	attr.stManual.DefectCnt1 = rand_range(0, 16);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DefectCnt1", "random");
	// set abnormal value test
	attr.stManual.DefectCnt1 = rand_range(17, 255);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.DefectCnt1 = 4;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DPC_DPDynamicAttr_DefectCnt1_manual(void)
{
	reg_api_test_fn(test_DPC_DPDynamicAttr_DefectCnt1_manual);
}

static int test_DPC_DPDynamicAttr_DefectCnt1_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DP_DYNAMIC_ATTR_S attr;

	ret = CVI_ISP_GetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDPDynamicAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 };
	if (memcmp(default_val_0, attr.stAuto.DefectCnt1, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DefectCnt1[j] = 0;
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DefectCnt1", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DefectCnt1[j] = 16;
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DefectCnt1", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DefectCnt1[j] = rand_range(0, 16);
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DefectCnt1", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DefectCnt1[j] = rand_range(17, 255);
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 };
	memcpy(attr.stAuto.DefectCnt1, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DPC_DPDynamicAttr_DefectCnt1_auto(void)
{
	reg_api_test_fn(test_DPC_DPDynamicAttr_DefectCnt1_auto);
}

static int test_DPC_DPDynamicAttr_DefectCnt2_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DP_DYNAMIC_ATTR_S attr;

	ret = CVI_ISP_GetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDPDynamicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.DefectCnt2 != 2) {
		TEST_FAIL("test default value: 2 != %d\n", (int)attr.stManual.DefectCnt2);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.DefectCnt2 = 0;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DefectCnt2", "min");
	// set maximum value
	attr.stManual.DefectCnt2 = 16;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DefectCnt2", "max");
	// set random value
	attr.stManual.DefectCnt2 = rand_range(0, 16);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DefectCnt2", "random");
	// set abnormal value test
	attr.stManual.DefectCnt2 = rand_range(17, 255);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.DefectCnt2 = 2;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DPC_DPDynamicAttr_DefectCnt2_manual(void)
{
	reg_api_test_fn(test_DPC_DPDynamicAttr_DefectCnt2_manual);
}

static int test_DPC_DPDynamicAttr_DefectCnt2_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DP_DYNAMIC_ATTR_S attr;

	ret = CVI_ISP_GetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDPDynamicAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 };
	if (memcmp(default_val_0, attr.stAuto.DefectCnt2, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DefectCnt2[j] = 0;
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DefectCnt2", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DefectCnt2[j] = 16;
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DefectCnt2", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DefectCnt2[j] = rand_range(0, 16);
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "DefectCnt2", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.DefectCnt2[j] = rand_range(17, 255);
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 };
	memcpy(attr.stAuto.DefectCnt2, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DPC_DPDynamicAttr_DefectCnt2_auto(void)
{
	reg_api_test_fn(test_DPC_DPDynamicAttr_DefectCnt2_auto);
}

static int test_DPC_DPDynamicAttr_AdvMode_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DP_DYNAMIC_ATTR_S attr;

	ret = CVI_ISP_GetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDPDynamicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.AdvMode != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.stManual.AdvMode);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.AdvMode = 0;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "AdvMode", "min");
	// set maximum value
	attr.stManual.AdvMode = 1;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "AdvMode", "max");
	// set random value
	attr.stManual.AdvMode = rand_range(0, 1);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "AdvMode", "random");
	// set abnormal value test
	attr.stManual.AdvMode = rand_range(2, 255);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.AdvMode = 0;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DPC_DPDynamicAttr_AdvMode_manual(void)
{
	reg_api_test_fn(test_DPC_DPDynamicAttr_AdvMode_manual);
}

static int test_DPC_DPDynamicAttr_AdvMode_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DP_DYNAMIC_ATTR_S attr;

	ret = CVI_ISP_GetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDPDynamicAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	if (memcmp(default_val_0, attr.stAuto.AdvMode, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.AdvMode[j] = 0;
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "AdvMode", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.AdvMode[j] = 1;
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "AdvMode", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.AdvMode[j] = rand_range(0, 1);
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "AdvMode", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.AdvMode[j] = rand_range(2, 255);
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	memcpy(attr.stAuto.AdvMode, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DPC_DPDynamicAttr_AdvMode_auto(void)
{
	reg_api_test_fn(test_DPC_DPDynamicAttr_AdvMode_auto);
}

static int test_DPC_DPDynamicAttr_AvgMode_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DP_DYNAMIC_ATTR_S attr;

	ret = CVI_ISP_GetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDPDynamicAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.AvgMode != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.stManual.AvgMode);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.AvgMode = 0;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "AvgMode", "min");
	// set maximum value
	attr.stManual.AvgMode = 1;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "AvgMode", "max");
	// set random value
	attr.stManual.AvgMode = rand_range(0, 1);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "AvgMode", "random");
	// set abnormal value test
	attr.stManual.AvgMode = rand_range(2, 255);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.AvgMode = 1;
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DPC_DPDynamicAttr_AvgMode_manual(void)
{
	reg_api_test_fn(test_DPC_DPDynamicAttr_AvgMode_manual);
}

static int test_DPC_DPDynamicAttr_AvgMode_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_DP_DYNAMIC_ATTR_S attr;

	ret = CVI_ISP_GetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetDPDynamicAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	if (memcmp(default_val_0, attr.stAuto.AvgMode, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.AvgMode[j] = 0;
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "AvgMode", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.AvgMode[j] = 1;
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "AvgMode", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.AvgMode[j] = rand_range(0, 1);
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "DPC", "AvgMode", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.AvgMode[j] = rand_range(2, 255);
	}
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
	memcpy(attr.stAuto.AvgMode, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetDPDynamicAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_DPC_DPDynamicAttr_AvgMode_auto(void)
{
	reg_api_test_fn(test_DPC_DPDynamicAttr_AvgMode_auto);
}
