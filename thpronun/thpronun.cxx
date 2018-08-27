#include "parser/parser.h"
#include "output/sylout-thai.h"
#include "output/sylout-roman.h"
#include "output/sylout-phonetic.h"
#include "output/sylout-raw.h"
#include "output/sylout-soundex.h"
#include "output/output-delim.h"
#include "output/output-roman.h"
#include "output/output-json.h"
#include "output/output-gjson.h"

#include <iostream>
#include <list>
#include <memory>
#include <cstring>

#define EXCEPT_DICT_NAME "except.dic"
#define EXCEPT_DICT_PATH EXCEPT_DICT_DIR "/" EXCEPT_DICT_NAME

using namespace std;

void
DoParse (const Parser& parser, string word,
         const list<unique_ptr<IOutput>>& stringOutputs)
{
    cout << word << ":" << endl;
    auto pronDAG = parser.parseWord (word);
    for (const auto& strOut : stringOutputs) {
        cout << strOut->output (pronDAG) << endl;;
    }
}

void
Version (const char* progName)
{
    cout << progName << " " VERSION << endl
         << endl
         << "Copyright (C) 2018 Theppitak Karoonboonyanan <theppitak@gmail.com>"
            << endl
         << "License GPLv3+: GNU GPL version 3 or later "
             "<http://gnu.org/licenses/gpl.html>." << endl
         << "This is free software: you are free to change and redistribute it."
            << endl
         << "There is NO WARRANTY, to the extent permitted by law."
            << endl
         << endl
         << "Written by Theppitak Karoonboonyanan, under the sponsorship"
            << endl
         << "of Metamedia Technology Co., Ltd." << endl;
}

void
Usage (const char* progName)
{
    cout << "Usage: " << progName << " [OPTION] [WORD...]" << endl
         << endl
         << "Thai word pronunciation program." << endl
         << endl
         << "It reads Thai words from command-line arguments, "
            "or from standard input" << endl
         << "if no argument is given, and generates all possible "
            "pronunciations" << endl
         << "of the words." << endl
         << endl
         << "Options:" << endl
         << endl
         << "General:" << endl
         << "  -V, --version  Displays program version info" << endl
         << "  -h, --help     Displays help" << endl
         << "  -d<DICTPATH>   Use exception dict from <DICTPATH>" << endl
         << "  -n             Turns off word segmentation" << endl
         << endl
         << "Output structures:" << endl
         << "  -j             Turns on JSON output" << endl
         << "  -g             Turns on grouping in JSON output (implies '-j')"
            << endl
         << endl
         << "Output notations:" << endl
         << "  -r             Outputs Romanization" << endl
         << "  -t             Outputs Thai pronunciation" << endl
         << "  -p             Outputs Phonetic form" << endl
         << "  -w             Outputs Raw pronunciation code" << endl
         << "  -s             Outputs Soundex code" << endl
         << endl;
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

static unique_ptr<IOutput>
MakeRawOutput (bool isJson, bool isGroup)
{
    auto rawSylOutput = make_unique<RawSylOutput>();

    if (isJson) {
        if (isGroup) {
            return make_unique<GroupedJsonOutput> (move (rawSylOutput));
        } else {
            return make_unique<JsonOutput> (move (rawSylOutput));
        }
    } else {
        return make_unique<DelimOutput> (move (rawSylOutput), ',');
    }
}

static unique_ptr<IOutput>
MakeSoundexOutput (bool isJson, bool isGroup)
{
    auto soundexSylOutput = make_unique<SoundexSylOutput>();

    if (isJson) {
        if (isGroup) {
            return make_unique<GroupedJsonOutput> (move (soundexSylOutput));
        } else {
            return make_unique<JsonOutput> (move (soundexSylOutput));
        }
    } else {
        return make_unique<DelimOutput> (move (soundexSylOutput), '-');
    }
}

static bool
LoadExceptDict (Parser& parser, const char* dictPath)
{
    if (dictPath) {
        if (parser.loadExceptDict (dictPath))
            return true;
        cerr << "Failed to load exception dictionary '" << dictPath << "'"
             << endl;
        return false;
    }

    if (parser.loadExceptDict (EXCEPT_DICT_PATH))
        return true;
    cerr << "Failed to load exception dictionary " EXCEPT_DICT_PATH
         << endl;

    return false;
}

int
main (int argc, const char* argv[])
{
    int optCnt = 0;
    const char* dictPath = nullptr;
    bool isBreakWords = true;
    bool isJson = false;
    bool isGroup = false;
    list<unique_ptr<IOutput>> stringOutputs;

    // first pass: general options
    for (int i = 1; i < argc; ++i) {
        if ('-' == argv[i][0]) {
            switch (argv[i][1]) {
            case '-':
                if (strcmp (argv[i]+2, "version") == 0) {
                    Version (argv[0]);
                    return 1;
                } else if (strcmp (argv[1]+2, "help") == 0) {
                    Usage (argv[0]);
                    return 1;
                } else {
                    cerr << "Unknown option '" << argv[i] << "'" << endl;
                    return 1;
                }
                break;
            case 'V':
                Version (argv[0]);
                return 1;
            case 'h':
                Usage (argv[0]);
                return 1;
            case 'd':
                if (!argv[i][2]) {
                    cerr << "Missing <dict-path> argument for -d" << endl;
                    return 1;
                }
                dictPath = argv[i] + 2;
                break;
            case 'n':
                isBreakWords = false;
                break;
            case 'j':
                isJson = true;
                break;
            case 'g':
                isJson = true;
                isGroup = true;
                break;
            case 'r':
            case 's':
            case 't':
            case 'p':
            case 'w':
                // do nothing in first pass
                break;
            default:
                cerr << "Unknown option '-" << argv[i][1] << "'" << endl;
                Usage (argv[0]);
                return 1;
            }
            ++optCnt;
        }
    }
    // second pass: output modules
    for (int i = 1; i < argc; ++i) {
        if ('-' == argv[i][0]) {
            switch (argv[i][1]) {
            case 'r':
                stringOutputs.push_back (MakeRomanOutput (isJson, isGroup));
                break;
            case 's':
                stringOutputs.push_back (MakeSoundexOutput (isJson, isGroup));
                break;
            case 't':
                stringOutputs.push_back (MakeThaiOutput (isJson, isGroup));
                break;
            case 'p':
                stringOutputs.push_back (MakePhoneticOutput (isJson, isGroup));
                break;
            case 'w':
                stringOutputs.push_back (MakeRawOutput (isJson, isGroup));
                break;
            default:
                break;
            }
        }
    }
    if (stringOutputs.empty()) {
        stringOutputs.push_back (MakeThaiOutput (isJson, isGroup));
        stringOutputs.push_back (MakeRomanOutput (isJson, isGroup));
        stringOutputs.push_back (MakePhoneticOutput (isJson, isGroup));
    }

    Parser parser (isBreakWords);
    if (!LoadExceptDict (parser, dictPath)) {
        cerr << "Warning: Working without exception dictionary" << endl;
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
