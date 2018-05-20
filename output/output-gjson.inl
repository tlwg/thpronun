// sylstrout-gjson.inl - Grouped JSON output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-20

#include <utility>

inline
GroupedJsonOutput::GroupedJsonOutput (std::unique_ptr<ISylOutput> sylOutput)
    : JsonOutput (std::move (sylOutput))
{
}

/*
vi:ts=4:ai:expandtab
*/
