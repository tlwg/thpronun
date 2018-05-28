#include "parser/parser.h"
#include "output/sylout-thai.h"
#include "output/sylout-roman.h"
#include "output/sylout-phonetic.h"
#include "output/output-delim.h"
#include "output/output-roman.h"
#include "output/output-json.h"
#include "output/output-gjson.h"

#include <iostream>
#include <list>
#include <memory>

#define EXCEPT_DICT_PATH "except.dic"

using namespace std;

void
DoParse (const Parser& parser, string word,
         const list<unique_ptr<IOutput>>& stringOutputs)
{
    cout << word << ":" << endl;
    auto sylList = parser.parseWord (word);
    for (const auto& sylStrOut : stringOutputs) {
        cout << sylStrOut->output (sylList) << endl;;
    }
}

void
Usage (const char* progName)
{
    cerr << "Usage: " << progName << " [options] [word...]" << endl
         << "Options:" << endl
         << "    -j    Turns on JSON output" << endl
         << "    -g    Turns on grouping in JSON output (implies '-j')" << endl
         << "    -r    Outputs Romanization" << endl
         << "    -t    Outputs Thai pronunciation" << endl
         << "    -p    Outputs Phonetic form" << endl
         << "    -h    Displays help" << endl
         << endl
         << "If no word is given, standard input will be read." << endl;
}

static unique_ptr<IOutput>
MakeThaiOutput (bool isJson, bool isGroup)
{
    auto thaiSylOutput = make_unique<ThaiSylOutput>();

    if (isJson) {
        if (isGroup) {
            return make_unique<GroupedJsonOutput> (move (thaiSylOutput));
        } else {
            return make_unique<JsonOutput> (move (thaiSylOutput));
        }
    } else {
        return make_unique<DelimOutput> (move (thaiSylOutput), '-');
    }
}

static unique_ptr<IOutput>
MakeRomanOutput (bool isJson, bool isGroup)
{
    if (isJson) {
        auto romanSylOutput = make_unique<RomanSylOutput>();

        if (isGroup) {
            return make_unique<GroupedJsonOutput> (move (romanSylOutput));
        } else {
            return make_unique<JsonOutput> (move (romanSylOutput));
        }
    } else {
        return make_unique<RomanOutput>();
    }
}

static unique_ptr<IOutput>
MakePhoneticOutput (bool isJson, bool isGroup)
{
    auto phoneticSylOutput = make_unique<PhoneticSylOutput>();

    if (isJson) {
        if (isGroup) {
            return make_unique<GroupedJsonOutput> (move (phoneticSylOutput));
        } else {
            return make_unique<JsonOutput> (move (phoneticSylOutput));
        }
    } else {
        return make_unique<DelimOutput> (move (phoneticSylOutput), ' ');
    }
}

int
main (int argc, const char* argv[])
{
    int optCnt = 0;
    bool isJson = false;
    bool isGroup = false;
    list<unique_ptr<IOutput>> stringOutputs;

    for (int i = 1; i < argc; ++i) {
        if ('-' == argv[i][0]) {
            switch (argv[i][1]) {
            case 'j':
                isJson = true;
                break;
            case 'g':
                isJson = true;
                isGroup = true;
                break;
            case 'r':
                stringOutputs.push_back (MakeRomanOutput (isJson, isGroup));
                break;
            case 't':
                stringOutputs.push_back (MakeThaiOutput (isJson, isGroup));
                break;
            case 'p':
                stringOutputs.push_back (MakePhoneticOutput (isJson, isGroup));
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
        stringOutputs.push_back (MakeThaiOutput (isJson, isGroup));
        stringOutputs.push_back (MakeRomanOutput (isJson, isGroup));
        stringOutputs.push_back (MakePhoneticOutput (isJson, isGroup));
    }

    Parser parser;
    if (!parser.loadExceptDict (EXCEPT_DICT_PATH)) {
        cerr << "Failed to load exception dictionary " EXCEPT_DICT_PATH
             << endl;
    }

    if (1 == argc - optCnt) {
        // read word list from stdin
        string word;
        while (getline (cin, word)) {
            DoParse (parser, word, stringOutputs);
        }
    } else {
        // read word list from command line args
        for (int i = 1; i < argc; ++i) {
            if ('-' != argv[i][0]) {
                DoParse (parser, argv[i], stringOutputs);
            }
        }
    }

    return 0;
}


/*
vi:ts=4:ai:expandtab
*/
