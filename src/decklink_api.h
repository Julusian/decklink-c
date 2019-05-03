#pragma once

#include "interop/Linux/include/DeckLinkAPI.h"

using String = const char *;
using BOOL   = bool;
#define TRUE true
#define FALSE false
using UINT32 = uint32_t;

template<typename T>
using com_ptr = std::shared_ptr<T>;

template<typename T>
using com_iface_ptr = std::shared_ptr<T>;

template<template<typename> class P, typename T>
static P<T> wrap_raw(T *ptr, bool already_referenced = false) {
    if (!already_referenced && ptr)
        ptr->AddRef();

    return P<T>(ptr, [](T *p) {
        if (p) {
            p->Release();
        }
    });
}

template<typename T>
static REFIID iface_id() {
    return T::REFID;
}

template<>
REFIID iface_id<IDeckLink>() {
    return IID_IDeckLink;
}

template<>
REFIID iface_id<IDeckLinkOutput>() {
    return IID_IDeckLinkOutput;
}

template<>
REFIID iface_id<IDeckLinkAPIInformation>() {
    return IID_IDeckLinkAPIInformation;
}

template<>
REFIID iface_id<IDeckLinkConfiguration>() {
    return IID_IDeckLinkConfiguration;
}

template<>
REFIID iface_id<IDeckLinkKeyer>() {
    return IID_IDeckLinkKeyer;
}

//template <>
//REFIID iface_id<IDeckLinkAttributes>()
//{
//    return IID_IDeckLinkAttributes;
//}
template<>
REFIID iface_id<IDeckLinkInput>() {
    return IID_IDeckLinkInput;
}

template<typename I, typename T>
static com_iface_ptr<I> iface_cast(com_ptr<T> ptr, bool optional = false) {
    I *iface;
    ptr->QueryInterface(iface_id<I>(), reinterpret_cast<void **>(&iface));

    return wrap_raw<com_iface_ptr>(iface, true);
}

template<typename I, typename T>
static I *iface_cast_raw(T ptr, bool optional = false) {
    I *iface;
    ptr->QueryInterface(iface_id<I>(), reinterpret_cast<void **>(&iface));

    return iface;
}