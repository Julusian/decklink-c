#ifndef DECKLINK_C_FRAME_H
#define DECKLINK_C_FRAME_H

#include "common.h"
#include "enums.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void cdecklink_release_frame(cdecklink_video_frame_t *frame);

long cdecklink_video_frame_width(cdecklink_video_frame_t *frame);

long cdecklink_video_frame_height(cdecklink_video_frame_t *frame);

long cdecklink_video_frame_row_bytes(cdecklink_video_frame_t *frame);

BMDPixelFormat cdecklink_video_frame_pixel_format(cdecklink_video_frame_t *frame);

BMDFrameFlags cdecklink_video_frame_flags(cdecklink_video_frame_t *frame);

HRESULT cdecklink_video_frame_bytes(cdecklink_video_frame_t *frame, void **buffer);

//HRESULT cdecklink_video_frame_timecode(cdecklink_video_frame_t* frame, IDeckLinkTimecode **timecode);
//HRESULT cdecklink_video_frame_ancillary_data(cdecklink_video_frame_t* frame, IDeckLinkVideoFrameAncillary **ancillary);

/* Mutable frame */

cdecklink_video_frame_t *cdecklink_video_mutable_frame_get_frame(cdecklink_mutable_video_frame_t *frame);

void cdecklink_release_mutable_frame(cdecklink_mutable_video_frame_t *frame);

HRESULT cdecklink_video_mutable_frame_set_flags (cdecklink_mutable_video_frame_t *frame, BMDFrameFlags newFlags);

//HRESULT SetTimecode (/* in */ BMDTimecodeFormat format, /* in */ IDeckLinkTimecode *timecode) = 0;
//HRESULT SetTimecodeFromComponents (/* in */ BMDTimecodeFormat format, /* in */ uint8_t hours, /* in */ uint8_t minutes, /* in */ uint8_t seconds, /* in */ uint8_t frames, /* in */ BMDTimecodeFlags flags) = 0;
//HRESULT SetAncillaryData (/* in */ IDeckLinkVideoFrameAncillary *ancillary) = 0;
//HRESULT SetTimecodeUserBits (/* in */ BMDTimecodeFormat format, /* in */ BMDTimecodeUserBits userBits) = 0;

#ifdef __cplusplus
};
#endif

#endif //DECKLINK_C_FRAME_H
