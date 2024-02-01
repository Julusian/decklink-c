#include "./api.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void cdecklink_custom_video_frame_free_bytes(void *bytes, void *context);

HRESULT cdecklink_custom_video_frame_create_frame(long width, long height, long row_bytes, DecklinkPixelFormat pixel_format, DecklinkFrameFlags flags, cdecklink_mutable_video_frame_t **frame);
unsigned long cdecklink_custom_video_frame_add_ref(cdecklink_mutable_video_frame_t *obj);
unsigned long cdecklink_custom_video_frame_release(cdecklink_mutable_video_frame_t *obj);
long cdecklink_custom_video_frame_get_width(cdecklink_mutable_video_frame_t *obj);
long cdecklink_custom_video_frame_get_height(cdecklink_mutable_video_frame_t *obj);
long cdecklink_custom_video_frame_get_row_bytes(cdecklink_mutable_video_frame_t *obj);
DecklinkPixelFormat cdecklink_custom_video_frame_get_pixel_format(cdecklink_mutable_video_frame_t *obj);
DecklinkFrameFlags cdecklink_custom_video_frame_get_flags(cdecklink_mutable_video_frame_t *obj);
HRESULT cdecklink_custom_video_frame_get_bytes(cdecklink_mutable_video_frame_t *obj, void **buffer);
HRESULT cdecklink_custom_video_frame_set_bytes(cdecklink_mutable_video_frame_t *obj, void *buffer, cdecklink_custom_video_frame_free_bytes *finalizer, void *context);

#ifdef __cplusplus
}
#endif