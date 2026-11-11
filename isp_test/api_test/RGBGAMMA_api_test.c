
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

static int test_RGBGAMMA_GammaAttr_Enable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_GAMMA_ATTR_S attr;

	ret = CVI_ISP_GetGammaAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetGammaAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.Enable != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.Enable);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.Enable = 0;
	ret = CVI_ISP_SetGammaAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "RGBGAMMA", "Enable", "min");
	// set maximum value
	attr.Enable = 1;
	ret = CVI_ISP_SetGammaAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "RGBGAMMA", "Enable", "max");
	// set random value
	attr.Enable = rand_range(0, 1);
	ret = CVI_ISP_SetGammaAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "RGBGAMMA", "Enable", "random");
	// restore default value
	attr.Enable = 1;
	ret = CVI_ISP_SetGammaAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_RGBGAMMA_GammaAttr_Enable(void)
{
	reg_api_test_fn(test_RGBGAMMA_GammaAttr_Enable);
}

static int test_RGBGAMMA_GammaAttr_UpdateInterval(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_GAMMA_ATTR_S attr;

	ret = CVI_ISP_GetGammaAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetGammaAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.UpdateInterval != 1) {
		TEST_FAIL("test default value: 1 != %d\n", (int)attr.UpdateInterval);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.UpdateInterval = 0;
	ret = CVI_ISP_SetGammaAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "RGBGAMMA", "UpdateInterval", "min");
	// set maximum value
	attr.UpdateInterval = 255;
	ret = CVI_ISP_SetGammaAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "RGBGAMMA", "UpdateInterval", "max");
	// set random value
	attr.UpdateInterval = rand_range(0, 255);
	ret = CVI_ISP_SetGammaAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "RGBGAMMA", "UpdateInterval", "random");
	// restore default value
	attr.UpdateInterval = 1;
	ret = CVI_ISP_SetGammaAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_RGBGAMMA_GammaAttr_UpdateInterval(void)
{
	reg_api_test_fn(test_RGBGAMMA_GammaAttr_UpdateInterval);
}

static int test_RGBGAMMA_GammaAttr_Table(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_GAMMA_ATTR_S attr;

	ret = CVI_ISP_GetGammaAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetGammaAttr failed\n");
		return ret;
	}
	// check default value test
	CVI_U16 default_val[256] = { 0,14,42,85,146,221,307,399,494,589,681,765,840,907,975,1041,1105,1168,1229,1288,1345,1398,1448,1496,1539,1579,1615,1651,1686,1720,1753,1785,1817,1847,1877,1906,1934,1962,1989,2015,2041,2067,2091,2116,2140,2163,2187,2210,2233,2255,2277,2300,2321,2342,2363,2383,2402,2421,2439,2457,2474,2491,2508,2524,2540,2555,2571,2586,2600,2615,2629,2644,2658,2672,2686,2700,2714,2728,2741,2755,2768,2781,2794,2806,2818,2830,2842,2853,2865,2876,2887,2898,2908,2919,2930,2940,2950,2961,2971,2982,2992,3002,3013,3023,3033,3043,3053,3063,3073,3083,3092,3102,3112,3121,3131,3140,3149,3158,3167,3177,3186,3195,3204,3212,3221,3230,3239,3248,3257,3265,3274,3282,3291,3299,3308,3316,3324,3333,3341,3349,3357,3365,3373,3381,3389,3397,3405,3413,3420,3428,3436,3444,3451,3459,3467,3474,3482,3489,3497,3504,3511,3519,3526,3533,3540,3548,3555,3562,3569,3576,3583,3590,3597,3604,3610,3617,3624,3631,3638,3645,3651,3658,3665,3671,3678,3684,3691,3697,3704,3710,3717,3723,3730,3736,3742,3749,3755,3761,3767,3774,3780,3786,3792,3798,3804,3811,3817,3823,3829,3835,3841,3846,3852,3858,3864,3870,3876,3881,3887,3893,3899,3904,3910,3916,3921,3927,3933,3938,3944,3949,3955,3961,3966,3972,3978,3983,3989,3995,4001,4007,4013,4019,4025,4031,4037,4042,4048,4053,4059,4064,4069,4074,4078,4083,4087,4091 };
	if (memcmp(default_val, attr.Table, sizeof(CVI_U16) * 256) != 0) {
		TEST_FAIL("test default value failed\n");
		return CVI_FAILURE;
	}
	// set minimum value
	for (int i = 0; i < 256; ++i) {
		attr.Table[i] = 0;
	}
	ret = CVI_ISP_SetGammaAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "RGBGAMMA", "Table", "min");
	// set maximum value
	for (int i = 0; i < 256; ++i) {
		attr.Table[i] = 4095;
	}
	ret = CVI_ISP_SetGammaAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "RGBGAMMA", "Table", "max");
	// set random value
	for (int i = 0; i < 256; i++) {
		attr.Table[i] = rand_range(0, 4095);
	}
	ret = CVI_ISP_SetGammaAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test random value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "RGBGAMMA", "Table", "random");
	// set abnormal value test
	for (int i = 0; i < 256; i++) {
		attr.Table[i] = rand_range(4096, 65535);
	}
	ret = CVI_ISP_SetGammaAttr(ViPipe, &attr);
	if (ret == CVI_SUCCESS) {
		TEST_FAIL("test abnormal value should fail\n");
		return CVI_FAILURE;
	}
	// restore default value
	memcpy(attr.Table, default_val, sizeof(CVI_U16) * 256);
	ret = CVI_ISP_SetGammaAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_RGBGAMMA_GammaAttr_Table(void)
{
	reg_api_test_fn(test_RGBGAMMA_GammaAttr_Table);
}

static int test_RGBGAMMA_GammaAttr_enCurveType(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_GAMMA_ATTR_S attr;

	ret = CVI_ISP_GetGammaAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetGammaAttr failed\n");
		return ret;
	}
	// check default value test
	if (attr.enCurveType != 2) {
		TEST_FAIL("test default value: 2 != %d\n", (int)attr.enCurveType);
		return CVI_FAILURE;
	}
	// set minimum value
	attr.enCurveType = ISP_GAMMA_CURVE_DEFAULT;
	ret = CVI_ISP_SetGammaAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test minimum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "RGBGAMMA", "enCurveType", "min");
	// set maximum value
	attr.enCurveType = ISP_GAMMA_CURVE_BYPASS;
	ret = CVI_ISP_SetGammaAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("test maximum value failed\n");
		return ret;
	}
	vd_wait_with_retry_or_exit(ViPipe, "RGBGAMMA", "enCurveType", "max");
	// restore default value
	attr.enCurveType = 2;
	ret = CVI_ISP_SetGammaAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore default value failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_RGBGAMMA_GammaAttr_enCurveType(void)
{
	reg_api_test_fn(test_RGBGAMMA_GammaAttr_enCurveType);
}
