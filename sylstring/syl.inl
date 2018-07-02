// syl.inl - Thai syllable class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-01-16

/////////////////
//  class Syl  //
/////////////////

inline
Syl::Syl (int endPos)
  : mICons1 (EInitConsSound::INVALID),
    mICons2 (ESecInitCons::NONE),
    mVowel (EVowel::INVALID),
    mECons (EEndConsClass::NONE),
    mTone (ETone::INVALID),
    mLiteral(),
    mEndPos (endPos)
{
}

inline
Syl::Syl (int endPos, std::u16string literal)
  : mICons1 (EInitConsSound::INVALID),
    mICons2 (ESecInitCons::NONE),
    mVowel (EVowel::INVALID),
    mECons (EEndConsClass::NONE),
    mTone (ETone::INVALID),
    mLiteral (literal),
    mEndPos (endPos)
{
}

inline
Syl::Syl (const Syl& other)
  : mICons1 (other.mICons1),
    mICons2 (other.mICons2),
    mVowel (other.mVowel),
    mECons (other.mECons),
    mTone (other.mTone),
    mLiteral (other.mLiteral),
    mEndPos (other.mEndPos)
{
}

inline
Syl::Syl (EInitConsSound iCons1, ESecInitCons iCons2, EVowel vowel,
          EEndConsClass eCons, ETone tone, int endPos)
  : mICons1 (iCons1),
    mICons2 (iCons2),
    mVowel (vowel),
    mECons (eCons),
    mTone (tone),
    mLiteral(),
    mEndPos (endPos)
{
}

inline
Syl::Syl (char iCons1, char iCons2, char vowel, char eCons, char tone,
          int endPos)
  : mICons1 (InitConsCodeToSound (iCons1)),
    mICons2 (static_cast<ESecInitCons> (iCons2)),
    mVowel (static_cast<EVowel> (vowel)),
    mECons (EndConsCodeToClass (eCons)),
    mTone (ToneCodeToTone (tone)),
    mLiteral(),
    mEndPos (endPos)
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

inline bool
Syl::isLiteral() const
{
    return mLiteral.size() != 0;
}

inline std::u16string
Syl::literal() const
{
    return mLiteral;
}

inline int
Syl::endPos() const
{
    return mEndPos;
}

inline void
Syl::setEndPos (int pos)
{
    mEndPos = pos;
}

inline bool
Syl::operator!= (const Syl& other) const
{
    return !(*this == other);
}

inline bool
Syl::operator<= (const Syl& other) const
{
    return !(*this > other);
}

inline bool
Syl::operator>= (const Syl& other) const
{
    return !(*this < other);
}

/*
vi:ts=4:ai:expandtab
*/
