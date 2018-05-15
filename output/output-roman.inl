// output-roman.inl - Romanization output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#include <utility>

inline
RomanOutput::RomanOutput (std::unique_ptr<ISylOutput> sylOutput,
                          bool                        isCapitalize)
    : mSylOutput (std::move (sylOutput)),
      mIsCapitalize (isCapitalize)
{
}

/*
vi:ts=4:ai:expandtab
*/
