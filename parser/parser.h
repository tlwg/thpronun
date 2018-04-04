// parser.h - Thai syllable parser class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-02-28

#ifndef PARSER_H
#define PARSER_H

#include "sylstring/sylstring.h"

#include <list>
#include <string>

std::list<SylString>
ParseWord (std::string word);

#endif // PARSER_H

/*
vi:ts=4:ai:expandtab
*/
