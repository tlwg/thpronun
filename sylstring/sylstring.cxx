// sylstring.cxx - Thai syllable string class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-01-16

#include "sylstring.h"

using namespace std;

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
        if (EInitConsSound::A == i->iCons1()
            || (EEndConsClass::NONE == prev->eCons()
                && EInitConsSound::NGA == i->iCons1()))
        {
            output += '-';
        }
        output += i->toRoman();
    }

    return output;
}

string
SylString::toPhonetic() const
{
    string output;

    auto i = mSyls.begin();
    output = i->toPhonetic();
    while (++i != mSyls.end()) {
        output += ' ' + i->toPhonetic();
    }

    return output;
}

/*
vi:ts=4:ai:expandtab
*/
