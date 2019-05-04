#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/decklink_c.h"

int main() {
    cdecklink_iterator_t *iterator = cdecklink_create_iterator();
    if (!iterator)
        goto CLEANUP;

    const char *version = cdecklink_api_version(iterator);
    if (!version)
        goto CLEANUP;

    printf("Driver version: %s\n\n", version);
    free((void *) version);

    cdecklink_device_t *device = NULL;
    int index = 0;
    while (cdecklink_next_device(iterator, &device) == S_OK) {
        const char *model_name = cdecklink_device_model_name(device);
        const char *display_name = cdecklink_device_display_name(device);
        cdecklink_destroy_device(device);

        printf("%d: %s - %s\n", index++, model_name, display_name);

        free((void *) model_name);
        free((void *) display_name);
    }

    CLEANUP:
    if (iterator)
        cdecklink_destroy_iterator(iterator);

    return 0;
}