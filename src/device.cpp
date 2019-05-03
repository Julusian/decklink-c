#include <memory>

#include "device.h"
#include "structs.h"

HRESULT cdecklink_next_device(cdecklink_iterator_t *it, cdecklink_device_t** device) {
    if (it != nullptr && it->obj != nullptr) {
        IDeckLink* dev = nullptr;
        auto ok = it->obj->Next(&dev);
        if (SUCCEEDED(ok)) {
            *device = (cdecklink_device_t*)malloc(sizeof(cdecklink_device_t));
            (*device)->obj = dev;
        }

        return ok;
    }

    return S_FALSE;
}
void cdecklink_destroy_device(cdecklink_device_t *device) {
    if (device != nullptr && device->obj != nullptr) {
        device->obj->Release();
        device->obj = nullptr;
    }
}

const char *cdecklink_device_model_name(cdecklink_device_t *device) {
    if (device != nullptr && device->obj != nullptr) {
        String name;
        if (SUCCEEDED(device->obj->GetModelName(&name))) {
            return name;
        }
    }

    return nullptr;
}

const char *cdecklink_device_display_name(cdecklink_device_t *device) {
    if (device != nullptr && device->obj != nullptr) {
        String name;
        if (SUCCEEDED(device->obj->GetDisplayName(&name))) {
            return name;
        }
    }

    return nullptr;
}
