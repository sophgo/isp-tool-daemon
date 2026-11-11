/*
 * isp_ut.c -- merged VI+ISP unit test: pattern generator mode OR real sensor mode.
 *
 * Config is read from ./isp_ut_cfg.ini (in the program's running directory):
 *
 *   [isp_ut]
 *   input = sensor        # sensor | pattern (default: sensor)
 *   compress_mode = none  # none | tile | line | frame (default: tile)
 *
 * If the config file is missing, defaults are used (sensor mode, tile compress).
 *
 * pattern mode = case_6_patgen_fe_dram_post_dram (no MIPI, no sensor driver)
 * sensor  mode = case_3_fe_dram_post_dram         (MIPI + sensor driver)
 *
 * Both modes:
 *   - sys / vb / vi / vpss init, isp + isp_daemon2 bring-up
 *   - vi_ut-style self-check (select + GetFrame + YUV CRC)
 *   - sit-and-wait for an exit-trigger file (/mnt/data/isp_test_ut_exit)
 */

#include <stdio.h>
#include <string.h>

#include "isp_pattern_isp.h"
#include "isp_ut_impl.h"

int main(int argc, char *argv[])
{
	ISP_UT_CFG_S cfg;

	(void)argc;
	(void)argv;

	/* Parse config from ./isp_ut_cfg.ini (defaults if file missing) */
	ISP_UT_ParseConfig(&cfg);

	/* Pass compress mode to the selected implementation */
	if (cfg.is_sensor_mode) {
		ISP_TEST_PRT("Starting sensor mode\n");
		isp_sensor_impl_set_compress_mode(cfg.compress_mode);
		return isp_sensor_impl_main();
	}

	ISP_TEST_PRT("Starting pattern generator mode\n");
	isp_pattern_impl_set_compress_mode(cfg.compress_mode);
	return isp_pattern_impl_main();
}
