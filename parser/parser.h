// parser.h - Thai syllable parser class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-02-28

#ifndef PARSER_H
#define PARSER_H

#include "sylstring/sylstring.h"
#include "dict/dict.h"

#include <list>
#include <string>
#include <memory>

class Parser {
public:
    Parser();
    Parser (const char* exceptDictPath);

    bool loadExceptDict (const char* exceptDictPath);

    std::list<SylString> parseWord (std::string word) const;

private:
    std::unique_ptr<Dict>  mExceptDict;
};

#endif // PARSER_H

/*
vi:ts=4:ai:expandtab
*/
