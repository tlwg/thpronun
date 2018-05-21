// lattice.cxx - Pronunciation Possibility Lattice
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-04

#include "lattice.h"

using namespace std;

////////////////////////
//  class PronunFrac  //
////////////////////////

PronunFrac&
PronunFrac::operator+= (const PronunFrac& other)
{
    for (const auto& sylString : other.mAltPronuns) {
        *this += sylString;
    }

    return *this;
}

PronunFrac&
PronunFrac::operator+= (const SylString& sylString)
{
    // keep mAltPronuns sorted & unique
    auto it = mAltPronuns.begin();
    while (it != mAltPronuns.end() && *it < sylString) {
        ++it;
    }
    if (it == mAltPronuns.end() || *it != sylString) {
        mAltPronuns.insert (it, sylString);
    }

    return *this;
}

bool
PronunFrac::operator== (const PronunFrac& other) const
{
    auto thisIt = this->begin();
    auto otherIt = other.begin();
    while (thisIt != this->end() && otherIt != other.end()) {
        if (*thisIt != *otherIt) return false;
        ++thisIt; ++otherIt;
    }
    return thisIt == this->end() && otherIt == other.end();
}

/////////////////////////
//  class PronunChain  //
/////////////////////////

PronunChain&
PronunChain::mergeSingles()
{
    for (auto fracIt = mFracs.begin(); fracIt != mFracs.end(); ++fracIt) {
        if (fracIt->altCount() == 1) {
            auto nextIt = fracIt;
            ++nextIt;
            while (nextIt != mFracs.end() && nextIt->altCount() == 1) {
                *fracIt->begin() += *nextIt->begin();
                nextIt = mFracs.erase (nextIt);
            }
        }
    }

    return *this;
}

////////////////////////
//  class PronunLatt  //
////////////////////////

PronunLatt&
PronunLatt::mergeSingles()
{
    for (auto& chain : *this) {
        chain.mergeSingles();
    }

    return *this;
}

/*
vi:ts=4:ai:expandtab
*/
