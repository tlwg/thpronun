// ioutput.h - Abstract output interface
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-15

#ifndef IOUTPUT_H
#define IOUTPUT_H

#include "sylstring/sylstring.h"
#include "lattice/pron-dag.h"

#include <string>
#include <list>

class IOutput {
public:
    virtual ~IOutput() {}

    virtual std::string output (const SylString& sylStr) const = 0;
    virtual std::string output (const std::list<SylString>& strList) const = 0;
    virtual std::string output (const PronunDAG& pronDAG) const = 0;

protected:
    static std::list<SylString>
    DAGSylStrings (const PronunDAG& pronDAG, int root);
};

#endif  // IOUTPUT_H

/*
vi:ts=4:ai:expandtab
*/
