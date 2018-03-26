// sylcomp.cxx - Thai syllable fundamental components
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-03-19

#include "sylcomp.h"

#include <unordered_map>

using namespace std;

#define ICS EInitConsSound
static const unordered_map<char, EInitConsSound>
InitConsCodeToSoundTbl_ = {
    { '*', ICS::INVALID },
    { 'k', ICS::KA  }, // ก
    { 'c', ICS::KHA }, // ข ฃ ค ฅ ฆ
    { 'g', ICS::NGA }, // ง
    { 'j', ICS::JA  }, // จ
    { 'J', ICS::CHA }, // ฉ ช ฌ
    { 'y', ICS::YA  }, // ญ ย
    { 'd', ICS::DA  }, // ฎ ด
    { 't', ICS::TA  }, // ฏ ต
    { 'T', ICS::THA }, // ฐ ฑ ฒ ถ ท ธ
    { 'n', ICS::NA  }, // ณ น
    { 'b', ICS::BA  }, // บ
    { 'p', ICS::PA  }, // ป
    { 'P', ICS::PHA }, // ผ พ ภ
    { 'f', ICS::FA  }, // ฝ ฟ
    { 'm', ICS::MA  }, // ม
    { 'r', ICS::RA  }, // ร
    { 'l', ICS::LA  }, // ล ฬ
    { 'w', ICS::WA  }, // ว
    { 's', ICS::SA  }, // ซ ศ ษ ส
    { 'h', ICS::HA  }, // ห ฮ
    { '?', ICS::A   }, // อ
};
#undef ICS

EInitConsSound
InitConsCodeToSound (char c)
{
    return InitConsCodeToSoundTbl_.at (c);
}

#define ECC EEndConsClass
static const unordered_map<char, EEndConsClass>
EndConsCodeToClassTbl_ = {
    { '_', ECC::NONE }, // แม่ ก กา
    { 'k', ECC::KOK  }, // แม่กก
    { 't', ECC::KOT  }, // แม่กด
    { 'p', ECC::KOP  }, // แม่กบ
    { 'g', ECC::KONG }, // แม่กง
    { 'n', ECC::KON  }, // แม่กน
    { 'm', ECC::KOM  }, // แม่กม
    { 'y', ECC::KOEY }, // แม่เกย
    { 'w', ECC::KOEW }, // แม่เกอว
};
#undef ECC

EEndConsClass
EndConsCodeToClass (char c)
{
    return EndConsCodeToClassTbl_.at (c);
}

static const unordered_map<char, ETone>
ToneCodeToToneTbl_ = {
    { '*', ETone::INVALID  },
    { '0', ETone::SAMAN    },
    { '1', ETone::EK       },
    { '2', ETone::THO      },
    { '3', ETone::TRI      },
    { '4', ETone::CHATTAWA },
};

ETone
ToneCodeToTone (char c)
{
    return ToneCodeToToneTbl_.at (c);
}

/*
vi:ts=4:ai:expandtab
*/
