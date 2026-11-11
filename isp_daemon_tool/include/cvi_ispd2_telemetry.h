/*
 * Copyright (C) Cvitek Co., Ltd. 2019-2022. All rights reserved.
 *
 * File Name: cvi_ispd2_telemetry.h
 * Description: ISP telemetry TCP protocol definitions (wire mirror) + lib API.
 *		Spec: mars3-dev-doc/isp-telemetry-udp.md (v8.0, protocol v5).
 *
 *		Wire rules (see spec §3):
 *		- little-endian; register raw values, no scaling;
 *		- 22B header, single-fragment packets only (frag_cnt=1/frag_idx=0);
 *		- payload wire layout is strictly packed: no alignment padding
 *		  between fields (structs carrying it are __attribute__((packed)),
 *		  so sizeof == wire size); sender memsets the whole struct first,
 *		  so any rsv bytes are zero-filled;
 *		- module disabled -> header-only packet with payload_len=0;
 *		- v5: hist-carrying payloads -- flags bit1
 *		  ISPD2_TLM_FLAG_HIST_VALID is set only when the hist
 *		  segment passed the pattern guard; bit1=0 means the
 *		  segment is zero-filled (DMA-unwritten pattern data);
 *		- TCP stream framing (v6): each message is preceded by a u32
 *		  little-endian length equal to ISPD2_TLM_HDR_SIZE + payload_len,
 *		  i.e. one frame = [u32 LE len][complete message];
 *		- v8: ANNOUNCE.soc_series identifies the SoC series
 *		  (0=legacy 1=cv184x 2=cv190x); the 60B payload size and
 *		  protocol version 5 are unchanged (reserved byte split);
 *		- (cv190x tree) DRC/GAMMA payload sizes follow the cv190x
 *		  hardware layout, not the cv184x sizes (see the payload
 *		  struct comments); ANNOUNCE.soc_series discriminates
 */

#ifndef _CVI_ISPD2_TELEMETRY_H_
#define _CVI_ISPD2_TELEMETRY_H_

#include <stdint.h>

#include "cvi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

// -----------------------------------------------------------------------------
// Protocol constants
// -----------------------------------------------------------------------------
#define ISPD2_TLM_MAGIC			(0x44505349U)	// "ISPD" little-endian
#define ISPD2_TLM_VERSION		(5U)
#define ISPD2_TLM_HDR_SIZE		(22U)

// SoC series id carried in ANNOUNCE.soc_series (v8). Non-breaking wire
// change: old daemons memset the whole struct, so their reserved bytes
// read as 0 == LEGACY (clients treat legacy as the cv184x wire layout)
#define ISPD2_TLM_SOC_LEGACY		(0U)	// old daemons, reserved zeroed
#define ISPD2_TLM_SOC_CV184X		(1U)
#define ISPD2_TLM_SOC_CV190X		(2U)

// Compile-time series selection for this daemon build. cv184x tree defaults
// to CV184X; the cv190x (phobos3) port flips the default to CV190X (same
// effect as -DISPD2_TLM_SERIES=2 in the Makefile).
#ifndef ISPD2_TLM_SERIES
#define ISPD2_TLM_SERIES		ISPD2_TLM_SOC_CV190X
#endif

#define ISPD2_TLM_MAX_PAYLOAD		(65536U)	// send-path buffer quota
							// only; the u16 payload_len
							// wire field actually caps
							// at 65535 (widened from
							// 2048 for MOTION_MAP 0xA0
							// (1080p frame = 32408B;
							// TCP stream, no MTU
							// constraint; client
							// accepts frames <= 70000)

// msg_type
#define ISPD2_TLM_MSG_ANNOUNCE		(0x00U)		// 1Hz heartbeat + meta
#define ISPD2_TLM_MSG_AE_HIST		(0x10U)		// AE hist, G channel only
#define ISPD2_TLM_MSG_DRC		(0x20U)
#define ISPD2_TLM_MSG_GAMMA		(0x30U)
#define ISPD2_TLM_MSG_DCI		(0x40U)
#define ISPD2_TLM_MSG_YCUR		(0x50U)
#define ISPD2_TLM_MSG_LSC_HIST		(0x60U)		// LSC stats hist, R/G/B
#define ISPD2_TLM_MSG_FSHDR_RSV		(0x70U)		// reserved, not sent this version
#define ISPD2_TLM_MSG_AWB		(0x80U)		// always-on OSD fallback info
#define ISPD2_TLM_MSG_AE		(0x90U)		// always-on OSD fallback info
#define ISPD2_TLM_MSG_MOTION_MAP	(0xA0U)		// TNR MO motion map (MoMp),
							// every-frame, page-gated

// header flags
#define ISPD2_TLM_FLAG_ENABLED		(0x01U)		// bit0: module enabled
#define ISPD2_TLM_FLAG_HIST_VALID	(0x02U)		// bit1: hist segment carries
						// real statistics (v5 pattern
						// guard passed); 0 = hist
						// segment zero-filled, do
						// not draw it

// v5 hist pattern-guard threshold (sender-side detection only, not a
// wire field): real per-bin pixel statistics u32 values stay far below
// this; DMA-unwritten pattern memory (observed raw u32 ~0xB1ACB1AC) and
// dirty data sit at/above it
#define ISPD2_TLM_HIST_PATTERN_TH	(0x80000000U)

// defaults
#define ISPD2_TLM_TCP_PORT		(5569U)		// default telemetry TCP server port
							// (v7: listen port is configurable via
							// SetTelemetryAttr "Port"; this value
							// applies when the param is absent;
							// 5566 = daemon JSON-RPC, 5567 = raw
							// dump, 5568 = clog all taken)
#define ISPD2_TLM_MAX_CLIENTS		(8U)		// concurrent TCP clients supported
#define ISPD2_TLM_DEFAULT_INTERVAL_FRAMES	(15U)
#define ISPD2_TLM_ANNOUNCE_PERIOD_MS	(1000U)

// -----------------------------------------------------------------------------
// 22B packet header (packed: sizeof == ISPD2_TLM_HDR_SIZE)
// -----------------------------------------------------------------------------
typedef struct _ispd2_tlm_hdr {
	uint32_t	magic;			// ISPD2_TLM_MAGIC
	uint8_t		version;		// ISPD2_TLM_VERSION
	uint8_t		msg_type;
	uint8_t		pipe;
	uint8_t		flags;			// bit0: enabled, bit1: hist valid (v5)
	uint32_t	frame_id;		// CVI_ISP_GetFrameID()
	uint32_t	timestamp_ms;		// mono ms since telemetry start
	uint8_t		frag_cnt;		// always 1 (this version)
	uint8_t		frag_idx;		// always 0 (this version)
	uint16_t	seq;			// per-sender monotonic
	uint16_t	payload_len;		// 0 when module disabled
} __attribute__((packed)) ispd2_tlm_hdr_t;	// sizeof == ISPD2_TLM_HDR_SIZE (22)

// -----------------------------------------------------------------------------
// Payloads (packed wire layout: no alignment padding, sizeof == wire size)
// -----------------------------------------------------------------------------

// msg 0x00 ANNOUNCE (60B, packed; field order carries no natural padding,
// so sizeof is unchanged by the attribute -- wire layout only, see §3).
// v8: soc_series (former reserved[0]) identifies the SoC series while
// reserved[1] stays zero, so the size and all field offsets are unchanged
typedef struct _ispd2_tlm_announce {
	uint32_t	interval_frames;	// current sampling interval
	uint32_t	tcp_port;		// telemetry TCP server port (actual
						// listen port, v7)
	uint8_t		pipes_bitmask;		// bitN set: pipe N streaming
	uint8_t		mode;			// reserved, always 0 (v2 mode retired)
	uint8_t		soc_series;		// SoC series id (v8): 0=legacy
						// 1=cv184x 2=cv190x
	uint8_t		reserved;		// zero
	char		host_ip[16];		// dotted, NUL-padded
	char		fw_version[32];		// NUL-padded
} __attribute__((packed)) ispd2_tlm_announce_t;	// sizeof == 60

// msg 0x10 MOD_AE_HIST (512B): u32 -> u16 saturated (v5: pattern-guarded,
// see ISPD2_TLM_FLAG_HIST_VALID)
typedef struct _ispd2_tlm_ae_hist {
	uint16_t	g_hist[256];
} ispd2_tlm_ae_hist_t;

// msg 0x20 MOD_DRC (125B, packed), spec §3.3; v5 carries no drc_hist:
// cv190x has no DRC histogram hardware, so the wire carries no hist
// section. Wire layout mirrors the cv190x hardware reality (this is the cv190x
// tree; the cv184x platform code does not live in this directory):
// point counts equal the cv190x DRC LUT sizes and each u16 container
// carries the hardware raw value at its native width. The cv184x wire
// layout differs (65/17/9/17 points, wider value ranges); clients
// select the layout per ANNOUNCE.soc_series.
typedef struct _ispd2_tlm_drc {
	uint8_t		auto_mode;		// 0=manual 1=auto (DRCAttr OpMode)
	uint32_t	strength;		// reg drc_strength raw value
	uint16_t	outbld_l[33];		// 8-bit values 0..255
	uint16_t	outbld_r[9];		// 8-bit values 0..255
	uint16_t	yv_bld[9];		// 4-bit values 0..15
	uint16_t	input_bld[9];		// 6-bit values 0..63
} __attribute__((packed)) ispd2_tlm_drc_t;	// sizeof == 125 (cv190x layout)

// msg 0x30 MOD_GAMMA (164B): rgb share one table; 82 entries = the cv190x
// hardware lut size (cv184x: 256), u16 raw values 0..1023 (10-bit)
typedef struct _ispd2_tlm_gamma {
	uint16_t	lut[82];
} ispd2_tlm_gamma_t;

// msg 0x40 MOD_DCI (1024B)
typedef struct _ispd2_tlm_dci {
	uint16_t	out_lut[256];		// dci_ygamma_curve, y 0..255
	uint16_t	dci_hist[256];		// u32 -> u16 saturated (v5: pattern-guarded)
} ispd2_tlm_dci_t;

// msg 0x50 MOD_YCUR (66B)
typedef struct _ispd2_tlm_ycur {
	uint8_t		iir_lut[64];		// x = 6-bit Y bin 0..63
	uint16_t	last_point;		// y up to 256
} ispd2_tlm_ycur_t;

// msg 0x60 MOD_LSC_HIST (1536B): QueryInnerStateInfo().rlsc_hist_r/g/b,
// u32 -> u16 saturated (v5: pattern-guarded per channel; bit1 set only
// when all three channels pass); stats block always on -> enabled is always 1
typedef struct _ispd2_tlm_lsc_hist {
	uint16_t	rlsc_hist[3][256];	// [0]=R [1]=G [2]=B
} ispd2_tlm_lsc_hist_t;

// msg 0x80 MOD_AWB (10B): R/Gr/Gb/B gains (Q10) + color temp
typedef struct _ispd2_tlm_awb {
	uint16_t	wb_gain[4];
	uint16_t	color_temp;		// Kelvin
} ispd2_tlm_awb_t;

// msg 0x90 MOD_AE (54B, packed), spec §3.4
typedef struct _ispd2_tlm_ae {
	uint32_t	inttime_le;		// LT  u32ExpTime (us)
	uint32_t	inttime_se;		// ST  u32ShortExpTime (us)
	uint32_t	again_le;		// LAG u32AGain (Q10)
	uint32_t	dgain_le;		// LDG u32DGain (Q10)
	uint32_t	ispgain_le;		// LIG u32ISPDGain (Q10)
	uint32_t	again_se;		// SAG u32AGainSF
	uint32_t	dgain_se;		// SDG u32DGainSF
	uint32_t	ispgain_se;		// SIG u32ISPDGainSF
	uint16_t	lum_avg;		// Lum u8AveLum
	int16_t		hist_err;		// HE  s16HistError
	uint16_t	fps_x100;		// FPS u32Fps x100
	uint32_t	iso_le;			// LISO u32ISO
	uint32_t	iso_se;			// SISO u32ISOSF
	uint32_t	wdr_exp_ratio;		// WER u32WDRExpRatio (x64)
	int32_t		light_value_x100;	// LV  fLightValue x100
} __attribute__((packed)) ispd2_tlm_ae_t;	// sizeof == 54 (client wire order)

// msg 0xA0 MOTION_MAP (8B packed header + trailing 2bpp data): TNR MO motion
// map (MoMp), one 4x4-block value per map pixel, from CVI_ISP_GetMmapSts().
// Wire data = header + map_h * stride_2bpp bytes; the flexible data[] member
// is not part of the header wire size (payload_len = 8 + map_h *
// stride_2bpp). The 2bpp data is bounded by the libisp export cap
// CVI_MMAP_STS_DATA_MAX (cvi_isp.h, == VI_MO_SNAPSHOT_MAX / 4); the
// daemon-side send quota ISPD2_TLM_MO_MAP_DATA_MAX
// (cvi_ispd2_telemetry.c) is asserted >= that cap. format 0 value
// semantics: 0 = still, 1 = transition, 2 = motion, 3 = reserved
// (render as motion). Packing: pixel i of a row lives in bits
// [(i % 4) * 2 + 1 : (i % 4) * 2] of data byte i / 4 (LSB-first), rows
// packed independently.
typedef struct _ispd2_tlm_mo_map {
	uint16_t	map_w;		// motion map width, ceil(W/4)
	uint16_t	map_h;		// motion map height, ceil(H/4)
	uint16_t	stride_2bpp;	// packed row bytes = (map_w * 2 + 7) / 8
	uint16_t	format;		// 0 = 2bpp packed MoMp (LSB-first)
	uint8_t		data[];		// map_h * stride_2bpp bytes follow on the wire
} __attribute__((packed)) ispd2_tlm_mo_map_t;	// sizeof(header) == 8

// -----------------------------------------------------------------------------
// Library API (used by daemon core, not a wire interface)
// -----------------------------------------------------------------------------
// Connection management: number of TCP clients currently connected to the
// telemetry server. Written by the telemetry worker only, so callers get a
// diagnostic-grade snapshot without extra locking (accuracy is not guaranteed
// under concurrent connect/close, which is fine for diagnostics/logging).
uint32_t CVI_ISPD2_Telemetry_GetClientCount(void);

// Stop the telemetry worker thread, close the listen socket and every client
// connection (called from isp_daemon2_uninit).
void CVI_ISPD2_Telemetry_Uninit(void);

// RPC-side mo snapshot gate (CVI_ISP_SetMmapSnapEnable RPC handler). The bit
// is OR-ed into the telemetry page switch inside tlm_apply_mo_snap_en(), so a
// snapshot enabled over JSON-RPC is not pushed back off by the worker's 1Hz
// self-heal re-push. Sticky until the RPC turns it off or the daemon exits;
// the setter pushes the resulting effective state to all pipes right away
// (unmapped pipes are rejected API-side and ignored).
void CVI_ISPD2_Telemetry_SetMmapSnapRpcEn(CVI_BOOL bEnable);
CVI_BOOL CVI_ISPD2_Telemetry_GetMmapSnapRpcEn(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif // _CVI_ISPD2_TELEMETRY_H_
