#include <atomic>
#include "types.h"
#include "../include/decklink_c.h"

class DeckLinkDeckControlStatusCallback final : public IDeckLinkDeckControlStatusCallback {
	std::atomic<int> ref_count_{0};
	void *ctx_;
	cdecklink_deck_control_status_callback_timecode_update *cb0_;
	cdecklink_deck_control_status_callback_vtr_control_state_changed *cb1_;
	cdecklink_deck_control_status_callback_deck_control_event_received *cb2_;
	cdecklink_deck_control_status_callback_deck_control_status_changed *cb3_;

public:
	DeckLinkDeckControlStatusCallback (void *ctx, cdecklink_deck_control_status_callback_timecode_update *cb0, cdecklink_deck_control_status_callback_vtr_control_state_changed *cb1, cdecklink_deck_control_status_callback_deck_control_event_received *cb2, cdecklink_deck_control_status_callback_deck_control_status_changed *cb3)
	: ctx_(ctx), cb0_(cb0), cb1_(cb1), cb2_(cb2), cb3_(cb3) {}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID, LPVOID *) override { return E_NOINTERFACE; }
	ULONG STDMETHODCALLTYPE AddRef() override { return ++ref_count_; }
	ULONG STDMETHODCALLTYPE Release() override {
		if (--ref_count_ == 0) {
			delete this;
			return 0;
		}
		return ref_count_;
	}

	HRESULT TimecodeUpdate(BMDTimecodeBCD currentTimecode) override {
		if (cb0_ != nullptr) {
			return cb0_(ctx_, currentTimecode);
		}
		return S_FALSE;
	}

	HRESULT VTRControlStateChanged(BMDDeckControlVTRControlState newState, BMDDeckControlError error) override {
		if (cb1_ != nullptr) {
			return cb1_(ctx_, newState, error);
		}
		return S_FALSE;
	}

	HRESULT DeckControlEventReceived(BMDDeckControlEvent event, BMDDeckControlError error) override {
		if (cb2_ != nullptr) {
			return cb2_(ctx_, event, error);
		}
		return S_FALSE;
	}

	HRESULT DeckControlStatusChanged(BMDDeckControlStatusFlags flags, uint32_t mask) override {
		if (cb3_ != nullptr) {
			return cb3_(ctx_, flags, mask);
		}
		return S_FALSE;
	}

};

class DeckLinkVideoOutputCallback final : public IDeckLinkVideoOutputCallback {
	std::atomic<int> ref_count_{0};
	void *ctx_;
	cdecklink_video_output_callback_scheduled_frame_completed *cb0_;
	cdecklink_video_output_callback_scheduled_playback_has_stopped *cb1_;

public:
	DeckLinkVideoOutputCallback (void *ctx, cdecklink_video_output_callback_scheduled_frame_completed *cb0, cdecklink_video_output_callback_scheduled_playback_has_stopped *cb1)
	: ctx_(ctx), cb0_(cb0), cb1_(cb1) {}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID, LPVOID *) override { return E_NOINTERFACE; }
	ULONG STDMETHODCALLTYPE AddRef() override { return ++ref_count_; }
	ULONG STDMETHODCALLTYPE Release() override {
		if (--ref_count_ == 0) {
			delete this;
			return 0;
		}
		return ref_count_;
	}

	HRESULT ScheduledFrameCompleted(IDeckLinkVideoFrame * completedFrame, BMDOutputFrameCompletionResult result) override {
		if (cb0_ != nullptr) {
			return cb0_(ctx_, completedFrame, result);
		}
		return S_FALSE;
	}

	HRESULT ScheduledPlaybackHasStopped() override {
		if (cb1_ != nullptr) {
			return cb1_(ctx_);
		}
		return S_FALSE;
	}

};

class DeckLinkInputCallback final : public IDeckLinkInputCallback {
	std::atomic<int> ref_count_{0};
	void *ctx_;
	cdecklink_input_callback_video_input_format_changed *cb0_;
	cdecklink_input_callback_video_input_frame_arrived *cb1_;

public:
	DeckLinkInputCallback (void *ctx, cdecklink_input_callback_video_input_format_changed *cb0, cdecklink_input_callback_video_input_frame_arrived *cb1)
	: ctx_(ctx), cb0_(cb0), cb1_(cb1) {}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID, LPVOID *) override { return E_NOINTERFACE; }
	ULONG STDMETHODCALLTYPE AddRef() override { return ++ref_count_; }
	ULONG STDMETHODCALLTYPE Release() override {
		if (--ref_count_ == 0) {
			delete this;
			return 0;
		}
		return ref_count_;
	}

	HRESULT VideoInputFormatChanged(BMDVideoInputFormatChangedEvents notificationEvents, IDeckLinkDisplayMode * newDisplayMode, BMDDetectedVideoInputFormatFlags detectedSignalFlags) override {
		if (cb0_ != nullptr) {
			return cb0_(ctx_, notificationEvents, newDisplayMode, detectedSignalFlags);
		}
		return S_FALSE;
	}

	HRESULT VideoInputFrameArrived(IDeckLinkVideoInputFrame * videoFrame, IDeckLinkAudioInputPacket * audioPacket) override {
		if (cb1_ != nullptr) {
			return cb1_(ctx_, videoFrame, audioPacket);
		}
		return S_FALSE;
	}

};

class DeckLinkEncoderInputCallback final : public IDeckLinkEncoderInputCallback {
	std::atomic<int> ref_count_{0};
	void *ctx_;
	cdecklink_encoder_input_callback_video_input_signal_changed *cb0_;
	cdecklink_encoder_input_callback_video_packet_arrived *cb1_;
	cdecklink_encoder_input_callback_audio_packet_arrived *cb2_;

public:
	DeckLinkEncoderInputCallback (void *ctx, cdecklink_encoder_input_callback_video_input_signal_changed *cb0, cdecklink_encoder_input_callback_video_packet_arrived *cb1, cdecklink_encoder_input_callback_audio_packet_arrived *cb2)
	: ctx_(ctx), cb0_(cb0), cb1_(cb1), cb2_(cb2) {}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID, LPVOID *) override { return E_NOINTERFACE; }
	ULONG STDMETHODCALLTYPE AddRef() override { return ++ref_count_; }
	ULONG STDMETHODCALLTYPE Release() override {
		if (--ref_count_ == 0) {
			delete this;
			return 0;
		}
		return ref_count_;
	}

	HRESULT VideoInputSignalChanged(BMDVideoInputFormatChangedEvents notificationEvents, IDeckLinkDisplayMode * newDisplayMode, BMDDetectedVideoInputFormatFlags detectedSignalFlags) override {
		if (cb0_ != nullptr) {
			return cb0_(ctx_, notificationEvents, newDisplayMode, detectedSignalFlags);
		}
		return S_FALSE;
	}

	HRESULT VideoPacketArrived(IDeckLinkEncoderVideoPacket * videoPacket) override {
		if (cb1_ != nullptr) {
			return cb1_(ctx_, videoPacket);
		}
		return S_FALSE;
	}

	HRESULT AudioPacketArrived(IDeckLinkEncoderAudioPacket * audioPacket) override {
		if (cb2_ != nullptr) {
			return cb2_(ctx_, audioPacket);
		}
		return S_FALSE;
	}

};

class DeckLinkAudioOutputCallback final : public IDeckLinkAudioOutputCallback {
	std::atomic<int> ref_count_{0};
	void *ctx_;
	cdecklink_audio_output_callback_render_audio_samples *cb0_;

public:
	DeckLinkAudioOutputCallback (void *ctx, cdecklink_audio_output_callback_render_audio_samples *cb0)
	: ctx_(ctx), cb0_(cb0) {}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID, LPVOID *) override { return E_NOINTERFACE; }
	ULONG STDMETHODCALLTYPE AddRef() override { return ++ref_count_; }
	ULONG STDMETHODCALLTYPE Release() override {
		if (--ref_count_ == 0) {
			delete this;
			return 0;
		}
		return ref_count_;
	}

	HRESULT RenderAudioSamples(bool preroll) override {
		if (cb0_ != nullptr) {
			return cb0_(ctx_, preroll);
		}
		return S_FALSE;
	}

};

class DeckLinkScreenPreviewCallback final : public IDeckLinkScreenPreviewCallback {
	std::atomic<int> ref_count_{0};
	void *ctx_;
	cdecklink_screen_preview_callback_draw_frame *cb0_;

public:
	DeckLinkScreenPreviewCallback (void *ctx, cdecklink_screen_preview_callback_draw_frame *cb0)
	: ctx_(ctx), cb0_(cb0) {}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID, LPVOID *) override { return E_NOINTERFACE; }
	ULONG STDMETHODCALLTYPE AddRef() override { return ++ref_count_; }
	ULONG STDMETHODCALLTYPE Release() override {
		if (--ref_count_ == 0) {
			delete this;
			return 0;
		}
		return ref_count_;
	}

	HRESULT DrawFrame(IDeckLinkVideoFrame * theFrame) override {
		if (cb0_ != nullptr) {
			return cb0_(ctx_, theFrame);
		}
		return S_FALSE;
	}

};

class DeckLinkNotificationCallback final : public IDeckLinkNotificationCallback {
	std::atomic<int> ref_count_{0};
	void *ctx_;
	cdecklink_notification_callback_notify *cb0_;

public:
	DeckLinkNotificationCallback (void *ctx, cdecklink_notification_callback_notify *cb0)
	: ctx_(ctx), cb0_(cb0) {}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID, LPVOID *) override { return E_NOINTERFACE; }
	ULONG STDMETHODCALLTYPE AddRef() override { return ++ref_count_; }
	ULONG STDMETHODCALLTYPE Release() override {
		if (--ref_count_ == 0) {
			delete this;
			return 0;
		}
		return ref_count_;
	}

	HRESULT Notify(BMDNotifications topic, uint64_t param1, uint64_t param2) override {
		if (cb0_ != nullptr) {
			return cb0_(ctx_, topic, param1, param2);
		}
		return S_FALSE;
	}

};

class DeckLinkDeviceNotificationCallback final : public IDeckLinkDeviceNotificationCallback {
	std::atomic<int> ref_count_{0};
	void *ctx_;
	cdecklink_device_notification_callback_deck_link_device_arrived *cb0_;
	cdecklink_device_notification_callback_deck_link_device_removed *cb1_;

public:
	DeckLinkDeviceNotificationCallback (void *ctx, cdecklink_device_notification_callback_deck_link_device_arrived *cb0, cdecklink_device_notification_callback_deck_link_device_removed *cb1)
	: ctx_(ctx), cb0_(cb0), cb1_(cb1) {}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID, LPVOID *) override { return E_NOINTERFACE; }
	ULONG STDMETHODCALLTYPE AddRef() override { return ++ref_count_; }
	ULONG STDMETHODCALLTYPE Release() override {
		if (--ref_count_ == 0) {
			delete this;
			return 0;
		}
		return ref_count_;
	}

	HRESULT DeckLinkDeviceArrived(IDeckLink * deckLinkDevice) override {
		if (cb0_ != nullptr) {
			return cb0_(ctx_, deckLinkDevice);
		}
		return S_FALSE;
	}

	HRESULT DeckLinkDeviceRemoved(IDeckLink * deckLinkDevice) override {
		if (cb1_ != nullptr) {
			return cb1_(ctx_, deckLinkDevice);
		}
		return S_FALSE;
	}

};

unsigned long cdecklink_timecode_add_ref(cdecklink_timecode_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_timecode_release(cdecklink_timecode_t *obj) {
	return obj->Release();
}

DecklinkTimecodeBCD cdecklink_timecode_get_bcd(cdecklink_timecode_t *obj) {
	return obj->GetBCD();
}

HRESULT cdecklink_timecode_get_components(cdecklink_timecode_t *obj, uint8_t * hours, uint8_t * minutes, uint8_t * seconds, uint8_t * frames) {
	return obj->GetComponents(hours, minutes, seconds, frames);
}

HRESULT cdecklink_timecode_get_string(cdecklink_timecode_t *obj, const char ** timecode) {
	return obj->GetString(timecode);
}

DecklinkTimecodeFlags cdecklink_timecode_get_flags(cdecklink_timecode_t *obj) {
	return obj->GetFlags();
}

HRESULT cdecklink_timecode_get_timecode_user_bits(cdecklink_timecode_t *obj, DecklinkTimecodeUserBits * userBits) {
	return obj->GetTimecodeUserBits(userBits);
}


unsigned long cdecklink_display_mode_iterator_add_ref(cdecklink_display_mode_iterator_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_display_mode_iterator_release(cdecklink_display_mode_iterator_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_display_mode_iterator_next(cdecklink_display_mode_iterator_t *obj, cdecklink_display_mode_t ** deckLinkDisplayMode) {
	return obj->Next(deckLinkDisplayMode);
}


unsigned long cdecklink_display_mode_add_ref(cdecklink_display_mode_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_display_mode_release(cdecklink_display_mode_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_display_mode_get_name(cdecklink_display_mode_t *obj, const char ** name) {
	return obj->GetName(name);
}

DecklinkDisplayMode cdecklink_display_mode_get_display_mode(cdecklink_display_mode_t *obj) {
	return obj->GetDisplayMode();
}

long cdecklink_display_mode_get_width(cdecklink_display_mode_t *obj) {
	return obj->GetWidth();
}

long cdecklink_display_mode_get_height(cdecklink_display_mode_t *obj) {
	return obj->GetHeight();
}

HRESULT cdecklink_display_mode_get_frame_rate(cdecklink_display_mode_t *obj, DecklinkTimeValue * frameDuration, DecklinkTimeScale * timeScale) {
	return obj->GetFrameRate(frameDuration, timeScale);
}

DecklinkFieldDominance cdecklink_display_mode_get_field_dominance(cdecklink_display_mode_t *obj) {
	return obj->GetFieldDominance();
}

DecklinkDisplayModeFlags cdecklink_display_mode_get_flags(cdecklink_display_mode_t *obj) {
	return obj->GetFlags();
}


unsigned long cdecklink_device_add_ref(cdecklink_device_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_device_release(cdecklink_device_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_device_get_model_name(cdecklink_device_t *obj, const char ** modelName) {
	return obj->GetModelName(modelName);
}

HRESULT cdecklink_device_get_display_name(cdecklink_device_t *obj, const char ** displayName) {
	return obj->GetDisplayName(displayName);
}


unsigned long cdecklink_configuration_add_ref(cdecklink_configuration_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_configuration_release(cdecklink_configuration_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_configuration_set_flag(cdecklink_configuration_t *obj, DecklinkConfigurationID cfgID, bool value) {
	return obj->SetFlag(cfgID, value);
}

HRESULT cdecklink_configuration_get_flag(cdecklink_configuration_t *obj, DecklinkConfigurationID cfgID, bool * value) {
	return obj->GetFlag(cfgID, value);
}

HRESULT cdecklink_configuration_set_int(cdecklink_configuration_t *obj, DecklinkConfigurationID cfgID, int64_t value) {
	return obj->SetInt(cfgID, value);
}

HRESULT cdecklink_configuration_get_int(cdecklink_configuration_t *obj, DecklinkConfigurationID cfgID, int64_t * value) {
	return obj->GetInt(cfgID, value);
}

HRESULT cdecklink_configuration_set_float(cdecklink_configuration_t *obj, DecklinkConfigurationID cfgID, double value) {
	return obj->SetFloat(cfgID, value);
}

HRESULT cdecklink_configuration_get_float(cdecklink_configuration_t *obj, DecklinkConfigurationID cfgID, double * value) {
	return obj->GetFloat(cfgID, value);
}

HRESULT cdecklink_configuration_set_string(cdecklink_configuration_t *obj, DecklinkConfigurationID cfgID, const char * value) {
	return obj->SetString(cfgID, value);
}

HRESULT cdecklink_configuration_get_string(cdecklink_configuration_t *obj, DecklinkConfigurationID cfgID, const char ** value) {
	return obj->GetString(cfgID, value);
}

HRESULT cdecklink_configuration_write_configuration_to_preferences(cdecklink_configuration_t *obj) {
	return obj->WriteConfigurationToPreferences();
}


unsigned long cdecklink_encoder_configuration_add_ref(cdecklink_encoder_configuration_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_encoder_configuration_release(cdecklink_encoder_configuration_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_encoder_configuration_set_flag(cdecklink_encoder_configuration_t *obj, DecklinkEncoderConfigurationID cfgID, bool value) {
	return obj->SetFlag(cfgID, value);
}

HRESULT cdecklink_encoder_configuration_get_flag(cdecklink_encoder_configuration_t *obj, DecklinkEncoderConfigurationID cfgID, bool * value) {
	return obj->GetFlag(cfgID, value);
}

HRESULT cdecklink_encoder_configuration_set_int(cdecklink_encoder_configuration_t *obj, DecklinkEncoderConfigurationID cfgID, int64_t value) {
	return obj->SetInt(cfgID, value);
}

HRESULT cdecklink_encoder_configuration_get_int(cdecklink_encoder_configuration_t *obj, DecklinkEncoderConfigurationID cfgID, int64_t * value) {
	return obj->GetInt(cfgID, value);
}

HRESULT cdecklink_encoder_configuration_set_float(cdecklink_encoder_configuration_t *obj, DecklinkEncoderConfigurationID cfgID, double value) {
	return obj->SetFloat(cfgID, value);
}

HRESULT cdecklink_encoder_configuration_get_float(cdecklink_encoder_configuration_t *obj, DecklinkEncoderConfigurationID cfgID, double * value) {
	return obj->GetFloat(cfgID, value);
}

HRESULT cdecklink_encoder_configuration_set_string(cdecklink_encoder_configuration_t *obj, DecklinkEncoderConfigurationID cfgID, const char * value) {
	return obj->SetString(cfgID, value);
}

HRESULT cdecklink_encoder_configuration_get_string(cdecklink_encoder_configuration_t *obj, DecklinkEncoderConfigurationID cfgID, const char ** value) {
	return obj->GetString(cfgID, value);
}

HRESULT cdecklink_encoder_configuration_get_bytes(cdecklink_encoder_configuration_t *obj, DecklinkEncoderConfigurationID cfgID, void * buffer, uint32_t * bufferSize) {
	return obj->GetBytes(cfgID, buffer, bufferSize);
}


unsigned long cdecklink_deck_control_add_ref(cdecklink_deck_control_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_deck_control_release(cdecklink_deck_control_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_deck_control_open(cdecklink_deck_control_t *obj, DecklinkTimeScale timeScale, DecklinkTimeValue timeValue, bool timecodeIsDropFrame, DecklinkDeckControlError * error) {
	return obj->Open(timeScale, timeValue, timecodeIsDropFrame, error);
}

HRESULT cdecklink_deck_control_close(cdecklink_deck_control_t *obj, bool standbyOn) {
	return obj->Close(standbyOn);
}

HRESULT cdecklink_deck_control_get_current_state(cdecklink_deck_control_t *obj, DecklinkDeckControlMode * mode, DecklinkDeckControlVTRControlState * vtrControlState, DecklinkDeckControlStatusFlags * flags) {
	return obj->GetCurrentState(mode, vtrControlState, flags);
}

HRESULT cdecklink_deck_control_set_standby(cdecklink_deck_control_t *obj, bool standbyOn) {
	return obj->SetStandby(standbyOn);
}

HRESULT cdecklink_deck_control_send_command(cdecklink_deck_control_t *obj, uint8_t * inBuffer, uint32_t inBufferSize, uint8_t * outBuffer, uint32_t * outDataSize, uint32_t outBufferSize, DecklinkDeckControlError * error) {
	return obj->SendCommand(inBuffer, inBufferSize, outBuffer, outDataSize, outBufferSize, error);
}

HRESULT cdecklink_deck_control_play(cdecklink_deck_control_t *obj, DecklinkDeckControlError * error) {
	return obj->Play(error);
}

HRESULT cdecklink_deck_control_stop(cdecklink_deck_control_t *obj, DecklinkDeckControlError * error) {
	return obj->Stop(error);
}

HRESULT cdecklink_deck_control_toggle_play_stop(cdecklink_deck_control_t *obj, DecklinkDeckControlError * error) {
	return obj->TogglePlayStop(error);
}

HRESULT cdecklink_deck_control_eject(cdecklink_deck_control_t *obj, DecklinkDeckControlError * error) {
	return obj->Eject(error);
}

HRESULT cdecklink_deck_control_go_to_timecode(cdecklink_deck_control_t *obj, DecklinkTimecodeBCD timecode, DecklinkDeckControlError * error) {
	return obj->GoToTimecode(timecode, error);
}

HRESULT cdecklink_deck_control_fast_forward(cdecklink_deck_control_t *obj, bool viewTape, DecklinkDeckControlError * error) {
	return obj->FastForward(viewTape, error);
}

HRESULT cdecklink_deck_control_rewind(cdecklink_deck_control_t *obj, bool viewTape, DecklinkDeckControlError * error) {
	return obj->Rewind(viewTape, error);
}

HRESULT cdecklink_deck_control_step_forward(cdecklink_deck_control_t *obj, DecklinkDeckControlError * error) {
	return obj->StepForward(error);
}

HRESULT cdecklink_deck_control_step_back(cdecklink_deck_control_t *obj, DecklinkDeckControlError * error) {
	return obj->StepBack(error);
}

HRESULT cdecklink_deck_control_jog(cdecklink_deck_control_t *obj, double rate, DecklinkDeckControlError * error) {
	return obj->Jog(rate, error);
}

HRESULT cdecklink_deck_control_shuttle(cdecklink_deck_control_t *obj, double rate, DecklinkDeckControlError * error) {
	return obj->Shuttle(rate, error);
}

HRESULT cdecklink_deck_control_get_timecode_string(cdecklink_deck_control_t *obj, const char ** currentTimeCode, DecklinkDeckControlError * error) {
	return obj->GetTimecodeString(currentTimeCode, error);
}

HRESULT cdecklink_deck_control_get_timecode(cdecklink_deck_control_t *obj, cdecklink_timecode_t ** currentTimecode, DecklinkDeckControlError * error) {
	return obj->GetTimecode(currentTimecode, error);
}

HRESULT cdecklink_deck_control_get_timecode_bcd(cdecklink_deck_control_t *obj, DecklinkTimecodeBCD * currentTimecode, DecklinkDeckControlError * error) {
	return obj->GetTimecodeBCD(currentTimecode, error);
}

HRESULT cdecklink_deck_control_set_preroll(cdecklink_deck_control_t *obj, uint32_t prerollSeconds) {
	return obj->SetPreroll(prerollSeconds);
}

HRESULT cdecklink_deck_control_get_preroll(cdecklink_deck_control_t *obj, uint32_t * prerollSeconds) {
	return obj->GetPreroll(prerollSeconds);
}

HRESULT cdecklink_deck_control_set_export_offset(cdecklink_deck_control_t *obj, int32_t exportOffsetFields) {
	return obj->SetExportOffset(exportOffsetFields);
}

HRESULT cdecklink_deck_control_get_export_offset(cdecklink_deck_control_t *obj, int32_t * exportOffsetFields) {
	return obj->GetExportOffset(exportOffsetFields);
}

HRESULT cdecklink_deck_control_get_manual_export_offset(cdecklink_deck_control_t *obj, int32_t * deckManualExportOffsetFields) {
	return obj->GetManualExportOffset(deckManualExportOffsetFields);
}

HRESULT cdecklink_deck_control_set_capture_offset(cdecklink_deck_control_t *obj, int32_t captureOffsetFields) {
	return obj->SetCaptureOffset(captureOffsetFields);
}

HRESULT cdecklink_deck_control_get_capture_offset(cdecklink_deck_control_t *obj, int32_t * captureOffsetFields) {
	return obj->GetCaptureOffset(captureOffsetFields);
}

HRESULT cdecklink_deck_control_start_export(cdecklink_deck_control_t *obj, DecklinkTimecodeBCD inTimecode, DecklinkTimecodeBCD outTimecode, DecklinkDeckControlExportModeOpsFlags exportModeOps, DecklinkDeckControlError * error) {
	return obj->StartExport(inTimecode, outTimecode, exportModeOps, error);
}

HRESULT cdecklink_deck_control_start_capture(cdecklink_deck_control_t *obj, bool useVITC, DecklinkTimecodeBCD inTimecode, DecklinkTimecodeBCD outTimecode, DecklinkDeckControlError * error) {
	return obj->StartCapture(useVITC, inTimecode, outTimecode, error);
}

HRESULT cdecklink_deck_control_get_device_id(cdecklink_deck_control_t *obj, uint16_t * deviceId, DecklinkDeckControlError * error) {
	return obj->GetDeviceID(deviceId, error);
}

HRESULT cdecklink_deck_control_abort(cdecklink_deck_control_t *obj) {
	return obj->Abort();
}

HRESULT cdecklink_deck_control_crash_record_start(cdecklink_deck_control_t *obj, DecklinkDeckControlError * error) {
	return obj->CrashRecordStart(error);
}

HRESULT cdecklink_deck_control_crash_record_stop(cdecklink_deck_control_t *obj, DecklinkDeckControlError * error) {
	return obj->CrashRecordStop(error);
}

HRESULT cdecklink_deck_control_set_callback(cdecklink_deck_control_t *obj, void *ctx, cdecklink_deck_control_status_callback_timecode_update* cb0, cdecklink_deck_control_status_callback_vtr_control_state_changed* cb1, cdecklink_deck_control_status_callback_deck_control_event_received* cb2, cdecklink_deck_control_status_callback_deck_control_status_changed* cb3) {
	IDeckLinkDeckControlStatusCallback * handler = nullptr;
	if (cb0 != nullptr && cb1 != nullptr && cb2 != nullptr && cb3 != nullptr) {
		handler = new DeckLinkDeckControlStatusCallback(ctx, cb0, cb1, cb2, cb3);
	}
	return obj->SetCallback(handler);
}


unsigned long cdecklink_memory_allocator_add_ref(cdecklink_memory_allocator_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_memory_allocator_release(cdecklink_memory_allocator_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_memory_allocator_allocate_buffer(cdecklink_memory_allocator_t *obj, uint32_t bufferSize, void ** allocatedBuffer) {
	return obj->AllocateBuffer(bufferSize, allocatedBuffer);
}

HRESULT cdecklink_memory_allocator_release_buffer(cdecklink_memory_allocator_t *obj, void * buffer) {
	return obj->ReleaseBuffer(buffer);
}

HRESULT cdecklink_memory_allocator_commit(cdecklink_memory_allocator_t *obj) {
	return obj->Commit();
}

HRESULT cdecklink_memory_allocator_decommit(cdecklink_memory_allocator_t *obj) {
	return obj->Decommit();
}


unsigned long cdecklink_iterator_add_ref(cdecklink_iterator_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_iterator_release(cdecklink_iterator_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_iterator_next(cdecklink_iterator_t *obj, cdecklink_device_t ** deckLinkInstance) {
	return obj->Next(deckLinkInstance);
}


unsigned long cdecklink_api_information_add_ref(cdecklink_api_information_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_api_information_release(cdecklink_api_information_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_api_information_get_flag(cdecklink_api_information_t *obj, DecklinkAPIInformationID cfgID, bool * value) {
	return obj->GetFlag(cfgID, value);
}

HRESULT cdecklink_api_information_get_int(cdecklink_api_information_t *obj, DecklinkAPIInformationID cfgID, int64_t * value) {
	return obj->GetInt(cfgID, value);
}

HRESULT cdecklink_api_information_get_float(cdecklink_api_information_t *obj, DecklinkAPIInformationID cfgID, double * value) {
	return obj->GetFloat(cfgID, value);
}

HRESULT cdecklink_api_information_get_string(cdecklink_api_information_t *obj, DecklinkAPIInformationID cfgID, const char ** value) {
	return obj->GetString(cfgID, value);
}


unsigned long cdecklink_output_add_ref(cdecklink_output_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_output_release(cdecklink_output_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_output_does_support_video_mode(cdecklink_output_t *obj, DecklinkDisplayMode displayMode, DecklinkPixelFormat pixelFormat, DecklinkVideoOutputFlags flags, DecklinkDisplayModeSupport * result, cdecklink_display_mode_t ** resultDisplayMode) {
	return obj->DoesSupportVideoMode(displayMode, pixelFormat, flags, result, resultDisplayMode);
}

HRESULT cdecklink_output_get_display_mode_iterator(cdecklink_output_t *obj, cdecklink_display_mode_iterator_t ** iterator) {
	return obj->GetDisplayModeIterator(iterator);
}

HRESULT cdecklink_output_set_screen_preview_callback(cdecklink_output_t *obj, void *ctx, cdecklink_screen_preview_callback_draw_frame* cb0) {
	IDeckLinkScreenPreviewCallback * handler = nullptr;
	if (cb0 != nullptr) {
		handler = new DeckLinkScreenPreviewCallback(ctx, cb0);
	}
	return obj->SetScreenPreviewCallback(handler);
}

HRESULT cdecklink_output_enable_video_output(cdecklink_output_t *obj, DecklinkDisplayMode displayMode, DecklinkVideoOutputFlags flags) {
	return obj->EnableVideoOutput(displayMode, flags);
}

HRESULT cdecklink_output_disable_video_output(cdecklink_output_t *obj) {
	return obj->DisableVideoOutput();
}

HRESULT cdecklink_output_set_video_output_frame_memory_allocator(cdecklink_output_t *obj, cdecklink_memory_allocator_t * theAllocator) {
	return obj->SetVideoOutputFrameMemoryAllocator(theAllocator);
}

HRESULT cdecklink_output_create_video_frame(cdecklink_output_t *obj, int32_t width, int32_t height, int32_t rowBytes, DecklinkPixelFormat pixelFormat, DecklinkFrameFlags flags, cdecklink_mutable_video_frame_t ** outFrame) {
	return obj->CreateVideoFrame(width, height, rowBytes, pixelFormat, flags, outFrame);
}

HRESULT cdecklink_output_create_ancillary_data(cdecklink_output_t *obj, DecklinkPixelFormat pixelFormat, cdecklink_video_frame_ancillary_t ** outBuffer) {
	return obj->CreateAncillaryData(pixelFormat, outBuffer);
}

HRESULT cdecklink_output_display_video_frame_sync(cdecklink_output_t *obj, cdecklink_video_frame_t * theFrame) {
	return obj->DisplayVideoFrameSync(theFrame);
}

HRESULT cdecklink_output_schedule_video_frame(cdecklink_output_t *obj, cdecklink_video_frame_t * theFrame, DecklinkTimeValue displayTime, DecklinkTimeValue displayDuration, DecklinkTimeScale timeScale) {
	return obj->ScheduleVideoFrame(theFrame, displayTime, displayDuration, timeScale);
}

HRESULT cdecklink_output_set_scheduled_frame_completion_callback(cdecklink_output_t *obj, void *ctx, cdecklink_video_output_callback_scheduled_frame_completed* cb0, cdecklink_video_output_callback_scheduled_playback_has_stopped* cb1) {
	IDeckLinkVideoOutputCallback * handler = nullptr;
	if (cb0 != nullptr && cb1 != nullptr) {
		handler = new DeckLinkVideoOutputCallback(ctx, cb0, cb1);
	}
	return obj->SetScheduledFrameCompletionCallback(handler);
}

HRESULT cdecklink_output_get_buffered_video_frame_count(cdecklink_output_t *obj, uint32_t * bufferedFrameCount) {
	return obj->GetBufferedVideoFrameCount(bufferedFrameCount);
}

HRESULT cdecklink_output_enable_audio_output(cdecklink_output_t *obj, DecklinkAudioSampleRate sampleRate, DecklinkAudioSampleType sampleType, uint32_t channelCount, DecklinkAudioOutputStreamType streamType) {
	return obj->EnableAudioOutput(sampleRate, sampleType, channelCount, streamType);
}

HRESULT cdecklink_output_disable_audio_output(cdecklink_output_t *obj) {
	return obj->DisableAudioOutput();
}

HRESULT cdecklink_output_write_audio_samples_sync(cdecklink_output_t *obj, void * buffer, uint32_t sampleFrameCount, uint32_t * sampleFramesWritten) {
	return obj->WriteAudioSamplesSync(buffer, sampleFrameCount, sampleFramesWritten);
}

HRESULT cdecklink_output_begin_audio_preroll(cdecklink_output_t *obj) {
	return obj->BeginAudioPreroll();
}

HRESULT cdecklink_output_end_audio_preroll(cdecklink_output_t *obj) {
	return obj->EndAudioPreroll();
}

HRESULT cdecklink_output_schedule_audio_samples(cdecklink_output_t *obj, void * buffer, uint32_t sampleFrameCount, DecklinkTimeValue streamTime, DecklinkTimeScale timeScale, uint32_t * sampleFramesWritten) {
	return obj->ScheduleAudioSamples(buffer, sampleFrameCount, streamTime, timeScale, sampleFramesWritten);
}

HRESULT cdecklink_output_get_buffered_audio_sample_frame_count(cdecklink_output_t *obj, uint32_t * bufferedSampleFrameCount) {
	return obj->GetBufferedAudioSampleFrameCount(bufferedSampleFrameCount);
}

HRESULT cdecklink_output_flush_buffered_audio_samples(cdecklink_output_t *obj) {
	return obj->FlushBufferedAudioSamples();
}

HRESULT cdecklink_output_set_audio_callback(cdecklink_output_t *obj, void *ctx, cdecklink_audio_output_callback_render_audio_samples* cb0) {
	IDeckLinkAudioOutputCallback * handler = nullptr;
	if (cb0 != nullptr) {
		handler = new DeckLinkAudioOutputCallback(ctx, cb0);
	}
	return obj->SetAudioCallback(handler);
}

HRESULT cdecklink_output_start_scheduled_playback(cdecklink_output_t *obj, DecklinkTimeValue playbackStartTime, DecklinkTimeScale timeScale, double playbackSpeed) {
	return obj->StartScheduledPlayback(playbackStartTime, timeScale, playbackSpeed);
}

HRESULT cdecklink_output_stop_scheduled_playback(cdecklink_output_t *obj, DecklinkTimeValue stopPlaybackAtTime, DecklinkTimeValue * actualStopTime, DecklinkTimeScale timeScale) {
	return obj->StopScheduledPlayback(stopPlaybackAtTime, actualStopTime, timeScale);
}

HRESULT cdecklink_output_is_scheduled_playback_running(cdecklink_output_t *obj, bool * active) {
	return obj->IsScheduledPlaybackRunning(active);
}

HRESULT cdecklink_output_get_scheduled_stream_time(cdecklink_output_t *obj, DecklinkTimeScale desiredTimeScale, DecklinkTimeValue * streamTime, double * playbackSpeed) {
	return obj->GetScheduledStreamTime(desiredTimeScale, streamTime, playbackSpeed);
}

HRESULT cdecklink_output_get_reference_status(cdecklink_output_t *obj, DecklinkReferenceStatus * referenceStatus) {
	return obj->GetReferenceStatus(referenceStatus);
}

HRESULT cdecklink_output_get_hardware_reference_clock(cdecklink_output_t *obj, DecklinkTimeScale desiredTimeScale, DecklinkTimeValue * hardwareTime, DecklinkTimeValue * timeInFrame, DecklinkTimeValue * ticksPerFrame) {
	return obj->GetHardwareReferenceClock(desiredTimeScale, hardwareTime, timeInFrame, ticksPerFrame);
}

HRESULT cdecklink_output_get_frame_completion_reference_timestamp(cdecklink_output_t *obj, cdecklink_video_frame_t * theFrame, DecklinkTimeScale desiredTimeScale, DecklinkTimeValue * frameCompletionTimestamp) {
	return obj->GetFrameCompletionReferenceTimestamp(theFrame, desiredTimeScale, frameCompletionTimestamp);
}


unsigned long cdecklink_input_add_ref(cdecklink_input_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_input_release(cdecklink_input_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_input_does_support_video_mode(cdecklink_input_t *obj, DecklinkDisplayMode displayMode, DecklinkPixelFormat pixelFormat, DecklinkVideoInputFlags flags, DecklinkDisplayModeSupport * result, cdecklink_display_mode_t ** resultDisplayMode) {
	return obj->DoesSupportVideoMode(displayMode, pixelFormat, flags, result, resultDisplayMode);
}

HRESULT cdecklink_input_get_display_mode_iterator(cdecklink_input_t *obj, cdecklink_display_mode_iterator_t ** iterator) {
	return obj->GetDisplayModeIterator(iterator);
}

HRESULT cdecklink_input_set_screen_preview_callback(cdecklink_input_t *obj, void *ctx, cdecklink_screen_preview_callback_draw_frame* cb0) {
	IDeckLinkScreenPreviewCallback * handler = nullptr;
	if (cb0 != nullptr) {
		handler = new DeckLinkScreenPreviewCallback(ctx, cb0);
	}
	return obj->SetScreenPreviewCallback(handler);
}

HRESULT cdecklink_input_enable_video_input(cdecklink_input_t *obj, DecklinkDisplayMode displayMode, DecklinkPixelFormat pixelFormat, DecklinkVideoInputFlags flags) {
	return obj->EnableVideoInput(displayMode, pixelFormat, flags);
}

HRESULT cdecklink_input_disable_video_input(cdecklink_input_t *obj) {
	return obj->DisableVideoInput();
}

HRESULT cdecklink_input_get_available_video_frame_count(cdecklink_input_t *obj, uint32_t * availableFrameCount) {
	return obj->GetAvailableVideoFrameCount(availableFrameCount);
}

HRESULT cdecklink_input_set_video_input_frame_memory_allocator(cdecklink_input_t *obj, cdecklink_memory_allocator_t * theAllocator) {
	return obj->SetVideoInputFrameMemoryAllocator(theAllocator);
}

HRESULT cdecklink_input_enable_audio_input(cdecklink_input_t *obj, DecklinkAudioSampleRate sampleRate, DecklinkAudioSampleType sampleType, uint32_t channelCount) {
	return obj->EnableAudioInput(sampleRate, sampleType, channelCount);
}

HRESULT cdecklink_input_disable_audio_input(cdecklink_input_t *obj) {
	return obj->DisableAudioInput();
}

HRESULT cdecklink_input_get_available_audio_sample_frame_count(cdecklink_input_t *obj, uint32_t * availableSampleFrameCount) {
	return obj->GetAvailableAudioSampleFrameCount(availableSampleFrameCount);
}

HRESULT cdecklink_input_start_streams(cdecklink_input_t *obj) {
	return obj->StartStreams();
}

HRESULT cdecklink_input_stop_streams(cdecklink_input_t *obj) {
	return obj->StopStreams();
}

HRESULT cdecklink_input_pause_streams(cdecklink_input_t *obj) {
	return obj->PauseStreams();
}

HRESULT cdecklink_input_flush_streams(cdecklink_input_t *obj) {
	return obj->FlushStreams();
}

HRESULT cdecklink_input_set_callback(cdecklink_input_t *obj, void *ctx, cdecklink_input_callback_video_input_format_changed* cb0, cdecklink_input_callback_video_input_frame_arrived* cb1) {
	IDeckLinkInputCallback * handler = nullptr;
	if (cb0 != nullptr && cb1 != nullptr) {
		handler = new DeckLinkInputCallback(ctx, cb0, cb1);
	}
	return obj->SetCallback(handler);
}

HRESULT cdecklink_input_get_hardware_reference_clock(cdecklink_input_t *obj, DecklinkTimeScale desiredTimeScale, DecklinkTimeValue * hardwareTime, DecklinkTimeValue * timeInFrame, DecklinkTimeValue * ticksPerFrame) {
	return obj->GetHardwareReferenceClock(desiredTimeScale, hardwareTime, timeInFrame, ticksPerFrame);
}


unsigned long cdecklink_encoder_input_add_ref(cdecklink_encoder_input_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_encoder_input_release(cdecklink_encoder_input_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_encoder_input_does_support_video_mode(cdecklink_encoder_input_t *obj, DecklinkDisplayMode displayMode, DecklinkPixelFormat pixelFormat, DecklinkVideoInputFlags flags, DecklinkDisplayModeSupport * result, cdecklink_display_mode_t ** resultDisplayMode) {
	return obj->DoesSupportVideoMode(displayMode, pixelFormat, flags, result, resultDisplayMode);
}

HRESULT cdecklink_encoder_input_get_display_mode_iterator(cdecklink_encoder_input_t *obj, cdecklink_display_mode_iterator_t ** iterator) {
	return obj->GetDisplayModeIterator(iterator);
}

HRESULT cdecklink_encoder_input_enable_video_input(cdecklink_encoder_input_t *obj, DecklinkDisplayMode displayMode, DecklinkPixelFormat pixelFormat, DecklinkVideoInputFlags flags) {
	return obj->EnableVideoInput(displayMode, pixelFormat, flags);
}

HRESULT cdecklink_encoder_input_disable_video_input(cdecklink_encoder_input_t *obj) {
	return obj->DisableVideoInput();
}

HRESULT cdecklink_encoder_input_get_available_packets_count(cdecklink_encoder_input_t *obj, uint32_t * availablePacketsCount) {
	return obj->GetAvailablePacketsCount(availablePacketsCount);
}

HRESULT cdecklink_encoder_input_set_memory_allocator(cdecklink_encoder_input_t *obj, cdecklink_memory_allocator_t * theAllocator) {
	return obj->SetMemoryAllocator(theAllocator);
}

HRESULT cdecklink_encoder_input_enable_audio_input(cdecklink_encoder_input_t *obj, DecklinkAudioFormat audioFormat, DecklinkAudioSampleRate sampleRate, DecklinkAudioSampleType sampleType, uint32_t channelCount) {
	return obj->EnableAudioInput(audioFormat, sampleRate, sampleType, channelCount);
}

HRESULT cdecklink_encoder_input_disable_audio_input(cdecklink_encoder_input_t *obj) {
	return obj->DisableAudioInput();
}

HRESULT cdecklink_encoder_input_get_available_audio_sample_frame_count(cdecklink_encoder_input_t *obj, uint32_t * availableSampleFrameCount) {
	return obj->GetAvailableAudioSampleFrameCount(availableSampleFrameCount);
}

HRESULT cdecklink_encoder_input_start_streams(cdecklink_encoder_input_t *obj) {
	return obj->StartStreams();
}

HRESULT cdecklink_encoder_input_stop_streams(cdecklink_encoder_input_t *obj) {
	return obj->StopStreams();
}

HRESULT cdecklink_encoder_input_pause_streams(cdecklink_encoder_input_t *obj) {
	return obj->PauseStreams();
}

HRESULT cdecklink_encoder_input_flush_streams(cdecklink_encoder_input_t *obj) {
	return obj->FlushStreams();
}

HRESULT cdecklink_encoder_input_set_callback(cdecklink_encoder_input_t *obj, void *ctx, cdecklink_encoder_input_callback_video_input_signal_changed* cb0, cdecklink_encoder_input_callback_video_packet_arrived* cb1, cdecklink_encoder_input_callback_audio_packet_arrived* cb2) {
	IDeckLinkEncoderInputCallback * handler = nullptr;
	if (cb0 != nullptr && cb1 != nullptr && cb2 != nullptr) {
		handler = new DeckLinkEncoderInputCallback(ctx, cb0, cb1, cb2);
	}
	return obj->SetCallback(handler);
}

HRESULT cdecklink_encoder_input_get_hardware_reference_clock(cdecklink_encoder_input_t *obj, DecklinkTimeScale desiredTimeScale, DecklinkTimeValue * hardwareTime, DecklinkTimeValue * timeInFrame, DecklinkTimeValue * ticksPerFrame) {
	return obj->GetHardwareReferenceClock(desiredTimeScale, hardwareTime, timeInFrame, ticksPerFrame);
}


unsigned long cdecklink_video_frame_add_ref(cdecklink_video_frame_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_video_frame_release(cdecklink_video_frame_t *obj) {
	return obj->Release();
}

long cdecklink_video_frame_get_width(cdecklink_video_frame_t *obj) {
	return obj->GetWidth();
}

long cdecklink_video_frame_get_height(cdecklink_video_frame_t *obj) {
	return obj->GetHeight();
}

long cdecklink_video_frame_get_row_bytes(cdecklink_video_frame_t *obj) {
	return obj->GetRowBytes();
}

DecklinkPixelFormat cdecklink_video_frame_get_pixel_format(cdecklink_video_frame_t *obj) {
	return obj->GetPixelFormat();
}

DecklinkFrameFlags cdecklink_video_frame_get_flags(cdecklink_video_frame_t *obj) {
	return obj->GetFlags();
}

HRESULT cdecklink_video_frame_get_bytes(cdecklink_video_frame_t *obj, void ** buffer) {
	return obj->GetBytes(buffer);
}

HRESULT cdecklink_video_frame_get_timecode(cdecklink_video_frame_t *obj, DecklinkTimecodeFormat format, cdecklink_timecode_t ** timecode) {
	return obj->GetTimecode(format, timecode);
}

HRESULT cdecklink_video_frame_get_ancillary_data(cdecklink_video_frame_t *obj, cdecklink_video_frame_ancillary_t ** ancillary) {
	return obj->GetAncillaryData(ancillary);
}


cdecklink_video_frame_t *cdecklink_mutable_video_frame_to_video_frame(cdecklink_mutable_video_frame_t *obj) {
	return obj;
}

unsigned long cdecklink_mutable_video_frame_add_ref(cdecklink_mutable_video_frame_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_mutable_video_frame_release(cdecklink_mutable_video_frame_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_mutable_video_frame_set_flags(cdecklink_mutable_video_frame_t *obj, DecklinkFrameFlags newFlags) {
	return obj->SetFlags(newFlags);
}

HRESULT cdecklink_mutable_video_frame_set_timecode(cdecklink_mutable_video_frame_t *obj, DecklinkTimecodeFormat format, cdecklink_timecode_t * timecode) {
	return obj->SetTimecode(format, timecode);
}

HRESULT cdecklink_mutable_video_frame_set_timecode_from_components(cdecklink_mutable_video_frame_t *obj, DecklinkTimecodeFormat format, uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t frames, DecklinkTimecodeFlags flags) {
	return obj->SetTimecodeFromComponents(format, hours, minutes, seconds, frames, flags);
}

HRESULT cdecklink_mutable_video_frame_set_ancillary_data(cdecklink_mutable_video_frame_t *obj, cdecklink_video_frame_ancillary_t * ancillary) {
	return obj->SetAncillaryData(ancillary);
}

HRESULT cdecklink_mutable_video_frame_set_timecode_user_bits(cdecklink_mutable_video_frame_t *obj, DecklinkTimecodeFormat format, DecklinkTimecodeUserBits userBits) {
	return obj->SetTimecodeUserBits(format, userBits);
}


unsigned long cdecklink_video_frame3_d_extensions_add_ref(cdecklink_video_frame3_d_extensions_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_video_frame3_d_extensions_release(cdecklink_video_frame3_d_extensions_t *obj) {
	return obj->Release();
}

DecklinkVideo3DPackingFormat cdecklink_video_frame3_d_extensions_get3_d_packing_format(cdecklink_video_frame3_d_extensions_t *obj) {
	return obj->Get3DPackingFormat();
}

HRESULT cdecklink_video_frame3_d_extensions_get_frame_for_right_eye(cdecklink_video_frame3_d_extensions_t *obj, cdecklink_video_frame_t ** rightEyeFrame) {
	return obj->GetFrameForRightEye(rightEyeFrame);
}


unsigned long cdecklink_video_frame_metadata_extensions_add_ref(cdecklink_video_frame_metadata_extensions_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_video_frame_metadata_extensions_release(cdecklink_video_frame_metadata_extensions_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_video_frame_metadata_extensions_get_int(cdecklink_video_frame_metadata_extensions_t *obj, DecklinkFrameMetadataID metadataID, int64_t * value) {
	return obj->GetInt(metadataID, value);
}

HRESULT cdecklink_video_frame_metadata_extensions_get_float(cdecklink_video_frame_metadata_extensions_t *obj, DecklinkFrameMetadataID metadataID, double * value) {
	return obj->GetFloat(metadataID, value);
}

HRESULT cdecklink_video_frame_metadata_extensions_get_flag(cdecklink_video_frame_metadata_extensions_t *obj, DecklinkFrameMetadataID metadataID, bool * value) {
	return obj->GetFlag(metadataID, value);
}

HRESULT cdecklink_video_frame_metadata_extensions_get_string(cdecklink_video_frame_metadata_extensions_t *obj, DecklinkFrameMetadataID metadataID, const char ** value) {
	return obj->GetString(metadataID, value);
}


cdecklink_video_frame_t *cdecklink_video_input_frame_to_video_frame(cdecklink_video_input_frame_t *obj) {
	return obj;
}

unsigned long cdecklink_video_input_frame_add_ref(cdecklink_video_input_frame_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_video_input_frame_release(cdecklink_video_input_frame_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_video_input_frame_get_stream_time(cdecklink_video_input_frame_t *obj, DecklinkTimeValue * frameTime, DecklinkTimeValue * frameDuration, DecklinkTimeScale timeScale) {
	return obj->GetStreamTime(frameTime, frameDuration, timeScale);
}

HRESULT cdecklink_video_input_frame_get_hardware_reference_timestamp(cdecklink_video_input_frame_t *obj, DecklinkTimeScale timeScale, DecklinkTimeValue * frameTime, DecklinkTimeValue * frameDuration) {
	return obj->GetHardwareReferenceTimestamp(timeScale, frameTime, frameDuration);
}


unsigned long cdecklink_video_frame_ancillary_add_ref(cdecklink_video_frame_ancillary_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_video_frame_ancillary_release(cdecklink_video_frame_ancillary_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_video_frame_ancillary_get_buffer_for_vertical_blanking_line(cdecklink_video_frame_ancillary_t *obj, uint32_t lineNumber, void ** buffer) {
	return obj->GetBufferForVerticalBlankingLine(lineNumber, buffer);
}

DecklinkPixelFormat cdecklink_video_frame_ancillary_get_pixel_format(cdecklink_video_frame_ancillary_t *obj) {
	return obj->GetPixelFormat();
}

DecklinkDisplayMode cdecklink_video_frame_ancillary_get_display_mode(cdecklink_video_frame_ancillary_t *obj) {
	return obj->GetDisplayMode();
}


unsigned long cdecklink_encoder_packet_add_ref(cdecklink_encoder_packet_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_encoder_packet_release(cdecklink_encoder_packet_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_encoder_packet_get_bytes(cdecklink_encoder_packet_t *obj, void ** buffer) {
	return obj->GetBytes(buffer);
}

long cdecklink_encoder_packet_get_size(cdecklink_encoder_packet_t *obj) {
	return obj->GetSize();
}

HRESULT cdecklink_encoder_packet_get_stream_time(cdecklink_encoder_packet_t *obj, DecklinkTimeValue * frameTime, DecklinkTimeScale timeScale) {
	return obj->GetStreamTime(frameTime, timeScale);
}

DecklinkPacketType cdecklink_encoder_packet_get_packet_type(cdecklink_encoder_packet_t *obj) {
	return obj->GetPacketType();
}


cdecklink_encoder_packet_t *cdecklink_encoder_video_packet_to_encoder_packet(cdecklink_encoder_video_packet_t *obj) {
	return obj;
}

unsigned long cdecklink_encoder_video_packet_add_ref(cdecklink_encoder_video_packet_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_encoder_video_packet_release(cdecklink_encoder_video_packet_t *obj) {
	return obj->Release();
}

DecklinkPixelFormat cdecklink_encoder_video_packet_get_pixel_format(cdecklink_encoder_video_packet_t *obj) {
	return obj->GetPixelFormat();
}

HRESULT cdecklink_encoder_video_packet_get_hardware_reference_timestamp(cdecklink_encoder_video_packet_t *obj, DecklinkTimeScale timeScale, DecklinkTimeValue * frameTime, DecklinkTimeValue * frameDuration) {
	return obj->GetHardwareReferenceTimestamp(timeScale, frameTime, frameDuration);
}

HRESULT cdecklink_encoder_video_packet_get_timecode(cdecklink_encoder_video_packet_t *obj, DecklinkTimecodeFormat format, cdecklink_timecode_t ** timecode) {
	return obj->GetTimecode(format, timecode);
}


cdecklink_encoder_packet_t *cdecklink_encoder_audio_packet_to_encoder_packet(cdecklink_encoder_audio_packet_t *obj) {
	return obj;
}

unsigned long cdecklink_encoder_audio_packet_add_ref(cdecklink_encoder_audio_packet_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_encoder_audio_packet_release(cdecklink_encoder_audio_packet_t *obj) {
	return obj->Release();
}

DecklinkAudioFormat cdecklink_encoder_audio_packet_get_audio_format(cdecklink_encoder_audio_packet_t *obj) {
	return obj->GetAudioFormat();
}


cdecklink_encoder_video_packet_t *cdecklink_h265nal_packet_to_encoder_video_packet(cdecklink_h265nal_packet_t *obj) {
	return obj;
}

unsigned long cdecklink_h265nal_packet_add_ref(cdecklink_h265nal_packet_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_h265nal_packet_release(cdecklink_h265nal_packet_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_h265nal_packet_get_unit_type(cdecklink_h265nal_packet_t *obj, uint8_t * unitType) {
	return obj->GetUnitType(unitType);
}

HRESULT cdecklink_h265nal_packet_get_bytes_no_prefix(cdecklink_h265nal_packet_t *obj, void ** buffer) {
	return obj->GetBytesNoPrefix(buffer);
}

long cdecklink_h265nal_packet_get_size_no_prefix(cdecklink_h265nal_packet_t *obj) {
	return obj->GetSizeNoPrefix();
}


unsigned long cdecklink_audio_input_packet_add_ref(cdecklink_audio_input_packet_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_audio_input_packet_release(cdecklink_audio_input_packet_t *obj) {
	return obj->Release();
}

long cdecklink_audio_input_packet_get_sample_frame_count(cdecklink_audio_input_packet_t *obj) {
	return obj->GetSampleFrameCount();
}

HRESULT cdecklink_audio_input_packet_get_bytes(cdecklink_audio_input_packet_t *obj, void ** buffer) {
	return obj->GetBytes(buffer);
}

HRESULT cdecklink_audio_input_packet_get_packet_time(cdecklink_audio_input_packet_t *obj, DecklinkTimeValue * packetTime, DecklinkTimeScale timeScale) {
	return obj->GetPacketTime(packetTime, timeScale);
}


unsigned long cdecklink_gl_screen_preview_helper_add_ref(cdecklink_gl_screen_preview_helper_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_gl_screen_preview_helper_release(cdecklink_gl_screen_preview_helper_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_gl_screen_preview_helper_initialize_gl(cdecklink_gl_screen_preview_helper_t *obj) {
	return obj->InitializeGL();
}

HRESULT cdecklink_gl_screen_preview_helper_paint_gl(cdecklink_gl_screen_preview_helper_t *obj) {
	return obj->PaintGL();
}

HRESULT cdecklink_gl_screen_preview_helper_set_frame(cdecklink_gl_screen_preview_helper_t *obj, cdecklink_video_frame_t * theFrame) {
	return obj->SetFrame(theFrame);
}

HRESULT cdecklink_gl_screen_preview_helper_set3_d_preview_format(cdecklink_gl_screen_preview_helper_t *obj, Decklink3DPreviewFormat previewFormat) {
	return obj->Set3DPreviewFormat(previewFormat);
}


unsigned long cdecklink_notification_add_ref(cdecklink_notification_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_notification_release(cdecklink_notification_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_notification_subscribe(cdecklink_notification_t *obj, DecklinkNotifications topic, void *ctx, cdecklink_notification_callback_notify* cb0) {
	IDeckLinkNotificationCallback * handler = nullptr;
	if (cb0 != nullptr) {
		handler = new DeckLinkNotificationCallback(ctx, cb0);
	}
	return obj->Subscribe(topic, handler);
}

HRESULT cdecklink_notification_unsubscribe(cdecklink_notification_t *obj, DecklinkNotifications topic, void *ctx, cdecklink_notification_callback_notify* cb0) {
	IDeckLinkNotificationCallback * handler = nullptr;
	if (cb0 != nullptr) {
		handler = new DeckLinkNotificationCallback(ctx, cb0);
	}
	return obj->Unsubscribe(topic, handler);
}


unsigned long cdecklink_attributes_add_ref(cdecklink_attributes_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_attributes_release(cdecklink_attributes_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_attributes_get_flag(cdecklink_attributes_t *obj, DecklinkAttributeID cfgID, bool * value) {
	return obj->GetFlag(cfgID, value);
}

HRESULT cdecklink_attributes_get_int(cdecklink_attributes_t *obj, DecklinkAttributeID cfgID, int64_t * value) {
	return obj->GetInt(cfgID, value);
}

HRESULT cdecklink_attributes_get_float(cdecklink_attributes_t *obj, DecklinkAttributeID cfgID, double * value) {
	return obj->GetFloat(cfgID, value);
}

HRESULT cdecklink_attributes_get_string(cdecklink_attributes_t *obj, DecklinkAttributeID cfgID, const char ** value) {
	return obj->GetString(cfgID, value);
}


unsigned long cdecklink_status_add_ref(cdecklink_status_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_status_release(cdecklink_status_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_status_get_flag(cdecklink_status_t *obj, DecklinkStatusID statusID, bool * value) {
	return obj->GetFlag(statusID, value);
}

HRESULT cdecklink_status_get_int(cdecklink_status_t *obj, DecklinkStatusID statusID, int64_t * value) {
	return obj->GetInt(statusID, value);
}

HRESULT cdecklink_status_get_float(cdecklink_status_t *obj, DecklinkStatusID statusID, double * value) {
	return obj->GetFloat(statusID, value);
}

HRESULT cdecklink_status_get_string(cdecklink_status_t *obj, DecklinkStatusID statusID, const char ** value) {
	return obj->GetString(statusID, value);
}

HRESULT cdecklink_status_get_bytes(cdecklink_status_t *obj, DecklinkStatusID statusID, void * buffer, uint32_t * bufferSize) {
	return obj->GetBytes(statusID, buffer, bufferSize);
}


unsigned long cdecklink_keyer_add_ref(cdecklink_keyer_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_keyer_release(cdecklink_keyer_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_keyer_enable(cdecklink_keyer_t *obj, bool isExternal) {
	return obj->Enable(isExternal);
}

HRESULT cdecklink_keyer_set_level(cdecklink_keyer_t *obj, uint8_t level) {
	return obj->SetLevel(level);
}

HRESULT cdecklink_keyer_ramp_up(cdecklink_keyer_t *obj, uint32_t numberOfFrames) {
	return obj->RampUp(numberOfFrames);
}

HRESULT cdecklink_keyer_ramp_down(cdecklink_keyer_t *obj, uint32_t numberOfFrames) {
	return obj->RampDown(numberOfFrames);
}

HRESULT cdecklink_keyer_disable(cdecklink_keyer_t *obj) {
	return obj->Disable();
}


unsigned long cdecklink_video_conversion_add_ref(cdecklink_video_conversion_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_video_conversion_release(cdecklink_video_conversion_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_video_conversion_convert_frame(cdecklink_video_conversion_t *obj, cdecklink_video_frame_t * srcFrame, cdecklink_video_frame_t * dstFrame) {
	return obj->ConvertFrame(srcFrame, dstFrame);
}


unsigned long cdecklink_discovery_add_ref(cdecklink_discovery_t *obj) {
	return obj->AddRef();
}

unsigned long cdecklink_discovery_release(cdecklink_discovery_t *obj) {
	return obj->Release();
}

HRESULT cdecklink_discovery_install_device_notifications(cdecklink_discovery_t *obj, void *ctx, cdecklink_device_notification_callback_deck_link_device_arrived* cb0, cdecklink_device_notification_callback_deck_link_device_removed* cb1) {
	IDeckLinkDeviceNotificationCallback * handler = nullptr;
	if (cb0 != nullptr && cb1 != nullptr) {
		handler = new DeckLinkDeviceNotificationCallback(ctx, cb0, cb1);
	}
	return obj->InstallDeviceNotifications(handler);
}

HRESULT cdecklink_discovery_uninstall_device_notifications(cdecklink_discovery_t *obj) {
	return obj->UninstallDeviceNotifications();
}


cdecklink_iterator_t * cdecklink_create_decklink_iterator_instance() {
	return CreateDeckLinkIteratorInstance();
}

cdecklink_discovery_t * cdecklink_create_decklink_discovery_instance() {
	return CreateDeckLinkDiscoveryInstance();
}

cdecklink_api_information_t * cdecklink_create_decklink_api_information_instance() {
	return CreateDeckLinkAPIInformationInstance();
}

cdecklink_gl_screen_preview_helper_t * cdecklink_create_open_gl_screen_preview_helper() {
	return CreateOpenGLScreenPreviewHelper();
}

cdecklink_video_conversion_t * cdecklink_create_video_conversion_instance() {
	return CreateVideoConversionInstance();
}

HRESULT cdecklink_device_query_output(cdecklink_device_t *obj, cdecklink_output_t **dst) {
	return obj->QueryInterface(IID_IDeckLinkOutput, reinterpret_cast<void**>(dst));
}

HRESULT cdecklink_device_query_input(cdecklink_device_t *obj, cdecklink_input_t **dst) {
	return obj->QueryInterface(IID_IDeckLinkInput, reinterpret_cast<void**>(dst));
}

HRESULT cdecklink_device_query_encoder_input(cdecklink_device_t *obj, cdecklink_encoder_input_t **dst) {
	return obj->QueryInterface(IID_IDeckLinkEncoderInput, reinterpret_cast<void**>(dst));
}

HRESULT cdecklink_video_frame_query_video_frame_ancillary(cdecklink_video_frame_t *obj, cdecklink_video_frame_ancillary_t **dst) {
	return obj->QueryInterface(IID_IDeckLinkVideoFrameAncillary, reinterpret_cast<void**>(dst));
}

HRESULT cdecklink_encoder_video_packet_query_h265nal_packet(cdecklink_encoder_video_packet_t *obj, cdecklink_h265nal_packet_t **dst) {
	return obj->QueryInterface(IID_IDeckLinkH265NALPacket, reinterpret_cast<void**>(dst));
}

