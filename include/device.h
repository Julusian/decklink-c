#ifndef DECKLINK_C_DEVICE_H
#define DECKLINK_C_DEVICE_H

#include "common.h"
#include "iterator.h"

#ifdef __cplusplus
extern "C" {
#endif

struct cdecklink_device;
typedef struct cdecklink_device cdecklink_device_t;

HRESULT cdecklink_next_device(cdecklink_iterator_t *it, cdecklink_device_t** device);
void cdecklink_destroy_device(cdecklink_device_t *device);

const char *cdecklink_device_model_name(cdecklink_device_t *device);
const char *cdecklink_device_display_name(cdecklink_device_t *device);

#ifdef __cplusplus
};
#endif

#endif //DECKLINK_C_DEVICE_H
