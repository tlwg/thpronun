// sylstring.inl - Thai syllable string class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-01-16

#include <utility>

///////////////////////
//  class SylString  //
///////////////////////

inline
SylString::SylString()
    : mSyls() {}

inline
SylString::SylString (const Syl& syl)
    : mSyls()
{
    *this += syl;
}

inline
SylString::SylString (const SylString& other)
    : mSyls (other.mSyls) {}

inline
SylString::SylString (SylString&& other)
    : mSyls (std::move (other.mSyls)) {}

inline SylString&
SylString::operator= (const SylString& other)
{
    mSyls = other.mSyls;
    return *this;
}

inline SylString&
SylString::operator+= (const SylString& other)
{
    mSyls.insert (mSyls.end(), other.mSyls.begin(), other.mSyls.end());
    return *this;
}

inline SylString&
SylString::operator= (const Syl& syl)
{
    mSyls.clear();
    return *this += syl;
}

inline SylString&
SylString::operator+= (const Syl& syl)
{
    mSyls.push_back (syl);
    return *this;
}

inline SylString::iterator
SylString::begin()
{
    return mSyls.begin();
}

inline SylString::iterator
SylString::end()
{
    return mSyls.end();
}


inline SylString::const_iterator
SylString::begin() const
{
    return mSyls.begin();
}

inline SylString::const_iterator
SylString::end() const
{
    return mSyls.end();
}

inline int
SylString::endPos() const
{
    return mSyls.empty() ? 0 : mSyls.back().endPos();
}

inline bool
SylString::operator!= (const SylString& other) const
{
    return !(*this == other);
}

inline bool
SylString::operator<= (const SylString& other) const
{
    return !(*this > other);
}

inline bool
SylString::operator>= (const SylString& other) const
{
    return !(*this < other);
}

/*
vi:ts=4:ai:expandtab
*/
