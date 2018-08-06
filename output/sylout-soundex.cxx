// sylout-soundex.cxx - Soundex output for Syl
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-08-06

#include "sylout-soundex.h"

#include <unordered_map>

using namespace std;

//////////////////////////////
//  class SoundexSylOutput  //
//////////////////////////////

#define ICS EInitConsSound
static const unordered_map<EInitConsSound, string>
SoundexInitConsTbl_ = {
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
    { ICS::RA,   "l" },  // ร
    { ICS::LA,   "l" },  // ล ฬ
    { ICS::WA,   "w" },  // ว
    { ICS::SA,   "s" },  // ซ ศ ษ ส
    { ICS::HA,   "h" },  // ห ฮ
    { ICS::A,    "?" },  // อ
};
#undef ICS

#define VW EVowel
static const unordered_map<EVowel, string>
SoundexVowelTbl_ = {
    { VW::A,     "a" },  // อะ
    { VW::AA,    "a" },  // อา
    { VW::I,     "i" },  // อิ
    { VW::II,    "i" },  // อี
    { VW::UE,    "v" },  // อึ
    { VW::UEE,   "v" },  // อือ
    { VW::U,     "u" },  // อุ
    { VW::UU,    "u" },  // อู
    { VW::E,     "e" },  // เอะ
    { VW::EE,    "e" },  // เอ
    { VW::AE,    "x" },  // แอะ
    { VW::AEE,   "x" },  // แอ
    { VW::IA,    "y" },  // เอียะ
    { VW::IAA,   "y" },  // เอีย
    { VW::UEA,   "z" },  // เอือะ
    { VW::UEAA,  "z" },  // เอือ
    { VW::UA,    "t" },  // อัวะ
    { VW::UAA,   "t" },  // อัว
    { VW::O,     "o" },  // โอะ
    { VW::OO,    "o" },  // โอ
    { VW::AU,    "c" },  // เอาะ
    { VW::AUU,   "c" },  // ออ
    { VW::OE,    "w" },  // เออะ
    { VW::OEE,   "w" },  // เออ
};
#undef VW

#define EC EEndConsClass
static const unordered_map<EEndConsClass, string>
SoundexEndConsTbl_ = {
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

string
SoundexSylOutput::output (const Syl& syl) const
{
    if (syl == Syl::Blank)
        return " ";

    if (syl.isLiteral())
        return outputLiteral (syl.literal());

    return SoundexInitConsTbl_.at (syl.iCons1())
           + SoundexVowelTbl_.at (syl.vowel())
           + SoundexEndConsTbl_.at (syl.eCons());
}

/*
vi:ts=4:ai:expandtab
*/
