// ioutput.h - Abstract output interface
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-15

#ifndef IOUTPUT_H
#define IOUTPUT_H

#include "sylstring/sylstring.h"

#include <string>

class IOutput {
public:
    virtual ~IOutput() {}

    virtual std::string output (const SylString& sylStr) const = 0;
};

#endif  // IOUTPUT_H

/*
vi:ts=4:ai:expandtab
*/
