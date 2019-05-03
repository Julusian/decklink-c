#ifndef DECKLINK_C_STRUCTS_H
#define DECKLINK_C_STRUCTS_H

#include "decklink_api.h"

struct cdecklink_iterator {
    IDeckLinkIterator *obj;
};

struct cdecklink_device {
    IDeckLink *obj;
};

struct cdecklink_display_mode {
    IDeckLinkDisplayMode *obj;
};

struct cdecklink_device_output {
    IDeckLinkOutput *obj;
};

#endif //DECKLINK_C_STRUCTS_H
