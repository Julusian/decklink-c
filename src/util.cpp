#include <memory>

#include "types.h"
#include "include/util.h"

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
