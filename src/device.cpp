#include <memory>
#include <atomic>

#include "types.h"

#include "include/device.h"

HRESULT cdecklink_next_device(cdecklink_iterator_t *it, cdecklink_device_t **device) {
    return it->Next(device);
}

void cdecklink_release_device(cdecklink_device_t *device) {
    device->Release();
}

HRESULT cdecklink_device_model_name(cdecklink_device_t *device, const char **name) {
    return device->GetModelName(name);
}

HRESULT cdecklink_device_display_name(cdecklink_device_t *device, const char **name) {
    return device->GetDisplayName(name);
}

/** Output **/

HRESULT cdecklink_device_output_cast(cdecklink_device_t *device, cdecklink_device_output_t **output) {
    // TODO - does this need an AddRef?
    return device->QueryInterface(IID_IDeckLinkOutput, reinterpret_cast<void **>(output));
}

void cdecklink_release_device_output(cdecklink_device_output_t *output) {
    output->Release();
}

HRESULT
cdecklink_device_output_does_support_video_mode(cdecklink_device_output_t *output, BMDDisplayMode displayMode,
                                                BMDPixelFormat pixelFormat,
                                                BMDVideoOutputFlags flags,
                                                BMDDisplayModeSupport *result,
                                                cdecklink_display_mode_t **resultDisplayMode) {
    return output->DoesSupportVideoMode(displayMode, pixelFormat, flags, result, resultDisplayMode);
}

HRESULT cdecklink_device_output_display_mode_iterator(cdecklink_device_output_t *output,
                                                      cdecklink_display_mode_iterator_t **iterator) {
    return output->GetDisplayModeIterator(iterator);
}

/* Video Output */

HRESULT cdecklink_device_output_enable_video_output(cdecklink_device_output_t *output,
                                                    BMDDisplayMode displayMode,
                                                    BMDVideoOutputFlags flags) {
    return output->EnableVideoOutput(displayMode, flags);
}

HRESULT cdecklink_device_output_disable_video_output(cdecklink_device_output_t *output) {
    return output->DisableVideoOutput();
}

HRESULT cdecklink_device_output_create_video_frame(cdecklink_device_output_t *output, int32_t width, int32_t height,
                                                   int32_t rowBytes, BMDPixelFormat pixelFormat, BMDFrameFlags flags,
                                                   cdecklink_mutable_video_frame_t **outFrame) {
    return output->CreateVideoFrame(width, height, rowBytes, pixelFormat, flags, outFrame);
}


HRESULT cdecklink_device_output_create_ancillary_data(cdecklink_device_output_t *output, BMDPixelFormat pixelFormat,
                                                      cdecklink_video_frame_ancillary_t **outBuffer) {
    return output->CreateAncillaryData(pixelFormat, outBuffer);
}

HRESULT
cdecklink_device_output_display_video_frame_sync(cdecklink_device_output_t *output, cdecklink_video_frame_t *frame) {
    return output->DisplayVideoFrameSync(frame);
}

HRESULT
cdecklink_device_output_schedule_video_frame(cdecklink_device_output_t *output, cdecklink_video_frame_t *theFrame,
                                             BMDTimeValue displayTime, BMDTimeValue displayDuration,
                                             BMDTimeScale timeScale) {
    return output->ScheduleVideoFrame(theFrame, displayTime, displayDuration, timeScale);
}

class DeckLinkVideoOutputCallback : public IDeckLinkVideoOutputCallback {
    std::atomic<int> ref_count_{0};
    void *context_;
    cdecklink_callback_schedule_frame_completed *completed_;
    cdecklink_callback_playback_stopped *playback_stopped_;

public:
    DeckLinkVideoOutputCallback(void *context,
                                cdecklink_callback_schedule_frame_completed *completed,
                                cdecklink_callback_playback_stopped *playback_stopped)
            : context_(context),
              completed_(completed),
              playback_stopped_(playback_stopped) {
    }

    // IUnknown

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID, LPVOID *) override { return E_NOINTERFACE; }

    ULONG STDMETHODCALLTYPE AddRef() override { return ++ref_count_; }

    ULONG STDMETHODCALLTYPE Release() override {
        if (--ref_count_ == 0) {
            delete this;
            return 0;
        }

        return ref_count_;
    }

    // IDeckLinkVideoOutputCallback

    HRESULT ScheduledFrameCompleted(/* in */ IDeckLinkVideoFrame *completedFrame, /* in */
                                             BMDOutputFrameCompletionResult result) override {
        if (completed_ != nullptr) {
            return completed_(context_, completedFrame, result);
        }

        return S_FALSE;
    }

    HRESULT ScheduledPlaybackHasStopped() override {
        if (playback_stopped_ != nullptr) {
            return playback_stopped_(context_);
        }

        return S_FALSE;
    }
};

HRESULT cdecklink_device_output_set_scheduled_frame_completion_callback(cdecklink_device_output_t *output,
                                                                        void *context,
                                                                        cdecklink_callback_schedule_frame_completed *completed,
                                                                        cdecklink_callback_playback_stopped *playback_stopped) {
    DeckLinkVideoOutputCallback *handler = nullptr;
    if (completed != nullptr || playback_stopped != nullptr) {
        // TODO - verify ref count
        handler = new DeckLinkVideoOutputCallback(context, completed, playback_stopped);
    }
    return output->SetScheduledFrameCompletionCallback(handler);
}

HRESULT
cdecklink_device_output_buffered_video_frame_count(cdecklink_device_output_t *output, uint32_t *bufferedFrameCount) {
    return output->GetBufferedVideoFrameCount(bufferedFrameCount);
}

/* Audio Output */

HRESULT cdecklink_device_output_enable_audio_output(cdecklink_device_output_t *output, BMDAudioSampleRate sampleRate,
                                                    BMDAudioSampleType sampleType, uint32_t channelCount,
                                                    BMDAudioOutputStreamType streamType) {
    return output->EnableAudioOutput(sampleRate, sampleType, channelCount, streamType);
}

HRESULT cdecklink_device_output_disable_audio_output(cdecklink_device_output_t *output) {
    return output->DisableAudioOutput();
}

HRESULT cdecklink_device_output_write_audio_samples_sync(cdecklink_device_output_t *output, void *buffer,
                                                         uint32_t sampleFrameCount, uint32_t *sampleFramesWritten) {
    return output->WriteAudioSamplesSync(buffer, sampleFrameCount, sampleFramesWritten);
}

HRESULT cdecklink_device_output_begin_audio_preroll(cdecklink_device_output_t *output) {
    return output->BeginAudioPreroll();
}

HRESULT cdecklink_device_output_end_audio_preroll(cdecklink_device_output_t *output) {
    return output->EndAudioPreroll();
}

HRESULT cdecklink_device_output_schedule_audio_samples(cdecklink_device_output_t *output, void *buffer,
                                                       uint32_t sampleFrameCount, BMDTimeValue streamTime,
                                                       BMDTimeScale timeScale, uint32_t *sampleFramesWritten) {
    return output->ScheduleAudioSamples(buffer, sampleFrameCount, streamTime, timeScale, sampleFramesWritten);
}

HRESULT cdecklink_device_output_buffered_audio_sample_frame_count(cdecklink_device_output_t *output,
                                                                  uint32_t *bufferedSampleFrameCount) {
    return output->GetBufferedAudioSampleFrameCount(bufferedSampleFrameCount);
}

HRESULT cdecklink_device_output_flush_buffered_audio_samples(cdecklink_device_output_t *output) {
    return output->FlushBufferedAudioSamples();
}

//virtual HRESULT SetAudioCallback (/* in */ IDeckLinkAudioOutputCallback *theCallback) = 0;

/* Output Control */

HRESULT
cdecklink_device_output_start_scheduled_playback(cdecklink_device_output_t *output, BMDTimeValue playbackStartTime,
                                                 BMDTimeScale timeScale, double playbackSpeed) {
    return output->StartScheduledPlayback(playbackStartTime, timeScale, playbackSpeed);
}

HRESULT
cdecklink_device_output_stop_scheduled_playback(cdecklink_device_output_t *output, BMDTimeValue stopPlaybackAtTime,
                                                BMDTimeValue *actualStopTime, BMDTimeScale timeScale) {
    return output->StopScheduledPlayback(stopPlaybackAtTime, actualStopTime, timeScale);
}

HRESULT cdecklink_device_output_is_scheduled_playback_running(cdecklink_device_output_t *output, bool *active) {
    return output->IsScheduledPlaybackRunning(active);
}

HRESULT cdecklink_device_output_scheduled_stream_time(cdecklink_device_output_t *output, BMDTimeScale desiredTimeScale,
                                                      BMDTimeValue *streamTime, double *playbackSpeed) {
    return output->GetScheduledStreamTime(desiredTimeScale, streamTime, playbackSpeed);
}

HRESULT
cdecklink_device_output_reference_status(cdecklink_device_output_t *output, BMDReferenceStatus *referenceStatus) {
    return output->GetReferenceStatus(referenceStatus);
}

/* Hardware Timing */

HRESULT
cdecklink_device_output_hardware_reference_clock(cdecklink_device_output_t *output, BMDTimeScale desiredTimeScale,
                                                 BMDTimeValue *hardwareTime, BMDTimeValue *timeInFrame,
                                                 BMDTimeValue *ticksPerFrame) {
    return output->GetHardwareReferenceClock(desiredTimeScale, hardwareTime, timeInFrame, ticksPerFrame);
}

HRESULT cdecklink_device_output_frame_completion_reference_timestamp(cdecklink_device_output_t *output,
                                                                     cdecklink_video_frame_t *theFrame,
                                                                     BMDTimeScale desiredTimeScale,
                                                                     BMDTimeValue *frameCompletionTimestamp) {
    return output->GetFrameCompletionReferenceTimestamp(theFrame, desiredTimeScale, frameCompletionTimestamp);
}

/** Input **/

HRESULT cdecklink_device_input_cast(cdecklink_device_t *device, cdecklink_device_input_t **input) {
    // TODO - does this need an AddRef?
    return device->QueryInterface(IID_IDeckLinkInput, reinterpret_cast<void **>(input));
}

void cdecklink_release_device_input(cdecklink_device_input_t *input) {
    input->Release();
}

HRESULT
cdecklink_device_input_does_support_video_mode(cdecklink_device_input_t *input, BMDDisplayMode displayMode,
                                               BMDPixelFormat pixelFormat,
                                               BMDVideoOutputFlags flags,
                                               BMDDisplayModeSupport *result,
                                               cdecklink_display_mode_t **resultDisplayMode) {
    return input->DoesSupportVideoMode(displayMode, pixelFormat, flags, result, resultDisplayMode);
}

HRESULT cdecklink_device_input_display_mode_iterator(cdecklink_device_input_t *input,
                                                     cdecklink_display_mode_iterator_t **iterator) {
    return input->GetDisplayModeIterator(iterator);
}

HRESULT cdecklink_device_input_enable_video_input(cdecklink_device_input_t *input, BMDDisplayMode displayMode,
                                                  BMDPixelFormat pixelFormat, BMDVideoInputFlags flags) {
    return input->EnableVideoInput(displayMode, pixelFormat, flags);
}

HRESULT cdecklink_device_input_disable_video_input(cdecklink_device_input_t *input) {
    return input->DisableVideoInput();
}

HRESULT
cdecklink_device_input_available_video_frame_vount(cdecklink_device_input_t *input, uint32_t *availableFrameCount) {
    return input->GetAvailableVideoFrameCount(availableFrameCount);
}

/* Audio Input */

HRESULT cdecklink_device_input_enable_audio_input(cdecklink_device_input_t *input, BMDAudioSampleRate sampleRate,
                                                  BMDAudioSampleType sampleType, uint32_t channelCount) {
    return input->EnableAudioInput(sampleRate, sampleType, channelCount);
}

HRESULT cdecklink_device_input_disable_audio_input(cdecklink_device_input_t *input) {
    return input->DisableAudioInput();
}

HRESULT cdecklink_device_input_available_audio_sample_frame_count(cdecklink_device_input_t *input,
                                                                  uint32_t *availableSampleFrameCount) {
    return input->GetAvailableAudioSampleFrameCount(availableSampleFrameCount);
}

/* Input Control */

HRESULT cdecklink_device_input_start_streams(cdecklink_device_input_t *input) {
    return input->StartStreams();
}

HRESULT cdecklink_device_input_stop_streams(cdecklink_device_input_t *input) {
    return input->StopStreams();
}

HRESULT cdecklink_device_input_pause_streams(cdecklink_device_input_t *input) {
    return input->PauseStreams();
}

HRESULT cdecklink_device_input_flush_streams(cdecklink_device_input_t *input) {
    return input->FlushStreams();
}


class DeckLinkInputCallback : public IDeckLinkInputCallback {
    std::atomic<int> ref_count_{0};
    void *context_;
    cdecklink_callback_input_format_changed *format_changed_;
    cdecklink_callback_input_frame_arrived *frame_arrived_;

public:
    DeckLinkInputCallback(void *context,
                          cdecklink_callback_input_format_changed *format_changed,
                          cdecklink_callback_input_frame_arrived *frame_arrived)
            : context_(context),
              format_changed_(format_changed),
              frame_arrived_(frame_arrived) {
    }

    // IUnknown

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID, LPVOID *) override { return E_NOINTERFACE; }

    ULONG STDMETHODCALLTYPE AddRef() override { return ++ref_count_; }

    ULONG STDMETHODCALLTYPE Release() override {
        if (--ref_count_ == 0) {
            delete this;
            return 0;
        }

        return ref_count_;
    }

    // IDeckLinkInputCallback

    HRESULT VideoInputFormatChanged(/* in */ BMDVideoInputFormatChangedEvents notificationEvents, /* in */
                                             IDeckLinkDisplayMode *newDisplayMode, /* in */
                                             BMDDetectedVideoInputFormatFlags detectedSignalFlags) override {
        if (format_changed_ != nullptr) {
            return format_changed_(context_, notificationEvents, newDisplayMode, detectedSignalFlags);
        }

        return S_FALSE;
    }

    HRESULT VideoInputFrameArrived(/* in */ IDeckLinkVideoInputFrame *videoFrame, /* in */
                                            IDeckLinkAudioInputPacket *audioPacket) override {
        if (frame_arrived_ != nullptr) {
            return frame_arrived_(context_, videoFrame, audioPacket);
        }

        return S_FALSE;
    }
};


HRESULT cdecklink_device_input_set_callback(cdecklink_device_input_t *input,
                                            void *context,
                                            cdecklink_callback_input_format_changed *format_changed,
                                            cdecklink_callback_input_frame_arrived *frame_arrived) {
    DeckLinkInputCallback *handler = nullptr;
    if (format_changed != nullptr || frame_arrived != nullptr) {
        // TODO - verify ref count
        handler = new DeckLinkInputCallback(context, format_changed, frame_arrived);
    }
    return input->SetCallback(handler);
}

/* Hardware Timing */

HRESULT cdecklink_device_input_hardware_reference_clock(cdecklink_device_input_t *input, BMDTimeScale desiredTimeScale,
                                                        BMDTimeValue *hardwareTime, BMDTimeValue *timeInFrame,
                                                        BMDTimeValue *ticksPerFrame) {
    return input->GetHardwareReferenceClock(desiredTimeScale, hardwareTime, timeInFrame, ticksPerFrame);
}
