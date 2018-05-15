// output-delim.cxx - Deliminated output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#include "output-delim.h"

using namespace std;

string
DelimOutput::output (const SylString& sylStr) const
{
    string output;

    auto i = sylStr.begin();
    output = mSylOutput->output (*i);
    while (++i != sylStr.end()) {
        output += mDelim + mSylOutput->output (*i);
    }

    return output;
}

/*
vi:ts=4:ai:expandtab
*/
