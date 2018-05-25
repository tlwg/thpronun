// dict.inl - Dictionary class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-22

//////////////////
//  class Dict  //
//////////////////

inline
Dict::Dict()
    : mTrie (nullptr),
      mData (nullptr) {}

inline
Dict::Dict (const char* dictPath)
    : mTrie (nullptr),
      mData (nullptr)
{
    open (dictPath);
}

inline
Dict::~Dict()
{
    close();
}

inline const Trie*
Dict::trie() const
{
    return mTrie;
}

inline std::string
Dict::getData (int dataIdx) const
{
    return mData + dataIdx;
}


///////////////////
//  class Match  //
///////////////////

inline int
Match::getCurPos() const
{
    return mCurPos;
}

/*
vi:ts=4:ai:expandtab
*/
