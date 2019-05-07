#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "include/decklink_c.h"

int main() {
    cdecklink_iterator_t *iterator = cdecklink_create_decklink_iterator_instance();
    if (!iterator)
        goto CLEANUP;

    int index = 3;
    printf("Choose decklink device to output to: ");
    printf("\n");
    scanf("%d", &index);

    // Fetch the selected device
    cdecklink_device_t *device = NULL;
    int i = -1;
    while (cdecklink_iterator_next(iterator, &device) == S_OK) {
        if (++i == index) {
            break;
        }

        cdecklink_device_release(device);
        device = NULL;
    }

    if (i != index || device == NULL) {
        printf("Invalid device index\n");
        goto CLEANUP;
    }

    const char *display_name;
    if (FAILED(cdecklink_device_get_display_name(device, &display_name))) {
        printf("Failed to get device name\n");
        goto CLEANUP;
    }
    printf("Selected device: %s\n", display_name);
    cdecklink_free_string(display_name);

    cdecklink_output_t *output;
    if (FAILED(cdecklink_device_query_output(device, &output))) {
        printf("Device does not support output\n");
        goto CLEANUP;
    }

    // List the supported modes
    cdecklink_display_mode_iterator_t *mode_iterator;
    if (cdecklink_output_get_display_mode_iterator(output, &mode_iterator) != S_OK) {
        printf("Failed to create output mode iterator\n");
        goto CLEANUP;
    }

    printf("Select videomode:\n");
    cdecklink_display_mode_t *mode;
    int mode_i = 0;
    while (cdecklink_display_mode_iterator_next(mode_iterator, &mode) == S_OK) {
        const char *name;
        if (FAILED(cdecklink_display_mode_get_name(mode, &name))) {
            // TODO
        } else {
            printf("%d: %s\n", mode_i++, name);
            cdecklink_free_string(name);
            cdecklink_display_mode_release(mode);
            mode = NULL;
        }
    }
    cdecklink_display_mode_iterator_release(mode_iterator);
    mode_iterator = NULL;

    index = 7;
    printf("\n");
    scanf("%d", &index);

    // Fetch the selected mode
    if (cdecklink_output_get_display_mode_iterator(output, &mode_iterator) != S_OK) {
        printf("Failed to create output mode iterator\n");
        goto CLEANUP;
    }
    mode_i = -1;
    while (cdecklink_display_mode_iterator_next(mode_iterator, &mode) == S_OK) {
        if (++mode_i == index) {
            break;
        }
        cdecklink_display_mode_release(mode);
        mode = NULL;
    }

    // Create a frame
    long width = cdecklink_display_mode_get_width(mode);
    long height = cdecklink_display_mode_get_height(mode);
    cdecklink_mutable_video_frame_t *mutable_frame;
    if (cdecklink_output_create_video_frame(output, width, height, width * 4, decklinkFormat8BitBGRA,
                                                   decklinkFrameFlagDefault, &mutable_frame) != S_OK) {
        printf("Failed to create output frame\n");
        goto CLEANUP;
    }
    cdecklink_video_frame_t *frame = cdecklink_video_input_frame_to_video_frame(mutable_frame);

    // Fill the frame
    uint8_t *bytes;
    if (cdecklink_video_frame_get_bytes(frame, (void **) (&bytes)) != S_OK) {
        printf("Failed to get frame bytes\n");
        goto CLEANUP;
    }
    for (int o = 0; o < width * height * 4; o += 4) {
        bytes[o] = 255;
        bytes[o + 1] = 120;
        bytes[o + 2] = 0;
        bytes[o + 3] = 255;
    }

    DecklinkDisplayMode mode2 = cdecklink_display_mode_get_display_mode(mode);
    if (cdecklink_output_enable_video_output(output, mode2, decklinkVideoOutputFlagDefault) != S_OK) {
        printf("Failed to enable video output\n");
        goto CLEANUP;
    }

    // Schedule frame
    if (cdecklink_output_display_video_frame_sync(output, frame) != S_OK) {
        printf("Failed to schedule frame\n");
        goto CLEANUP;
    }

    // Wait for termination
    sleep(1);
    printf("Press Any Key to Continue\n");
    scanf("%d", &index);

    CLEANUP:

    if (mutable_frame)
        cdecklink_mutable_video_frame_release(mutable_frame);

    if (mode_iterator)
        cdecklink_display_mode_iterator_release(mode_iterator);

    if (output)
        cdecklink_output_release(output);

    if (device)
        cdecklink_device_release(device);

    if (iterator)
        cdecklink_iterator_release(iterator);

    return 0;
}