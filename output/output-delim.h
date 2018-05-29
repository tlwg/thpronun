// output-delim.h - Deliminated output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#ifndef OUTPUT_DELIM_H
#define OUTPUT_DELIM_H

#include "ioutput.h"
#include "isyl-output.h"

#include <memory>

class DelimOutput : public IOutput {
public:
    DelimOutput (std::unique_ptr<ISylOutput> sylOutput, char delim);

    virtual std::string output (const SylString& sylStr) const;
    virtual std::string output (const std::list<SylString>& strList) const;
    virtual std::string output (const PronunDAG& pronDAG) const;

private:
    std::unique_ptr<ISylOutput> mSylOutput;
    char                        mDelim;
};

#include "output-delim.inl"

#endif  // OUTPUT_DELIM_H

/*
vi:ts=4:ai:expandtab
*/
