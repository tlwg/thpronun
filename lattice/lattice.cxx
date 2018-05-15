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
    mAltPronuns.push_back (sylString);
    return *this;
}

/*
vi:ts=4:ai:expandtab
*/
