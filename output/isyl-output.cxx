// isyl-output.cxx - Abstract output interface for Syl
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-07-02

#include "isyl-output.h"

#include <locale>
#include <codecvt>

using namespace std;

string
ISylOutput::outputLiteral (std::u16string lit) const
{
    // convert UTF-16 string to UTF-8
    wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t> u16conv;
    string u8lit = u16conv.to_bytes (lit);

    return "(" + u8lit + ")";
}

/*
vi:ts=4:ai:expandtab
*/
