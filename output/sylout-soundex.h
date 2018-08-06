// sylout-soundex.h - Soundex output for Syl
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-08-06

#ifndef SYLOUT_SOUNDEX_H
#define SYLOUT_SOUNDEX_H

#include "isyl-output.h"

class SoundexSylOutput : public ISylOutput {
public:
    virtual std::string output (const Syl& syl) const;
};

#endif  // SYLOUT_SOUNDEX_H

/*
vi:ts=4:ai:expandtab
*/
