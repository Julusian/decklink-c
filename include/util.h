#ifndef DECKLINK_C_UTIL_H
#define DECKLINK_C_UTIL_H

#include "common.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void cdecklink_free_string(const char *str);

HRESULT cdecklink_api_version(cdecklink_iterator_t* it, const char** str);

#ifdef __cplusplus
};
#endif

#endif //DECKLINK_C_UTIL_H
