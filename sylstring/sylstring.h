// sylstring.h - Thai syllable string class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-01-16

#ifndef SYLSTRING_H
#define SYLSTRING_H

#include "sylcomp.h"

#include <list>
#include <string>

class Syl {
public:
    Syl (EInitConst iConst1, ESecInitConst iConst2, EVowel vowel,
         EEndConstClass eConst, ETone tone);
    Syl (char iConst1, char iConst2, char vowel, char eConst, char tone);
    // c-tor with string of length 5
    Syl (const std::string& aSylStr);

    std::string toThai() const;
    std::string toRoman() const;

private:
    EInitConst     iConst1;
    ESecInitConst  iConst2;
    EVowel         vowel;
    EEndConstClass eConst;
    ETone          tone;
};

class SylString {
public:
    SylString& operator= (const Syl& syl);
    SylString& operator+= (const Syl& syl);

    std::string toThai() const;
    std::string toRoman (bool isCapitalize = false) const;

private:
    std::list<Syl> mSyls;
};

#include "sylstring.inl"

#endif  // SYLSTRING_H

/*
vi:ts=4:ai:expandtab
*/
