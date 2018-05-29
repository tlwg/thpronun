// ouptut-gjson.cxx - Grouped JSON output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-20

#include "output-gjson.h"
#include "lattice/pron-dag.h"

using namespace std;

string
GroupedJsonOutput::output (const list<SylString>& strList) const
{
    return output (PronunDAG (strList).fracDAG().lattice());
}

string
GroupedJsonOutput::output (const PronunDAG& pronDAG) const
{
    return output (pronDAG.fracDAG().lattice());
}

string
GroupedJsonOutput::output (const PronunLatt& latt) const
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
                outStr += JsonOutput::output (*sylStr);
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
