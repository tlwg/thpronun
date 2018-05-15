// lattice.h - Pronunciation Possibility Lattice
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-03

#ifndef LATTICE_H
#define LATTICE_H

#include "sylstring/sylstring.h"

#include <list>

class PronunFrac {
public:
    typedef std::list<SylString>::iterator        iterator;
    typedef std::list<SylString>::const_iterator  const_iterator;

public:
    PronunFrac();
    PronunFrac (int endPos, const SylString& sylString);
    PronunFrac (const PronunFrac& other);
    PronunFrac (PronunFrac&& other);

    PronunFrac& operator= (const PronunFrac& other);
    PronunFrac& operator+= (const PronunFrac& other);

    PronunFrac& operator= (const SylString& sylString);
    PronunFrac& operator+= (const SylString& sylString);

    int            altCount() const;

    iterator       begin();
    iterator       end();
    const_iterator begin() const;
    const_iterator end() const;

    int            endPos() const;
    void           setEndPos (int endPos);

private:
    std::list<SylString>    mAltPronuns;
    int                     mEndPos;
};

class PronunChain {
public:
    typedef std::list<PronunFrac>::iterator       iterator;
    typedef std::list<PronunFrac>::const_iterator const_iterator;

public:
    PronunChain();
    PronunChain (const PronunFrac& frac);
    PronunChain (const PronunChain& other);
    PronunChain (PronunChain&& other);

    PronunChain& operator= (const PronunChain& other);
    PronunChain& operator+= (const PronunChain& other);

    PronunChain& operator+= (const PronunFrac& frac);

    iterator       begin();
    iterator       end();
    const_iterator begin() const;
    const_iterator end() const;

private:
    std::list<PronunFrac>   mFracs;
};

class PronunLatt {
public:
    typedef std::list<PronunChain>::iterator       iterator;
    typedef std::list<PronunChain>::const_iterator const_iterator;

public:
    PronunLatt();
    PronunLatt (const PronunChain& chain);
    PronunLatt (const PronunLatt& other);
    PronunLatt (PronunLatt&& other);

    PronunLatt& operator= (const PronunLatt& other);

    PronunLatt& operator+= (const PronunChain& chain);

    int            altCount() const;

    iterator       begin();
    iterator       end();
    const_iterator begin() const;
    const_iterator end() const;

private:
    std::list<PronunChain>   mAltChains;
};

#include "lattice.inl"

#endif  // LATTICE_H

/*
vi:ts=4:ai:expandtab
*/
