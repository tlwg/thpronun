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

/*
vi:ts=4:ai:expandtab
*/
