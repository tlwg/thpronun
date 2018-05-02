// sylstrout-delim.inl - SylString deliminated output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#include <utility>

inline
DelimSylStringOut::DelimSylStringOut (std::unique_ptr<ISylOut> sylOut,
                                      char                     delim)
    : mSylOut (std::move (sylOut)),
      mDelim (delim)
{
}

/*
vi:ts=4:ai:expandtab
*/
