#include <memory>

#include "types.h"

#include "include/display_mode.h"

void cdecklink_release_display_mode_iterator(cdecklink_display_mode_iterator_t *it) {
    it->Release();
}


HRESULT cdecklink_next_display_mode(cdecklink_display_mode_iterator_t *it, cdecklink_display_mode_t **mode) {
    return it->Next(mode);
}

void cdecklink_release_display_mode(cdecklink_display_mode_t *mode) {
    mode->Release();
}


HRESULT cdecklink_display_mode_name(cdecklink_display_mode_t *mode, const char **name) {
    return mode->GetName(name);
}

BMDDisplayMode cdecklink_display_mode_mode(cdecklink_display_mode_t *mode) {
    return mode->GetDisplayMode();
}

long cdecklink_display_mode_width(cdecklink_display_mode_t *mode) {
    return mode->GetWidth();
}

long cdecklink_display_mode_height(cdecklink_display_mode_t *mode) {
    return mode->GetHeight();
}

HRESULT cdecklink_display_mode_framerate(cdecklink_display_mode_t *mode, int64_t *duration, int64_t *scale) {
    return mode->GetFrameRate(duration, scale);
}

BMDFieldDominance cdecklink_display_mode_field_dominance(cdecklink_display_mode_t *mode) {
    return mode->GetFieldDominance();
}

BMDDisplayModeFlags cdecklink_display_mode_flags(cdecklink_display_mode_t *mode) {
    return mode->GetFlags();
}
