// sylout-roman.cxx - Romanization output for Syl
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#include "sylout-roman.h"

#include <unordered_map>

using namespace std;

////////////////////////////
//  class RomanSylOutput  //
////////////////////////////

#define ICS EInitConsSound
static const unordered_map<EInitConsSound, string>
RomanInitConsTbl_ = {
    { ICS::KA,   "k"  },  // ก
    { ICS::KHA,  "kh" },  // ข ฃ ค ฅ ฆ
    { ICS::NGA,  "ng" },  // ง
    { ICS::JA,   "ch" },  // จ
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
RomanSecInitConsTbl_ = {
    { SC::NONE,  ""  },
    { SC::RA,    "r" },  // ร ควบ
    { SC::LA,    "l" },  // ล ควบ
    { SC::WA,    "w" },  // ว ควบ
};
#undef SC

#define VW EVowel
static const unordered_map<EVowel, string>
RomanVowelTbl_ = {
    { VW::A,     "a"   },  // อะ
    { VW::AA,    "a"   },  // อา
    { VW::I,     "i"   },  // อิ
    { VW::II,    "i"   },  // อี
    { VW::UE,    "ue"  },  // อึ
    { VW::UEE,   "ue"  },  // อือ
    { VW::U,     "u"   },  // อุ
    { VW::UU,    "u"   },  // อู
    { VW::E,     "e"   },  // เอะ
    { VW::EE,    "e"   },  // เอ
    { VW::AE,    "ae"  },  // แอะ
    { VW::AEE,   "ae"  },  // แอ
    { VW::IA,    "ia"  },  // เอียะ
    { VW::IAA,   "ia"  },  // เอีย
    { VW::UEA,   "uea" },  // เอือะ
    { VW::UEAA,  "uea" },  // เอือ
    { VW::UA,    "ua"  },  // อัวะ
    { VW::UAA,   "ua"  },  // อัว
    { VW::O,     "o"   },  // โอะ
    { VW::OO,    "o"   },  // โอ
    { VW::AU,    "o"   },  // เอาะ
    { VW::AUU,   "o"   },  // ออ
    { VW::OE,    "oe"  },  // เออะ
    { VW::OEE,   "oe"  },  // เออ
};
#undef VW

#define EC EEndConsClass
static const unordered_map<EEndConsClass, string>
RomanEndConsTbl_ = {
    { EC::NONE,  ""   },  // แม่ ก กา
    { EC::KOK,   "k"  },  // แม่กก
    { EC::KOT,   "t"  },  // แม่กด
    { EC::KOP,   "p"  },  // แม่กบ
    { EC::KONG,  "ng" },  // แม่กง
    { EC::KON,   "n"  },  // แม่กน
    { EC::KOM,   "m"  },  // แม่กม
    { EC::KOEY,  "i"  },  // แม่เกย
    { EC::KOEW,  "o"  },  // แม่เกอว
};
#undef EC

string
RomanSylOutput::output (const Syl& syl) const
{
    if (syl == Syl::Blank)
        return " ";

    if (syl.isLiteral())
        return outputLiteral (syl.literal());

    return RomanInitConsTbl_.at (syl.iCons1())
           + RomanSecInitConsTbl_.at (syl.iCons2())
           + RomanVowelTbl_.at (syl.vowel())
           + RomanEndConsTbl_.at (syl.eCons());
}

/*
vi:ts=4:ai:expandtab
*/
