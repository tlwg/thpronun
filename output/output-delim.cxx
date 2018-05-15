// output-delim.cxx - Deliminated output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#include "output-delim.h"

using namespace std;

string
DelimOutput::output (const SylString& sylStr) const
{
    string outStr;

    auto i = sylStr.begin();
    outStr = mSylOutput->output (*i);
    while (++i != sylStr.end()) {
        outStr += mDelim + mSylOutput->output (*i);
    }

    return outStr;
}

/*
vi:ts=4:ai:expandtab
*/
