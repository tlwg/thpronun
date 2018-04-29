#include "parser/parser.h"

#include <iostream>

using namespace std;

void
DoParse (string word, bool outThai, bool outRoman, bool outPhonetic)
{
    cout << word << ":" << endl;
    auto sylList = ParseWord (word);
    for (const auto& s : sylList) {
        if (outThai) {
            cout << s.toThai();
            if (outRoman) {
                cout << '\t' << s.toRoman();
            }
            if (outPhonetic) {
                cout << '\t' << s.toPhonetic();
            }
            cout << endl;
        } else if (outRoman) {
            cout << s.toRoman();
            if (outPhonetic) {
                cout << '\t' << s.toPhonetic();
            }
            cout << endl;
        } else if (outPhonetic) {
            cout << s.toPhonetic();
            cout << endl;
        }
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
    bool outThai = false;
    bool outRoman = false;
    bool outPhonetic = false;

    for (int i = 1; i < argc; ++i) {
        if ('-' == argv[i][0]) {
            switch (argv[i][1]) {
            case 'r':
                outRoman = true;
                break;
            case 't':
                outThai = true;
                break;
            case 'p':
                outPhonetic = true;
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
    if (!outThai && !outRoman && !outPhonetic) {
        outThai = outRoman = outPhonetic = true;
    }

    if (1 == argc - optCnt) {
        // read word list from stdin
        string word;
        while (getline (cin, word)) {
            DoParse (word, outThai, outRoman, outPhonetic);
        }
    } else {
        // read word list from command line args
        for (int i = 1; i < argc; ++i) {
            if ('-' != argv[i][0]) {
                DoParse (argv[i], outThai, outRoman, outPhonetic);
            }
        }
    }

    return 0;
}


/*
vi:ts=4:ai:expandtab
*/
