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

string
DelimOutput::output (const list<SylString>& strList) const
{
    string outStr;

    for (const auto& str : strList) {
        outStr += output (str) + '\n';
    }

    return outStr;
}

string
DelimOutput::output (const PronunDAG& pronDAG) const
{
    return output (DAGSylStrings (pronDAG, 0));
}

/*
vi:ts=4:ai:expandtab
*/
