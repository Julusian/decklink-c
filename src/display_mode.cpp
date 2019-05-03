#include <memory>

#include "structs.h"

#include "include/display_mode.h"

const char *cdecklink_display_mode_name(cdecklink_display_mode_t *mode) {
    if (mode != nullptr && mode->obj != nullptr) {
        String name;
        if (mode->obj->GetName(&name) == S_OK) {
            return name;
        }
    }

    return nullptr;
}

BMDDisplayMode cdecklink_display_mode_mode(cdecklink_display_mode_t *mode) {
    if (mode != nullptr && mode->obj != nullptr) {
        return mode->obj->GetDisplayMode();
    }

    return 0;
}

long cdecklink_display_mode_width(cdecklink_display_mode_t *mode) {
    if (mode != nullptr && mode->obj != nullptr) {
        return mode->obj->GetWidth();
    }

    return 0;
}

long cdecklink_display_mode_height(cdecklink_display_mode_t *mode) {
    if (mode != nullptr && mode->obj != nullptr) {
        return mode->obj->GetHeight();
    }

    return 0;
}

HRESULT cdecklink_display_mode_framerate(cdecklink_display_mode_t *mode, int64_t *duration, int64_t *scale) {
    if (mode != nullptr && mode->obj != nullptr) {
        return mode->obj->GetFrameRate(duration, scale);
    }

    return S_FALSE;
}

BMDFieldDominance cdecklink_display_mode_field_dominance(cdecklink_display_mode_t *mode) {
    if (mode != nullptr && mode->obj != nullptr) {
        return mode->obj->GetFieldDominance();
    }

    return 0;
}

BMDDisplayModeFlags cdecklink_display_mode_flags(cdecklink_display_mode_t *mode) {
    if (mode != nullptr && mode->obj != nullptr) {
        return mode->obj->GetFlags();
    }

    return 0;
}
