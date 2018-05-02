// sylout-roman.h - Romanization output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#ifndef SYLOUT_ROMAN_H
#define SYLOUT_ROMAN_H

#include "syl.h"

class RomanSylOut : public ISylOut {
public:
    virtual std::string output (const Syl& syl) const;
};

#endif  // SYLOUT_ROMAN_H

/*
vi:ts=4:ai:expandtab
*/
