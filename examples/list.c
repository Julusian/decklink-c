#include <stdio.h>
#include <string.h>

#include "include/decklink_c.h"

int main() {
    cdecklink_iterator_t *iterator = cdecklink_create_iterator();
    if (!iterator)
        goto CLEANUP;

    cdecklink_device_t *device = NULL;
    while (cdecklink_next_device(iterator, &device) == S_OK) {
        const char *model_name = cdecklink_device_model_name(device);
        const char *display_name = cdecklink_device_display_name(device);

        printf("%s - %s\n", model_name, display_name);
    }
    printf("\n");

    CLEANUP:
    printf("Cleanup\n");

    if (iterator)
        cdecklink_destroy_iterator(iterator);

    return 0;
}