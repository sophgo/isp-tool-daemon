#ifndef _ISP_TEST_UT_ISP_H_
#define _ISP_TEST_UT_ISP_H_

#include <stdio.h>

#include "cvi_type.h"
#include "cvi_isp.h"
#include "cvi_comm_video.h"	/* COMPRESS_MODE_E */

/* isp daemon2 JSON-RPC port (same as vi_ut / CviPQTool default) */
#define JSONRPC_PORT (5566)

/* Config file read from the program's running directory. */
#define ISP_UT_CFG_FILE "isp_ut_cfg.ini"

#ifndef UNUSED
#define UNUSED(x) ((void)(x))
#endif

#define ISP_TEST_PRT(fmt...) printf("[isp_test_ut] " fmt)

/*
 * isp_ut runtime config, parsed from ./isp_ut_cfg.ini:
 *
 *   [isp_ut]
 *   input = sensor        # sensor | pattern (default: sensor)
 *   compress_mode = none  # none | tile | line | frame (default: tile)
 *
 * Fields that are missing or unrecognised fall back to the defaults printed
 * by ISP_UT_ParseConfig().
 */
typedef struct _ISP_UT_CFG_S {
	int is_sensor_mode;		/* 1 = sensor, 0 = pattern */
	COMPRESS_MODE_E compress_mode;
} ISP_UT_CFG_S;

/*
 * Parse ./isp_ut_cfg.ini into *cfg. Returns 0 on success (including the
 * file being absent — defaults are filled in). Prints the resolved values
 * via ISP_TEST_PRT so the user can see what is in effect.
 */
int ISP_UT_ParseConfig(ISP_UT_CFG_S *cfg);

/*
 * patgen ISP config: the ISP pipeline runs without a physical sensor.
 * pub_attr is synthesized from the patgen geometry (W/H/bayer come from
 * /mnt/data/sensor_cfg.ini); 3A tuning updates are suppressed via the
 * tuning_dis sysfs so the patgen output stays deterministic.
 */
typedef struct _ISP_TEST_PATGEN_CONFIG_S {
	int width;
	int height;
	int bayer_id;
	int frame_rate;
	int wdr_mode;	/* WDR_MODE_E — ignored in patgen mode (forced to NONE);
			 * used as-is when is_sensor_mode=1 (isp_sensor).
			 */
	int is_sensor_mode;	/* 1 = real sensor (load pqbin, honor wdr_mode);
				 * 0 = patgen (no pqbin, WDR forced to NONE).
				 */
} ISP_TEST_PATGEN_CONFIG_S;

/*
 * Bring up the ISP pipeline on pipe: 3A register + SetBindAttr + MemInit +
 * SetPubAttr + CVI_ISP_Init, spawn the SCHED_RR CVI_ISP_Run thread, then
 * START ISP DAEMON2 on 127.0.0.1:JSONRPC_PORT.
 */
int ISP_TEST_ISP_Init(VI_PIPE pipe, ISP_TEST_PATGEN_CONFIG_S *patgen_config);

/*
 * Tear down: CVI_ISP_Exit + join the run thread + unregister 3A +
 * isp_daemon2_uninit().
 */
int ISP_TEST_ISP_Exit(VI_PIPE pipe);

#endif /* _ISP_TEST_UT_ISP_H_ */
