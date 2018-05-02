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
    Syl();
    Syl (const Syl& other);
    Syl (EInitConsSound iCons1, ESecInitCons iCons2, EVowel vowel,
         EEndConsClass eCons, ETone tone);
    Syl (char iCons1, char iCons2, char vowel, char eCons, char tone);
    // c-tor with string of length 5
    Syl (const std::string& aSylStr);

    EInitConsSound  iCons1() const;
    ESecInitCons    iCons2() const;
    EVowel          vowel() const;
    EEndConsClass   eCons() const;
    ETone           tone() const;

    std::string toThai() const;
    std::string toRoman() const;
    std::string toPhonetic() const;

private:
    EInitConsSound  mICons1;
    ESecInitCons    mICons2;
    EVowel          mVowel;
    EEndConsClass   mECons;
    ETone           mTone;
};

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
