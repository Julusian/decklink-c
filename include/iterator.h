#ifndef DECKLINK_C_ITERATOR_H
#define DECKLINK_C_ITERATOR_H

#include "common.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void cdecklink_free_string(const char *str);

cdecklink_iterator_t *cdecklink_create_iterator();

void cdecklink_release_iterator(cdecklink_iterator_t *it);

HRESULT cdecklink_api_version(cdecklink_iterator_t *it, const char **version);

#ifdef __cplusplus
};
#endif

#endif //DECKLINK_C_ITERATOR_H
