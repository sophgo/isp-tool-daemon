
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

static int test_LDCI_LDCIAttr_Enable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_LDCI_ATTR_S attr;

	ret = CVI_ISP_GetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetLDCIAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.Enable != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.Enable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.Enable = 0;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "Enable", "min");
	// set maximum value
	attr.Enable = 1;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "Enable", "max");
	// set random value
	attr.Enable = rand_range(0, 1);
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "Enable", "random");
	// restore default value
	attr.Enable = 1;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_LDCI_LDCIAttr_Enable(void)
{
	reg_api_test_fn(test_LDCI_LDCIAttr_Enable);
}

static int test_LDCI_LDCIAttr_enOpType(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_LDCI_ATTR_S attr;

	ret = CVI_ISP_GetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetLDCIAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.enOpType != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.enOpType);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.enOpType = OP_TYPE_AUTO;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "enOpType", "min");
	// set maximum value
	attr.enOpType = OP_TYPE_MANUAL;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "enOpType", "max");
	// restore default value
	attr.enOpType = 0;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_LDCI_LDCIAttr_enOpType(void)
{
	reg_api_test_fn(test_LDCI_LDCIAttr_enOpType);
}

static int test_LDCI_LDCIAttr_UpdateInterval(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_LDCI_ATTR_S attr;

	ret = CVI_ISP_GetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetLDCIAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.UpdateInterval != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.UpdateInterval);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.UpdateInterval = 0;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "UpdateInterval", "min");
	// set maximum value
	attr.UpdateInterval = 255;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "UpdateInterval", "max");
	// set random value
	attr.UpdateInterval = rand_range(0, 255);
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "UpdateInterval", "random");
	// restore default value
	attr.UpdateInterval = 1;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_LDCI_LDCIAttr_UpdateInterval(void)
{
	reg_api_test_fn(test_LDCI_LDCIAttr_UpdateInterval);
}

static int test_LDCI_LDCIAttr_BlockNum(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_LDCI_ATTR_S attr;

	ret = CVI_ISP_GetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetLDCIAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.BlockNum != 62) {
		TEST_FAIL("test default value: 62 != %d\n", (int)attr.BlockNum);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.BlockNum = 32;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "BlockNum", "min");
	// set maximum value
	attr.BlockNum = 62;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "BlockNum", "max");
	// set random value
	attr.BlockNum = rand_range(32, 62);
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "BlockNum", "random");
	// set abnormal value test
	attr.BlockNum = rand_range(0, 31);
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.BlockNum = 62;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_LDCI_LDCIAttr_BlockNum(void)
{
	reg_api_test_fn(test_LDCI_LDCIAttr_BlockNum);
}

static int test_LDCI_LDCIAttr_DRCLinkEnable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_LDCI_ATTR_S attr;

	ret = CVI_ISP_GetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetLDCIAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.DRCLinkEnable != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.DRCLinkEnable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.DRCLinkEnable = 0;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "DRCLinkEnable", "min");
	// set maximum value
	attr.DRCLinkEnable = 1;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "DRCLinkEnable", "max");
	// set random value
	attr.DRCLinkEnable = rand_range(0, 1);
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "DRCLinkEnable", "random");
	// set abnormal value test
	attr.DRCLinkEnable = rand_range(2, 255);
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.DRCLinkEnable = 0;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_LDCI_LDCIAttr_DRCLinkEnable(void)
{
	reg_api_test_fn(test_LDCI_LDCIAttr_DRCLinkEnable);
}

static int test_LDCI_LDCIAttr_DRCLinkAtten(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_LDCI_ATTR_S attr;

	ret = CVI_ISP_GetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetLDCIAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val[17] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	if (memcmp(default_val, attr.DRCLinkAtten, sizeof(CVI_U8) * 17) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int i = 0; i < 17; ++i) {
		attr.DRCLinkAtten[i] = 0;
	}
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "DRCLinkAtten", "min");
	// set maximum value
	for (int i = 0; i < 17; ++i) {
		attr.DRCLinkAtten[i] = 255;
	}
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "DRCLinkAtten", "max");
	// set random value
	for (int i = 0; i < 17; i++) {
		attr.DRCLinkAtten[i] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "DRCLinkAtten", "random");
	// restore default value
	memcpy(attr.DRCLinkAtten, default_val, sizeof(CVI_U8) * 17);
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_LDCI_LDCIAttr_DRCLinkAtten(void)
{
	reg_api_test_fn(test_LDCI_LDCIAttr_DRCLinkAtten);
}

static int test_LDCI_LDCIAttr_LdciStrength_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_LDCI_ATTR_S attr;

	ret = CVI_ISP_GetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetLDCIAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.LdciStrength[0] != 20) {
		TEST_FAIL("test default value: 20 != %d\n", (int)attr.stManual.LdciStrength[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.LdciStrength[1] != 80) {
		TEST_FAIL("test default value: 80 != %d\n", (int)attr.stManual.LdciStrength[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.LdciStrength[2] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.LdciStrength[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.LdciStrength[3] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.LdciStrength[3]);
		return CVI_FAILURE;
	}
	if (attr.stManual.LdciStrength[4] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.LdciStrength[4]);
		return CVI_FAILURE;
	}
	if (attr.stManual.LdciStrength[5] != 96) {
		TEST_FAIL("test default value: 96 != %d\n", (int)attr.stManual.LdciStrength[5]);
		return CVI_FAILURE;
	}
	if (attr.stManual.LdciStrength[6] != 64) {
		TEST_FAIL("test default value: 64 != %d\n", (int)attr.stManual.LdciStrength[6]);
		return CVI_FAILURE;
	}
	if (attr.stManual.LdciStrength[7] != 64) {
		TEST_FAIL("test default value: 64 != %d\n", (int)attr.stManual.LdciStrength[7]);
		return CVI_FAILURE;
	}
	if (attr.stManual.LdciStrength[8] != 64) {
		TEST_FAIL("test default value: 64 != %d\n", (int)attr.stManual.LdciStrength[8]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.LdciStrength[0] = 0;
	attr.stManual.LdciStrength[1] = 0;
	attr.stManual.LdciStrength[2] = 0;
	attr.stManual.LdciStrength[3] = 0;
	attr.stManual.LdciStrength[4] = 0;
	attr.stManual.LdciStrength[5] = 0;
	attr.stManual.LdciStrength[6] = 0;
	attr.stManual.LdciStrength[7] = 0;
	attr.stManual.LdciStrength[8] = 0;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "LdciStrength", "min");
	// set maximum value
	attr.stManual.LdciStrength[0] = 255;
	attr.stManual.LdciStrength[1] = 255;
	attr.stManual.LdciStrength[2] = 255;
	attr.stManual.LdciStrength[3] = 255;
	attr.stManual.LdciStrength[4] = 255;
	attr.stManual.LdciStrength[5] = 255;
	attr.stManual.LdciStrength[6] = 255;
	attr.stManual.LdciStrength[7] = 255;
	attr.stManual.LdciStrength[8] = 255;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "LdciStrength", "max");
	// set random value
	attr.stManual.LdciStrength[0] = rand_range(0, 255);
	attr.stManual.LdciStrength[1] = rand_range(0, 255);
	attr.stManual.LdciStrength[2] = rand_range(0, 255);
	attr.stManual.LdciStrength[3] = rand_range(0, 255);
	attr.stManual.LdciStrength[4] = rand_range(0, 255);
	attr.stManual.LdciStrength[5] = rand_range(0, 255);
	attr.stManual.LdciStrength[6] = rand_range(0, 255);
	attr.stManual.LdciStrength[7] = rand_range(0, 255);
	attr.stManual.LdciStrength[8] = rand_range(0, 255);
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "LdciStrength", "random");
	// restore default value
	attr.stManual.LdciStrength[0] = 20;
	attr.stManual.LdciStrength[1] = 80;
	attr.stManual.LdciStrength[2] = 128;
	attr.stManual.LdciStrength[3] = 128;
	attr.stManual.LdciStrength[4] = 128;
	attr.stManual.LdciStrength[5] = 96;
	attr.stManual.LdciStrength[6] = 64;
	attr.stManual.LdciStrength[7] = 64;
	attr.stManual.LdciStrength[8] = 64;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_LDCI_LDCIAttr_LdciStrength_manual(void)
{
	reg_api_test_fn(test_LDCI_LDCIAttr_LdciStrength_manual);
}

static int test_LDCI_LDCIAttr_LdciStrength_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_LDCI_ATTR_S attr;

	ret = CVI_ISP_GetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetLDCIAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.LdciStrength[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.LdciStrength[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.LdciStrength[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.LdciStrength[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.LdciStrength[j][4] != default_val_4[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.LdciStrength[j][5] != default_val_5[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.LdciStrength[j][6] != default_val_6[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.LdciStrength[j][7] != default_val_7[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U8 default_val_8[ISP_AUTO_ISO_STRENGTH_NUM] = { 64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.LdciStrength[j][8] != default_val_8[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][3] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][4] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][5] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][6] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][7] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][8] = 0;
	}
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "LdciStrength", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][0] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][1] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][2] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][3] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][4] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][5] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][6] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][7] = 255;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][8] = 255;
	}
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "LdciStrength", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][0] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][1] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][2] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][3] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][4] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][5] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][6] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][7] = rand_range(0, 255);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][8] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "LdciStrength", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][0] = restore_val_0[j];
	}
	CVI_U8 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][1] = restore_val_1[j];
	}
	CVI_U8 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][2] = restore_val_2[j];
	}
	CVI_U8 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][3] = restore_val_3[j];
	}
	CVI_U8 restore_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][4] = restore_val_4[j];
	}
	CVI_U8 restore_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][5] = restore_val_5[j];
	}
	CVI_U8 restore_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][6] = restore_val_6[j];
	}
	CVI_U8 restore_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][7] = restore_val_7[j];
	}
	CVI_U8 restore_val_8[ISP_AUTO_ISO_STRENGTH_NUM] = { 64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciStrength[j][8] = restore_val_8[j];
	}
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_LDCI_LDCIAttr_LdciStrength_auto(void)
{
	reg_api_test_fn(test_LDCI_LDCIAttr_LdciStrength_auto);
}

static int test_LDCI_LDCIAttr_AdaptiveGainMax_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_LDCI_ATTR_S attr;

	ret = CVI_ISP_GetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetLDCIAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.AdaptiveGainMax != 40) {
		TEST_FAIL("test default value: 40 != %d\n", (int)attr.stManual.AdaptiveGainMax);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.AdaptiveGainMax = 0;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "AdaptiveGainMax", "min");
	// set maximum value
	attr.stManual.AdaptiveGainMax = 255;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "AdaptiveGainMax", "max");
	// set random value
	attr.stManual.AdaptiveGainMax = rand_range(0, 255);
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "AdaptiveGainMax", "random");
	// restore default value
	attr.stManual.AdaptiveGainMax = 40;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_LDCI_LDCIAttr_AdaptiveGainMax_manual(void)
{
	reg_api_test_fn(test_LDCI_LDCIAttr_AdaptiveGainMax_manual);
}

static int test_LDCI_LDCIAttr_AdaptiveGainMax_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_LDCI_ATTR_S attr;

	ret = CVI_ISP_GetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetLDCIAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40 };
	if (memcmp(default_val_0, attr.stAuto.AdaptiveGainMax, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.AdaptiveGainMax[j] = 0;
	}
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "AdaptiveGainMax", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.AdaptiveGainMax[j] = 255;
	}
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "AdaptiveGainMax", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.AdaptiveGainMax[j] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "AdaptiveGainMax", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40 };
	memcpy(attr.stAuto.AdaptiveGainMax, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_LDCI_LDCIAttr_AdaptiveGainMax_auto(void)
{
	reg_api_test_fn(test_LDCI_LDCIAttr_AdaptiveGainMax_auto);
}

static int test_LDCI_LDCIAttr_AdaptiveGainMin_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_LDCI_ATTR_S attr;

	ret = CVI_ISP_GetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetLDCIAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.AdaptiveGainMin != 24) {
		TEST_FAIL("test default value: 24 != %d\n", (int)attr.stManual.AdaptiveGainMin);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.AdaptiveGainMin = 0;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "AdaptiveGainMin", "min");
	// set maximum value
	attr.stManual.AdaptiveGainMin = 255;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "AdaptiveGainMin", "max");
	// set random value
	attr.stManual.AdaptiveGainMin = rand_range(0, 255);
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "AdaptiveGainMin", "random");
	// restore default value
	attr.stManual.AdaptiveGainMin = 24;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_LDCI_LDCIAttr_AdaptiveGainMin_manual(void)
{
	reg_api_test_fn(test_LDCI_LDCIAttr_AdaptiveGainMin_manual);
}

static int test_LDCI_LDCIAttr_AdaptiveGainMin_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_LDCI_ATTR_S attr;

	ret = CVI_ISP_GetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetLDCIAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 };
	if (memcmp(default_val_0, attr.stAuto.AdaptiveGainMin, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.AdaptiveGainMin[j] = 0;
	}
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "AdaptiveGainMin", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.AdaptiveGainMin[j] = 255;
	}
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "AdaptiveGainMin", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.AdaptiveGainMin[j] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "AdaptiveGainMin", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 };
	memcpy(attr.stAuto.AdaptiveGainMin, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_LDCI_LDCIAttr_AdaptiveGainMin_auto(void)
{
	reg_api_test_fn(test_LDCI_LDCIAttr_AdaptiveGainMin_auto);
}

static int test_LDCI_LDCIAttr_FBCStrength_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_LDCI_ATTR_S attr;

	ret = CVI_ISP_GetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetLDCIAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.FBCStrength != 2) {
		TEST_FAIL("test default value: 2 != %d\n", (int)attr.stManual.FBCStrength);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.FBCStrength = 0;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "FBCStrength", "min");
	// set maximum value
	attr.stManual.FBCStrength = 31;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "FBCStrength", "max");
	// set random value
	attr.stManual.FBCStrength = rand_range(0, 31);
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "FBCStrength", "random");
	// set abnormal value test
	attr.stManual.FBCStrength = rand_range(32, 255);
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.FBCStrength = 2;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_LDCI_LDCIAttr_FBCStrength_manual(void)
{
	reg_api_test_fn(test_LDCI_LDCIAttr_FBCStrength_manual);
}

static int test_LDCI_LDCIAttr_FBCStrength_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_LDCI_ATTR_S attr;

	ret = CVI_ISP_GetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetLDCIAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 };
	if (memcmp(default_val_0, attr.stAuto.FBCStrength, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.FBCStrength[j] = 0;
	}
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "FBCStrength", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.FBCStrength[j] = 31;
	}
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "FBCStrength", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.FBCStrength[j] = rand_range(0, 31);
	}
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "FBCStrength", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.FBCStrength[j] = rand_range(32, 255);
	}
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 };
	memcpy(attr.stAuto.FBCStrength, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_LDCI_LDCIAttr_FBCStrength_auto(void)
{
	reg_api_test_fn(test_LDCI_LDCIAttr_FBCStrength_auto);
}

static int test_LDCI_LDCIAttr_LdciThres1_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_LDCI_ATTR_S attr;

	ret = CVI_ISP_GetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetLDCIAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.LdciThres1 != 3) {
		TEST_FAIL("test default value: 3 != %d\n", (int)attr.stManual.LdciThres1);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.LdciThres1 = 0;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "LdciThres1", "min");
	// set maximum value
	attr.stManual.LdciThres1 = 255;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "LdciThres1", "max");
	// set random value
	attr.stManual.LdciThres1 = rand_range(0, 255);
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "LdciThres1", "random");
	// restore default value
	attr.stManual.LdciThres1 = 3;
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_LDCI_LDCIAttr_LdciThres1_manual(void)
{
	reg_api_test_fn(test_LDCI_LDCIAttr_LdciThres1_manual);
}

static int test_LDCI_LDCIAttr_LdciThres1_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_LDCI_ATTR_S attr;

	ret = CVI_ISP_GetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetLDCIAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 };
	if (memcmp(default_val_0, attr.stAuto.LdciThres1, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciThres1[j] = 0;
	}
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "LdciThres1", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciThres1[j] = 255;
	}
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "LdciThres1", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.LdciThres1[j] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "LDCI", "LdciThres1", "random");
	// restore default value
	CVI_U8 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 };
	memcpy(attr.stAuto.LdciThres1, restore_val_0, sizeof(CVI_U8) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetLDCIAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_LDCI_LDCIAttr_LdciThres1_auto(void)
{
	reg_api_test_fn(test_LDCI_LDCIAttr_LdciThres1_auto);
}
