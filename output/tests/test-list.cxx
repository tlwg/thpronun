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

using namespace std;

list<SylString>
PrepareList()
{
    list<SylString> strList;

    SylString sylStr;

    // เพ-ลา
    sylStr = Syl ("P_E_0", 2);
    sylStr += Syl ("l_A_0", 4);
    strList.push_back (sylStr);

    // เพฺลา
    sylStr = Syl ("Plaw0", 4);
    strList.push_back (sylStr);

    // พะ-เลา
    sylStr = Syl ("P_a_3", -4);
    sylStr += Syl ("l_aw0", 4);
    strList.push_back (sylStr);

    return strList;
}

bool
TestThaiPronun()
{
    bool isSuccess = true;

    auto output
        = make_unique<DelimOutput> (make_unique<ThaiSylOutput>(), '-');

    auto strList = PrepareList();

    cout << "Testing Thai output" << endl;
    string result = output->output (strList);
    if (result == "เพ-ลา\nเพฺลา\nพะ-เลา\n") {
        cout << "OK" << endl;
    } else {
        cout << "Got unexpected result:'" << result << "'" << endl;
        isSuccess = false;
    }

    return isSuccess;
}

bool
TestRomanPronun()
{
    bool isSuccess = true;

    auto output    = make_unique<RomanOutput>();
    auto outputCap = make_unique<RomanOutput> (true);

    auto strList = PrepareList();

    cout << "Testing Romanization output" << endl;
    string result = output->output (strList);
    if (result == "phela\nphlao\nphalao\n") {
        cout << "OK" << endl;
    } else {
        cout << "Got unexpected result:'" << result << "'" << endl;
        isSuccess = false;
    }

    cout << "Testing capitalized Romanization output" << endl;
    result = outputCap->output (strList);
    if (result == "Phela\nPhlao\nPhalao\n") {
        cout << "OK" << endl;
    } else {
        cout << "Got unexpected result:'" << result << "'" << endl;
        isSuccess = false;
    }

    return isSuccess;
}

bool
TestJson()
{
    bool isSuccess = true;
    SylString syls;
    auto output
        = make_unique<JsonOutput> (make_unique<ThaiSylOutput>());

    auto strList = PrepareList();

    cout << "Testing JSON output" << endl;
    string result = output->output (strList);
    if (result == "[[\"เพ\",\"ลา\"],[\"เพฺลา\"],[\"พะ\",\"เลา\"]]") {
        cout << "OK" << endl;
    } else {
        cout << "Got unexpected result:'" << result << "'" << endl;
        isSuccess = false;
    }

    return isSuccess;
}

bool
TestGroupedJson()
{
    bool isSuccess = true;
    SylString syls;
    auto output
        = make_unique<GroupedJsonOutput> (make_unique<ThaiSylOutput>());

    auto strList = PrepareList();

    cout << "Testing Grouped JSON output" << endl;
    string result = output->output (strList);
    static const string expected =
        "["
            "["
                "["
                    "[\"เพ\",\"ลา\"],"
                    "[\"พะ\",\"เลา\"],"
                    "[\"เพฺลา\"]"
                "]"
            "]"
        "]";
    if (result == expected) {
        cout << "OK" << endl;
    } else {
        cout << "Got unexpected result:'" << result << "'" << endl;
        isSuccess = false;
    }

    return isSuccess;
}

int
main()
{
    bool isSuccess = true;

    if (!TestThaiPronun()) {
        isSuccess = false;
    }

    if (!TestRomanPronun()) {
        isSuccess = false;
    }

    if (!TestJson()) {
        isSuccess = false;
    }

    if (!TestGroupedJson()) {
        isSuccess = false;
    }

    return isSuccess ? 0 : 1;
}

/*
vi:ts=4:ai:expandtab
*/
