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
    { ICS::KA,   "k"  },  // ก
    { ICS::KHA,  "kh" },  // ข ฃ ค ฅ ฆ
    { ICS::NGA,  "ng" },  // ง
    { ICS::JA,   "j"  },  // จ
    { ICS::CHA,  "ch" },  // ฉ ช ฌ
    { ICS::YA,   "y"  },  // ญ ย
    { ICS::DA,   "d"  },  // ฎ ด
    { ICS::TA,   "t"  },  // ฏ ต
    { ICS::THA,  "th" },  // ฐ ฑ ฒ ถ ท ธ
    { ICS::NA,   "n"  },  // ณ น
    { ICS::BA,   "b"  },  // บ
    { ICS::PA,   "p"  },  // ป
    { ICS::PHA,  "ph" },  // ผ พ ภ
    { ICS::FA,   "f"  },  // ฝ ฟ
    { ICS::MA,   "m"  },  // ม
    { ICS::RA,   "r"  },  // ร
    { ICS::LA,   "l"  },  // ล ฬ
    { ICS::WA,   "w"  },  // ว
    { ICS::SA,   "s"  },  // ซ ศ ษ ส
    { ICS::HA,   "h"  },  // ห ฮ
    { ICS::A,    ""   },  // อ
};
#undef ICS

#define SC ESecInitCons
static const unordered_map<ESecInitCons, string>
PhoneticSecInitConsTbl_ = {
    { SC::NONE,  ""  },
    { SC::RA,    "r" },  // ร ควบ
    { SC::LA,    "l" },  // ล ควบ
    { SC::WA,    "w" },  // ว ควบ
};
#undef SC

#define VW EVowel
static const unordered_map<EVowel, string>
PhoneticVowelTbl_ = {
    { VW::A,     "ah"   },  // อะ
    { VW::AA,    "aa"   },  // อา
    { VW::I,     "ih"   },  // อิ
    { VW::II,    "iy"   },  // อี
    { VW::UE,    "ueh"  },  // อึ
    { VW::UEE,   "uee"  },  // อือ
    { VW::U,     "uh"   },  // อุ
    { VW::UU,    "uw"   },  // อู
    { VW::E,     "eh"   },  // เอะ
    { VW::EE,    "ey"   },  // เอ
    { VW::AE,    "aeh"  },  // แอะ
    { VW::AEE,   "aee"  },  // แอ
    { VW::IA,    "iah"  },  // เอียะ
    { VW::IAA,   "iaa"  },  // เอีย
    { VW::UEA,   "ueah" },  // เอือะ
    { VW::UEAA,  "ueaa" },  // เอือ
    { VW::UA,    "uah"  },  // อัวะ
    { VW::UAA,   "uaa"  },  // อัว
    { VW::O,     "oh"   },  // โอะ
    { VW::OO,    "ow"   },  // โอ
    { VW::AU,    "aoh"  },  // เอาะ
    { VW::AUU,   "aow"  },  // ออ
    { VW::OE,    "oeh"  },  // เออะ
    { VW::OEE,   "oee"  },  // เออ
};
#undef VW

#define EC EEndConsClass
static const unordered_map<EEndConsClass, string>
PhoneticEndConsTbl_ = {
    { EC::NONE,  ""   },  // แม่ ก กา
    { EC::KOK,   "k"  },  // แม่กก
    { EC::KOT,   "t"  },  // แม่กด
    { EC::KOP,   "p"  },  // แม่กบ
    { EC::KONG,  "ng" },  // แม่กง
    { EC::KON,   "n"  },  // แม่กน
    { EC::KOM,   "m"  },  // แม่กม
    { EC::KOEY,  "y"  },  // แม่เกย
    { EC::KOEW,  "w"  },  // แม่เกอว
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
