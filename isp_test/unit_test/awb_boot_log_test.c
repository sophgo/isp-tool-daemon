#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include "cvi_isp.h"
#include "cvi_awb.h"
#include "cvi_bin.h"
#include "isp_internal_api.h"

// algo/awb/awbalgo.h debug channel values (internal header not on public include path)
#define AWB_DEBUG_DUMP_BOOT_LOG			(6)
#define AWB_DEBUG_DISABLE_LOG_TO_FILE		(201)

#define TEST_FAIL(fmt, arg...) printf("[ISP_TEST_FAIL] %s,%d: " fmt, __func__, __LINE__, ##arg)
#define TEST_INFO(fmt, arg...) printf("[AWBBOOT] " fmt, ##arg)

#define SNAP_BUF_SIZE		AWB_SNAP_LOG_BUFF_SIZE
#define BOOT_RECORD_CAP		(40 * 1024)
#define MIN_FRAME_LINES		30
#define FILL_POLL_MAX		12
#define FILL_POLL_FRAMES	30

typedef struct {
	const char *name;
	int pass;
} SUBTEST_RESULT;

static int g_total;
static int g_passed;

static void subtest_done(SUBTEST_RESULT *r, int pass)
{
	r->pass = pass;
	g_total++;
	if (pass)
		g_passed++;
	printf("[AWBBOOT] %-42s : %s\n", r->name, pass ? "PASS" : "FAIL");
}

static int wait_frames(VI_PIPE pipe, int n)
{
	int i;

	for (i = 0; i < n; i++) {
		if (CVI_ISP_GetVDTimeOut(pipe, ISP_VD_BE_END, 200) != CVI_SUCCESS)
			return -1;
	}
	return 0;
}

static int set_debug_mode(VI_PIPE pipe, ISP_WB_ATTR_S *attr, CVI_U8 mode)
{
	attr->u8DebugMode = mode;
	return CVI_ISP_SetWBAttr(pipe, attr);
}

static int parse_frame_lines(const char *buf, unsigned int *first_fid, unsigned int *last_fid, int *cnt)
{
	const char *p = buf;
	int count = 0;
	unsigned int fid;
	int ascending = 1;

	*first_fid = 0;
	*last_fid = 0;
	while ((p = strstr(p, " fid:")) != NULL) {
		if (sscanf(p + 5, "%u", &fid) == 1) {
			if (count == 0)
				*first_fid = fid;
			else if (fid <= *last_fid)
				ascending = 0;
			*last_fid = fid;
			count++;
		}
		p += 5;
	}
	*cnt = count;
	return (count > 0) ? ascending : 0;
}

static unsigned int snap_line_len(const char *buf)
{
	const char *nl = strchr(buf, '\n');

	return nl ? (unsigned int)(nl - buf + 1) : (unsigned int)strlen(buf);
}

static int test_wb_attr_api(VI_PIPE pipe, ISP_WB_ATTR_S *orig)
{
	if (CVI_ISP_GetWBAttr(pipe, orig) != CVI_SUCCESS) {
		TEST_FAIL("CVI_ISP_GetWBAttr failed\n");
		return 0;
	}
	if (orig->u8AWBRunInterval == 0) {
		TEST_FAIL("bad u8AWBRunInterval %u\n", orig->u8AWBRunInterval);
		return 0;
	}
	return 1;
}

static int test_reset_stale_log(VI_PIPE pipe, ISP_WB_ATTR_S *attr)
{
	if (set_debug_mode(pipe, attr, AWB_DEBUG_DISABLE_LOG_TO_FILE) != CVI_SUCCESS) {
		TEST_FAIL("set debug 201 (destroy stale log) failed\n");
		return 0;
	}
	wait_frames(pipe, 2);
	if (set_debug_mode(pipe, attr, 0) != CVI_SUCCESS) {
		TEST_FAIL("set debug 0 failed\n");
		return 0;
	}
	wait_frames(pipe, 2);
	if (CVI_ISP_GetWBAttr(pipe, attr) != CVI_SUCCESS || attr->u8DebugMode != 0) {
		TEST_FAIL("debug mode not cleared after reset\n");
		return 0;
	}
	return 1;
}

static int test_arm_boot_log(VI_PIPE pipe, ISP_WB_ATTR_S *attr)
{
	if (set_debug_mode(pipe, attr, AWB_DEBUG_DUMP_BOOT_LOG) != CVI_SUCCESS) {
		TEST_FAIL("set debug 6 (arm boot log) failed\n");
		return 0;
	}
	wait_frames(pipe, 2);
	return 1;
}

static int test_snap_content(char *snap, unsigned int snap_len)
{
	unsigned int first_fid = 0, last_fid = 0;
	int cnt = 0;
	int ascending;

	if (strstr(snap, "AWB v:") == NULL) {
		TEST_FAIL("log header version line missing\n");
		return 0;
	}
	if (strstr(snap, "AWB [h:m:s.ms] pN fid run skip int") == NULL) {
		TEST_FAIL("log table header missing\n");
		return 0;
	}
	ascending = parse_frame_lines(snap, &first_fid, &last_fid, &cnt);
	if (cnt < MIN_FRAME_LINES) {
		TEST_FAIL("frame lines %d < %d\n", cnt, MIN_FRAME_LINES);
		return 0;
	}
	if (!ascending) {
		TEST_FAIL("frame id not ascending (first %u last %u)\n", first_fid, last_fid);
		return 0;
	}
	if (strstr(snap, "CAL") == NULL || strstr(snap, "RHL:") == NULL) {
		TEST_FAIL("param snapshot section missing\n");
		return 0;
	}
	if (snap_len == 0 || snap_len > SNAP_BUF_SIZE) {
		TEST_FAIL("snap len %u out of range\n", snap_len);
		return 0;
	}
	TEST_INFO("boot log ok: %d lines, fid %u->%u, len %u\n", cnt, first_fid, last_fid, snap_len);
	return 1;
}

static int test_export_pqbin(VI_PIPE pipe, CVI_U8 **pbuf, CVI_U32 *plen)
{
	CVI_U32 len;
	CVI_U8 *buf;
	char path[128];
	FILE *fp;

	len = CVI_BIN_GetSingleISPBinLen(CVI_BIN_ID_ISP0 + pipe);
	if (len == 0) {
		TEST_FAIL("CVI_BIN_GetSingleISPBinLen == 0\n");
		return 0;
	}
	buf = calloc(1, len);
	if (buf == NULL) {
		TEST_FAIL("alloc %u fail\n", len);
		return 0;
	}
	if (CVI_BIN_ExportSingleISPBinData(CVI_BIN_ID_ISP0 + pipe, buf, len) != CVI_SUCCESS) {
		TEST_FAIL("CVI_BIN_ExportSingleISPBinData failed\n");
		free(buf);
		return 0;
	}
	snprintf(path, sizeof(path), "/tmp/awbboot_pq_pipe%d.bin", pipe);
	fp = fopen(path, "wb");
	if (fp != NULL) {
		fwrite(buf, 1, len, fp);
		fclose(fp);
	}
	if (wait_frames(pipe, 1) != 0) {
		TEST_FAIL("no VD after export\n");
		free(buf);
		return 0;
	}
	*pbuf = buf;
	*plen = len;
	TEST_INFO("export ok: %u bytes -> %s\n", len, path);
	return 1;
}

static int test_import_pqbin_delivers_debug6(VI_PIPE pipe, ISP_WB_ATTR_S *attr,
						CVI_U8 *binbuf, CVI_U32 binlen)
{
	if (set_debug_mode(pipe, attr, 0) != CVI_SUCCESS) {
		TEST_FAIL("clear debug failed\n");
		return 0;
	}
	wait_frames(pipe, 2);
	if (CVI_ISP_GetWBAttr(pipe, attr) != CVI_SUCCESS || attr->u8DebugMode != 0) {
		TEST_FAIL("debug mode not cleared before import\n");
		return 0;
	}
	if (CVI_BIN_LoadParamFromBinEx(CVI_BIN_ID_ISP0 + pipe, binbuf, binlen) != CVI_SUCCESS) {
		TEST_FAIL("CVI_BIN_LoadParamFromBinEx failed\n");
		return 0;
	}
	wait_frames(pipe, 2);
	if (CVI_ISP_GetWBAttr(pipe, attr) != CVI_SUCCESS) {
		TEST_FAIL("GetWBAttr after import failed\n");
		return 0;
	}
	if (attr->u8DebugMode != AWB_DEBUG_DUMP_BOOT_LOG) {
		TEST_FAIL("pqbin import did not deliver debug 6 (got %u)\n", attr->u8DebugMode);
		return 0;
	}
	return 1;
}

static int test_boot_no_overwrite(char *snap1, unsigned int len1, char *snap2, unsigned int len2)
{
	unsigned int line1;

	if (len2 < len1) {
		TEST_FAIL("snapshot shrank (%u -> %u)\n", len1, len2);
		return 0;
	}
	line1 = snap_line_len(snap1);
	if (strncmp(snap1, snap2, line1) != 0) {
		TEST_FAIL("first log line overwritten (BOOT must not wrap)\n");
		return 0;
	}
	return 1;
}

static int test_fill_and_stop(VI_PIPE pipe, char *snap, unsigned int *plen)
{
	unsigned int prev = *plen;
	unsigned int cur = *plen;
	int i;
	int stopped = 0;

	for (i = 0; i < FILL_POLL_MAX; i++) {
		wait_frames(pipe, FILL_POLL_FRAMES);
		memset(snap, 0, SNAP_BUF_SIZE);
		CVI_ISP_GetAWBSnapLogBuf(pipe, (CVI_U8 *)snap, SNAP_BUF_SIZE);
		cur = strnlen(snap, SNAP_BUF_SIZE);
		if (cur == prev) {
			stopped = 1;
			break;
		}
		prev = cur;
	}
	*plen = cur;
	if (!stopped) {
		TEST_FAIL("log still growing after %d polls (BOOT must stop at cap)\n", FILL_POLL_MAX);
		return 0;
	}
	if (cur > SNAP_BUF_SIZE) {
		TEST_FAIL("snap len %u over cap\n", cur);
		return 0;
	}
	TEST_INFO("boot log full and stopped at %u bytes (cap %u)\n", cur, SNAP_BUF_SIZE);
	return 1;
}

static unsigned int take_snapshot(VI_PIPE pipe, char *snap)
{
	memset(snap, 0, SNAP_BUF_SIZE);
	CVI_ISP_GetAWBSnapLogBuf(pipe, (CVI_U8 *)snap, SNAP_BUF_SIZE);
	return strnlen(snap, SNAP_BUF_SIZE);
}

static int dump_only_mode(VI_PIPE pipe)
{
	char path[128];
	FILE *f;
	char *snap = calloc(1, SNAP_BUF_SIZE);
	unsigned int len;

	if (snap == NULL)
		return -1;
	len = take_snapshot(pipe, snap);
	snprintf(path, sizeof(path), "/tmp/awblog_dump_pipe%d.txt", pipe);
	f = fopen(path, "w");
	if (f == NULL) {
		free(snap);
		return -1;
	}
	fwrite(snap, 1, len, f);
	fclose(f);
	printf("[AWBBOOT] dump-only: %u bytes -> %s\n", len, path);
	free(snap);
	return 0;
}

int awb_boot_log_test_main(VI_PIPE ViPipe)
{
	SUBTEST_RESULT r;
	ISP_WB_ATTR_S orig_attr;
	ISP_WB_ATTR_S attr;
	CVI_U8 *binbuf = NULL;
	CVI_U32 binlen = 0;
	char *snap1 = calloc(1, SNAP_BUF_SIZE);
	char *snap2 = calloc(1, SNAP_BUF_SIZE);
	unsigned int len1 = 0, len2 = 0;
	int ret_all = 0;

	if (getenv("AWB_BOOT_LOG_DUMP_ONLY") != NULL)
		return dump_only_mode(ViPipe);

	g_total = 0;
	g_passed = 0;

	TEST_INFO("===== AWB boot log + pqbin import/export test [pipe %d] =====\n", ViPipe);

	if (snap1 == NULL || snap2 == NULL) {
		TEST_FAIL("snapshot buffer alloc fail\n");
		free(snap1);
		free(snap2);
		return -1;
	}

	r.name = "wb attr get/set api";
	subtest_done(&r, test_wb_attr_api(ViPipe, &orig_attr));
	ret_all |= !r.pass;
	memcpy(&attr, &orig_attr, sizeof(attr));

	r.name = "reset stale log state (debug 201)";
	subtest_done(&r, test_reset_stale_log(ViPipe, &attr));
	ret_all |= !r.pass;

	r.name = "arm boot log recording (debug 6)";
	subtest_done(&r, test_arm_boot_log(ViPipe, &attr));
	ret_all |= !r.pass;

	wait_frames(ViPipe, 45);

	len1 = take_snapshot(ViPipe, snap1);
	r.name = "boot log content (header/frames/snap)";
	subtest_done(&r, test_snap_content(snap1, len1));
	ret_all |= !r.pass;

	r.name = "pqbin export (carries debug 6)";
	subtest_done(&r, test_export_pqbin(ViPipe, &binbuf, &binlen));
	ret_all |= !r.pass;

	r.name = "pqbin import delivers debug 6";
	subtest_done(&r, binbuf ? test_import_pqbin_delivers_debug6(ViPipe, &attr, binbuf, binlen) : 0);
	ret_all |= !r.pass;

	wait_frames(ViPipe, 15);
	len2 = take_snapshot(ViPipe, snap2);
	r.name = "boot log no-overwrite + growth";
	subtest_done(&r, test_boot_no_overwrite(snap1, len1, snap2, len2));
	ret_all |= !r.pass;

	r.name = "boot log fill then stop";
	subtest_done(&r, test_fill_and_stop(ViPipe, snap2, &len2));
	ret_all |= !r.pass;

	memcpy(&attr, &orig_attr, sizeof(attr));
	attr.u8DebugMode = 0;
	CVI_ISP_SetWBAttr(ViPipe, &attr);

	free(binbuf);
	free(snap1);
	free(snap2);

	printf("ISP_AWB_BOOT_LOG_TEST finished[pipe: %d], total: %d, passed: %d, failed: %d, passed_ratio: %.2f%%\n",
		ViPipe, g_total, g_passed, g_total - g_passed,
		g_total ? 100.0 * g_passed / g_total : 0.0);
	if (ret_all == 0)
		printf("ISP_AWB_BOOT_LOG_TEST pipe %d success!\n", ViPipe);
	else
		printf("ISP_AWB_BOOT_LOG_TEST pipe %d fail!\n", ViPipe);

	return ret_all;
}
