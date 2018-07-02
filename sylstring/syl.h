// syl.h - Thai syllable class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-01-16

#ifndef SYL_H
#define SYL_H

#include "sylcomp.h"

#include <string>

class Syl {
public:
    static const Syl Blank;

public:
    explicit Syl (int endPos = -1);
    Syl (int endPos, std::u16string literal);
    Syl (const Syl& other);
    Syl (EInitConsSound iCons1, ESecInitCons iCons2, EVowel vowel,
         EEndConsClass eCons, ETone tone, int endPos = -1);
    Syl (char iCons1, char iCons2, char vowel, char eCons, char tone,
         int endPos = -1);
    // c-tor with description string (of length >= 5)
    Syl (const std::string& desc, int endPos = -1);

    EInitConsSound  iCons1() const;
    ESecInitCons    iCons2() const;
    EVowel          vowel() const;
    EEndConsClass   eCons() const;
    ETone           tone() const;

    bool            isLiteral() const;
    std::u16string  literal() const;

    int             endPos() const;
    void            setEndPos (int pos);

    bool operator== (const Syl& other) const;
    bool operator!= (const Syl& other) const;

    // for sorting purpose
    bool operator< (const Syl& other) const;
    bool operator> (const Syl& other) const;
    bool operator<= (const Syl& other) const;
    bool operator>= (const Syl& other) const;

private:
    EInitConsSound  mICons1;
    ESecInitCons    mICons2;
    EVowel          mVowel;
    EEndConsClass   mECons;
    ETone           mTone;

    std::u16string  mLiteral;

    int             mEndPos;
};

#include "syl.inl"

#endif  // SYL_H

/*
vi:ts=4:ai:expandtab
*/
