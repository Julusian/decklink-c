#ifndef DECKLINK_C_ITERATOR_H
#define DECKLINK_C_ITERATOR_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

struct cdecklink_iterator;
typedef struct cdecklink_iterator cdecklink_iterator_t;

cdecklink_iterator_t *cdecklink_create_iterator();

void cdecklink_destroy_iterator(cdecklink_iterator_t *it);

const char *cdecklink_api_version(cdecklink_iterator_t *it);

#ifdef __cplusplus
};
#endif

#endif //DECKLINK_C_ITERATOR_H
