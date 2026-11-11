/*
 * ae_api_ext_test.c - AE family MPI coverage for daemon builtin suite 1 (module api test).
 *
 * NOTE: this file lives in unit_test/ (hand-written zone) on purpose:
 * files under api_test/ are AUTO-GENERATED from module_param/isp_module_param_phobos3.xlsx
 * (cvi_mpi/modules/isp/common/code_gen/gen_module_api_test.py) and get
 * overwritten on regeneration. AE is not in the xlsx (3A defaults are
 * sensor-dependent, they don't fit the generated assert-default pattern);
 * these tests register into suite 1 via reg_api_test_fn() constructors.
 *
 * Covered APIs (symbols confirmed in cvi_mpi/include/isp/cvi_ae.h and
 * cvi_mpi/lib/libisp_ipc_client.so; struct definitions in cvi_comm_3a.h
 * and cvi_comm_isp.h):
 *   CVI_ISP_SetExposureAttr / CVI_ISP_GetExposureAttr		per-field roundtrip
 *   CVI_ISP_QueryExposureInfo					call + sanity assertions
 *   CVI_ISP_GetAEConvergeInfo					call + sanity assertions
 *   CVI_ISP_SetAERouteAttr / CVI_ISP_GetAERouteAttr		identity roundtrip
 *   CVI_ISP_SetAERouteAttrEx / CVI_ISP_GetAERouteAttrEx	identity roundtrip
 *   CVI_ISP_SetAERouteSFAttr / CVI_ISP_GetAERouteSFAttr	identity roundtrip
 *   CVI_ISP_SetAERouteSFAttrEx / CVI_ISP_GetAERouteSFAttrEx	identity roundtrip
 *   CVI_ISP_SetSmartExposureAttr / CVI_ISP_GetSmartExposureAttr	per-field roundtrip
 *   CVI_ISP_SetAEStatisticsConfig / CVI_ISP_GetAEStatisticsConfig	per-field roundtrip
 *   CVI_ISP_SetFastConvergeAttr / CVI_ISP_GetFastConvergeAttr	per-field roundtrip
 *   CVI_ISP_GetFastConvCalibrationInfo				guarded call test
 *
 * Strategy: AE defaults vary with sensor and pqbin, so no hardcoded default
 * values are asserted. Each Set test does: Get original -> modify field(s)
 * within documented ranges -> Set -> wait VD -> Get -> verify the modified
 * fields read back identical -> restore original -> wait VD. Fields without
 * a documented range are perturbed within conservative sub-ranges or left
 * out. Route tables use identity roundtrip (Set the value just Read) because
 * a valid route must satisfy inter-node constraints; if the running route is
 * unconfigured (u32TotalNum == 0, Set would be rejected by range check), only
 * the Get path is exercised and a skip note is printed.
 */

#include <stdlib.h>
#include <string.h>
#include "api_test_main.h"
#include "cvi_ae.h"

#define TEST_FAIL(fmt, arg...) printf("[ISP_TEST_FAIL] %s,%d: " fmt, __func__, __LINE__, ##arg)

static long long rand_range(long long a, long long b)
{
	return rand() % (b - a + 1) + a;
}

static CVI_U8 pick_diff_u8(CVI_U8 cur, CVI_U8 lo, CVI_U8 hi)
{
	CVI_U8 v = (CVI_U8)rand_range(lo, hi);

	if (v == cur) {
		v = (cur == lo) ? hi : lo;
	}
	return v;
}

static CVI_U16 pick_diff_u16(CVI_U16 cur, CVI_U16 lo, CVI_U16 hi)
{
	CVI_U16 v = (CVI_U16)rand_range(lo, hi);

	if (v == cur) {
		v = (cur == lo) ? hi : lo;
	}
	return v;
}

static CVI_U32 pick_diff_u32(CVI_U32 cur, CVI_U32 lo, CVI_U32 hi)
{
	CVI_U32 v = (CVI_U32)rand_range((long long)lo, (long long)hi);

	if (v == cur) {
		v = (cur == lo) ? hi : lo;
	}
	return v;
}

static CVI_S8 pick_diff_s8(CVI_S8 cur, CVI_S8 lo, CVI_S8 hi)
{
	CVI_S8 v = (CVI_S8)rand_range(lo, hi);

	if (v == cur) {
		v = (cur == lo) ? hi : lo;
	}
	return v;
}

static CVI_S32 ae_wait_vd(VI_PIPE ViPipe)
{
	return CVI_ISP_GetVDTimeOut(ViPipe, ISP_VD_BE_END, 200);
}

/* -------------------- CVI_ISP_Set/GetExposureAttr -------------------- */

static int test_AE_ExposureAttr_bByPass(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within {0,1}
	attr.bByPass = !attr.bByPass;
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set bByPass=%d failed\n", (int)attr.bByPass);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	// verify readback
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.bByPass != attr.bByPass) {
		TEST_FAIL("bByPass readback %d != %d\n", (int)attr2.bByPass, (int)attr.bByPass);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	// restore original
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_bByPass(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_bByPass);
}

static int test_AE_ExposureAttr_u8AERunInterval(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [0x1, 0xFF]
	attr.u8AERunInterval = pick_diff_u8(attr.u8AERunInterval, 0x1, 0xFF);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u8AERunInterval=%d failed\n", (int)attr.u8AERunInterval);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.u8AERunInterval != attr.u8AERunInterval) {
		TEST_FAIL("u8AERunInterval readback %d != %d\n", (int)attr2.u8AERunInterval,
			  (int)attr.u8AERunInterval);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_u8AERunInterval(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_u8AERunInterval);
}

static int test_AE_ExposureAttr_bHistStatAdjust(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within {0,1}
	attr.bHistStatAdjust = !attr.bHistStatAdjust;
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set bHistStatAdjust=%d failed\n", (int)attr.bHistStatAdjust);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.bHistStatAdjust != attr.bHistStatAdjust) {
		TEST_FAIL("bHistStatAdjust readback %d != %d\n", (int)attr2.bHistStatAdjust,
			  (int)attr.bHistStatAdjust);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_bHistStatAdjust(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_bHistStatAdjust);
}

static int test_AE_ExposureAttr_bAERouteExValid(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within {0,1}
	attr.bAERouteExValid = !attr.bAERouteExValid;
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set bAERouteExValid=%d failed\n", (int)attr.bAERouteExValid);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.bAERouteExValid != attr.bAERouteExValid) {
		TEST_FAIL("bAERouteExValid readback %d != %d\n", (int)attr2.bAERouteExValid,
			  (int)attr.bAERouteExValid);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_bAERouteExValid(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_bAERouteExValid);
}

static int test_AE_ExposureAttr_bAEGainSepCfg(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within {0,1}
	attr.bAEGainSepCfg = !attr.bAEGainSepCfg;
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set bAEGainSepCfg=%d failed\n", (int)attr.bAEGainSepCfg);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.bAEGainSepCfg != attr.bAEGainSepCfg) {
		TEST_FAIL("bAEGainSepCfg readback %d != %d\n", (int)attr2.bAEGainSepCfg,
			  (int)attr.bAEGainSepCfg);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_bAEGainSepCfg(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_bAEGainSepCfg);
}

static int test_AE_ExposureAttr_u8DebugMode(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [0, 0xFF]
	attr.u8DebugMode = pick_diff_u8(attr.u8DebugMode, 0, 0xFF);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u8DebugMode=%d failed\n", (int)attr.u8DebugMode);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.u8DebugMode != attr.u8DebugMode) {
		TEST_FAIL("u8DebugMode readback %d != %d\n", (int)attr2.u8DebugMode,
			  (int)attr.u8DebugMode);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_u8DebugMode(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_u8DebugMode);
}

static int test_AE_ExposureAttr_s8SensorSensitivity(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [-0xA, 0xA]
	attr.s8SensorSensitivity = pick_diff_s8(attr.s8SensorSensitivity, -0xA, 0xA);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set s8SensorSensitivity=%d failed\n", (int)attr.s8SensorSensitivity);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.s8SensorSensitivity != attr.s8SensorSensitivity) {
		TEST_FAIL("s8SensorSensitivity readback %d != %d\n", (int)attr2.s8SensorSensitivity,
			  (int)attr.s8SensorSensitivity);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_s8SensorSensitivity(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_s8SensorSensitivity);
}

static int test_AE_ExposureAttr_stAuto_u8Speed(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [1, 100]
	attr.stAuto.u8Speed = pick_diff_u8(attr.stAuto.u8Speed, 1, 100);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u8Speed=%d failed\n", (int)attr.stAuto.u8Speed);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.stAuto.u8Speed != attr.stAuto.u8Speed) {
		TEST_FAIL("u8Speed readback %d != %d\n", (int)attr2.stAuto.u8Speed,
			  (int)attr.stAuto.u8Speed);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stAuto_u8Speed(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stAuto_u8Speed);
}

static int test_AE_ExposureAttr_stAuto_u8Tolerance(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [0, 0x50]
	attr.stAuto.u8Tolerance = pick_diff_u8(attr.stAuto.u8Tolerance, 0, 0x50);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u8Tolerance=%d failed\n", (int)attr.stAuto.u8Tolerance);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.stAuto.u8Tolerance != attr.stAuto.u8Tolerance) {
		TEST_FAIL("u8Tolerance readback %d != %d\n", (int)attr2.stAuto.u8Tolerance,
			  (int)attr.stAuto.u8Tolerance);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stAuto_u8Tolerance(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stAuto_u8Tolerance);
}

static int test_AE_ExposureAttr_stAuto_u8Compensation(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [0, 100]
	attr.stAuto.u8Compensation = pick_diff_u8(attr.stAuto.u8Compensation, 0, 100);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u8Compensation=%d failed\n", (int)attr.stAuto.u8Compensation);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.stAuto.u8Compensation != attr.stAuto.u8Compensation) {
		TEST_FAIL("u8Compensation readback %d != %d\n", (int)attr2.stAuto.u8Compensation,
			  (int)attr.stAuto.u8Compensation);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stAuto_u8Compensation(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stAuto_u8Compensation);
}

static int test_AE_ExposureAttr_stAuto_stAEDelayAttr(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify both u16 delay frames within [0, 0xFFFF]
	attr.stAuto.stAEDelayAttr.u16BlackDelayFrame =
		pick_diff_u16(attr.stAuto.stAEDelayAttr.u16BlackDelayFrame, 0, 0xFFFF);
	attr.stAuto.stAEDelayAttr.u16WhiteDelayFrame =
		pick_diff_u16(attr.stAuto.stAEDelayAttr.u16WhiteDelayFrame, 0, 0xFFFF);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set stAEDelayAttr failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.stAuto.stAEDelayAttr.u16BlackDelayFrame != attr.stAuto.stAEDelayAttr.u16BlackDelayFrame ||
	    attr2.stAuto.stAEDelayAttr.u16WhiteDelayFrame != attr.stAuto.stAEDelayAttr.u16WhiteDelayFrame) {
		TEST_FAIL("stAEDelayAttr readback %d/%d != %d/%d\n",
			  (int)attr2.stAuto.stAEDelayAttr.u16BlackDelayFrame,
			  (int)attr2.stAuto.stAEDelayAttr.u16WhiteDelayFrame,
			  (int)attr.stAuto.stAEDelayAttr.u16BlackDelayFrame,
			  (int)attr.stAuto.stAEDelayAttr.u16WhiteDelayFrame);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stAuto_stAEDelayAttr(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stAuto_stAEDelayAttr);
}

static int test_AE_ExposureAttr_stAuto_enAEStrategyMode(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify enum within {AE_EXP_HIGHLIGHT_PRIOR, AE_EXP_LOWLIGHT_PRIOR}
	attr.stAuto.enAEStrategyMode = (attr.stAuto.enAEStrategyMode == AE_EXP_HIGHLIGHT_PRIOR)
					       ? AE_EXP_LOWLIGHT_PRIOR
					       : AE_EXP_HIGHLIGHT_PRIOR;
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set enAEStrategyMode=%d failed\n", (int)attr.stAuto.enAEStrategyMode);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.stAuto.enAEStrategyMode != attr.stAuto.enAEStrategyMode) {
		TEST_FAIL("enAEStrategyMode readback %d != %d\n", (int)attr2.stAuto.enAEStrategyMode,
			  (int)attr.stAuto.enAEStrategyMode);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stAuto_enAEStrategyMode(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stAuto_enAEStrategyMode);
}

static int test_AE_ExposureAttr_stAuto_enAEMode(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify enum within {AE_MODE_SLOW_SHUTTER, AE_MODE_FIX_FRAME_RATE}
	attr.stAuto.enAEMode = (attr.stAuto.enAEMode == AE_MODE_SLOW_SHUTTER) ? AE_MODE_FIX_FRAME_RATE
										 : AE_MODE_SLOW_SHUTTER;
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set enAEMode=%d failed\n", (int)attr.stAuto.enAEMode);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.stAuto.enAEMode != attr.stAuto.enAEMode) {
		TEST_FAIL("enAEMode readback %d != %d\n", (int)attr2.stAuto.enAEMode,
			  (int)attr.stAuto.enAEMode);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stAuto_enAEMode(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stAuto_enAEMode);
}

static int test_AE_ExposureAttr_stAuto_enGainType(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify enum within {AE_TYPE_GAIN, AE_TYPE_ISO}
	attr.stAuto.enGainType =
		(attr.stAuto.enGainType == AE_TYPE_GAIN) ? AE_TYPE_ISO : AE_TYPE_GAIN;
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set enGainType=%d failed\n", (int)attr.stAuto.enGainType);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.stAuto.enGainType != attr.stAuto.enGainType) {
		TEST_FAIL("enGainType readback %d != %d\n", (int)attr2.stAuto.enGainType,
			  (int)attr.stAuto.enGainType);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stAuto_enGainType(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stAuto_enGainType);
}

static int test_AE_ExposureAttr_stAuto_u16HistRatioSlope(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [0, 0x200]
	attr.stAuto.u16HistRatioSlope = pick_diff_u16(attr.stAuto.u16HistRatioSlope, 0, 0x200);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u16HistRatioSlope=%d failed\n", (int)attr.stAuto.u16HistRatioSlope);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.stAuto.u16HistRatioSlope != attr.stAuto.u16HistRatioSlope) {
		TEST_FAIL("u16HistRatioSlope readback %d != %d\n", (int)attr2.stAuto.u16HistRatioSlope,
			  (int)attr.stAuto.u16HistRatioSlope);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stAuto_u16HistRatioSlope(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stAuto_u16HistRatioSlope);
}

static int test_AE_ExposureAttr_stAuto_u16AEStrategyThr(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;
	CVI_U8 i;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [1, 0x3E8]
	for (i = 0; i < LV_TOTAL_NUM; i++)
		attr.stAuto.u16AEStrategyThr[i] = pick_diff_u16(attr.stAuto.u16AEStrategyThr[i], 1, 0x3E8);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u16AEStrategyThr failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (memcmp(attr2.stAuto.u16AEStrategyThr, attr.stAuto.u16AEStrategyThr,
		   sizeof(attr.stAuto.u16AEStrategyThr)) != 0) {
		TEST_FAIL("u16AEStrategyThr readback mismatch\n");
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stAuto_u16AEStrategyThr(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stAuto_u16AEStrategyThr);
}

static int test_AE_ExposureAttr_stAuto_bEnableFaceAE(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within {0,1}
	attr.stAuto.bEnableFaceAE = !attr.stAuto.bEnableFaceAE;
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set bEnableFaceAE=%d failed\n", (int)attr.stAuto.bEnableFaceAE);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.stAuto.bEnableFaceAE != attr.stAuto.bEnableFaceAE) {
		TEST_FAIL("bEnableFaceAE readback %d != %d\n", (int)attr2.stAuto.bEnableFaceAE,
			  (int)attr.stAuto.bEnableFaceAE);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stAuto_bEnableFaceAE(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stAuto_bEnableFaceAE);
}

static int test_AE_ExposureAttr_stAuto_u8FaceTargetLuma(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [1, 0xFF]
	attr.stAuto.u8FaceTargetLuma = pick_diff_u8(attr.stAuto.u8FaceTargetLuma, 1, 0xFF);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u8FaceTargetLuma=%d failed\n", (int)attr.stAuto.u8FaceTargetLuma);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.stAuto.u8FaceTargetLuma != attr.stAuto.u8FaceTargetLuma) {
		TEST_FAIL("u8FaceTargetLuma readback %d != %d\n", (int)attr2.stAuto.u8FaceTargetLuma,
			  (int)attr.stAuto.u8FaceTargetLuma);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stAuto_u8FaceTargetLuma(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stAuto_u8FaceTargetLuma);
}

static int test_AE_ExposureAttr_stAuto_u8FaceWeight(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [0, 0x64]
	attr.stAuto.u8FaceWeight = pick_diff_u8(attr.stAuto.u8FaceWeight, 0, 0x64);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u8FaceWeight=%d failed\n", (int)attr.stAuto.u8FaceWeight);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.stAuto.u8FaceWeight != attr.stAuto.u8FaceWeight) {
		TEST_FAIL("u8FaceWeight readback %d != %d\n", (int)attr2.stAuto.u8FaceWeight,
			  (int)attr.stAuto.u8FaceWeight);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stAuto_u8FaceWeight(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stAuto_u8FaceWeight);
}

static int test_AE_ExposureAttr_stAuto_u8HighLightLumaThr(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;
	CVI_U8 i;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [0, 0xFF]
	for (i = 0; i < LV_TOTAL_NUM; i++)
		attr.stAuto.u8HighLightLumaThr[i] = pick_diff_u8(attr.stAuto.u8HighLightLumaThr[i], 0, 0xFF);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u8HighLightLumaThr failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (memcmp(attr2.stAuto.u8HighLightLumaThr, attr.stAuto.u8HighLightLumaThr,
		   sizeof(attr.stAuto.u8HighLightLumaThr)) != 0) {
		TEST_FAIL("u8HighLightLumaThr readback mismatch\n");
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stAuto_u8HighLightLumaThr(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stAuto_u8HighLightLumaThr);
}

static int test_AE_ExposureAttr_stAuto_u8HighLightBufLumaThr(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;
	CVI_U8 i;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [0, 0xFF]
	for (i = 0; i < LV_TOTAL_NUM; i++)
		attr.stAuto.u8HighLightBufLumaThr[i] = pick_diff_u8(attr.stAuto.u8HighLightBufLumaThr[i], 0, 0xFF);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u8HighLightBufLumaThr failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (memcmp(attr2.stAuto.u8HighLightBufLumaThr, attr.stAuto.u8HighLightBufLumaThr,
		   sizeof(attr.stAuto.u8HighLightBufLumaThr)) != 0) {
		TEST_FAIL("u8HighLightBufLumaThr readback mismatch\n");
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stAuto_u8HighLightBufLumaThr(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stAuto_u8HighLightBufLumaThr);
}

static int test_AE_ExposureAttr_stAuto_u8LowLightLumaThr(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;
	CVI_U8 i;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [0, 0xFF]
	for (i = 0; i < LV_TOTAL_NUM; i++)
		attr.stAuto.u8LowLightLumaThr[i] = pick_diff_u8(attr.stAuto.u8LowLightLumaThr[i], 0, 0xFF);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u8LowLightLumaThr failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (memcmp(attr2.stAuto.u8LowLightLumaThr, attr.stAuto.u8LowLightLumaThr,
		   sizeof(attr.stAuto.u8LowLightLumaThr)) != 0) {
		TEST_FAIL("u8LowLightLumaThr readback mismatch\n");
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stAuto_u8LowLightLumaThr(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stAuto_u8LowLightLumaThr);
}

static int test_AE_ExposureAttr_stAuto_u8LowLightBufLumaThr(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;
	CVI_U8 i;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [0, 0xFF]
	for (i = 0; i < LV_TOTAL_NUM; i++)
		attr.stAuto.u8LowLightBufLumaThr[i] = pick_diff_u8(attr.stAuto.u8LowLightBufLumaThr[i], 0, 0xFF);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u8LowLightBufLumaThr failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (memcmp(attr2.stAuto.u8LowLightBufLumaThr, attr.stAuto.u8LowLightBufLumaThr,
		   sizeof(attr.stAuto.u8LowLightBufLumaThr)) != 0) {
		TEST_FAIL("u8LowLightBufLumaThr readback mismatch\n");
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stAuto_u8LowLightBufLumaThr(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stAuto_u8LowLightBufLumaThr);
}

static int test_AE_ExposureAttr_stAuto_bHistogramAssist(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within {0,1}
	attr.stAuto.bHistogramAssist = !attr.stAuto.bHistogramAssist;
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set bHistogramAssist=%d failed\n", (int)attr.stAuto.bHistogramAssist);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.stAuto.bHistogramAssist != attr.stAuto.bHistogramAssist) {
		TEST_FAIL("bHistogramAssist readback %d != %d\n", (int)attr2.stAuto.bHistogramAssist,
			  (int)attr.stAuto.bHistogramAssist);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stAuto_bHistogramAssist(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stAuto_bHistogramAssist);
}

static int test_AE_ExposureAttr_stAuto_u16StsWithWBGainStr(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [0, 0x1000]
	attr.stAuto.u16StsWithWBGainStr = pick_diff_u16(attr.stAuto.u16StsWithWBGainStr, 0, 0x1000);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u16StsWithWBGainStr=%d failed\n", (int)attr.stAuto.u16StsWithWBGainStr);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.stAuto.u16StsWithWBGainStr != attr.stAuto.u16StsWithWBGainStr) {
		TEST_FAIL("u16StsWithWBGainStr readback %d != %d\n",
			  (int)attr2.stAuto.u16StsWithWBGainStr, (int)attr.stAuto.u16StsWithWBGainStr);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stAuto_u16StsWithWBGainStr(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stAuto_u16StsWithWBGainStr);
}

/*
 * stManual fields only take effect when enOpType is OP_TYPE_MANUAL. These
 * tests keep the current enOpType untouched, so in the usual AUTO mode they
 * verify pure storage roundtrip without driving real sensor exposure.
 */
static int test_AE_ExposureAttr_stManual_u32ExpTime(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [0x1, 0xF4240]
	attr.stManual.u32ExpTime = pick_diff_u32(attr.stManual.u32ExpTime, 0x1, 0xF4240);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u32ExpTime=%u failed\n", (unsigned int)attr.stManual.u32ExpTime);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.stManual.u32ExpTime != attr.stManual.u32ExpTime) {
		TEST_FAIL("u32ExpTime readback %u != %u\n", (unsigned int)attr2.stManual.u32ExpTime,
			  (unsigned int)attr.stManual.u32ExpTime);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stManual_u32ExpTime(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stManual_u32ExpTime);
}

static int test_AE_ExposureAttr_stManual_u32AGain(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [0x400, 0x100000]
	attr.stManual.u32AGain = pick_diff_u32(attr.stManual.u32AGain, 0x400, 0x100000);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u32AGain=%u failed\n", (unsigned int)attr.stManual.u32AGain);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.stManual.u32AGain != attr.stManual.u32AGain) {
		TEST_FAIL("u32AGain readback %u != %u\n", (unsigned int)attr2.stManual.u32AGain,
			  (unsigned int)attr.stManual.u32AGain);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stManual_u32AGain(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stManual_u32AGain);
}

static int test_AE_ExposureAttr_stManual_u32DGain(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [0x400, 0x100000]
	attr.stManual.u32DGain = pick_diff_u32(attr.stManual.u32DGain, 0x400, 0x100000);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u32DGain=%u failed\n", (unsigned int)attr.stManual.u32DGain);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.stManual.u32DGain != attr.stManual.u32DGain) {
		TEST_FAIL("u32DGain readback %u != %u\n", (unsigned int)attr2.stManual.u32DGain,
			  (unsigned int)attr.stManual.u32DGain);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stManual_u32DGain(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stManual_u32DGain);
}

static int test_AE_ExposureAttr_stManual_u32ISPDGain(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [0x400, 0x40000]
	attr.stManual.u32ISPDGain = pick_diff_u32(attr.stManual.u32ISPDGain, 0x400, 0x40000);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u32ISPDGain=%u failed\n", (unsigned int)attr.stManual.u32ISPDGain);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.stManual.u32ISPDGain != attr.stManual.u32ISPDGain) {
		TEST_FAIL("u32ISPDGain readback %u != %u\n", (unsigned int)attr2.stManual.u32ISPDGain,
			  (unsigned int)attr.stManual.u32ISPDGain);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stManual_u32ISPDGain(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stManual_u32ISPDGain);
}

static int test_AE_ExposureAttr_stManual_u32ISONum(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [0x64, 0x3200]
	attr.stManual.u32ISONum = pick_diff_u32(attr.stManual.u32ISONum, 0x64, 0x3200);
	ret = CVI_ISP_SetExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u32ISONum=%u failed\n", (unsigned int)attr.stManual.u32ISONum);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.stManual.u32ISONum != attr.stManual.u32ISONum) {
		TEST_FAIL("u32ISONum readback %u != %u\n", (unsigned int)attr2.stManual.u32ISONum,
			  (unsigned int)attr.stManual.u32ISONum);
		CVI_ISP_SetExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_ExposureAttr_stManual_u32ISONum(void)
{
	reg_api_test_fn(test_AE_ExposureAttr_stManual_u32ISONum);
}

/* -------------------- CVI_ISP_QueryExposureInfo -------------------- */

static int test_AE_QueryExposureInfo(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_EXP_INFO_S info;

	memset(&info, 0, sizeof(info));
	ret = CVI_ISP_QueryExposureInfo(ViPipe, &info);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_QueryExposureInfo failed\n");
		return ret;
	}
	// sanity: exposure time in us must be positive
	if (info.u32ExpTime == 0) {
		TEST_FAIL("u32ExpTime == 0\n");
		return CVI_FAILURE;
	}
	// sanity: ISO must be positive
	if (info.u32ISO == 0) {
		TEST_FAIL("u32ISO == 0\n");
		return CVI_FAILURE;
	}
	// sanity: u32Fps is fps * 100, allow (0, 240] fps
	if (info.u32Fps == 0 || info.u32Fps > 24000) {
		TEST_FAIL("u32Fps out of range: %u\n", (unsigned int)info.u32Fps);
		return CVI_FAILURE;
	}
	// sanity: gains must be positive
	if (info.u32AGain == 0 || info.u32DGain == 0 || info.u32ISPDGain == 0) {
		TEST_FAIL("gain zero: AGain=%u DGain=%u ISPDGain=%u\n", (unsigned int)info.u32AGain,
			  (unsigned int)info.u32DGain, (unsigned int)info.u32ISPDGain);
		return CVI_FAILURE;
	}
	printf("[ISP_TEST_INFO] QueryExposureInfo: ExpTime=%uus ISO=%u Fps=%u AGain=%u DGain=%u ISPDGain=%u\n",
	       (unsigned int)info.u32ExpTime, (unsigned int)info.u32ISO, (unsigned int)info.u32Fps,
	       (unsigned int)info.u32AGain, (unsigned int)info.u32DGain,
	       (unsigned int)info.u32ISPDGain);
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_QueryExposureInfo(void)
{
	reg_api_test_fn(test_AE_QueryExposureInfo);
}

/* -------------------- CVI_ISP_GetAEConvergeInfo -------------------- */

static int test_AE_GetAEConvergeInfo(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_AE_CONVERGE_INFO_S conv;

	memset(&conv, 0, sizeof(conv));
	ret = CVI_ISP_GetAEConvergeInfo(ViPipe, &conv);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetAEConvergeInfo failed\n");
		return ret;
	}
	// sanity: bIsStable must be 0/1
	if (conv.bIsStable != CVI_FALSE && conv.bIsStable != CVI_TRUE) {
		TEST_FAIL("bIsStable invalid: %d\n", (int)conv.bIsStable);
		return CVI_FAILURE;
	}
	// sanity: tolerance documented range [0, 0x50]
	if (conv.u8Tolerance > 0x50) {
		TEST_FAIL("u8Tolerance out of range: %d\n", (int)conv.u8Tolerance);
		return CVI_FAILURE;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_GetAEConvergeInfo(void)
{
	reg_api_test_fn(test_AE_GetAEConvergeInfo);
}

/* -------------------- CVI_ISP_Set/GetAERouteAttr family -------------------- */

static int test_AE_AERouteAttr(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_AE_ROUTE_S attr, attr2;

	memset(&attr, 0, sizeof(attr));
	ret = CVI_ISP_GetAERouteAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetAERouteAttr failed\n");
		return ret;
	}
	// identity roundtrip only when a route is configured; Set rejects TotalNum 0
	if (attr.u32TotalNum < ISP_AE_ROUTE_MIN_NODES || attr.u32TotalNum > ISP_AE_ROUTE_MAX_NODES) {
		printf("[ISP_TEST_SKIP] %s: route unconfigured (TotalNum=%u), Get-only\n", __func__,
		       (unsigned int)attr.u32TotalNum);
		return CVI_SUCCESS;
	}
	ret = CVI_ISP_SetAERouteAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_SetAERouteAttr failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	memset(&attr2, 0, sizeof(attr2));
	ret = CVI_ISP_GetAERouteAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetAERouteAttr after set failed\n");
		return ret;
	}
	// all members are 4-byte aligned, no padding: memcmp is safe
	if (memcmp(&attr, &attr2, sizeof(ISP_AE_ROUTE_S)) != 0) {
		TEST_FAIL("route identity roundtrip mismatch\n");
		return CVI_FAILURE;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_AERouteAttr(void)
{
	reg_api_test_fn(test_AE_AERouteAttr);
}

static int test_AE_AERouteAttrEx(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_AE_ROUTE_EX_S attr, attr2;

	memset(&attr, 0, sizeof(attr));
	ret = CVI_ISP_GetAERouteAttrEx(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetAERouteAttrEx failed\n");
		return ret;
	}
	// identity roundtrip only when a route is configured; Set rejects TotalNum 0
	if (attr.u32TotalNum < ISP_AE_ROUTE_EX_MIN_NODES ||
	    attr.u32TotalNum > ISP_AE_ROUTE_EX_MAX_NODES) {
		printf("[ISP_TEST_SKIP] %s: route ex unconfigured (TotalNum=%u), Get-only\n",
		       __func__, (unsigned int)attr.u32TotalNum);
		return CVI_SUCCESS;
	}
	ret = CVI_ISP_SetAERouteAttrEx(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_SetAERouteAttrEx failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	memset(&attr2, 0, sizeof(attr2));
	ret = CVI_ISP_GetAERouteAttrEx(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetAERouteAttrEx after set failed\n");
		return ret;
	}
	if (memcmp(&attr, &attr2, sizeof(ISP_AE_ROUTE_EX_S)) != 0) {
		TEST_FAIL("route ex identity roundtrip mismatch\n");
		return CVI_FAILURE;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_AERouteAttrEx(void)
{
	reg_api_test_fn(test_AE_AERouteAttrEx);
}

static int test_AE_AERouteSFAttr(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_AE_ROUTE_S attr, attr2;

	memset(&attr, 0, sizeof(attr));
	ret = CVI_ISP_GetAERouteSFAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetAERouteSFAttr failed\n");
		return ret;
	}
	// in non-WDR mode Get returns an all-zero struct and Set is a no-op:
	// only exercise the roundtrip when a SF route is actually configured
	if (attr.u32TotalNum < ISP_AE_ROUTE_MIN_NODES || attr.u32TotalNum > ISP_AE_ROUTE_MAX_NODES) {
		printf("[ISP_TEST_SKIP] %s: SF route unconfigured (TotalNum=%u), Get-only\n",
		       __func__, (unsigned int)attr.u32TotalNum);
		return CVI_SUCCESS;
	}
	ret = CVI_ISP_SetAERouteSFAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_SetAERouteSFAttr failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	memset(&attr2, 0, sizeof(attr2));
	ret = CVI_ISP_GetAERouteSFAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetAERouteSFAttr after set failed\n");
		return ret;
	}
	if (memcmp(&attr, &attr2, sizeof(ISP_AE_ROUTE_S)) != 0) {
		TEST_FAIL("SF route identity roundtrip mismatch\n");
		return CVI_FAILURE;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_AERouteSFAttr(void)
{
	reg_api_test_fn(test_AE_AERouteSFAttr);
}

static int test_AE_AERouteSFAttrEx(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_AE_ROUTE_EX_S attr, attr2;

	memset(&attr, 0, sizeof(attr));
	ret = CVI_ISP_GetAERouteSFAttrEx(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetAERouteSFAttrEx failed\n");
		return ret;
	}
	// in non-WDR mode Get returns an all-zero struct and Set is a no-op:
	// only exercise the roundtrip when a SF route is actually configured
	if (attr.u32TotalNum < ISP_AE_ROUTE_EX_MIN_NODES ||
	    attr.u32TotalNum > ISP_AE_ROUTE_EX_MAX_NODES) {
		printf("[ISP_TEST_SKIP] %s: SF route ex unconfigured (TotalNum=%u), Get-only\n",
		       __func__, (unsigned int)attr.u32TotalNum);
		return CVI_SUCCESS;
	}
	ret = CVI_ISP_SetAERouteSFAttrEx(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_SetAERouteSFAttrEx failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	memset(&attr2, 0, sizeof(attr2));
	ret = CVI_ISP_GetAERouteSFAttrEx(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetAERouteSFAttrEx after set failed\n");
		return ret;
	}
	if (memcmp(&attr, &attr2, sizeof(ISP_AE_ROUTE_EX_S)) != 0) {
		TEST_FAIL("SF route ex identity roundtrip mismatch\n");
		return CVI_FAILURE;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_AERouteSFAttrEx(void)
{
	reg_api_test_fn(test_AE_AERouteSFAttrEx);
}

/* -------------------- CVI_ISP_Set/GetSmartExposureAttr -------------------- */

static int test_AE_SmartExposureAttr_bEnable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SMART_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetSmartExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSmartExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within {0,1}
	attr.bEnable = !attr.bEnable;
	ret = CVI_ISP_SetSmartExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set bEnable=%d failed\n", (int)attr.bEnable);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetSmartExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.bEnable != attr.bEnable) {
		TEST_FAIL("bEnable readback %d != %d\n", (int)attr2.bEnable, (int)attr.bEnable);
		CVI_ISP_SetSmartExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetSmartExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_SmartExposureAttr_bEnable(void)
{
	reg_api_test_fn(test_AE_SmartExposureAttr_bEnable);
}

static int test_AE_SmartExposureAttr_bIRMode(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SMART_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetSmartExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSmartExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within {0,1}
	attr.bIRMode = !attr.bIRMode;
	ret = CVI_ISP_SetSmartExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set bIRMode=%d failed\n", (int)attr.bIRMode);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetSmartExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.bIRMode != attr.bIRMode) {
		TEST_FAIL("bIRMode readback %d != %d\n", (int)attr2.bIRMode, (int)attr.bIRMode);
		CVI_ISP_SetSmartExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetSmartExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_SmartExposureAttr_bIRMode(void)
{
	reg_api_test_fn(test_AE_SmartExposureAttr_bIRMode);
}

static int test_AE_SmartExposureAttr_enSmartExpType(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SMART_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetSmartExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSmartExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify enum within {OP_TYPE_AUTO, OP_TYPE_MANUAL}
	attr.enSmartExpType =
		(attr.enSmartExpType == OP_TYPE_AUTO) ? OP_TYPE_MANUAL : OP_TYPE_AUTO;
	ret = CVI_ISP_SetSmartExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set enSmartExpType=%d failed\n", (int)attr.enSmartExpType);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetSmartExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.enSmartExpType != attr.enSmartExpType) {
		TEST_FAIL("enSmartExpType readback %d != %d\n", (int)attr2.enSmartExpType,
			  (int)attr.enSmartExpType);
		CVI_ISP_SetSmartExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetSmartExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_SmartExposureAttr_enSmartExpType(void)
{
	reg_api_test_fn(test_AE_SmartExposureAttr_enSmartExpType);
}

static int test_AE_SmartExposureAttr_u8LumaTarget(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SMART_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetSmartExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSmartExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [0, 0xFF]
	attr.u8LumaTarget = pick_diff_u8(attr.u8LumaTarget, 0, 0xFF);
	ret = CVI_ISP_SetSmartExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u8LumaTarget=%d failed\n", (int)attr.u8LumaTarget);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetSmartExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.u8LumaTarget != attr.u8LumaTarget) {
		TEST_FAIL("u8LumaTarget readback %d != %d\n", (int)attr2.u8LumaTarget,
			  (int)attr.u8LumaTarget);
		CVI_ISP_SetSmartExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetSmartExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_SmartExposureAttr_u8LumaTarget(void)
{
	reg_api_test_fn(test_AE_SmartExposureAttr_u8LumaTarget);
}

static int test_AE_SmartExposureAttr_u8SmartInterval(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SMART_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetSmartExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSmartExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [1, 0xFF]
	attr.u8SmartInterval = pick_diff_u8(attr.u8SmartInterval, 1, 0xFF);
	ret = CVI_ISP_SetSmartExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u8SmartInterval=%d failed\n", (int)attr.u8SmartInterval);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetSmartExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.u8SmartInterval != attr.u8SmartInterval) {
		TEST_FAIL("u8SmartInterval readback %d != %d\n", (int)attr2.u8SmartInterval,
			  (int)attr.u8SmartInterval);
		CVI_ISP_SetSmartExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetSmartExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_SmartExposureAttr_u8SmartInterval(void)
{
	reg_api_test_fn(test_AE_SmartExposureAttr_u8SmartInterval);
}

static int test_AE_SmartExposureAttr_u8SmartSpeed(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SMART_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetSmartExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSmartExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [1, 0xFF]
	attr.u8SmartSpeed = pick_diff_u8(attr.u8SmartSpeed, 1, 0xFF);
	ret = CVI_ISP_SetSmartExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u8SmartSpeed=%d failed\n", (int)attr.u8SmartSpeed);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetSmartExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.u8SmartSpeed != attr.u8SmartSpeed) {
		TEST_FAIL("u8SmartSpeed readback %d != %d\n", (int)attr2.u8SmartSpeed,
			  (int)attr.u8SmartSpeed);
		CVI_ISP_SetSmartExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetSmartExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_SmartExposureAttr_u8SmartSpeed(void)
{
	reg_api_test_fn(test_AE_SmartExposureAttr_u8SmartSpeed);
}

static int test_AE_SmartExposureAttr_u8Weight(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SMART_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetSmartExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSmartExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [0, 0x64]
	attr.u8Weight = pick_diff_u8(attr.u8Weight, 0, 0x64);
	ret = CVI_ISP_SetSmartExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u8Weight=%d failed\n", (int)attr.u8Weight);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetSmartExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.u8Weight != attr.u8Weight) {
		TEST_FAIL("u8Weight readback %d != %d\n", (int)attr2.u8Weight, (int)attr.u8Weight);
		CVI_ISP_SetSmartExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetSmartExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_SmartExposureAttr_u8Weight(void)
{
	reg_api_test_fn(test_AE_SmartExposureAttr_u8Weight);
}

static int test_AE_SmartExposureAttr_u8NarrowRatio(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_SMART_EXPOSURE_ATTR_S attr, orig, attr2;

	ret = CVI_ISP_GetSmartExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetSmartExposureAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [0, 0x64]
	attr.u8NarrowRatio = pick_diff_u8(attr.u8NarrowRatio, 0, 0x64);
	ret = CVI_ISP_SetSmartExposureAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set u8NarrowRatio=%d failed\n", (int)attr.u8NarrowRatio);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetSmartExposureAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.u8NarrowRatio != attr.u8NarrowRatio) {
		TEST_FAIL("u8NarrowRatio readback %d != %d\n", (int)attr2.u8NarrowRatio,
			  (int)attr.u8NarrowRatio);
		CVI_ISP_SetSmartExposureAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetSmartExposureAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_SmartExposureAttr_u8NarrowRatio(void)
{
	reg_api_test_fn(test_AE_SmartExposureAttr_u8NarrowRatio);
}

/* -------------------- CVI_ISP_Set/GetAEStatisticsConfig -------------------- */

static int test_AE_AEStatisticsConfig_bHisStatisticsEnable(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_AE_STATISTICS_CFG_S attr, orig, attr2;

	ret = CVI_ISP_GetAEStatisticsConfig(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetAEStatisticsConfig failed\n");
		return ret;
	}
	orig = attr;
	// modify field within {0,1}
	attr.bHisStatisticsEnable = !attr.bHisStatisticsEnable;
	ret = CVI_ISP_SetAEStatisticsConfig(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set bHisStatisticsEnable=%d failed\n", (int)attr.bHisStatisticsEnable);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetAEStatisticsConfig(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.bHisStatisticsEnable != attr.bHisStatisticsEnable) {
		TEST_FAIL("bHisStatisticsEnable readback %d != %d\n", (int)attr2.bHisStatisticsEnable,
			  (int)attr.bHisStatisticsEnable);
		CVI_ISP_SetAEStatisticsConfig(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetAEStatisticsConfig(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_AEStatisticsConfig_bHisStatisticsEnable(void)
{
	reg_api_test_fn(test_AE_AEStatisticsConfig_bHisStatisticsEnable);
}

static int test_AE_AEStatisticsConfig_stCrop(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_AE_STATISTICS_CFG_S attr, orig, attr2;

	ret = CVI_ISP_GetAEStatisticsConfig(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetAEStatisticsConfig failed\n");
		return ret;
	}
	orig = attr;
	// modify stCrop[0] fields within documented ranges
	attr.stCrop[0].bEnable = !attr.stCrop[0].bEnable;
	attr.stCrop[0].u16X = pick_diff_u16(attr.stCrop[0].u16X, 0, 0x1FFF);
	attr.stCrop[0].u16Y = pick_diff_u16(attr.stCrop[0].u16Y, 0, 0x1FFF);
	attr.stCrop[0].u16W = pick_diff_u16(attr.stCrop[0].u16W, 0, 0x1FFF);
	attr.stCrop[0].u16H = pick_diff_u16(attr.stCrop[0].u16H, 0, 0x1FFF);
	ret = CVI_ISP_SetAEStatisticsConfig(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set stCrop failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetAEStatisticsConfig(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.stCrop[0].bEnable != attr.stCrop[0].bEnable ||
	    attr2.stCrop[0].u16X != attr.stCrop[0].u16X || attr2.stCrop[0].u16Y != attr.stCrop[0].u16Y ||
	    attr2.stCrop[0].u16W != attr.stCrop[0].u16W || attr2.stCrop[0].u16H != attr.stCrop[0].u16H) {
		TEST_FAIL("stCrop readback mismatch\n");
		CVI_ISP_SetAEStatisticsConfig(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetAEStatisticsConfig(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_AEStatisticsConfig_stCrop(void)
{
	reg_api_test_fn(test_AE_AEStatisticsConfig_stCrop);
}

static int test_AE_AEStatisticsConfig_fast2A(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_AE_STATISTICS_CFG_S attr, orig, attr2;

	ret = CVI_ISP_GetAEStatisticsConfig(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetAEStatisticsConfig failed\n");
		return ret;
	}
	orig = attr;
	// modify fast2A fields within documented ranges
	attr.fast2A_ena = !attr.fast2A_ena;
	attr.fast2A_awb_top = pick_diff_u16(attr.fast2A_awb_top, 0, 0xFFF);
	attr.fast2A_awb_bot = pick_diff_u16(attr.fast2A_awb_bot, 0, 0xFFF);
	ret = CVI_ISP_SetAEStatisticsConfig(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set fast2A params failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetAEStatisticsConfig(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.fast2A_ena != attr.fast2A_ena || attr2.fast2A_awb_top != attr.fast2A_awb_top ||
	    attr2.fast2A_awb_bot != attr.fast2A_awb_bot) {
		TEST_FAIL("fast2A readback mismatch\n");
		CVI_ISP_SetAEStatisticsConfig(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetAEStatisticsConfig(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_AEStatisticsConfig_fast2A(void)
{
	reg_api_test_fn(test_AE_AEStatisticsConfig_fast2A);
}

static int test_AE_AEStatisticsConfig_over_exp_thr(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_AE_STATISTICS_CFG_S attr, orig, attr2;

	ret = CVI_ISP_GetAEStatisticsConfig(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetAEStatisticsConfig failed\n");
		return ret;
	}
	orig = attr;
	// modify field within [0, 0x3FF]
	attr.over_exp_thr = pick_diff_u16(attr.over_exp_thr, 0, 0x3FF);
	ret = CVI_ISP_SetAEStatisticsConfig(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set over_exp_thr=%d failed\n", (int)attr.over_exp_thr);
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetAEStatisticsConfig(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.over_exp_thr != attr.over_exp_thr) {
		TEST_FAIL("over_exp_thr readback %d != %d\n", (int)attr2.over_exp_thr,
			  (int)attr.over_exp_thr);
		CVI_ISP_SetAEStatisticsConfig(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetAEStatisticsConfig(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_AEStatisticsConfig_over_exp_thr(void)
{
	reg_api_test_fn(test_AE_AEStatisticsConfig_over_exp_thr);
}

static int test_AE_AEStatisticsConfig_au8Weight(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_AE_STATISTICS_CFG_S attr, orig, attr2;

	ret = CVI_ISP_GetAEStatisticsConfig(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetAEStatisticsConfig failed\n");
		return ret;
	}
	orig = attr;
	// modify all zone weights within [0, 0xF]
	for (int i = 0; i < AE_WEIGHT_ZONE_ROW; i++) {
		for (int j = 0; j < AE_WEIGHT_ZONE_COLUMN; j++) {
			attr.au8Weight[i][j] = (CVI_U8)rand_range(0, 0xF);
		}
	}
	ret = CVI_ISP_SetAEStatisticsConfig(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("set au8Weight failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after set failed\n");
		return ret;
	}
	ret = CVI_ISP_GetAEStatisticsConfig(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (memcmp(attr2.au8Weight, attr.au8Weight, sizeof(attr.au8Weight)) != 0) {
		TEST_FAIL("au8Weight readback mismatch\n");
		CVI_ISP_SetAEStatisticsConfig(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetAEStatisticsConfig(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	ret = ae_wait_vd(ViPipe);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("VD wait after restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_AEStatisticsConfig_au8Weight(void)
{
	reg_api_test_fn(test_AE_AEStatisticsConfig_au8Weight);
}

/* -------------------- CVI_ISP_Set/GetFastConvergeAttr -------------------- */

static int test_AE_FastConvergeAttr(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_AE_BOOT_FAST_CONVERGE_S attr, orig, attr2;

	ret = CVI_ISP_GetFastConvergeAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetFastConvergeAttr failed\n");
		return ret;
	}
	orig = attr;
	// modify fields; takes effect only on next fast boot, restored right after
	attr.bEnable = !attr.bEnable;
	attr.availableNode = pick_diff_u8(attr.availableNode, 0, FAST_CONVERGE_NODES);
	for (int i = 0; i < FAST_CONVERGE_NODES; i++) {
		attr.firstFrLuma[i] = (CVI_S16)rand_range(-4096, 4096);
		attr.targetBv[i] = (CVI_S16)rand_range(-4096, 4096);
	}
	ret = CVI_ISP_SetFastConvergeAttr(ViPipe, &attr);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_SetFastConvergeAttr failed\n");
		return ret;
	}
	ret = CVI_ISP_GetFastConvergeAttr(ViPipe, &attr2);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("get after set failed\n");
		return ret;
	}
	if (attr2.bEnable != attr.bEnable || attr2.availableNode != attr.availableNode ||
	    memcmp(attr2.firstFrLuma, attr.firstFrLuma, sizeof(attr.firstFrLuma)) != 0 ||
	    memcmp(attr2.targetBv, attr.targetBv, sizeof(attr.targetBv)) != 0) {
		TEST_FAIL("fast converge readback mismatch\n");
		CVI_ISP_SetFastConvergeAttr(ViPipe, &orig);
		return CVI_FAILURE;
	}
	ret = CVI_ISP_SetFastConvergeAttr(ViPipe, &orig);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("restore failed\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_FastConvergeAttr(void)
{
	reg_api_test_fn(test_AE_FastConvergeAttr);
}

/*
 * AE_GetFastConvCalibrationInfo returns FAILURE while AE has not converged
 * (bIsStable != 1). Gate the expectation on CVI_ISP_GetAEConvergeInfo.
 */
static int test_AE_GetFastConvCalibrationInfo(VI_PIPE ViPipe)
{
	CVI_S32 ret = CVI_SUCCESS;
	ISP_AE_CONVERGE_INFO_S conv;
	CVI_S16 s16FirstFrameLuma = 0;
	CVI_S16 s16StableBv = 0;

	memset(&conv, 0, sizeof(conv));
	ret = CVI_ISP_GetAEConvergeInfo(ViPipe, &conv);
	if (ret != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetAEConvergeInfo failed\n");
		return ret;
	}
	ret = CVI_ISP_GetFastConvCalibrationInfo(ViPipe, &s16FirstFrameLuma, &s16StableBv);
	if (ret != CVI_SUCCESS) {
		if (conv.bIsStable != CVI_TRUE) {
			printf("[ISP_TEST_SKIP] %s: AE not stable yet, calib info not ready\n",
			       __func__);
			return CVI_SUCCESS;
		}
		TEST_FAIL("CVI_ISP_GetFastConvCalibrationInfo failed though AE is stable\n");
		return ret;
	}
	return CVI_SUCCESS;
}

static void __attribute__((constructor)) reg_test_AE_GetFastConvCalibrationInfo(void)
{
	reg_api_test_fn(test_AE_GetFastConvCalibrationInfo);
}
