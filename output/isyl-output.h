// isyl-output.h - Abstract output interface for Syl
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-15

#ifndef ISYL_OUTPUT_H
#define ISYL_OUTPUT_H

#include "sylstring/syl.h"

#include <string>

class ISylOutput {
public:
    virtual ~ISylOutput() {}

    virtual std::string output (const Syl& syl) const = 0;

    std::string outputLiteral (std::u16string lit) const;
};

#endif  // ISYL_OUTPUT_H

/*
vi:ts=4:ai:expandtab
*/
