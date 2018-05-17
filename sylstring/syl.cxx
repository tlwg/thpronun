// syl.cxx - Thai syllable class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-12

#include "syl.h"

using namespace std;

/////////////////
//  class Syl  //
/////////////////

bool
Syl::operator== (const Syl& other) const
{
    return (
        mICons1 == other.mICons1 &&
        mICons2 == other.mICons2 &&
        mVowel  == other.mVowel &&
        mECons  == other.mECons &&
        mTone   == other.mTone
    );
}

bool
Syl::operator< (const Syl& other) const
{
    if (mICons1 < other.mICons1) return true;
    if (mICons1 > other.mICons1) return false;
    if (mICons2 < other.mICons2) return true;
    if (mICons2 > other.mICons2) return false;
    if (mVowel < other.mVowel) return true;
    if (mVowel > other.mVowel) return false;
    if (mECons < other.mECons) return true;
    if (mECons > other.mECons) return false;
    if (mTone < other.mTone) return true;
    if (mTone > other.mTone) return false;
    return mEndPos < other.mEndPos;
}

bool
Syl::operator> (const Syl& other) const
{
    if (mICons1 > other.mICons1) return true;
    if (mICons1 < other.mICons1) return false;
    if (mICons2 > other.mICons2) return true;
    if (mICons2 < other.mICons2) return false;
    if (mVowel > other.mVowel) return true;
    if (mVowel < other.mVowel) return false;
    if (mECons > other.mECons) return true;
    if (mECons < other.mECons) return false;
    if (mTone > other.mTone) return true;
    if (mTone < other.mTone) return false;
    return mEndPos > other.mEndPos;
}

/*
vi:ts=4:ai:expandtab
*/
