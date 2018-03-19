// thcons.inl - Thai consonant properties
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-01-15

inline bool
IsDeadEndConstClass (EEndConstClass c)
{
    return EEndConstClass::KOK == c ||
           EEndConstClass::KOT == c ||
           EEndConstClass::KOP == c;
}

