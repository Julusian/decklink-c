#include <memory>

#include "types.h"
#include "include/util.h"

void cdecklink_free_string(const char *str) {
    free((void *) str);
}