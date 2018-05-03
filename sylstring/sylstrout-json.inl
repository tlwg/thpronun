// sylstrout-json.inl - SylString JSON output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-03

#include <utility>

inline
JsonSylStringOut::JsonSylStringOut (std::unique_ptr<ISylOut> sylOut)
    : mSylOut (std::move (sylOut))
{
}

/*
vi:ts=4:ai:expandtab
*/
