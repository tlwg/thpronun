// output-roman.h - Romanization output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#ifndef OUTPUT_ROMAN_H
#define OUTPUT_ROMAN_H

#include "ioutput.h"
#include "sylout-roman.h"

class RomanOutput : public IOutput {
public:
    RomanOutput (bool isCapitalize = false);

    virtual std::string output (const SylString& sylStr) const;
    virtual std::string output (const std::list<SylString>& strList) const;
    virtual std::string output (const PronunDAG& pronDAG) const;

private:
    RomanSylOutput mRomanSylOutput;
    bool           mIsCapitalize;
};

#include "output-roman.inl"

#endif  // OUTPUT_ROMAN_H

/*
vi:ts=4:ai:expandtab
*/
