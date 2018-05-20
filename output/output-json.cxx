// ouptut-json.cxx - JSON output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-03

#include "output-json.h"

using namespace std;

string
JsonOutput::output (const SylString& sylStr) const
{
    string outStr;

    auto i = sylStr.begin();
    outStr = "[\"" + mSylOutput->output (*i) + "\"";
    while (++i != sylStr.end()) {
        outStr += ",\"" + mSylOutput->output (*i) + "\"";
    }
    outStr += "]";

    return outStr;
}

string
JsonOutput::output (const list<SylString>& strList) const
{
    string outStr;

    outStr = "[";
    auto i = strList.begin();
    outStr += output (*i);
    while (++i != strList.end()) {
        outStr += "," + output (*i);
    }
    outStr += "]";

    return outStr;
}

/*
vi:ts=4:ai:expandtab
*/
