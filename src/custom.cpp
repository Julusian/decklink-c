#include "./types.h"
#include "../include/custom.h"

#include <atomic>

class CustomDecklinkFrame : public IDeckLinkVideoFrame
{
    const long width;
    const long height;
    const long row_bytes;
    const BMDPixelFormat pixel_format;
    const BMDFrameFlags flags;

    void *bytes;
    cdecklink_custom_video_frame_free_bytes *finalizer;
    void *context;

    std::atomic<int> ref_count_{0};

public:
    CustomDecklinkFrame(long width, long height, long row_bytes, BMDPixelFormat pixel_format, BMDFrameFlags flags)
        : width(width), height(height), row_bytes(row_bytes), pixel_format(pixel_format), flags(flags)
    {
    }

    ~CustomDecklinkFrame()
    {
        if (finalizer && bytes)
        {
            finalizer(bytes, context);
            bytes = nullptr;
            finalizer = nullptr;
            context = nullptr;
        }
    }

    // IUnknown

    HRESULT STDMETHODCALLTYPE
    QueryInterface(REFIID, LPVOID *) override
    {
        return E_NOINTERFACE;
    }

    ULONG STDMETHODCALLTYPE AddRef() override { return ++ref_count_; }

    ULONG STDMETHODCALLTYPE Release() override
    {
        if (--ref_count_ == 0)
        {
            delete this;

            return 0;
        }

        return ref_count_;
    }

    // IDecklinkVideoFrame

    long STDMETHODCALLTYPE GetWidth() override { return width; }
    long STDMETHODCALLTYPE GetHeight() override { return height; }
    long STDMETHODCALLTYPE GetRowBytes() override { return row_bytes; }
    BMDPixelFormat STDMETHODCALLTYPE GetPixelFormat() override { return pixel_format; }
    BMDFrameFlags STDMETHODCALLTYPE GetFlags() override { return flags; }

    HRESULT STDMETHODCALLTYPE GetBytes(void **buffer) override
    {

        if (bytes)
        {
            *buffer = bytes;
            return S_OK;
        }
        else
        {
            return S_FALSE;
        }
    }

    HRESULT STDMETHODCALLTYPE GetTimecode(BMDTimecodeFormat format, IDeckLinkTimecode **timecode) override
    {
        return S_FALSE;
    }

    HRESULT STDMETHODCALLTYPE GetAncillaryData(IDeckLinkVideoFrameAncillary **ancillary) override { return S_FALSE; }

    // Custom

    void SetBytes(void *buffer, cdecklink_custom_video_frame_free_bytes *finalizer, void *context)
    {
        if (finalizer && bytes)
        {
            finalizer(bytes, context);
            bytes = nullptr;
            finalizer = nullptr;
            context = nullptr;
        }

        bytes = buffer;
        finalizer = finalizer;
        context = context;
    }
};

HRESULT cdecklink_custom_video_frame_create_frame(long width, long height, long row_bytes, BMDPixelFormat pixel_format, BMDFrameFlags flags, cdecklink_custom_video_frame_t **frame)
{
    *frame = new CustomDecklinkFrame(width, height, row_bytes, pixel_format, flags);
    return S_OK;
}
unsigned long cdecklink_custom_video_frame_add_ref(cdecklink_custom_video_frame_t *obj)
{
    return obj->AddRef();
}
unsigned long cdecklink_custom_video_frame_release(cdecklink_custom_video_frame_t *obj)
{
    return obj->Release();
}
long cdecklink_custom_video_frame_get_width(cdecklink_custom_video_frame_t *obj)
{
    return obj->GetWidth();
}
long cdecklink_custom_video_frame_get_height(cdecklink_custom_video_frame_t *obj)
{
    return obj->GetHeight();
}
long cdecklink_custom_video_frame_get_row_bytes(cdecklink_custom_video_frame_t *obj)
{
    return obj->GetRowBytes();
}
DecklinkPixelFormat cdecklink_custom_video_frame_get_pixel_format(cdecklink_custom_video_frame_t *obj)
{
    return obj->GetPixelFormat();
}
DecklinkFrameFlags cdecklink_custom_video_frame_get_flags(cdecklink_custom_video_frame_t *obj)
{
    return obj->GetFlags();
}
HRESULT cdecklink_custom_video_frame_get_bytes(cdecklink_custom_video_frame_t *obj, void **buffer)
{
    return obj->GetBytes(buffer);
}
HRESULT cdecklink_custom_video_frame_set_bytes(cdecklink_custom_video_frame_t *obj, void *buffer, cdecklink_custom_video_frame_free_bytes *finalizer, void *context)
{
    obj->SetBytes(buffer, finalizer, context);
    return S_OK;
}
