#pragma once

#if defined(__APPLE__)
#include <string>
#include <CoreFoundation/CoreFoundation.h>
#include "../interop/Mac/include/DeckLinkAPI.h"

#define dlstring_t	CFStringRef

const auto DlToConstChar = [](dlstring_t dl_str, const char ** str) {
	std::string returnString("");
	CFIndex stringSize = CFStringGetLength(dl_str) + 1;
	char* stringBuffer = (char *)malloc(stringSize);
	CFStringGetCString(dl_str, stringBuffer, stringSize, kCFStringEncodingUTF8);

	*str = stringBuffer;
};

const auto ConstCharToDl = [](const char * value) -> CFStringRef {
	return CFStringCreateWithCString(NULL, value, kCFStringEncodingUTF8);
};
#elif defined(__UNIX__)
#include "../interop/Linux/include/DeckLinkAPI.h"

#define dlstring_t	const char*

const auto DlToConstChar = [](dlstring_t dl_str, const char ** str) {
    *str = dl_str;
};

const auto ConstCharToDl = [](const char * value) -> const char * {
	return value;
};
#endif
