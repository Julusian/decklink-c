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

//virtual HRESULT CreateAncillaryData (/* in */ BMDPixelFormat pixelFormat, /* out */ IDeckLinkVideoFrameAncillary **outBuffer) = 0;

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

//virtual HRESULT SetAudioCallback (/* in */ IDeckLinkAudioOutputCallback *theCallback) = 0;

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

#ifdef __cplusplus
};
#endif

#endif //DECKLINK_C_DEVICE_H
