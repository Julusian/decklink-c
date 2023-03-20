#include "types.h"

#ifndef DECKLINK_C_CUSTOM_TYPES_H
#define DECKLINK_C_CUSTOM_TYPES_H

typedef IDeckLinkNotificationCallback cdecklink_notification_callback_notify_handle;

class CustomDecklinkFrame;
typedef CustomDecklinkFrame cdecklink_custom_video_frame_t;

#endif // DECKLINK_C_CUSTOM_TYPES_H
