
#ifndef __VIDEO_SRC_CFG_H__
#define __VIDEO_SRC_CFG_H__

int module_sys_vi_init(void *pipe_cfg);
int module_sys_vi_deinit(void *pipe_cfg);

int replay_sys_vi_int(daemon_pipe_cfg_t *pipe_cfg);
int replay_sys_vi_deinit(daemon_pipe_cfg_t *pipe_cfg);

#endif // __VIDEO_SRC_CFG_H__