// sylstrout-delim.h - SylString deliminated output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#ifndef SYLSTROUT_DELIM_H
#define SYLSTROUT_DELIM_H

#include "sylstring.h"

#include <memory>

class DelimSylStringOut : public ISylStringOut {
public:
    DelimSylStringOut (std::unique_ptr<ISylOut> sylOut, char delim);

    virtual std::string output (const SylString& sylStr) const;

private:
    std::unique_ptr<ISylOut> mSylOut;
    char                     mDelim;
};

#include "sylstrout-delim.inl"

#endif  // SYLSTROUT_DELIM_H

/*
vi:ts=4:ai:expandtab
*/
