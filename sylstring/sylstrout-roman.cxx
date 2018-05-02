// sylstrout-roman.cxx - SylString Romanization output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#include "sylstrout-roman.h"

#include <cctype>

using namespace std;

string
RomanSylStringOut::output (const SylString& sylStr) const
{
    string output;

    auto i = sylStr.begin();
    output = mSylOut->output (*i);
    if (mIsCapitalize) {
        output[0] = toupper (output[0]);
    }
    for (auto prev = i++; i != sylStr.end(); prev = i++) {
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
        output += mSylOut->output (*i);
    }

    return output;
}

/*
vi:ts=4:ai:expandtab
*/
