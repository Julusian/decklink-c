#ifndef DECKLINK_C_API_H
#define DECKLINK_C_API_H

#include "common.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int64_t DecklinkTimeValue;
typedef int64_t DecklinkTimeScale;
typedef uint32_t DecklinkTimecodeBCD;
typedef uint32_t DecklinkTimecodeUserBits;
typedef uint32_t DecklinkTimecodeFlags;
typedef uint32_t DecklinkVideoConnection;
typedef uint32_t DecklinkAudioConnection;
typedef uint32_t DecklinkDeckControlConnection;
typedef uint32_t DecklinkDisplayMode;
typedef uint32_t DecklinkFieldDominance;
typedef uint32_t DecklinkPixelFormat;
typedef uint32_t DecklinkDisplayModeFlags;
typedef uint32_t DecklinkConfigurationID;
typedef uint32_t DecklinkEncoderConfigurationID;
typedef uint32_t DecklinkDeckControlMode;
typedef uint32_t DecklinkDeckControlEvent;
typedef uint32_t DecklinkDeckControlVTRControlState;
typedef uint32_t DecklinkDeckControlStatusFlags;
typedef uint32_t DecklinkDeckControlExportModeOpsFlags;
typedef uint32_t DecklinkDeckControlError;
typedef uint32_t DecklinkVideoOutputFlags;
typedef uint32_t DecklinkSupportedVideoModeFlags;
typedef uint32_t DecklinkPacketType;
typedef uint32_t DecklinkFrameFlags;
typedef uint32_t DecklinkVideoInputFlags;
typedef uint32_t DecklinkVideoInputFormatChangedEvents;
typedef uint32_t DecklinkDetectedVideoInputFormatFlags;
typedef uint32_t DecklinkCapturePassthroughMode;
typedef uint32_t DecklinkOutputFrameCompletionResult;
typedef uint32_t DecklinkReferenceStatus;
typedef uint32_t DecklinkAudioFormat;
typedef uint32_t DecklinkAudioSampleRate;
typedef uint32_t DecklinkAudioSampleType;
typedef uint32_t DecklinkAudioOutputStreamType;
typedef uint32_t DecklinkAncillaryPacketFormat;
typedef uint32_t DecklinkTimecodeFormat;
typedef uint32_t DecklinkAnalogVideoFlags;
typedef uint32_t DecklinkAudioOutputAnalogAESSwitch;
typedef uint32_t DecklinkVideoOutputConversionMode;
typedef uint32_t DecklinkVideoInputConversionMode;
typedef uint32_t DecklinkVideo3DPackingFormat;
typedef uint32_t DecklinkIdleVideoOutputOperation;
typedef uint32_t DecklinkVideoEncoderFrameCodingMode;
typedef uint32_t DecklinkDNxHRLevel;
typedef uint32_t DecklinkLinkConfiguration;
typedef uint32_t DecklinkDeviceInterface;
typedef uint32_t DecklinkColorspace;
typedef uint32_t DecklinkDynamicRange;
typedef uint32_t DecklinkHDMIInputEDIDID;
typedef uint32_t DecklinkFrameMetadataID;
typedef uint32_t DecklinkEthernetLinkState;
typedef uint32_t DecklinkProfileID;
typedef uint32_t DecklinkHDMITimecodePacking;
typedef uint32_t DecklinkInternalKeyingAncillaryDataSource;
typedef uint32_t DecklinkAttributeID;
typedef uint32_t DecklinkAPIInformationID;
typedef uint32_t DecklinkStatusID;
typedef uint32_t DecklinkVideoStatusFlags;
typedef uint32_t DecklinkDuplexMode;
typedef uint32_t DecklinkPanelType;
typedef uint32_t DecklinkDeviceBusyState;
typedef uint32_t DecklinkVideoIOSupport;
typedef uint32_t Decklink3DPreviewFormat;
typedef uint32_t DecklinkNotifications;

enum _DecklinkTimecodeFlags {
	decklinkTimecodeFlagDefault = 0,
	decklinkTimecodeIsDropFrame = 1,
	decklinkTimecodeFieldMark = 2,
	decklinkTimecodeColorFrame = 4,
	decklinkTimecodeEmbedRecordingTrigger = 8,
	decklinkTimecodeRecordingTriggered = 16,
};

enum _DecklinkVideoConnection {
	decklinkVideoConnectionUnspecified = 0,
	decklinkVideoConnectionSDI = 1,
	decklinkVideoConnectionHDMI = 2,
	decklinkVideoConnectionOpticalSDI = 4,
	decklinkVideoConnectionComponent = 8,
	decklinkVideoConnectionComposite = 16,
	decklinkVideoConnectionSVideo = 32,
	decklinkVideoConnectionEthernet = 64,
	decklinkVideoConnectionOpticalEthernet = 128,
};

enum _DecklinkAudioConnection {
	decklinkAudioConnectionEmbedded = 1,
	decklinkAudioConnectionAESEBU = 2,
	decklinkAudioConnectionAnalog = 4,
	decklinkAudioConnectionAnalogXLR = 8,
	decklinkAudioConnectionAnalogRCA = 16,
	decklinkAudioConnectionMicrophone = 32,
	decklinkAudioConnectionHeadphones = 64,
};

enum _DecklinkDeckControlConnection {
	decklinkDeckControlConnectionRS422Remote1 = 1,
	decklinkDeckControlConnectionRS422Remote2 = 2,
};

enum _DecklinkDisplayMode {
	decklinkModeNTSC = 1853125475,
	decklinkModeNTSC2398 = 1853108787,
	decklinkModePAL = 1885432864,
	decklinkModeNTSCp = 1853125488,
	decklinkModePALp = 1885432944,
	decklinkModeHD1080p2398 = 842231923,
	decklinkModeHD1080p24 = 842297459,
	decklinkModeHD1080p25 = 1215312437,
	decklinkModeHD1080p2997 = 1215312441,
	decklinkModeHD1080p30 = 1215312688,
	decklinkModeHD1080p4795 = 1215312951,
	decklinkModeHD1080p48 = 1215312952,
	decklinkModeHD1080p50 = 1215313200,
	decklinkModeHD1080p5994 = 1215313209,
	decklinkModeHD1080p6000 = 1215313456,
	decklinkModeHD1080p9590 = 1215314229,
	decklinkModeHD1080p96 = 1215314230,
	decklinkModeHD1080p100 = 1215312176,
	decklinkModeHD1080p11988 = 1215312177,
	decklinkModeHD1080p120 = 1215312178,
	decklinkModeHD1080i50 = 1214854448,
	decklinkModeHD1080i5994 = 1214854457,
	decklinkModeHD1080i6000 = 1214854704,
	decklinkModeHD720p50 = 1752184112,
	decklinkModeHD720p5994 = 1752184121,
	decklinkModeHD720p60 = 1752184368,
	decklinkMode2k2398 = 845886003,
	decklinkMode2k24 = 845886004,
	decklinkMode2k25 = 845886005,
	decklinkMode2kDCI2398 = 845427251,
	decklinkMode2kDCI24 = 845427252,
	decklinkMode2kDCI25 = 845427253,
	decklinkMode2kDCI2997 = 845427257,
	decklinkMode2kDCI30 = 845427504,
	decklinkMode2kDCI4795 = 845427767,
	decklinkMode2kDCI48 = 845427768,
	decklinkMode2kDCI50 = 845428016,
	decklinkMode2kDCI5994 = 845428025,
	decklinkMode2kDCI60 = 845428272,
	decklinkMode2kDCI9590 = 845429045,
	decklinkMode2kDCI96 = 845429046,
	decklinkMode2kDCI100 = 845426992,
	decklinkMode2kDCI11988 = 845426993,
	decklinkMode2kDCI120 = 845426994,
	decklinkMode4K2160p2398 = 879440435,
	decklinkMode4K2160p24 = 879440436,
	decklinkMode4K2160p25 = 879440437,
	decklinkMode4K2160p2997 = 879440441,
	decklinkMode4K2160p30 = 879440688,
	decklinkMode4K2160p4795 = 879440951,
	decklinkMode4K2160p48 = 879440952,
	decklinkMode4K2160p50 = 879441200,
	decklinkMode4K2160p5994 = 879441209,
	decklinkMode4K2160p60 = 879441456,
	decklinkMode4K2160p9590 = 879442229,
	decklinkMode4K2160p96 = 879442230,
	decklinkMode4K2160p100 = 879440176,
	decklinkMode4K2160p11988 = 879440177,
	decklinkMode4K2160p120 = 879440178,
	decklinkMode4kDCI2398 = 878981683,
	decklinkMode4kDCI24 = 878981684,
	decklinkMode4kDCI25 = 878981685,
	decklinkMode4kDCI2997 = 878981689,
	decklinkMode4kDCI30 = 878981936,
	decklinkMode4kDCI4795 = 878982199,
	decklinkMode4kDCI48 = 878982200,
	decklinkMode4kDCI50 = 878982448,
	decklinkMode4kDCI5994 = 878982457,
	decklinkMode4kDCI60 = 878982704,
	decklinkMode4kDCI9590 = 878983477,
	decklinkMode4kDCI96 = 878983478,
	decklinkMode4kDCI100 = 878981424,
	decklinkMode4kDCI11988 = 878981425,
	decklinkMode4kDCI120 = 878981426,
	decklinkMode8K4320p2398 = 946549299,
	decklinkMode8K4320p24 = 946549300,
	decklinkMode8K4320p25 = 946549301,
	decklinkMode8K4320p2997 = 946549305,
	decklinkMode8K4320p30 = 946549552,
	decklinkMode8K4320p4795 = 946549815,
	decklinkMode8K4320p48 = 946549816,
	decklinkMode8K4320p50 = 946550064,
	decklinkMode8K4320p5994 = 946550073,
	decklinkMode8K4320p60 = 946550320,
	decklinkMode8kDCI2398 = 946090547,
	decklinkMode8kDCI24 = 946090548,
	decklinkMode8kDCI25 = 946090549,
	decklinkMode8kDCI2997 = 946090553,
	decklinkMode8kDCI30 = 946090800,
	decklinkMode8kDCI4795 = 946091063,
	decklinkMode8kDCI48 = 946091064,
	decklinkMode8kDCI50 = 946091312,
	decklinkMode8kDCI5994 = 946091321,
	decklinkMode8kDCI60 = 946091568,
	decklinkMode640x480p60 = 1986486582,
	decklinkMode800x600p60 = 1937139510,
	decklinkMode1440x900p50 = 2004379445,
	decklinkMode1440x900p60 = 2004379446,
	decklinkMode1440x1080p50 = 1937270581,
	decklinkMode1440x1080p60 = 1937270582,
	decklinkMode1600x1200p50 = 1970825013,
	decklinkMode1600x1200p60 = 1970825014,
	decklinkMode1920x1200p50 = 2004187189,
	decklinkMode1920x1200p60 = 2004187190,
	decklinkMode1920x1440p50 = 825832501,
	decklinkMode1920x1440p60 = 825832502,
	decklinkMode2560x1440p50 = 2003920949,
	decklinkMode2560x1440p60 = 2003920950,
	decklinkMode2560x1600p50 = 2003925045,
	decklinkMode2560x1600p60 = 2003925046,
	decklinkModeUnknown = 1769303659,
};

enum _DecklinkFieldDominance {
	decklinkUnknownFieldDominance = 0,
	decklinkLowerFieldFirst = 1819244402,
	decklinkUpperFieldFirst = 1970303090,
	decklinkProgressiveFrame = 1886547815,
	decklinkProgressiveSegmentedFrame = 1886610976,
};

enum _DecklinkPixelFormat {
	decklinkFormatUnspecified = 0,
	decklinkFormat8BitYUV = 846624121,
	decklinkFormat10BitYUV = 1983000880,
	decklinkFormat8BitARGB = 32,
	decklinkFormat8BitBGRA = 1111970369,
	decklinkFormat10BitRGB = 1915892016,
	decklinkFormat12BitRGB = 1378955842,
	decklinkFormat12BitRGBLE = 1378955852,
	decklinkFormat10BitRGBXLE = 1378955372,
	decklinkFormat10BitRGBX = 1378955362,
	decklinkFormatH265 = 1751479857,
	decklinkFormatDNxHR = 1096180840,
};

enum _DecklinkDisplayModeFlags {
	decklinkDisplayModeSupports3D = 1,
	decklinkDisplayModeColorspaceRec601 = 2,
	decklinkDisplayModeColorspaceRec709 = 4,
	decklinkDisplayModeColorspaceRec2020 = 8,
};

enum _DecklinkConfigurationID {
	decklinkConfigSwapSerialRxTx = 1936945780,
	decklinkConfigHDMI3DPackingFormat = 862220390,
	decklinkConfigBypass = 1652125811,
	decklinkConfigClockTimingAdjustment = 1668571492,
	decklinkConfigAnalogAudioConsumerLevels = 1633772396,
	decklinkConfigSwapHDMICh3AndCh4OnInput = 1751724852,
	decklinkConfigSwapHDMICh3AndCh4OnOutput = 1752118068,
	decklinkConfigFieldFlickerRemoval = 1717855858,
	decklinkConfigHD1080p24ToHD1080i5994Conversion = 1953445177,
	decklinkConfig444SDIVideoOutput = 875836527,
	decklinkConfigBlackVideoOutputDuringCapture = 1651928931,
	decklinkConfigLowLatencyVideoOutput = 1819047535,
	decklinkConfigDownConversionOnAllAnalogOutput = 1667326319,
	decklinkConfigSMPTELevelAOutput = 1936553057,
	decklinkConfigRec2020Output = 1919247154,
	decklinkConfigQuadLinkSDIVideoOutputSquareDivisionSplit = 1396986195,
	decklinkConfigOutput1080pAsPsF = 1885761650,
	decklinkConfigVideoOutputConnection = 1987011438,
	decklinkConfigVideoOutputConversionMode = 1987011437,
	decklinkConfigAnalogVideoOutputFlags = 1635151718,
	decklinkConfigReferenceInputTimingOffset = 1735159668,
	decklinkConfigReferenceOutputMode = 1735151469,
	decklinkConfigVideoOutputIdleOperation = 1987012975,
	decklinkConfigDefaultVideoOutputMode = 1685483373,
	decklinkConfigDefaultVideoOutputModeFlags = 1685483366,
	decklinkConfigSDIOutputLinkConfiguration = 1936682083,
	decklinkConfigHDMITimecodePacking = 1752461419,
	decklinkConfigPlaybackGroup = 1886152562,
	decklinkConfigVideoOutputComponentLumaGain = 1868786791,
	decklinkConfigVideoOutputComponentChromaBlueGain = 1868784482,
	decklinkConfigVideoOutputComponentChromaRedGain = 1868784498,
	decklinkConfigVideoOutputCompositeLumaGain = 1869180007,
	decklinkConfigVideoOutputCompositeChromaGain = 1869177703,
	decklinkConfigVideoOutputSVideoLumaGain = 1869835367,
	decklinkConfigVideoOutputSVideoChromaGain = 1869833063,
	decklinkConfigVideoInputScanning = 1986622307,
	decklinkConfigUseDedicatedLTCInput = 1684829283,
	decklinkConfigSDIInput3DPayloadOverride = 862217331,
	decklinkConfigCapture1080pAsPsF = 1667657842,
	decklinkConfigVideoInputConnection = 1986618222,
	decklinkConfigAnalogVideoInputFlags = 1635150182,
	decklinkConfigVideoInputConversionMode = 1986618221,
	decklinkConfig32PulldownSequenceInitialTimecodeFrame = 1885628774,
	decklinkConfigVANCSourceLine1Mapping = 1987275825,
	decklinkConfigVANCSourceLine2Mapping = 1987275826,
	decklinkConfigVANCSourceLine3Mapping = 1987275827,
	decklinkConfigCapturePassThroughMode = 1668314221,
	decklinkConfigCaptureGroup = 1668310898,
	decklinkConfigVideoInputComponentLumaGain = 1768123495,
	decklinkConfigVideoInputComponentChromaBlueGain = 1768121186,
	decklinkConfigVideoInputComponentChromaRedGain = 1768121202,
	decklinkConfigVideoInputCompositeLumaGain = 1768516711,
	decklinkConfigVideoInputCompositeChromaGain = 1768514407,
	decklinkConfigVideoInputSVideoLumaGain = 1769172071,
	decklinkConfigVideoInputSVideoChromaGain = 1769169767,
	decklinkConfigInternalKeyingAncillaryDataSource = 1768644979,
	decklinkConfigMicrophonePhantomPower = 1836083312,
	decklinkConfigAudioInputConnection = 1634296686,
	decklinkConfigAnalogAudioInputScaleChannel1 = 1634300721,
	decklinkConfigAnalogAudioInputScaleChannel2 = 1634300722,
	decklinkConfigAnalogAudioInputScaleChannel3 = 1634300723,
	decklinkConfigAnalogAudioInputScaleChannel4 = 1634300724,
	decklinkConfigDigitalAudioInputScale = 1684105587,
	decklinkConfigMicrophoneInputGain = 1835623271,
	decklinkConfigAudioOutputAESAnalogSwitch = 1634689377,
	decklinkConfigAnalogAudioOutputScaleChannel1 = 1634693937,
	decklinkConfigAnalogAudioOutputScaleChannel2 = 1634693938,
	decklinkConfigAnalogAudioOutputScaleChannel3 = 1634693939,
	decklinkConfigAnalogAudioOutputScaleChannel4 = 1634693940,
	decklinkConfigDigitalAudioOutputScale = 1684107123,
	decklinkConfigHeadphoneVolume = 1752592236,
	decklinkConfigEthernetUseDHCP = 1145586512,
	decklinkConfigEthernetPTPFollowerOnly = 1347702886,
	decklinkConfigEthernetPTPUseUDPEncapsulation = 1347702869,
	decklinkConfigEthernetPTPPriority1 = 1347702833,
	decklinkConfigEthernetPTPPriority2 = 1347702834,
	decklinkConfigEthernetPTPDomain = 1347702852,
	decklinkConfigEthernetStaticLocalIPAddress = 1853057392,
	decklinkConfigEthernetStaticSubnetMask = 1853059949,
	decklinkConfigEthernetStaticGatewayIPAddress = 1853056887,
	decklinkConfigEthernetStaticPrimaryDNS = 1853059172,
	decklinkConfigEthernetStaticSecondaryDNS = 1853059940,
	decklinkConfigEthernetVideoOutputAddress = 1852793206,
	decklinkConfigEthernetAudioOutputAddress = 1852793185,
	decklinkConfigEthernetAncillaryOutputAddress = 1852793153,
	decklinkConfigEthernetAudioOutputChannelOrder = 1667326831,
	decklinkConfigDeviceInformationLabel = 1684630625,
	decklinkConfigDeviceInformationSerialNumber = 1684632430,
	decklinkConfigDeviceInformationCompany = 1684628335,
	decklinkConfigDeviceInformationPhone = 1684631656,
	decklinkConfigDeviceInformationEmail = 1684628845,
	decklinkConfigDeviceInformationDate = 1684628577,
	decklinkConfigDeckControlConnection = 1684235119,
};

enum _DecklinkEncoderConfigurationID {
	decklinkEncoderConfigPreferredBitDepth = 1701864050,
	decklinkEncoderConfigFrameCodingMode = 1701208941,
	decklinkEncoderConfigH265TargetBitrate = 1752457842,
	decklinkEncoderConfigDNxHRCompressionID = 1684236644,
	decklinkEncoderConfigDNxHRLevel = 1684825462,
	decklinkEncoderConfigMPEG4SampleDescription = 1937011525,
	decklinkEncoderConfigMPEG4CodecSpecificDesc = 1702061171,
};

enum _DecklinkDeckControlMode {
	decklinkDeckControlNotOpened = 1853124464,
	decklinkDeckControlVTRControlMode = 1987342947,
	decklinkDeckControlExportMode = 1702391917,
	decklinkDeckControlCaptureMode = 1667330157,
};

enum _DecklinkDeckControlEvent {
	decklinkDeckControlAbortedEvent = 1633842277,
	decklinkDeckControlPrepareForExportEvent = 1885758821,
	decklinkDeckControlExportCompleteEvent = 1702388581,
	decklinkDeckControlPrepareForCaptureEvent = 1885758309,
	decklinkDeckControlCaptureCompleteEvent = 1667458422,
};

enum _DecklinkDeckControlVTRControlState {
	decklinkDeckControlNotInVTRControlMode = 1853252461,
	decklinkDeckControlVTRControlPlaying = 1987342960,
	decklinkDeckControlVTRControlRecording = 1987342962,
	decklinkDeckControlVTRControlStill = 1987342945,
	decklinkDeckControlVTRControlShuttleForward = 1987343206,
	decklinkDeckControlVTRControlShuttleReverse = 1987343218,
	decklinkDeckControlVTRControlJogForward = 1987340902,
	decklinkDeckControlVTRControlJogReverse = 1987340914,
	decklinkDeckControlVTRControlStopped = 1987342959,
};

enum _DecklinkDeckControlStatusFlags {
	decklinkDeckControlStatusDeckConnected = 1,
	decklinkDeckControlStatusRemoteMode = 2,
	decklinkDeckControlStatusRecordInhibited = 4,
	decklinkDeckControlStatusCassetteOut = 8,
};

enum _DecklinkDeckControlExportModeOpsFlags {
	decklinkDeckControlExportModeInsertVideo = 1,
	decklinkDeckControlExportModeInsertAudio1 = 2,
	decklinkDeckControlExportModeInsertAudio2 = 4,
	decklinkDeckControlExportModeInsertAudio3 = 8,
	decklinkDeckControlExportModeInsertAudio4 = 16,
	decklinkDeckControlExportModeInsertAudio5 = 32,
	decklinkDeckControlExportModeInsertAudio6 = 64,
	decklinkDeckControlExportModeInsertAudio7 = 128,
	decklinkDeckControlExportModeInsertAudio8 = 256,
	decklinkDeckControlExportModeInsertAudio9 = 512,
	decklinkDeckControlExportModeInsertAudio10 = 1024,
	decklinkDeckControlExportModeInsertAudio11 = 2048,
	decklinkDeckControlExportModeInsertAudio12 = 4096,
	decklinkDeckControlExportModeInsertTimeCode = 8192,
	decklinkDeckControlExportModeInsertAssemble = 16384,
	decklinkDeckControlExportModeInsertPreview = 32768,
	decklinkDeckControlUseManualExport = 65536,
};

enum _DecklinkDeckControlError {
	decklinkDeckControlNoError = 1852794226,
	decklinkDeckControlModeError = 1836017010,
	decklinkDeckControlMissedInPointError = 1835623794,
	decklinkDeckControlDeckTimeoutError = 1685349746,
	decklinkDeckControlCommandFailedError = 1667655026,
	decklinkDeckControlDeviceAlreadyOpenedError = 1684106351,
	decklinkDeckControlFailedToOpenDeviceError = 1717855602,
	decklinkDeckControlInLocalModeError = 1819108722,
	decklinkDeckControlEndOfTapeError = 1702126962,
	decklinkDeckControlUserAbortError = 1969317234,
	decklinkDeckControlNoTapeInDeckError = 1853121906,
	decklinkDeckControlNoVideoFromCardError = 1853253219,
	decklinkDeckControlNoCommunicationError = 1852010349,
	decklinkDeckControlBufferTooSmallError = 1651798893,
	decklinkDeckControlBadChecksumError = 1667787635,
	decklinkDeckControlUnknownError = 1970169202,
};

enum _DecklinkVideoOutputFlags {
	decklinkVideoOutputFlagDefault = 0,
	decklinkVideoOutputVANC = 1,
	decklinkVideoOutputVITC = 2,
	decklinkVideoOutputRP188 = 4,
	decklinkVideoOutputDualStream3D = 16,
	decklinkVideoOutputSynchronizeToPlaybackGroup = 64,
};

enum _DecklinkSupportedVideoModeFlags {
	decklinkSupportedVideoModeDefault = 0,
	decklinkSupportedVideoModeKeying = 1,
	decklinkSupportedVideoModeDualStream3D = 2,
	decklinkSupportedVideoModeSDISingleLink = 4,
	decklinkSupportedVideoModeSDIDualLink = 8,
	decklinkSupportedVideoModeSDIQuadLink = 16,
	decklinkSupportedVideoModeInAnyProfile = 32,
	decklinkSupportedVideoModePsF = 64,
};

enum _DecklinkPacketType {
	decklinkPacketTypeStreamInterruptedMarker = 1936289396,
	decklinkPacketTypeStreamData = 1935958388,
};

enum _DecklinkFrameFlags {
	decklinkFrameFlagDefault = 0,
	decklinkFrameFlagFlipVertical = 1,
	decklinkFrameContainsHDRMetadata = 2,
	decklinkFrameCapturedAsPsF = 1073741824,
	decklinkFrameHasNoInputSource = 2147483648,
};

enum _DecklinkVideoInputFlags {
	decklinkVideoInputFlagDefault = 0,
	decklinkVideoInputEnableFormatDetection = 1,
	decklinkVideoInputDualStream3D = 2,
	decklinkVideoInputSynchronizeToCaptureGroup = 4,
};

enum _DecklinkVideoInputFormatChangedEvents {
	decklinkVideoInputDisplayModeChanged = 1,
	decklinkVideoInputFieldDominanceChanged = 2,
	decklinkVideoInputColorspaceChanged = 4,
};

enum _DecklinkDetectedVideoInputFormatFlags {
	decklinkDetectedVideoInputYCbCr422 = 1,
	decklinkDetectedVideoInputRGB444 = 2,
	decklinkDetectedVideoInputDualStream3D = 4,
	decklinkDetectedVideoInput12BitDepth = 8,
	decklinkDetectedVideoInput10BitDepth = 16,
	decklinkDetectedVideoInput8BitDepth = 32,
};

enum _DecklinkCapturePassthroughMode {
	decklinkCapturePassthroughModeDisabled = 1885628787,
	decklinkCapturePassthroughModeDirect = 1885628786,
	decklinkCapturePassthroughModeCleanSwitch = 1885564014,
};

enum _DecklinkOutputFrameCompletionResult {
	decklinkOutputFrameCompleted = 0,
	decklinkOutputFrameDisplayedLate = 1,
	decklinkOutputFrameDropped = 2,
	decklinkOutputFrameFlushed = 3,
};

enum _DecklinkReferenceStatus {
	decklinkReferenceUnlocked = 0,
	decklinkReferenceNotSupportedByHardware = 1,
	decklinkReferenceLocked = 2,
};

enum _DecklinkAudioFormat {
	decklinkAudioFormatPCM = 1819304813,
};

enum _DecklinkAudioSampleRate {
	decklinkAudioSampleRate48kHz = 48000,
};

enum _DecklinkAudioSampleType {
	decklinkAudioSampleType16bitInteger = 16,
	decklinkAudioSampleType32bitInteger = 32,
};

enum _DecklinkAudioOutputStreamType {
	decklinkAudioOutputStreamContinuous = 0,
	decklinkAudioOutputStreamContinuousDontResample = 1,
	decklinkAudioOutputStreamTimestamped = 2,
};

enum _DecklinkAncillaryPacketFormat {
	decklinkAncillaryPacketFormatUInt8 = 1969827896,
	decklinkAncillaryPacketFormatUInt16 = 1969828150,
	decklinkAncillaryPacketFormatYCbCr10 = 1983000880,
};

enum _DecklinkTimecodeFormat {
	decklinkTimecodeRP188VITC1 = 1919972913,
	decklinkTimecodeRP188VITC2 = 1919955250,
	decklinkTimecodeRP188LTC = 1919970420,
	decklinkTimecodeRP188HighFrameRate = 1919969394,
	decklinkTimecodeRP188Any = 1919955256,
	decklinkTimecodeVITC = 1986622563,
	decklinkTimecodeVITCField2 = 1986622514,
	decklinkTimecodeSerial = 1936028265,
};

enum _DecklinkAnalogVideoFlags {
	decklinkAnalogVideoFlagCompositeSetup75 = 1,
	decklinkAnalogVideoFlagComponentBetacamLevels = 2,
};

enum _DecklinkAudioOutputAnalogAESSwitch {
	decklinkAudioOutputSwitchAESEBU = 1634038560,
	decklinkAudioOutputSwitchAnalog = 1634626663,
};

enum _DecklinkVideoOutputConversionMode {
	decklinkNoVideoOutputConversion = 1852796517,
	decklinkVideoOutputLetterboxDownconversion = 1819566712,
	decklinkVideoOutputAnamorphicDownconversion = 1634562152,
	decklinkVideoOutputHD720toHD1080Conversion = 926036067,
	decklinkVideoOutputHardwareLetterboxDownconversion = 1213688930,
	decklinkVideoOutputHardwareAnamorphicDownconversion = 1213686125,
	decklinkVideoOutputHardwareCenterCutDownconversion = 1213686627,
	decklinkVideoOutputHardware720p1080pCrossconversion = 2019778928,
	decklinkVideoOutputHardwareAnamorphic720pUpconversion = 1969305456,
	decklinkVideoOutputHardwareAnamorphic1080iUpconversion = 1969303913,
	decklinkVideoOutputHardwareAnamorphic149To720pUpconversion = 1966356336,
	decklinkVideoOutputHardwareAnamorphic149To1080iUpconversion = 1966354793,
	decklinkVideoOutputHardwarePillarbox720pUpconversion = 1970288496,
	decklinkVideoOutputHardwarePillarbox1080iUpconversion = 1970286953,
};

enum _DecklinkVideoInputConversionMode {
	decklinkNoVideoInputConversion = 1852796517,
	decklinkVideoInputLetterboxDownconversionFromHD1080 = 825257058,
	decklinkVideoInputAnamorphicDownconversionFromHD1080 = 825254253,
	decklinkVideoInputLetterboxDownconversionFromHD720 = 926051426,
	decklinkVideoInputAnamorphicDownconversionFromHD720 = 926048621,
	decklinkVideoInputLetterboxUpconversion = 1818391920,
	decklinkVideoInputAnamorphicUpconversion = 1634563440,
};

enum _DecklinkVideo3DPackingFormat {
	decklinkVideo3DPackingSidebySideHalf = 1935831912,
	decklinkVideo3DPackingLinebyLine = 1818392940,
	decklinkVideo3DPackingTopAndBottom = 1952539247,
	decklinkVideo3DPackingFramePacking = 1718775915,
	decklinkVideo3DPackingLeftOnly = 1818584692,
	decklinkVideo3DPackingRightOnly = 1919510376,
};

enum _DecklinkIdleVideoOutputOperation {
	decklinkIdleVideoOutputBlack = 1651269987,
	decklinkIdleVideoOutputLastFrame = 1818322529,
};

enum _DecklinkVideoEncoderFrameCodingMode {
	decklinkVideoEncoderFrameCodingModeInter = 1768846437,
	decklinkVideoEncoderFrameCodingModeIntra = 1768846450,
};

enum _DecklinkDNxHRLevel {
	decklinkDNxHRLevelSQ = 1684960113,
	decklinkDNxHRLevelLB = 1684958306,
	decklinkDNxHRLevelHQ = 1684957297,
	decklinkDNxHRLevelHQX = 1684566392,
	decklinkDNxHRLevel444 = 1681142836,
};

enum _DecklinkLinkConfiguration {
	decklinkLinkConfigurationSingleLink = 1818456940,
	decklinkLinkConfigurationDualLink = 1818453100,
	decklinkLinkConfigurationQuadLink = 1818456428,
};

enum _DecklinkDeviceInterface {
	decklinkDeviceInterfacePCI = 1885563168,
	decklinkDeviceInterfaceUSB = 1970496032,
	decklinkDeviceInterfaceThunderbolt = 1953002862,
};

enum _DecklinkColorspace {
	decklinkColorspaceRec601 = 1916153905,
	decklinkColorspaceRec709 = 1916219449,
	decklinkColorspaceRec2020 = 842019376,
};

enum _DecklinkDynamicRange {
	decklinkDynamicRangeSDR = 0,
	decklinkDynamicRangeHDRStaticPQ = 536870912,
	decklinkDynamicRangeHDRStaticHLG = 1073741824,
};

enum _DecklinkHDMIInputEDIDID {
	decklinkHDMIInputEDIDDynamicRange = 1212761209,
};

enum _DecklinkFrameMetadataID {
	decklinkFrameMetadataColorspace = 1668509795,
	decklinkFrameMetadataHDRElectroOpticalTransferFunc = 1701803110,
	decklinkFrameMetadataHDRDisplayPrimariesRedX = 1751413368,
	decklinkFrameMetadataHDRDisplayPrimariesRedY = 1751413369,
	decklinkFrameMetadataHDRDisplayPrimariesGreenX = 1751410552,
	decklinkFrameMetadataHDRDisplayPrimariesGreenY = 1751410553,
	decklinkFrameMetadataHDRDisplayPrimariesBlueX = 1751409272,
	decklinkFrameMetadataHDRDisplayPrimariesBlueY = 1751409273,
	decklinkFrameMetadataHDRWhitePointX = 1751414648,
	decklinkFrameMetadataHDRWhitePointY = 1751414649,
	decklinkFrameMetadataHDRMaxDisplayMasteringLuminance = 1751412076,
	decklinkFrameMetadataHDRMinDisplayMasteringLuminance = 1752000876,
	decklinkFrameMetadataHDRMaximumContentLightLevel = 1835232364,
	decklinkFrameMetadataHDRMaximumFrameAverageLightLevel = 1717660780,
};

enum _DecklinkEthernetLinkState {
	decklinkEthernetLinkStateDisconnected = 1701602419,
	decklinkEthernetLinkStateConnectedUnbound = 1701602165,
	decklinkEthernetLinkStateConnectedBound = 1701602146,
};

enum _DecklinkProfileID {
	decklinkProfileOneSubDeviceFullDuplex = 828663396,
	decklinkProfileOneSubDeviceHalfDuplex = 828663908,
	decklinkProfileTwoSubDevicesFullDuplex = 845440612,
	decklinkProfileTwoSubDevicesHalfDuplex = 845441124,
	decklinkProfileFourSubDevicesHalfDuplex = 878995556,
};

enum _DecklinkHDMITimecodePacking {
	decklinkHDMITimecodePackingIEEEOUI000085 = 34048,
	decklinkHDMITimecodePackingIEEEOUI080046 = 134235649,
	decklinkHDMITimecodePackingIEEEOUI5CF9F0 = 1559883779,
};

enum _DecklinkInternalKeyingAncillaryDataSource {
	decklinkInternalKeyingUsesAncillaryDataFromInputSignal = 1768644969,
	decklinkInternalKeyingUsesAncillaryDataFromKeyFrame = 1768644971,
};

enum _DecklinkAttributeID {
	decklinkSupportsInternalKeying = 1801812329,
	decklinkSupportsExternalKeying = 1801812325,
	decklinkSupportsInputFormatDetection = 1768842852,
	decklinkHasReferenceInput = 1752328558,
	decklinkHasSerialPort = 1752395892,
	decklinkHasAnalogVideoOutputGain = 1635151719,
	decklinkCanOnlyAdjustOverallVideoOutputGain = 1870032743,
	decklinkHasVideoInputAntiAliasingFilter = 1633773164,
	decklinkHasBypass = 1652125811,
	decklinkSupportsClockTimingAdjustment = 1668571492,
	decklinkSupportsFullFrameReferenceInputTimingOffset = 1718774126,
	decklinkSupportsSMPTELevelAOutput = 1819700321,
	decklinkSupportsAutoSwitchingPPsFOnInput = 1634759526,
	decklinkSupportsDualLinkSDI = 1935961203,
	decklinkSupportsQuadLinkSDI = 1936813171,
	decklinkSupportsIdleOutput = 1768189813,
	decklinkVANCRequires10BitYUVVideoFrames = 1986621273,
	decklinkHasLTCTimecodeInput = 1751938147,
	decklinkSupportsHDRMetadata = 1751413357,
	decklinkSupportsColorspaceMetadata = 1668113780,
	decklinkSupportsHDMITimecode = 1752459629,
	decklinkSupportsHighFrameRateTimecode = 1212568148,
	decklinkSupportsSynchronizeToCaptureGroup = 1937007463,
	decklinkSupportsSynchronizeToPlaybackGroup = 1937010791,
	decklinkMaximumAudioChannels = 1835098984,
	decklinkMaximumAnalogAudioInputChannels = 1767990120,
	decklinkMaximumAnalogAudioOutputChannels = 1633772392,
	decklinkNumberOfSubDevices = 1853055588,
	decklinkSubDeviceIndex = 1937072745,
	decklinkPersistentID = 1885694308,
	decklinkDeviceGroupID = 1684498788,
	decklinkTopologicalID = 1953458532,
	decklinkVideoOutputConnections = 1987011438,
	decklinkVideoInputConnections = 1986618222,
	decklinkAudioOutputConnections = 1634689902,
	decklinkAudioInputConnections = 1634296686,
	decklinkVideoIOSupport = 1986621299,
	decklinkDeckControlConnections = 1684235118,
	decklinkDeviceInterface = 1684174195,
	decklinkAudioInputRCAChannelCount = 1634300515,
	decklinkAudioInputXLRChannelCount = 1634302051,
	decklinkAudioOutputRCAChannelCount = 1634693731,
	decklinkAudioOutputXLRChannelCount = 1634695267,
	decklinkProfileID = 1886546276,
	decklinkDuplex = 1685418104,
	decklinkMinimumPrerollFrames = 1836085862,
	decklinkSupportedDynamicRange = 1937073266,
	decklinkVideoInputGainMinimum = 1986619245,
	decklinkVideoInputGainMaximum = 1986619256,
	decklinkVideoOutputGainMinimum = 1987012461,
	decklinkVideoOutputGainMaximum = 1987012472,
	decklinkMicrophoneInputGainMinimum = 1835624301,
	decklinkMicrophoneInputGainMaximum = 1835624312,
	decklinkSerialPortDeviceName = 1936486510,
	decklinkVendorName = 1986946162,
	decklinkDisplayName = 1685287022,
	decklinkModelName = 1835297902,
	decklinkDeviceHandle = 1684371048,
	decklinkEthernetMACAddress = 1699561795,
};

enum _DecklinkAPIInformationID {
	decklinkAPIVersion = 1986359923,
};

enum _DecklinkStatusID {
	decklinkStatusDetectedVideoInputMode = 1685481837,
	decklinkStatusDetectedVideoInputFormatFlags = 1685481062,
	decklinkStatusDetectedVideoInputFieldDominance = 1685481060,
	decklinkStatusDetectedVideoInputColorspace = 1685283692,
	decklinkStatusDetectedVideoInputDynamicRange = 1685283954,
	decklinkStatusDetectedSDILinkConfiguration = 1685285987,
	decklinkStatusCurrentVideoInputMode = 1668704621,
	decklinkStatusCurrentVideoInputPixelFormat = 1668704624,
	decklinkStatusCurrentVideoInputFlags = 1668704614,
	decklinkStatusCurrentVideoOutputMode = 1668706157,
	decklinkStatusCurrentVideoOutputFlags = 1668706150,
	decklinkStatusEthernetLink = 1936026739,
	decklinkStatusEthernetLinkMbps = 1936028528,
	decklinkStatusPCIExpressLinkWidth = 1886873956,
	decklinkStatusPCIExpressLinkSpeed = 1886154347,
	decklinkStatusLastVideoOutputPixelFormat = 1869638008,
	decklinkStatusReferenceSignalMode = 1919247981,
	decklinkStatusReferenceSignalFlags = 1919247974,
	decklinkStatusBusy = 1651864441,
	decklinkStatusInterchangeablePanelType = 1768124532,
	decklinkStatusDeviceTemperature = 1685351792,
	decklinkStatusVideoInputSignalLocked = 1986622316,
	decklinkStatusReferenceSignalLocked = 1919247980,
	decklinkStatusEthernetLocalIPAddress = 1936025968,
	decklinkStatusEthernetSubnetMask = 1936028525,
	decklinkStatusEthernetGatewayIPAddress = 1936025463,
	decklinkStatusEthernetPrimaryDNS = 1936027748,
	decklinkStatusEthernetSecondaryDNS = 1936028516,
	decklinkStatusEthernetPTPGrandmasterIdentity = 1936746852,
	decklinkStatusEthernetVideoOutputAddress = 1936679286,
	decklinkStatusEthernetAudioOutputAddress = 1936679265,
	decklinkStatusEthernetAncillaryOutputAddress = 1936679233,
	decklinkStatusEthernetAudioInputChannelOrder = 1935762287,
	decklinkStatusReceivedEDID = 1701079396,
};

enum _DecklinkVideoStatusFlags {
	decklinkVideoStatusPsF = 1,
	decklinkVideoStatusDualStream3D = 2,
};

enum _DecklinkDuplexMode {
	decklinkDuplexFull = 1685612149,
	decklinkDuplexHalf = 1685612641,
	decklinkDuplexSimplex = 1685615472,
	decklinkDuplexInactive = 1685612910,
};

enum _DecklinkPanelType {
	decklinkPanelNotDetected = 1852862060,
	decklinkPanelTeranexMiniSmartPanel = 1953330029,
};

enum _DecklinkDeviceBusyState {
	decklinkDeviceCaptureBusy = 1,
	decklinkDevicePlaybackBusy = 2,
	decklinkDeviceSerialPortBusy = 4,
};

enum _DecklinkVideoIOSupport {
	decklinkDeviceSupportsCapture = 1,
	decklinkDeviceSupportsPlayback = 2,
};

enum _Decklink3DPreviewFormat {
	decklink3DPreviewFormatDefault = 1684366945,
	decklink3DPreviewFormatLeftOnly = 1818584692,
	decklink3DPreviewFormatRightOnly = 1919510376,
	decklink3DPreviewFormatSideBySide = 1936286821,
	decklink3DPreviewFormatTopBottom = 1953460322,
};

enum _DecklinkNotifications {
	decklinkPreferencesChanged = 1886545254,
	decklinkStatusChanged = 1937006964,
};


typedef HRESULT cdecklink_deck_control_status_callback_timecode_update(void *obj, DecklinkTimecodeBCD currentTimecode);
typedef HRESULT cdecklink_deck_control_status_callback_vtr_control_state_changed(void *obj, DecklinkDeckControlVTRControlState newState, DecklinkDeckControlError error);
typedef HRESULT cdecklink_deck_control_status_callback_deck_control_event_received(void *obj, DecklinkDeckControlEvent event, DecklinkDeckControlError error);
typedef HRESULT cdecklink_deck_control_status_callback_deck_control_status_changed(void *obj, DecklinkDeckControlStatusFlags flags, uint32_t mask);

typedef HRESULT cdecklink_video_output_callback_scheduled_frame_completed(void *obj, cdecklink_video_frame_t * completedFrame, DecklinkOutputFrameCompletionResult result);
typedef HRESULT cdecklink_video_output_callback_scheduled_playback_has_stopped(void *obj);

typedef HRESULT cdecklink_input_callback_video_input_format_changed(void *obj, DecklinkVideoInputFormatChangedEvents notificationEvents, cdecklink_display_mode_t * newDisplayMode, DecklinkDetectedVideoInputFormatFlags detectedSignalFlags);
typedef HRESULT cdecklink_input_callback_video_input_frame_arrived(void *obj, cdecklink_video_input_frame_t * videoFrame, cdecklink_audio_input_packet_t * audioPacket);

typedef HRESULT cdecklink_encoder_input_callback_video_input_signal_changed(void *obj, DecklinkVideoInputFormatChangedEvents notificationEvents, cdecklink_display_mode_t * newDisplayMode, DecklinkDetectedVideoInputFormatFlags detectedSignalFlags);
typedef HRESULT cdecklink_encoder_input_callback_video_packet_arrived(void *obj, cdecklink_encoder_video_packet_t * videoPacket);
typedef HRESULT cdecklink_encoder_input_callback_audio_packet_arrived(void *obj, cdecklink_encoder_audio_packet_t * audioPacket);

typedef HRESULT cdecklink_audio_output_callback_render_audio_samples(void *obj, bool preroll);

typedef HRESULT cdecklink_screen_preview_callback_draw_frame(void *obj, cdecklink_video_frame_t * theFrame);

typedef HRESULT cdecklink_notification_callback_notify(void *obj, DecklinkNotifications topic, uint64_t param1, uint64_t param2);

typedef HRESULT cdecklink_profile_callback_profile_changing(void *obj, cdecklink_profile_t * profileToBeActivated, bool streamsWillBeForcedToStop);
typedef HRESULT cdecklink_profile_callback_profile_activated(void *obj, cdecklink_profile_t * activatedProfile);

typedef HRESULT cdecklink_device_notification_callback_deck_link_device_arrived(void *obj, cdecklink_device_t * deckLinkDevice);
typedef HRESULT cdecklink_device_notification_callback_deck_link_device_removed(void *obj, cdecklink_device_t * deckLinkDevice);

unsigned long cdecklink_timecode_add_ref(cdecklink_timecode_t *obj);
unsigned long cdecklink_timecode_release(cdecklink_timecode_t *obj);
DecklinkTimecodeBCD cdecklink_timecode_get_bcd(cdecklink_timecode_t *obj);
HRESULT cdecklink_timecode_get_components(cdecklink_timecode_t *obj, uint8_t * hours, uint8_t * minutes, uint8_t * seconds, uint8_t * frames);
HRESULT cdecklink_timecode_get_string(cdecklink_timecode_t *obj, const char ** timecode);
DecklinkTimecodeFlags cdecklink_timecode_get_flags(cdecklink_timecode_t *obj);
HRESULT cdecklink_timecode_get_timecode_user_bits(cdecklink_timecode_t *obj, DecklinkTimecodeUserBits * userBits);

unsigned long cdecklink_display_mode_iterator_add_ref(cdecklink_display_mode_iterator_t *obj);
unsigned long cdecklink_display_mode_iterator_release(cdecklink_display_mode_iterator_t *obj);
HRESULT cdecklink_display_mode_iterator_next(cdecklink_display_mode_iterator_t *obj, cdecklink_display_mode_t ** deckLinkDisplayMode);

unsigned long cdecklink_display_mode_add_ref(cdecklink_display_mode_t *obj);
unsigned long cdecklink_display_mode_release(cdecklink_display_mode_t *obj);
HRESULT cdecklink_display_mode_get_name(cdecklink_display_mode_t *obj, const char ** name);
DecklinkDisplayMode cdecklink_display_mode_get_display_mode(cdecklink_display_mode_t *obj);
long cdecklink_display_mode_get_width(cdecklink_display_mode_t *obj);
long cdecklink_display_mode_get_height(cdecklink_display_mode_t *obj);
HRESULT cdecklink_display_mode_get_frame_rate(cdecklink_display_mode_t *obj, DecklinkTimeValue * frameDuration, DecklinkTimeScale * timeScale);
DecklinkFieldDominance cdecklink_display_mode_get_field_dominance(cdecklink_display_mode_t *obj);
DecklinkDisplayModeFlags cdecklink_display_mode_get_flags(cdecklink_display_mode_t *obj);

unsigned long cdecklink_device_add_ref(cdecklink_device_t *obj);
unsigned long cdecklink_device_release(cdecklink_device_t *obj);
HRESULT cdecklink_device_get_model_name(cdecklink_device_t *obj, const char ** modelName);
HRESULT cdecklink_device_get_display_name(cdecklink_device_t *obj, const char ** displayName);

unsigned long cdecklink_configuration_add_ref(cdecklink_configuration_t *obj);
unsigned long cdecklink_configuration_release(cdecklink_configuration_t *obj);
HRESULT cdecklink_configuration_set_flag(cdecklink_configuration_t *obj, DecklinkConfigurationID cfgID, bool value);
HRESULT cdecklink_configuration_get_flag(cdecklink_configuration_t *obj, DecklinkConfigurationID cfgID, bool * value);
HRESULT cdecklink_configuration_set_int(cdecklink_configuration_t *obj, DecklinkConfigurationID cfgID, int64_t value);
HRESULT cdecklink_configuration_get_int(cdecklink_configuration_t *obj, DecklinkConfigurationID cfgID, int64_t * value);
HRESULT cdecklink_configuration_set_float(cdecklink_configuration_t *obj, DecklinkConfigurationID cfgID, double value);
HRESULT cdecklink_configuration_get_float(cdecklink_configuration_t *obj, DecklinkConfigurationID cfgID, double * value);
HRESULT cdecklink_configuration_set_string(cdecklink_configuration_t *obj, DecklinkConfigurationID cfgID, const char * value);
HRESULT cdecklink_configuration_get_string(cdecklink_configuration_t *obj, DecklinkConfigurationID cfgID, const char ** value);
HRESULT cdecklink_configuration_write_configuration_to_preferences(cdecklink_configuration_t *obj);

unsigned long cdecklink_encoder_configuration_add_ref(cdecklink_encoder_configuration_t *obj);
unsigned long cdecklink_encoder_configuration_release(cdecklink_encoder_configuration_t *obj);
HRESULT cdecklink_encoder_configuration_set_flag(cdecklink_encoder_configuration_t *obj, DecklinkEncoderConfigurationID cfgID, bool value);
HRESULT cdecklink_encoder_configuration_get_flag(cdecklink_encoder_configuration_t *obj, DecklinkEncoderConfigurationID cfgID, bool * value);
HRESULT cdecklink_encoder_configuration_set_int(cdecklink_encoder_configuration_t *obj, DecklinkEncoderConfigurationID cfgID, int64_t value);
HRESULT cdecklink_encoder_configuration_get_int(cdecklink_encoder_configuration_t *obj, DecklinkEncoderConfigurationID cfgID, int64_t * value);
HRESULT cdecklink_encoder_configuration_set_float(cdecklink_encoder_configuration_t *obj, DecklinkEncoderConfigurationID cfgID, double value);
HRESULT cdecklink_encoder_configuration_get_float(cdecklink_encoder_configuration_t *obj, DecklinkEncoderConfigurationID cfgID, double * value);
HRESULT cdecklink_encoder_configuration_set_string(cdecklink_encoder_configuration_t *obj, DecklinkEncoderConfigurationID cfgID, const char * value);
HRESULT cdecklink_encoder_configuration_get_string(cdecklink_encoder_configuration_t *obj, DecklinkEncoderConfigurationID cfgID, const char ** value);
HRESULT cdecklink_encoder_configuration_get_bytes(cdecklink_encoder_configuration_t *obj, DecklinkEncoderConfigurationID cfgID, void * buffer, uint32_t * bufferSize);

unsigned long cdecklink_deck_control_add_ref(cdecklink_deck_control_t *obj);
unsigned long cdecklink_deck_control_release(cdecklink_deck_control_t *obj);
HRESULT cdecklink_deck_control_open(cdecklink_deck_control_t *obj, DecklinkTimeScale timeScale, DecklinkTimeValue timeValue, bool timecodeIsDropFrame, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_close(cdecklink_deck_control_t *obj, bool standbyOn);
HRESULT cdecklink_deck_control_get_current_state(cdecklink_deck_control_t *obj, DecklinkDeckControlMode * mode, DecklinkDeckControlVTRControlState * vtrControlState, DecklinkDeckControlStatusFlags * flags);
HRESULT cdecklink_deck_control_set_standby(cdecklink_deck_control_t *obj, bool standbyOn);
HRESULT cdecklink_deck_control_send_command(cdecklink_deck_control_t *obj, uint8_t * inBuffer, uint32_t inBufferSize, uint8_t * outBuffer, uint32_t * outDataSize, uint32_t outBufferSize, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_play(cdecklink_deck_control_t *obj, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_stop(cdecklink_deck_control_t *obj, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_toggle_play_stop(cdecklink_deck_control_t *obj, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_eject(cdecklink_deck_control_t *obj, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_go_to_timecode(cdecklink_deck_control_t *obj, DecklinkTimecodeBCD timecode, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_fast_forward(cdecklink_deck_control_t *obj, bool viewTape, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_rewind(cdecklink_deck_control_t *obj, bool viewTape, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_step_forward(cdecklink_deck_control_t *obj, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_step_back(cdecklink_deck_control_t *obj, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_jog(cdecklink_deck_control_t *obj, double rate, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_shuttle(cdecklink_deck_control_t *obj, double rate, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_get_timecode_string(cdecklink_deck_control_t *obj, const char ** currentTimeCode, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_get_timecode(cdecklink_deck_control_t *obj, cdecklink_timecode_t ** currentTimecode, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_get_timecode_bcd(cdecklink_deck_control_t *obj, DecklinkTimecodeBCD * currentTimecode, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_set_preroll(cdecklink_deck_control_t *obj, uint32_t prerollSeconds);
HRESULT cdecklink_deck_control_get_preroll(cdecklink_deck_control_t *obj, uint32_t * prerollSeconds);
HRESULT cdecklink_deck_control_set_export_offset(cdecklink_deck_control_t *obj, int32_t exportOffsetFields);
HRESULT cdecklink_deck_control_get_export_offset(cdecklink_deck_control_t *obj, int32_t * exportOffsetFields);
HRESULT cdecklink_deck_control_get_manual_export_offset(cdecklink_deck_control_t *obj, int32_t * deckManualExportOffsetFields);
HRESULT cdecklink_deck_control_set_capture_offset(cdecklink_deck_control_t *obj, int32_t captureOffsetFields);
HRESULT cdecklink_deck_control_get_capture_offset(cdecklink_deck_control_t *obj, int32_t * captureOffsetFields);
HRESULT cdecklink_deck_control_start_export(cdecklink_deck_control_t *obj, DecklinkTimecodeBCD inTimecode, DecklinkTimecodeBCD outTimecode, DecklinkDeckControlExportModeOpsFlags exportModeOps, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_start_capture(cdecklink_deck_control_t *obj, bool useVITC, DecklinkTimecodeBCD inTimecode, DecklinkTimecodeBCD outTimecode, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_get_device_id(cdecklink_deck_control_t *obj, uint16_t * deviceId, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_abort(cdecklink_deck_control_t *obj);
HRESULT cdecklink_deck_control_crash_record_start(cdecklink_deck_control_t *obj, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_crash_record_stop(cdecklink_deck_control_t *obj, DecklinkDeckControlError * error);
HRESULT cdecklink_deck_control_set_callback(cdecklink_deck_control_t *obj, void *ctx, cdecklink_deck_control_status_callback_timecode_update* cb0, cdecklink_deck_control_status_callback_vtr_control_state_changed* cb1, cdecklink_deck_control_status_callback_deck_control_event_received* cb2, cdecklink_deck_control_status_callback_deck_control_status_changed* cb3);

unsigned long cdecklink_memory_allocator_add_ref(cdecklink_memory_allocator_t *obj);
unsigned long cdecklink_memory_allocator_release(cdecklink_memory_allocator_t *obj);
HRESULT cdecklink_memory_allocator_allocate_buffer(cdecklink_memory_allocator_t *obj, uint32_t bufferSize, void ** allocatedBuffer);
HRESULT cdecklink_memory_allocator_release_buffer(cdecklink_memory_allocator_t *obj, void * buffer);
HRESULT cdecklink_memory_allocator_commit(cdecklink_memory_allocator_t *obj);
HRESULT cdecklink_memory_allocator_decommit(cdecklink_memory_allocator_t *obj);

unsigned long cdecklink_iterator_add_ref(cdecklink_iterator_t *obj);
unsigned long cdecklink_iterator_release(cdecklink_iterator_t *obj);
HRESULT cdecklink_iterator_next(cdecklink_iterator_t *obj, cdecklink_device_t ** deckLinkInstance);

unsigned long cdecklink_api_information_add_ref(cdecklink_api_information_t *obj);
unsigned long cdecklink_api_information_release(cdecklink_api_information_t *obj);
HRESULT cdecklink_api_information_get_flag(cdecklink_api_information_t *obj, DecklinkAPIInformationID cfgID, bool * value);
HRESULT cdecklink_api_information_get_int(cdecklink_api_information_t *obj, DecklinkAPIInformationID cfgID, int64_t * value);
HRESULT cdecklink_api_information_get_float(cdecklink_api_information_t *obj, DecklinkAPIInformationID cfgID, double * value);
HRESULT cdecklink_api_information_get_string(cdecklink_api_information_t *obj, DecklinkAPIInformationID cfgID, const char ** value);

unsigned long cdecklink_output_add_ref(cdecklink_output_t *obj);
unsigned long cdecklink_output_release(cdecklink_output_t *obj);
HRESULT cdecklink_output_does_support_video_mode(cdecklink_output_t *obj, DecklinkVideoConnection connection, DecklinkDisplayMode requestedMode, DecklinkPixelFormat requestedPixelFormat, DecklinkVideoOutputConversionMode conversionMode, DecklinkSupportedVideoModeFlags flags, DecklinkDisplayMode * actualMode, bool * supported);
HRESULT cdecklink_output_get_display_mode(cdecklink_output_t *obj, DecklinkDisplayMode displayMode, cdecklink_display_mode_t ** resultDisplayMode);
HRESULT cdecklink_output_get_display_mode_iterator(cdecklink_output_t *obj, cdecklink_display_mode_iterator_t ** iterator);
HRESULT cdecklink_output_set_screen_preview_callback(cdecklink_output_t *obj, void *ctx, cdecklink_screen_preview_callback_draw_frame* cb0);
HRESULT cdecklink_output_enable_video_output(cdecklink_output_t *obj, DecklinkDisplayMode displayMode, DecklinkVideoOutputFlags flags);
HRESULT cdecklink_output_disable_video_output(cdecklink_output_t *obj);
HRESULT cdecklink_output_set_video_output_frame_memory_allocator(cdecklink_output_t *obj, cdecklink_memory_allocator_t * theAllocator);
HRESULT cdecklink_output_create_video_frame(cdecklink_output_t *obj, int32_t width, int32_t height, int32_t rowBytes, DecklinkPixelFormat pixelFormat, DecklinkFrameFlags flags, cdecklink_mutable_video_frame_t ** outFrame);
HRESULT cdecklink_output_create_ancillary_data(cdecklink_output_t *obj, DecklinkPixelFormat pixelFormat, cdecklink_video_frame_ancillary_t ** outBuffer);
HRESULT cdecklink_output_display_video_frame_sync(cdecklink_output_t *obj, cdecklink_video_frame_t * theFrame);
HRESULT cdecklink_output_schedule_video_frame(cdecklink_output_t *obj, cdecklink_video_frame_t * theFrame, DecklinkTimeValue displayTime, DecklinkTimeValue displayDuration, DecklinkTimeScale timeScale);
HRESULT cdecklink_output_set_scheduled_frame_completion_callback(cdecklink_output_t *obj, void *ctx, cdecklink_video_output_callback_scheduled_frame_completed* cb0, cdecklink_video_output_callback_scheduled_playback_has_stopped* cb1);
HRESULT cdecklink_output_get_buffered_video_frame_count(cdecklink_output_t *obj, uint32_t * bufferedFrameCount);
HRESULT cdecklink_output_enable_audio_output(cdecklink_output_t *obj, DecklinkAudioSampleRate sampleRate, DecklinkAudioSampleType sampleType, uint32_t channelCount, DecklinkAudioOutputStreamType streamType);
HRESULT cdecklink_output_disable_audio_output(cdecklink_output_t *obj);
HRESULT cdecklink_output_write_audio_samples_sync(cdecklink_output_t *obj, void * buffer, uint32_t sampleFrameCount, uint32_t * sampleFramesWritten);
HRESULT cdecklink_output_begin_audio_preroll(cdecklink_output_t *obj);
HRESULT cdecklink_output_end_audio_preroll(cdecklink_output_t *obj);
HRESULT cdecklink_output_schedule_audio_samples(cdecklink_output_t *obj, void * buffer, uint32_t sampleFrameCount, DecklinkTimeValue streamTime, DecklinkTimeScale timeScale, uint32_t * sampleFramesWritten);
HRESULT cdecklink_output_get_buffered_audio_sample_frame_count(cdecklink_output_t *obj, uint32_t * bufferedSampleFrameCount);
HRESULT cdecklink_output_flush_buffered_audio_samples(cdecklink_output_t *obj);
HRESULT cdecklink_output_set_audio_callback(cdecklink_output_t *obj, void *ctx, cdecklink_audio_output_callback_render_audio_samples* cb0);
HRESULT cdecklink_output_start_scheduled_playback(cdecklink_output_t *obj, DecklinkTimeValue playbackStartTime, DecklinkTimeScale timeScale, double playbackSpeed);
HRESULT cdecklink_output_stop_scheduled_playback(cdecklink_output_t *obj, DecklinkTimeValue stopPlaybackAtTime, DecklinkTimeValue * actualStopTime, DecklinkTimeScale timeScale);
HRESULT cdecklink_output_is_scheduled_playback_running(cdecklink_output_t *obj, bool * active);
HRESULT cdecklink_output_get_scheduled_stream_time(cdecklink_output_t *obj, DecklinkTimeScale desiredTimeScale, DecklinkTimeValue * streamTime, double * playbackSpeed);
HRESULT cdecklink_output_get_reference_status(cdecklink_output_t *obj, DecklinkReferenceStatus * referenceStatus);
HRESULT cdecklink_output_get_hardware_reference_clock(cdecklink_output_t *obj, DecklinkTimeScale desiredTimeScale, DecklinkTimeValue * hardwareTime, DecklinkTimeValue * timeInFrame, DecklinkTimeValue * ticksPerFrame);
HRESULT cdecklink_output_get_frame_completion_reference_timestamp(cdecklink_output_t *obj, cdecklink_video_frame_t * theFrame, DecklinkTimeScale desiredTimeScale, DecklinkTimeValue * frameCompletionTimestamp);

unsigned long cdecklink_input_add_ref(cdecklink_input_t *obj);
unsigned long cdecklink_input_release(cdecklink_input_t *obj);
HRESULT cdecklink_input_does_support_video_mode(cdecklink_input_t *obj, DecklinkVideoConnection connection, DecklinkDisplayMode requestedMode, DecklinkPixelFormat requestedPixelFormat, DecklinkVideoInputConversionMode conversionMode, DecklinkSupportedVideoModeFlags flags, DecklinkDisplayMode * actualMode, bool * supported);
HRESULT cdecklink_input_get_display_mode(cdecklink_input_t *obj, DecklinkDisplayMode displayMode, cdecklink_display_mode_t ** resultDisplayMode);
HRESULT cdecklink_input_get_display_mode_iterator(cdecklink_input_t *obj, cdecklink_display_mode_iterator_t ** iterator);
HRESULT cdecklink_input_set_screen_preview_callback(cdecklink_input_t *obj, void *ctx, cdecklink_screen_preview_callback_draw_frame* cb0);
HRESULT cdecklink_input_enable_video_input(cdecklink_input_t *obj, DecklinkDisplayMode displayMode, DecklinkPixelFormat pixelFormat, DecklinkVideoInputFlags flags);
HRESULT cdecklink_input_disable_video_input(cdecklink_input_t *obj);
HRESULT cdecklink_input_get_available_video_frame_count(cdecklink_input_t *obj, uint32_t * availableFrameCount);
HRESULT cdecklink_input_set_video_input_frame_memory_allocator(cdecklink_input_t *obj, cdecklink_memory_allocator_t * theAllocator);
HRESULT cdecklink_input_enable_audio_input(cdecklink_input_t *obj, DecklinkAudioSampleRate sampleRate, DecklinkAudioSampleType sampleType, uint32_t channelCount);
HRESULT cdecklink_input_disable_audio_input(cdecklink_input_t *obj);
HRESULT cdecklink_input_get_available_audio_sample_frame_count(cdecklink_input_t *obj, uint32_t * availableSampleFrameCount);
HRESULT cdecklink_input_start_streams(cdecklink_input_t *obj);
HRESULT cdecklink_input_stop_streams(cdecklink_input_t *obj);
HRESULT cdecklink_input_pause_streams(cdecklink_input_t *obj);
HRESULT cdecklink_input_flush_streams(cdecklink_input_t *obj);
HRESULT cdecklink_input_set_callback(cdecklink_input_t *obj, void *ctx, cdecklink_input_callback_video_input_format_changed* cb0, cdecklink_input_callback_video_input_frame_arrived* cb1);
HRESULT cdecklink_input_get_hardware_reference_clock(cdecklink_input_t *obj, DecklinkTimeScale desiredTimeScale, DecklinkTimeValue * hardwareTime, DecklinkTimeValue * timeInFrame, DecklinkTimeValue * ticksPerFrame);

unsigned long cdecklink_hdmi_input_edid_add_ref(cdecklink_hdmi_input_edid_t *obj);
unsigned long cdecklink_hdmi_input_edid_release(cdecklink_hdmi_input_edid_t *obj);
HRESULT cdecklink_hdmi_input_edid_set_int(cdecklink_hdmi_input_edid_t *obj, DecklinkHDMIInputEDIDID cfgID, int64_t value);
HRESULT cdecklink_hdmi_input_edid_get_int(cdecklink_hdmi_input_edid_t *obj, DecklinkHDMIInputEDIDID cfgID, int64_t * value);
HRESULT cdecklink_hdmi_input_edid_write_to_edid(cdecklink_hdmi_input_edid_t *obj);

unsigned long cdecklink_encoder_input_add_ref(cdecklink_encoder_input_t *obj);
unsigned long cdecklink_encoder_input_release(cdecklink_encoder_input_t *obj);
HRESULT cdecklink_encoder_input_does_support_video_mode(cdecklink_encoder_input_t *obj, DecklinkVideoConnection connection, DecklinkDisplayMode requestedMode, DecklinkPixelFormat requestedCodec, uint32_t requestedCodecProfile, DecklinkSupportedVideoModeFlags flags, bool * supported);
HRESULT cdecklink_encoder_input_get_display_mode(cdecklink_encoder_input_t *obj, DecklinkDisplayMode displayMode, cdecklink_display_mode_t ** resultDisplayMode);
HRESULT cdecklink_encoder_input_get_display_mode_iterator(cdecklink_encoder_input_t *obj, cdecklink_display_mode_iterator_t ** iterator);
HRESULT cdecklink_encoder_input_enable_video_input(cdecklink_encoder_input_t *obj, DecklinkDisplayMode displayMode, DecklinkPixelFormat pixelFormat, DecklinkVideoInputFlags flags);
HRESULT cdecklink_encoder_input_disable_video_input(cdecklink_encoder_input_t *obj);
HRESULT cdecklink_encoder_input_get_available_packets_count(cdecklink_encoder_input_t *obj, uint32_t * availablePacketsCount);
HRESULT cdecklink_encoder_input_set_memory_allocator(cdecklink_encoder_input_t *obj, cdecklink_memory_allocator_t * theAllocator);
HRESULT cdecklink_encoder_input_enable_audio_input(cdecklink_encoder_input_t *obj, DecklinkAudioFormat audioFormat, DecklinkAudioSampleRate sampleRate, DecklinkAudioSampleType sampleType, uint32_t channelCount);
HRESULT cdecklink_encoder_input_disable_audio_input(cdecklink_encoder_input_t *obj);
HRESULT cdecklink_encoder_input_get_available_audio_sample_frame_count(cdecklink_encoder_input_t *obj, uint32_t * availableSampleFrameCount);
HRESULT cdecklink_encoder_input_start_streams(cdecklink_encoder_input_t *obj);
HRESULT cdecklink_encoder_input_stop_streams(cdecklink_encoder_input_t *obj);
HRESULT cdecklink_encoder_input_pause_streams(cdecklink_encoder_input_t *obj);
HRESULT cdecklink_encoder_input_flush_streams(cdecklink_encoder_input_t *obj);
HRESULT cdecklink_encoder_input_set_callback(cdecklink_encoder_input_t *obj, void *ctx, cdecklink_encoder_input_callback_video_input_signal_changed* cb0, cdecklink_encoder_input_callback_video_packet_arrived* cb1, cdecklink_encoder_input_callback_audio_packet_arrived* cb2);
HRESULT cdecklink_encoder_input_get_hardware_reference_clock(cdecklink_encoder_input_t *obj, DecklinkTimeScale desiredTimeScale, DecklinkTimeValue * hardwareTime, DecklinkTimeValue * timeInFrame, DecklinkTimeValue * ticksPerFrame);

unsigned long cdecklink_video_frame_add_ref(cdecklink_video_frame_t *obj);
unsigned long cdecklink_video_frame_release(cdecklink_video_frame_t *obj);
long cdecklink_video_frame_get_width(cdecklink_video_frame_t *obj);
long cdecklink_video_frame_get_height(cdecklink_video_frame_t *obj);
long cdecklink_video_frame_get_row_bytes(cdecklink_video_frame_t *obj);
DecklinkPixelFormat cdecklink_video_frame_get_pixel_format(cdecklink_video_frame_t *obj);
DecklinkFrameFlags cdecklink_video_frame_get_flags(cdecklink_video_frame_t *obj);
HRESULT cdecklink_video_frame_get_bytes(cdecklink_video_frame_t *obj, void ** buffer);
HRESULT cdecklink_video_frame_get_timecode(cdecklink_video_frame_t *obj, DecklinkTimecodeFormat format, cdecklink_timecode_t ** timecode);
HRESULT cdecklink_video_frame_get_ancillary_data(cdecklink_video_frame_t *obj, cdecklink_video_frame_ancillary_t ** ancillary);

cdecklink_video_frame_t *cdecklink_mutable_video_frame_to_video_frame(cdecklink_mutable_video_frame_t *obj);
unsigned long cdecklink_mutable_video_frame_add_ref(cdecklink_mutable_video_frame_t *obj);
unsigned long cdecklink_mutable_video_frame_release(cdecklink_mutable_video_frame_t *obj);
HRESULT cdecklink_mutable_video_frame_set_flags(cdecklink_mutable_video_frame_t *obj, DecklinkFrameFlags newFlags);
HRESULT cdecklink_mutable_video_frame_set_timecode(cdecklink_mutable_video_frame_t *obj, DecklinkTimecodeFormat format, cdecklink_timecode_t * timecode);
HRESULT cdecklink_mutable_video_frame_set_timecode_from_components(cdecklink_mutable_video_frame_t *obj, DecklinkTimecodeFormat format, uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t frames, DecklinkTimecodeFlags flags);
HRESULT cdecklink_mutable_video_frame_set_ancillary_data(cdecklink_mutable_video_frame_t *obj, cdecklink_video_frame_ancillary_t * ancillary);
HRESULT cdecklink_mutable_video_frame_set_timecode_user_bits(cdecklink_mutable_video_frame_t *obj, DecklinkTimecodeFormat format, DecklinkTimecodeUserBits userBits);

unsigned long cdecklink_video_frame3_d_extensions_add_ref(cdecklink_video_frame3_d_extensions_t *obj);
unsigned long cdecklink_video_frame3_d_extensions_release(cdecklink_video_frame3_d_extensions_t *obj);
DecklinkVideo3DPackingFormat cdecklink_video_frame3_d_extensions_get3_d_packing_format(cdecklink_video_frame3_d_extensions_t *obj);
HRESULT cdecklink_video_frame3_d_extensions_get_frame_for_right_eye(cdecklink_video_frame3_d_extensions_t *obj, cdecklink_video_frame_t ** rightEyeFrame);

unsigned long cdecklink_video_frame_metadata_extensions_add_ref(cdecklink_video_frame_metadata_extensions_t *obj);
unsigned long cdecklink_video_frame_metadata_extensions_release(cdecklink_video_frame_metadata_extensions_t *obj);
HRESULT cdecklink_video_frame_metadata_extensions_get_int(cdecklink_video_frame_metadata_extensions_t *obj, DecklinkFrameMetadataID metadataID, int64_t * value);
HRESULT cdecklink_video_frame_metadata_extensions_get_float(cdecklink_video_frame_metadata_extensions_t *obj, DecklinkFrameMetadataID metadataID, double * value);
HRESULT cdecklink_video_frame_metadata_extensions_get_flag(cdecklink_video_frame_metadata_extensions_t *obj, DecklinkFrameMetadataID metadataID, bool * value);
HRESULT cdecklink_video_frame_metadata_extensions_get_string(cdecklink_video_frame_metadata_extensions_t *obj, DecklinkFrameMetadataID metadataID, const char ** value);
HRESULT cdecklink_video_frame_metadata_extensions_get_bytes(cdecklink_video_frame_metadata_extensions_t *obj, DecklinkFrameMetadataID metadataID, void * buffer, uint32_t * bufferSize);

cdecklink_video_frame_t *cdecklink_video_input_frame_to_video_frame(cdecklink_video_input_frame_t *obj);
unsigned long cdecklink_video_input_frame_add_ref(cdecklink_video_input_frame_t *obj);
unsigned long cdecklink_video_input_frame_release(cdecklink_video_input_frame_t *obj);
HRESULT cdecklink_video_input_frame_get_stream_time(cdecklink_video_input_frame_t *obj, DecklinkTimeValue * frameTime, DecklinkTimeValue * frameDuration, DecklinkTimeScale timeScale);
HRESULT cdecklink_video_input_frame_get_hardware_reference_timestamp(cdecklink_video_input_frame_t *obj, DecklinkTimeScale timeScale, DecklinkTimeValue * frameTime, DecklinkTimeValue * frameDuration);

unsigned long cdecklink_ancillary_packet_add_ref(cdecklink_ancillary_packet_t *obj);
unsigned long cdecklink_ancillary_packet_release(cdecklink_ancillary_packet_t *obj);
HRESULT cdecklink_ancillary_packet_get_bytes(cdecklink_ancillary_packet_t *obj, DecklinkAncillaryPacketFormat format, const void ** data, uint32_t * size);
uint8_t cdecklink_ancillary_packet_get_did(cdecklink_ancillary_packet_t *obj);
uint8_t cdecklink_ancillary_packet_get_sdid(cdecklink_ancillary_packet_t *obj);
uint32_t cdecklink_ancillary_packet_get_line_number(cdecklink_ancillary_packet_t *obj);
uint8_t cdecklink_ancillary_packet_get_data_stream_index(cdecklink_ancillary_packet_t *obj);

unsigned long cdecklink_ancillary_packet_iterator_add_ref(cdecklink_ancillary_packet_iterator_t *obj);
unsigned long cdecklink_ancillary_packet_iterator_release(cdecklink_ancillary_packet_iterator_t *obj);
HRESULT cdecklink_ancillary_packet_iterator_next(cdecklink_ancillary_packet_iterator_t *obj, cdecklink_ancillary_packet_t ** packet);

unsigned long cdecklink_video_frame_ancillary_packets_add_ref(cdecklink_video_frame_ancillary_packets_t *obj);
unsigned long cdecklink_video_frame_ancillary_packets_release(cdecklink_video_frame_ancillary_packets_t *obj);
HRESULT cdecklink_video_frame_ancillary_packets_get_packet_iterator(cdecklink_video_frame_ancillary_packets_t *obj, cdecklink_ancillary_packet_iterator_t ** iterator);
HRESULT cdecklink_video_frame_ancillary_packets_get_first_packet_by_id(cdecklink_video_frame_ancillary_packets_t *obj, uint8_t DID, uint8_t SDID, cdecklink_ancillary_packet_t ** packet);
HRESULT cdecklink_video_frame_ancillary_packets_attach_packet(cdecklink_video_frame_ancillary_packets_t *obj, cdecklink_ancillary_packet_t * packet);
HRESULT cdecklink_video_frame_ancillary_packets_detach_packet(cdecklink_video_frame_ancillary_packets_t *obj, cdecklink_ancillary_packet_t * packet);
HRESULT cdecklink_video_frame_ancillary_packets_detach_all_packets(cdecklink_video_frame_ancillary_packets_t *obj);

unsigned long cdecklink_video_frame_ancillary_add_ref(cdecklink_video_frame_ancillary_t *obj);
unsigned long cdecklink_video_frame_ancillary_release(cdecklink_video_frame_ancillary_t *obj);
HRESULT cdecklink_video_frame_ancillary_get_buffer_for_vertical_blanking_line(cdecklink_video_frame_ancillary_t *obj, uint32_t lineNumber, void ** buffer);
DecklinkPixelFormat cdecklink_video_frame_ancillary_get_pixel_format(cdecklink_video_frame_ancillary_t *obj);
DecklinkDisplayMode cdecklink_video_frame_ancillary_get_display_mode(cdecklink_video_frame_ancillary_t *obj);

unsigned long cdecklink_encoder_packet_add_ref(cdecklink_encoder_packet_t *obj);
unsigned long cdecklink_encoder_packet_release(cdecklink_encoder_packet_t *obj);
HRESULT cdecklink_encoder_packet_get_bytes(cdecklink_encoder_packet_t *obj, void ** buffer);
long cdecklink_encoder_packet_get_size(cdecklink_encoder_packet_t *obj);
HRESULT cdecklink_encoder_packet_get_stream_time(cdecklink_encoder_packet_t *obj, DecklinkTimeValue * frameTime, DecklinkTimeScale timeScale);
DecklinkPacketType cdecklink_encoder_packet_get_packet_type(cdecklink_encoder_packet_t *obj);

cdecklink_encoder_packet_t *cdecklink_encoder_video_packet_to_encoder_packet(cdecklink_encoder_video_packet_t *obj);
unsigned long cdecklink_encoder_video_packet_add_ref(cdecklink_encoder_video_packet_t *obj);
unsigned long cdecklink_encoder_video_packet_release(cdecklink_encoder_video_packet_t *obj);
DecklinkPixelFormat cdecklink_encoder_video_packet_get_pixel_format(cdecklink_encoder_video_packet_t *obj);
HRESULT cdecklink_encoder_video_packet_get_hardware_reference_timestamp(cdecklink_encoder_video_packet_t *obj, DecklinkTimeScale timeScale, DecklinkTimeValue * frameTime, DecklinkTimeValue * frameDuration);
HRESULT cdecklink_encoder_video_packet_get_timecode(cdecklink_encoder_video_packet_t *obj, DecklinkTimecodeFormat format, cdecklink_timecode_t ** timecode);

cdecklink_encoder_packet_t *cdecklink_encoder_audio_packet_to_encoder_packet(cdecklink_encoder_audio_packet_t *obj);
unsigned long cdecklink_encoder_audio_packet_add_ref(cdecklink_encoder_audio_packet_t *obj);
unsigned long cdecklink_encoder_audio_packet_release(cdecklink_encoder_audio_packet_t *obj);
DecklinkAudioFormat cdecklink_encoder_audio_packet_get_audio_format(cdecklink_encoder_audio_packet_t *obj);

cdecklink_encoder_video_packet_t *cdecklink_h265nal_packet_to_encoder_video_packet(cdecklink_h265nal_packet_t *obj);
unsigned long cdecklink_h265nal_packet_add_ref(cdecklink_h265nal_packet_t *obj);
unsigned long cdecklink_h265nal_packet_release(cdecklink_h265nal_packet_t *obj);
HRESULT cdecklink_h265nal_packet_get_unit_type(cdecklink_h265nal_packet_t *obj, uint8_t * unitType);
HRESULT cdecklink_h265nal_packet_get_bytes_no_prefix(cdecklink_h265nal_packet_t *obj, void ** buffer);
long cdecklink_h265nal_packet_get_size_no_prefix(cdecklink_h265nal_packet_t *obj);

unsigned long cdecklink_audio_input_packet_add_ref(cdecklink_audio_input_packet_t *obj);
unsigned long cdecklink_audio_input_packet_release(cdecklink_audio_input_packet_t *obj);
long cdecklink_audio_input_packet_get_sample_frame_count(cdecklink_audio_input_packet_t *obj);
HRESULT cdecklink_audio_input_packet_get_bytes(cdecklink_audio_input_packet_t *obj, void ** buffer);
HRESULT cdecklink_audio_input_packet_get_packet_time(cdecklink_audio_input_packet_t *obj, DecklinkTimeValue * packetTime, DecklinkTimeScale timeScale);

unsigned long cdecklink_gl_screen_preview_helper_add_ref(cdecklink_gl_screen_preview_helper_t *obj);
unsigned long cdecklink_gl_screen_preview_helper_release(cdecklink_gl_screen_preview_helper_t *obj);
HRESULT cdecklink_gl_screen_preview_helper_initialize_gl(cdecklink_gl_screen_preview_helper_t *obj);
HRESULT cdecklink_gl_screen_preview_helper_paint_gl(cdecklink_gl_screen_preview_helper_t *obj);
HRESULT cdecklink_gl_screen_preview_helper_set_frame(cdecklink_gl_screen_preview_helper_t *obj, cdecklink_video_frame_t * theFrame);
HRESULT cdecklink_gl_screen_preview_helper_set3_d_preview_format(cdecklink_gl_screen_preview_helper_t *obj, Decklink3DPreviewFormat previewFormat);

unsigned long cdecklink_notification_add_ref(cdecklink_notification_t *obj);
unsigned long cdecklink_notification_release(cdecklink_notification_t *obj);

unsigned long cdecklink_profile_attributes_add_ref(cdecklink_profile_attributes_t *obj);
unsigned long cdecklink_profile_attributes_release(cdecklink_profile_attributes_t *obj);
HRESULT cdecklink_profile_attributes_get_flag(cdecklink_profile_attributes_t *obj, DecklinkAttributeID cfgID, bool * value);
HRESULT cdecklink_profile_attributes_get_int(cdecklink_profile_attributes_t *obj, DecklinkAttributeID cfgID, int64_t * value);
HRESULT cdecklink_profile_attributes_get_float(cdecklink_profile_attributes_t *obj, DecklinkAttributeID cfgID, double * value);
HRESULT cdecklink_profile_attributes_get_string(cdecklink_profile_attributes_t *obj, DecklinkAttributeID cfgID, const char ** value);

unsigned long cdecklink_profile_iterator_add_ref(cdecklink_profile_iterator_t *obj);
unsigned long cdecklink_profile_iterator_release(cdecklink_profile_iterator_t *obj);
HRESULT cdecklink_profile_iterator_next(cdecklink_profile_iterator_t *obj, cdecklink_profile_t ** profile);

unsigned long cdecklink_profile_add_ref(cdecklink_profile_t *obj);
unsigned long cdecklink_profile_release(cdecklink_profile_t *obj);
HRESULT cdecklink_profile_get_device(cdecklink_profile_t *obj, cdecklink_device_t ** device);
HRESULT cdecklink_profile_is_active(cdecklink_profile_t *obj, bool * isActive);
HRESULT cdecklink_profile_set_active(cdecklink_profile_t *obj);
HRESULT cdecklink_profile_get_peers(cdecklink_profile_t *obj, cdecklink_profile_iterator_t ** profileIterator);

unsigned long cdecklink_profile_manager_add_ref(cdecklink_profile_manager_t *obj);
unsigned long cdecklink_profile_manager_release(cdecklink_profile_manager_t *obj);
HRESULT cdecklink_profile_manager_get_profiles(cdecklink_profile_manager_t *obj, cdecklink_profile_iterator_t ** profileIterator);
HRESULT cdecklink_profile_manager_get_profile(cdecklink_profile_manager_t *obj, DecklinkProfileID profileID, cdecklink_profile_t ** profile);
HRESULT cdecklink_profile_manager_set_callback(cdecklink_profile_manager_t *obj, void *ctx, cdecklink_profile_callback_profile_changing* cb0, cdecklink_profile_callback_profile_activated* cb1);

unsigned long cdecklink_status_add_ref(cdecklink_status_t *obj);
unsigned long cdecklink_status_release(cdecklink_status_t *obj);
HRESULT cdecklink_status_get_flag(cdecklink_status_t *obj, DecklinkStatusID statusID, bool * value);
HRESULT cdecklink_status_get_int(cdecklink_status_t *obj, DecklinkStatusID statusID, int64_t * value);
HRESULT cdecklink_status_get_float(cdecklink_status_t *obj, DecklinkStatusID statusID, double * value);
HRESULT cdecklink_status_get_string(cdecklink_status_t *obj, DecklinkStatusID statusID, const char ** value);
HRESULT cdecklink_status_get_bytes(cdecklink_status_t *obj, DecklinkStatusID statusID, void * buffer, uint32_t * bufferSize);

unsigned long cdecklink_keyer_add_ref(cdecklink_keyer_t *obj);
unsigned long cdecklink_keyer_release(cdecklink_keyer_t *obj);
HRESULT cdecklink_keyer_enable(cdecklink_keyer_t *obj, bool isExternal);
HRESULT cdecklink_keyer_set_level(cdecklink_keyer_t *obj, uint8_t level);
HRESULT cdecklink_keyer_ramp_up(cdecklink_keyer_t *obj, uint32_t numberOfFrames);
HRESULT cdecklink_keyer_ramp_down(cdecklink_keyer_t *obj, uint32_t numberOfFrames);
HRESULT cdecklink_keyer_disable(cdecklink_keyer_t *obj);

unsigned long cdecklink_video_conversion_add_ref(cdecklink_video_conversion_t *obj);
unsigned long cdecklink_video_conversion_release(cdecklink_video_conversion_t *obj);
HRESULT cdecklink_video_conversion_convert_frame(cdecklink_video_conversion_t *obj, cdecklink_video_frame_t * srcFrame, cdecklink_video_frame_t * dstFrame);

unsigned long cdecklink_discovery_add_ref(cdecklink_discovery_t *obj);
unsigned long cdecklink_discovery_release(cdecklink_discovery_t *obj);
HRESULT cdecklink_discovery_install_device_notifications(cdecklink_discovery_t *obj, void *ctx, cdecklink_device_notification_callback_deck_link_device_arrived* cb0, cdecklink_device_notification_callback_deck_link_device_removed* cb1);
HRESULT cdecklink_discovery_uninstall_device_notifications(cdecklink_discovery_t *obj);

cdecklink_iterator_t * cdecklink_create_decklink_iterator_instance();
cdecklink_discovery_t * cdecklink_create_decklink_discovery_instance();
cdecklink_api_information_t * cdecklink_create_decklink_api_information_instance();
cdecklink_gl_screen_preview_helper_t * cdecklink_create_open_gl_screen_preview_helper();
cdecklink_gl_screen_preview_helper_t * cdecklink_create_open_gl3_screen_preview_helper();
cdecklink_video_conversion_t * cdecklink_create_video_conversion_instance();
cdecklink_video_frame_ancillary_packets_t * cdecklink_create_video_frame_ancillary_packets_instance();
HRESULT cdecklink_device_query_output(cdecklink_device_t *obj, cdecklink_output_t **dst);
HRESULT cdecklink_device_query_input(cdecklink_device_t *obj, cdecklink_input_t **dst);
HRESULT cdecklink_device_query_hdmi_input_edid(cdecklink_device_t *obj, cdecklink_hdmi_input_edid_t **dst);
HRESULT cdecklink_device_query_encoder_input(cdecklink_device_t *obj, cdecklink_encoder_input_t **dst);
HRESULT cdecklink_video_frame_query_video_frame_ancillary_packets(cdecklink_video_frame_t *obj, cdecklink_video_frame_ancillary_packets_t **dst);
HRESULT cdecklink_video_frame_query_video_frame_ancillary(cdecklink_video_frame_t *obj, cdecklink_video_frame_ancillary_t **dst);
HRESULT cdecklink_encoder_video_packet_query_h265nal_packet(cdecklink_encoder_video_packet_t *obj, cdecklink_h265nal_packet_t **dst);
HRESULT cdecklink_device_query_profile_attributes(cdecklink_device_t *obj, cdecklink_profile_attributes_t **dst);
HRESULT cdecklink_device_query_profile_manager(cdecklink_device_t *obj, cdecklink_profile_manager_t **dst);
#ifdef __cplusplus
};
#endif


#endif //DECKLINK_C_API_H
