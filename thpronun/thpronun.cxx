#include "parser/parser.h"
#include "output/sylout-thai.h"
#include "output/sylout-roman.h"
#include "output/sylout-phonetic.h"
#include "output/output-delim.h"
#include "output/output-roman.h"
#include "output/output-json.h"

#include <iostream>
#include <list>
#include <memory>

using namespace std;

void
DoParse (string word, const list<unique_ptr<IOutput>>& stringOutputs)
{
    cout << word << ":" << endl;
    auto sylList = ParseWord (word);
    for (const auto& s : sylList) {
        bool isFirst = true;
        for (const auto& sylStrOut : stringOutputs) {
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

static unique_ptr<IOutput>
MakeThaiOutput (bool isJson)
{
    if (isJson) {
        return make_unique<JsonOutput> (make_unique<ThaiSylOutput>());
    } else {
        return make_unique<DelimOutput> (make_unique<ThaiSylOutput>(), '-');
    }
}

static unique_ptr<IOutput>
MakeRomanOutput (bool isJson)
{
    if (isJson) {
        return make_unique<JsonOutput> (make_unique<RomanSylOutput>());
    } else {
        return make_unique<RomanOutput>();
    }
}

static unique_ptr<IOutput>
MakePhoneticOutput (bool isJson)
{
    if (isJson) {
        return make_unique<JsonOutput> (make_unique<PhoneticSylOutput>());
    } else {
        return make_unique<DelimOutput> (make_unique<PhoneticSylOutput>(),
                                               ' ');
    }
}

int
main (int argc, const char* argv[])
{
    int optCnt = 0;
    bool isJson = false;
    list<unique_ptr<IOutput>> stringOutputs;

    for (int i = 1; i < argc; ++i) {
        if ('-' == argv[i][0]) {
            switch (argv[i][1]) {
            case 'j':
                isJson = true;
                break;
            case 'r':
                stringOutputs.push_back (MakeRomanOutput (isJson));
                break;
            case 't':
                stringOutputs.push_back (MakeThaiOutput (isJson));
                break;
            case 'p':
                stringOutputs.push_back (MakePhoneticOutput (isJson));
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
    if (stringOutputs.empty()) {
        stringOutputs.push_back (MakeThaiOutput (isJson));
        stringOutputs.push_back (MakeRomanOutput (isJson));
        stringOutputs.push_back (MakePhoneticOutput (isJson));
    }

    if (1 == argc - optCnt) {
        // read word list from stdin
        string word;
        while (getline (cin, word)) {
            DoParse (word, stringOutputs);
        }
    } else {
        // read word list from command line args
        for (int i = 1; i < argc; ++i) {
            if ('-' != argv[i][0]) {
                DoParse (argv[i], stringOutputs);
            }
        }
    }

    return 0;
}


/*
vi:ts=4:ai:expandtab
*/
