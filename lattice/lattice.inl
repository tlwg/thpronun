// lattice.inl - Pronunciation Possibility Lattice
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-04

#include <utility>

////////////////////////
//  class PronunFrac  //
////////////////////////

inline
PronunFrac::PronunFrac()
    : mAltPronuns(), mEndPos (-1) {}

inline
PronunFrac::PronunFrac (int endPos, const SylString& sylString)
    : mAltPronuns(), mEndPos (endPos)
{
    *this += sylString;
}

inline
PronunFrac::PronunFrac (const PronunFrac& other)
    : mAltPronuns (other.mAltPronuns),
      mEndPos (other.mEndPos) {}

inline
PronunFrac::PronunFrac (PronunFrac&& other)
    : mAltPronuns (std::move (other.mAltPronuns)),
      mEndPos (other.mEndPos) {}

inline PronunFrac&
PronunFrac::operator= (const PronunFrac& other)
{
    mAltPronuns = other.mAltPronuns;
    mEndPos = other.mEndPos;
    return *this;
}

inline PronunFrac&
PronunFrac::operator= (const SylString& sylString)
{
    mAltPronuns.clear();
    mEndPos = sylString.endPos();
    return *this += sylString;
}

inline int
PronunFrac::altCount() const
{
    return mAltPronuns.size();
}

inline PronunFrac::iterator
PronunFrac::begin()
{
    return mAltPronuns.begin();
}

inline PronunFrac::iterator
PronunFrac::end()
{
    return mAltPronuns.end();
}

inline PronunFrac::const_iterator
PronunFrac::begin() const
{
    return mAltPronuns.begin();
}

inline PronunFrac::const_iterator
PronunFrac::end() const
{
    return mAltPronuns.end();
}

inline int
PronunFrac::endPos() const
{
    return mEndPos;
}

inline void
PronunFrac::setEndPos (int endPos)
{
    mEndPos = endPos;
}

/////////////////////////
//  class PronunChain  //
/////////////////////////

inline
PronunChain::PronunChain()
    : mFracs() {}

// single elemnt c-tor
inline
PronunChain::PronunChain (const PronunFrac& frac)
    : mFracs()
{
    *this += frac;
}
inline
PronunChain::PronunChain (const PronunChain& other)
    : mFracs (other.mFracs) {}

inline
PronunChain::PronunChain (PronunChain&& other)
    : mFracs (std::move (other.mFracs)) {}


inline PronunChain&
PronunChain::operator= (const PronunChain& other)
{
    mFracs = other.mFracs;
    return *this;
}

inline PronunChain&
PronunChain::operator+= (const PronunChain& other)
{
    mFracs.insert (mFracs.end(), other.mFracs.begin(), other.mFracs.end());
    return *this;
}

inline PronunChain&
PronunChain::operator+= (const PronunFrac& frac)
{
    mFracs.push_back (frac);
    return *this;
}

inline PronunChain::iterator
PronunChain::begin()
{
    return mFracs.begin();
}

inline PronunChain::iterator
PronunChain::end()
{
    return mFracs.end();
}

inline PronunChain::const_iterator
PronunChain::begin() const
{
    return mFracs.begin();
}

inline PronunChain::const_iterator
PronunChain::end() const
{
    return mFracs.end();
}

/////////////////////////
//  class PronunLatt  //
/////////////////////////

inline
PronunLatt::PronunLatt()
    : mAltChains() {}

// single element c-tor
inline
PronunLatt::PronunLatt (const PronunChain& chain)
    : mAltChains()
{
    *this += chain;
}

inline
PronunLatt::PronunLatt (const PronunLatt& other)
    : mAltChains (other.mAltChains) {}

inline
PronunLatt::PronunLatt (PronunLatt&& other)
    : mAltChains (std::move (other.mAltChains)) {}


inline PronunLatt&
PronunLatt::operator= (const PronunLatt& other)
{
    mAltChains = other.mAltChains;
    return *this;
}

inline PronunLatt&
PronunLatt::operator+= (const PronunChain& chain)
{
    mAltChains.push_back (chain);
    return *this;
}

inline int
PronunLatt::altCount() const
{
    return mAltChains.size();
}

inline PronunLatt::iterator
PronunLatt::begin()
{
    return mAltChains.begin();
}

inline PronunLatt::iterator
PronunLatt::end()
{
    return mAltChains.end();
}

inline PronunLatt::const_iterator
PronunLatt::begin() const
{
    return mAltChains.begin();
}

inline PronunLatt::const_iterator
PronunLatt::end() const
{
    return mAltChains.end();
}

/*
vi:ts=4:ai:expandtab
*/
