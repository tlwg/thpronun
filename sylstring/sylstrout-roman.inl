// sylstrout-roman.inl - SylString Romanization output
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-02

#include <utility>

inline
RomanSylStringOut::RomanSylStringOut (std::unique_ptr<ISylOut> sylOut,
                                      bool                     isCapitalize)
    : mSylOut (std::move (sylOut)),
      mIsCapitalize (isCapitalize)
{
}

/*
vi:ts=4:ai:expandtab
*/
