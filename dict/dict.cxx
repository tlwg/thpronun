// dict.cxx - Dictionary class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-22

#include "dict.h"

#include <cstdio>

using namespace std;

//////////////////
//  class Dict  //
//////////////////

static bool
ReadInt32 (FILE* input, int32_t& output)
{
    unsigned char buff[4];
    if (fread (buff, 4, 1, input) != 1)
        return false;

    output = (buff[0] << 24) | (buff[1] << 16) |  (buff[2] << 8) | buff[3];
    return true;
}

static char*
ReadDataBank (FILE* input)
{
    int bankSize;
    if (!ReadInt32 (input, bankSize))
        return nullptr;

    char* data = new char[bankSize];
    if (fread (data, bankSize, 1, input) != 1) {
        delete[] data;
        return nullptr;
    }

    return data;
}

bool
Dict::open (const char* dictPath)
{
    close();

    FILE *dictFile = fopen (dictPath, "rb");
    if (!dictFile)
        return false;

    mTrie = trie_fread (dictFile);
    mData = ReadDataBank (dictFile);

    fclose (dictFile);
    return mTrie != nullptr && mData != nullptr;
}

void
Dict::close()
{
    if (mTrie) {
        trie_free (mTrie);
        mTrie = nullptr;
    }
    if (mData) {
        delete[] mData;
        mData = nullptr;
    }
}


///////////////////
//  class Match  //
///////////////////

Match::Match (const std::u16string& word, int beginPos, const Dict* dict)
    : mWord (word),
      mBeginPos (beginPos),
      mCurPos (beginPos),
      mDict (dict),
      mTrieState (nullptr)
{
    if (dict->trie()) {
        mTrieState = trie_root (dict->trie());
    }
}

Match::~Match()
{
    if (mTrieState) {
        trie_state_free (mTrieState);
    }
}

bool
Match::findNext()
{
    if (!mTrieState)
        return false;

    while (mCurPos < mWord.size()
           && trie_state_walk (mTrieState, mWord[mCurPos]))
    {
        ++mCurPos;
        if (trie_state_is_terminal (mTrieState)) {
            return true;
        }
    }

    return false;
}

string
Match::getData() const
{
    TrieData trieData = trie_state_get_data (mTrieState);
    if (TRIE_DATA_ERROR == trieData)
        return "";
    return mDict->getData (trieData);
}

/*
vi:ts=4:ai:expandtab
*/
