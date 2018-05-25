#include "dict/dict.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <list>
#include <utility>

#define DICT_FILENAME  "test.dic"

using namespace std;

Bool
DumpEntry (const AlphaChar* key, TrieData keyData, void* userData)
{
    wstring_convert<codecvt_utf8<char32_t>, char32_t> u32conv;
    cout << u32conv.to_bytes (reinterpret_cast<const char32_t*>(key))
         << " -> "
         << static_cast<const Dict*> (userData)->getData (keyData)
         << endl;
    return TRUE;
}

void
DumpDict (const Dict& dict)
{
    trie_enumerate (dict.trie(), DumpEntry, const_cast<Dict*>(&dict));
}

bool
TestDict()
{
    bool isSuccess = true;

    Dict dict (DICT_FILENAME);

    cout << " Opening dictionary" << endl;
    if (!dict.open (DICT_FILENAME)) {
        cout << "Failed to open dict '" DICT_FILENAME "'" << endl;
        return false;
    }

    cout << " Dictionary dump:" << endl;
    DumpDict (dict);

    cout << " Testing dictionary matching" << endl;
    u16string phrase = u"สามารถปรารถนาได้";

    cout << "  At 0" << endl;
    const list<pair<int, string>> expect0 = {
        { 3, "s_Am4@3" },
        { 6, "s_A_4@2,m_At2@6" },
    };
    Match match0 (phrase, 0, &dict);
    auto expect0It = expect0.begin();
    while (match0.findNext()) {
        cout << "   Found: @" << match0.getCurPos() << ": " << match0.getData()
             << endl;
        if (expect0It == expect0.end()
            || match0.getCurPos() != expect0It->first
            || match0.getData() != expect0It->second)
        {
            cout << "   Not matched with expected [" << expect0It->first
                 << ", '" << expect0It->second << "']"
                 << endl;
            isSuccess = false;
        }
        ++expect0It;
    }

    cout << "  At 6" << endl;
    const list<pair<int, string>> expect6 = {
        { 13, "prAt1@-4,t_a_1@-407,n_A_4@7" },
    };
    Match match6 (phrase, 6, &dict);
    auto expect6It = expect6.begin();
    while (match6.findNext()) {
        cout << "   Found: @" << match6.getCurPos() << ": " << match6.getData()
             << endl;
        if (expect6It == expect6.end()
            || match6.getCurPos() != expect6It->first
            || match6.getData() != expect6It->second)
        {
            cout << "   Not matched with expected [" << expect6It->first
                 << ", '" << expect6It->second << "']"
                 << endl;
            isSuccess = false;
        }
        ++expect6It;
    }

    return isSuccess;
}

int
main()
{
    bool isSuccess = true;

    if (!TestDict()) {
        isSuccess = false;
    }

    return isSuccess ? EXIT_SUCCESS : EXIT_FAILURE;
}

/*
vi:ts=4:ai:expandtab
*/
