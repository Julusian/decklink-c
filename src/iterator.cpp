#include <memory>

#include "types.h"

#include "include/iterator.h"

void cdecklink_free_string(const char *str) {
    free((void *) str);
}

cdecklink_iterator_t *cdecklink_create_iterator() {
    return CreateDeckLinkIteratorInstance();
}

void cdecklink_release_iterator(cdecklink_iterator_t *it) {
    it->Release();
}

HRESULT cdecklink_api_version(cdecklink_iterator_t *it, const char **version) {
    auto info = iface_cast_raw<IDeckLinkAPIInformation>(it);
    if (info) {
        return info->GetString(BMDDeckLinkAPIVersion, version);
    }

    return E_NOINTERFACE;
}
