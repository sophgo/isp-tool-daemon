#ifndef ISP_INTERNAL_API_H
#define ISP_INTERNAL_API_H

#include "cvi_type.h"
#include "cvi_comm_isp.h"

/* internal ISP APIs without a public header declaration yet */
extern CVI_S32 CVI_ISP_GetAWBSnapLogBuf(VI_PIPE ViPipe, CVI_U8 *buf, CVI_U32 bufSize);

#endif /* ISP_INTERNAL_API_H */
