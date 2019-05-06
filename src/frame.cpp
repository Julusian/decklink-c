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

HRESULT cdecklink_video_frame_timecode(cdecklink_video_frame_t *frame, BMDTimecodeFormat format,
                                       cdecklink_timecode_t **timecode) {
    return frame->GetTimecode(format, timecode);
}

HRESULT
cdecklink_video_frame_ancillary_data(cdecklink_video_frame_t *frame, cdecklink_video_frame_ancillary_t **ancillary) {
    return frame->GetAncillaryData(ancillary);
}

/** Mutable frame **/

cdecklink_video_frame_t *cdecklink_video_mutable_frame_get_frame(cdecklink_mutable_video_frame_t *frame) {
    return frame;
}

void cdecklink_release_mutable_frame(cdecklink_mutable_video_frame_t *frame) {
    frame->Release();
}

HRESULT cdecklink_video_mutable_frame_set_flags(cdecklink_mutable_video_frame_t *frame, BMDFrameFlags newFlags) {
    return frame->SetFlags(newFlags);
}

/** Input frame **/

cdecklink_video_frame_t *cdecklink_video_input_frame_get_frame(cdecklink_video_input_frame_t *frame) {
    return frame;
}

HRESULT cdecklink_video_input_frame_stream_time(cdecklink_video_input_frame_t *frame, BMDTimeValue *frameTime,
                                                BMDTimeValue *frameDuration, BMDTimeScale timeScale) {
    return frame->GetStreamTime(frameTime, frameDuration, timeScale);
}

HRESULT
cdecklink_video_input_frame_hardware_reference_timestamp(cdecklink_video_input_frame_t *frame, BMDTimeScale timeScale,
                                                         BMDTimeValue *frameTime, BMDTimeValue *frameDuration) {
    return frame->GetHardwareReferenceTimestamp(timeScale, frameTime, frameDuration);
}

/** Ancillary data **/

HRESULT cdecklink_video_frame_ancillary_buffer_for_vertical_blanking_line(cdecklink_video_frame_ancillary_t *ancillary,
                                                                          uint32_t lineNumber, void **buffer) {
    return ancillary->GetBufferForVerticalBlankingLine(lineNumber, buffer);
}

BMDPixelFormat cdecklink_video_frame_ancillary_pixel_format(cdecklink_video_frame_ancillary_t *ancillary) {
    return ancillary->GetPixelFormat();
}

BMDDisplayMode cdecklink_video_frame_ancillary_display_mode(cdecklink_video_frame_ancillary_t *ancillary) {
    return ancillary->GetDisplayMode();
}

/** Timecode **/

BMDTimecodeBCD cdecklink_timecode_bcd(cdecklink_timecode_t *timecode) {
    return timecode->GetBCD();
}

HRESULT
cdecklink_timecode_components(cdecklink_timecode_t *timecode, uint8_t *hours, uint8_t *minutes, uint8_t *seconds,
                              uint8_t *frames) {
    return timecode->GetComponents(hours, minutes, seconds, frames);
}

HRESULT cdecklink_timecode_string(cdecklink_timecode_t *timecode, const char **string) {
    return timecode->GetString(string);
}

BMDTimecodeFlags cdecklink_timecode_flags(cdecklink_timecode_t *timecode) {
    return timecode->GetFlags();
}

HRESULT cdecklink_timecode_user_bits(cdecklink_timecode_t *timecode, BMDTimecodeUserBits *userBits) {
    return timecode->GetTimecodeUserBits(userBits);
}
