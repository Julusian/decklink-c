#include <memory>
#include <atomic>

#include "structs.h"

#include "include/device.h"

HRESULT cdecklink_next_device(cdecklink_iterator_t *it, cdecklink_device_t **device) {
    if (it != nullptr && it->obj != nullptr) {
        IDeckLink *dev = nullptr;
        auto result = it->obj->Next(&dev);
        if (result == S_OK) {
            *device = (cdecklink_device_t *) malloc(sizeof(cdecklink_device_t));
            (*device)->obj = dev;
        }

        return result;
    }

    return S_FALSE;
}

void cdecklink_destroy_device(cdecklink_device_t *device) {
    if (device != nullptr && device->obj != nullptr) {
        device->obj->Release();
        free(device);
    }
}

const char *cdecklink_device_model_name(cdecklink_device_t *device) {
    if (device != nullptr && device->obj != nullptr) {
        String name;
        if (SUCCEEDED(device->obj->GetModelName(&name))) {
            return name;
        }
    }

    return nullptr;
}

const char *cdecklink_device_display_name(cdecklink_device_t *device) {
    if (device != nullptr && device->obj != nullptr) {
        String name;
        if (SUCCEEDED(device->obj->GetDisplayName(&name))) {
            return name;
        }
    }

    return nullptr;
}

cdecklink_device_output_t *cdecklink_device_output_cast(cdecklink_device_t *device) {
    if (device != nullptr && device->obj != nullptr) {
        IDeckLinkOutput *output;
        if (device->obj->QueryInterface(IID_IDeckLinkOutput, reinterpret_cast<void **>(&output)) == S_OK) {
            auto device2 = (cdecklink_device_output_t *) malloc(sizeof(cdecklink_device_output_t));
            device2->obj = output;

//            auto r = output->AddRef();
//            printf("%d refs\n\n", r);
            return device2;
        }
    }

    return nullptr;
}

void cdecklink_destroy_device_output(cdecklink_device_output_t *output) {
    if (output != nullptr && output->obj != nullptr) {
        output->obj->Release();
        free(output);
    }
}

HRESULT
cdecklink_device_output_does_support_video_mode(cdecklink_device_output_t *output, BMDDisplayMode displayMode,
                                                BMDPixelFormat pixelFormat,
                                                BMDVideoOutputFlags flags,
                                                BMDDisplayModeSupport *result,
                                                cdecklink_display_mode_t **resultDisplayMode) {
    if (output != nullptr && output->obj != nullptr) {
        IDeckLinkDisplayMode *resultDisplayMode2;
        auto res = output->obj->DoesSupportVideoMode(displayMode, pixelFormat, flags, result, &resultDisplayMode2);
        if (res == S_OK) {
            *resultDisplayMode = (cdecklink_display_mode_t *) malloc(sizeof(cdecklink_display_mode_t));
            (*resultDisplayMode)->obj = resultDisplayMode2;
        }

        return res;
    }

    return S_FALSE;
}

HRESULT cdecklink_device_output_display_mode_iterator(cdecklink_device_output_t *output,
                                                      cdecklink_display_mode_iterator_t **iterator) {
    if (output != nullptr && output->obj != nullptr) {
        IDeckLinkDisplayModeIterator *it;
        auto result = output->obj->GetDisplayModeIterator(&it);
        if (result == S_OK) {
            *iterator = (cdecklink_display_mode_iterator_t *) malloc(sizeof(cdecklink_display_mode_iterator_t));
            (*iterator)->obj = it;
        }

        return result;
    }

    return S_FALSE;
}

/* Video Output */

HRESULT cdecklink_device_output_enable_video_output(cdecklink_device_output_t *output,
                                                    BMDDisplayMode displayMode,
                                                    BMDVideoOutputFlags flags) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->EnableVideoOutput(displayMode, flags);
    }

    return S_FALSE;
}

HRESULT cdecklink_device_output_disable_video_output(cdecklink_device_output_t *output) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->DisableVideoOutput();
    }

    return S_FALSE;
}

HRESULT cdecklink_device_output_create_video_frame(cdecklink_device_output_t *output, int32_t width, int32_t height,
                                                   int32_t rowBytes, BMDPixelFormat pixelFormat, BMDFrameFlags flags,
                                                   cdecklink_mutable_video_frame_t **outFrame) {
    if (output != nullptr && output->obj != nullptr) {
        IDeckLinkMutableVideoFrame *outFrame2;
        auto result = output->obj->CreateVideoFrame(width, height, rowBytes, pixelFormat, flags, &outFrame2);
        if (result == S_OK) {
            *outFrame = (cdecklink_mutable_video_frame_t *) malloc(sizeof(cdecklink_mutable_video_frame_t));
            (*outFrame)->obj = outFrame2;
            (*outFrame)->base = (cdecklink_video_frame_t *) malloc(sizeof(cdecklink_video_frame_t));
            (*outFrame)->base->obj = outFrame2;
        }

        return result;
    }

    return S_FALSE;
}

HRESULT
cdecklink_device_output_display_video_frame_sync(cdecklink_device_output_t *output, cdecklink_video_frame_t *frame) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->DisplayVideoFrameSync(frame->obj);
    }

    return S_FALSE;
}

HRESULT
cdecklink_device_output_schedule_video_frame(cdecklink_device_output_t *output, cdecklink_video_frame_t *theFrame,
                                             BMDTimeValue displayTime, BMDTimeValue displayDuration,
                                             BMDTimeScale timeScale) {
    if (output != nullptr && output->obj != nullptr) {
        IDeckLinkVideoFrame *frame = nullptr;
        if (theFrame != nullptr) frame = theFrame->obj;

        return output->obj->ScheduleVideoFrame(frame, displayTime, displayDuration, timeScale);
    }

    return S_FALSE;
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
            auto frame2 = (cdecklink_video_frame_t *) malloc(sizeof(cdecklink_video_frame_t));
            frame2->obj = completedFrame;

            return completed_(context_, frame2, result);
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
    if (output != nullptr && output->obj != nullptr) {
        if (completed != nullptr || playback_stopped != nullptr) {
            auto handler = new DeckLinkVideoOutputCallback(context, completed, playback_stopped);
            return output->obj->SetScheduledFrameCompletionCallback(handler);
        }
    }

    return S_FALSE;
}

HRESULT
cdecklink_device_output_buffered_video_frame_count(cdecklink_device_output_t *output, uint32_t *bufferedFrameCount) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->GetBufferedVideoFrameCount(bufferedFrameCount);
    }

    return S_FALSE;
}

/* Audio Output */

HRESULT cdecklink_device_output_enable_audio_output(cdecklink_device_output_t *output, BMDAudioSampleRate sampleRate,
                                                    BMDAudioSampleType sampleType, uint32_t channelCount,
                                                    BMDAudioOutputStreamType streamType) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->EnableAudioOutput(sampleRate, sampleType, channelCount, streamType);
    }

    return S_FALSE;
}

HRESULT cdecklink_device_output_disable_audio_output(cdecklink_device_output_t *output) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->DisableAudioOutput();
    }

    return S_FALSE;
}

HRESULT cdecklink_device_output_write_audio_samples_sync(cdecklink_device_output_t *output, void *buffer,
                                                         uint32_t sampleFrameCount, uint32_t *sampleFramesWritten) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->WriteAudioSamplesSync(buffer, sampleFrameCount, sampleFramesWritten);
    }

    return S_FALSE;
}

HRESULT cdecklink_device_output_begin_audio_preroll(cdecklink_device_output_t *output) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->BeginAudioPreroll();
    }

    return S_FALSE;
}

HRESULT cdecklink_device_output_end_audio_preroll(cdecklink_device_output_t *output) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->EndAudioPreroll();
    }

    return S_FALSE;
}

HRESULT cdecklink_device_output_schedule_audio_samples(cdecklink_device_output_t *output, void *buffer,
                                                       uint32_t sampleFrameCount, BMDTimeValue streamTime,
                                                       BMDTimeScale timeScale, uint32_t *sampleFramesWritten) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->ScheduleAudioSamples(buffer, sampleFrameCount, streamTime, timeScale, sampleFramesWritten);
    }

    return S_FALSE;
}

HRESULT cdecklink_device_output_buffered_audio_sample_frame_count(cdecklink_device_output_t *output,
                                                                  uint32_t *bufferedSampleFrameCount) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->GetBufferedAudioSampleFrameCount(bufferedSampleFrameCount);
    }

    return S_FALSE;
}

HRESULT cdecklink_device_output_flush_buffered_audio_samples(cdecklink_device_output_t *output) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->FlushBufferedAudioSamples();
    }

    return S_FALSE;
}

//virtual HRESULT SetAudioCallback (/* in */ IDeckLinkAudioOutputCallback *theCallback) = 0;

/* Output Control */

HRESULT
cdecklink_device_output_start_scheduled_playback(cdecklink_device_output_t *output, BMDTimeValue playbackStartTime,
                                                 BMDTimeScale timeScale, double playbackSpeed) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->StartScheduledPlayback(playbackStartTime, timeScale, playbackSpeed);
    }

    return S_FALSE;
}

HRESULT
cdecklink_device_output_stop_scheduled_playback(cdecklink_device_output_t *output, BMDTimeValue stopPlaybackAtTime,
                                                BMDTimeValue *actualStopTime, BMDTimeScale timeScale) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->StopScheduledPlayback(stopPlaybackAtTime, actualStopTime, timeScale);
    }

    return S_FALSE;
}

HRESULT cdecklink_device_output_is_scheduled_playback_running(cdecklink_device_output_t *output, bool *active) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->IsScheduledPlaybackRunning(active);
    }

    return S_FALSE;
}

HRESULT cdecklink_device_output_scheduled_stream_time(cdecklink_device_output_t *output, BMDTimeScale desiredTimeScale,
                                                      BMDTimeValue *streamTime, double *playbackSpeed) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->GetScheduledStreamTime(desiredTimeScale, streamTime, playbackSpeed);
    }

    return S_FALSE;
}

HRESULT
cdecklink_device_output_reference_status(cdecklink_device_output_t *output, BMDReferenceStatus *referenceStatus) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->GetReferenceStatus(referenceStatus);
    }

    return S_FALSE;
}

/* Hardware Timing */

HRESULT
cdecklink_device_output_hardware_reference_clock(cdecklink_device_output_t *output, BMDTimeScale desiredTimeScale,
                                                 BMDTimeValue *hardwareTime, BMDTimeValue *timeInFrame,
                                                 BMDTimeValue *ticksPerFrame) {
    if (output != nullptr && output->obj != nullptr) {
        return output->obj->GetHardwareReferenceClock(desiredTimeScale, hardwareTime, timeInFrame, ticksPerFrame);
    }

    return S_FALSE;
}

HRESULT cdecklink_device_output_frame_completion_reference_timestamp(cdecklink_device_output_t *output,
                                                                     cdecklink_video_frame_t *theFrame,
                                                                     BMDTimeScale desiredTimeScale,
                                                                     BMDTimeValue *frameCompletionTimestamp) {
    if (output != nullptr && output->obj != nullptr) {
        IDeckLinkVideoFrame *frame;
        if (theFrame != nullptr) frame = theFrame->obj;

        return output->obj->GetFrameCompletionReferenceTimestamp(frame, desiredTimeScale, frameCompletionTimestamp);
    }

    return S_FALSE;
}
