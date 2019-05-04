#include <memory>

#include "structs.h"

#include "include/device.h"

HRESULT cdecklink_next_device(cdecklink_iterator_t *it, cdecklink_device_t **device) {
    if (it != nullptr && it->obj != nullptr) {
        IDeckLink *dev = nullptr;
        auto result = it->obj->Next(&dev);
        if (result == S_OK) {
            *device = (cdecklink_device_t *) malloc(sizeof(cdecklink_device_t));
            (*device)->obj = dev;
        }

        return result;
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

HRESULT
cdecklink_device_output_does_support_display_mode(cdecklink_device_output_t *output, BMDDisplayMode displayMode,
                                                  BMDPixelFormat pixelFormat,
                                                  BMDVideoOutputFlags flags,
                                                  BMDDisplayModeSupport *result,
                                                  cdecklink_display_mode_t **resultDisplayMode) {
    if (output != nullptr && output->obj != nullptr) {
        IDeckLinkDisplayMode *resultDisplayMode2;
        auto res = output->obj->DoesSupportVideoMode(displayMode, pixelFormat, flags, result, &resultDisplayMode2);
        if (res == S_OK) {
            *resultDisplayMode = (cdecklink_display_mode_t *) malloc(sizeof(cdecklink_display_mode_t));
            (*resultDisplayMode)->obj = resultDisplayMode2;
        }

        return res;
    }

    return S_FALSE;
}

HRESULT cdecklink_device_output_display_mode_iterator(cdecklink_device_output_t *output,
                                                      cdecklink_display_mode_iterator_t **iterator) {
    if (output != nullptr && output->obj != nullptr) {
        IDeckLinkDisplayModeIterator *it;
        auto result = output->obj->GetDisplayModeIterator(&it);
        if (result == S_OK) {
            *iterator = (cdecklink_display_mode_iterator_t *) malloc(sizeof(cdecklink_display_mode_iterator_t));
            (*iterator)->obj = it;
        }

        return result;
    }

    return S_FALSE;
}

/* Video Output */

HRESULT cdecklink_device_output_enable_video_output(cdecklink_device_output_t *output,
                                                    BMDDisplayMode displayMode,
                                                    BMDVideoOutputFlags flags) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->EnableVideoOutput(displayMode, flags);
    }

    return S_FALSE;
}

HRESULT cdecklink_device_output_disable_video_output(cdecklink_device_output_t *output) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->DisableVideoOutput();
    }

    return S_FALSE;
}

HRESULT cdecklink_device_output_create_video_frame(cdecklink_device_output_t *output, int32_t width, int32_t height,
                                                   int32_t rowBytes, BMDPixelFormat pixelFormat, BMDFrameFlags flags,
                                                   cdecklink_mutable_video_frame_t **outFrame) {
    if (output != nullptr && output->obj != nullptr) {
        IDeckLinkMutableVideoFrame *outFrame2;
        auto result = output->obj->CreateVideoFrame(width, height, rowBytes, pixelFormat, flags, &outFrame2);
        if (result == S_OK) {
            *outFrame = (cdecklink_mutable_video_frame_t *) malloc(sizeof(cdecklink_mutable_video_frame_t));
            (*outFrame)->obj = outFrame2;
            (*outFrame)->base = (cdecklink_video_frame_t *) malloc(sizeof(cdecklink_video_frame_t));
            (*outFrame)->base->obj = outFrame2;
        }

        return result;
    }

    return S_FALSE;
}

HRESULT
cdecklink_device_output_display_video_frame_sync(cdecklink_device_output_t *output, cdecklink_video_frame_t *frame) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->DisplayVideoFrameSync(frame->obj);
    }

    return S_FALSE;
}
