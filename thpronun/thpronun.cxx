#include "parser/parser.h"
#include "sylstring/sylout-thai.h"
#include "sylstring/sylout-roman.h"
#include "sylstring/sylout-phonetic.h"
#include "sylstring/sylstrout-delim.h"
#include "sylstring/sylstrout-roman.h"
#include "sylstring/sylstrout-json.h"

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
         << "    -j    Turns on JSON output" << endl
         << "    -r    Outputs Romanization" << endl
         << "    -t    Outputs Thai pronunciation" << endl
         << "    -p    Outputs Phonetic form" << endl
         << "    -h    Displays help" << endl
         << endl
         << "If no word is given, standard input will be read." << endl;
}

static unique_ptr<ISylStringOut>
ThaiOut (bool isJson)
{
    if (isJson) {
        return make_unique<JsonSylStringOut> (make_unique<ThaiSylOut>());
    } else {
        return make_unique<DelimSylStringOut> (make_unique<ThaiSylOut>(), '-');
    }
}

static unique_ptr<ISylStringOut>
RomanOut (bool isJson)
{
    if (isJson) {
        return make_unique<JsonSylStringOut> (make_unique<RomanSylOut>());
    } else {
        return make_unique<RomanSylStringOut> (make_unique<RomanSylOut>());
    }
}

static unique_ptr<ISylStringOut>
PhoneticOut (bool isJson)
{
    if (isJson) {
        return make_unique<JsonSylStringOut> (make_unique<PhoneticSylOut>());
    } else {
        return make_unique<DelimSylStringOut> (make_unique<PhoneticSylOut>(),
                                               ' ');
    }
}

int
main (int argc, const char* argv[])
{
    int optCnt = 0;
    bool isJson = false;
    list<unique_ptr<ISylStringOut>> stringOuts;

    for (int i = 1; i < argc; ++i) {
        if ('-' == argv[i][0]) {
            switch (argv[i][1]) {
            case 'j':
                isJson = true;
                break;
            case 'r':
                stringOuts.push_back (RomanOut (isJson));
                break;
            case 't':
                stringOuts.push_back (ThaiOut (isJson));
                break;
            case 'p':
                stringOuts.push_back (PhoneticOut (isJson));
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
        stringOuts.push_back (ThaiOut (isJson));
        stringOuts.push_back (RomanOut (isJson));
        stringOuts.push_back (PhoneticOut (isJson));
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
