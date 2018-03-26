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

EInitConsSound
InitConsCodeToSound (char c);

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

ETone
ToneCodeToTone (char c);

#include "sylcomp.inl"

#endif // SYLCOMP_H

/*
vi:ts=4:ai:expandtab
*/
