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

enum class EInitConsSound {
    INVALID,
    KA,     // ก
    KHA,    // ข ฃ ค ฅ ฆ
    NGA,    // ง
    JA,     // จ
    CHA,    // ฉ ช ฌ
    YA,     // ญ ย
    DA,     // ฎ ด
    TA,     // ฏ ต
    THA,    // ฐ ฑ ฒ ถ ท ธ
    NA,     // ณ น
    BA,     // บ
    PA,     // ป
    PHA,    // ผ พ ภ
    FA,     // ฝ ฟ
    MA,     // ม
    RA,     // ร
    LA,     // ล ฬ
    WA,     // ว
    SA,     // ซ ศ ษ ส
    HA,     // ห ฮ
    A,      // อ
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

EInitConsSound
InitConsSound (char16_t c);

EEndConsClass
EndConsClass (char16_t c);

bool
IsDeadEndConsClass (EEndConsClass c);

#include "thcons.inl"

#endif // THCONS_H

/*
vi:ts=4:ai:expandtab
*/
