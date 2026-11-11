
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

static int test_CA_CAAttr_Enable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CA_ATTR_S attr;

	ret = CVI_ISP_GetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.Enable != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.Enable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.Enable = 0;
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "Enable", "min");
	// set maximum value
	attr.Enable = 1;
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "Enable", "max");
	// set random value
	attr.Enable = rand_range(0, 1);
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "Enable", "random");
	// restore default value
	attr.Enable = 0;
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CA_CAAttr_Enable(void)
{
	reg_api_test_fn(test_CA_CAAttr_Enable);
}

static int test_CA_CAAttr_enOpType(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CA_ATTR_S attr;

	ret = CVI_ISP_GetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.enOpType != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.enOpType);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.enOpType = OP_TYPE_AUTO;
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "enOpType", "min");
	// set maximum value
	attr.enOpType = OP_TYPE_MANUAL;
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "enOpType", "max");
	// restore default value
	attr.enOpType = 0;
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CA_CAAttr_enOpType(void)
{
	reg_api_test_fn(test_CA_CAAttr_enOpType);
}

static int test_CA_CAAttr_UpdateInterval(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CA_ATTR_S attr;

	ret = CVI_ISP_GetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.UpdateInterval != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.UpdateInterval);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.UpdateInterval = 1;
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "UpdateInterval", "min");
	// set maximum value
	attr.UpdateInterval = 255;
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "UpdateInterval", "max");
	// set random value
	attr.UpdateInterval = rand_range(1, 255);
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "UpdateInterval", "random");
	// set abnormal value test
	attr.UpdateInterval = rand_range(0, 0);
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.UpdateInterval = 1;
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CA_CAAttr_UpdateInterval(void)
{
	reg_api_test_fn(test_CA_CAAttr_UpdateInterval);
}

static int test_CA_CAAttr_CaCpMode(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CA_ATTR_S attr;

	ret = CVI_ISP_GetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.CaCpMode != 0) {
		TEST_FAIL("test default value: 0 != %d\n", (int)attr.CaCpMode);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.CaCpMode = 0;
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "CaCpMode", "min");
	// set maximum value
	attr.CaCpMode = 1;
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "CaCpMode", "max");
	// set random value
	attr.CaCpMode = rand_range(0, 1);
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "CaCpMode", "random");
	// restore default value
	attr.CaCpMode = 0;
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CA_CAAttr_CaCpMode(void)
{
	reg_api_test_fn(test_CA_CAAttr_CaCpMode);
}

static int test_CA_CAAttr_CPLutY(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CA_ATTR_S attr;

	ret = CVI_ISP_GetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val[256] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255 };
	if (memcmp(default_val, attr.CPLutY, sizeof(CVI_U8) * 256) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int i = 0; i < 256; ++i) {
		attr.CPLutY[i] = 0;
	}
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "CPLutY", "min");
	// set maximum value
	for (int i = 0; i < 256; ++i) {
		attr.CPLutY[i] = 255;
	}
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "CPLutY", "max");
	// set random value
	for (int i = 0; i < 256; i++) {
		attr.CPLutY[i] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "CPLutY", "random");
	// restore default value
	memcpy(attr.CPLutY, default_val, sizeof(CVI_U8) * 256);
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CA_CAAttr_CPLutY(void)
{
	reg_api_test_fn(test_CA_CAAttr_CPLutY);
}

static int test_CA_CAAttr_CPLutU(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CA_ATTR_S attr;

	ret = CVI_ISP_GetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val[256] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255 };
	if (memcmp(default_val, attr.CPLutU, sizeof(CVI_U8) * 256) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int i = 0; i < 256; ++i) {
		attr.CPLutU[i] = 0;
	}
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "CPLutU", "min");
	// set maximum value
	for (int i = 0; i < 256; ++i) {
		attr.CPLutU[i] = 255;
	}
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "CPLutU", "max");
	// set random value
	for (int i = 0; i < 256; i++) {
		attr.CPLutU[i] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "CPLutU", "random");
	// restore default value
	memcpy(attr.CPLutU, default_val, sizeof(CVI_U8) * 256);
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CA_CAAttr_CPLutU(void)
{
	reg_api_test_fn(test_CA_CAAttr_CPLutU);
}

static int test_CA_CAAttr_CPLutV(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CA_ATTR_S attr;

	ret = CVI_ISP_GetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U8 default_val[256] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255 };
	if (memcmp(default_val, attr.CPLutV, sizeof(CVI_U8) * 256) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int i = 0; i < 256; ++i) {
		attr.CPLutV[i] = 0;
	}
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "CPLutV", "min");
	// set maximum value
	for (int i = 0; i < 256; ++i) {
		attr.CPLutV[i] = 255;
	}
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "CPLutV", "max");
	// set random value
	for (int i = 0; i < 256; i++) {
		attr.CPLutV[i] = rand_range(0, 255);
	}
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "CPLutV", "random");
	// restore default value
	memcpy(attr.CPLutV, default_val, sizeof(CVI_U8) * 256);
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CA_CAAttr_CPLutV(void)
{
	reg_api_test_fn(test_CA_CAAttr_CPLutV);
}

static int test_CA_CAAttr_ISORatio_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CA_ATTR_S attr;

	ret = CVI_ISP_GetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.ISORatio != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.ISORatio);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.ISORatio = 0;
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "ISORatio", "min");
	// set maximum value
	attr.stManual.ISORatio = 2047;
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "ISORatio", "max");
	// set random value
	attr.stManual.ISORatio = rand_range(0, 2047);
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "ISORatio", "random");
	// set abnormal value test
	attr.stManual.ISORatio = rand_range(2048, 65535);
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.ISORatio = 128;
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CA_CAAttr_ISORatio_manual(void)
{
	reg_api_test_fn(test_CA_CAAttr_ISORatio_manual);
}

static int test_CA_CAAttr_ISORatio_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CA_ATTR_S attr;

	ret = CVI_ISP_GetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U16 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	if (memcmp(default_val_0, attr.stAuto.ISORatio, sizeof(CVI_U16) * ISP_AUTO_ISO_STRENGTH_NUM) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.ISORatio[j] = 0;
	}
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "ISORatio", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.ISORatio[j] = 2047;
	}
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "ISORatio", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.ISORatio[j] = rand_range(0, 2047);
	}
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "ISORatio", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.ISORatio[j] = rand_range(2048, 65535);
	}
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U16 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	memcpy(attr.stAuto.ISORatio, restore_val_0, sizeof(CVI_U16) * ISP_AUTO_ISO_STRENGTH_NUM);
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CA_CAAttr_ISORatio_auto(void)
{
	reg_api_test_fn(test_CA_CAAttr_ISORatio_auto);
}

static int test_CA_CAAttr_YRatioLut_manual(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CA_ATTR_S attr;

	ret = CVI_ISP_GetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.stManual.YRatioLut[0] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[0]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[1] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[1]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[2] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[2]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[3] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[3]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[4] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[4]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[5] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[5]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[6] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[6]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[7] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[7]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[8] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[8]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[9] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[9]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[10] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[10]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[11] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[11]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[12] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[12]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[13] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[13]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[14] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[14]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[15] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[15]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[16] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[16]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[17] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[17]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[18] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[18]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[19] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[19]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[20] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[20]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[21] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[21]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[22] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[22]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[23] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[23]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[24] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[24]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[25] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[25]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[26] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[26]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[27] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[27]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[28] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[28]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[29] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[29]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[30] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[30]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[31] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[31]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[32] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[32]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[33] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[33]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[34] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[34]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[35] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[35]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[36] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[36]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[37] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[37]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[38] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[38]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[39] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[39]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[40] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[40]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[41] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[41]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[42] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[42]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[43] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[43]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[44] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[44]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[45] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[45]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[46] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[46]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[47] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[47]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[48] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[48]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[49] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[49]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[50] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[50]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[51] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[51]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[52] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[52]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[53] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[53]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[54] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[54]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[55] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[55]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[56] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[56]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[57] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[57]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[58] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[58]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[59] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[59]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[60] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[60]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[61] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[61]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[62] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[62]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[63] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[63]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[64] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[64]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[65] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[65]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[66] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[66]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[67] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[67]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[68] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[68]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[69] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[69]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[70] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[70]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[71] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[71]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[72] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[72]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[73] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[73]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[74] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[74]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[75] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[75]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[76] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[76]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[77] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[77]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[78] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[78]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[79] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[79]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[80] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[80]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[81] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[81]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[82] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[82]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[83] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[83]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[84] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[84]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[85] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[85]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[86] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[86]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[87] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[87]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[88] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[88]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[89] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[89]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[90] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[90]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[91] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[91]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[92] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[92]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[93] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[93]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[94] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[94]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[95] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[95]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[96] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[96]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[97] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[97]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[98] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[98]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[99] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[99]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[100] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[100]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[101] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[101]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[102] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[102]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[103] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[103]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[104] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[104]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[105] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[105]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[106] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[106]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[107] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[107]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[108] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[108]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[109] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[109]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[110] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[110]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[111] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[111]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[112] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[112]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[113] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[113]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[114] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[114]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[115] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[115]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[116] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[116]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[117] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[117]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[118] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[118]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[119] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[119]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[120] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[120]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[121] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[121]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[122] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[122]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[123] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[123]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[124] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[124]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[125] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[125]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[126] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[126]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[127] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[127]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[128] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[128]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[129] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[129]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[130] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[130]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[131] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[131]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[132] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[132]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[133] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[133]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[134] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[134]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[135] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[135]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[136] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[136]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[137] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[137]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[138] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[138]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[139] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[139]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[140] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[140]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[141] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[141]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[142] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[142]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[143] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[143]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[144] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[144]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[145] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[145]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[146] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[146]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[147] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[147]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[148] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[148]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[149] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[149]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[150] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[150]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[151] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[151]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[152] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[152]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[153] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[153]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[154] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[154]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[155] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[155]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[156] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[156]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[157] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[157]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[158] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[158]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[159] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[159]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[160] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[160]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[161] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[161]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[162] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[162]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[163] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[163]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[164] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[164]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[165] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[165]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[166] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[166]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[167] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[167]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[168] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[168]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[169] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[169]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[170] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[170]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[171] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[171]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[172] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[172]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[173] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[173]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[174] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[174]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[175] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[175]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[176] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[176]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[177] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[177]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[178] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[178]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[179] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[179]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[180] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[180]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[181] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[181]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[182] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[182]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[183] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[183]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[184] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[184]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[185] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[185]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[186] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[186]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[187] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[187]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[188] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[188]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[189] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[189]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[190] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[190]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[191] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[191]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[192] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[192]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[193] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[193]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[194] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[194]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[195] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[195]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[196] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[196]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[197] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[197]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[198] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[198]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[199] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[199]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[200] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[200]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[201] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[201]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[202] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[202]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[203] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[203]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[204] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[204]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[205] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[205]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[206] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[206]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[207] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[207]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[208] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[208]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[209] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[209]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[210] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[210]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[211] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[211]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[212] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[212]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[213] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[213]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[214] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[214]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[215] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[215]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[216] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[216]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[217] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[217]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[218] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[218]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[219] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[219]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[220] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[220]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[221] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[221]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[222] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[222]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[223] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[223]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[224] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[224]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[225] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[225]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[226] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[226]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[227] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[227]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[228] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[228]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[229] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[229]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[230] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[230]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[231] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[231]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[232] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[232]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[233] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[233]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[234] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[234]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[235] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[235]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[236] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[236]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[237] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[237]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[238] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[238]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[239] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[239]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[240] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[240]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[241] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[241]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[242] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[242]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[243] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[243]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[244] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[244]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[245] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[245]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[246] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[246]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[247] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[247]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[248] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[248]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[249] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[249]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[250] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[250]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[251] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[251]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[252] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[252]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[253] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[253]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[254] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[254]);
		return CVI_FAILURE;
	}
	if (attr.stManual.YRatioLut[255] != 128) {
		TEST_FAIL("test default value: 128 != %d\n", (int)attr.stManual.YRatioLut[255]);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.stManual.YRatioLut[0] = 0;
	attr.stManual.YRatioLut[1] = 0;
	attr.stManual.YRatioLut[2] = 0;
	attr.stManual.YRatioLut[3] = 0;
	attr.stManual.YRatioLut[4] = 0;
	attr.stManual.YRatioLut[5] = 0;
	attr.stManual.YRatioLut[6] = 0;
	attr.stManual.YRatioLut[7] = 0;
	attr.stManual.YRatioLut[8] = 0;
	attr.stManual.YRatioLut[9] = 0;
	attr.stManual.YRatioLut[10] = 0;
	attr.stManual.YRatioLut[11] = 0;
	attr.stManual.YRatioLut[12] = 0;
	attr.stManual.YRatioLut[13] = 0;
	attr.stManual.YRatioLut[14] = 0;
	attr.stManual.YRatioLut[15] = 0;
	attr.stManual.YRatioLut[16] = 0;
	attr.stManual.YRatioLut[17] = 0;
	attr.stManual.YRatioLut[18] = 0;
	attr.stManual.YRatioLut[19] = 0;
	attr.stManual.YRatioLut[20] = 0;
	attr.stManual.YRatioLut[21] = 0;
	attr.stManual.YRatioLut[22] = 0;
	attr.stManual.YRatioLut[23] = 0;
	attr.stManual.YRatioLut[24] = 0;
	attr.stManual.YRatioLut[25] = 0;
	attr.stManual.YRatioLut[26] = 0;
	attr.stManual.YRatioLut[27] = 0;
	attr.stManual.YRatioLut[28] = 0;
	attr.stManual.YRatioLut[29] = 0;
	attr.stManual.YRatioLut[30] = 0;
	attr.stManual.YRatioLut[31] = 0;
	attr.stManual.YRatioLut[32] = 0;
	attr.stManual.YRatioLut[33] = 0;
	attr.stManual.YRatioLut[34] = 0;
	attr.stManual.YRatioLut[35] = 0;
	attr.stManual.YRatioLut[36] = 0;
	attr.stManual.YRatioLut[37] = 0;
	attr.stManual.YRatioLut[38] = 0;
	attr.stManual.YRatioLut[39] = 0;
	attr.stManual.YRatioLut[40] = 0;
	attr.stManual.YRatioLut[41] = 0;
	attr.stManual.YRatioLut[42] = 0;
	attr.stManual.YRatioLut[43] = 0;
	attr.stManual.YRatioLut[44] = 0;
	attr.stManual.YRatioLut[45] = 0;
	attr.stManual.YRatioLut[46] = 0;
	attr.stManual.YRatioLut[47] = 0;
	attr.stManual.YRatioLut[48] = 0;
	attr.stManual.YRatioLut[49] = 0;
	attr.stManual.YRatioLut[50] = 0;
	attr.stManual.YRatioLut[51] = 0;
	attr.stManual.YRatioLut[52] = 0;
	attr.stManual.YRatioLut[53] = 0;
	attr.stManual.YRatioLut[54] = 0;
	attr.stManual.YRatioLut[55] = 0;
	attr.stManual.YRatioLut[56] = 0;
	attr.stManual.YRatioLut[57] = 0;
	attr.stManual.YRatioLut[58] = 0;
	attr.stManual.YRatioLut[59] = 0;
	attr.stManual.YRatioLut[60] = 0;
	attr.stManual.YRatioLut[61] = 0;
	attr.stManual.YRatioLut[62] = 0;
	attr.stManual.YRatioLut[63] = 0;
	attr.stManual.YRatioLut[64] = 0;
	attr.stManual.YRatioLut[65] = 0;
	attr.stManual.YRatioLut[66] = 0;
	attr.stManual.YRatioLut[67] = 0;
	attr.stManual.YRatioLut[68] = 0;
	attr.stManual.YRatioLut[69] = 0;
	attr.stManual.YRatioLut[70] = 0;
	attr.stManual.YRatioLut[71] = 0;
	attr.stManual.YRatioLut[72] = 0;
	attr.stManual.YRatioLut[73] = 0;
	attr.stManual.YRatioLut[74] = 0;
	attr.stManual.YRatioLut[75] = 0;
	attr.stManual.YRatioLut[76] = 0;
	attr.stManual.YRatioLut[77] = 0;
	attr.stManual.YRatioLut[78] = 0;
	attr.stManual.YRatioLut[79] = 0;
	attr.stManual.YRatioLut[80] = 0;
	attr.stManual.YRatioLut[81] = 0;
	attr.stManual.YRatioLut[82] = 0;
	attr.stManual.YRatioLut[83] = 0;
	attr.stManual.YRatioLut[84] = 0;
	attr.stManual.YRatioLut[85] = 0;
	attr.stManual.YRatioLut[86] = 0;
	attr.stManual.YRatioLut[87] = 0;
	attr.stManual.YRatioLut[88] = 0;
	attr.stManual.YRatioLut[89] = 0;
	attr.stManual.YRatioLut[90] = 0;
	attr.stManual.YRatioLut[91] = 0;
	attr.stManual.YRatioLut[92] = 0;
	attr.stManual.YRatioLut[93] = 0;
	attr.stManual.YRatioLut[94] = 0;
	attr.stManual.YRatioLut[95] = 0;
	attr.stManual.YRatioLut[96] = 0;
	attr.stManual.YRatioLut[97] = 0;
	attr.stManual.YRatioLut[98] = 0;
	attr.stManual.YRatioLut[99] = 0;
	attr.stManual.YRatioLut[100] = 0;
	attr.stManual.YRatioLut[101] = 0;
	attr.stManual.YRatioLut[102] = 0;
	attr.stManual.YRatioLut[103] = 0;
	attr.stManual.YRatioLut[104] = 0;
	attr.stManual.YRatioLut[105] = 0;
	attr.stManual.YRatioLut[106] = 0;
	attr.stManual.YRatioLut[107] = 0;
	attr.stManual.YRatioLut[108] = 0;
	attr.stManual.YRatioLut[109] = 0;
	attr.stManual.YRatioLut[110] = 0;
	attr.stManual.YRatioLut[111] = 0;
	attr.stManual.YRatioLut[112] = 0;
	attr.stManual.YRatioLut[113] = 0;
	attr.stManual.YRatioLut[114] = 0;
	attr.stManual.YRatioLut[115] = 0;
	attr.stManual.YRatioLut[116] = 0;
	attr.stManual.YRatioLut[117] = 0;
	attr.stManual.YRatioLut[118] = 0;
	attr.stManual.YRatioLut[119] = 0;
	attr.stManual.YRatioLut[120] = 0;
	attr.stManual.YRatioLut[121] = 0;
	attr.stManual.YRatioLut[122] = 0;
	attr.stManual.YRatioLut[123] = 0;
	attr.stManual.YRatioLut[124] = 0;
	attr.stManual.YRatioLut[125] = 0;
	attr.stManual.YRatioLut[126] = 0;
	attr.stManual.YRatioLut[127] = 0;
	attr.stManual.YRatioLut[128] = 0;
	attr.stManual.YRatioLut[129] = 0;
	attr.stManual.YRatioLut[130] = 0;
	attr.stManual.YRatioLut[131] = 0;
	attr.stManual.YRatioLut[132] = 0;
	attr.stManual.YRatioLut[133] = 0;
	attr.stManual.YRatioLut[134] = 0;
	attr.stManual.YRatioLut[135] = 0;
	attr.stManual.YRatioLut[136] = 0;
	attr.stManual.YRatioLut[137] = 0;
	attr.stManual.YRatioLut[138] = 0;
	attr.stManual.YRatioLut[139] = 0;
	attr.stManual.YRatioLut[140] = 0;
	attr.stManual.YRatioLut[141] = 0;
	attr.stManual.YRatioLut[142] = 0;
	attr.stManual.YRatioLut[143] = 0;
	attr.stManual.YRatioLut[144] = 0;
	attr.stManual.YRatioLut[145] = 0;
	attr.stManual.YRatioLut[146] = 0;
	attr.stManual.YRatioLut[147] = 0;
	attr.stManual.YRatioLut[148] = 0;
	attr.stManual.YRatioLut[149] = 0;
	attr.stManual.YRatioLut[150] = 0;
	attr.stManual.YRatioLut[151] = 0;
	attr.stManual.YRatioLut[152] = 0;
	attr.stManual.YRatioLut[153] = 0;
	attr.stManual.YRatioLut[154] = 0;
	attr.stManual.YRatioLut[155] = 0;
	attr.stManual.YRatioLut[156] = 0;
	attr.stManual.YRatioLut[157] = 0;
	attr.stManual.YRatioLut[158] = 0;
	attr.stManual.YRatioLut[159] = 0;
	attr.stManual.YRatioLut[160] = 0;
	attr.stManual.YRatioLut[161] = 0;
	attr.stManual.YRatioLut[162] = 0;
	attr.stManual.YRatioLut[163] = 0;
	attr.stManual.YRatioLut[164] = 0;
	attr.stManual.YRatioLut[165] = 0;
	attr.stManual.YRatioLut[166] = 0;
	attr.stManual.YRatioLut[167] = 0;
	attr.stManual.YRatioLut[168] = 0;
	attr.stManual.YRatioLut[169] = 0;
	attr.stManual.YRatioLut[170] = 0;
	attr.stManual.YRatioLut[171] = 0;
	attr.stManual.YRatioLut[172] = 0;
	attr.stManual.YRatioLut[173] = 0;
	attr.stManual.YRatioLut[174] = 0;
	attr.stManual.YRatioLut[175] = 0;
	attr.stManual.YRatioLut[176] = 0;
	attr.stManual.YRatioLut[177] = 0;
	attr.stManual.YRatioLut[178] = 0;
	attr.stManual.YRatioLut[179] = 0;
	attr.stManual.YRatioLut[180] = 0;
	attr.stManual.YRatioLut[181] = 0;
	attr.stManual.YRatioLut[182] = 0;
	attr.stManual.YRatioLut[183] = 0;
	attr.stManual.YRatioLut[184] = 0;
	attr.stManual.YRatioLut[185] = 0;
	attr.stManual.YRatioLut[186] = 0;
	attr.stManual.YRatioLut[187] = 0;
	attr.stManual.YRatioLut[188] = 0;
	attr.stManual.YRatioLut[189] = 0;
	attr.stManual.YRatioLut[190] = 0;
	attr.stManual.YRatioLut[191] = 0;
	attr.stManual.YRatioLut[192] = 0;
	attr.stManual.YRatioLut[193] = 0;
	attr.stManual.YRatioLut[194] = 0;
	attr.stManual.YRatioLut[195] = 0;
	attr.stManual.YRatioLut[196] = 0;
	attr.stManual.YRatioLut[197] = 0;
	attr.stManual.YRatioLut[198] = 0;
	attr.stManual.YRatioLut[199] = 0;
	attr.stManual.YRatioLut[200] = 0;
	attr.stManual.YRatioLut[201] = 0;
	attr.stManual.YRatioLut[202] = 0;
	attr.stManual.YRatioLut[203] = 0;
	attr.stManual.YRatioLut[204] = 0;
	attr.stManual.YRatioLut[205] = 0;
	attr.stManual.YRatioLut[206] = 0;
	attr.stManual.YRatioLut[207] = 0;
	attr.stManual.YRatioLut[208] = 0;
	attr.stManual.YRatioLut[209] = 0;
	attr.stManual.YRatioLut[210] = 0;
	attr.stManual.YRatioLut[211] = 0;
	attr.stManual.YRatioLut[212] = 0;
	attr.stManual.YRatioLut[213] = 0;
	attr.stManual.YRatioLut[214] = 0;
	attr.stManual.YRatioLut[215] = 0;
	attr.stManual.YRatioLut[216] = 0;
	attr.stManual.YRatioLut[217] = 0;
	attr.stManual.YRatioLut[218] = 0;
	attr.stManual.YRatioLut[219] = 0;
	attr.stManual.YRatioLut[220] = 0;
	attr.stManual.YRatioLut[221] = 0;
	attr.stManual.YRatioLut[222] = 0;
	attr.stManual.YRatioLut[223] = 0;
	attr.stManual.YRatioLut[224] = 0;
	attr.stManual.YRatioLut[225] = 0;
	attr.stManual.YRatioLut[226] = 0;
	attr.stManual.YRatioLut[227] = 0;
	attr.stManual.YRatioLut[228] = 0;
	attr.stManual.YRatioLut[229] = 0;
	attr.stManual.YRatioLut[230] = 0;
	attr.stManual.YRatioLut[231] = 0;
	attr.stManual.YRatioLut[232] = 0;
	attr.stManual.YRatioLut[233] = 0;
	attr.stManual.YRatioLut[234] = 0;
	attr.stManual.YRatioLut[235] = 0;
	attr.stManual.YRatioLut[236] = 0;
	attr.stManual.YRatioLut[237] = 0;
	attr.stManual.YRatioLut[238] = 0;
	attr.stManual.YRatioLut[239] = 0;
	attr.stManual.YRatioLut[240] = 0;
	attr.stManual.YRatioLut[241] = 0;
	attr.stManual.YRatioLut[242] = 0;
	attr.stManual.YRatioLut[243] = 0;
	attr.stManual.YRatioLut[244] = 0;
	attr.stManual.YRatioLut[245] = 0;
	attr.stManual.YRatioLut[246] = 0;
	attr.stManual.YRatioLut[247] = 0;
	attr.stManual.YRatioLut[248] = 0;
	attr.stManual.YRatioLut[249] = 0;
	attr.stManual.YRatioLut[250] = 0;
	attr.stManual.YRatioLut[251] = 0;
	attr.stManual.YRatioLut[252] = 0;
	attr.stManual.YRatioLut[253] = 0;
	attr.stManual.YRatioLut[254] = 0;
	attr.stManual.YRatioLut[255] = 0;
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "YRatioLut", "min");
	// set maximum value
	attr.stManual.YRatioLut[0] = 2047;
	attr.stManual.YRatioLut[1] = 2047;
	attr.stManual.YRatioLut[2] = 2047;
	attr.stManual.YRatioLut[3] = 2047;
	attr.stManual.YRatioLut[4] = 2047;
	attr.stManual.YRatioLut[5] = 2047;
	attr.stManual.YRatioLut[6] = 2047;
	attr.stManual.YRatioLut[7] = 2047;
	attr.stManual.YRatioLut[8] = 2047;
	attr.stManual.YRatioLut[9] = 2047;
	attr.stManual.YRatioLut[10] = 2047;
	attr.stManual.YRatioLut[11] = 2047;
	attr.stManual.YRatioLut[12] = 2047;
	attr.stManual.YRatioLut[13] = 2047;
	attr.stManual.YRatioLut[14] = 2047;
	attr.stManual.YRatioLut[15] = 2047;
	attr.stManual.YRatioLut[16] = 2047;
	attr.stManual.YRatioLut[17] = 2047;
	attr.stManual.YRatioLut[18] = 2047;
	attr.stManual.YRatioLut[19] = 2047;
	attr.stManual.YRatioLut[20] = 2047;
	attr.stManual.YRatioLut[21] = 2047;
	attr.stManual.YRatioLut[22] = 2047;
	attr.stManual.YRatioLut[23] = 2047;
	attr.stManual.YRatioLut[24] = 2047;
	attr.stManual.YRatioLut[25] = 2047;
	attr.stManual.YRatioLut[26] = 2047;
	attr.stManual.YRatioLut[27] = 2047;
	attr.stManual.YRatioLut[28] = 2047;
	attr.stManual.YRatioLut[29] = 2047;
	attr.stManual.YRatioLut[30] = 2047;
	attr.stManual.YRatioLut[31] = 2047;
	attr.stManual.YRatioLut[32] = 2047;
	attr.stManual.YRatioLut[33] = 2047;
	attr.stManual.YRatioLut[34] = 2047;
	attr.stManual.YRatioLut[35] = 2047;
	attr.stManual.YRatioLut[36] = 2047;
	attr.stManual.YRatioLut[37] = 2047;
	attr.stManual.YRatioLut[38] = 2047;
	attr.stManual.YRatioLut[39] = 2047;
	attr.stManual.YRatioLut[40] = 2047;
	attr.stManual.YRatioLut[41] = 2047;
	attr.stManual.YRatioLut[42] = 2047;
	attr.stManual.YRatioLut[43] = 2047;
	attr.stManual.YRatioLut[44] = 2047;
	attr.stManual.YRatioLut[45] = 2047;
	attr.stManual.YRatioLut[46] = 2047;
	attr.stManual.YRatioLut[47] = 2047;
	attr.stManual.YRatioLut[48] = 2047;
	attr.stManual.YRatioLut[49] = 2047;
	attr.stManual.YRatioLut[50] = 2047;
	attr.stManual.YRatioLut[51] = 2047;
	attr.stManual.YRatioLut[52] = 2047;
	attr.stManual.YRatioLut[53] = 2047;
	attr.stManual.YRatioLut[54] = 2047;
	attr.stManual.YRatioLut[55] = 2047;
	attr.stManual.YRatioLut[56] = 2047;
	attr.stManual.YRatioLut[57] = 2047;
	attr.stManual.YRatioLut[58] = 2047;
	attr.stManual.YRatioLut[59] = 2047;
	attr.stManual.YRatioLut[60] = 2047;
	attr.stManual.YRatioLut[61] = 2047;
	attr.stManual.YRatioLut[62] = 2047;
	attr.stManual.YRatioLut[63] = 2047;
	attr.stManual.YRatioLut[64] = 2047;
	attr.stManual.YRatioLut[65] = 2047;
	attr.stManual.YRatioLut[66] = 2047;
	attr.stManual.YRatioLut[67] = 2047;
	attr.stManual.YRatioLut[68] = 2047;
	attr.stManual.YRatioLut[69] = 2047;
	attr.stManual.YRatioLut[70] = 2047;
	attr.stManual.YRatioLut[71] = 2047;
	attr.stManual.YRatioLut[72] = 2047;
	attr.stManual.YRatioLut[73] = 2047;
	attr.stManual.YRatioLut[74] = 2047;
	attr.stManual.YRatioLut[75] = 2047;
	attr.stManual.YRatioLut[76] = 2047;
	attr.stManual.YRatioLut[77] = 2047;
	attr.stManual.YRatioLut[78] = 2047;
	attr.stManual.YRatioLut[79] = 2047;
	attr.stManual.YRatioLut[80] = 2047;
	attr.stManual.YRatioLut[81] = 2047;
	attr.stManual.YRatioLut[82] = 2047;
	attr.stManual.YRatioLut[83] = 2047;
	attr.stManual.YRatioLut[84] = 2047;
	attr.stManual.YRatioLut[85] = 2047;
	attr.stManual.YRatioLut[86] = 2047;
	attr.stManual.YRatioLut[87] = 2047;
	attr.stManual.YRatioLut[88] = 2047;
	attr.stManual.YRatioLut[89] = 2047;
	attr.stManual.YRatioLut[90] = 2047;
	attr.stManual.YRatioLut[91] = 2047;
	attr.stManual.YRatioLut[92] = 2047;
	attr.stManual.YRatioLut[93] = 2047;
	attr.stManual.YRatioLut[94] = 2047;
	attr.stManual.YRatioLut[95] = 2047;
	attr.stManual.YRatioLut[96] = 2047;
	attr.stManual.YRatioLut[97] = 2047;
	attr.stManual.YRatioLut[98] = 2047;
	attr.stManual.YRatioLut[99] = 2047;
	attr.stManual.YRatioLut[100] = 2047;
	attr.stManual.YRatioLut[101] = 2047;
	attr.stManual.YRatioLut[102] = 2047;
	attr.stManual.YRatioLut[103] = 2047;
	attr.stManual.YRatioLut[104] = 2047;
	attr.stManual.YRatioLut[105] = 2047;
	attr.stManual.YRatioLut[106] = 2047;
	attr.stManual.YRatioLut[107] = 2047;
	attr.stManual.YRatioLut[108] = 2047;
	attr.stManual.YRatioLut[109] = 2047;
	attr.stManual.YRatioLut[110] = 2047;
	attr.stManual.YRatioLut[111] = 2047;
	attr.stManual.YRatioLut[112] = 2047;
	attr.stManual.YRatioLut[113] = 2047;
	attr.stManual.YRatioLut[114] = 2047;
	attr.stManual.YRatioLut[115] = 2047;
	attr.stManual.YRatioLut[116] = 2047;
	attr.stManual.YRatioLut[117] = 2047;
	attr.stManual.YRatioLut[118] = 2047;
	attr.stManual.YRatioLut[119] = 2047;
	attr.stManual.YRatioLut[120] = 2047;
	attr.stManual.YRatioLut[121] = 2047;
	attr.stManual.YRatioLut[122] = 2047;
	attr.stManual.YRatioLut[123] = 2047;
	attr.stManual.YRatioLut[124] = 2047;
	attr.stManual.YRatioLut[125] = 2047;
	attr.stManual.YRatioLut[126] = 2047;
	attr.stManual.YRatioLut[127] = 2047;
	attr.stManual.YRatioLut[128] = 2047;
	attr.stManual.YRatioLut[129] = 2047;
	attr.stManual.YRatioLut[130] = 2047;
	attr.stManual.YRatioLut[131] = 2047;
	attr.stManual.YRatioLut[132] = 2047;
	attr.stManual.YRatioLut[133] = 2047;
	attr.stManual.YRatioLut[134] = 2047;
	attr.stManual.YRatioLut[135] = 2047;
	attr.stManual.YRatioLut[136] = 2047;
	attr.stManual.YRatioLut[137] = 2047;
	attr.stManual.YRatioLut[138] = 2047;
	attr.stManual.YRatioLut[139] = 2047;
	attr.stManual.YRatioLut[140] = 2047;
	attr.stManual.YRatioLut[141] = 2047;
	attr.stManual.YRatioLut[142] = 2047;
	attr.stManual.YRatioLut[143] = 2047;
	attr.stManual.YRatioLut[144] = 2047;
	attr.stManual.YRatioLut[145] = 2047;
	attr.stManual.YRatioLut[146] = 2047;
	attr.stManual.YRatioLut[147] = 2047;
	attr.stManual.YRatioLut[148] = 2047;
	attr.stManual.YRatioLut[149] = 2047;
	attr.stManual.YRatioLut[150] = 2047;
	attr.stManual.YRatioLut[151] = 2047;
	attr.stManual.YRatioLut[152] = 2047;
	attr.stManual.YRatioLut[153] = 2047;
	attr.stManual.YRatioLut[154] = 2047;
	attr.stManual.YRatioLut[155] = 2047;
	attr.stManual.YRatioLut[156] = 2047;
	attr.stManual.YRatioLut[157] = 2047;
	attr.stManual.YRatioLut[158] = 2047;
	attr.stManual.YRatioLut[159] = 2047;
	attr.stManual.YRatioLut[160] = 2047;
	attr.stManual.YRatioLut[161] = 2047;
	attr.stManual.YRatioLut[162] = 2047;
	attr.stManual.YRatioLut[163] = 2047;
	attr.stManual.YRatioLut[164] = 2047;
	attr.stManual.YRatioLut[165] = 2047;
	attr.stManual.YRatioLut[166] = 2047;
	attr.stManual.YRatioLut[167] = 2047;
	attr.stManual.YRatioLut[168] = 2047;
	attr.stManual.YRatioLut[169] = 2047;
	attr.stManual.YRatioLut[170] = 2047;
	attr.stManual.YRatioLut[171] = 2047;
	attr.stManual.YRatioLut[172] = 2047;
	attr.stManual.YRatioLut[173] = 2047;
	attr.stManual.YRatioLut[174] = 2047;
	attr.stManual.YRatioLut[175] = 2047;
	attr.stManual.YRatioLut[176] = 2047;
	attr.stManual.YRatioLut[177] = 2047;
	attr.stManual.YRatioLut[178] = 2047;
	attr.stManual.YRatioLut[179] = 2047;
	attr.stManual.YRatioLut[180] = 2047;
	attr.stManual.YRatioLut[181] = 2047;
	attr.stManual.YRatioLut[182] = 2047;
	attr.stManual.YRatioLut[183] = 2047;
	attr.stManual.YRatioLut[184] = 2047;
	attr.stManual.YRatioLut[185] = 2047;
	attr.stManual.YRatioLut[186] = 2047;
	attr.stManual.YRatioLut[187] = 2047;
	attr.stManual.YRatioLut[188] = 2047;
	attr.stManual.YRatioLut[189] = 2047;
	attr.stManual.YRatioLut[190] = 2047;
	attr.stManual.YRatioLut[191] = 2047;
	attr.stManual.YRatioLut[192] = 2047;
	attr.stManual.YRatioLut[193] = 2047;
	attr.stManual.YRatioLut[194] = 2047;
	attr.stManual.YRatioLut[195] = 2047;
	attr.stManual.YRatioLut[196] = 2047;
	attr.stManual.YRatioLut[197] = 2047;
	attr.stManual.YRatioLut[198] = 2047;
	attr.stManual.YRatioLut[199] = 2047;
	attr.stManual.YRatioLut[200] = 2047;
	attr.stManual.YRatioLut[201] = 2047;
	attr.stManual.YRatioLut[202] = 2047;
	attr.stManual.YRatioLut[203] = 2047;
	attr.stManual.YRatioLut[204] = 2047;
	attr.stManual.YRatioLut[205] = 2047;
	attr.stManual.YRatioLut[206] = 2047;
	attr.stManual.YRatioLut[207] = 2047;
	attr.stManual.YRatioLut[208] = 2047;
	attr.stManual.YRatioLut[209] = 2047;
	attr.stManual.YRatioLut[210] = 2047;
	attr.stManual.YRatioLut[211] = 2047;
	attr.stManual.YRatioLut[212] = 2047;
	attr.stManual.YRatioLut[213] = 2047;
	attr.stManual.YRatioLut[214] = 2047;
	attr.stManual.YRatioLut[215] = 2047;
	attr.stManual.YRatioLut[216] = 2047;
	attr.stManual.YRatioLut[217] = 2047;
	attr.stManual.YRatioLut[218] = 2047;
	attr.stManual.YRatioLut[219] = 2047;
	attr.stManual.YRatioLut[220] = 2047;
	attr.stManual.YRatioLut[221] = 2047;
	attr.stManual.YRatioLut[222] = 2047;
	attr.stManual.YRatioLut[223] = 2047;
	attr.stManual.YRatioLut[224] = 2047;
	attr.stManual.YRatioLut[225] = 2047;
	attr.stManual.YRatioLut[226] = 2047;
	attr.stManual.YRatioLut[227] = 2047;
	attr.stManual.YRatioLut[228] = 2047;
	attr.stManual.YRatioLut[229] = 2047;
	attr.stManual.YRatioLut[230] = 2047;
	attr.stManual.YRatioLut[231] = 2047;
	attr.stManual.YRatioLut[232] = 2047;
	attr.stManual.YRatioLut[233] = 2047;
	attr.stManual.YRatioLut[234] = 2047;
	attr.stManual.YRatioLut[235] = 2047;
	attr.stManual.YRatioLut[236] = 2047;
	attr.stManual.YRatioLut[237] = 2047;
	attr.stManual.YRatioLut[238] = 2047;
	attr.stManual.YRatioLut[239] = 2047;
	attr.stManual.YRatioLut[240] = 2047;
	attr.stManual.YRatioLut[241] = 2047;
	attr.stManual.YRatioLut[242] = 2047;
	attr.stManual.YRatioLut[243] = 2047;
	attr.stManual.YRatioLut[244] = 2047;
	attr.stManual.YRatioLut[245] = 2047;
	attr.stManual.YRatioLut[246] = 2047;
	attr.stManual.YRatioLut[247] = 2047;
	attr.stManual.YRatioLut[248] = 2047;
	attr.stManual.YRatioLut[249] = 2047;
	attr.stManual.YRatioLut[250] = 2047;
	attr.stManual.YRatioLut[251] = 2047;
	attr.stManual.YRatioLut[252] = 2047;
	attr.stManual.YRatioLut[253] = 2047;
	attr.stManual.YRatioLut[254] = 2047;
	attr.stManual.YRatioLut[255] = 2047;
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "YRatioLut", "max");
	// set random value
	attr.stManual.YRatioLut[0] = rand_range(0, 2047);
	attr.stManual.YRatioLut[1] = rand_range(0, 2047);
	attr.stManual.YRatioLut[2] = rand_range(0, 2047);
	attr.stManual.YRatioLut[3] = rand_range(0, 2047);
	attr.stManual.YRatioLut[4] = rand_range(0, 2047);
	attr.stManual.YRatioLut[5] = rand_range(0, 2047);
	attr.stManual.YRatioLut[6] = rand_range(0, 2047);
	attr.stManual.YRatioLut[7] = rand_range(0, 2047);
	attr.stManual.YRatioLut[8] = rand_range(0, 2047);
	attr.stManual.YRatioLut[9] = rand_range(0, 2047);
	attr.stManual.YRatioLut[10] = rand_range(0, 2047);
	attr.stManual.YRatioLut[11] = rand_range(0, 2047);
	attr.stManual.YRatioLut[12] = rand_range(0, 2047);
	attr.stManual.YRatioLut[13] = rand_range(0, 2047);
	attr.stManual.YRatioLut[14] = rand_range(0, 2047);
	attr.stManual.YRatioLut[15] = rand_range(0, 2047);
	attr.stManual.YRatioLut[16] = rand_range(0, 2047);
	attr.stManual.YRatioLut[17] = rand_range(0, 2047);
	attr.stManual.YRatioLut[18] = rand_range(0, 2047);
	attr.stManual.YRatioLut[19] = rand_range(0, 2047);
	attr.stManual.YRatioLut[20] = rand_range(0, 2047);
	attr.stManual.YRatioLut[21] = rand_range(0, 2047);
	attr.stManual.YRatioLut[22] = rand_range(0, 2047);
	attr.stManual.YRatioLut[23] = rand_range(0, 2047);
	attr.stManual.YRatioLut[24] = rand_range(0, 2047);
	attr.stManual.YRatioLut[25] = rand_range(0, 2047);
	attr.stManual.YRatioLut[26] = rand_range(0, 2047);
	attr.stManual.YRatioLut[27] = rand_range(0, 2047);
	attr.stManual.YRatioLut[28] = rand_range(0, 2047);
	attr.stManual.YRatioLut[29] = rand_range(0, 2047);
	attr.stManual.YRatioLut[30] = rand_range(0, 2047);
	attr.stManual.YRatioLut[31] = rand_range(0, 2047);
	attr.stManual.YRatioLut[32] = rand_range(0, 2047);
	attr.stManual.YRatioLut[33] = rand_range(0, 2047);
	attr.stManual.YRatioLut[34] = rand_range(0, 2047);
	attr.stManual.YRatioLut[35] = rand_range(0, 2047);
	attr.stManual.YRatioLut[36] = rand_range(0, 2047);
	attr.stManual.YRatioLut[37] = rand_range(0, 2047);
	attr.stManual.YRatioLut[38] = rand_range(0, 2047);
	attr.stManual.YRatioLut[39] = rand_range(0, 2047);
	attr.stManual.YRatioLut[40] = rand_range(0, 2047);
	attr.stManual.YRatioLut[41] = rand_range(0, 2047);
	attr.stManual.YRatioLut[42] = rand_range(0, 2047);
	attr.stManual.YRatioLut[43] = rand_range(0, 2047);
	attr.stManual.YRatioLut[44] = rand_range(0, 2047);
	attr.stManual.YRatioLut[45] = rand_range(0, 2047);
	attr.stManual.YRatioLut[46] = rand_range(0, 2047);
	attr.stManual.YRatioLut[47] = rand_range(0, 2047);
	attr.stManual.YRatioLut[48] = rand_range(0, 2047);
	attr.stManual.YRatioLut[49] = rand_range(0, 2047);
	attr.stManual.YRatioLut[50] = rand_range(0, 2047);
	attr.stManual.YRatioLut[51] = rand_range(0, 2047);
	attr.stManual.YRatioLut[52] = rand_range(0, 2047);
	attr.stManual.YRatioLut[53] = rand_range(0, 2047);
	attr.stManual.YRatioLut[54] = rand_range(0, 2047);
	attr.stManual.YRatioLut[55] = rand_range(0, 2047);
	attr.stManual.YRatioLut[56] = rand_range(0, 2047);
	attr.stManual.YRatioLut[57] = rand_range(0, 2047);
	attr.stManual.YRatioLut[58] = rand_range(0, 2047);
	attr.stManual.YRatioLut[59] = rand_range(0, 2047);
	attr.stManual.YRatioLut[60] = rand_range(0, 2047);
	attr.stManual.YRatioLut[61] = rand_range(0, 2047);
	attr.stManual.YRatioLut[62] = rand_range(0, 2047);
	attr.stManual.YRatioLut[63] = rand_range(0, 2047);
	attr.stManual.YRatioLut[64] = rand_range(0, 2047);
	attr.stManual.YRatioLut[65] = rand_range(0, 2047);
	attr.stManual.YRatioLut[66] = rand_range(0, 2047);
	attr.stManual.YRatioLut[67] = rand_range(0, 2047);
	attr.stManual.YRatioLut[68] = rand_range(0, 2047);
	attr.stManual.YRatioLut[69] = rand_range(0, 2047);
	attr.stManual.YRatioLut[70] = rand_range(0, 2047);
	attr.stManual.YRatioLut[71] = rand_range(0, 2047);
	attr.stManual.YRatioLut[72] = rand_range(0, 2047);
	attr.stManual.YRatioLut[73] = rand_range(0, 2047);
	attr.stManual.YRatioLut[74] = rand_range(0, 2047);
	attr.stManual.YRatioLut[75] = rand_range(0, 2047);
	attr.stManual.YRatioLut[76] = rand_range(0, 2047);
	attr.stManual.YRatioLut[77] = rand_range(0, 2047);
	attr.stManual.YRatioLut[78] = rand_range(0, 2047);
	attr.stManual.YRatioLut[79] = rand_range(0, 2047);
	attr.stManual.YRatioLut[80] = rand_range(0, 2047);
	attr.stManual.YRatioLut[81] = rand_range(0, 2047);
	attr.stManual.YRatioLut[82] = rand_range(0, 2047);
	attr.stManual.YRatioLut[83] = rand_range(0, 2047);
	attr.stManual.YRatioLut[84] = rand_range(0, 2047);
	attr.stManual.YRatioLut[85] = rand_range(0, 2047);
	attr.stManual.YRatioLut[86] = rand_range(0, 2047);
	attr.stManual.YRatioLut[87] = rand_range(0, 2047);
	attr.stManual.YRatioLut[88] = rand_range(0, 2047);
	attr.stManual.YRatioLut[89] = rand_range(0, 2047);
	attr.stManual.YRatioLut[90] = rand_range(0, 2047);
	attr.stManual.YRatioLut[91] = rand_range(0, 2047);
	attr.stManual.YRatioLut[92] = rand_range(0, 2047);
	attr.stManual.YRatioLut[93] = rand_range(0, 2047);
	attr.stManual.YRatioLut[94] = rand_range(0, 2047);
	attr.stManual.YRatioLut[95] = rand_range(0, 2047);
	attr.stManual.YRatioLut[96] = rand_range(0, 2047);
	attr.stManual.YRatioLut[97] = rand_range(0, 2047);
	attr.stManual.YRatioLut[98] = rand_range(0, 2047);
	attr.stManual.YRatioLut[99] = rand_range(0, 2047);
	attr.stManual.YRatioLut[100] = rand_range(0, 2047);
	attr.stManual.YRatioLut[101] = rand_range(0, 2047);
	attr.stManual.YRatioLut[102] = rand_range(0, 2047);
	attr.stManual.YRatioLut[103] = rand_range(0, 2047);
	attr.stManual.YRatioLut[104] = rand_range(0, 2047);
	attr.stManual.YRatioLut[105] = rand_range(0, 2047);
	attr.stManual.YRatioLut[106] = rand_range(0, 2047);
	attr.stManual.YRatioLut[107] = rand_range(0, 2047);
	attr.stManual.YRatioLut[108] = rand_range(0, 2047);
	attr.stManual.YRatioLut[109] = rand_range(0, 2047);
	attr.stManual.YRatioLut[110] = rand_range(0, 2047);
	attr.stManual.YRatioLut[111] = rand_range(0, 2047);
	attr.stManual.YRatioLut[112] = rand_range(0, 2047);
	attr.stManual.YRatioLut[113] = rand_range(0, 2047);
	attr.stManual.YRatioLut[114] = rand_range(0, 2047);
	attr.stManual.YRatioLut[115] = rand_range(0, 2047);
	attr.stManual.YRatioLut[116] = rand_range(0, 2047);
	attr.stManual.YRatioLut[117] = rand_range(0, 2047);
	attr.stManual.YRatioLut[118] = rand_range(0, 2047);
	attr.stManual.YRatioLut[119] = rand_range(0, 2047);
	attr.stManual.YRatioLut[120] = rand_range(0, 2047);
	attr.stManual.YRatioLut[121] = rand_range(0, 2047);
	attr.stManual.YRatioLut[122] = rand_range(0, 2047);
	attr.stManual.YRatioLut[123] = rand_range(0, 2047);
	attr.stManual.YRatioLut[124] = rand_range(0, 2047);
	attr.stManual.YRatioLut[125] = rand_range(0, 2047);
	attr.stManual.YRatioLut[126] = rand_range(0, 2047);
	attr.stManual.YRatioLut[127] = rand_range(0, 2047);
	attr.stManual.YRatioLut[128] = rand_range(0, 2047);
	attr.stManual.YRatioLut[129] = rand_range(0, 2047);
	attr.stManual.YRatioLut[130] = rand_range(0, 2047);
	attr.stManual.YRatioLut[131] = rand_range(0, 2047);
	attr.stManual.YRatioLut[132] = rand_range(0, 2047);
	attr.stManual.YRatioLut[133] = rand_range(0, 2047);
	attr.stManual.YRatioLut[134] = rand_range(0, 2047);
	attr.stManual.YRatioLut[135] = rand_range(0, 2047);
	attr.stManual.YRatioLut[136] = rand_range(0, 2047);
	attr.stManual.YRatioLut[137] = rand_range(0, 2047);
	attr.stManual.YRatioLut[138] = rand_range(0, 2047);
	attr.stManual.YRatioLut[139] = rand_range(0, 2047);
	attr.stManual.YRatioLut[140] = rand_range(0, 2047);
	attr.stManual.YRatioLut[141] = rand_range(0, 2047);
	attr.stManual.YRatioLut[142] = rand_range(0, 2047);
	attr.stManual.YRatioLut[143] = rand_range(0, 2047);
	attr.stManual.YRatioLut[144] = rand_range(0, 2047);
	attr.stManual.YRatioLut[145] = rand_range(0, 2047);
	attr.stManual.YRatioLut[146] = rand_range(0, 2047);
	attr.stManual.YRatioLut[147] = rand_range(0, 2047);
	attr.stManual.YRatioLut[148] = rand_range(0, 2047);
	attr.stManual.YRatioLut[149] = rand_range(0, 2047);
	attr.stManual.YRatioLut[150] = rand_range(0, 2047);
	attr.stManual.YRatioLut[151] = rand_range(0, 2047);
	attr.stManual.YRatioLut[152] = rand_range(0, 2047);
	attr.stManual.YRatioLut[153] = rand_range(0, 2047);
	attr.stManual.YRatioLut[154] = rand_range(0, 2047);
	attr.stManual.YRatioLut[155] = rand_range(0, 2047);
	attr.stManual.YRatioLut[156] = rand_range(0, 2047);
	attr.stManual.YRatioLut[157] = rand_range(0, 2047);
	attr.stManual.YRatioLut[158] = rand_range(0, 2047);
	attr.stManual.YRatioLut[159] = rand_range(0, 2047);
	attr.stManual.YRatioLut[160] = rand_range(0, 2047);
	attr.stManual.YRatioLut[161] = rand_range(0, 2047);
	attr.stManual.YRatioLut[162] = rand_range(0, 2047);
	attr.stManual.YRatioLut[163] = rand_range(0, 2047);
	attr.stManual.YRatioLut[164] = rand_range(0, 2047);
	attr.stManual.YRatioLut[165] = rand_range(0, 2047);
	attr.stManual.YRatioLut[166] = rand_range(0, 2047);
	attr.stManual.YRatioLut[167] = rand_range(0, 2047);
	attr.stManual.YRatioLut[168] = rand_range(0, 2047);
	attr.stManual.YRatioLut[169] = rand_range(0, 2047);
	attr.stManual.YRatioLut[170] = rand_range(0, 2047);
	attr.stManual.YRatioLut[171] = rand_range(0, 2047);
	attr.stManual.YRatioLut[172] = rand_range(0, 2047);
	attr.stManual.YRatioLut[173] = rand_range(0, 2047);
	attr.stManual.YRatioLut[174] = rand_range(0, 2047);
	attr.stManual.YRatioLut[175] = rand_range(0, 2047);
	attr.stManual.YRatioLut[176] = rand_range(0, 2047);
	attr.stManual.YRatioLut[177] = rand_range(0, 2047);
	attr.stManual.YRatioLut[178] = rand_range(0, 2047);
	attr.stManual.YRatioLut[179] = rand_range(0, 2047);
	attr.stManual.YRatioLut[180] = rand_range(0, 2047);
	attr.stManual.YRatioLut[181] = rand_range(0, 2047);
	attr.stManual.YRatioLut[182] = rand_range(0, 2047);
	attr.stManual.YRatioLut[183] = rand_range(0, 2047);
	attr.stManual.YRatioLut[184] = rand_range(0, 2047);
	attr.stManual.YRatioLut[185] = rand_range(0, 2047);
	attr.stManual.YRatioLut[186] = rand_range(0, 2047);
	attr.stManual.YRatioLut[187] = rand_range(0, 2047);
	attr.stManual.YRatioLut[188] = rand_range(0, 2047);
	attr.stManual.YRatioLut[189] = rand_range(0, 2047);
	attr.stManual.YRatioLut[190] = rand_range(0, 2047);
	attr.stManual.YRatioLut[191] = rand_range(0, 2047);
	attr.stManual.YRatioLut[192] = rand_range(0, 2047);
	attr.stManual.YRatioLut[193] = rand_range(0, 2047);
	attr.stManual.YRatioLut[194] = rand_range(0, 2047);
	attr.stManual.YRatioLut[195] = rand_range(0, 2047);
	attr.stManual.YRatioLut[196] = rand_range(0, 2047);
	attr.stManual.YRatioLut[197] = rand_range(0, 2047);
	attr.stManual.YRatioLut[198] = rand_range(0, 2047);
	attr.stManual.YRatioLut[199] = rand_range(0, 2047);
	attr.stManual.YRatioLut[200] = rand_range(0, 2047);
	attr.stManual.YRatioLut[201] = rand_range(0, 2047);
	attr.stManual.YRatioLut[202] = rand_range(0, 2047);
	attr.stManual.YRatioLut[203] = rand_range(0, 2047);
	attr.stManual.YRatioLut[204] = rand_range(0, 2047);
	attr.stManual.YRatioLut[205] = rand_range(0, 2047);
	attr.stManual.YRatioLut[206] = rand_range(0, 2047);
	attr.stManual.YRatioLut[207] = rand_range(0, 2047);
	attr.stManual.YRatioLut[208] = rand_range(0, 2047);
	attr.stManual.YRatioLut[209] = rand_range(0, 2047);
	attr.stManual.YRatioLut[210] = rand_range(0, 2047);
	attr.stManual.YRatioLut[211] = rand_range(0, 2047);
	attr.stManual.YRatioLut[212] = rand_range(0, 2047);
	attr.stManual.YRatioLut[213] = rand_range(0, 2047);
	attr.stManual.YRatioLut[214] = rand_range(0, 2047);
	attr.stManual.YRatioLut[215] = rand_range(0, 2047);
	attr.stManual.YRatioLut[216] = rand_range(0, 2047);
	attr.stManual.YRatioLut[217] = rand_range(0, 2047);
	attr.stManual.YRatioLut[218] = rand_range(0, 2047);
	attr.stManual.YRatioLut[219] = rand_range(0, 2047);
	attr.stManual.YRatioLut[220] = rand_range(0, 2047);
	attr.stManual.YRatioLut[221] = rand_range(0, 2047);
	attr.stManual.YRatioLut[222] = rand_range(0, 2047);
	attr.stManual.YRatioLut[223] = rand_range(0, 2047);
	attr.stManual.YRatioLut[224] = rand_range(0, 2047);
	attr.stManual.YRatioLut[225] = rand_range(0, 2047);
	attr.stManual.YRatioLut[226] = rand_range(0, 2047);
	attr.stManual.YRatioLut[227] = rand_range(0, 2047);
	attr.stManual.YRatioLut[228] = rand_range(0, 2047);
	attr.stManual.YRatioLut[229] = rand_range(0, 2047);
	attr.stManual.YRatioLut[230] = rand_range(0, 2047);
	attr.stManual.YRatioLut[231] = rand_range(0, 2047);
	attr.stManual.YRatioLut[232] = rand_range(0, 2047);
	attr.stManual.YRatioLut[233] = rand_range(0, 2047);
	attr.stManual.YRatioLut[234] = rand_range(0, 2047);
	attr.stManual.YRatioLut[235] = rand_range(0, 2047);
	attr.stManual.YRatioLut[236] = rand_range(0, 2047);
	attr.stManual.YRatioLut[237] = rand_range(0, 2047);
	attr.stManual.YRatioLut[238] = rand_range(0, 2047);
	attr.stManual.YRatioLut[239] = rand_range(0, 2047);
	attr.stManual.YRatioLut[240] = rand_range(0, 2047);
	attr.stManual.YRatioLut[241] = rand_range(0, 2047);
	attr.stManual.YRatioLut[242] = rand_range(0, 2047);
	attr.stManual.YRatioLut[243] = rand_range(0, 2047);
	attr.stManual.YRatioLut[244] = rand_range(0, 2047);
	attr.stManual.YRatioLut[245] = rand_range(0, 2047);
	attr.stManual.YRatioLut[246] = rand_range(0, 2047);
	attr.stManual.YRatioLut[247] = rand_range(0, 2047);
	attr.stManual.YRatioLut[248] = rand_range(0, 2047);
	attr.stManual.YRatioLut[249] = rand_range(0, 2047);
	attr.stManual.YRatioLut[250] = rand_range(0, 2047);
	attr.stManual.YRatioLut[251] = rand_range(0, 2047);
	attr.stManual.YRatioLut[252] = rand_range(0, 2047);
	attr.stManual.YRatioLut[253] = rand_range(0, 2047);
	attr.stManual.YRatioLut[254] = rand_range(0, 2047);
	attr.stManual.YRatioLut[255] = rand_range(0, 2047);
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "YRatioLut", "random");
	// set abnormal value test
	attr.stManual.YRatioLut[0] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[1] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[2] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[3] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[4] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[5] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[6] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[7] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[8] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[9] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[10] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[11] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[12] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[13] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[14] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[15] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[16] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[17] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[18] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[19] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[20] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[21] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[22] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[23] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[24] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[25] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[26] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[27] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[28] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[29] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[30] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[31] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[32] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[33] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[34] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[35] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[36] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[37] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[38] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[39] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[40] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[41] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[42] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[43] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[44] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[45] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[46] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[47] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[48] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[49] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[50] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[51] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[52] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[53] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[54] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[55] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[56] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[57] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[58] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[59] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[60] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[61] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[62] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[63] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[64] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[65] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[66] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[67] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[68] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[69] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[70] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[71] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[72] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[73] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[74] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[75] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[76] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[77] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[78] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[79] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[80] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[81] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[82] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[83] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[84] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[85] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[86] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[87] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[88] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[89] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[90] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[91] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[92] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[93] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[94] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[95] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[96] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[97] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[98] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[99] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[100] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[101] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[102] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[103] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[104] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[105] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[106] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[107] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[108] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[109] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[110] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[111] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[112] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[113] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[114] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[115] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[116] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[117] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[118] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[119] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[120] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[121] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[122] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[123] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[124] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[125] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[126] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[127] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[128] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[129] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[130] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[131] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[132] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[133] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[134] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[135] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[136] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[137] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[138] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[139] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[140] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[141] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[142] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[143] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[144] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[145] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[146] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[147] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[148] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[149] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[150] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[151] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[152] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[153] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[154] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[155] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[156] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[157] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[158] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[159] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[160] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[161] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[162] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[163] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[164] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[165] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[166] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[167] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[168] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[169] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[170] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[171] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[172] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[173] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[174] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[175] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[176] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[177] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[178] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[179] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[180] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[181] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[182] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[183] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[184] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[185] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[186] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[187] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[188] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[189] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[190] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[191] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[192] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[193] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[194] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[195] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[196] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[197] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[198] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[199] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[200] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[201] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[202] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[203] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[204] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[205] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[206] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[207] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[208] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[209] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[210] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[211] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[212] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[213] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[214] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[215] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[216] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[217] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[218] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[219] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[220] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[221] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[222] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[223] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[224] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[225] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[226] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[227] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[228] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[229] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[230] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[231] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[232] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[233] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[234] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[235] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[236] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[237] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[238] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[239] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[240] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[241] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[242] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[243] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[244] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[245] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[246] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[247] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[248] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[249] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[250] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[251] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[252] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[253] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[254] = rand_range(2048, 65535);
	attr.stManual.YRatioLut[255] = rand_range(2048, 65535);
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	attr.stManual.YRatioLut[0] = 128;
	attr.stManual.YRatioLut[1] = 128;
	attr.stManual.YRatioLut[2] = 128;
	attr.stManual.YRatioLut[3] = 128;
	attr.stManual.YRatioLut[4] = 128;
	attr.stManual.YRatioLut[5] = 128;
	attr.stManual.YRatioLut[6] = 128;
	attr.stManual.YRatioLut[7] = 128;
	attr.stManual.YRatioLut[8] = 128;
	attr.stManual.YRatioLut[9] = 128;
	attr.stManual.YRatioLut[10] = 128;
	attr.stManual.YRatioLut[11] = 128;
	attr.stManual.YRatioLut[12] = 128;
	attr.stManual.YRatioLut[13] = 128;
	attr.stManual.YRatioLut[14] = 128;
	attr.stManual.YRatioLut[15] = 128;
	attr.stManual.YRatioLut[16] = 128;
	attr.stManual.YRatioLut[17] = 128;
	attr.stManual.YRatioLut[18] = 128;
	attr.stManual.YRatioLut[19] = 128;
	attr.stManual.YRatioLut[20] = 128;
	attr.stManual.YRatioLut[21] = 128;
	attr.stManual.YRatioLut[22] = 128;
	attr.stManual.YRatioLut[23] = 128;
	attr.stManual.YRatioLut[24] = 128;
	attr.stManual.YRatioLut[25] = 128;
	attr.stManual.YRatioLut[26] = 128;
	attr.stManual.YRatioLut[27] = 128;
	attr.stManual.YRatioLut[28] = 128;
	attr.stManual.YRatioLut[29] = 128;
	attr.stManual.YRatioLut[30] = 128;
	attr.stManual.YRatioLut[31] = 128;
	attr.stManual.YRatioLut[32] = 128;
	attr.stManual.YRatioLut[33] = 128;
	attr.stManual.YRatioLut[34] = 128;
	attr.stManual.YRatioLut[35] = 128;
	attr.stManual.YRatioLut[36] = 128;
	attr.stManual.YRatioLut[37] = 128;
	attr.stManual.YRatioLut[38] = 128;
	attr.stManual.YRatioLut[39] = 128;
	attr.stManual.YRatioLut[40] = 128;
	attr.stManual.YRatioLut[41] = 128;
	attr.stManual.YRatioLut[42] = 128;
	attr.stManual.YRatioLut[43] = 128;
	attr.stManual.YRatioLut[44] = 128;
	attr.stManual.YRatioLut[45] = 128;
	attr.stManual.YRatioLut[46] = 128;
	attr.stManual.YRatioLut[47] = 128;
	attr.stManual.YRatioLut[48] = 128;
	attr.stManual.YRatioLut[49] = 128;
	attr.stManual.YRatioLut[50] = 128;
	attr.stManual.YRatioLut[51] = 128;
	attr.stManual.YRatioLut[52] = 128;
	attr.stManual.YRatioLut[53] = 128;
	attr.stManual.YRatioLut[54] = 128;
	attr.stManual.YRatioLut[55] = 128;
	attr.stManual.YRatioLut[56] = 128;
	attr.stManual.YRatioLut[57] = 128;
	attr.stManual.YRatioLut[58] = 128;
	attr.stManual.YRatioLut[59] = 128;
	attr.stManual.YRatioLut[60] = 128;
	attr.stManual.YRatioLut[61] = 128;
	attr.stManual.YRatioLut[62] = 128;
	attr.stManual.YRatioLut[63] = 128;
	attr.stManual.YRatioLut[64] = 128;
	attr.stManual.YRatioLut[65] = 128;
	attr.stManual.YRatioLut[66] = 128;
	attr.stManual.YRatioLut[67] = 128;
	attr.stManual.YRatioLut[68] = 128;
	attr.stManual.YRatioLut[69] = 128;
	attr.stManual.YRatioLut[70] = 128;
	attr.stManual.YRatioLut[71] = 128;
	attr.stManual.YRatioLut[72] = 128;
	attr.stManual.YRatioLut[73] = 128;
	attr.stManual.YRatioLut[74] = 128;
	attr.stManual.YRatioLut[75] = 128;
	attr.stManual.YRatioLut[76] = 128;
	attr.stManual.YRatioLut[77] = 128;
	attr.stManual.YRatioLut[78] = 128;
	attr.stManual.YRatioLut[79] = 128;
	attr.stManual.YRatioLut[80] = 128;
	attr.stManual.YRatioLut[81] = 128;
	attr.stManual.YRatioLut[82] = 128;
	attr.stManual.YRatioLut[83] = 128;
	attr.stManual.YRatioLut[84] = 128;
	attr.stManual.YRatioLut[85] = 128;
	attr.stManual.YRatioLut[86] = 128;
	attr.stManual.YRatioLut[87] = 128;
	attr.stManual.YRatioLut[88] = 128;
	attr.stManual.YRatioLut[89] = 128;
	attr.stManual.YRatioLut[90] = 128;
	attr.stManual.YRatioLut[91] = 128;
	attr.stManual.YRatioLut[92] = 128;
	attr.stManual.YRatioLut[93] = 128;
	attr.stManual.YRatioLut[94] = 128;
	attr.stManual.YRatioLut[95] = 128;
	attr.stManual.YRatioLut[96] = 128;
	attr.stManual.YRatioLut[97] = 128;
	attr.stManual.YRatioLut[98] = 128;
	attr.stManual.YRatioLut[99] = 128;
	attr.stManual.YRatioLut[100] = 128;
	attr.stManual.YRatioLut[101] = 128;
	attr.stManual.YRatioLut[102] = 128;
	attr.stManual.YRatioLut[103] = 128;
	attr.stManual.YRatioLut[104] = 128;
	attr.stManual.YRatioLut[105] = 128;
	attr.stManual.YRatioLut[106] = 128;
	attr.stManual.YRatioLut[107] = 128;
	attr.stManual.YRatioLut[108] = 128;
	attr.stManual.YRatioLut[109] = 128;
	attr.stManual.YRatioLut[110] = 128;
	attr.stManual.YRatioLut[111] = 128;
	attr.stManual.YRatioLut[112] = 128;
	attr.stManual.YRatioLut[113] = 128;
	attr.stManual.YRatioLut[114] = 128;
	attr.stManual.YRatioLut[115] = 128;
	attr.stManual.YRatioLut[116] = 128;
	attr.stManual.YRatioLut[117] = 128;
	attr.stManual.YRatioLut[118] = 128;
	attr.stManual.YRatioLut[119] = 128;
	attr.stManual.YRatioLut[120] = 128;
	attr.stManual.YRatioLut[121] = 128;
	attr.stManual.YRatioLut[122] = 128;
	attr.stManual.YRatioLut[123] = 128;
	attr.stManual.YRatioLut[124] = 128;
	attr.stManual.YRatioLut[125] = 128;
	attr.stManual.YRatioLut[126] = 128;
	attr.stManual.YRatioLut[127] = 128;
	attr.stManual.YRatioLut[128] = 128;
	attr.stManual.YRatioLut[129] = 128;
	attr.stManual.YRatioLut[130] = 128;
	attr.stManual.YRatioLut[131] = 128;
	attr.stManual.YRatioLut[132] = 128;
	attr.stManual.YRatioLut[133] = 128;
	attr.stManual.YRatioLut[134] = 128;
	attr.stManual.YRatioLut[135] = 128;
	attr.stManual.YRatioLut[136] = 128;
	attr.stManual.YRatioLut[137] = 128;
	attr.stManual.YRatioLut[138] = 128;
	attr.stManual.YRatioLut[139] = 128;
	attr.stManual.YRatioLut[140] = 128;
	attr.stManual.YRatioLut[141] = 128;
	attr.stManual.YRatioLut[142] = 128;
	attr.stManual.YRatioLut[143] = 128;
	attr.stManual.YRatioLut[144] = 128;
	attr.stManual.YRatioLut[145] = 128;
	attr.stManual.YRatioLut[146] = 128;
	attr.stManual.YRatioLut[147] = 128;
	attr.stManual.YRatioLut[148] = 128;
	attr.stManual.YRatioLut[149] = 128;
	attr.stManual.YRatioLut[150] = 128;
	attr.stManual.YRatioLut[151] = 128;
	attr.stManual.YRatioLut[152] = 128;
	attr.stManual.YRatioLut[153] = 128;
	attr.stManual.YRatioLut[154] = 128;
	attr.stManual.YRatioLut[155] = 128;
	attr.stManual.YRatioLut[156] = 128;
	attr.stManual.YRatioLut[157] = 128;
	attr.stManual.YRatioLut[158] = 128;
	attr.stManual.YRatioLut[159] = 128;
	attr.stManual.YRatioLut[160] = 128;
	attr.stManual.YRatioLut[161] = 128;
	attr.stManual.YRatioLut[162] = 128;
	attr.stManual.YRatioLut[163] = 128;
	attr.stManual.YRatioLut[164] = 128;
	attr.stManual.YRatioLut[165] = 128;
	attr.stManual.YRatioLut[166] = 128;
	attr.stManual.YRatioLut[167] = 128;
	attr.stManual.YRatioLut[168] = 128;
	attr.stManual.YRatioLut[169] = 128;
	attr.stManual.YRatioLut[170] = 128;
	attr.stManual.YRatioLut[171] = 128;
	attr.stManual.YRatioLut[172] = 128;
	attr.stManual.YRatioLut[173] = 128;
	attr.stManual.YRatioLut[174] = 128;
	attr.stManual.YRatioLut[175] = 128;
	attr.stManual.YRatioLut[176] = 128;
	attr.stManual.YRatioLut[177] = 128;
	attr.stManual.YRatioLut[178] = 128;
	attr.stManual.YRatioLut[179] = 128;
	attr.stManual.YRatioLut[180] = 128;
	attr.stManual.YRatioLut[181] = 128;
	attr.stManual.YRatioLut[182] = 128;
	attr.stManual.YRatioLut[183] = 128;
	attr.stManual.YRatioLut[184] = 128;
	attr.stManual.YRatioLut[185] = 128;
	attr.stManual.YRatioLut[186] = 128;
	attr.stManual.YRatioLut[187] = 128;
	attr.stManual.YRatioLut[188] = 128;
	attr.stManual.YRatioLut[189] = 128;
	attr.stManual.YRatioLut[190] = 128;
	attr.stManual.YRatioLut[191] = 128;
	attr.stManual.YRatioLut[192] = 128;
	attr.stManual.YRatioLut[193] = 128;
	attr.stManual.YRatioLut[194] = 128;
	attr.stManual.YRatioLut[195] = 128;
	attr.stManual.YRatioLut[196] = 128;
	attr.stManual.YRatioLut[197] = 128;
	attr.stManual.YRatioLut[198] = 128;
	attr.stManual.YRatioLut[199] = 128;
	attr.stManual.YRatioLut[200] = 128;
	attr.stManual.YRatioLut[201] = 128;
	attr.stManual.YRatioLut[202] = 128;
	attr.stManual.YRatioLut[203] = 128;
	attr.stManual.YRatioLut[204] = 128;
	attr.stManual.YRatioLut[205] = 128;
	attr.stManual.YRatioLut[206] = 128;
	attr.stManual.YRatioLut[207] = 128;
	attr.stManual.YRatioLut[208] = 128;
	attr.stManual.YRatioLut[209] = 128;
	attr.stManual.YRatioLut[210] = 128;
	attr.stManual.YRatioLut[211] = 128;
	attr.stManual.YRatioLut[212] = 128;
	attr.stManual.YRatioLut[213] = 128;
	attr.stManual.YRatioLut[214] = 128;
	attr.stManual.YRatioLut[215] = 128;
	attr.stManual.YRatioLut[216] = 128;
	attr.stManual.YRatioLut[217] = 128;
	attr.stManual.YRatioLut[218] = 128;
	attr.stManual.YRatioLut[219] = 128;
	attr.stManual.YRatioLut[220] = 128;
	attr.stManual.YRatioLut[221] = 128;
	attr.stManual.YRatioLut[222] = 128;
	attr.stManual.YRatioLut[223] = 128;
	attr.stManual.YRatioLut[224] = 128;
	attr.stManual.YRatioLut[225] = 128;
	attr.stManual.YRatioLut[226] = 128;
	attr.stManual.YRatioLut[227] = 128;
	attr.stManual.YRatioLut[228] = 128;
	attr.stManual.YRatioLut[229] = 128;
	attr.stManual.YRatioLut[230] = 128;
	attr.stManual.YRatioLut[231] = 128;
	attr.stManual.YRatioLut[232] = 128;
	attr.stManual.YRatioLut[233] = 128;
	attr.stManual.YRatioLut[234] = 128;
	attr.stManual.YRatioLut[235] = 128;
	attr.stManual.YRatioLut[236] = 128;
	attr.stManual.YRatioLut[237] = 128;
	attr.stManual.YRatioLut[238] = 128;
	attr.stManual.YRatioLut[239] = 128;
	attr.stManual.YRatioLut[240] = 128;
	attr.stManual.YRatioLut[241] = 128;
	attr.stManual.YRatioLut[242] = 128;
	attr.stManual.YRatioLut[243] = 128;
	attr.stManual.YRatioLut[244] = 128;
	attr.stManual.YRatioLut[245] = 128;
	attr.stManual.YRatioLut[246] = 128;
	attr.stManual.YRatioLut[247] = 128;
	attr.stManual.YRatioLut[248] = 128;
	attr.stManual.YRatioLut[249] = 128;
	attr.stManual.YRatioLut[250] = 128;
	attr.stManual.YRatioLut[251] = 128;
	attr.stManual.YRatioLut[252] = 128;
	attr.stManual.YRatioLut[253] = 128;
	attr.stManual.YRatioLut[254] = 128;
	attr.stManual.YRatioLut[255] = 128;
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CA_CAAttr_YRatioLut_manual(void)
{
	reg_api_test_fn(test_CA_CAAttr_YRatioLut_manual);
}

static int test_CA_CAAttr_YRatioLut_auto(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_CA_ATTR_S attr;

	ret = CVI_ISP_GetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetCAAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U16 default_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][0] != default_val_0[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][1] != default_val_1[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][2] != default_val_2[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][3] != default_val_3[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][4] != default_val_4[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][5] != default_val_5[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][6] != default_val_6[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][7] != default_val_7[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_8[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][8] != default_val_8[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_9[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][9] != default_val_9[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_10[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][10] != default_val_10[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_11[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][11] != default_val_11[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_12[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][12] != default_val_12[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_13[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][13] != default_val_13[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_14[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][14] != default_val_14[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_15[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][15] != default_val_15[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_16[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][16] != default_val_16[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_17[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][17] != default_val_17[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_18[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][18] != default_val_18[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_19[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][19] != default_val_19[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_20[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][20] != default_val_20[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_21[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][21] != default_val_21[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_22[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][22] != default_val_22[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_23[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][23] != default_val_23[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_24[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][24] != default_val_24[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_25[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][25] != default_val_25[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_26[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][26] != default_val_26[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_27[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][27] != default_val_27[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_28[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][28] != default_val_28[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_29[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][29] != default_val_29[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_30[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][30] != default_val_30[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_31[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][31] != default_val_31[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_32[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][32] != default_val_32[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_33[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][33] != default_val_33[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_34[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][34] != default_val_34[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_35[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][35] != default_val_35[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_36[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][36] != default_val_36[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_37[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][37] != default_val_37[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_38[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][38] != default_val_38[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_39[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][39] != default_val_39[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_40[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][40] != default_val_40[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_41[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][41] != default_val_41[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_42[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][42] != default_val_42[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_43[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][43] != default_val_43[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_44[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][44] != default_val_44[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_45[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][45] != default_val_45[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_46[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][46] != default_val_46[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_47[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][47] != default_val_47[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_48[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][48] != default_val_48[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_49[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][49] != default_val_49[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_50[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][50] != default_val_50[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_51[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][51] != default_val_51[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_52[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][52] != default_val_52[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_53[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][53] != default_val_53[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_54[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][54] != default_val_54[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_55[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][55] != default_val_55[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_56[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][56] != default_val_56[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_57[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][57] != default_val_57[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_58[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][58] != default_val_58[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_59[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][59] != default_val_59[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_60[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][60] != default_val_60[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_61[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][61] != default_val_61[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_62[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][62] != default_val_62[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_63[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][63] != default_val_63[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_64[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][64] != default_val_64[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_65[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][65] != default_val_65[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_66[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][66] != default_val_66[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_67[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][67] != default_val_67[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_68[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][68] != default_val_68[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_69[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][69] != default_val_69[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_70[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][70] != default_val_70[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_71[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][71] != default_val_71[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_72[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][72] != default_val_72[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_73[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][73] != default_val_73[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_74[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][74] != default_val_74[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_75[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][75] != default_val_75[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_76[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][76] != default_val_76[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_77[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][77] != default_val_77[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_78[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][78] != default_val_78[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_79[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][79] != default_val_79[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_80[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][80] != default_val_80[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_81[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][81] != default_val_81[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_82[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][82] != default_val_82[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_83[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][83] != default_val_83[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_84[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][84] != default_val_84[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_85[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][85] != default_val_85[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_86[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][86] != default_val_86[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_87[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][87] != default_val_87[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_88[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][88] != default_val_88[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_89[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][89] != default_val_89[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_90[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][90] != default_val_90[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_91[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][91] != default_val_91[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_92[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][92] != default_val_92[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_93[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][93] != default_val_93[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_94[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][94] != default_val_94[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_95[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][95] != default_val_95[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_96[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][96] != default_val_96[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_97[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][97] != default_val_97[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_98[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][98] != default_val_98[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_99[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][99] != default_val_99[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_100[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][100] != default_val_100[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_101[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][101] != default_val_101[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_102[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][102] != default_val_102[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_103[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][103] != default_val_103[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_104[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][104] != default_val_104[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_105[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][105] != default_val_105[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_106[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][106] != default_val_106[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_107[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][107] != default_val_107[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_108[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][108] != default_val_108[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_109[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][109] != default_val_109[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_110[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][110] != default_val_110[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_111[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][111] != default_val_111[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_112[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][112] != default_val_112[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_113[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][113] != default_val_113[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_114[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][114] != default_val_114[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_115[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][115] != default_val_115[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_116[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][116] != default_val_116[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_117[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][117] != default_val_117[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_118[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][118] != default_val_118[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_119[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][119] != default_val_119[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_120[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][120] != default_val_120[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_121[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][121] != default_val_121[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_122[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][122] != default_val_122[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_123[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][123] != default_val_123[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_124[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][124] != default_val_124[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_125[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][125] != default_val_125[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_126[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][126] != default_val_126[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_127[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][127] != default_val_127[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_128[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][128] != default_val_128[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_129[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][129] != default_val_129[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_130[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][130] != default_val_130[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_131[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][131] != default_val_131[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_132[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][132] != default_val_132[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_133[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][133] != default_val_133[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_134[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][134] != default_val_134[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_135[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][135] != default_val_135[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_136[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][136] != default_val_136[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_137[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][137] != default_val_137[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_138[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][138] != default_val_138[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_139[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][139] != default_val_139[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_140[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][140] != default_val_140[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_141[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][141] != default_val_141[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_142[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][142] != default_val_142[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_143[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][143] != default_val_143[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_144[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][144] != default_val_144[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_145[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][145] != default_val_145[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_146[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][146] != default_val_146[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_147[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][147] != default_val_147[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_148[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][148] != default_val_148[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_149[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][149] != default_val_149[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_150[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][150] != default_val_150[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_151[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][151] != default_val_151[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_152[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][152] != default_val_152[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_153[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][153] != default_val_153[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_154[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][154] != default_val_154[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_155[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][155] != default_val_155[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_156[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][156] != default_val_156[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_157[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][157] != default_val_157[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_158[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][158] != default_val_158[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_159[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][159] != default_val_159[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_160[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][160] != default_val_160[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_161[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][161] != default_val_161[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_162[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][162] != default_val_162[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_163[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][163] != default_val_163[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_164[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][164] != default_val_164[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_165[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][165] != default_val_165[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_166[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][166] != default_val_166[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_167[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][167] != default_val_167[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_168[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][168] != default_val_168[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_169[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][169] != default_val_169[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_170[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][170] != default_val_170[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_171[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][171] != default_val_171[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_172[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][172] != default_val_172[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_173[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][173] != default_val_173[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_174[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][174] != default_val_174[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_175[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][175] != default_val_175[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_176[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][176] != default_val_176[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_177[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][177] != default_val_177[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_178[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][178] != default_val_178[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_179[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][179] != default_val_179[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_180[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][180] != default_val_180[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_181[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][181] != default_val_181[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_182[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][182] != default_val_182[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_183[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][183] != default_val_183[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_184[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][184] != default_val_184[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_185[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][185] != default_val_185[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_186[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][186] != default_val_186[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_187[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][187] != default_val_187[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_188[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][188] != default_val_188[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_189[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][189] != default_val_189[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_190[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][190] != default_val_190[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_191[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][191] != default_val_191[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_192[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][192] != default_val_192[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_193[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][193] != default_val_193[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_194[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][194] != default_val_194[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_195[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][195] != default_val_195[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_196[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][196] != default_val_196[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_197[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][197] != default_val_197[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_198[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][198] != default_val_198[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_199[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][199] != default_val_199[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_200[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][200] != default_val_200[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_201[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][201] != default_val_201[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_202[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][202] != default_val_202[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_203[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][203] != default_val_203[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_204[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][204] != default_val_204[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_205[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][205] != default_val_205[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_206[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][206] != default_val_206[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_207[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][207] != default_val_207[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_208[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][208] != default_val_208[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_209[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][209] != default_val_209[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_210[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][210] != default_val_210[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_211[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][211] != default_val_211[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_212[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][212] != default_val_212[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_213[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][213] != default_val_213[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_214[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][214] != default_val_214[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_215[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][215] != default_val_215[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_216[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][216] != default_val_216[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_217[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][217] != default_val_217[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_218[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][218] != default_val_218[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_219[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][219] != default_val_219[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_220[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][220] != default_val_220[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_221[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][221] != default_val_221[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_222[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][222] != default_val_222[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_223[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][223] != default_val_223[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_224[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][224] != default_val_224[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_225[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][225] != default_val_225[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_226[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][226] != default_val_226[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_227[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][227] != default_val_227[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_228[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][228] != default_val_228[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_229[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][229] != default_val_229[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_230[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][230] != default_val_230[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_231[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][231] != default_val_231[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_232[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][232] != default_val_232[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_233[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][233] != default_val_233[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_234[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][234] != default_val_234[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_235[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][235] != default_val_235[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_236[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][236] != default_val_236[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_237[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][237] != default_val_237[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_238[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][238] != default_val_238[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_239[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][239] != default_val_239[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_240[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][240] != default_val_240[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_241[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][241] != default_val_241[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_242[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][242] != default_val_242[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_243[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][243] != default_val_243[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_244[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][244] != default_val_244[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_245[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][245] != default_val_245[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_246[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][246] != default_val_246[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_247[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][247] != default_val_247[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_248[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][248] != default_val_248[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_249[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][249] != default_val_249[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_250[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][250] != default_val_250[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_251[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][251] != default_val_251[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_252[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][252] != default_val_252[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_253[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][253] != default_val_253[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_254[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][254] != default_val_254[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	CVI_U16 default_val_255[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		if (attr.stAuto.YRatioLut[j][255] != default_val_255[j]) {
			TEST_FAIL("test default value failed\n");
			return CVI_FAILURE;
		}
	}
	// set minimum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][0] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][1] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][2] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][3] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][4] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][5] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][6] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][7] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][8] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][9] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][10] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][11] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][12] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][13] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][14] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][15] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][16] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][17] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][18] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][19] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][20] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][21] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][22] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][23] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][24] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][25] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][26] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][27] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][28] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][29] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][30] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][31] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][32] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][33] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][34] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][35] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][36] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][37] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][38] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][39] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][40] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][41] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][42] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][43] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][44] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][45] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][46] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][47] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][48] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][49] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][50] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][51] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][52] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][53] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][54] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][55] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][56] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][57] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][58] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][59] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][60] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][61] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][62] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][63] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][64] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][65] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][66] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][67] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][68] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][69] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][70] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][71] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][72] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][73] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][74] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][75] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][76] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][77] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][78] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][79] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][80] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][81] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][82] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][83] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][84] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][85] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][86] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][87] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][88] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][89] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][90] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][91] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][92] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][93] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][94] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][95] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][96] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][97] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][98] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][99] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][100] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][101] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][102] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][103] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][104] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][105] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][106] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][107] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][108] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][109] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][110] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][111] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][112] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][113] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][114] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][115] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][116] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][117] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][118] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][119] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][120] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][121] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][122] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][123] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][124] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][125] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][126] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][127] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][128] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][129] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][130] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][131] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][132] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][133] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][134] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][135] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][136] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][137] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][138] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][139] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][140] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][141] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][142] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][143] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][144] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][145] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][146] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][147] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][148] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][149] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][150] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][151] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][152] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][153] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][154] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][155] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][156] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][157] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][158] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][159] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][160] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][161] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][162] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][163] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][164] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][165] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][166] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][167] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][168] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][169] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][170] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][171] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][172] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][173] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][174] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][175] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][176] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][177] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][178] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][179] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][180] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][181] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][182] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][183] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][184] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][185] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][186] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][187] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][188] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][189] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][190] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][191] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][192] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][193] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][194] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][195] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][196] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][197] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][198] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][199] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][200] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][201] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][202] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][203] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][204] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][205] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][206] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][207] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][208] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][209] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][210] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][211] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][212] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][213] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][214] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][215] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][216] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][217] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][218] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][219] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][220] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][221] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][222] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][223] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][224] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][225] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][226] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][227] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][228] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][229] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][230] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][231] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][232] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][233] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][234] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][235] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][236] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][237] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][238] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][239] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][240] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][241] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][242] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][243] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][244] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][245] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][246] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][247] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][248] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][249] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][250] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][251] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][252] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][253] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][254] = 0;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][255] = 0;
	}
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "YRatioLut", "min");
	// set maximum value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][0] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][1] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][2] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][3] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][4] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][5] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][6] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][7] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][8] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][9] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][10] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][11] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][12] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][13] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][14] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][15] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][16] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][17] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][18] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][19] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][20] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][21] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][22] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][23] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][24] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][25] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][26] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][27] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][28] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][29] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][30] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][31] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][32] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][33] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][34] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][35] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][36] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][37] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][38] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][39] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][40] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][41] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][42] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][43] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][44] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][45] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][46] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][47] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][48] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][49] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][50] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][51] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][52] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][53] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][54] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][55] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][56] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][57] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][58] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][59] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][60] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][61] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][62] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][63] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][64] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][65] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][66] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][67] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][68] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][69] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][70] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][71] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][72] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][73] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][74] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][75] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][76] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][77] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][78] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][79] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][80] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][81] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][82] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][83] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][84] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][85] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][86] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][87] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][88] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][89] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][90] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][91] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][92] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][93] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][94] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][95] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][96] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][97] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][98] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][99] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][100] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][101] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][102] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][103] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][104] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][105] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][106] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][107] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][108] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][109] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][110] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][111] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][112] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][113] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][114] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][115] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][116] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][117] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][118] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][119] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][120] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][121] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][122] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][123] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][124] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][125] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][126] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][127] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][128] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][129] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][130] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][131] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][132] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][133] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][134] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][135] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][136] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][137] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][138] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][139] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][140] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][141] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][142] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][143] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][144] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][145] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][146] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][147] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][148] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][149] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][150] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][151] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][152] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][153] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][154] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][155] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][156] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][157] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][158] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][159] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][160] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][161] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][162] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][163] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][164] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][165] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][166] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][167] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][168] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][169] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][170] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][171] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][172] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][173] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][174] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][175] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][176] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][177] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][178] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][179] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][180] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][181] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][182] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][183] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][184] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][185] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][186] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][187] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][188] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][189] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][190] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][191] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][192] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][193] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][194] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][195] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][196] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][197] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][198] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][199] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][200] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][201] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][202] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][203] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][204] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][205] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][206] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][207] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][208] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][209] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][210] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][211] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][212] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][213] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][214] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][215] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][216] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][217] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][218] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][219] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][220] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][221] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][222] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][223] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][224] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][225] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][226] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][227] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][228] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][229] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][230] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][231] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][232] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][233] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][234] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][235] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][236] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][237] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][238] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][239] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][240] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][241] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][242] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][243] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][244] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][245] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][246] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][247] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][248] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][249] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][250] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][251] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][252] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][253] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][254] = 2047;
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][255] = 2047;
	}
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "YRatioLut", "max");
	// set random value
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][0] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][1] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][2] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][3] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][4] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][5] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][6] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][7] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][8] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][9] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][10] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][11] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][12] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][13] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][14] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][15] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][16] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][17] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][18] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][19] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][20] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][21] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][22] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][23] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][24] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][25] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][26] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][27] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][28] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][29] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][30] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][31] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][32] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][33] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][34] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][35] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][36] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][37] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][38] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][39] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][40] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][41] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][42] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][43] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][44] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][45] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][46] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][47] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][48] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][49] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][50] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][51] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][52] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][53] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][54] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][55] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][56] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][57] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][58] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][59] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][60] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][61] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][62] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][63] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][64] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][65] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][66] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][67] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][68] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][69] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][70] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][71] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][72] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][73] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][74] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][75] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][76] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][77] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][78] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][79] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][80] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][81] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][82] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][83] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][84] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][85] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][86] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][87] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][88] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][89] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][90] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][91] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][92] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][93] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][94] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][95] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][96] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][97] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][98] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][99] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][100] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][101] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][102] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][103] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][104] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][105] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][106] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][107] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][108] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][109] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][110] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][111] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][112] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][113] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][114] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][115] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][116] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][117] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][118] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][119] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][120] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][121] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][122] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][123] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][124] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][125] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][126] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][127] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][128] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][129] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][130] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][131] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][132] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][133] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][134] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][135] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][136] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][137] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][138] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][139] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][140] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][141] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][142] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][143] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][144] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][145] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][146] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][147] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][148] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][149] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][150] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][151] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][152] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][153] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][154] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][155] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][156] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][157] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][158] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][159] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][160] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][161] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][162] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][163] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][164] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][165] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][166] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][167] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][168] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][169] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][170] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][171] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][172] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][173] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][174] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][175] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][176] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][177] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][178] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][179] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][180] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][181] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][182] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][183] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][184] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][185] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][186] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][187] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][188] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][189] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][190] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][191] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][192] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][193] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][194] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][195] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][196] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][197] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][198] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][199] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][200] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][201] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][202] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][203] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][204] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][205] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][206] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][207] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][208] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][209] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][210] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][211] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][212] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][213] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][214] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][215] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][216] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][217] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][218] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][219] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][220] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][221] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][222] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][223] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][224] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][225] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][226] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][227] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][228] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][229] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][230] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][231] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][232] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][233] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][234] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][235] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][236] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][237] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][238] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][239] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][240] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][241] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][242] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][243] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][244] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][245] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][246] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][247] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][248] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][249] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][250] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][251] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][252] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][253] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][254] = rand_range(0, 2047);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][255] = rand_range(0, 2047);
	}
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "CA", "YRatioLut", "random");
	// set abnormal value test
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][0] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][1] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][2] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][3] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][4] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][5] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][6] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][7] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][8] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][9] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][10] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][11] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][12] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][13] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][14] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][15] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][16] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][17] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][18] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][19] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][20] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][21] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][22] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][23] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][24] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][25] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][26] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][27] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][28] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][29] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][30] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][31] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][32] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][33] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][34] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][35] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][36] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][37] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][38] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][39] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][40] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][41] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][42] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][43] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][44] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][45] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][46] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][47] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][48] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][49] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][50] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][51] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][52] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][53] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][54] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][55] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][56] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][57] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][58] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][59] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][60] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][61] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][62] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][63] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][64] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][65] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][66] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][67] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][68] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][69] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][70] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][71] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][72] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][73] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][74] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][75] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][76] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][77] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][78] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][79] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][80] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][81] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][82] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][83] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][84] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][85] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][86] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][87] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][88] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][89] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][90] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][91] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][92] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][93] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][94] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][95] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][96] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][97] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][98] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][99] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][100] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][101] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][102] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][103] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][104] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][105] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][106] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][107] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][108] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][109] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][110] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][111] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][112] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][113] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][114] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][115] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][116] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][117] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][118] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][119] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][120] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][121] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][122] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][123] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][124] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][125] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][126] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][127] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][128] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][129] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][130] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][131] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][132] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][133] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][134] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][135] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][136] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][137] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][138] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][139] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][140] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][141] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][142] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][143] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][144] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][145] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][146] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][147] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][148] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][149] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][150] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][151] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][152] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][153] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][154] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][155] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][156] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][157] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][158] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][159] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][160] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][161] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][162] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][163] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][164] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][165] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][166] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][167] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][168] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][169] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][170] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][171] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][172] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][173] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][174] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][175] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][176] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][177] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][178] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][179] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][180] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][181] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][182] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][183] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][184] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][185] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][186] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][187] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][188] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][189] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][190] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][191] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][192] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][193] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][194] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][195] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][196] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][197] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][198] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][199] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][200] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][201] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][202] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][203] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][204] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][205] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][206] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][207] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][208] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][209] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][210] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][211] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][212] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][213] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][214] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][215] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][216] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][217] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][218] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][219] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][220] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][221] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][222] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][223] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][224] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][225] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][226] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][227] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][228] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][229] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][230] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][231] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][232] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][233] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][234] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][235] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][236] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][237] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][238] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][239] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][240] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][241] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][242] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][243] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][244] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][245] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][246] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][247] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][248] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][249] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][250] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][251] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][252] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][253] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][254] = rand_range(2048, 65535);
	}
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][255] = rand_range(2048, 65535);
	}
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	CVI_U16 restore_val_0[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][0] = restore_val_0[j];
	}
	CVI_U16 restore_val_1[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][1] = restore_val_1[j];
	}
	CVI_U16 restore_val_2[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][2] = restore_val_2[j];
	}
	CVI_U16 restore_val_3[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][3] = restore_val_3[j];
	}
	CVI_U16 restore_val_4[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][4] = restore_val_4[j];
	}
	CVI_U16 restore_val_5[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][5] = restore_val_5[j];
	}
	CVI_U16 restore_val_6[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][6] = restore_val_6[j];
	}
	CVI_U16 restore_val_7[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][7] = restore_val_7[j];
	}
	CVI_U16 restore_val_8[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][8] = restore_val_8[j];
	}
	CVI_U16 restore_val_9[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][9] = restore_val_9[j];
	}
	CVI_U16 restore_val_10[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][10] = restore_val_10[j];
	}
	CVI_U16 restore_val_11[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][11] = restore_val_11[j];
	}
	CVI_U16 restore_val_12[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][12] = restore_val_12[j];
	}
	CVI_U16 restore_val_13[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][13] = restore_val_13[j];
	}
	CVI_U16 restore_val_14[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][14] = restore_val_14[j];
	}
	CVI_U16 restore_val_15[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][15] = restore_val_15[j];
	}
	CVI_U16 restore_val_16[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][16] = restore_val_16[j];
	}
	CVI_U16 restore_val_17[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][17] = restore_val_17[j];
	}
	CVI_U16 restore_val_18[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][18] = restore_val_18[j];
	}
	CVI_U16 restore_val_19[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][19] = restore_val_19[j];
	}
	CVI_U16 restore_val_20[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][20] = restore_val_20[j];
	}
	CVI_U16 restore_val_21[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][21] = restore_val_21[j];
	}
	CVI_U16 restore_val_22[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][22] = restore_val_22[j];
	}
	CVI_U16 restore_val_23[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][23] = restore_val_23[j];
	}
	CVI_U16 restore_val_24[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][24] = restore_val_24[j];
	}
	CVI_U16 restore_val_25[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][25] = restore_val_25[j];
	}
	CVI_U16 restore_val_26[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][26] = restore_val_26[j];
	}
	CVI_U16 restore_val_27[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][27] = restore_val_27[j];
	}
	CVI_U16 restore_val_28[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][28] = restore_val_28[j];
	}
	CVI_U16 restore_val_29[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][29] = restore_val_29[j];
	}
	CVI_U16 restore_val_30[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][30] = restore_val_30[j];
	}
	CVI_U16 restore_val_31[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][31] = restore_val_31[j];
	}
	CVI_U16 restore_val_32[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][32] = restore_val_32[j];
	}
	CVI_U16 restore_val_33[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][33] = restore_val_33[j];
	}
	CVI_U16 restore_val_34[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][34] = restore_val_34[j];
	}
	CVI_U16 restore_val_35[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][35] = restore_val_35[j];
	}
	CVI_U16 restore_val_36[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][36] = restore_val_36[j];
	}
	CVI_U16 restore_val_37[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][37] = restore_val_37[j];
	}
	CVI_U16 restore_val_38[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][38] = restore_val_38[j];
	}
	CVI_U16 restore_val_39[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][39] = restore_val_39[j];
	}
	CVI_U16 restore_val_40[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][40] = restore_val_40[j];
	}
	CVI_U16 restore_val_41[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][41] = restore_val_41[j];
	}
	CVI_U16 restore_val_42[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][42] = restore_val_42[j];
	}
	CVI_U16 restore_val_43[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][43] = restore_val_43[j];
	}
	CVI_U16 restore_val_44[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][44] = restore_val_44[j];
	}
	CVI_U16 restore_val_45[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][45] = restore_val_45[j];
	}
	CVI_U16 restore_val_46[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][46] = restore_val_46[j];
	}
	CVI_U16 restore_val_47[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][47] = restore_val_47[j];
	}
	CVI_U16 restore_val_48[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][48] = restore_val_48[j];
	}
	CVI_U16 restore_val_49[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][49] = restore_val_49[j];
	}
	CVI_U16 restore_val_50[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][50] = restore_val_50[j];
	}
	CVI_U16 restore_val_51[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][51] = restore_val_51[j];
	}
	CVI_U16 restore_val_52[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][52] = restore_val_52[j];
	}
	CVI_U16 restore_val_53[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][53] = restore_val_53[j];
	}
	CVI_U16 restore_val_54[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][54] = restore_val_54[j];
	}
	CVI_U16 restore_val_55[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][55] = restore_val_55[j];
	}
	CVI_U16 restore_val_56[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][56] = restore_val_56[j];
	}
	CVI_U16 restore_val_57[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][57] = restore_val_57[j];
	}
	CVI_U16 restore_val_58[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][58] = restore_val_58[j];
	}
	CVI_U16 restore_val_59[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][59] = restore_val_59[j];
	}
	CVI_U16 restore_val_60[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][60] = restore_val_60[j];
	}
	CVI_U16 restore_val_61[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][61] = restore_val_61[j];
	}
	CVI_U16 restore_val_62[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][62] = restore_val_62[j];
	}
	CVI_U16 restore_val_63[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][63] = restore_val_63[j];
	}
	CVI_U16 restore_val_64[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][64] = restore_val_64[j];
	}
	CVI_U16 restore_val_65[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][65] = restore_val_65[j];
	}
	CVI_U16 restore_val_66[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][66] = restore_val_66[j];
	}
	CVI_U16 restore_val_67[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][67] = restore_val_67[j];
	}
	CVI_U16 restore_val_68[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][68] = restore_val_68[j];
	}
	CVI_U16 restore_val_69[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][69] = restore_val_69[j];
	}
	CVI_U16 restore_val_70[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][70] = restore_val_70[j];
	}
	CVI_U16 restore_val_71[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][71] = restore_val_71[j];
	}
	CVI_U16 restore_val_72[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][72] = restore_val_72[j];
	}
	CVI_U16 restore_val_73[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][73] = restore_val_73[j];
	}
	CVI_U16 restore_val_74[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][74] = restore_val_74[j];
	}
	CVI_U16 restore_val_75[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][75] = restore_val_75[j];
	}
	CVI_U16 restore_val_76[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][76] = restore_val_76[j];
	}
	CVI_U16 restore_val_77[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][77] = restore_val_77[j];
	}
	CVI_U16 restore_val_78[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][78] = restore_val_78[j];
	}
	CVI_U16 restore_val_79[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][79] = restore_val_79[j];
	}
	CVI_U16 restore_val_80[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][80] = restore_val_80[j];
	}
	CVI_U16 restore_val_81[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][81] = restore_val_81[j];
	}
	CVI_U16 restore_val_82[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][82] = restore_val_82[j];
	}
	CVI_U16 restore_val_83[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][83] = restore_val_83[j];
	}
	CVI_U16 restore_val_84[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][84] = restore_val_84[j];
	}
	CVI_U16 restore_val_85[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][85] = restore_val_85[j];
	}
	CVI_U16 restore_val_86[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][86] = restore_val_86[j];
	}
	CVI_U16 restore_val_87[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][87] = restore_val_87[j];
	}
	CVI_U16 restore_val_88[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][88] = restore_val_88[j];
	}
	CVI_U16 restore_val_89[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][89] = restore_val_89[j];
	}
	CVI_U16 restore_val_90[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][90] = restore_val_90[j];
	}
	CVI_U16 restore_val_91[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][91] = restore_val_91[j];
	}
	CVI_U16 restore_val_92[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][92] = restore_val_92[j];
	}
	CVI_U16 restore_val_93[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][93] = restore_val_93[j];
	}
	CVI_U16 restore_val_94[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][94] = restore_val_94[j];
	}
	CVI_U16 restore_val_95[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][95] = restore_val_95[j];
	}
	CVI_U16 restore_val_96[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][96] = restore_val_96[j];
	}
	CVI_U16 restore_val_97[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][97] = restore_val_97[j];
	}
	CVI_U16 restore_val_98[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][98] = restore_val_98[j];
	}
	CVI_U16 restore_val_99[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][99] = restore_val_99[j];
	}
	CVI_U16 restore_val_100[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][100] = restore_val_100[j];
	}
	CVI_U16 restore_val_101[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][101] = restore_val_101[j];
	}
	CVI_U16 restore_val_102[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][102] = restore_val_102[j];
	}
	CVI_U16 restore_val_103[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][103] = restore_val_103[j];
	}
	CVI_U16 restore_val_104[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][104] = restore_val_104[j];
	}
	CVI_U16 restore_val_105[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][105] = restore_val_105[j];
	}
	CVI_U16 restore_val_106[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][106] = restore_val_106[j];
	}
	CVI_U16 restore_val_107[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][107] = restore_val_107[j];
	}
	CVI_U16 restore_val_108[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][108] = restore_val_108[j];
	}
	CVI_U16 restore_val_109[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][109] = restore_val_109[j];
	}
	CVI_U16 restore_val_110[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][110] = restore_val_110[j];
	}
	CVI_U16 restore_val_111[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][111] = restore_val_111[j];
	}
	CVI_U16 restore_val_112[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][112] = restore_val_112[j];
	}
	CVI_U16 restore_val_113[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][113] = restore_val_113[j];
	}
	CVI_U16 restore_val_114[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][114] = restore_val_114[j];
	}
	CVI_U16 restore_val_115[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][115] = restore_val_115[j];
	}
	CVI_U16 restore_val_116[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][116] = restore_val_116[j];
	}
	CVI_U16 restore_val_117[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][117] = restore_val_117[j];
	}
	CVI_U16 restore_val_118[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][118] = restore_val_118[j];
	}
	CVI_U16 restore_val_119[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][119] = restore_val_119[j];
	}
	CVI_U16 restore_val_120[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][120] = restore_val_120[j];
	}
	CVI_U16 restore_val_121[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][121] = restore_val_121[j];
	}
	CVI_U16 restore_val_122[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][122] = restore_val_122[j];
	}
	CVI_U16 restore_val_123[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][123] = restore_val_123[j];
	}
	CVI_U16 restore_val_124[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][124] = restore_val_124[j];
	}
	CVI_U16 restore_val_125[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][125] = restore_val_125[j];
	}
	CVI_U16 restore_val_126[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][126] = restore_val_126[j];
	}
	CVI_U16 restore_val_127[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][127] = restore_val_127[j];
	}
	CVI_U16 restore_val_128[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][128] = restore_val_128[j];
	}
	CVI_U16 restore_val_129[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][129] = restore_val_129[j];
	}
	CVI_U16 restore_val_130[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][130] = restore_val_130[j];
	}
	CVI_U16 restore_val_131[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][131] = restore_val_131[j];
	}
	CVI_U16 restore_val_132[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][132] = restore_val_132[j];
	}
	CVI_U16 restore_val_133[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][133] = restore_val_133[j];
	}
	CVI_U16 restore_val_134[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][134] = restore_val_134[j];
	}
	CVI_U16 restore_val_135[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][135] = restore_val_135[j];
	}
	CVI_U16 restore_val_136[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][136] = restore_val_136[j];
	}
	CVI_U16 restore_val_137[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][137] = restore_val_137[j];
	}
	CVI_U16 restore_val_138[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][138] = restore_val_138[j];
	}
	CVI_U16 restore_val_139[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][139] = restore_val_139[j];
	}
	CVI_U16 restore_val_140[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][140] = restore_val_140[j];
	}
	CVI_U16 restore_val_141[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][141] = restore_val_141[j];
	}
	CVI_U16 restore_val_142[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][142] = restore_val_142[j];
	}
	CVI_U16 restore_val_143[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][143] = restore_val_143[j];
	}
	CVI_U16 restore_val_144[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][144] = restore_val_144[j];
	}
	CVI_U16 restore_val_145[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][145] = restore_val_145[j];
	}
	CVI_U16 restore_val_146[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][146] = restore_val_146[j];
	}
	CVI_U16 restore_val_147[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][147] = restore_val_147[j];
	}
	CVI_U16 restore_val_148[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][148] = restore_val_148[j];
	}
	CVI_U16 restore_val_149[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][149] = restore_val_149[j];
	}
	CVI_U16 restore_val_150[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][150] = restore_val_150[j];
	}
	CVI_U16 restore_val_151[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][151] = restore_val_151[j];
	}
	CVI_U16 restore_val_152[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][152] = restore_val_152[j];
	}
	CVI_U16 restore_val_153[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][153] = restore_val_153[j];
	}
	CVI_U16 restore_val_154[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][154] = restore_val_154[j];
	}
	CVI_U16 restore_val_155[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][155] = restore_val_155[j];
	}
	CVI_U16 restore_val_156[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][156] = restore_val_156[j];
	}
	CVI_U16 restore_val_157[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][157] = restore_val_157[j];
	}
	CVI_U16 restore_val_158[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][158] = restore_val_158[j];
	}
	CVI_U16 restore_val_159[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][159] = restore_val_159[j];
	}
	CVI_U16 restore_val_160[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][160] = restore_val_160[j];
	}
	CVI_U16 restore_val_161[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][161] = restore_val_161[j];
	}
	CVI_U16 restore_val_162[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][162] = restore_val_162[j];
	}
	CVI_U16 restore_val_163[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][163] = restore_val_163[j];
	}
	CVI_U16 restore_val_164[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][164] = restore_val_164[j];
	}
	CVI_U16 restore_val_165[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][165] = restore_val_165[j];
	}
	CVI_U16 restore_val_166[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][166] = restore_val_166[j];
	}
	CVI_U16 restore_val_167[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][167] = restore_val_167[j];
	}
	CVI_U16 restore_val_168[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][168] = restore_val_168[j];
	}
	CVI_U16 restore_val_169[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][169] = restore_val_169[j];
	}
	CVI_U16 restore_val_170[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][170] = restore_val_170[j];
	}
	CVI_U16 restore_val_171[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][171] = restore_val_171[j];
	}
	CVI_U16 restore_val_172[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][172] = restore_val_172[j];
	}
	CVI_U16 restore_val_173[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][173] = restore_val_173[j];
	}
	CVI_U16 restore_val_174[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][174] = restore_val_174[j];
	}
	CVI_U16 restore_val_175[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][175] = restore_val_175[j];
	}
	CVI_U16 restore_val_176[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][176] = restore_val_176[j];
	}
	CVI_U16 restore_val_177[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][177] = restore_val_177[j];
	}
	CVI_U16 restore_val_178[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][178] = restore_val_178[j];
	}
	CVI_U16 restore_val_179[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][179] = restore_val_179[j];
	}
	CVI_U16 restore_val_180[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][180] = restore_val_180[j];
	}
	CVI_U16 restore_val_181[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][181] = restore_val_181[j];
	}
	CVI_U16 restore_val_182[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][182] = restore_val_182[j];
	}
	CVI_U16 restore_val_183[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][183] = restore_val_183[j];
	}
	CVI_U16 restore_val_184[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][184] = restore_val_184[j];
	}
	CVI_U16 restore_val_185[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][185] = restore_val_185[j];
	}
	CVI_U16 restore_val_186[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][186] = restore_val_186[j];
	}
	CVI_U16 restore_val_187[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][187] = restore_val_187[j];
	}
	CVI_U16 restore_val_188[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][188] = restore_val_188[j];
	}
	CVI_U16 restore_val_189[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][189] = restore_val_189[j];
	}
	CVI_U16 restore_val_190[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][190] = restore_val_190[j];
	}
	CVI_U16 restore_val_191[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][191] = restore_val_191[j];
	}
	CVI_U16 restore_val_192[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][192] = restore_val_192[j];
	}
	CVI_U16 restore_val_193[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][193] = restore_val_193[j];
	}
	CVI_U16 restore_val_194[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][194] = restore_val_194[j];
	}
	CVI_U16 restore_val_195[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][195] = restore_val_195[j];
	}
	CVI_U16 restore_val_196[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][196] = restore_val_196[j];
	}
	CVI_U16 restore_val_197[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][197] = restore_val_197[j];
	}
	CVI_U16 restore_val_198[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][198] = restore_val_198[j];
	}
	CVI_U16 restore_val_199[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][199] = restore_val_199[j];
	}
	CVI_U16 restore_val_200[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][200] = restore_val_200[j];
	}
	CVI_U16 restore_val_201[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][201] = restore_val_201[j];
	}
	CVI_U16 restore_val_202[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][202] = restore_val_202[j];
	}
	CVI_U16 restore_val_203[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][203] = restore_val_203[j];
	}
	CVI_U16 restore_val_204[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][204] = restore_val_204[j];
	}
	CVI_U16 restore_val_205[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][205] = restore_val_205[j];
	}
	CVI_U16 restore_val_206[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][206] = restore_val_206[j];
	}
	CVI_U16 restore_val_207[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][207] = restore_val_207[j];
	}
	CVI_U16 restore_val_208[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][208] = restore_val_208[j];
	}
	CVI_U16 restore_val_209[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][209] = restore_val_209[j];
	}
	CVI_U16 restore_val_210[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][210] = restore_val_210[j];
	}
	CVI_U16 restore_val_211[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][211] = restore_val_211[j];
	}
	CVI_U16 restore_val_212[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][212] = restore_val_212[j];
	}
	CVI_U16 restore_val_213[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][213] = restore_val_213[j];
	}
	CVI_U16 restore_val_214[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][214] = restore_val_214[j];
	}
	CVI_U16 restore_val_215[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][215] = restore_val_215[j];
	}
	CVI_U16 restore_val_216[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][216] = restore_val_216[j];
	}
	CVI_U16 restore_val_217[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][217] = restore_val_217[j];
	}
	CVI_U16 restore_val_218[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][218] = restore_val_218[j];
	}
	CVI_U16 restore_val_219[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][219] = restore_val_219[j];
	}
	CVI_U16 restore_val_220[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][220] = restore_val_220[j];
	}
	CVI_U16 restore_val_221[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][221] = restore_val_221[j];
	}
	CVI_U16 restore_val_222[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][222] = restore_val_222[j];
	}
	CVI_U16 restore_val_223[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][223] = restore_val_223[j];
	}
	CVI_U16 restore_val_224[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][224] = restore_val_224[j];
	}
	CVI_U16 restore_val_225[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][225] = restore_val_225[j];
	}
	CVI_U16 restore_val_226[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][226] = restore_val_226[j];
	}
	CVI_U16 restore_val_227[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][227] = restore_val_227[j];
	}
	CVI_U16 restore_val_228[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][228] = restore_val_228[j];
	}
	CVI_U16 restore_val_229[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][229] = restore_val_229[j];
	}
	CVI_U16 restore_val_230[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][230] = restore_val_230[j];
	}
	CVI_U16 restore_val_231[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][231] = restore_val_231[j];
	}
	CVI_U16 restore_val_232[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][232] = restore_val_232[j];
	}
	CVI_U16 restore_val_233[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][233] = restore_val_233[j];
	}
	CVI_U16 restore_val_234[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][234] = restore_val_234[j];
	}
	CVI_U16 restore_val_235[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][235] = restore_val_235[j];
	}
	CVI_U16 restore_val_236[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][236] = restore_val_236[j];
	}
	CVI_U16 restore_val_237[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][237] = restore_val_237[j];
	}
	CVI_U16 restore_val_238[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][238] = restore_val_238[j];
	}
	CVI_U16 restore_val_239[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][239] = restore_val_239[j];
	}
	CVI_U16 restore_val_240[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][240] = restore_val_240[j];
	}
	CVI_U16 restore_val_241[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][241] = restore_val_241[j];
	}
	CVI_U16 restore_val_242[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][242] = restore_val_242[j];
	}
	CVI_U16 restore_val_243[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][243] = restore_val_243[j];
	}
	CVI_U16 restore_val_244[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][244] = restore_val_244[j];
	}
	CVI_U16 restore_val_245[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][245] = restore_val_245[j];
	}
	CVI_U16 restore_val_246[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][246] = restore_val_246[j];
	}
	CVI_U16 restore_val_247[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][247] = restore_val_247[j];
	}
	CVI_U16 restore_val_248[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][248] = restore_val_248[j];
	}
	CVI_U16 restore_val_249[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][249] = restore_val_249[j];
	}
	CVI_U16 restore_val_250[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][250] = restore_val_250[j];
	}
	CVI_U16 restore_val_251[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][251] = restore_val_251[j];
	}
	CVI_U16 restore_val_252[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][252] = restore_val_252[j];
	}
	CVI_U16 restore_val_253[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][253] = restore_val_253[j];
	}
	CVI_U16 restore_val_254[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][254] = restore_val_254[j];
	}
	CVI_U16 restore_val_255[ISP_AUTO_ISO_STRENGTH_NUM] = { 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128 };
	for (int j = 0; j < ISP_AUTO_ISO_STRENGTH_NUM; ++j) {
		attr.stAuto.YRatioLut[j][255] = restore_val_255[j];
	}
	ret = CVI_ISP_SetCAAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_CA_CAAttr_YRatioLut_auto(void)
{
	reg_api_test_fn(test_CA_CAAttr_YRatioLut_auto);
}
