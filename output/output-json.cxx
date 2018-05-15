// ouptut-json.cxx - JSON output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-03

#include "output-json.h"

using namespace std;

string
JsonOutput::output (const SylString& sylStr) const
{
    string output;

    auto i = sylStr.begin();
    output = "[\"" + mSylOutput->output (*i) + "\"";
    while (++i != sylStr.end()) {
        output += ",\"" + mSylOutput->output (*i) + "\"";
    }
    output += "]";

    return output;
}

/*
vi:ts=4:ai:expandtab
*/
