// sylstrout-json.cxx - SylString JSON output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-03

#include "sylstrout-json.h"

using namespace std;

string
JsonSylStringOut::output (const SylString& sylStr) const
{
    string output;

    auto i = sylStr.begin();
    output = "[\"" + mSylOut->output (*i) + "\"";
    while (++i != sylStr.end()) {
        output += ",\"" + mSylOut->output (*i) + "\"";
    }
    output += "]";

    return output;
}

/*
vi:ts=4:ai:expandtab
*/
