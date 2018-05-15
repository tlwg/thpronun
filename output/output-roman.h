// output-roman.h - Romanization output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#ifndef OUTPUT_ROMAN_H
#define OUTPUT_ROMAN_H

#include "ioutput.h"
#include "isyl-output.h"

#include <memory>

class RomanOutput : public IOutput {
public:
    RomanOutput (std::unique_ptr<ISylOutput> sylOutput,
                 bool                        isCapitalize = false);

    virtual std::string output (const SylString& sylStr) const;

private:
    std::unique_ptr<ISylOutput> mSylOutput;
    bool                        mIsCapitalize;
};

#include "output-roman.inl"

#endif  // OUTPUT_ROMAN_H

/*
vi:ts=4:ai:expandtab
*/
