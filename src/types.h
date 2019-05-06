#ifndef DECKLINK_C_TYPES_H
#define DECKLINK_C_TYPES_H

#include "decklink_api.h"

typedef IDeckLinkIterator cdecklink_iterator_t;

typedef IDeckLinkDisplayModeIterator cdecklink_display_mode_iterator_t;

typedef IDeckLinkDisplayMode cdecklink_display_mode_t;

typedef IDeckLink cdecklink_device_t;

typedef IDeckLinkOutput cdecklink_device_output_t;

typedef IDeckLinkVideoFrame cdecklink_video_frame_t;

typedef IDeckLinkMutableVideoFrame cdecklink_mutable_video_frame_t;


typedef IDeckLinkTimecode cdecklink_timecode_t;

typedef IDeckLinkVideoFrameAncillary cdecklink_video_frame_ancillary_t;

#endif //DECKLINK_C_TYPES_H
