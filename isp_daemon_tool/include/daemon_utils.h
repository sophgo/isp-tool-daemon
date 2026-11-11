
#ifndef __DAEMON_UTILS_H__
#define __DAEMON_UTILS_H__

#include "daemon_base.h"
#include "daemon_cfg.h"
#include "sensor_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

int dump_video_frame(FILE *fp, void *pframe);
SENSOR_CFG_S *init_sensor_cfg(daemon_pipe_cfg_t *p_cfg);
SENSOR_CFG_S *get_sensor_cfg(void);

#ifdef __cplusplus
}
#endif
#endif
