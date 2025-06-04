
#ifndef __DAEMON_MODULE_H__
#define __DAEMON_MODULE_H__

#include "daemon_base.h"
#include "cvi_vpss.h"
#include "cvi_bin.h"

#ifdef __cplusplus
extern "C" {
#endif

extern struct module_fun_t video_src_fun;
extern struct module_fun_t venc_fun;
extern struct module_fun_t cvi_rtsp_fun;
extern struct module_fun_t cvi_rtsp2_fun;
extern struct module_fun_t osd_fun;

typedef struct module_vpss_cfg_t {
	VPSS_GRP_ATTR_S st_vpss_grp_attr;
	VPSS_CHN_ATTR_S st_vpss_chn_attr;
} module_vpss_cfg_t;
extern struct module_fun_t vpss_fun;

typedef struct module_vpss_chn_cfg_t {
	void *src_module;
	VPSS_CHN_ATTR_S st_vpss_chn_attr;
} module_vpss_chn_cfg_t;
extern struct module_fun_t vpss_chn_fun;

extern struct module_fun_t face_ae_fun;
extern struct module_fun_t teaisp_pq_fun;
#ifdef __cplusplus
}
#endif
#endif
