// sylstring.cxx - Thai syllable string class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-01-16

#include "sylstring.h"

#include <cassert>
#include <cctype>
#include <utility>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/////////////////
//  class Syl  //
/////////////////
static bool
IsDeadSyl (bool isShortVowel, EEndConsClass eCons)
{
    return IsDeadEndConsClass (eCons) || (
               isShortVowel && EEndConsClass::NONE == eCons
           );
}

#define YO_STR              u8"\u0e22"
#define WO_STR              u8"\u0e27"
#define AU_STR              u8"\u0e2d"

#define PHINTHU_STR         u8"\u0e3a"

#define SARA_A_STR          u8"\u0e30"
#define MAI_HAN_AKAT_STR    u8"\u0e31"
#define SARA_AA_STR         u8"\u0e32"
#define SARA_I_STR          u8"\u0e34"
#define SARA_II_STR         u8"\u0e35"
#define SARA_UE_STR         u8"\u0e36"
#define SARA_UEE_STR        u8"\u0e37"
#define SARA_U_STR          u8"\u0e38"
#define SARA_UU_STR         u8"\u0e39"
#define PHINTHU_STR         u8"\u0e3a"
#define SARA_E_STR          u8"\u0e40"
#define SARA_AE_STR         u8"\u0e41"
#define SARA_O_STR          u8"\u0e42"
#define MAITAIKHU_STR       u8"\u0e47"

#define TONE_EK_STR         u8"\u0e48"
#define TONE_THO_STR        u8"\u0e49"
#define TONE_TRI_STR        u8"\u0e4a"
#define TONE_CHATTAWA_STR   u8"\u0e4b"

//
// Initial Consonant Classification & Thai Pronunciations
//

#define IC EInitCons
static const unordered_set<EInitCons>
ThaiMidConsSet_ = {
    IC::KA, // ก
    IC::JA, // จ
    IC::DA, // ฎ ด
    IC::TA, // ฏ ต
    IC::BA, // บ
    IC::PA, // ป
    IC::A,  // อ
};

static const unordered_map<EInitCons,string>
ThaiMidCons1Tbl_ = {
    { IC::KA,  u8"ก" },
    { IC::JA,  u8"จ" },
    { IC::DA,  u8"ด" },
    { IC::TA,  u8"ต" },
    { IC::BA,  u8"บ" },
    { IC::PA,  u8"ป" },
    { IC::A,   u8"อ" },
};

static const unordered_map<EInitCons, pair<string, string>>
ThaiHighLowInitCons1Tbl_ = {
    { IC::KHA, { u8"ข",  u8"ค" } },
    { IC::NGA, { u8"หฺง", u8"ง" } },
    { IC::CHA, { u8"ฉ",  u8"ช" } },
    { IC::YA,  { u8"หฺย", u8"ย" } },
    { IC::THA, { u8"ถ",  u8"ท" } },
    { IC::NA,  { u8"หฺน", u8"น" } },
    { IC::PHA, { u8"ผ",  u8"พ" } },
    { IC::FA,  { u8"ฝ",  u8"ฟ" } },
    { IC::MA,  { u8"หฺม", u8"ม" } },
    { IC::RA,  { u8"หฺร", u8"ร" } },
    { IC::LA,  { u8"หฺล", u8"ล" } },
    { IC::WA,  { u8"หฺว", u8"ว" } },
    { IC::SA,  { u8"ส",  u8"ซ" } },
    { IC::HA,  { u8"ห",  u8"ฮ" } },
};
#undef IC

//
// Second Initial Consonant Thai Pronunciations
//

#define SC ESecInitCons
static const unordered_map<ESecInitCons,string>
ThaiSecIConsTbl_ = {
    { SC::NONE, ""                },
    { SC::RA,   PHINTHU_STR u8"ร" },
    { SC::LA,   PHINTHU_STR u8"ล" },
    { SC::WA,   PHINTHU_STR u8"ว" },
};

#undef SC

//
// Ending Consonant Thai Pronunciations
//

#define EC EEndConsClass
static const unordered_map<EEndConsClass, string>
ThaiEndConsTbl_ = {
    { EC::NONE, "" },
    { EC::KOK,  u8"ก" },
    { EC::KOT,  u8"ด" },
    { EC::KOP,  u8"บ" },
    { EC::KONG, u8"ง" },
    { EC::KON,  u8"น" },
    { EC::KOM,  u8"ม" },
    { EC::KOEY, u8"ย" },
    { EC::KOEW, u8"ว" },
};
#undef EC

//
// Tone Thai Pronunciations
//

#define TN ETone
static const unordered_map<ETone, string>
ThaiToneTbl_ = {
    { TN::SAMAN,     ""                },
    { TN::EK,        TONE_EK_STR       },
    { TN::THO,       TONE_THO_STR      },
    { TN::TRI,       TONE_TRI_STR      },
    { TN::CHATTAWA,  TONE_CHATTAWA_STR },
};
#undef TN

//
// Thai Initial Consonant & Tone Determination for Different Syllable Types
//

static pair<string, string>
ThaiLiveIConsTonePair (EInitCons iCons1, ESecInitCons iCons2, ETone tone)
{
    string oICons;
    string oTone;

    if (ThaiMidConsSet_.find (iCons1) != ThaiMidConsSet_.end()) {
        oICons = ThaiMidCons1Tbl_.at (iCons1);
        oTone = ThaiToneTbl_.at (tone);
    } else {
        auto hiloPair = ThaiHighLowInitCons1Tbl_.at (iCons1);
        switch (tone) {
            case ETone::SAMAN:
                oICons = hiloPair.second;
                break;
            case ETone::EK:
                oICons = hiloPair.first;
                oTone = TONE_EK_STR;
                break;
            case ETone::THO:
                oICons = hiloPair.second;
                oTone = TONE_EK_STR;
                break;
            case ETone::TRI:
                oICons = hiloPair.second;
                oTone = TONE_THO_STR;
                break;
            case ETone::CHATTAWA:
                oICons = hiloPair.first;
                break;
        }
    }

    oICons += ThaiSecIConsTbl_.at (iCons2);

    return make_pair (oICons, oTone);
}

static pair<string, string>
ThaiDeadShortIConsTonePair (EInitCons iCons1, ESecInitCons iCons2,
                             ETone tone)
{
    string oICons;
    string oTone;

    if (ThaiMidConsSet_.find (iCons1) != ThaiMidConsSet_.end()) {
        oICons = ThaiMidCons1Tbl_.at (iCons1);
        if (ETone::EK != tone) {
            oTone = ThaiToneTbl_.at (tone);
        }
    } else {
        auto hiloPair = ThaiHighLowInitCons1Tbl_.at (iCons1);
        switch (tone) {
            case ETone::SAMAN: // not exists, just fall back
                oICons = hiloPair.second;
                break;
            case ETone::EK:
                oICons = hiloPair.first;
                break;
            case ETone::THO:
                oICons = hiloPair.second;
                oTone = TONE_EK_STR;
                break;
            case ETone::TRI:
                oICons = hiloPair.second;
                break;
            case ETone::CHATTAWA:
                oICons = hiloPair.second;
                oTone = TONE_CHATTAWA_STR;
                break;
        }
    }

    oICons += ThaiSecIConsTbl_.at (iCons2);

    return make_pair (oICons, oTone);
}

static pair<string, string>
ThaiDeadLongIConsTonePair (EInitCons iCons1, ESecInitCons iCons2,
                            ETone tone)
{
    string oICons;
    string oTone;

    if (ThaiMidConsSet_.find (iCons1) != ThaiMidConsSet_.end()) {
        oICons = ThaiMidCons1Tbl_.at (iCons1);
        if (ETone::EK != tone) {
            oTone = ThaiToneTbl_.at (tone);
        }
    } else {
        auto hiloPair = ThaiHighLowInitCons1Tbl_.at (iCons1);
        switch (tone) {
            case ETone::SAMAN: // not exists, just fall back
                oICons = hiloPair.second;
                break;
            case ETone::EK:
                oICons = hiloPair.first;
                break;
            case ETone::THO:
                oICons = hiloPair.second;
                break;
            case ETone::TRI:
                oICons = hiloPair.second;
                oTone = TONE_THO_STR;
                break;
            case ETone::CHATTAWA:
                oICons = hiloPair.second;
                oTone = TONE_CHATTAWA_STR;
                break;
        }
    }

    oICons += ThaiSecIConsTbl_.at (iCons2);

    return make_pair (oICons, oTone);
}

//
// Thai Syllable Generation based on Vowel
//

// อ้ะ, เอ้า, อั้-
static string
ThaiSylA (EInitCons iCons1, ESecInitCons iCons2, EEndConsClass eCons,
          ETone tone)
{
    if (EEndConsClass::NONE == eCons) {
        auto iConsTonePair
            = ThaiDeadShortIConsTonePair (iCons1, iCons2, tone);
        return iConsTonePair.first + iConsTonePair.second + SARA_A_STR;
    } else if (EEndConsClass::KOEW == eCons) {
        auto iConsTonePair
            = ThaiLiveIConsTonePair (iCons1, iCons2, tone);
        return SARA_E_STR + iConsTonePair.first + iConsTonePair.second
                   + SARA_AA_STR;
    } else {
        auto iConsTonePair
            = IsDeadSyl (true, eCons)
                  ? ThaiDeadShortIConsTonePair (iCons1, iCons2, tone)
                  : ThaiLiveIConsTonePair (iCons1, iCons2, tone);
        return iConsTonePair.first + MAI_HAN_AKAT_STR + iConsTonePair.second
                   + ThaiEndConsTbl_.at (eCons);
    }
}

// อ้า-
static string
ThaiSylAA (EInitCons iCons1, ESecInitCons iCons2, EEndConsClass eCons,
           ETone tone)
{
    auto iConsTonePair
        = IsDeadSyl (false, eCons)
              ? ThaiDeadLongIConsTonePair (iCons1, iCons2, tone)
              : ThaiLiveIConsTonePair (iCons1, iCons2, tone);
    return iConsTonePair.first + iConsTonePair.second + SARA_AA_STR
               + ThaiEndConsTbl_.at (eCons);
}

// อิ้-, อี้-, อึ้-, อุ้-, อู้-
static string
ThaiSylBelowAbove (EInitCons iCons1, ESecInitCons iCons2, bool isShort,
                   EVowel vowel, EEndConsClass eCons, ETone tone)
{
    assert (EVowel::I == vowel || EVowel::II == vowel
            || EVowel::UE == vowel
            || EVowel::U == vowel || EVowel::UU == vowel);

    static const unordered_map<EVowel, string> vowelTbl = {
        { EVowel::I,  SARA_I_STR },
        { EVowel::II,  SARA_II_STR },
        { EVowel::UE, SARA_UE_STR },
        { EVowel::U,  SARA_U_STR },
        { EVowel::UU,  SARA_UU_STR },
    };

    auto iConsTonePair
        = IsDeadSyl (isShort, eCons)
              ? (isShort
                     ? ThaiDeadShortIConsTonePair (iCons1, iCons2, tone)
                     : ThaiDeadLongIConsTonePair (iCons1, iCons2, tone))
              : ThaiLiveIConsTonePair (iCons1, iCons2, tone);
    return iConsTonePair.first + vowelTbl.at (vowel) + iConsTonePair.second
               + ThaiEndConsTbl_.at (eCons);
}

// อื้อ, อึ้-
static string
ThaiSylUEE (EInitCons iCons1, ESecInitCons iCons2, EEndConsClass eCons,
            ETone tone)
{
    auto iConsTonePair
        = IsDeadSyl (false, eCons)
              ? ThaiDeadLongIConsTonePair (iCons1, iCons2, tone)
              : ThaiLiveIConsTonePair (iCons1, iCons2, tone);
    return iConsTonePair.first + SARA_UEE_STR + iConsTonePair.second
               + (EEndConsClass::NONE == eCons
                      ? AU_STR : ThaiEndConsTbl_.at (eCons));
}

// เอ้ะ, เอ็-, แอ้ะ, แอ้-
static string
ThaiSylLeadShort (EInitCons iCons1, ESecInitCons iCons2,
                  EVowel vowel, EEndConsClass eCons, ETone tone)
{
    assert (EVowel::E == vowel || EVowel::AE == vowel);

    static const unordered_map<EVowel, string> vowelTbl = {
        { EVowel::E,  SARA_E_STR },
        { EVowel::AE, SARA_AE_STR },
    };

    auto iConsTonePair
        = IsDeadSyl (true, eCons)
              ? ThaiDeadShortIConsTonePair (iCons1, iCons2, tone)
              : ThaiLiveIConsTonePair (iCons1, iCons2, tone);
    if (EEndConsClass::NONE != eCons && iConsTonePair.second.empty()) {
        iConsTonePair.second = MAITAIKHU_STR;
    }
    return vowelTbl.at (vowel) + iConsTonePair.first + iConsTonePair.second
               + (EEndConsClass::NONE == eCons
                   ? SARA_A_STR : ThaiEndConsTbl_.at (eCons));
}

// เอ้-, แอ้-, โอ้-
static string
ThaiSylLeadLong (EInitCons iCons1, ESecInitCons iCons2,
                 EVowel vowel, EEndConsClass eCons, ETone tone)
{
    assert (EVowel::EE == vowel || EVowel::AEE == vowel || EVowel::OO == vowel);

    static const unordered_map<EVowel, string> vowelTbl = {
        { EVowel::EE,  SARA_E_STR  },
        { EVowel::AEE, SARA_AE_STR },
        { EVowel::OO,  SARA_O_STR  },
    };

    auto iConsTonePair
        = IsDeadSyl (false, eCons)
              ? ThaiDeadLongIConsTonePair (iCons1, iCons2, tone)
              : ThaiLiveIConsTonePair (iCons1, iCons2, tone);
    return vowelTbl.at (vowel) + iConsTonePair.first + iConsTonePair.second
               + ThaiEndConsTbl_.at (eCons);
}

// โอ้ะ, อ้-
static string
ThaiSylO (EInitCons iCons1, ESecInitCons iCons2, EEndConsClass eCons,
          ETone tone)
{
    auto iConsTonePair
        = IsDeadSyl (true, eCons)
              ? ThaiDeadShortIConsTonePair (iCons1, iCons2, tone)
              : ThaiLiveIConsTonePair (iCons1, iCons2, tone);
    if (EEndConsClass::NONE == eCons) {
        return SARA_O_STR + iConsTonePair.first + iConsTonePair.second
                   + SARA_A_STR;
    } else {
        return iConsTonePair.first + iConsTonePair.second
                   + ThaiEndConsTbl_.at (eCons);
    }
}

// เอี้ยะ, เอี้ย-
static string
ThaiSylIA (EInitCons iCons1, ESecInitCons iCons2, bool isShort,
           EEndConsClass eCons, ETone tone)
{
    // Note: There is no short IA with ending consonant.
    //       So, long IA is assumed if it exists.
    if (EEndConsClass::NONE != eCons) {
        isShort = false;
    }
    auto iConsTonePair
        = IsDeadSyl (isShort, eCons)
              ? (isShort
                     ? ThaiDeadShortIConsTonePair (iCons1, iCons2, tone)
                     : ThaiDeadLongIConsTonePair (iCons1, iCons2, tone))
              : ThaiLiveIConsTonePair (iCons1, iCons2, tone);
    return SARA_E_STR
               + iConsTonePair.first + SARA_II_STR + iConsTonePair.second
               + YO_STR
               + (isShort ? SARA_A_STR : ThaiEndConsTbl_.at (eCons));
}

// เอื้อะ, เอื้อ-
static string
ThaiSylUEA (EInitCons iCons1, ESecInitCons iCons2, bool isShort,
            EEndConsClass eCons, ETone tone)
{
    // Note: There is no short UEA with ending consonant.
    //       So, long UEA is assumed if it exists.
    if (EEndConsClass::NONE != eCons) {
        isShort = false;
    }
    auto iConsTonePair
        = IsDeadSyl (isShort, eCons)
              ? (isShort
                     ? ThaiDeadShortIConsTonePair (iCons1, iCons2, tone)
                     : ThaiDeadLongIConsTonePair (iCons1, iCons2, tone))
              : ThaiLiveIConsTonePair (iCons1, iCons2, tone);
    return SARA_E_STR
               + iConsTonePair.first + SARA_UEE_STR + iConsTonePair.second
               + AU_STR
               + (isShort ? SARA_A_STR : ThaiEndConsTbl_.at (eCons));
}

// อั้วะ, อั้ว, อ็ว-, อ้ว-
static string
ThaiSylUA (EInitCons iCons1, ESecInitCons iCons2, bool isShort,
           EEndConsClass eCons, ETone tone)
{
    auto iConsTonePair
        = IsDeadSyl (isShort, eCons)
              ? (isShort
                     ? ThaiDeadShortIConsTonePair (iCons1, iCons2, tone)
                     : ThaiDeadLongIConsTonePair (iCons1, iCons2, tone))
              : ThaiLiveIConsTonePair (iCons1, iCons2, tone);
    if (isShort && EEndConsClass::NONE != eCons
        && iConsTonePair.second.empty())
    {
        iConsTonePair.second = MAITAIKHU_STR;
    }
    if (EEndConsClass::NONE == eCons) {
        return iConsTonePair.first + MAI_HAN_AKAT_STR + iConsTonePair.second
                + WO_STR
                + (isShort ? SARA_A_STR : "");
    } else {
        return iConsTonePair.first + iConsTonePair.second
                + WO_STR
                + ThaiEndConsTbl_.at (eCons);
    }
}

// เอ้าะ, อ้อ, อ้อ-
static string
ThaiSylAU (EInitCons iCons1, ESecInitCons iCons2, bool isShort,
           EEndConsClass eCons, ETone tone)
{
    auto iConsTonePair
        = IsDeadSyl (isShort, eCons)
              ? (isShort
                     ? ThaiDeadShortIConsTonePair (iCons1, iCons2, tone)
                     : ThaiDeadLongIConsTonePair (iCons1, iCons2, tone))
              : ThaiLiveIConsTonePair (iCons1, iCons2, tone);

    if (isShort) {
        if (EEndConsClass::NONE == eCons) {
            return SARA_E_STR + iConsTonePair.first + iConsTonePair.second
                       + SARA_AA_STR + SARA_A_STR;
        }
        if (iConsTonePair.second.empty()) {
            iConsTonePair.second = MAITAIKHU_STR;
        }
    }

    return iConsTonePair.first + iConsTonePair.second
            + AU_STR
            + ThaiEndConsTbl_.at (eCons);
}

// เอ้อะ, เอ้อ, เอิ้-
static string
ThaiSylOE (EInitCons iCons1, ESecInitCons iCons2, bool isShort,
           EEndConsClass eCons, ETone tone)
{
    // Note: There is no short OE with ending consonant.
    //       So, long OE is assumed if it exists.
    if (EEndConsClass::NONE != eCons) {
        isShort = false;
    }
    auto iConsTonePair
        = IsDeadSyl (isShort, eCons)
              ? (isShort
                     ? ThaiDeadShortIConsTonePair (iCons1, iCons2, tone)
                     : ThaiDeadLongIConsTonePair (iCons1, iCons2, tone))
              : ThaiLiveIConsTonePair (iCons1, iCons2, tone);

    if (EEndConsClass::NONE == eCons) {
        return SARA_E_STR + iConsTonePair.first + iConsTonePair.second
                + AU_STR
                + (isShort ? SARA_A_STR : "");
    } else {
        return SARA_E_STR
                + iConsTonePair.first + SARA_I_STR + iConsTonePair.second
                + ThaiEndConsTbl_.at (eCons);
    }
}

//
// Thai Syllable Pronunciation Generation
//

string
Syl::toThai() const
{
    // determine vowel form
    switch (vowel) {
        case EVowel::A:
            return ThaiSylA (iCons1, iCons2, eCons, tone);

        case EVowel::AA:
            return ThaiSylAA (iCons1, iCons2, eCons, tone);

        case EVowel::I:
        case EVowel::UE:
        case EVowel::U:
            return ThaiSylBelowAbove (iCons1, iCons2, true, vowel,
                                      eCons, tone);

        case EVowel::II:
        case EVowel::UU:
            return ThaiSylBelowAbove (iCons1, iCons2, false, vowel,
                                      eCons, tone);

        case EVowel::UEE:
            return ThaiSylUEE (iCons1, iCons2, eCons, tone);

        case EVowel::E:
        case EVowel::AE:
            return ThaiSylLeadShort (iCons1, iCons2, vowel, eCons, tone);

        case EVowel::EE:
        case EVowel::AEE:
        case EVowel::OO:
            return ThaiSylLeadLong (iCons1, iCons2, vowel, eCons, tone);

        case EVowel::O:
            return ThaiSylO (iCons1, iCons2, eCons, tone);

        case EVowel::IA:
            return ThaiSylIA (iCons1, iCons2, true, eCons, tone);

        case EVowel::IAA:
            return ThaiSylIA (iCons1, iCons2, false, eCons, tone);

        case EVowel::UEA:
            return ThaiSylUEA (iCons1, iCons2, true, eCons, tone);

        case EVowel::UEAA:
            return ThaiSylUEA (iCons1, iCons2, false, eCons, tone);

        case EVowel::UA:
            return ThaiSylUA (iCons1, iCons2, true, eCons, tone);

        case EVowel::UAA:
            return ThaiSylUA (iCons1, iCons2, false, eCons, tone);

        case EVowel::AU:
            return ThaiSylAU (iCons1, iCons2, true, eCons, tone);

        case EVowel::AUU:
            return ThaiSylAU (iCons1, iCons2, false, eCons, tone);

        case EVowel::OE:
            return ThaiSylOE (iCons1, iCons2, true, eCons, tone);

        case EVowel::OEE:
            return ThaiSylOE (iCons1, iCons2, false, eCons, tone);
    }
}

//
// Romanized Syllable Pronunciation Generation
//

#define IC EInitCons
static const unordered_map<EInitCons, string>
RomanInitConsTbl_ = {
    { IC::KA,   "k"  },  // ก
    { IC::KHA,  "kh" },  // ข ฃ ค ฅ ฆ
    { IC::NGA,  "ng" },  // ง
    { IC::JA,   "ch" },  // จ
    { IC::CHA,  "ch" },  // ฉ ช ฌ
    { IC::YA,   "y"  },  // ญ ย
    { IC::DA,   "d"  },  // ฎ ด
    { IC::TA,   "t"  },  // ฏ ต
    { IC::THA,  "th" },  // ฐ ฑ ฒ ถ ท ธ
    { IC::NA,   "n"  },  // ณ น
    { IC::BA,   "b"  },  // บ
    { IC::PA,   "p"  },  // ป
    { IC::PHA,  "ph" },  // ผ พ ภ
    { IC::FA,   "f"  },  // ฝ ฟ
    { IC::MA,   "m"  },  // ม
    { IC::RA,   "r"  },  // ร
    { IC::LA,   "l"  },  // ล ฬ
    { IC::WA,   "w"  },  // ว
    { IC::SA,   "s"  },  // ซ ศ ษ ส
    { IC::HA,   "h"  },  // ห ฮ
    { IC::A,    ""   },  // อ
};
#undef IC

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
Syl::toRoman() const
{
    return RomanInitConsTbl_.at (iCons1)
           + RomanSecInitConsTbl_.at (iCons2)
           + RomanVowelTbl_.at (vowel)
           + RomanEndConsTbl_.at (eCons);
}

///////////////////////
//  class SylString  //
///////////////////////

string
SylString::toThai() const
{
    string output;

    auto i = mSyls.begin();
    output = i->toThai();
    while (++i != mSyls.end()) {
        output += '-' + i->toThai();
    }

    return output;
}

string
SylString::toRoman (bool isCapitalize) const
{
    string output;

    auto i = mSyls.begin();
    output = i->toRoman();
    if (isCapitalize) {
        output[0] = toupper (output[0]);
    }
    for (auto prev = i++; i != mSyls.end(); prev = i++) {
        // According to Royal Institute, insert hyphen for 3 cases:
        //   1. prev->eCons == NONE and i->iCons1 == NGA
        //   2. prev->eCons == KONG and i->iCons1 == A
        //   3. i->iCons1 == A
        if (EInitCons::A == i->iCons1
            || (EEndConsClass::NONE == prev->eCons
                && EInitCons::NGA == i->iCons1))
        {
            output += '-';
        }
        output += i->toRoman();
    }

    return output;
}

/*
vi:ts=4:ai:expandtab
*/
