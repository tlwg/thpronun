#include "parser/parser.h"

#include <iostream>

using namespace std;

void
DoParse (string word)
{
    cout << word << ":" << endl;
    auto sylList = ParseWord (word);
    for (const auto& s : sylList) {
       cout << s.toThai() << '\t' << s.toRoman() << endl;
    }
}

int
main (int argc, const char* argv[])
{
    if (1 == argc) {
        // read word list from stdin
        string word;
        while (getline (cin, word)) {
            DoParse (word);
        }
    } else {
        // read word list from command line args
        for (int i = 1; i < argc; ++i) {
            DoParse (argv[i]);
        }
    }

    return 0;
}


/*
vi:ts=4:ai:expandtab
*/
