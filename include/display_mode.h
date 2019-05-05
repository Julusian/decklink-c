#ifndef DECKLINK_C_DISPLAY_MODE_H
#define DECKLINK_C_DISPLAY_MODE_H

#include "common.h"
#include "enums.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void cdecklink_release_display_mode_iterator(cdecklink_display_mode_iterator_t *it);

HRESULT cdecklink_next_display_mode(cdecklink_display_mode_iterator_t *it, cdecklink_display_mode_t **mode);

void cdecklink_release_display_mode(cdecklink_display_mode_t *mode);

HRESULT cdecklink_display_mode_name(cdecklink_display_mode_t *mode, const char **name);

BMDDisplayMode cdecklink_display_mode_mode(cdecklink_display_mode_t *mode);

long cdecklink_display_mode_width(cdecklink_display_mode_t *mode);

long cdecklink_display_mode_height(cdecklink_display_mode_t *mode);

HRESULT cdecklink_display_mode_framerate(cdecklink_display_mode_t *mode, int64_t *duration, int64_t *scale);

BMDFieldDominance cdecklink_display_mode_field_dominance(cdecklink_display_mode_t *mode);

BMDDisplayModeFlags cdecklink_display_mode_flags(cdecklink_display_mode_t *mode);

#ifdef __cplusplus
};
#endif

#endif //DECKLINK_C_DISPLAY_MODE_H
