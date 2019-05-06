#ifndef DECKLINK_C_TYPES_H
#define DECKLINK_C_TYPES_H

#include "interop/Linux/include/DeckLinkAPI.h"

typedef IDeckLinkIterator cdecklink_iterator_t;

typedef IDeckLinkDisplayModeIterator cdecklink_display_mode_iterator_t;

typedef IDeckLinkDisplayMode cdecklink_display_mode_t;

typedef IDeckLink cdecklink_device_t;

typedef IDeckLinkOutput cdecklink_device_output_t;

typedef IDeckLinkInput cdecklink_device_input_t;

typedef IDeckLinkAttributes cdecklink_device_attributes_t;

typedef IDeckLinkStatus cdecklink_device_status_t;

typedef IDeckLinkVideoFrame cdecklink_video_frame_t;

typedef IDeckLinkMutableVideoFrame cdecklink_mutable_video_frame_t;

typedef IDeckLinkVideoInputFrame cdecklink_video_input_frame_t;

typedef IDeckLinkAudioInputPacket cdecklink_audio_input_packet_t;

typedef IDeckLinkTimecode cdecklink_timecode_t;

typedef IDeckLinkVideoFrameAncillary cdecklink_video_frame_ancillary_t;

typedef IDeckLinkVideoConversion cdecklink_video_conversion_t;

#endif //DECKLINK_C_TYPES_H
