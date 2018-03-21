// thcons.h - Thai consonant properties
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-03-18

#ifndef THCONS_H
#define THCONS_H

enum class EInitConsClass {
    INVALID,
    HIGH,
    MID,
    LOWP,
    LOWS,
};

enum class EEndConsClass {
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

EInitConsClass
InitConsClass (char16_t c);

EEndConsClass
EndConsClass (char16_t c);

bool
IsDeadEndConsClass (EEndConsClass c);

#include "thcons.inl"

#endif // THCONS_H

/*
vi:ts=4:ai:expandtab
*/
