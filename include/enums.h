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

#ifndef BMD_DECKLINKAPI_H


/* Enum BMDVideoOutputFlags - Flags to control the output of ancillary data along with video. */

typedef uint32_t BMDVideoOutputFlags;
enum _BMDVideoOutputFlags {
    bmdVideoOutputFlagDefault                                    = 0,
    bmdVideoOutputVANC                                           = 1 << 0,
    bmdVideoOutputVITC                                           = 1 << 1,
    bmdVideoOutputRP188                                          = 1 << 2,
    bmdVideoOutputDualStream3D                                   = 1 << 4
};

/* Enum BMDPacketType - Type of packet */

typedef uint32_t BMDPacketType;
enum _BMDPacketType {
    bmdPacketTypeStreamInterruptedMarker                         = /* 'sint' */ 0x73696E74,	// A packet of this type marks the time when a video stream was interrupted, for example by a disconnected cable
    bmdPacketTypeStreamData                                      = /* 'sdat' */ 0x73646174	// Regular stream data
};

/* Enum BMDFrameFlags - Frame flags */

typedef uint32_t BMDFrameFlags;
enum _BMDFrameFlags {
    bmdFrameFlagDefault                                          = 0,
    bmdFrameFlagFlipVertical                                     = 1 << 0,
    bmdFrameContainsHDRMetadata                                  = 1 << 1,
    bmdFrameContainsCintelMetadata                               = 1 << 2,

    /* Flags that are applicable only to instances of IDeckLinkVideoInputFrame */

    bmdFrameHasNoInputSource                                     = 1 << 31
};

/* Enum BMDVideoInputFlags - Flags applicable to video input */

typedef uint32_t BMDVideoInputFlags;
enum _BMDVideoInputFlags {
    bmdVideoInputFlagDefault                                     = 0,
    bmdVideoInputEnableFormatDetection                           = 1 << 0,
    bmdVideoInputDualStream3D                                    = 1 << 1
};

/* Enum BMDVideoInputFormatChangedEvents - Bitmask passed to the VideoInputFormatChanged notification to identify the properties of the input signal that have changed */

typedef uint32_t BMDVideoInputFormatChangedEvents;
enum _BMDVideoInputFormatChangedEvents {
    bmdVideoInputDisplayModeChanged                              = 1 << 0,
    bmdVideoInputFieldDominanceChanged                           = 1 << 1,
    bmdVideoInputColorspaceChanged                               = 1 << 2
};

/* Enum BMDDetectedVideoInputFormatFlags - Flags passed to the VideoInputFormatChanged notification to describe the detected video input signal */

typedef uint32_t BMDDetectedVideoInputFormatFlags;
enum _BMDDetectedVideoInputFormatFlags {
    bmdDetectedVideoInputYCbCr422                                = 1 << 0,
    bmdDetectedVideoInputRGB444                                  = 1 << 1,
    bmdDetectedVideoInputDualStream3D                            = 1 << 2
};

/* Enum BMDDeckLinkCapturePassthroughMode - Enumerates whether the video output is electrically connected to the video input or if the clean switching mode is enabled */

typedef uint32_t BMDDeckLinkCapturePassthroughMode;
enum _BMDDeckLinkCapturePassthroughMode {
    bmdDeckLinkCapturePassthroughModeDisabled                    = /* 'pdis' */ 0x70646973,
    bmdDeckLinkCapturePassthroughModeDirect                      = /* 'pdir' */ 0x70646972,
    bmdDeckLinkCapturePassthroughModeCleanSwitch                 = /* 'pcln' */ 0x70636C6E
};

/* Enum BMDOutputFrameCompletionResult - Frame Completion Callback */

typedef uint32_t BMDOutputFrameCompletionResult;
enum _BMDOutputFrameCompletionResult {
    bmdOutputFrameCompleted,
    bmdOutputFrameDisplayedLate,
    bmdOutputFrameDropped,
    bmdOutputFrameFlushed
};

/* Enum BMDReferenceStatus - GenLock input status */

typedef uint32_t BMDReferenceStatus;
enum _BMDReferenceStatus {
    bmdReferenceNotSupportedByHardware                           = 1 << 0,
    bmdReferenceLocked                                           = 1 << 1
};

/* Enum BMDAudioFormat - Audio Format */

typedef uint32_t BMDAudioFormat;
enum _BMDAudioFormat {
    bmdAudioFormatPCM                                            = /* 'lpcm' */ 0x6C70636D	// Linear signed PCM samples
};

/* Enum BMDAudioSampleRate - Audio sample rates supported for output/input */

typedef uint32_t BMDAudioSampleRate;
enum _BMDAudioSampleRate {
    bmdAudioSampleRate48kHz                                      = 48000
};

/* Enum BMDAudioSampleType - Audio sample sizes supported for output/input */

typedef uint32_t BMDAudioSampleType;
enum _BMDAudioSampleType {
    bmdAudioSampleType16bitInteger                               = 16,
    bmdAudioSampleType32bitInteger                               = 32
};

/* Enum BMDAudioOutputStreamType - Audio output stream type */

typedef uint32_t BMDAudioOutputStreamType;
enum _BMDAudioOutputStreamType {
    bmdAudioOutputStreamContinuous,
    bmdAudioOutputStreamContinuousDontResample,
    bmdAudioOutputStreamTimestamped
};

/* Enum BMDDisplayModeSupport - Output mode supported flags */

typedef uint32_t BMDDisplayModeSupport;
enum _BMDDisplayModeSupport {
    bmdDisplayModeNotSupported                                   = 0,
    bmdDisplayModeSupported,
    bmdDisplayModeSupportedWithConversion
};

/* Enum BMDTimecodeFormat - Timecode formats for frame metadata */

typedef uint32_t BMDTimecodeFormat;
enum _BMDTimecodeFormat {
    bmdTimecodeRP188VITC1                                        = /* 'rpv1' */ 0x72707631,	// RP188 timecode where DBB1 equals VITC1 (line 9)
    bmdTimecodeRP188VITC2                                        = /* 'rp12' */ 0x72703132,	// RP188 timecode where DBB1 equals VITC2 (line 9 for progressive or line 571 for interlaced/PsF)
    bmdTimecodeRP188LTC                                          = /* 'rplt' */ 0x72706C74,	// RP188 timecode where DBB1 equals LTC (line 10)
    bmdTimecodeRP188Any                                          = /* 'rp18' */ 0x72703138,	// For capture: return the first valid timecode in {VITC1, LTC ,VITC2} - For playback: set the timecode as VITC1
    bmdTimecodeVITC                                              = /* 'vitc' */ 0x76697463,
    bmdTimecodeVITCField2                                        = /* 'vit2' */ 0x76697432,
    bmdTimecodeSerial                                            = /* 'seri' */ 0x73657269
};

/* Enum BMDAnalogVideoFlags - Analog video display flags */

typedef uint32_t BMDAnalogVideoFlags;
enum _BMDAnalogVideoFlags {
    bmdAnalogVideoFlagCompositeSetup75                           = 1 << 0,
    bmdAnalogVideoFlagComponentBetacamLevels                     = 1 << 1
};

/* Enum BMDAudioOutputAnalogAESSwitch - Audio output Analog/AESEBU switch */

typedef uint32_t BMDAudioOutputAnalogAESSwitch;
enum _BMDAudioOutputAnalogAESSwitch {
    bmdAudioOutputSwitchAESEBU                                   = /* 'aes ' */ 0x61657320,
    bmdAudioOutputSwitchAnalog                                   = /* 'anlg' */ 0x616E6C67
};

/* Enum BMDVideoOutputConversionMode - Video/audio conversion mode */

typedef uint32_t BMDVideoOutputConversionMode;
enum _BMDVideoOutputConversionMode {
    bmdNoVideoOutputConversion                                   = /* 'none' */ 0x6E6F6E65,
    bmdVideoOutputLetterboxDownconversion                        = /* 'ltbx' */ 0x6C746278,
    bmdVideoOutputAnamorphicDownconversion                       = /* 'amph' */ 0x616D7068,
    bmdVideoOutputHD720toHD1080Conversion                        = /* '720c' */ 0x37323063,
    bmdVideoOutputHardwareLetterboxDownconversion                = /* 'HWlb' */ 0x48576C62,
    bmdVideoOutputHardwareAnamorphicDownconversion               = /* 'HWam' */ 0x4857616D,
    bmdVideoOutputHardwareCenterCutDownconversion                = /* 'HWcc' */ 0x48576363,
    bmdVideoOutputHardware720p1080pCrossconversion               = /* 'xcap' */ 0x78636170,
    bmdVideoOutputHardwareAnamorphic720pUpconversion             = /* 'ua7p' */ 0x75613770,
    bmdVideoOutputHardwareAnamorphic1080iUpconversion            = /* 'ua1i' */ 0x75613169,
    bmdVideoOutputHardwareAnamorphic149To720pUpconversion        = /* 'u47p' */ 0x75343770,
    bmdVideoOutputHardwareAnamorphic149To1080iUpconversion       = /* 'u41i' */ 0x75343169,
    bmdVideoOutputHardwarePillarbox720pUpconversion              = /* 'up7p' */ 0x75703770,
    bmdVideoOutputHardwarePillarbox1080iUpconversion             = /* 'up1i' */ 0x75703169
};

/* Enum BMDVideoInputConversionMode - Video input conversion mode */

typedef uint32_t BMDVideoInputConversionMode;
enum _BMDVideoInputConversionMode {
    bmdNoVideoInputConversion                                    = /* 'none' */ 0x6E6F6E65,
    bmdVideoInputLetterboxDownconversionFromHD1080               = /* '10lb' */ 0x31306C62,
    bmdVideoInputAnamorphicDownconversionFromHD1080              = /* '10am' */ 0x3130616D,
    bmdVideoInputLetterboxDownconversionFromHD720                = /* '72lb' */ 0x37326C62,
    bmdVideoInputAnamorphicDownconversionFromHD720               = /* '72am' */ 0x3732616D,
    bmdVideoInputLetterboxUpconversion                           = /* 'lbup' */ 0x6C627570,
    bmdVideoInputAnamorphicUpconversion                          = /* 'amup' */ 0x616D7570
};

/* Enum BMDVideo3DPackingFormat - Video 3D packing format */

typedef uint32_t BMDVideo3DPackingFormat;
enum _BMDVideo3DPackingFormat {
    bmdVideo3DPackingSidebySideHalf                              = /* 'sbsh' */ 0x73627368,
    bmdVideo3DPackingLinebyLine                                  = /* 'lbyl' */ 0x6C62796C,
    bmdVideo3DPackingTopAndBottom                                = /* 'tabo' */ 0x7461626F,
    bmdVideo3DPackingFramePacking                                = /* 'frpk' */ 0x6672706B,
    bmdVideo3DPackingLeftOnly                                    = /* 'left' */ 0x6C656674,
    bmdVideo3DPackingRightOnly                                   = /* 'righ' */ 0x72696768
};

/* Enum BMDIdleVideoOutputOperation - Video output operation when not playing video */

typedef uint32_t BMDIdleVideoOutputOperation;
enum _BMDIdleVideoOutputOperation {
    bmdIdleVideoOutputBlack                                      = /* 'blac' */ 0x626C6163,
    bmdIdleVideoOutputLastFrame                                  = /* 'lafa' */ 0x6C616661
};

/* Enum BMDVideoEncoderFrameCodingMode - Video frame coding mode */

typedef uint32_t BMDVideoEncoderFrameCodingMode;
enum _BMDVideoEncoderFrameCodingMode {
    bmdVideoEncoderFrameCodingModeInter                          = /* 'inte' */ 0x696E7465,
    bmdVideoEncoderFrameCodingModeIntra                          = /* 'intr' */ 0x696E7472
};

/* Enum BMDDNxHRLevel - DNxHR Levels */

typedef uint32_t BMDDNxHRLevel;
enum _BMDDNxHRLevel {
    bmdDNxHRLevelSQ                                              = /* 'dnsq' */ 0x646E7371,
    bmdDNxHRLevelLB                                              = /* 'dnlb' */ 0x646E6C62,
    bmdDNxHRLevelHQ                                              = /* 'dnhq' */ 0x646E6871,
    bmdDNxHRLevelHQX                                             = /* 'dhqx' */ 0x64687178,
    bmdDNxHRLevel444                                             = /* 'd444' */ 0x64343434
};

/* Enum BMDLinkConfiguration - Video link configuration */

typedef uint32_t BMDLinkConfiguration;
enum _BMDLinkConfiguration {
    bmdLinkConfigurationSingleLink                               = /* 'lcsl' */ 0x6C63736C,
    bmdLinkConfigurationDualLink                                 = /* 'lcdl' */ 0x6C63646C,
    bmdLinkConfigurationQuadLink                                 = /* 'lcql' */ 0x6C63716C
};

/* Enum BMDDeviceInterface - Device interface type */

typedef uint32_t BMDDeviceInterface;
enum _BMDDeviceInterface {
    bmdDeviceInterfacePCI                                        = /* 'pci ' */ 0x70636920,
    bmdDeviceInterfaceUSB                                        = /* 'usb ' */ 0x75736220,
    bmdDeviceInterfaceThunderbolt                                = /* 'thun' */ 0x7468756E
};

/* Enum BMDDeckLinkFrameMetadataID - DeckLink Frame Metadata ID */

typedef uint32_t BMDDeckLinkFrameMetadataID;
enum _BMDDeckLinkFrameMetadataID {
    bmdDeckLinkFrameMetadataHDRElectroOpticalTransferFunc        = /* 'eotf' */ 0x656F7466,	// EOTF in range 0-7 as per CEA 861.3
    bmdDeckLinkFrameMetadataCintelFilmType                       = /* 'cfty' */ 0x63667479,	// Current film type
    bmdDeckLinkFrameMetadataCintelFilmGauge                      = /* 'cfga' */ 0x63666761,	// Current film gauge
    bmdDeckLinkFrameMetadataCintelOffsetDetectedHorizontal       = /* 'odfh' */ 0x6F646668,	// Horizontal offset (pixels) detected in image
    bmdDeckLinkFrameMetadataCintelOffsetDetectedVertical         = /* 'odfv' */ 0x6F646676,	// Vertical offset (pixels) detected in image
    bmdDeckLinkFrameMetadataCintelKeykodeLow                     = /* 'ckkl' */ 0x636B6B6C,	// Raw keykode value - low 64 bits
    bmdDeckLinkFrameMetadataCintelKeykodeHigh                    = /* 'ckkh' */ 0x636B6B68,	// Raw keykode value - high 64 bits
    bmdDeckLinkFrameMetadataCintelTile1Size                      = /* 'ct1s' */ 0x63743173,	// Size in bytes of compressed raw tile 1
    bmdDeckLinkFrameMetadataCintelTile2Size                      = /* 'ct2s' */ 0x63743273,	// Size in bytes of compressed raw tile 2
    bmdDeckLinkFrameMetadataCintelTile3Size                      = /* 'ct3s' */ 0x63743373,	// Size in bytes of compressed raw tile 3
    bmdDeckLinkFrameMetadataCintelTile4Size                      = /* 'ct4s' */ 0x63743473,	// Size in bytes of compressed raw tile 4
    bmdDeckLinkFrameMetadataCintelImageWidth                     = /* 'IWPx' */ 0x49575078,	// Width in pixels of image
    bmdDeckLinkFrameMetadataCintelImageHeight                    = /* 'IHPx' */ 0x49485078,	// Height in pixels of image
    bmdDeckLinkFrameMetadataCintelLinearMaskingRedInRed          = /* 'mrir' */ 0x6D726972,	// Red in red linear masking parameter
    bmdDeckLinkFrameMetadataCintelLinearMaskingGreenInRed        = /* 'mgir' */ 0x6D676972,	// Green in red linear masking parameter
    bmdDeckLinkFrameMetadataCintelLinearMaskingBlueInRed         = /* 'mbir' */ 0x6D626972,	// Blue in red linear masking parameter
    bmdDeckLinkFrameMetadataCintelLinearMaskingRedInGreen        = /* 'mrig' */ 0x6D726967,	// Red in green linear masking parameter
    bmdDeckLinkFrameMetadataCintelLinearMaskingGreenInGreen      = /* 'mgig' */ 0x6D676967,	// Green in green linear masking parameter
    bmdDeckLinkFrameMetadataCintelLinearMaskingBlueInGreen       = /* 'mbig' */ 0x6D626967,	// Blue in green linear masking parameter
    bmdDeckLinkFrameMetadataCintelLinearMaskingRedInBlue         = /* 'mrib' */ 0x6D726962,	// Red in blue linear masking parameter
    bmdDeckLinkFrameMetadataCintelLinearMaskingGreenInBlue       = /* 'mgib' */ 0x6D676962,	// Green in blue linear masking parameter
    bmdDeckLinkFrameMetadataCintelLinearMaskingBlueInBlue        = /* 'mbib' */ 0x6D626962,	// Blue in blue linear masking parameter
    bmdDeckLinkFrameMetadataCintelLogMaskingRedInRed             = /* 'mlrr' */ 0x6D6C7272,	// Red in red log masking parameter
    bmdDeckLinkFrameMetadataCintelLogMaskingGreenInRed           = /* 'mlgr' */ 0x6D6C6772,	// Green in red log masking parameter
    bmdDeckLinkFrameMetadataCintelLogMaskingBlueInRed            = /* 'mlbr' */ 0x6D6C6272,	// Blue in red log masking parameter
    bmdDeckLinkFrameMetadataCintelLogMaskingRedInGreen           = /* 'mlrg' */ 0x6D6C7267,	// Red in green log masking parameter
    bmdDeckLinkFrameMetadataCintelLogMaskingGreenInGreen         = /* 'mlgg' */ 0x6D6C6767,	// Green in green log masking parameter
    bmdDeckLinkFrameMetadataCintelLogMaskingBlueInGreen          = /* 'mlbg' */ 0x6D6C6267,	// Blue in green log masking parameter
    bmdDeckLinkFrameMetadataCintelLogMaskingRedInBlue            = /* 'mlrb' */ 0x6D6C7262,	// Red in blue log masking parameter
    bmdDeckLinkFrameMetadataCintelLogMaskingGreenInBlue          = /* 'mlgb' */ 0x6D6C6762,	// Green in blue log masking parameter
    bmdDeckLinkFrameMetadataCintelLogMaskingBlueInBlue           = /* 'mlbb' */ 0x6D6C6262,	// Blue in blue log masking parameter
    bmdDeckLinkFrameMetadataCintelFilmFrameRate                  = /* 'cffr' */ 0x63666672,	// Film frame rate
    bmdDeckLinkFrameMetadataHDRDisplayPrimariesRedX              = /* 'hdrx' */ 0x68647278,	// Red display primaries in range 0.0 - 1.0
    bmdDeckLinkFrameMetadataHDRDisplayPrimariesRedY              = /* 'hdry' */ 0x68647279,	// Red display primaries in range 0.0 - 1.0
    bmdDeckLinkFrameMetadataHDRDisplayPrimariesGreenX            = /* 'hdgx' */ 0x68646778,	// Green display primaries in range 0.0 - 1.0
    bmdDeckLinkFrameMetadataHDRDisplayPrimariesGreenY            = /* 'hdgy' */ 0x68646779,	// Green display primaries in range 0.0 - 1.0
    bmdDeckLinkFrameMetadataHDRDisplayPrimariesBlueX             = /* 'hdbx' */ 0x68646278,	// Blue display primaries in range 0.0 - 1.0
    bmdDeckLinkFrameMetadataHDRDisplayPrimariesBlueY             = /* 'hdby' */ 0x68646279,	// Blue display primaries in range 0.0 - 1.0
    bmdDeckLinkFrameMetadataHDRWhitePointX                       = /* 'hdwx' */ 0x68647778,	// White point in range 0.0 - 1.0
    bmdDeckLinkFrameMetadataHDRWhitePointY                       = /* 'hdwy' */ 0x68647779,	// White point in range 0.0 - 1.0
    bmdDeckLinkFrameMetadataHDRMaxDisplayMasteringLuminance      = /* 'hdml' */ 0x68646D6C,	// Max display mastering luminance in range 1 cd/m2 - 65535 cd/m2
    bmdDeckLinkFrameMetadataHDRMinDisplayMasteringLuminance      = /* 'hmil' */ 0x686D696C,	// Min display mastering luminance in range 0.0001 cd/m2 - 6.5535 cd/m2
    bmdDeckLinkFrameMetadataHDRMaximumContentLightLevel          = /* 'mcll' */ 0x6D636C6C,	// Maximum Content Light Level in range 1 cd/m2 - 65535 cd/m2
    bmdDeckLinkFrameMetadataHDRMaximumFrameAverageLightLevel     = /* 'fall' */ 0x66616C6C,	// Maximum Frame Average Light Level in range 1 cd/m2 - 65535 cd/m2
    bmdDeckLinkFrameMetadataCintelOffsetToApplyHorizontal        = /* 'otah' */ 0x6F746168,	// Horizontal offset (pixels) to be applied to image
    bmdDeckLinkFrameMetadataCintelOffsetToApplyVertical          = /* 'otav' */ 0x6F746176,	// Vertical offset (pixels) to be applied to image
    bmdDeckLinkFrameMetadataCintelGainRed                        = /* 'LfRd' */ 0x4C665264,	// Red gain parameter to apply after log
    bmdDeckLinkFrameMetadataCintelGainGreen                      = /* 'LfGr' */ 0x4C664772,	// Green gain parameter to apply after log
    bmdDeckLinkFrameMetadataCintelGainBlue                       = /* 'LfBl' */ 0x4C66426C,	// Blue gain parameter to apply after log
    bmdDeckLinkFrameMetadataCintelLiftRed                        = /* 'GnRd' */ 0x476E5264,	// Red lift parameter to apply after log and gain
    bmdDeckLinkFrameMetadataCintelLiftGreen                      = /* 'GnGr' */ 0x476E4772,	// Green lift parameter to apply after log and gain
    bmdDeckLinkFrameMetadataCintelLiftBlue                       = /* 'GnBl' */ 0x476E426C	// Blue lift parameter to apply after log and gain
};

/* Enum BMDDuplexMode - Duplex for configurable ports */

typedef uint32_t BMDDuplexMode;
enum _BMDDuplexMode {
    bmdDuplexModeFull                                            = /* 'fdup' */ 0x66647570,
    bmdDuplexModeHalf                                            = /* 'hdup' */ 0x68647570
};

/* Enum BMDDeckLinkAttributeID - DeckLink Attribute ID */

typedef uint32_t BMDDeckLinkAttributeID;
enum _BMDDeckLinkAttributeID {

    /* Flags */

    BMDDeckLinkSupportsInternalKeying                            = /* 'keyi' */ 0x6B657969,
    BMDDeckLinkSupportsExternalKeying                            = /* 'keye' */ 0x6B657965,
    BMDDeckLinkSupportsHDKeying                                  = /* 'keyh' */ 0x6B657968,
    BMDDeckLinkSupportsInputFormatDetection                      = /* 'infd' */ 0x696E6664,
    BMDDeckLinkHasReferenceInput                                 = /* 'hrin' */ 0x6872696E,
    BMDDeckLinkHasSerialPort                                     = /* 'hspt' */ 0x68737074,
    BMDDeckLinkHasAnalogVideoOutputGain                          = /* 'avog' */ 0x61766F67,
    BMDDeckLinkCanOnlyAdjustOverallVideoOutputGain               = /* 'ovog' */ 0x6F766F67,
    BMDDeckLinkHasVideoInputAntiAliasingFilter                   = /* 'aafl' */ 0x6161666C,
    BMDDeckLinkHasBypass                                         = /* 'byps' */ 0x62797073,
    BMDDeckLinkSupportsClockTimingAdjustment                     = /* 'ctad' */ 0x63746164,
    BMDDeckLinkSupportsFullDuplex                                = /* 'fdup' */ 0x66647570,
    BMDDeckLinkSupportsFullFrameReferenceInputTimingOffset       = /* 'frin' */ 0x6672696E,
    BMDDeckLinkSupportsSMPTELevelAOutput                         = /* 'lvla' */ 0x6C766C61,
    BMDDeckLinkSupportsDualLinkSDI                               = /* 'sdls' */ 0x73646C73,
    BMDDeckLinkSupportsQuadLinkSDI                               = /* 'sqls' */ 0x73716C73,
    BMDDeckLinkSupportsIdleOutput                                = /* 'idou' */ 0x69646F75,
    BMDDeckLinkHasLTCTimecodeInput                               = /* 'hltc' */ 0x686C7463,
    BMDDeckLinkSupportsDuplexModeConfiguration                   = /* 'dupx' */ 0x64757078,
    BMDDeckLinkSupportsHDRMetadata                               = /* 'hdrm' */ 0x6864726D,

    /* Integers */

    BMDDeckLinkMaximumAudioChannels                              = /* 'mach' */ 0x6D616368,
    BMDDeckLinkMaximumAnalogAudioInputChannels                   = /* 'iach' */ 0x69616368,
    BMDDeckLinkMaximumAnalogAudioOutputChannels                  = /* 'aach' */ 0x61616368,
    BMDDeckLinkNumberOfSubDevices                                = /* 'nsbd' */ 0x6E736264,
    BMDDeckLinkSubDeviceIndex                                    = /* 'subi' */ 0x73756269,
    BMDDeckLinkPersistentID                                      = /* 'peid' */ 0x70656964,
    BMDDeckLinkDeviceGroupID                                     = /* 'dgid' */ 0x64676964,
    BMDDeckLinkTopologicalID                                     = /* 'toid' */ 0x746F6964,
    BMDDeckLinkVideoOutputConnections                            = /* 'vocn' */ 0x766F636E,	// Returns a BMDVideoConnection bit field
    BMDDeckLinkVideoInputConnections                             = /* 'vicn' */ 0x7669636E,	// Returns a BMDVideoConnection bit field
    BMDDeckLinkAudioOutputConnections                            = /* 'aocn' */ 0x616F636E,	// Returns a BMDAudioConnection bit field
    BMDDeckLinkAudioInputConnections                             = /* 'aicn' */ 0x6169636E,	// Returns a BMDAudioConnection bit field
    BMDDeckLinkVideoIOSupport                                    = /* 'vios' */ 0x76696F73,	// Returns a BMDVideoIOSupport bit field
    BMDDeckLinkDeckControlConnections                            = /* 'dccn' */ 0x6463636E,	// Returns a BMDDeckControlConnection bit field
    BMDDeckLinkDeviceInterface                                   = /* 'dbus' */ 0x64627573,	// Returns a BMDDeviceInterface
    BMDDeckLinkAudioInputRCAChannelCount                         = /* 'airc' */ 0x61697263,
    BMDDeckLinkAudioInputXLRChannelCount                         = /* 'aixc' */ 0x61697863,
    BMDDeckLinkAudioOutputRCAChannelCount                        = /* 'aorc' */ 0x616F7263,
    BMDDeckLinkAudioOutputXLRChannelCount                        = /* 'aoxc' */ 0x616F7863,
    BMDDeckLinkPairedDevicePersistentID                          = /* 'ppid' */ 0x70706964,

    /* Floats */

    BMDDeckLinkVideoInputGainMinimum                             = /* 'vigm' */ 0x7669676D,
    BMDDeckLinkVideoInputGainMaximum                             = /* 'vigx' */ 0x76696778,
    BMDDeckLinkVideoOutputGainMinimum                            = /* 'vogm' */ 0x766F676D,
    BMDDeckLinkVideoOutputGainMaximum                            = /* 'vogx' */ 0x766F6778,
    BMDDeckLinkMicrophoneInputGainMinimum                        = /* 'migm' */ 0x6D69676D,
    BMDDeckLinkMicrophoneInputGainMaximum                        = /* 'migx' */ 0x6D696778,

    /* Strings */

    BMDDeckLinkSerialPortDeviceName                              = /* 'slpn' */ 0x736C706E,
    BMDDeckLinkVendorName                                        = /* 'vndr' */ 0x766E6472,
    BMDDeckLinkDisplayName                                       = /* 'dspn' */ 0x6473706E,
    BMDDeckLinkModelName                                         = /* 'mdln' */ 0x6D646C6E,
    BMDDeckLinkDeviceHandle                                      = /* 'devh' */ 0x64657668
};

/* Enum BMDDeckLinkAPIInformationID - DeckLinkAPI information ID */

typedef uint32_t BMDDeckLinkAPIInformationID;
enum _BMDDeckLinkAPIInformationID {
    BMDDeckLinkAPIVersion                                        = /* 'vers' */ 0x76657273
};

/* Enum BMDDeckLinkStatusID - DeckLink Status ID */

typedef uint32_t BMDDeckLinkStatusID;
enum _BMDDeckLinkStatusID {

    /* Integers */

    bmdDeckLinkStatusDetectedVideoInputMode                      = /* 'dvim' */ 0x6476696D,
    bmdDeckLinkStatusDetectedVideoInputFlags                     = /* 'dvif' */ 0x64766966,
    bmdDeckLinkStatusCurrentVideoInputMode                       = /* 'cvim' */ 0x6376696D,
    bmdDeckLinkStatusCurrentVideoInputPixelFormat                = /* 'cvip' */ 0x63766970,
    bmdDeckLinkStatusCurrentVideoInputFlags                      = /* 'cvif' */ 0x63766966,
    bmdDeckLinkStatusCurrentVideoOutputMode                      = /* 'cvom' */ 0x63766F6D,
    bmdDeckLinkStatusCurrentVideoOutputFlags                     = /* 'cvof' */ 0x63766F66,
    bmdDeckLinkStatusPCIExpressLinkWidth                         = /* 'pwid' */ 0x70776964,
    bmdDeckLinkStatusPCIExpressLinkSpeed                         = /* 'plnk' */ 0x706C6E6B,
    bmdDeckLinkStatusLastVideoOutputPixelFormat                  = /* 'opix' */ 0x6F706978,
    bmdDeckLinkStatusReferenceSignalMode                         = /* 'refm' */ 0x7265666D,
    bmdDeckLinkStatusReferenceSignalFlags                        = /* 'reff' */ 0x72656666,
    bmdDeckLinkStatusDuplexMode                                  = /* 'dupx' */ 0x64757078,
    bmdDeckLinkStatusBusy                                        = /* 'busy' */ 0x62757379,
    bmdDeckLinkStatusInterchangeablePanelType                    = /* 'icpt' */ 0x69637074,

    /* Flags */

    bmdDeckLinkStatusVideoInputSignalLocked                      = /* 'visl' */ 0x7669736C,
    bmdDeckLinkStatusReferenceSignalLocked                       = /* 'refl' */ 0x7265666C,
    bmdDeckLinkStatusReceivedEDID                                = /* 'edid' */ 0x65646964
};

/* Enum BMDDeckLinkVideoStatusFlags -  */

typedef uint32_t BMDDeckLinkVideoStatusFlags;
enum _BMDDeckLinkVideoStatusFlags {
    bmdDeckLinkVideoStatusPsF                                    = 1 << 0,
    bmdDeckLinkVideoStatusDualStream3D                           = 1 << 1
};

/* Enum BMDDuplexStatus - Duplex status of the device */

typedef uint32_t BMDDuplexStatus;
enum _BMDDuplexStatus {
    bmdDuplexStatusFullDuplex                                    = /* 'fdup' */ 0x66647570,
    bmdDuplexStatusHalfDuplex                                    = /* 'hdup' */ 0x68647570,
    bmdDuplexStatusSimplex                                       = /* 'splx' */ 0x73706C78,
    bmdDuplexStatusInactive                                      = /* 'inac' */ 0x696E6163
};

/* Enum BMDPanelType - The type of interchangeable panel */

typedef uint32_t BMDPanelType;
enum _BMDPanelType {
    bmdPanelNotDetected                                          = /* 'npnl' */ 0x6E706E6C,
    bmdPanelTeranexMiniSmartPanel                                = /* 'tmsm' */ 0x746D736D
};

/* Enum BMDDeviceBusyState - Current device busy state */

typedef uint32_t BMDDeviceBusyState;
enum _BMDDeviceBusyState {
    bmdDeviceCaptureBusy                                         = 1 << 0,
    bmdDevicePlaybackBusy                                        = 1 << 1,
    bmdDeviceSerialPortBusy                                      = 1 << 2
};

/* Enum BMDVideoIOSupport - Device video input/output support */

typedef uint32_t BMDVideoIOSupport;
enum _BMDVideoIOSupport {
    bmdDeviceSupportsCapture                                     = 1 << 0,
    bmdDeviceSupportsPlayback                                    = 1 << 1
};

/* Enum BMD3DPreviewFormat - Linked Frame preview format */

typedef uint32_t BMD3DPreviewFormat;
enum _BMD3DPreviewFormat {
    bmd3DPreviewFormatDefault                                    = /* 'defa' */ 0x64656661,
    bmd3DPreviewFormatLeftOnly                                   = /* 'left' */ 0x6C656674,
    bmd3DPreviewFormatRightOnly                                  = /* 'righ' */ 0x72696768,
    bmd3DPreviewFormatSideBySide                                 = /* 'side' */ 0x73696465,
    bmd3DPreviewFormatTopBottom                                  = /* 'topb' */ 0x746F7062
};

/* Enum BMDNotifications - Events that can be subscribed through IDeckLinkNotification */

typedef uint32_t BMDNotifications;
enum _BMDNotifications {
    bmdPreferencesChanged                                        = /* 'pref' */ 0x70726566,
    bmdStatusChanged                                             = /* 'stat' */ 0x73746174
};

#endif //BMD_DECKLINKAPI_H

#endif //DECKLINK_C_ENUMS_H
