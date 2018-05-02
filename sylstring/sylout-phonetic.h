// sylout-phonetic.h - Phonetic pronunciation output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#ifndef SYLOUT_PHONETIC_H
#define SYLOUT_PHONETIC_H

#include "syl.h"

class PhoneticSylOut : public ISylOut {
public:
    virtual std::string output (const Syl& syl) const;
};

#endif  // SYLOUT_PHONETIC_H

/*
vi:ts=4:ai:expandtab
*/
