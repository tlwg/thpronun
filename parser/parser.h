// parser.h - Thai syllable parser class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-02-28

#ifndef PARSER_H
#define PARSER_H

#include "lattice/pron-dag.h"
#include "dict/dict.h"

#include <string>
#include <memory>

class Parser {
public:
    Parser();
    Parser (const char* exceptDictPath);

    bool loadExceptDict (const char* exceptDictPath);

    PronunDAG parseWord (std::string word) const;

private:
    std::unique_ptr<Dict>  mExceptDict;
};

#endif // PARSER_H

/*
vi:ts=4:ai:expandtab
*/
