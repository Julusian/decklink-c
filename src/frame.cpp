#include <memory>

#include "types.h"

#include "include/frame.h"

void cdecklink_release_frame(cdecklink_video_frame_t *frame) {
    frame->Release();
}

long cdecklink_video_frame_width(cdecklink_video_frame_t *frame) {
    return frame->GetWidth();
}

long cdecklink_video_frame_height(cdecklink_video_frame_t *frame) {
    return frame->GetHeight();
}

long cdecklink_video_frame_row_bytes(cdecklink_video_frame_t *frame) {
    return frame->GetRowBytes();
}

BMDPixelFormat cdecklink_video_frame_pixel_format(cdecklink_video_frame_t *frame) {
    return frame->GetPixelFormat();
}

BMDFrameFlags cdecklink_video_frame_flags(cdecklink_video_frame_t *frame) {
    return frame->GetFlags();
}

HRESULT cdecklink_video_frame_bytes(cdecklink_video_frame_t *frame, void **buffer) {
    return frame->GetBytes(buffer);
}

/* Mutable frame */

cdecklink_video_frame_t *cdecklink_video_mutable_frame_get_frame(cdecklink_mutable_video_frame_t *frame) {
    return frame;
}

void cdecklink_release_mutable_frame(cdecklink_mutable_video_frame_t *frame) {
    frame->Release();
}

HRESULT cdecklink_video_mutable_frame_set_flags(cdecklink_mutable_video_frame_t *frame, BMDFrameFlags newFlags) {
    return frame->SetFlags(newFlags);
}
