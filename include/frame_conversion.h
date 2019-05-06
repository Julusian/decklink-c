#ifndef DECKLINK_C_FRAME_CONVERSION_H
#define DECKLINK_C_FRAME_CONVERSION_H

#include "common.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

cdecklink_video_conversion_t *cdecklink_create_video_conversion();

void cdecklink_release_video_conversion(cdecklink_video_conversion_t *converter);

HRESULT cdecklink_video_conversion_convert_frame(cdecklink_video_conversion_t *converter, cdecklink_video_frame_t* srcFrame, cdecklink_video_frame_t* dstFrame);

#ifdef __cplusplus
};
#endif

#endif //DECKLINK_C_FRAME_CONVERSION_H
