#include "parser/parser.h"
#include "sylstring/sylout-thai.h"
#include "sylstring/sylout-roman.h"
#include "sylstring/sylout-phonetic.h"
#include "sylstring/sylstrout-delim.h"
#include "sylstring/sylstrout-roman.h"

#include <iostream>
#include <list>
#include <memory>

using namespace std;

void
DoParse (string word, const list<unique_ptr<ISylStringOut>>& stringOuts)
{
    cout << word << ":" << endl;
    auto sylList = ParseWord (word);
    for (const auto& s : sylList) {
        bool isFirst = true;
        for (const auto& sylStrOut : stringOuts) {
            if (!isFirst) {
                cout << '\t';
            }
            isFirst = false;
            cout << sylStrOut->output (s);
        }
        cout << endl;
    }
}

void
Usage (const char* progName)
{
    cerr << "Usage: " << progName << " [options] [word...]" << endl
         << "Options:" << endl
         << "    -r    Outputs Romanization" << endl
         << "    -t    Outputs Thai pronunciation" << endl
         << "    -p    Outputs Phonetic form" << endl
         << "    -h    Displays help" << endl
         << endl
         << "If no word is given, standard input will be read." << endl;
}

int
main (int argc, const char* argv[])
{
    int optCnt = 0;
    list<unique_ptr<ISylStringOut>> stringOuts;

    for (int i = 1; i < argc; ++i) {
        if ('-' == argv[i][0]) {
            switch (argv[i][1]) {
            case 'r':
                stringOuts.push_back (
                    make_unique<RomanSylStringOut> (
                        make_unique<RomanSylOut>()
                    )
                );
                break;
            case 't':
                stringOuts.push_back (
                    make_unique<DelimSylStringOut> (
                        make_unique<ThaiSylOut>(), '-'
                    )
                );
                break;
            case 'p':
                stringOuts.push_back (
                    make_unique<DelimSylStringOut> (
                        make_unique<PhoneticSylOut>(), ' '
                    )
                );
                break;
            case 'h':
                Usage (argv[0]);
                return 1;
            default:
                cerr << "Unknown option '-" << argv[i][1] << "'" << endl;
                Usage (argv[0]);
                return 1;
            }
            ++optCnt;
        }
    }
    if (stringOuts.empty()) {
        stringOuts.push_back (
            make_unique<DelimSylStringOut> (make_unique<ThaiSylOut>(), '-')
        );
        stringOuts.push_back (
            make_unique<RomanSylStringOut> (make_unique<RomanSylOut>())
        );
        stringOuts.push_back (
            make_unique<DelimSylStringOut> (make_unique<PhoneticSylOut>(), ' ')
        );
    }

    if (1 == argc - optCnt) {
        // read word list from stdin
        string word;
        while (getline (cin, word)) {
            DoParse (word, stringOuts);
        }
    } else {
        // read word list from command line args
        for (int i = 1; i < argc; ++i) {
            if ('-' != argv[i][0]) {
                DoParse (argv[i], stringOuts);
            }
        }
    }

    return 0;
}


/*
vi:ts=4:ai:expandtab
*/
