// sylout-phonetic.cxx - Phonetic output for Syl
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#include "sylout-phonetic.h"

#include <unordered_map>

using namespace std;

///////////////////////////////
//  class PhoneticSylOutput  //
///////////////////////////////

#define ICS EInitConsSound
static const unordered_map<EInitConsSound, string>
PhoneticInitConsTbl_ = {
    { ICS::KA,   "K"  },  // ก
    { ICS::KHA,  "KH" },  // ข ฃ ค ฅ ฆ
    { ICS::NGA,  "NG" },  // ง
    { ICS::JA,   "J"  },  // จ
    { ICS::CHA,  "CH" },  // ฉ ช ฌ
    { ICS::YA,   "Y"  },  // ญ ย
    { ICS::DA,   "D"  },  // ฎ ด
    { ICS::TA,   "T"  },  // ฏ ต
    { ICS::THA,  "TH" },  // ฐ ฑ ฒ ถ ท ธ
    { ICS::NA,   "N"  },  // ณ น
    { ICS::BA,   "B"  },  // บ
    { ICS::PA,   "P"  },  // ป
    { ICS::PHA,  "PH" },  // ผ พ ภ
    { ICS::FA,   "F"  },  // ฝ ฟ
    { ICS::MA,   "M"  },  // ม
    { ICS::RA,   "R"  },  // ร
    { ICS::LA,   "L"  },  // ล ฬ
    { ICS::WA,   "W"  },  // ว
    { ICS::SA,   "S"  },  // ซ ศ ษ ส
    { ICS::HA,   "H"  },  // ห ฮ
    { ICS::A,    ""   },  // อ
};
#undef ICS

#define SC ESecInitCons
static const unordered_map<ESecInitCons, string>
PhoneticSecInitConsTbl_ = {
    { SC::NONE,  ""  },
    { SC::RA,    "R" },  // ร ควบ
    { SC::LA,    "L" },  // ล ควบ
    { SC::WA,    "W" },  // ว ควบ
};
#undef SC

#define VW EVowel
static const unordered_map<EVowel, string>
PhoneticVowelTbl_ = {
    { VW::A,     "AH"   },  // อะ
    { VW::AA,    "AA"   },  // อา
    { VW::I,     "IH"   },  // อิ
    { VW::II,    "IY"   },  // อี
    { VW::UE,    "UEH"  },  // อึ
    { VW::UEE,   "UEE"  },  // อือ
    { VW::U,     "UH"   },  // อุ
    { VW::UU,    "UW"   },  // อู
    { VW::E,     "EH"   },  // เอะ
    { VW::EE,    "EY"   },  // เอ
    { VW::AE,    "AEH"  },  // แอะ
    { VW::AEE,   "AEE"  },  // แอ
    { VW::IA,    "IAH"  },  // เอียะ
    { VW::IAA,   "IAA"  },  // เอีย
    { VW::UEA,   "UEAH" },  // เอือะ
    { VW::UEAA,  "UEAA" },  // เอือ
    { VW::UA,    "UAH"  },  // อัวะ
    { VW::UAA,   "UAA"  },  // อัว
    { VW::O,     "OH"   },  // โอะ
    { VW::OO,    "OW"   },  // โอ
    { VW::AU,    "AOH"  },  // เอาะ
    { VW::AUU,   "AOW"  },  // ออ
    { VW::OE,    "OEH"  },  // เออะ
    { VW::OEE,   "OEE"  },  // เออ
};
#undef VW

#define EC EEndConsClass
static const unordered_map<EEndConsClass, string>
PhoneticEndConsTbl_ = {
    { EC::NONE,  ""   },  // แม่ ก กา
    { EC::KOK,   "K"  },  // แม่กก
    { EC::KOT,   "T"  },  // แม่กด
    { EC::KOP,   "P"  },  // แม่กบ
    { EC::KONG,  "NG" },  // แม่กง
    { EC::KON,   "N"  },  // แม่กน
    { EC::KOM,   "M"  },  // แม่กม
    { EC::KOEY,  "Y"  },  // แม่เกย
    { EC::KOEW,  "W"  },  // แม่เกอว
};
#undef EC

//
// Tone Phonetic Pronunciations
//

#define TN ETone
static const unordered_map<ETone, string>
PhoneticToneTbl_ = {
    { TN::SAMAN,     "0"    },
    { TN::EK,        "1"    },
    { TN::THO,       "2"    },
    { TN::TRI,       "3"    },
    { TN::CHATTAWA,  "4"    },
};
#undef TN

string
PhoneticSylOutput::output (const Syl& syl) const
{
    return PhoneticInitConsTbl_.at (syl.iCons1())
           + PhoneticSecInitConsTbl_.at (syl.iCons2())
           + PhoneticVowelTbl_.at (syl.vowel())
           + PhoneticEndConsTbl_.at (syl.eCons())
           + PhoneticToneTbl_.at (syl.tone());
}

/*
vi:ts=4:ai:expandtab
*/
