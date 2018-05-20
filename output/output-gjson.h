// output-gjson.h - Grouped JSON output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-20

#ifndef OUTPUT_GJSON_H
#define OUTPUT_GJSON_H

#include "output-json.h"
#include "lattice/lattice.h"

#include <memory>

class GroupedJsonOutput : public JsonOutput {
public:
    GroupedJsonOutput (std::unique_ptr<ISylOutput> sylOutput);

    virtual std::string output (const std::list<SylString>& strList) const;

    std::string output (const PronunLatt& latt) const;
};

#include "output-gjson.inl"

#endif  // OUTPUT_GJSON_H

/*
vi:ts=4:ai:expandtab
*/
