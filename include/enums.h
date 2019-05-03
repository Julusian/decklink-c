#ifndef DECKLINK_C_ENUMS_H
#define DECKLINK_C_ENUMS_H

#include <stdint.h>

#ifndef BMD_DECKLINKAPIMODES_H

/* Enum BMDDisplayMode - Video display modes */

typedef uint32_t BMDDisplayMode;
enum _BMDDisplayMode {

    /* SD Modes */

    bmdModeNTSC                                                  = /* 'ntsc' */ 0x6E747363,
    bmdModeNTSC2398                                              = /* 'nt23' */ 0x6E743233,	// 3:2 pulldown
    bmdModePAL                                                   = /* 'pal ' */ 0x70616C20,
    bmdModeNTSCp                                                 = /* 'ntsp' */ 0x6E747370,
    bmdModePALp                                                  = /* 'palp' */ 0x70616C70,

    /* HD 1080 Modes */

    bmdModeHD1080p2398                                           = /* '23ps' */ 0x32337073,
    bmdModeHD1080p24                                             = /* '24ps' */ 0x32347073,
    bmdModeHD1080p25                                             = /* 'Hp25' */ 0x48703235,
    bmdModeHD1080p2997                                           = /* 'Hp29' */ 0x48703239,
    bmdModeHD1080p30                                             = /* 'Hp30' */ 0x48703330,
    bmdModeHD1080i50                                             = /* 'Hi50' */ 0x48693530,
    bmdModeHD1080i5994                                           = /* 'Hi59' */ 0x48693539,
    bmdModeHD1080i6000                                           = /* 'Hi60' */ 0x48693630,	// N.B. This _really_ is 60.00 Hz.
    bmdModeHD1080p50                                             = /* 'Hp50' */ 0x48703530,
    bmdModeHD1080p5994                                           = /* 'Hp59' */ 0x48703539,
    bmdModeHD1080p6000                                           = /* 'Hp60' */ 0x48703630,	// N.B. This _really_ is 60.00 Hz.

    /* HD 720 Modes */

    bmdModeHD720p50                                              = /* 'hp50' */ 0x68703530,
    bmdModeHD720p5994                                            = /* 'hp59' */ 0x68703539,
    bmdModeHD720p60                                              = /* 'hp60' */ 0x68703630,

    /* 2k Modes */

    bmdMode2k2398                                                = /* '2k23' */ 0x326B3233,
    bmdMode2k24                                                  = /* '2k24' */ 0x326B3234,
    bmdMode2k25                                                  = /* '2k25' */ 0x326B3235,

    /* DCI Modes (output only) */

    bmdMode2kDCI2398                                             = /* '2d23' */ 0x32643233,
    bmdMode2kDCI24                                               = /* '2d24' */ 0x32643234,
    bmdMode2kDCI25                                               = /* '2d25' */ 0x32643235,

    /* 4k Modes */

    bmdMode4K2160p2398                                           = /* '4k23' */ 0x346B3233,
    bmdMode4K2160p24                                             = /* '4k24' */ 0x346B3234,
    bmdMode4K2160p25                                             = /* '4k25' */ 0x346B3235,
    bmdMode4K2160p2997                                           = /* '4k29' */ 0x346B3239,
    bmdMode4K2160p30                                             = /* '4k30' */ 0x346B3330,
    bmdMode4K2160p50                                             = /* '4k50' */ 0x346B3530,
    bmdMode4K2160p5994                                           = /* '4k59' */ 0x346B3539,
    bmdMode4K2160p60                                             = /* '4k60' */ 0x346B3630,

    /* DCI Modes (output only) */

    bmdMode4kDCI2398                                             = /* '4d23' */ 0x34643233,
    bmdMode4kDCI24                                               = /* '4d24' */ 0x34643234,
    bmdMode4kDCI25                                               = /* '4d25' */ 0x34643235,

    /* RAW Modes for Cintel (input only) */

    bmdModeCintelRAW                                             = /* 'rwci' */ 0x72776369,	// Frame size up to 4096x3072, variable frame rate
    bmdModeCintelCompressedRAW                                   = /* 'rwcc' */ 0x72776363,	// Frame size up to 4096x3072, variable frame rate

    /* Special Modes */

    bmdModeUnknown                                               = /* 'iunk' */ 0x69756E6B
};

/* Enum BMDFieldDominance - Video field dominance */

typedef uint32_t BMDFieldDominance;
enum _BMDFieldDominance {
    bmdUnknownFieldDominance                                     = 0,
    bmdLowerFieldFirst                                           = /* 'lowr' */ 0x6C6F7772,
    bmdUpperFieldFirst                                           = /* 'uppr' */ 0x75707072,
    bmdProgressiveFrame                                          = /* 'prog' */ 0x70726F67,
    bmdProgressiveSegmentedFrame                                 = /* 'psf ' */ 0x70736620
};

/* Enum BMDPixelFormat - Video pixel formats supported for output/input */

typedef uint32_t BMDPixelFormat;
enum _BMDPixelFormat {
    bmdFormat8BitYUV                                             = /* '2vuy' */ 0x32767579,
    bmdFormat10BitYUV                                            = /* 'v210' */ 0x76323130,
    bmdFormat8BitARGB                                            = 32,
    bmdFormat8BitBGRA                                            = /* 'BGRA' */ 0x42475241,
    bmdFormat10BitRGB                                            = /* 'r210' */ 0x72323130,	// Big-endian RGB 10-bit per component with SMPTE video levels (64-960). Packed as 2:10:10:10
    bmdFormat12BitRGB                                            = /* 'R12B' */ 0x52313242,	// Big-endian RGB 12-bit per component with full range (0-4095). Packed as 12-bit per component
    bmdFormat12BitRGBLE                                          = /* 'R12L' */ 0x5231324C,	// Little-endian RGB 12-bit per component with full range (0-4095). Packed as 12-bit per component
    bmdFormat10BitRGBXLE                                         = /* 'R10l' */ 0x5231306C,	// Little-endian 10-bit RGB with SMPTE video levels (64-940)
    bmdFormat10BitRGBX                                           = /* 'R10b' */ 0x52313062,	// Big-endian 10-bit RGB with SMPTE video levels (64-940)
    bmdFormatH265                                                = /* 'hev1' */ 0x68657631,	// High Efficiency Video Coding (HEVC/h.265)

    /* AVID DNxHR */

    bmdFormatDNxHR                                               = /* 'AVdh' */ 0x41566468,

    /* Cintel formats */

    bmdFormat12BitRAWGRBG                                        = /* 'r12p' */ 0x72313270,	// 12-bit RAW data for bayer pattern GRBG
    bmdFormat12BitRAWJPEG                                        = /* 'r16p' */ 0x72313670	// 12-bit RAW data arranged in tiles and JPEG compressed
};

/* Enum BMDDisplayModeFlags - Flags to describe the characteristics of an IDeckLinkDisplayMode. */

typedef uint32_t BMDDisplayModeFlags;
enum _BMDDisplayModeFlags {
    bmdDisplayModeSupports3D                                     = 1 << 0,
    bmdDisplayModeColorspaceRec601                               = 1 << 1,
    bmdDisplayModeColorspaceRec709                               = 1 << 2
};

#endif //BMD_DECKLINKAPIMODES_H

#endif //DECKLINK_C_ENUMS_H
