#include <atomic>
#include "types.h"
#include "../include/api.h"
#include "callbacks.h"

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

IDeckLinkDeckControlStatusCallback* cdecklink_internal_callback_create_deck_link_deck_control_status_callback (void *ctx, cdecklink_deck_control_status_callback_timecode_update *cb0, cdecklink_deck_control_status_callback_vtr_control_state_changed *cb1, cdecklink_deck_control_status_callback_deck_control_event_received *cb2, cdecklink_deck_control_status_callback_deck_control_status_changed *cb3) {
	if (cb0 != nullptr || cb1 != nullptr || cb2 != nullptr || cb3 != nullptr) {
		return new DeckLinkDeckControlStatusCallback(ctx, cb0, cb1, cb2, cb3);
	}
	return nullptr;
}

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

IDeckLinkVideoOutputCallback* cdecklink_internal_callback_create_deck_link_video_output_callback (void *ctx, cdecklink_video_output_callback_scheduled_frame_completed *cb0, cdecklink_video_output_callback_scheduled_playback_has_stopped *cb1) {
	if (cb0 != nullptr || cb1 != nullptr) {
		return new DeckLinkVideoOutputCallback(ctx, cb0, cb1);
	}
	return nullptr;
}

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

IDeckLinkInputCallback* cdecklink_internal_callback_create_deck_link_input_callback (void *ctx, cdecklink_input_callback_video_input_format_changed *cb0, cdecklink_input_callback_video_input_frame_arrived *cb1) {
	if (cb0 != nullptr || cb1 != nullptr) {
		return new DeckLinkInputCallback(ctx, cb0, cb1);
	}
	return nullptr;
}

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

IDeckLinkEncoderInputCallback* cdecklink_internal_callback_create_deck_link_encoder_input_callback (void *ctx, cdecklink_encoder_input_callback_video_input_signal_changed *cb0, cdecklink_encoder_input_callback_video_packet_arrived *cb1, cdecklink_encoder_input_callback_audio_packet_arrived *cb2) {
	if (cb0 != nullptr || cb1 != nullptr || cb2 != nullptr) {
		return new DeckLinkEncoderInputCallback(ctx, cb0, cb1, cb2);
	}
	return nullptr;
}

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

IDeckLinkAudioOutputCallback* cdecklink_internal_callback_create_deck_link_audio_output_callback (void *ctx, cdecklink_audio_output_callback_render_audio_samples *cb0) {
	if (cb0 != nullptr) {
		return new DeckLinkAudioOutputCallback(ctx, cb0);
	}
	return nullptr;
}

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

IDeckLinkScreenPreviewCallback* cdecklink_internal_callback_create_deck_link_screen_preview_callback (void *ctx, cdecklink_screen_preview_callback_draw_frame *cb0) {
	if (cb0 != nullptr) {
		return new DeckLinkScreenPreviewCallback(ctx, cb0);
	}
	return nullptr;
}

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

IDeckLinkNotificationCallback* cdecklink_internal_callback_create_deck_link_notification_callback (void *ctx, cdecklink_notification_callback_notify *cb0) {
	if (cb0 != nullptr) {
		return new DeckLinkNotificationCallback(ctx, cb0);
	}
	return nullptr;
}

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

IDeckLinkDeviceNotificationCallback* cdecklink_internal_callback_create_deck_link_device_notification_callback (void *ctx, cdecklink_device_notification_callback_deck_link_device_arrived *cb0, cdecklink_device_notification_callback_deck_link_device_removed *cb1) {
	if (cb0 != nullptr || cb1 != nullptr) {
		return new DeckLinkDeviceNotificationCallback(ctx, cb0, cb1);
	}
	return nullptr;
}

