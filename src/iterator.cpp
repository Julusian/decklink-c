#include <memory>

#include "structs.h"

#include "include/iterator.h"

void cdecklink_free_string(const char *str) {
    free((void *) str);
}

cdecklink_iterator_t *cdecklink_create_iterator() {
    IDeckLinkIterator *iterator = CreateDeckLinkIteratorInstance();
    if (iterator == nullptr)
        return nullptr;

    auto it = (cdecklink_iterator_t *) malloc(sizeof(cdecklink_iterator_t));
    it->obj = iterator;
    return it;
}

void cdecklink_destroy_iterator(cdecklink_iterator_t *it) {
    if (it != nullptr && it->obj != nullptr) {
        it->obj->Release();
        free(it);
    }
}

const char *cdecklink_api_version(cdecklink_iterator_t *it) {
    if (it != nullptr && it->obj != nullptr) {
        auto info = iface_cast_raw<IDeckLinkAPIInformation>(it->obj);
        if (info) {
            String ver;
            if (SUCCEEDED(info->GetString(BMDDeckLinkAPIVersion, &ver)))
                return ver;
        }
    }

    return nullptr;
}
