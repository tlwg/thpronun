// sylout-roman.h - Romanization output for Syl
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#ifndef SYLOUT_ROMAN_H
#define SYLOUT_ROMAN_H

#include "isyl-output.h"

class RomanSylOutput : public ISylOutput {
public:
    virtual std::string output (const Syl& syl) const;
};

#endif  // SYLOUT_ROMAN_H

/*
vi:ts=4:ai:expandtab
*/
