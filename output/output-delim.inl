// output-delim.inl - Deliminated output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#include <utility>

inline
DelimOutput::DelimOutput (std::unique_ptr<ISylOutput> sylOutput,
                          char                        delim)
    : mSylOutput (std::move (sylOutput)),
      mDelim (delim)
{
}

/*
vi:ts=4:ai:expandtab
*/
