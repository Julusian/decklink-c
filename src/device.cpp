#include <memory>

#include "structs.h"

#include "include/device.h"

HRESULT cdecklink_next_device(cdecklink_iterator_t *it, cdecklink_device_t **device) {
    if (it != nullptr && it->obj != nullptr) {
        IDeckLink *dev = nullptr;
        auto ok = it->obj->Next(&dev);
        if (ok == S_OK) {
            *device = (cdecklink_device_t *) malloc(sizeof(cdecklink_device_t));
            (*device)->obj = dev;
        }

        return ok;
    }

    return S_FALSE;
}

void cdecklink_destroy_device(cdecklink_device_t *device) {
    if (device != nullptr && device->obj != nullptr) {
        device->obj->Release();
        free(device);
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

cdecklink_device_output_t *cdecklink_device_output_cast(cdecklink_device_t *device) {
    if (device != nullptr && device->obj != nullptr) {
        IDeckLinkOutput *output;
        if (device->obj->QueryInterface(IID_IDeckLinkOutput, reinterpret_cast<void **>(&output)) == S_OK) {
            auto device2 = (cdecklink_device_output_t *) malloc(sizeof(cdecklink_device_output_t));
            device2->obj = output;

//            auto r = output->AddRef();
//            printf("%d refs\n\n", r);
            return device2;
        }
    }

    return nullptr;
}

void cdecklink_destroy_device_output(cdecklink_device_output_t *output) {
    if (output != nullptr && output->obj != nullptr) {
        output->obj->Release();
        free(output);
    }
}
