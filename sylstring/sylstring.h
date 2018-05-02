// sylstring.h - Thai syllable string class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-01-16

#ifndef SYLSTRING_H
#define SYLSTRING_H

#include "syl.h"

#include <list>
#include <string>

class SylString {
public:
    SylString();
    SylString (const SylString& other);
    SylString (SylString&& other);

    SylString& operator= (const SylString& other);

    SylString& operator= (const Syl& syl);
    SylString& operator+= (const Syl& syl);

    std::string toThai() const;
    std::string toRoman (bool isCapitalize = false) const;
    std::string toPhonetic() const;

private:
    std::list<Syl> mSyls;
};

#include "sylstring.inl"

#endif  // SYLSTRING_H

/*
vi:ts=4:ai:expandtab
*/
