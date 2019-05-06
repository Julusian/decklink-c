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

HRESULT cdecklink_video_frame_timecode(cdecklink_video_frame_t *frame, BMDTimecodeFormat format,
                                       cdecklink_timecode_t **timecode);

HRESULT
cdecklink_video_frame_ancillary_data(cdecklink_video_frame_t *frame, cdecklink_video_frame_ancillary_t **ancillary);

/** Mutable frame **/

cdecklink_video_frame_t *cdecklink_video_mutable_frame_get_frame(cdecklink_mutable_video_frame_t *frame);

void cdecklink_release_mutable_frame(cdecklink_mutable_video_frame_t *frame);

HRESULT cdecklink_video_mutable_frame_set_flags(cdecklink_mutable_video_frame_t *frame, BMDFrameFlags newFlags);

//HRESULT SetTimecode (/* in */ BMDTimecodeFormat format, /* in */ IDeckLinkTimecode *timecode) = 0;
//HRESULT SetTimecodeFromComponents (/* in */ BMDTimecodeFormat format, /* in */ uint8_t hours, /* in */ uint8_t minutes, /* in */ uint8_t seconds, /* in */ uint8_t frames, /* in */ BMDTimecodeFlags flags) = 0;
//HRESULT SetAncillaryData (/* in */ IDeckLinkVideoFrameAncillary *ancillary) = 0;
//HRESULT SetTimecodeUserBits (/* in */ BMDTimecodeFormat format, /* in */ BMDTimecodeUserBits userBits) = 0;

/** Input frame **/

cdecklink_video_frame_t *cdecklink_video_input_frame_get_frame(cdecklink_video_input_frame_t *frame);

HRESULT cdecklink_video_input_frame_stream_time(cdecklink_video_input_frame_t *frame, BMDTimeValue *frameTime,
                                                BMDTimeValue *frameDuration, BMDTimeScale timeScale);

HRESULT
cdecklink_video_input_frame_hardware_reference_timestamp(cdecklink_video_input_frame_t *frame, BMDTimeScale timeScale,
                                                         BMDTimeValue *frameTime, BMDTimeValue *frameDuration);

/** Ancillary data **/

HRESULT cdecklink_video_frame_ancillary_buffer_for_vertical_blanking_line(cdecklink_video_frame_ancillary_t *ancillary,
                                                                          uint32_t lineNumber, void **buffer);

BMDPixelFormat cdecklink_video_frame_ancillary_pixel_format(cdecklink_video_frame_ancillary_t *ancillary);

BMDDisplayMode cdecklink_video_frame_ancillary_display_mode(cdecklink_video_frame_ancillary_t *ancillary);

/** Timecode **/

// TODO - release
// TODO - addref?

BMDTimecodeBCD cdecklink_timecode_bcd(cdecklink_timecode_t *timecode);

HRESULT
cdecklink_timecode_components(cdecklink_timecode_t *timecode, uint8_t *hours, uint8_t *minutes, uint8_t *seconds,
                              uint8_t *frames);

HRESULT cdecklink_timecode_string(cdecklink_timecode_t *timecode, const char **string);

BMDTimecodeFlags cdecklink_timecode_flags(cdecklink_timecode_t *timecode);

HRESULT cdecklink_timecode_user_bits(cdecklink_timecode_t *timecode, BMDTimecodeUserBits *userBits);

#ifdef __cplusplus
};
#endif

#endif //DECKLINK_C_FRAME_H
