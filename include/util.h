#ifndef DECKLINK_C_UTIL_H
#define DECKLINK_C_UTIL_H

#include "api.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DECKLINK_C_CUSTOM_TYPES_H
#define DECKLINK_C_CUSTOM_TYPES_H

typedef void cdecklink_notification_callback_notify_handle;
typedef void cdecklink_custom_video_frame_t;

#endif //DECKLINK_C_CUSTOM_TYPES_H

void cdecklink_free_string(const char *str);

HRESULT cdecklink_api_version(cdecklink_iterator_t* it, const char** str);

HRESULT cdecklink_device_query_attributes(cdecklink_device_t *obj, cdecklink_attributes_t **dst);

HRESULT cdecklink_device_query_status(cdecklink_device_t *obj, cdecklink_status_t **dst);

HRESULT cdecklink_device_query_notification(cdecklink_device_t *obj, cdecklink_notification_t **dst);

HRESULT cdecklink_notification_subscribe(
    cdecklink_notification_t *obj,
    DecklinkNotifications topic,
    void *ctx,
    cdecklink_notification_callback_notify *cb0,
    cdecklink_notification_callback_notify_handle **handle);

HRESULT cdecklink_notification_unsubscribe(
    cdecklink_notification_t *obj,
    DecklinkNotifications topic,
    cdecklink_notification_callback_notify_handle *handle);

#ifdef __cplusplus
};
#endif

#endif //DECKLINK_C_UTIL_H
