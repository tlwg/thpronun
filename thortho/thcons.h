// thcons.h - Thai consonant properties
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-03-18

#ifndef THCONS_H
#define THCONS_H

enum class EInitConstClass {
    HIGH,
    MID,
    LOWP,
    LOWS,
};

enum class EEndConstClass {
    NONE,
    KOK,
    KOT,
    KOP,
    KONG,
    KON,
    KOM,
    KOEY,
    KOEW,
};

EInitConstClass
InitConstClass (char16_t c);

EEndConstClass
EndConstClass (char16_t c);

bool
IsDeadEndConstClass (EEndConstClass c);

#include "thcons.inl"

#endif // THCONS_H

/*
vi:ts=4:ai:expandtab
*/
