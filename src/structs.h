#ifndef DECKLINK_C_STRUCTS_H
#define DECKLINK_C_STRUCTS_H

#include "decklink_api.h"

struct cdecklink_iterator {
    IDeckLinkIterator *obj;
};

struct cdecklink_device {
    IDeckLink *obj;
};

struct cdecklink_display_mode_iterator {
    IDeckLinkDisplayModeIterator *obj;
};

struct cdecklink_display_mode {
    IDeckLinkDisplayMode *obj;
};

struct cdecklink_device_output {
    IDeckLinkOutput *obj;
};

struct cdecklink_video_frame {
    IDeckLinkVideoFrame *obj;
};

struct cdecklink_mutable_video_frame {
    cdecklink_video_frame *base;
    IDeckLinkMutableVideoFrame *obj;
};

#endif //DECKLINK_C_STRUCTS_H
