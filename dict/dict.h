// dict.h - Dictionary class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-22

#ifndef DICT_H
#define DICT_H

#include <datrie/trie.h>

#include <string>

class Dict {
public:
    Dict();
    Dict (const char* dictPath);
    ~Dict();

    bool open (const char* dictPath);
    void close();

    const Trie* trie() const;
    std::string getData (int dataIdx) const;

private:
    Trie*   mTrie;
    char*   mData;
};


class Match {
public:
    Match (const std::u16string& word, int beginPos, const Dict* dict);
    ~Match();

    bool        findNext();
    int         getCurPos() const;
    std::string getData() const;

private:
    const std::u16string&   mWord;
    int                     mBeginPos;
    int                     mCurPos;
    const Dict*             mDict;
    TrieState*              mTrieState;
};

#include "dict.inl"

#endif  // DICT_H

/*
vi:ts=4:ai:expandtab
*/
