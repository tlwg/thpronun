// sylstrout-roman.h - SylString Romanization output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#ifndef SYLSTROUT_ROMAN_H
#define SYLSTROUT_ROMAN_H

#include "sylstring.h"

#include <memory>

class RomanSylStringOut : public ISylStringOut {
public:
    RomanSylStringOut (std::unique_ptr<ISylOut> sylOut,
                       bool                     isCapitalize = false);

    virtual std::string output (const SylString& sylStr) const;

private:
    std::unique_ptr<ISylOut> mSylOut;
    bool                     mIsCapitalize;
};

#include "sylstrout-roman.inl"

#endif  // SYLSTROUT_ROMAN_H

/*
vi:ts=4:ai:expandtab
*/
