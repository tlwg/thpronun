// sylout-raw.cxx - Raw output for Syl
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-31

#include "sylout-raw.h"

#include <unordered_map>

using namespace std;

//////////////////////////
//  class RawSylOutput  //
//////////////////////////

#define ICS EInitConsSound
static const unordered_map<EInitConsSound, string>
RawInitConsTbl_ = {
    { ICS::KA,   "k" },  // ก
    { ICS::KHA,  "c" },  // ข ฃ ค ฅ ฆ
    { ICS::NGA,  "g" },  // ง
    { ICS::JA,   "j" },  // จ
    { ICS::CHA,  "J" },  // ฉ ช ฌ
    { ICS::YA,   "y" },  // ญ ย
    { ICS::DA,   "d" },  // ฎ ด
    { ICS::TA,   "t" },  // ฏ ต
    { ICS::THA,  "T" },  // ฐ ฑ ฒ ถ ท ธ
    { ICS::NA,   "n" },  // ณ น
    { ICS::BA,   "b" },  // บ
    { ICS::PA,   "p" },  // ป
    { ICS::PHA,  "P" },  // ผ พ ภ
    { ICS::FA,   "f" },  // ฝ ฟ
    { ICS::MA,   "m" },  // ม
    { ICS::RA,   "r" },  // ร
    { ICS::LA,   "l" },  // ล ฬ
    { ICS::WA,   "w" },  // ว
    { ICS::SA,   "s" },  // ซ ศ ษ ส
    { ICS::HA,   "h" },  // ห ฮ
    { ICS::A,    "?" },  // อ
};
#undef ICS

#define SC ESecInitCons
static const unordered_map<ESecInitCons, string>
RawSecInitConsTbl_ = {
    { SC::NONE,  "_" },
    { SC::RA,    "r" },  // ร ควบ
    { SC::LA,    "l" },  // ล ควบ
    { SC::WA,    "w" },  // ว ควบ
};
#undef SC

#define VW EVowel
static const unordered_map<EVowel, string>
RawVowelTbl_ = {
    { VW::A,     "a" },  // อะ
    { VW::AA,    "A" },  // อา
    { VW::I,     "i" },  // อิ
    { VW::II,    "I" },  // อี
    { VW::UE,    "v" },  // อึ
    { VW::UEE,   "V" },  // อือ
    { VW::U,     "u" },  // อุ
    { VW::UU,    "U" },  // อู
    { VW::E,     "e" },  // เอะ
    { VW::EE,    "E" },  // เอ
    { VW::AE,    "x" },  // แอะ
    { VW::AEE,   "X" },  // แอ
    { VW::IA,    "y" },  // เอียะ
    { VW::IAA,   "Y" },  // เอีย
    { VW::UEA,   "z" },  // เอือะ
    { VW::UEAA,  "Z" },  // เอือ
    { VW::UA,    "t" },  // อัวะ
    { VW::UAA,   "T" },  // อัว
    { VW::O,     "o" },  // โอะ
    { VW::OO,    "O" },  // โอ
    { VW::AU,    "c" },  // เอาะ
    { VW::AUU,   "C" },  // ออ
    { VW::OE,    "w" },  // เออะ
    { VW::OEE,   "W" },  // เออ
};
#undef VW

#define EC EEndConsClass
static const unordered_map<EEndConsClass, string>
RawEndConsTbl_ = {
    { EC::NONE,  "_" },  // แม่ ก กา
    { EC::KOK,   "k" },  // แม่กก
    { EC::KOT,   "t" },  // แม่กด
    { EC::KOP,   "p" },  // แม่กบ
    { EC::KONG,  "g" },  // แม่กง
    { EC::KON,   "n" },  // แม่กน
    { EC::KOM,   "m" },  // แม่กม
    { EC::KOEY,  "y" },  // แม่เกย
    { EC::KOEW,  "w" },  // แม่เกอว
};
#undef EC

#define TN ETone
static const unordered_map<ETone, string>
RawToneTbl_ = {
    { TN::SAMAN,     "0" },
    { TN::EK,        "1" },
    { TN::THO,       "2" },
    { TN::TRI,       "3" },
    { TN::CHATTAWA,  "4" },
};
#undef TN

string
RawSylOutput::output (const Syl& syl) const
{
    if (syl == Syl::Blank)
        return " ";

    if (syl.isLiteral())
        return outputLiteral (syl.literal()) + "@" + to_string (syl.endPos());

    return RawInitConsTbl_.at (syl.iCons1())
           + RawSecInitConsTbl_.at (syl.iCons2())
           + RawVowelTbl_.at (syl.vowel())
           + RawEndConsTbl_.at (syl.eCons())
           + RawToneTbl_.at (syl.tone())
           + "@" + to_string (syl.endPos());
}

/*
vi:ts=4:ai:expandtab
*/
