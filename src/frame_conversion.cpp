#include <memory>

#include "types.h"

#include "include/frame_conversion.h"

cdecklink_video_conversion_t *cdecklink_create_video_conversion() {
    return CreateVideoConversionInstance();
}

void cdecklink_release_video_conversion(cdecklink_video_conversion_t *converter) {
    converter->Release();
}

HRESULT cdecklink_video_conversion_convert_frame(cdecklink_video_conversion_t *converter, cdecklink_video_frame_t* srcFrame, cdecklink_video_frame_t* dstFrame) {
    return converter->ConvertFrame(srcFrame, dstFrame);
}
