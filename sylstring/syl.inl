// syl.inl - Thai syllable class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-01-16

/////////////////
//  class Syl  //
/////////////////

inline
Syl::Syl()
  : mICons1 (EInitConsSound::INVALID),
    mICons2 (ESecInitCons::NONE),
    mVowel (EVowel::INVALID),
    mECons (EEndConsClass::NONE),
    mTone (ETone::INVALID)
{
}

inline
Syl::Syl (const Syl& other)
  : mICons1 (other.mICons1),
    mICons2 (other.mICons2),
    mVowel (other.mVowel),
    mECons (other.mECons),
    mTone (other.mTone)
{
}

inline
Syl::Syl (EInitConsSound iCons1, ESecInitCons iCons2, EVowel vowel,
          EEndConsClass eCons, ETone tone)
  : mICons1 (iCons1),
    mICons2 (iCons2),
    mVowel (vowel),
    mECons (eCons),
    mTone (tone)
{
}

inline
Syl::Syl (char iCons1, char iCons2, char vowel, char eCons, char tone)
  : mICons1 (InitConsCodeToSound (iCons1)),
    mICons2 (static_cast<ESecInitCons> (iCons2)),
    mVowel (static_cast<EVowel> (vowel)),
    mECons (EndConsCodeToClass (eCons)),
    mTone (ToneCodeToTone (tone))
{
}

inline
Syl::Syl (const std::string& aSylStr)
  : mICons1 (InitConsCodeToSound (aSylStr.at (0))),
    mICons2 (static_cast<ESecInitCons> (aSylStr.at (1))),
    mVowel (static_cast<EVowel> (aSylStr.at (2))),
    mECons (EndConsCodeToClass (aSylStr.at (3))),
    mTone (ToneCodeToTone (aSylStr.at (4)))
{
}

inline EInitConsSound
Syl::iCons1() const
{
    return mICons1;
}

inline ESecInitCons
Syl::iCons2() const
{
    return mICons2;
}

inline EVowel
Syl::vowel() const
{
    return mVowel;
}

inline EEndConsClass
Syl::eCons() const
{
    return mECons;
}

inline ETone
Syl::tone() const
{
    return mTone;
}

/*
vi:ts=4:ai:expandtab
*/
