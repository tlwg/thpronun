// sylcomp.cxx - Thai syllable fundamental components
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-03-19

#include "sylcomp.h"

#include <unordered_map>

using namespace std;

#define ECC EEndConstClass
static const unordered_map<char, EEndConstClass>
EndConstCodeToClassTbl_ = {
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

EEndConstClass
EndConstCodeToClass (char c)
{
    return EndConstCodeToClassTbl_.at (c);
}

