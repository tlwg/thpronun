// thcons.inl - Thai consonant properties
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-01-15

inline bool
IsDeadEndConsClass (EEndConsClass c)
{
    return EEndConsClass::KOK == c ||
           EEndConsClass::KOT == c ||
           EEndConsClass::KOP == c;
}

