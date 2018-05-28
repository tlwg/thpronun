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
    typedef std::list<Syl>::iterator       iterator;
    typedef std::list<Syl>::const_iterator const_iterator;

public:
    SylString();
    SylString (const Syl& syl);
    SylString (const std::string& desc);
    SylString (const SylString& other);
    SylString (SylString&& other);

    SylString& operator= (const SylString& other);
    SylString& operator+= (const SylString& other);

    SylString& operator= (const Syl& syl);
    SylString& operator+= (const Syl& syl);

    // iteration
    iterator       begin();
    iterator       end();
    const_iterator begin() const;
    const_iterator end() const;

    int            endPos() const;
    void           shiftEndPos (int offset);

    bool operator== (const SylString& other) const;
    bool operator!= (const SylString& other) const;

    // for sorting purpose
    bool operator< (const SylString& other) const;
    bool operator> (const SylString& other) const;
    bool operator<= (const SylString& other) const;
    bool operator>= (const SylString& other) const;

private:
    std::list<Syl> mSyls;
};

#include "sylstring.inl"

#endif  // SYLSTRING_H

/*
vi:ts=4:ai:expandtab
*/
