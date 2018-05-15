// sylstrout-json.inl - SylString JSON output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-03

#include <utility>

inline
JsonOutput::JsonOutput (std::unique_ptr<ISylOutput> sylOutput)
    : mSylOutput (std::move (sylOutput))
{
}

/*
vi:ts=4:ai:expandtab
*/
