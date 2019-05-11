#include <memory>
#include "types.h"

#ifndef DECKLINK_C_CUSTOM_TYPES_H
#define DECKLINK_C_CUSTOM_TYPES_H

typedef IDeckLinkNotificationCallback cdecklink_notification_callback_notify_handle;

#endif //DECKLINK_C_CUSTOM_TYPES_H

#include "types.h"
#include "include/util.h"
#include "callbacks.h"

void cdecklink_free_string(const char *str) {
    free((void *) str);
}

HRESULT cdecklink_api_version(cdecklink_iterator_t* it, const char** str) {
    IDeckLinkAPIInformation *info;
    HRESULT result = it->QueryInterface(IID_IDeckLinkAPIInformation, reinterpret_cast<void**>(&info));
    if (FAILED(result)) return result;

    return info->GetString(BMDDeckLinkAPIVersion, str);
}

HRESULT cdecklink_device_query_attributes(cdecklink_device_t *obj, cdecklink_attributes_t **dst) {
    return obj->QueryInterface(IID_IDeckLinkAttributes, reinterpret_cast<void**>(dst));
}

HRESULT cdecklink_device_query_status(cdecklink_device_t *obj, cdecklink_status_t **dst) {
    return obj->QueryInterface(IID_IDeckLinkStatus, reinterpret_cast<void**>(dst));
}

HRESULT cdecklink_device_query_notification(cdecklink_device_t *obj, cdecklink_notification_t **dst) {
    return obj->QueryInterface(IID_IDeckLinkNotification, reinterpret_cast<void**>(dst));
}

HRESULT cdecklink_notification_subscribe(
        cdecklink_notification_t *obj,
        DecklinkNotifications topic,
        void *ctx,
        cdecklink_notification_callback_notify *cb0,
        cdecklink_notification_callback_notify_handle **handle) {
    *handle = cdecklink_internal_callback_create_deck_link_notification_callback(ctx, cb0);
    if (*handle != nullptr) {
        return obj->Subscribe(topic, *handle);
    }

    return S_FALSE;
}

HRESULT cdecklink_notification_unsubscribe(
        cdecklink_notification_t *obj,
        DecklinkNotifications topic,
        cdecklink_notification_callback_notify_handle *handle) {
    return obj->Unsubscribe(topic, handle);
}
