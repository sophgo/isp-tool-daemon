/* SPDX-License-Identifier: GPL-2.0 */
/*
 * awb_sim_adapter.h — cross-file declarations shared between
 * awb_simulation_tool.c and sdk_adapter.c.
 */
#ifndef AWB_SIM_ADAPTER_H
#define AWB_SIM_ADAPTER_H

#include <stdint.h>
#include "cvi_vpss.h"

/* Defined in awb_simulation_tool.c */
CVI_S32 CVI_VPSS_ReleaseChnFrame(VPSS_GRP VpssGrp, VPSS_CHN VpssChn,
				 const VIDEO_FRAME_INFO_S *pstVideoFrame);
CVI_S32 CVI_VPSS_GetChnFrame(VPSS_GRP VpssGrp, VPSS_CHN VpssChn,
			     VIDEO_FRAME_INFO_S *pstFrameInfo, CVI_S32 s32MilliSec);

/*
 * Defined in sdk_adapter.c: inject parsed zone stats into the simulated 3A
 * buffers so that CVI_ISPD2_CBFunc_Get3AStatisticsInfo can return them to
 * the PC tool.
 */
void awbsim_fill_3a_stats(uint8_t frame_num,
			  uint16_t zone_row, uint16_t zone_col,
			  const uint16_t *zone_r0, const uint16_t *zone_g0,
			  const uint16_t *zone_b0,
			  const uint16_t *zone_r1, const uint16_t *zone_g1,
			  const uint16_t *zone_b1);

#endif /* AWB_SIM_ADAPTER_H */
