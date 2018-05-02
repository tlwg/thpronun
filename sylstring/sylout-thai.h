// sylout-thai.h - Thai pronunciation output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#ifndef SYLOUT_THAI_H
#define SYLOUT_THAI_H

#include "syl.h"

class ThaiSylOut : public ISylOut {
public:
    virtual std::string output (const Syl& syl) const;
};

#endif  // SYLOUT_THAI_H

/*
vi:ts=4:ai:expandtab
*/
