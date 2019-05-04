#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "include/decklink_c.h"

bool abort_loop = false;
uint8_t next_blue = 0;
long width = 1920;
long height = 1080;
BMDTimeValue scheduled = 0;

cdecklink_video_frame_t *generate_next_frame(cdecklink_device_output_t *output) {
    cdecklink_mutable_video_frame_t *mutable_frame;
    if (cdecklink_device_output_create_video_frame(output, width, height, width * 4, bmdFormat8BitBGRA,
                                                   bmdFrameFlagDefault, &mutable_frame) != S_OK) {
        printf("Failed to create output frame\n");
        return NULL;
    }

    cdecklink_video_frame_t *frame = cdecklink_video_mutable_frame_base(mutable_frame);

    // Fill the frame
    uint8_t *bytes;
    if (cdecklink_video_frame_bytes(frame, (void **) (&bytes)) != S_OK) {
        printf("Failed to get frame bytes\n");
        cdecklink_destroy_mutable_frame(mutable_frame);
        return NULL;
    }

    for (int o = 0; o < width * height * 4; o += 4) {
        bytes[o] = 255;
        bytes[o + 1] = next_blue;
        bytes[o + 2] = 0;
        bytes[o + 3] = 255;
    }
    next_blue += 10;

    return frame;
}

HRESULT frame_completed(void *context, cdecklink_video_frame_t *frame,
                        BMDOutputFrameCompletionResult result) {
//    printf("frame completed\n");

    if (frame != NULL) {
        cdecklink_destroy_frame(frame); // TODO - leaking the mutable wrapper
    }

    if (context == NULL) {
        printf("No output in callback\n");
        return S_FALSE;
    }
    cdecklink_device_output_t *output = context;

    cdecklink_video_frame_t *next_frame = generate_next_frame(output);
    if (next_frame == NULL) {
        printf("Failed to generate next frame\n");
        return S_FALSE;
    }

    if (cdecklink_device_output_schedule_video_frame(output, next_frame, scheduled, 1000, 25000) != S_OK) {
        printf("Failed to schedule next frame\n");
        return S_FALSE;
    }

    scheduled += 1000;

    return S_OK;
}

HRESULT playback_stopped(void *context) {
    printf("Playback stopped\n");
    return S_OK;
}

int main() {
    cdecklink_iterator_t *iterator = cdecklink_create_iterator();
    if (!iterator)
        goto CLEANUP;

    int index = 3;
    printf("Choose decklink device to output to: ");
    printf("\n");
    scanf("%d", &index);

    // Fetch the selected device
    cdecklink_device_t *device = NULL;
    int i = -1;
    while (cdecklink_next_device(iterator, &device) == S_OK) {
        if (++i == index) {
            break;
        }

        cdecklink_destroy_device(device);
        device = NULL;
    }

    if (i != index || device == NULL) {
        printf("Invalid device index\n");
        goto CLEANUP;
    }

    const char *display_name = cdecklink_device_display_name(device);
    printf("Selected device: %s\n", display_name);
    free((void *) display_name);

    cdecklink_device_output_t *output = cdecklink_device_output_cast(device);
    if (output == NULL) {
        printf("Device does not support output\n");
        goto CLEANUP;
    }

    // List the supported modes
    cdecklink_display_mode_iterator_t *mode_iterator;
    if (cdecklink_device_output_display_mode_iterator(output, &mode_iterator) != S_OK) {
        printf("Failed to create output mode iterator\n");
        goto CLEANUP;
    }

    printf("Select videomode:\n");
    cdecklink_display_mode_t *mode;
    int mode_i = 0;
    while (cdecklink_next_display_mode(mode_iterator, &mode) == S_OK) {
        const char *name = cdecklink_display_mode_name(mode);
        printf("%d: %s\n", mode_i++, name);
        free((void *) name);
        cdecklink_destroy_display_mode(mode);
        mode = NULL;
    }
    cdecklink_destroy_display_mode_iterator(mode_iterator);
    mode_iterator = NULL;

    index = 7;
    printf("\n");
    scanf("%d", &index);

    // Fetch the selected mode
    if (cdecklink_device_output_display_mode_iterator(output, &mode_iterator) != S_OK) {
        printf("Failed to create output mode iterator\n");
        goto CLEANUP;
    }
    mode_i = -1;
    while (cdecklink_next_display_mode(mode_iterator, &mode) == S_OK) {
        if (++mode_i == index) {
            break;
        }
        cdecklink_destroy_display_mode(mode);
        mode = NULL;
    }

    // Create a frame
    width = cdecklink_display_mode_width(mode);
    height = cdecklink_display_mode_height(mode);

    BMDDisplayMode mode2 = cdecklink_display_mode_mode(mode);
    if (cdecklink_device_output_enable_video_output(output, mode2, bmdVideoOutputFlagDefault) != S_OK) {
        printf("Failed to enable video output\n");
        goto CLEANUP;
    }

    // Set the callbacks
    if (cdecklink_device_output_set_scheduled_frame_completion_callback(output, output, &frame_completed,
                                                                        &playback_stopped) !=
        S_OK) {
        printf("Failed to set callback\n");
        goto CLEANUP;
    }

    // Preroll some frames
    for (int j = 0; j < 3; ++j) {
        cdecklink_video_frame_t *frame = generate_next_frame(
                output); // This is being assumed to be freed in the on_complete_callback
        // Schedule frame
        if (cdecklink_device_output_schedule_video_frame(output, frame, scheduled, 1000, 25000) != S_OK) {
            printf("Failed to schedule frame\n");
            goto CLEANUP;
        }
        scheduled += 1000;
    }

    if (cdecklink_device_output_start_scheduled_playback(output, 0, 1000, 1.0) != S_OK) {
        printf("Failed to start playback\n");
        goto CLEANUP;
    }

    // Wait for termination
    sleep(1);
    printf("Press Any Key to Continue\n");
    scanf("%d", &index);


    abort_loop = true;
    BMDTimeValue stopped;
    if (cdecklink_device_output_stop_scheduled_playback(output, 0, &stopped, 1000) != S_OK) {
        printf("Failed to start playback\n");
        goto CLEANUP;
    }

    sleep(1);

    CLEANUP:

//    if (mutable_frame)
//        cdecklink_destroy_mutable_frame(mutable_frame);

    if (mode_iterator)
        cdecklink_destroy_display_mode_iterator(mode_iterator);

    if (output)
        cdecklink_destroy_device_output(output);

    if (device)
        cdecklink_destroy_device(device);

    if (iterator)
        cdecklink_destroy_iterator(iterator);

    return 0;
}