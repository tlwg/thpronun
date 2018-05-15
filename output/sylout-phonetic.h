// sylout-phonetic.h - Phonetic output for Syl
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#ifndef SYLOUT_PHONETIC_H
#define SYLOUT_PHONETIC_H

#include "isyl-output.h"

class PhoneticSylOutput : public ISylOutput {
public:
    virtual std::string output (const Syl& syl) const;
};

#endif  // SYLOUT_PHONETIC_H

/*
vi:ts=4:ai:expandtab
*/
