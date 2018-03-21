// sylstring.inl - Thai syllable string class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-01-16

#include <utility>

/////////////////
//  class Syl  //
/////////////////

inline
Syl::Syl()
  : iCons1 (EInitCons::INVALID),
    iCons2 (ESecInitCons::NONE),
    vowel (EVowel::INVALID),
    eCons (EEndConsClass::NONE),
    tone (ETone::INVALID)
{
}

inline
Syl::Syl (EInitCons iCons1, ESecInitCons iCons2, EVowel vowel,
          EEndConsClass eCons, ETone tone)
  : iCons1 (iCons1),
    iCons2 (iCons2),
    vowel (vowel),
    eCons (eCons),
    tone (tone)
{
}

inline
Syl::Syl (char iCons1, char iCons2, char vowel, char eCons, char tone)
  : iCons1 (static_cast<EInitCons> (iCons1)),
    iCons2 (static_cast<ESecInitCons> (iCons2)),
    vowel (static_cast<EVowel> (vowel)),
    eCons (EndConsCodeToClass (eCons)),
    tone (static_cast<ETone> (tone))
{
}

inline
Syl::Syl (const std::string& aSylStr)
  : iCons1 (static_cast<EInitCons> (aSylStr.at (0))),
    iCons2 (static_cast<ESecInitCons> (aSylStr.at (1))),
    vowel (static_cast<EVowel> (aSylStr.at (2))),
    eCons (EndConsCodeToClass (aSylStr.at (3))),
    tone (static_cast<ETone> (aSylStr.at (4)))
{
}

///////////////////////
//  class SylString  //
///////////////////////

inline
SylString::SylString()
    : mSyls() {}

inline
SylString::SylString (const SylString& other)
    : mSyls (other.mSyls) {}

inline
SylString::SylString (SylString&& other)
    : mSyls (std::move (other.mSyls)) {}

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

/*
vi:ts=4:ai:expandtab
*/
