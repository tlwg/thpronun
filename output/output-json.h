// output-json.h - JSON output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-03

#ifndef OUTPUT_JSON_H
#define OUTPUT_JSON_H

#include "ioutput.h"
#include "isyl-output.h"

#include <memory>

class JsonOutput : public IOutput {
public:
    JsonOutput (std::unique_ptr<ISylOutput> sylOutput);

    virtual std::string output (const SylString& sylStr) const;
    virtual std::string output (const std::list<SylString>& strList) const;

private:
    std::unique_ptr<ISylOutput> mSylOutput;
};

#include "output-json.inl"

#endif  // OUTPUT_JSON_H

/*
vi:ts=4:ai:expandtab
*/
