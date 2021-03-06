#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/decklink_c.h"

int main() {
    cdecklink_iterator_t *iterator = cdecklink_create_decklink_iterator_instance();
    if (!iterator)
        goto CLEANUP;

    const char *version;
    if (FAILED(cdecklink_api_version(iterator, &version)))
        goto CLEANUP;

    printf("Driver version: %s\n\n", version);
    cdecklink_free_string(version);

    cdecklink_device_t *device = NULL;
    int index = 0;
    while (cdecklink_iterator_next(iterator, &device) == S_OK) {
        const char *model_name;
        const char *display_name;
        if (FAILED(cdecklink_device_get_model_name(device, &model_name))) {
            model_name = "Unknown";
        }
        if (FAILED(cdecklink_device_get_display_name(device, &display_name))) {
            display_name = "Unknown";
        }
        cdecklink_device_release(device);

        printf("%d: %s - %s\n", index++, model_name, display_name);

        cdecklink_free_string(model_name);
        cdecklink_free_string(display_name);
    }

    CLEANUP:
    if (iterator)
        cdecklink_iterator_release(iterator);

    return 0;
}