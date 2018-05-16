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

string
JsonOutput::output (const PronunLatt& latt) const
{
    string outStr;

    outStr = "[";
    for (auto chain = latt.begin(); chain != latt.end(); ++chain) {
        if (chain != latt.begin()) {
            outStr += ",";
        }
        outStr += "[";
        for (auto frac = chain->begin(); frac != chain->end(); ++frac) {
            if (frac != chain->begin()) {
                outStr += ",";
            }
            outStr += "[";
            for (auto sylStr = frac->begin(); sylStr != frac->end(); ++sylStr) {
                if (sylStr != frac->begin()) {
                    outStr += ",";
                }
                outStr += output (*sylStr);
            }
            outStr += "]";
        }
        outStr += "]";
    }
    outStr += "]";

    return outStr;
}

/*
vi:ts=4:ai:expandtab
*/
