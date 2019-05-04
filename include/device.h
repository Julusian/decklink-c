#ifndef DECKLINK_C_DEVICE_H
#define DECKLINK_C_DEVICE_H

#include "common.h"
#include "display_mode.h"
#include "enums.h"
#include "frame.h"
#include "iterator.h"

#ifdef __cplusplus
extern "C" {
#endif

struct cdecklink_device;
typedef struct cdecklink_device cdecklink_device_t;

HRESULT cdecklink_next_device(cdecklink_iterator_t *it, cdecklink_device_t **device);

void cdecklink_destroy_device(cdecklink_device_t *device);

const char *cdecklink_device_model_name(cdecklink_device_t *device);

const char *cdecklink_device_display_name(cdecklink_device_t *device);

struct cdecklink_device_output;
typedef struct cdecklink_device_output cdecklink_device_output_t;

cdecklink_device_output_t *cdecklink_device_output_cast(cdecklink_device_t *device);

void cdecklink_destroy_device_output(cdecklink_device_output_t *output);

HRESULT
cdecklink_device_output_does_support_display_mode(cdecklink_device_output_t *output, BMDDisplayMode displayMode,
                                                  BMDPixelFormat pixelFormat,
                                                  BMDVideoOutputFlags flags,
                                                  BMDDisplayModeSupport *result,
                                                  cdecklink_display_mode_t **resultDisplayMode);

HRESULT cdecklink_device_output_display_mode_iterator(cdecklink_device_output_t *output,
                                                      cdecklink_display_mode_iterator_t **iterator);

//virtual HRESULT SetScreenPreviewCallback (/* in */ IDeckLinkScreenPreviewCallback *previewCallback) = 0;

/* Video Output */

HRESULT cdecklink_device_output_enable_video_output(cdecklink_device_output_t *output,
                                                    BMDDisplayMode displayMode,
                                                    BMDVideoOutputFlags flags);

HRESULT cdecklink_device_output_disable_video_output(cdecklink_device_output_t *output);

// virtual HRESULT SetVideoOutputFrameMemoryAllocator (/* in */ IDeckLinkMemoryAllocator *theAllocator) = 0;

HRESULT
cdecklink_device_output_create_video_frame(cdecklink_device_output_t *output, int32_t width, int32_t height,
                                           int32_t rowBytes, BMDPixelFormat pixelFormat,
                                           BMDFrameFlags flags, cdecklink_mutable_video_frame_t **outFrame);

//virtual HRESULT CreateAncillaryData (/* in */ BMDPixelFormat pixelFormat, /* out */ IDeckLinkVideoFrameAncillary **outBuffer) = 0;

HRESULT cdecklink_device_output_display_video_frame_sync (cdecklink_device_output_t *output, cdecklink_video_frame_t *frame);

#ifdef __cplusplus
};
#endif

#endif //DECKLINK_C_DEVICE_H
