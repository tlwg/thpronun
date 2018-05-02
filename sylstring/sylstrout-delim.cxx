// sylstrout-delim.cxx - SylString deliminated output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#include "sylstrout-delim.h"

using namespace std;

string
DelimSylStringOut::output (const SylString& sylStr) const
{
    string output;

    auto i = sylStr.begin();
    output = mSylOut->output (*i);
    while (++i != sylStr.end()) {
        output += mDelim + mSylOut->output (*i);
    }

    return output;
}

/*
vi:ts=4:ai:expandtab
*/
