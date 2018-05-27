// sylstring.cxx - Thai syllable string class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-12

#include "sylstring.h"

using namespace std;

///////////////////////
//  class SylString  //
///////////////////////

SylString::SylString (const string& desc)
{
    size_t begin = 0;
    size_t end;
    while ((end = desc.find (',', begin)) != string::npos) {
        *this += Syl (desc.substr (begin, end - begin));
        begin = end + 1;
    }
    *this += Syl (desc.substr (begin));
}

bool
SylString::operator== (const SylString& other) const
{
    auto thisIt = this->begin();
    auto otherIt = other.begin();
    while (thisIt != this->end() && otherIt != other.end()) {
        if (*thisIt != *otherIt) return false;
        ++thisIt; ++otherIt;
    }
    return thisIt == this->end() && otherIt == other.end();
}

bool
SylString::operator< (const SylString& other) const
{
    auto thisIt = this->begin();
    auto otherIt = other.begin();
    while (thisIt != this->end() && otherIt != other.end()) {
        if (*thisIt < *otherIt) return true;
        if (*thisIt > *otherIt) return false;
        ++thisIt; ++otherIt;
    }
    return otherIt != other.end();
}

bool
SylString::operator> (const SylString& other) const
{
    auto thisIt = this->begin();
    auto otherIt = other.begin();
    while (thisIt != this->end() && otherIt != other.end()) {
        if (*thisIt > *otherIt) return true;
        if (*thisIt < *otherIt) return false;
        ++thisIt; ++otherIt;
    }
    return thisIt != this->end();
}

/*
vi:ts=4:ai:expandtab
*/
