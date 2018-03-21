// sylcomp.h - Thai syllable fundamental components
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-01-15

#ifndef SYLCOMP_H
#define SYLCOMP_H

#include "thortho/thcons.h"

// Internal syllable encoding
// Ex:
//   กก   -> k_ok1
//   โกรธ -> krOt1
//   โค้ก  -> c_Ok3
//   ควาย -> cwAy0
//   ไกล  -> klay0
//   ใกล้  -> klay2

enum class EInitCons {
    INVALID = '*',
    KA  = 'k', // ก
    KHA = 'c', // ข ฃ ค ฅ ฆ
    NGA = 'g', // ง
    JA  = 'j', // จ
    CHA = 'J', // ฉ ช ฌ
    YA  = 'y', // ญ ย
    DA  = 'd', // ฎ ด
    TA  = 't', // ฏ ต
    THA = 'T', // ฐ ฑ ฒ ถ ท ธ
    NA  = 'n', // ณ น
    BA  = 'b', // บ
    PA  = 'p', // ป
    PHA = 'P', // ผ พ ภ
    FA  = 'f', // ฝ ฟ
    MA  = 'm', // ม
    RA  = 'r', // ร
    LA  = 'l', // ล ฬ
    WA  = 'w', // ว
    SA  = 's', // ซ ศ ษ ส
    HA  = 'h', // ห ฮ
    A   = '?', // อ
};

enum class ESecInitCons {
    NONE = '_',
    RA   = 'r', // ร ควบ
    LA   = 'l', // ล ควบ
    WA   = 'w', // ว ควบ
};

enum class EVowel {
    INVALID = '*',
    A    = 'a',  // อะ
    AA   = 'A',  // อา
    I    = 'i',  // อิ
    II   = 'I',  // อี
    UE   = 'v',  // อึ
    UEE  = 'V',  // อือ
    U    = 'u',  // อุ
    UU   = 'U',  // อู
    E    = 'e',  // เอะ
    EE   = 'E',  // เอ
    AE   = 'x',  // แอะ
    AEE  = 'X',  // แอ
    IA   = 'y',  // เอียะ
    IAA  = 'Y',  // เอีย
    UEA  = 'z',  // เอือะ
    UEAA = 'Z',  // เอือ
    UA   = 't',  // อัวะ
    UAA  = 'T',  // อัว
    O    = 'o',  // โอะ
    OO   = 'O',  // โอ
    AU   = 'c',  // เอาะ
    AUU  = 'C',  // ออ
    OE   = 'w',  // เออะ
    OEE  = 'W',  // เออ
};

bool
IsShortVowel (EVowel v);

EEndConsClass
EndConsCodeToClass (char c);

enum class ETone {
    INVALID  = '*',
    SAMAN    = '0',
    EK       = '1',
    THO      = '2',
    TRI      = '3',
    CHATTAWA = '4',
};

#include "sylcomp.inl"

#endif // SYLCOMP_H

/*
vi:ts=4:ai:expandtab
*/
