// sylstring.h - Thai syllable string class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-01-16

#ifndef SYLSTRING_H
#define SYLSTRING_H

#include "sylcomp.h"

#include <list>
#include <string>

class Syl {
    friend class SylString;

public:
    Syl();
    Syl (EInitCons iCons1, ESecInitCons iCons2, EVowel vowel,
         EEndConsClass eCons, ETone tone);
    Syl (char iCons1, char iCons2, char vowel, char eCons, char tone);
    // c-tor with string of length 5
    Syl (const std::string& aSylStr);

    std::string toThai() const;
    std::string toRoman() const;

private:
    EInitCons       iCons1;
    ESecInitCons    iCons2;
    EVowel          vowel;
    EEndConsClass   eCons;
    ETone           tone;
};

class SylString {
public:
    SylString();
    SylString (const SylString& other);
    SylString (SylString&& other);

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
