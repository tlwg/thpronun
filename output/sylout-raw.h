// sylout-raw.h - Raw output for Syl
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-31

#ifndef SYLOUT_RAW_H
#define SYLOUT_RAW_H

#include "isyl-output.h"

class RawSylOutput : public ISylOutput {
public:
    virtual std::string output (const Syl& syl) const;
};

#endif  // SYLOUT_RAW_H

/*
vi:ts=4:ai:expandtab
*/
