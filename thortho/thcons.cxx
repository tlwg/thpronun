// thcons.cxx - Thai consonant properties
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-01-15

#include "thcons.h"
#include "thuni.h"

#include <cassert>

using namespace std;

#define IC EInitConsClass

static const EInitConsClass InitConsClassTbl_[46] = {
    // ก ข ฃ ค ฅ ฆ ง
    IC::MID,  IC::HIGH, IC::HIGH, IC::LOWP, IC::LOWP, IC::LOWP, IC::LOWS,
    // จ ฉ ช ซ ฌ ญ
    IC::MID,  IC::HIGH, IC::LOWP, IC::LOWP, IC::LOWP, IC::LOWS,
    // ฎ ฏ ฐ ฑ ฒ ณ
    IC::MID,  IC::MID,  IC::HIGH, IC::LOWP, IC::LOWP, IC::LOWS,
    // ด ต ถ ท ธ น
    IC::MID,  IC::MID,  IC::HIGH, IC::LOWP, IC::LOWP, IC::LOWS,
    // บ ป ผ ฝ พ ฟ ภ ม
    IC::MID,  IC::MID,  IC::HIGH, IC::HIGH, IC::LOWP, IC::LOWP, IC::LOWP, IC::LOWS,
    // ย ร ฤ ล ฦ ว
    IC::LOWS, IC::LOWS, IC::LOWS, IC::LOWS, IC::LOWS, IC::LOWS,
    // ศ ษ ส ห ฬ อ ฮ
    IC::HIGH, IC::HIGH, IC::HIGH, IC::HIGH, IC::LOWS, IC::MID,  IC::LOWP
};

#undef IC

EInitConsClass
InitConsClass (char16_t c)
{
    assert (UTH_KO_KAI <= c && c <= UTH_HO_NOKHUK);
    return InitConsClassTbl_[c - UTH_KO_KAI];
}

#define IC EInitConsSound

static const EInitConsSound InitConsSoundTbl_[46] = {
    // ก ข ฃ ค ฅ ฆ ง
    IC::KA,  IC::KHA, IC::KHA, IC::KHA, IC::KHA, IC::KHA, IC::NGA,
    // จ ฉ ช ซ ฌ ญ
    IC::JA,  IC::CHA, IC::CHA, IC::SA, IC::CHA, IC::YA,
    // ฎ ฏ ฐ ฑ ฒ ณ
    IC::DA,  IC::TA,  IC::THA, IC::THA, IC::THA, IC::NA,
    // ด ต ถ ท ธ น
    IC::DA,  IC::TA,  IC::THA, IC::THA, IC::THA, IC::NA,
    // บ ป ผ ฝ พ ฟ ภ ม
    IC::BA,  IC::PA,  IC::PHA, IC::FA, IC::PHA, IC::FA, IC::PHA, IC::MA,
    // ย ร ฤ ล ฦ ว
    IC::YA, IC::RA, IC::INVALID, IC::LA, IC::INVALID, IC::WA,
    // ศ ษ ส ห ฬ อ ฮ
    IC::SA, IC::SA, IC::SA, IC::HA, IC::LA, IC::A,  IC::HA
};

#undef IC

EInitConsSound
InitConsSound (char16_t c)
{
    assert (UTH_KO_KAI <= c && c <= UTH_HO_NOKHUK);
    return InitConsSoundTbl_[c - UTH_KO_KAI];
}

#define EC EEndConsClass

static const EEndConsClass EndConsClassTbl_[46] = {
    // ก ข ฃ ค ฅ ฆ ง
    EC::KOK,  EC::KOK,  EC::KOK,  EC::KOK,  EC::KOK,  EC::KOK,  EC::KONG,
    // จ ฉ ช ซ ฌ ญ
    EC::KOT,  EC::KOT,  EC::KOT,  EC::KOT,  EC::KOT,  EC::KON,
    // ฎ ฏ ฐ ฑ ฒ ณ
    EC::KOT,  EC::KOT,  EC::KOT,  EC::KOT,  EC::KOT,  EC::KON,
    // ด ต ถ ท ธ น
    EC::KOT,  EC::KOT,  EC::KOT,  EC::KOT,  EC::KOT,  EC::KON,
    // บ ป ผ ฝ พ ฟ ภ ม
    EC::KOP,  EC::KOP,  EC::KOP,  EC::KOP,  EC::KOP,  EC::KOP,  EC::KOP,  EC::KOM,
    // ย ร ฤ ล ฦ ว
    EC::KOEY, EC::KON,  EC::NONE, EC::KON,  EC::NONE, EC::KOEW,
    // ศ ษ ส ห ฬ อ ฮ
    EC::KOT,  EC::KOT,  EC::KOT,  EC::NONE, EC::KON,  EC::NONE, EC::NONE
};

#undef EC

EEndConsClass
EndConsClass (char16_t c)
{
    assert (UTH_KO_KAI <= c && c <= UTH_HO_NOKHUK);
    return EndConsClassTbl_[c - UTH_KO_KAI];
}

/*
vi:ts=4:ai:expandtab
*/
