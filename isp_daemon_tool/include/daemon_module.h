
#ifndef __DAEMON_MODULE_H__
#define __DAEMON_MODULE_H__

#include "daemon_base.h"
#include "daemon_cfg.h"
#include "cvi_vpss.h"

#ifdef __cplusplus
extern "C" {
#endif

extern struct module_fun_t video_src_fun;

typedef struct module_venc_cfg_t {
	uint32_t width;
	uint32_t height;
	PIXEL_FORMAT_E pixel_format;
	char codec[MAX_CODEC_LEN];
	vc_cfg_t vc_cfg;
} module_venc_cfg_t;
extern struct module_fun_t venc_fun;

typedef struct module_rtsp_cfg_t {
	int rtsp_port;
	int max_buf_size;
	int bitrate;
	char codec[MAX_CODEC_LEN];
} module_rtsp_cfg_t;
extern struct module_fun_t rtsp_fun;

extern struct module_fun_t osd_fun;

typedef struct module_vpss_cfg_t {
	int8_t grp_id; // -1 for auto assign
	uint8_t chn_id;
	uint8_t chn_num;
	uint8_t enable_bypass_src_frame;
	VPSS_GRP_ATTR_S st_vpss_grp_attr;
	uint8_t chn_vb_cnt[VPSS_MAX_CHN_NUM];
	VPSS_CHN_ATTR_S st_vpss_chn_attr[VPSS_MAX_CHN_NUM];
} module_vpss_cfg_t;
extern struct module_fun_t vpss_fun;

typedef struct module_vpss_chn_cfg_t {
	uint8_t src_grp_id;
	uint8_t chn_id;
} module_vpss_chn_cfg_t;
extern struct module_fun_t vpss_chn_fun;

typedef struct module_teaisp_drc_cfg_t {
	char model_path[MAX_PATH_LEN];
} module_teaisp_drc_cfg_t;
extern struct module_fun_t teaisp_drc_fun;

typedef struct module_teaisp_vsr_cfg_t {
	char model_path[MAX_PATH_LEN];
} module_teaisp_vsr_cfg_t;
extern struct module_fun_t teaisp_vsr_fun;

typedef struct module_face_ae_cfg_t {
	char model_path[MAX_PATH_LEN];
} module_face_ae_cfg_t;
extern struct module_fun_t face_ae_fun;

typedef struct module_teaisp_pq_cfg_t {
	char model_path[MAX_PATH_LEN];
} module_teaisp_pq_cfg_t;
extern struct module_fun_t teaisp_pq_fun;

extern struct module_fun_t empty_module_fun;
#ifdef __cplusplus
}
#endif
#endif
