
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "cvi_sys.h"
#include "cvi_vo.h"
#include "cvi_vpss.h"
#include "cvi_vi.h"
#include "cvi_isp.h"

#ifndef UNUSED
#define UNUSED(x) ((void)(x))
#endif

// sys module -----------------------------------------------------------------------
CVI_S32 *log_levels;
CVI_CHAR const *log_name[8] = {
	(CVI_CHAR *)"EMG", (CVI_CHAR *)"ALT", (CVI_CHAR *)"CRI", (CVI_CHAR *)"ERR",
	(CVI_CHAR *)"WRN", (CVI_CHAR *)"NOT", (CVI_CHAR *)"INF", (CVI_CHAR *)"DBG"
};

void *CVI_SYS_MmapCache(CVI_U64 u64PhyAddr, CVI_U32 u32Size)
{
	UNUSED(u32Size);
	return (void *) (uintptr_t) u64PhyAddr;
}

CVI_S32 CVI_SYS_IonAlloc_Cached(CVI_U64 *pu64PhyAddr, CVI_VOID **ppVirAddr,
				 const CVI_CHAR *strName, CVI_U32 u32Len)
{
	UNUSED(strName);
	*ppVirAddr = (CVI_VOID *) calloc(1, u32Len);
	*pu64PhyAddr = (CVI_U64) (uintptr_t) *ppVirAddr;
	return CVI_SUCCESS;
}

CVI_S32 CVI_SYS_IonFree(CVI_U64 u64PhyAddr, CVI_VOID *pVirAddr)
{
	UNUSED(u64PhyAddr);
	free(pVirAddr);
	return CVI_SUCCESS;
}

void *CVI_SYS_Mmap(CVI_U64 u64PhyAddr, CVI_U32 u32Size)
{
	UNUSED(u32Size);
	return (void *) (uintptr_t) u64PhyAddr;
}

CVI_S32 CVI_SYS_Munmap(void *pVirAddr, CVI_U32 u32Size)
{
	UNUSED(pVirAddr);
	UNUSED(u32Size);
	return CVI_SUCCESS;
}

CVI_S32 CVI_SYS_IonInvalidateCache(CVI_U64 u64PhyAddr, CVI_VOID *pVirAddr, CVI_U32 u32Len)
{
	UNUSED(u64PhyAddr);
	UNUSED(pVirAddr);
	UNUSED(u32Len);
	return CVI_SUCCESS;
}

CVI_S32 CVI_SYS_IonFlushCache(CVI_U64 u64PhyAddr, CVI_VOID *pVirAddr, CVI_U32 u32Len)
{
	UNUSED(u64PhyAddr);
	UNUSED(pVirAddr);
	UNUSED(u32Len);
	return CVI_SUCCESS;
}

CVI_S32 CVI_SYS_GetBindbySrc(const MMF_CHN_S *pstSrcChn, MMF_BIND_DEST_S *pstBindDest)
{
	UNUSED(pstSrcChn);
	UNUSED(pstBindDest);
	return CVI_SUCCESS;
}

CVI_S32 CVI_SYS_UnBind(const MMF_CHN_S *pstSrcChn, const MMF_CHN_S *pstDestChn)
{
	UNUSED(pstSrcChn);
	UNUSED(pstDestChn);
	return CVI_SUCCESS;
}

CVI_S32 CVI_SYS_Bind(const MMF_CHN_S *pstSrcChn, const MMF_CHN_S *pstDestChn)
{
	UNUSED(pstSrcChn);
	UNUSED(pstDestChn);
	return CVI_SUCCESS;
}

CVI_S32 CVI_SYS_GetVIVPSSMode(VI_VPSS_MODE_S *pstVIVPSSMode)
{
	memset(pstVIVPSSMode, 0, sizeof(VI_VPSS_MODE_S));
	return CVI_SUCCESS;
}

CVI_S32 CVI_SYS_GetChipId(CVI_U32 *pu32ChipId)
{
	*pu32ChipId = 28;
	return CVI_SUCCESS;
}

int devm_open(void)
{
	return 0;
}

void devm_close(int fd)
{
	UNUSED(fd);
}

void *devm_map(int fd, uint64_t phy_addr, size_t len)
{
	UNUSED(fd);
	UNUSED(len);
	return (void *)(uintptr_t)phy_addr;
}

void devm_unmap(void *virt_addr, size_t len)
{
	UNUSED(virt_addr);
	UNUSED(len);
}

// vo module -----------------------------------------------------------------------
static VO_GAMMA_INFO_S g_vo_gamma_info;

CVI_S32 CVI_VO_GetGammaInfo(VO_GAMMA_INFO_S *pinfo)
{
	*pinfo = g_vo_gamma_info;
	return CVI_SUCCESS;
}

CVI_S32 CVI_VO_SetGammaInfo(VO_GAMMA_INFO_S *pinfo)
{
	g_vo_gamma_info = *pinfo;
	return CVI_SUCCESS;
}

// vpss module -----------------------------------------------------------------------
static VPSS_ALL_PROC_AMP_S g_vpss_all_proc_amp;

CVI_S32 CVI_VPSS_GetAllProcAmp(VPSS_ALL_PROC_AMP_S *pstProcAmp)
{
	*pstProcAmp = g_vpss_all_proc_amp;
	return CVI_SUCCESS;
}

CVI_S32 CVI_VPSS_GetGrpProcAmp(VPSS_GRP VpssGrp, PROC_AMP_E type, CVI_S32 *value)
{
	if (VpssGrp < 0 || VpssGrp >= VPSS_MAX_GRP_NUM || type < 0 || type >= PROC_AMP_MAX) {
		return CVI_ERR_VPSS_ILLEGAL_PARAM;
	}

	*value = g_vpss_all_proc_amp.s32ProcAmp[VpssGrp][type];
	return CVI_SUCCESS;
}

CVI_S32 CVI_VPSS_SetGrpProcAmp(VPSS_GRP VpssGrp, PROC_AMP_E type, const CVI_S32 value)
{
	if (VpssGrp < 0 || VpssGrp >= VPSS_MAX_GRP_NUM || type < 0 || type >= PROC_AMP_MAX) {
		return CVI_ERR_VPSS_ILLEGAL_PARAM;
	}

	g_vpss_all_proc_amp.s32ProcAmp[VpssGrp][type] = value;
	return CVI_SUCCESS;
}

CVI_S32 CVI_VPSS_SetGrpParamfromBin(VPSS_GRP VpssGrp, VPSS_BIN_DATA *bin_data)
{
	if (VpssGrp < 0 || VpssGrp >= VPSS_MAX_GRP_NUM || bin_data == NULL) {
		return CVI_ERR_VPSS_ILLEGAL_PARAM;
	}

	for (int i = 0; i < PROC_AMP_MAX; i++) {
		g_vpss_all_proc_amp.s32ProcAmp[VpssGrp][i] = bin_data->proc_amp[i];
	}
	return CVI_SUCCESS;
}

CVI_S32 CVI_VPSS_GetChnLDCAttr(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, VPSS_LDC_ATTR_S *pstLDCAttr)
{
	UNUSED(VpssGrp);
	UNUSED(VpssChn);
	memset(pstLDCAttr, 0, sizeof(VPSS_LDC_ATTR_S));
	return CVI_SUCCESS;
}

CVI_S32 CVI_VPSS_SetChnLDCAttr(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, const VPSS_LDC_ATTR_S *pstLDCAttr)
{
	UNUSED(VpssGrp);
	UNUSED(VpssChn);
	UNUSED(pstLDCAttr);
	return CVI_SUCCESS;
}

#include "awb_sim_adapter.h"

// vi module -----------------------------------------------------------------------
CVI_S32 CVI_VI_QueryDevStatus(VI_PIPE ViPipe)
{
	UNUSED(ViPipe);
	return CVI_SUCCESS;
}

CVI_S32 CVI_VI_GetChnLDCAttr(VI_PIPE ViPipe, VI_CHN ViChn, VI_LDC_ATTR_S *pstLDCAttr)
{
	UNUSED(ViPipe);
	UNUSED(ViChn);
	memset(pstLDCAttr, 0, sizeof(VI_LDC_ATTR_S));
	return CVI_SUCCESS;
}

CVI_S32 CVI_VI_SetChnLDCAttr(VI_PIPE ViPipe, VI_CHN ViChn, const VI_LDC_ATTR_S *pstLDCAttr)
{
	UNUSED(ViPipe);
	UNUSED(ViChn);
	UNUSED(pstLDCAttr);
	return CVI_SUCCESS;
}

CVI_S32 CVI_VI_ReleaseChnFrame(VI_PIPE ViPipe, VI_CHN ViChn, const VIDEO_FRAME_INFO_S *pstFrameInfo)
{
	UNUSED(ViPipe);
	UNUSED(ViChn);
	return CVI_VPSS_ReleaseChnFrame(0, 0, pstFrameInfo);
}

CVI_S32 CVI_VI_ReleasePipeFrame(VI_PIPE ViPipe, const VIDEO_FRAME_INFO_S *pstFrameInfo)
{
	UNUSED(ViPipe);
	UNUSED(pstFrameInfo);
	return CVI_SUCCESS;
}

CVI_S32 CVI_VI_GetChnFrame(VI_PIPE ViPipe, VI_CHN ViChn, VIDEO_FRAME_INFO_S *pstFrameInfo, CVI_S32 s32MilliSec)
{
	UNUSED(ViPipe);
	UNUSED(ViChn);
	return CVI_VPSS_GetChnFrame(0, 0, pstFrameInfo, s32MilliSec);
}

CVI_S32 CVI_VI_GetDevAttr(VI_DEV ViDev, VI_DEV_ATTR_S *pstDevAttr)
{
	UNUSED(ViDev);
	memset(pstDevAttr, 0, sizeof(VI_DEV_ATTR_S));
	return CVI_SUCCESS;
}

CVI_S32 CVI_VI_GetChnAttr(VI_PIPE ViPipe, VI_CHN ViChn, VI_CHN_ATTR_S *pstChnAttr)
{
	UNUSED(ViPipe);
	UNUSED(ViChn);
	memset(pstChnAttr, 0, sizeof(VI_CHN_ATTR_S));
	return CVI_SUCCESS;
}

CVI_S32 CVI_VI_SetPipeDumpAttr(VI_PIPE ViPipe, const VI_DUMP_ATTR_S *pstDumpAttr)
{
	UNUSED(ViPipe);
	UNUSED(pstDumpAttr);
	return CVI_SUCCESS;
}

CVI_S32 CVI_VI_GetPipeAttr(VI_PIPE ViPipe, VI_PIPE_ATTR_S *pstPipeAttr)
{
	UNUSED(ViPipe);
	memset(pstPipeAttr, 0, sizeof(VI_PIPE_ATTR_S));
	return CVI_SUCCESS;
}

CVI_S32 CVI_VI_DumpHwRegisterToFile(VI_PIPE ViPipe, FILE *fp, VI_DUMP_REGISTER_TABLE_S *pstRegTbl)
{
	UNUSED(ViPipe);
	UNUSED(fp);
	UNUSED(pstRegTbl);
	return CVI_SUCCESS;
}

CVI_S32 CVI_VI_GetPipeFrame(VI_PIPE ViPipe, VIDEO_FRAME_INFO_S *pstFrameInfo, CVI_S32 s32MilliSec)
{
	UNUSED(ViPipe);
	memset(pstFrameInfo, 0, sizeof(VIDEO_FRAME_INFO_S));
	UNUSED(s32MilliSec);
	return CVI_SUCCESS;
}

CVI_S32 CVI_VI_SetBypassFrm(VI_PIPE ViPipe, CVI_U8 bypass_num)
{
	UNUSED(ViPipe);
	UNUSED(bypass_num);
	return CVI_SUCCESS;
}

// VB module -----------------------------------------------------------------------
CVI_S32 CVI_VB_ReleaseBlock(VB_BLK Block)
{
	UNUSED(Block);
	return CVI_SUCCESS;
}

CVI_S32 CVI_VB_DestroyPool(VB_POOL Pool)
{
	UNUSED(Pool);
	return CVI_SUCCESS;
}

VB_POOL CVI_VB_CreatePool(VB_POOL_CONFIG_S *pstVbPoolCfg)
{
	UNUSED(pstVbPoolCfg);
	return CVI_SUCCESS;
}

VB_BLK CVI_VB_GetBlock(VB_POOL Pool, CVI_U32 u32BlkSize)
{
	UNUSED(Pool);
	UNUSED(u32BlkSize);
	return 0;
}

CVI_U64 CVI_VB_Handle2PhysAddr(VB_BLK Block)
{
	UNUSED(Block);
	return 0;
}

// ----------------------------------------------------------------------------
// Simulated 3A statistics injection
//
// The real CVI_ISP_GetWBStatistics / CVI_ISP_GetAEStatistics read from the ISP
// shared-memory buffer which is populated by hardware DMA on the board.  In the
// AWB simulation environment that buffer is just a calloc'd block and is always
// zero.  These override implementations return data that was parsed from the AWB
// log file and injected via awbsim_fill_3a_stats().
//
// Because the tool object files appear before -lisp on the link line, the linker
// resolves CVI_ISP_GetWBStatistics / CVI_ISP_GetAEStatistics to these definitions
// and the library versions are never used.
// ----------------------------------------------------------------------------

static ISP_WB_STATISTICS_S g_sim_wb_stat;
static ISP_AE_STATISTICS_S g_sim_ae_stat;
static int                 g_sim_stats_valid;

/*
 * awbsim_fill_3a_stats - Populate the simulated 3A statistics buffers.
 *
 * @frame_num  : number of WDR frames (1 = linear, 2 = WDR LE+SE)
 * @zone_row   : number of AWB/AE zone rows  (typically 30)
 * @zone_col   : number of AWB/AE zone columns (typically 34)
 * @zone_r0/g0/b0 : flat zone arrays for frame 0 (LE), length = zone_row * zone_col
 * @zone_r1/g1/b1 : flat zone arrays for frame 1 (SE), or NULL in linear mode
 *
 * Must be called after CVI_ISP_MemInit() and awbInit() have succeeded.
 */
void awbsim_fill_3a_stats(uint8_t frame_num,
			  uint16_t zone_row, uint16_t zone_col,
			  const uint16_t *zone_r0, const uint16_t *zone_g0, const uint16_t *zone_b0,
			  const uint16_t *zone_r1, const uint16_t *zone_g1, const uint16_t *zone_b1)
{
	const uint16_t *zr[ISP_CHANNEL_MAX_NUM] = { zone_r0, zone_r1 };
	const uint16_t *zg[ISP_CHANNEL_MAX_NUM] = { zone_g0, zone_g1 };
	const uint16_t *zb[ISP_CHANNEL_MAX_NUM] = { zone_b0, zone_b1 };

	uint32_t total_zones = (uint32_t)zone_row * zone_col;

	if (total_zones > AWB_ZONE_NUM)
		total_zones = AWB_ZONE_NUM;

	memset(&g_sim_wb_stat, 0, sizeof(g_sim_wb_stat));
	memset(&g_sim_ae_stat, 0, sizeof(g_sim_ae_stat));

	for (int f = 0; f < frame_num && f < ISP_CHANNEL_MAX_NUM; f++) {
		if (!zr[f] || !zg[f] || !zb[f])
			continue;

		uint32_t sum_r = 0, sum_g = 0, sum_b = 0;

		/* Fill WB and AE zone arrays */
		for (uint32_t row = 0; row < zone_row && row < AE_ZONE_ROW; row++) {
			for (uint32_t col = 0; col < zone_col && col < AE_ZONE_COLUMN; col++) {
				uint32_t z = row * zone_col + col;

				/* WB zone stats */
				g_sim_wb_stat.au16ZoneAvgR[f][z]       = zr[f][z];
				g_sim_wb_stat.au16ZoneAvgG[f][z]       = zg[f][z];
				g_sim_wb_stat.au16ZoneAvgB[f][z]       = zb[f][z];
				g_sim_wb_stat.au16ZoneCountAll[f][z]   = 0xFFFF;

				/*
				 * AE zone stats — channel order in au16FEZoneAvg:
				 *   [0] = B, [1] = Gb, [2] = Gr, [3] = R
				 * Use zone_g for both Gb and Gr (AWB log only has one G channel).
				 */
				g_sim_ae_stat.au16FEZoneAvg[f][0][row][col][0] = zb[f][z];
				g_sim_ae_stat.au16FEZoneAvg[f][0][row][col][1] = zg[f][z];
				g_sim_ae_stat.au16FEZoneAvg[f][0][row][col][2] = zg[f][z];
				g_sim_ae_stat.au16FEZoneAvg[f][0][row][col][3] = zr[f][z];

				sum_r += zr[f][z];
				sum_g += zg[f][z];
				sum_b += zb[f][z];
			}
		}

		/* Global averages */
		if (total_zones > 0) {
			g_sim_wb_stat.u16GlobalR[f]  = (uint16_t)(sum_r / total_zones);
			g_sim_wb_stat.u16GlobalG[f]  = (uint16_t)(sum_g / total_zones);
			g_sim_wb_stat.u16GlobalB[f]  = (uint16_t)(sum_b / total_zones);
			g_sim_wb_stat.u16CountAll[f] = 0xFFFF;

			g_sim_ae_stat.au16FEGlobalAvg[f][0][0] = (uint16_t)(sum_b / total_zones);
			g_sim_ae_stat.au16FEGlobalAvg[f][0][1] = (uint16_t)(sum_g / total_zones);
			g_sim_ae_stat.au16FEGlobalAvg[f][0][2] = (uint16_t)(sum_g / total_zones);
			g_sim_ae_stat.au16FEGlobalAvg[f][0][3] = (uint16_t)(sum_r / total_zones);
		}
	}

	g_sim_stats_valid = 1;
}

/* Override CVI_ISP_GetWBStatistics from libisp — returns simulated AWB zone stats */
CVI_S32 CVI_ISP_GetWBStatistics(VI_PIPE ViPipe, ISP_WB_STATISTICS_S *pstWBStat)
{
	UNUSED(ViPipe);
	if (!pstWBStat)
		return CVI_FAILURE;
	if (g_sim_stats_valid)
		*pstWBStat = g_sim_wb_stat;
	else
		memset(pstWBStat, 0, sizeof(*pstWBStat));
	return CVI_SUCCESS;
}

/* Override CVI_ISP_GetAEStatistics from libisp — returns simulated AE zone stats */
CVI_S32 CVI_ISP_GetAEStatistics(VI_PIPE ViPipe, ISP_AE_STATISTICS_S *pstAeStat)
{
	UNUSED(ViPipe);
	if (!pstAeStat)
		return CVI_FAILURE;
	if (g_sim_stats_valid)
		*pstAeStat = g_sim_ae_stat;
	else
		memset(pstAeStat, 0, sizeof(*pstAeStat));
	return CVI_SUCCESS;
}
