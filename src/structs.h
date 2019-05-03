#ifndef DECKLINK_C_STRUCTS_H
#define DECKLINK_C_STRUCTS_H

#include "decklink_api.h"

struct cdecklink_iterator {
    IDeckLinkIterator* obj;
};

struct cdecklink_device {
    IDeckLink* obj;
};

#endif //DECKLINK_C_STRUCTS_H
