
#ifndef __TDL_SDK_API_H_
#define __TDL_SDK_API_H_

#include "cvi_tdl.h"

typedef CVI_S32 (*create_handle_t)(cvitdl_handle_t *handle);
typedef CVI_S32 (*destroy_handle_t)(cvitdl_handle_t handle);
typedef CVI_S32 (*open_model_t)(cvitdl_handle_t handle,
				CVI_TDL_SUPPORTED_MODEL_E config,
				const char *filepath);
typedef CVI_S32 (*set_skip_vpss_preprocess_t)(cvitdl_handle_t handle,
					      CVI_TDL_SUPPORTED_MODEL_E model,
					      bool skip);
typedef CVI_S32 (*face_detection_t)(cvitdl_handle_t handle,
				    VIDEO_FRAME_INFO_S *frame,
				    CVI_TDL_SUPPORTED_MODEL_E model_index,
				    cvtdl_face_t *face_meta);
typedef CVI_S32 (*free_face_meta_t)(cvtdl_face_t *face_meta);
typedef CVI_S32 (*rescale_face_meta_t)(VIDEO_FRAME_INFO_S *frame,
				       cvtdl_face_t *face_meta);
typedef CVI_S32 (*isp_image_classification_t)(cvitdl_handle_t handle,
					      VIDEO_FRAME_INFO_S *frame,
					      cvtdl_class_meta_t *obj_meta,
					      cvtdl_isp_meta_t *isp_meta);
typedef CVI_S32 (*free_class_meta_t)(cvtdl_class_meta_t *cls_meta);

typedef CVI_S32 (*service_create_handle_t)(cvitdl_service_handle_t *handle,
					   cvitdl_handle_t tdl_handle);
typedef CVI_S32 (*service_destroy_handle_t)(cvitdl_service_handle_t handle);
typedef CVI_S32 (*service_face_draw_rect_t)(cvitdl_service_handle_t handle,
					    const cvtdl_face_t *meta,
					    VIDEO_FRAME_INFO_S *frame,
					    const bool drawText,
					    cvtdl_service_brush_t brush);
typedef CVI_S32 (*service_object_write_text_t)(char *name, int x, int y,
					       VIDEO_FRAME_INFO_S *frame,
					       float r, float g, float b);

typedef struct {
	create_handle_t create_handle;
	destroy_handle_t destroy_handle;
	open_model_t open_model;
	set_skip_vpss_preprocess_t set_skip_vpss_preprocess;
	face_detection_t face_detection;
	free_face_meta_t free_face_meta;
	rescale_face_meta_t rescale_face_meta;
	isp_image_classification_t isp_image_classification;
	free_class_meta_t free_class_meta;

	service_create_handle_t service_create_handle;
	service_destroy_handle_t service_destroy_handle;
	service_face_draw_rect_t service_face_draw_rect;
	service_object_write_text_t service_object_write_text;
} tdl_sdk_api_t;

int load_tdl_sdk_lib(void);
int unload_tdl_sdk_lib(void);

tdl_sdk_api_t *get_tdl_sdk_api(void);

#endif // __TDL_SDK_API_H_
