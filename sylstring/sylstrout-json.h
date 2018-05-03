// sylstrout-json.h - SylString JSON output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-03

#ifndef SYLSTROUT_JSON_H
#define SYLSTROUT_JSON_H

#include "sylstring.h"

#include <memory>

class JsonSylStringOut : public ISylStringOut {
public:
    JsonSylStringOut (std::unique_ptr<ISylOut> sylOut);

    virtual std::string output (const SylString& sylStr) const;

private:
    std::unique_ptr<ISylOut> mSylOut;
};

#include "sylstrout-json.inl"

#endif  // SYLSTROUT_JSON_H

/*
vi:ts=4:ai:expandtab
*/
