// ioutput.cxx - Abstract output interface
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-29

#include "ioutput.h"

using namespace std;

list<SylString>
IOutput::DAGSylStrings (const PronunDAG& pronDAG, int root)
{
    list<SylString> sylStrings;
    auto range = pronDAG.outEdges (root);
    for (auto it = range.first; it != range.second; ++it) {
        list<SylString> childStrs = DAGSylStrings (pronDAG, it->second.target);
        if (childStrs.size() == 0) {
            sylStrings.push_back (SylString (it->second.edgeVal));
        } else {
            for (const auto& sylString : childStrs) {
                SylString newSylStr (it->second.edgeVal);
                newSylStr += sylString;
                sylStrings.push_back (newSylStr);
            }
        }
    }
    return sylStrings;
}

/*
vi:ts=4:ai:expandtab
*/
