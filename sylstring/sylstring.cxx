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
IsDeadSyl (bool isShortVowel, EEndConstClass eConst)
{
    return IsDeadEndConstClass (eConst) || (
               isShortVowel && EEndConstClass::NONE == eConst
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

#define IC EInitConst
static const unordered_set<EInitConst>
ThaiMidConstSet_ = {
    IC::KA, // ก
    IC::JA, // จ
    IC::DA, // ฎ ด
    IC::TA, // ฏ ต
    IC::BA, // บ
    IC::PA, // ป
    IC::A,  // อ
};

static const unordered_map<EInitConst,string>
ThaiMidConst1Tbl_ = {
    { IC::KA,  u8"ก" },
    { IC::JA,  u8"จ" },
    { IC::DA,  u8"ด" },
    { IC::TA,  u8"ต" },
    { IC::BA,  u8"บ" },
    { IC::PA,  u8"ป" },
    { IC::A,   u8"อ" },
};

static const unordered_map<EInitConst, pair<string, string>>
ThaiHighLowInitConst1Tbl_ = {
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

#define SC ESecInitConst
static const unordered_map<ESecInitConst,string>
ThaiSecIConstTbl_ = {
    { SC::NONE, ""                },
    { SC::RA,   PHINTHU_STR u8"ร" },
    { SC::LA,   PHINTHU_STR u8"ล" },
    { SC::WA,   PHINTHU_STR u8"ว" },
};

#undef SC

//
// Ending Consonant Thai Pronunciations
//

#define EC EEndConstClass
static const unordered_map<EEndConstClass, string>
ThaiEndConstTbl_ = {
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
ThaiLiveIConstTonePair (EInitConst iConst1, ESecInitConst iConst2, ETone tone)
{
    string oIConst;
    string oTone;

    if (ThaiMidConstSet_.find (iConst1) != ThaiMidConstSet_.end()) {
        oIConst = ThaiMidConst1Tbl_.at (iConst1);
        oTone = ThaiToneTbl_.at (tone);
    } else {
        auto hiloPair = ThaiHighLowInitConst1Tbl_.at (iConst1);
        switch (tone) {
            case ETone::SAMAN:
                oIConst = hiloPair.second;
                break;
            case ETone::EK:
                oIConst = hiloPair.first;
                oTone = TONE_EK_STR;
                break;
            case ETone::THO:
                oIConst = hiloPair.second;
                oTone = TONE_EK_STR;
                break;
            case ETone::TRI:
                oIConst = hiloPair.second;
                oTone = TONE_THO_STR;
                break;
            case ETone::CHATTAWA:
                oIConst = hiloPair.first;
                break;
        }
    }

    oIConst += ThaiSecIConstTbl_.at (iConst2);

    return make_pair (oIConst, oTone);
}

static pair<string, string>
ThaiDeadShortIConstTonePair (EInitConst iConst1, ESecInitConst iConst2,
                             ETone tone)
{
    string oIConst;
    string oTone;

    if (ThaiMidConstSet_.find (iConst1) != ThaiMidConstSet_.end()) {
        oIConst = ThaiMidConst1Tbl_.at (iConst1);
        if (ETone::EK != tone) {
            oTone = ThaiToneTbl_.at (tone);
        }
    } else {
        auto hiloPair = ThaiHighLowInitConst1Tbl_.at (iConst1);
        switch (tone) {
            case ETone::SAMAN: // not exists, just fall back
                oIConst = hiloPair.second;
                break;
            case ETone::EK:
                oIConst = hiloPair.first;
                break;
            case ETone::THO:
                oIConst = hiloPair.second;
                oTone = TONE_EK_STR;
                break;
            case ETone::TRI:
                oIConst = hiloPair.second;
                break;
            case ETone::CHATTAWA:
                oIConst = hiloPair.second;
                oTone = TONE_CHATTAWA_STR;
                break;
        }
    }

    oIConst += ThaiSecIConstTbl_.at (iConst2);

    return make_pair (oIConst, oTone);
}

static pair<string, string>
ThaiDeadLongIConstTonePair (EInitConst iConst1, ESecInitConst iConst2,
                            ETone tone)
{
    string oIConst;
    string oTone;

    if (ThaiMidConstSet_.find (iConst1) != ThaiMidConstSet_.end()) {
        oIConst = ThaiMidConst1Tbl_.at (iConst1);
        if (ETone::EK != tone) {
            oTone = ThaiToneTbl_.at (tone);
        }
    } else {
        auto hiloPair = ThaiHighLowInitConst1Tbl_.at (iConst1);
        switch (tone) {
            case ETone::SAMAN: // not exists, just fall back
                oIConst = hiloPair.second;
                break;
            case ETone::EK:
                oIConst = hiloPair.first;
                break;
            case ETone::THO:
                oIConst = hiloPair.second;
                break;
            case ETone::TRI:
                oIConst = hiloPair.second;
                oTone = TONE_THO_STR;
                break;
            case ETone::CHATTAWA:
                oIConst = hiloPair.second;
                oTone = TONE_CHATTAWA_STR;
                break;
        }
    }

    oIConst += ThaiSecIConstTbl_.at (iConst2);

    return make_pair (oIConst, oTone);
}

//
// Thai Syllable Generation based on Vowel
//

// อ้ะ, เอ้า, อั้-
static string
ThaiSylA (EInitConst iConst1, ESecInitConst iConst2, EEndConstClass eConst,
          ETone tone)
{
    if (EEndConstClass::NONE == eConst) {
        auto iConstTonePair
            = ThaiDeadShortIConstTonePair (iConst1, iConst2, tone);
        return iConstTonePair.first + iConstTonePair.second + SARA_A_STR;
    } else if (EEndConstClass::KOEW == eConst) {
        auto iConstTonePair
            = ThaiLiveIConstTonePair (iConst1, iConst2, tone);
        return SARA_E_STR + iConstTonePair.first + iConstTonePair.second
                   + SARA_AA_STR;
    } else {
        auto iConstTonePair
            = IsDeadSyl (true, eConst)
                  ? ThaiDeadShortIConstTonePair (iConst1, iConst2, tone)
                  : ThaiLiveIConstTonePair (iConst1, iConst2, tone);
        return iConstTonePair.first + MAI_HAN_AKAT_STR + iConstTonePair.second
                   + ThaiEndConstTbl_.at (eConst);
    }
}

// อ้า-
static string
ThaiSylAA (EInitConst iConst1, ESecInitConst iConst2, EEndConstClass eConst,
           ETone tone)
{
    auto iConstTonePair
        = IsDeadSyl (false, eConst)
              ? ThaiDeadLongIConstTonePair (iConst1, iConst2, tone)
              : ThaiLiveIConstTonePair (iConst1, iConst2, tone);
    return iConstTonePair.first + iConstTonePair.second + SARA_AA_STR
               + ThaiEndConstTbl_.at (eConst);
}

// อิ้-, อี้-, อึ้-, อุ้-, อู้-
static string
ThaiSylBelowAbove (EInitConst iConst1, ESecInitConst iConst2, bool isShort,
                   EVowel vowel, EEndConstClass eConst, ETone tone)
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

    auto iConstTonePair
        = IsDeadSyl (isShort, eConst)
              ? (isShort
                     ? ThaiDeadShortIConstTonePair (iConst1, iConst2, tone)
                     : ThaiDeadLongIConstTonePair (iConst1, iConst2, tone))
              : ThaiLiveIConstTonePair (iConst1, iConst2, tone);
    return iConstTonePair.first + vowelTbl.at (vowel) + iConstTonePair.second
               + ThaiEndConstTbl_.at (eConst);
}

// อื้อ, อึ้-
static string
ThaiSylUEE (EInitConst iConst1, ESecInitConst iConst2, EEndConstClass eConst,
            ETone tone)
{
    auto iConstTonePair
        = IsDeadSyl (false, eConst)
              ? ThaiDeadShortIConstTonePair (iConst1, iConst2, tone)
              : ThaiLiveIConstTonePair (iConst1, iConst2, tone);
    return iConstTonePair.first + SARA_UEE_STR + iConstTonePair.second
               + (EEndConstClass::NONE == eConst
                      ? AU_STR : ThaiEndConstTbl_.at (eConst));
}

// เอ้ะ, เอ็-, แอ้ะ, แอ้-
static string
ThaiSylLeadShort (EInitConst iConst1, ESecInitConst iConst2,
                  EVowel vowel, EEndConstClass eConst, ETone tone)
{
    assert (EVowel::E == vowel || EVowel::AE == vowel);

    static const unordered_map<EVowel, string> vowelTbl = {
        { EVowel::E,  SARA_E_STR },
        { EVowel::AE, SARA_AE_STR },
    };

    auto iConstTonePair
        = IsDeadSyl (true, eConst)
              ? ThaiDeadShortIConstTonePair (iConst1, iConst2, tone)
              : ThaiLiveIConstTonePair (iConst1, iConst2, tone);
    if (EEndConstClass::NONE != eConst && iConstTonePair.second.empty()) {
        iConstTonePair.second = MAITAIKHU_STR;
    }
    return vowelTbl.at (vowel) + iConstTonePair.first + iConstTonePair.second
               + (EEndConstClass::NONE == eConst
                   ? SARA_A_STR : ThaiEndConstTbl_.at (eConst));
}

// เอ้-, แอ้-, โอ้-
static string
ThaiSylLeadLong (EInitConst iConst1, ESecInitConst iConst2,
                 EVowel vowel, EEndConstClass eConst, ETone tone)
{
    assert (EVowel::EE == vowel || EVowel::AEE == vowel || EVowel::OO == vowel);

    static const unordered_map<EVowel, string> vowelTbl = {
        { EVowel::EE,  SARA_E_STR  },
        { EVowel::AEE, SARA_AE_STR },
        { EVowel::OO,  SARA_O_STR  },
    };

    auto iConstTonePair
        = IsDeadSyl (false, eConst)
              ? ThaiDeadLongIConstTonePair (iConst1, iConst2, tone)
              : ThaiLiveIConstTonePair (iConst1, iConst2, tone);
    return vowelTbl.at (vowel) + iConstTonePair.first + iConstTonePair.second
               + ThaiEndConstTbl_.at (eConst);
}

// โอ้ะ, อ้-
static string
ThaiSylO (EInitConst iConst1, ESecInitConst iConst2, EEndConstClass eConst,
          ETone tone)
{
    auto iConstTonePair
        = IsDeadSyl (true, eConst)
              ? ThaiDeadShortIConstTonePair (iConst1, iConst2, tone)
              : ThaiLiveIConstTonePair (iConst1, iConst2, tone);
    if (EEndConstClass::NONE == eConst) {
        return SARA_O_STR + iConstTonePair.first + iConstTonePair.second
                   + SARA_A_STR;
    } else {
        return iConstTonePair.first + iConstTonePair.second
                   + ThaiEndConstTbl_.at (eConst);
    }
}

// เอี้ยะ, เอี้ย-
static string
ThaiSylIA (EInitConst iConst1, ESecInitConst iConst2, bool isShort,
           EEndConstClass eConst, ETone tone)
{
    // Note: There is no short IA with ending consonant.
    //       So, long IA is assumed if it exists.
    if (EEndConstClass::NONE != eConst) {
        isShort = false;
    }
    auto iConstTonePair
        = IsDeadSyl (isShort, eConst)
              ? (isShort
                     ? ThaiDeadShortIConstTonePair (iConst1, iConst2, tone)
                     : ThaiDeadLongIConstTonePair (iConst1, iConst2, tone))
              : ThaiLiveIConstTonePair (iConst1, iConst2, tone);
    return SARA_E_STR
               + iConstTonePair.first + SARA_II_STR + iConstTonePair.second
               + YO_STR
               + (isShort ? SARA_A_STR : ThaiEndConstTbl_.at (eConst));
}

// เอื้อะ, เอื้อ-
static string
ThaiSylUEA (EInitConst iConst1, ESecInitConst iConst2, bool isShort,
            EEndConstClass eConst, ETone tone)
{
    // Note: There is no short UEA with ending consonant.
    //       So, long UEA is assumed if it exists.
    if (EEndConstClass::NONE != eConst) {
        isShort = false;
    }
    auto iConstTonePair
        = IsDeadSyl (isShort, eConst)
              ? (isShort
                     ? ThaiDeadShortIConstTonePair (iConst1, iConst2, tone)
                     : ThaiDeadLongIConstTonePair (iConst1, iConst2, tone))
              : ThaiLiveIConstTonePair (iConst1, iConst2, tone);
    return SARA_E_STR
               + iConstTonePair.first + SARA_UEE_STR + iConstTonePair.second
               + AU_STR
               + (isShort ? SARA_A_STR : ThaiEndConstTbl_.at (eConst));
}

// อั้วะ, อั้ว, อ็ว-, อ้ว-
static string
ThaiSylUA (EInitConst iConst1, ESecInitConst iConst2, bool isShort,
           EEndConstClass eConst, ETone tone)
{
    auto iConstTonePair
        = IsDeadSyl (isShort, eConst)
              ? (isShort
                     ? ThaiDeadShortIConstTonePair (iConst1, iConst2, tone)
                     : ThaiDeadLongIConstTonePair (iConst1, iConst2, tone))
              : ThaiLiveIConstTonePair (iConst1, iConst2, tone);
    if (isShort && EEndConstClass::NONE != eConst
        && iConstTonePair.second.empty())
    {
        iConstTonePair.second = MAITAIKHU_STR;
    }
    if (EEndConstClass::NONE == eConst) {
        return iConstTonePair.first + MAI_HAN_AKAT_STR + iConstTonePair.second
                + WO_STR
                + (isShort ? SARA_A_STR : "");
    } else {
        return iConstTonePair.first + iConstTonePair.second
                + WO_STR
                + ThaiEndConstTbl_.at (eConst);
    }
}

// เอ้าะ, อ้อ, อ้อ-
static string
ThaiSylAU (EInitConst iConst1, ESecInitConst iConst2, bool isShort,
           EEndConstClass eConst, ETone tone)
{
    auto iConstTonePair
        = IsDeadSyl (isShort, eConst)
              ? (isShort
                     ? ThaiDeadShortIConstTonePair (iConst1, iConst2, tone)
                     : ThaiDeadLongIConstTonePair (iConst1, iConst2, tone))
              : ThaiLiveIConstTonePair (iConst1, iConst2, tone);

    if (isShort) {
        if (EEndConstClass::NONE == eConst) {
            return SARA_E_STR + iConstTonePair.first + iConstTonePair.second
                       + SARA_AA_STR + SARA_A_STR;
        }
        if (iConstTonePair.second.empty()) {
            iConstTonePair.second = MAITAIKHU_STR;
        }
    }

    return iConstTonePair.first + iConstTonePair.second
            + AU_STR
            + ThaiEndConstTbl_.at (eConst);
}

// เอ้อะ, เอ้อ, เอิ้-
static string
ThaiSylOE (EInitConst iConst1, ESecInitConst iConst2, bool isShort,
           EEndConstClass eConst, ETone tone)
{
    // Note: There is no short OE with ending consonant.
    //       So, long OE is assumed if it exists.
    if (EEndConstClass::NONE != eConst) {
        isShort = false;
    }
    auto iConstTonePair
        = IsDeadSyl (isShort, eConst)
              ? (isShort
                     ? ThaiDeadShortIConstTonePair (iConst1, iConst2, tone)
                     : ThaiDeadLongIConstTonePair (iConst1, iConst2, tone))
              : ThaiLiveIConstTonePair (iConst1, iConst2, tone);

    if (EEndConstClass::NONE == eConst) {
        return SARA_E_STR + iConstTonePair.first + iConstTonePair.second
                + AU_STR
                + (isShort ? SARA_A_STR : "");
    } else {
        return SARA_E_STR
                + iConstTonePair.first + SARA_I_STR + iConstTonePair.second
                + ThaiEndConstTbl_.at (eConst);
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
            return ThaiSylA (iConst1, iConst2, eConst, tone);

        case EVowel::AA:
            return ThaiSylAA (iConst1, iConst2, eConst, tone);

        case EVowel::I:
        case EVowel::UE:
        case EVowel::U:
            return ThaiSylBelowAbove (iConst1, iConst2, true, vowel,
                                      eConst, tone);

        case EVowel::II:
        case EVowel::UU:
            return ThaiSylBelowAbove (iConst1, iConst2, false, vowel,
                                      eConst, tone);

        case EVowel::UEE:
            return ThaiSylUEE (iConst1, iConst2, eConst, tone);

        case EVowel::E:
        case EVowel::AE:
            return ThaiSylLeadShort (iConst1, iConst2, vowel, eConst, tone);

        case EVowel::EE:
        case EVowel::AEE:
        case EVowel::OO:
            return ThaiSylLeadLong (iConst1, iConst2, vowel, eConst, tone);

        case EVowel::O:
            return ThaiSylO (iConst1, iConst2, eConst, tone);

        case EVowel::IA:
            return ThaiSylIA (iConst1, iConst2, true, eConst, tone);

        case EVowel::IAA:
            return ThaiSylIA (iConst1, iConst2, false, eConst, tone);

        case EVowel::UEA:
            return ThaiSylUEA (iConst1, iConst2, true, eConst, tone);

        case EVowel::UEAA:
            return ThaiSylUEA (iConst1, iConst2, false, eConst, tone);

        case EVowel::UA:
            return ThaiSylUA (iConst1, iConst2, true, eConst, tone);

        case EVowel::UAA:
            return ThaiSylUA (iConst1, iConst2, false, eConst, tone);

        case EVowel::AU:
            return ThaiSylAU (iConst1, iConst2, true, eConst, tone);

        case EVowel::AUU:
            return ThaiSylAU (iConst1, iConst2, false, eConst, tone);

        case EVowel::OE:
            return ThaiSylOE (iConst1, iConst2, true, eConst, tone);

        case EVowel::OEE:
            return ThaiSylOE (iConst1, iConst2, false, eConst, tone);
    }
}

//
// Romanized Syllable Pronunciation Generation
//

#define IC EInitConst
static const unordered_map<EInitConst, string>
RomanInitConstTbl_ = {
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

#define SC ESecInitConst
static const unordered_map<ESecInitConst, string>
RomanSecInitConstTbl_ = {
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

#define EC EEndConstClass
static const unordered_map<EEndConstClass, string>
RomanEndConstTbl_ = {
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
    return RomanInitConstTbl_.at (iConst1)
           + RomanSecInitConstTbl_.at (iConst2)
           + RomanVowelTbl_.at (vowel)
           + RomanEndConstTbl_.at (eConst);
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
        //   1. prev->eConst == NONE and i->iConst1 == NGA
        //   2. prev->eConst == KONG and i->iConst1 == A
        //   3. i->iConst1 == A
        if (EInitConst::A == i->iConst1
            || (EEndConstClass::NONE == prev->eConst
                && EInitConst::NGA == i->iConst1))
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
