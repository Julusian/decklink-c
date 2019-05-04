#include <memory>

#include "structs.h"

#include "include/frame.h"

void cdecklink_destroy_frame(cdecklink_video_frame_t *frame) {
    if (frame != nullptr && frame->obj != nullptr) {
        frame->obj->Release();
        free(frame);
    }
}

long cdecklink_video_frame_width(cdecklink_video_frame_t *frame) {
    if (frame != nullptr && frame->obj != nullptr) {
        return frame->obj->GetWidth();
    }

    return 0;
}

long cdecklink_video_frame_height(cdecklink_video_frame_t *frame) {
    if (frame != nullptr && frame->obj != nullptr) {
        return frame->obj->GetHeight();
    }

    return 0;
}

long cdecklink_video_frame_row_bytes(cdecklink_video_frame_t *frame) {
    if (frame != nullptr && frame->obj != nullptr) {
        return frame->obj->GetRowBytes();
    }

    return 0;
}

BMDPixelFormat cdecklink_video_frame_pixel_format(cdecklink_video_frame_t *frame) {
    if (frame != nullptr && frame->obj != nullptr) {
        return frame->obj->GetPixelFormat();
    }

    return bmdFormat8BitYUV;
}

BMDFrameFlags cdecklink_video_frame_flags(cdecklink_video_frame_t *frame) {
    if (frame != nullptr && frame->obj != nullptr) {
        return frame->obj->GetFlags();
    }

    return bmdFrameFlagDefault;
}

HRESULT cdecklink_video_frame_bytes(cdecklink_video_frame_t *frame, void **buffer) {
    if (frame != nullptr && frame->obj != nullptr) {
        return frame->obj->GetBytes(buffer);
    }

    return S_FALSE;
}

cdecklink_video_frame_t *cdecklink_video_mutable_frame_base(cdecklink_mutable_video_frame_t *frame) {
    if (frame != nullptr && frame->obj != nullptr) {
        return frame->base;
    }

    return nullptr;
}

void cdecklink_destroy_mutable_frame(cdecklink_mutable_video_frame_t *frame) {
    if (frame != nullptr && frame->obj != nullptr) {
        frame->obj->Release();
        free(frame->base);
        free(frame);
    }
}

HRESULT cdecklink_video_mutable_frame_set_flags(cdecklink_mutable_video_frame_t *frame, BMDFrameFlags newFlags) {
    if (frame != nullptr && frame->obj != nullptr) {
        return frame->obj->SetFlags(newFlags);
    }

    return S_FALSE;
}
