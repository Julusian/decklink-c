#ifndef DECKLINK_C_DEVICE_H
#define DECKLINK_C_DEVICE_H

#include "common.h"
#include "display_mode.h"
#include "enums.h"
#include "frame.h"
#include "iterator.h"

#ifdef __cplusplus
extern "C" {
#endif

HRESULT cdecklink_next_device(cdecklink_iterator_t *it, cdecklink_device_t **device);

void cdecklink_release_device(cdecklink_device_t *device);

HRESULT cdecklink_device_model_name(cdecklink_device_t *device, const char **name);

HRESULT cdecklink_device_display_name(cdecklink_device_t *device, const char **name);

/** Output **/

HRESULT cdecklink_device_output_cast(cdecklink_device_t *device, cdecklink_device_output_t **output);

void cdecklink_release_device_output(cdecklink_device_output_t *output);

HRESULT
cdecklink_device_output_does_support_video_mode(cdecklink_device_output_t *output, BMDDisplayMode displayMode,
                                                BMDPixelFormat pixelFormat,
                                                BMDVideoOutputFlags flags,
                                                BMDDisplayModeSupport *result,
                                                cdecklink_display_mode_t **resultDisplayMode);

HRESULT cdecklink_device_output_display_mode_iterator(cdecklink_device_output_t *output,
                                                      cdecklink_display_mode_iterator_t **iterator);

//virtual HRESULT SetScreenPreviewCallback (/* in */ IDeckLinkScreenPreviewCallback *previewCallback) = 0;

/* Video Output */

HRESULT cdecklink_device_output_enable_video_output(cdecklink_device_output_t *output,
                                                    BMDDisplayMode displayMode,
                                                    BMDVideoOutputFlags flags);

HRESULT cdecklink_device_output_disable_video_output(cdecklink_device_output_t *output);

// virtual HRESULT SetVideoOutputFrameMemoryAllocator (/* in */ IDeckLinkMemoryAllocator *theAllocator) = 0;

HRESULT
cdecklink_device_output_create_video_frame(cdecklink_device_output_t *output, int32_t width, int32_t height,
                                           int32_t rowBytes, BMDPixelFormat pixelFormat,
                                           BMDFrameFlags flags, cdecklink_mutable_video_frame_t **outFrame);

HRESULT cdecklink_device_output_create_ancillary_data(cdecklink_device_output_t *output, BMDPixelFormat pixelFormat,
                                                      cdecklink_video_frame_ancillary_t **outBuffer);

HRESULT
cdecklink_device_output_display_video_frame_sync(cdecklink_device_output_t *output, cdecklink_video_frame_t *frame);

HRESULT
cdecklink_device_output_schedule_video_frame(cdecklink_device_output_t *output, cdecklink_video_frame_t *theFrame,
                                             BMDTimeValue displayTime, BMDTimeValue displayDuration,
                                             BMDTimeScale timeScale);

typedef HRESULT cdecklink_callback_schedule_frame_completed(void *context, cdecklink_video_frame_t *frame,
                                                            BMDOutputFrameCompletionResult result);

typedef HRESULT cdecklink_callback_playback_stopped(void *context);

HRESULT cdecklink_device_output_set_scheduled_frame_completion_callback(cdecklink_device_output_t *output,
                                                                        void *context,
                                                                        cdecklink_callback_schedule_frame_completed *completed,
                                                                        cdecklink_callback_playback_stopped *playback_stopped);

HRESULT
cdecklink_device_output_buffered_video_frame_count(cdecklink_device_output_t *output, uint32_t *bufferedFrameCount);

/* Audio Output */

HRESULT cdecklink_device_output_enable_audio_output(cdecklink_device_output_t *output, BMDAudioSampleRate sampleRate,
                                                    BMDAudioSampleType sampleType, uint32_t channelCount,
                                                    BMDAudioOutputStreamType streamType);

HRESULT cdecklink_device_output_disable_audio_output(cdecklink_device_output_t *output);

HRESULT cdecklink_device_output_write_audio_samples_sync(cdecklink_device_output_t *output, void *buffer,
                                                         uint32_t sampleFrameCount, uint32_t *sampleFramesWritten);

HRESULT cdecklink_device_output_begin_audio_preroll(cdecklink_device_output_t *output);

HRESULT cdecklink_device_output_end_audio_preroll(cdecklink_device_output_t *output);

HRESULT cdecklink_device_output_schedule_audio_samples(cdecklink_device_output_t *output, void *buffer,
                                                       uint32_t sampleFrameCount, BMDTimeValue streamTime,
                                                       BMDTimeScale timeScale, uint32_t *sampleFramesWritten);

HRESULT cdecklink_device_output_buffered_audio_sample_frame_count(cdecklink_device_output_t *output,
                                                                  uint32_t *bufferedSampleFrameCount);

HRESULT cdecklink_device_output_flush_buffered_audio_samples(cdecklink_device_output_t *output);


typedef HRESULT cdecklink_callback_render_audio_samples(void *context, bool preroll);

HRESULT cdecklink_device_output_set_audio_callback(cdecklink_device_output_t *output,
                                                   void *context,
                                                   cdecklink_callback_render_audio_samples *format_changed);

/* Output Control */

HRESULT
cdecklink_device_output_start_scheduled_playback(cdecklink_device_output_t *output, BMDTimeValue playbackStartTime,
                                                 BMDTimeScale timeScale, double playbackSpeed);

HRESULT
cdecklink_device_output_stop_scheduled_playback(cdecklink_device_output_t *output, BMDTimeValue stopPlaybackAtTime,
                                                BMDTimeValue *actualStopTime, BMDTimeScale timeScale);

HRESULT cdecklink_device_output_is_scheduled_playback_running(cdecklink_device_output_t *output, bool *active);

HRESULT cdecklink_device_output_scheduled_stream_time(cdecklink_device_output_t *output, BMDTimeScale desiredTimeScale,
                                                      BMDTimeValue *streamTime, double *playbackSpeed);

HRESULT
cdecklink_device_output_reference_status(cdecklink_device_output_t *output, BMDReferenceStatus *referenceStatus);

/* Hardware Timing */

HRESULT
cdecklink_device_output_hardware_reference_clock(cdecklink_device_output_t *output, BMDTimeScale desiredTimeScale,
                                                 BMDTimeValue *hardwareTime,
                                                 BMDTimeValue *timeInFrame, BMDTimeValue *ticksPerFrame);

HRESULT cdecklink_device_output_frame_completion_reference_timestamp(cdecklink_device_output_t *output,
                                                                     cdecklink_video_frame_t *theFrame,
                                                                     BMDTimeScale desiredTimeScale,
                                                                     BMDTimeValue *frameCompletionTimestamp);

/** Input **/

HRESULT cdecklink_device_input_cast(cdecklink_device_t *device, cdecklink_device_input_t **input);

void cdecklink_release_device_input(cdecklink_device_input_t *input);

HRESULT
cdecklink_device_input_does_support_video_mode(cdecklink_device_input_t *input, BMDDisplayMode displayMode,
                                               BMDPixelFormat pixelFormat,
                                               BMDVideoOutputFlags flags,
                                               BMDDisplayModeSupport *result,
                                               cdecklink_display_mode_t **resultDisplayMode);

HRESULT cdecklink_device_input_display_mode_iterator(cdecklink_device_input_t *input,
                                                     cdecklink_display_mode_iterator_t **iterator);

// virtual HRESULT SetScreenPreviewCallback (/* in */ IDeckLinkScreenPreviewCallback *previewCallback) = 0;

/* Video Input */

HRESULT cdecklink_device_input_enable_video_input(cdecklink_device_input_t *input, BMDDisplayMode displayMode,
                                                  BMDPixelFormat pixelFormat, BMDVideoInputFlags flags);

HRESULT cdecklink_device_input_disable_video_input(cdecklink_device_input_t *input);

HRESULT
cdecklink_device_input_available_video_frame_vount(cdecklink_device_input_t *input, uint32_t *availableFrameCount);

//HRESULT SetVideoInputFrameMemoryAllocator (IDeckLinkMemoryAllocator *theAllocator);

/* Audio Input */

HRESULT cdecklink_device_input_enable_audio_input(cdecklink_device_input_t *input, BMDAudioSampleRate sampleRate,
                                                  BMDAudioSampleType sampleType, uint32_t channelCount);

HRESULT cdecklink_device_input_disable_audio_input(cdecklink_device_input_t *input);

HRESULT cdecklink_device_input_available_audio_sample_frame_count(cdecklink_device_input_t *input,
                                                                  uint32_t *availableSampleFrameCount);

/* Input Control */

HRESULT cdecklink_device_input_start_streams(cdecklink_device_input_t *input);

HRESULT cdecklink_device_input_stop_streams(cdecklink_device_input_t *input);

HRESULT cdecklink_device_input_pause_streams(cdecklink_device_input_t *input);

HRESULT cdecklink_device_input_flush_streams(cdecklink_device_input_t *input);


typedef HRESULT cdecklink_callback_input_format_changed(void *context,
                                                        BMDVideoInputFormatChangedEvents notificationEvents,
                                                        cdecklink_display_mode_t *newDisplayMode,
                                                        BMDDetectedVideoInputFormatFlags detectedSignalFlags);

typedef HRESULT cdecklink_callback_input_frame_arrived(void *context, cdecklink_video_input_frame_t *videoFrame,
                                                       cdecklink_audio_input_packet_t *audioPacket);

HRESULT cdecklink_device_input_set_callback(cdecklink_device_input_t *input,
                                            void *context,
                                            cdecklink_callback_input_format_changed *format_changed,
                                            cdecklink_callback_input_frame_arrived *frame_arrived);

/* Hardware Timing */

HRESULT cdecklink_device_input_hardware_reference_clock(cdecklink_device_input_t *input, BMDTimeScale desiredTimeScale,
                                                        BMDTimeValue *hardwareTime, BMDTimeValue *timeInFrame,
                                                        BMDTimeValue *ticksPerFrame);

/** Attributes **/

HRESULT cdecklink_device_attributes_cast(cdecklink_device_t *device, cdecklink_device_attributes_t **attributes);

void cdecklink_release_device_attributes(cdecklink_device_attributes_t *attributes);

HRESULT
cdecklink_device_attributes_flag(cdecklink_device_attributes_t *attributes, BMDDeckLinkAttributeID cfgID, bool *value);

HRESULT cdecklink_device_attributes_int(cdecklink_device_attributes_t *attributes, BMDDeckLinkAttributeID cfgID,
                                        int64_t *value);

HRESULT cdecklink_device_attributes_float(cdecklink_device_attributes_t *attributes, BMDDeckLinkAttributeID cfgID,
                                          double *value);

HRESULT cdecklink_device_attributes_string(cdecklink_device_attributes_t *attributes, BMDDeckLinkAttributeID cfgID,
                                           const char **value);

/** Status **/

HRESULT cdecklink_device_status_cast(cdecklink_device_t *device, cdecklink_device_status_t **status);

void cdecklink_release_device_status(cdecklink_device_status_t *status);

HRESULT
cdecklink_device_status_flag(cdecklink_device_status_t *status, BMDDeckLinkAttributeID cfgID, bool *value);

HRESULT cdecklink_device_status_int(cdecklink_device_status_t *status, BMDDeckLinkAttributeID cfgID,
                                    int64_t *value);

HRESULT cdecklink_device_status_float(cdecklink_device_status_t *status, BMDDeckLinkAttributeID cfgID,
                                      double *value);

HRESULT cdecklink_device_status_string(cdecklink_device_status_t *status, BMDDeckLinkAttributeID cfgID,
                                       const char **value);

HRESULT cdecklink_device_status_bytes(cdecklink_device_status_t *status, BMDDeckLinkAttributeID cfgID,
                                      void *buffer, /* in, out */ uint32_t *bufferSize);

#ifdef __cplusplus
};
#endif

#endif //DECKLINK_C_DEVICE_H
