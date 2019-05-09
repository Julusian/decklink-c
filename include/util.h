#ifndef DECKLINK_C_UTIL_H
#define DECKLINK_C_UTIL_H

#include "common.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void cdecklink_free_string(const char *str);

HRESULT cdecklink_api_version(cdecklink_iterator_t* it, const char** str);

HRESULT cdecklink_device_query_attributes(cdecklink_device_t *obj, cdecklink_attributes_t **dst);

#ifdef __cplusplus
};
#endif

#endif //DECKLINK_C_UTIL_H
