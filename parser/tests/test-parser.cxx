#include "parser/parser.h"

#include <iostream>

using namespace std;

bool ParseAll (list<string> words)
{
    for (auto w : words) {
        cout << w << ':' << endl;
        auto sylList = ParseWord (w);
        for (const auto& s : sylList) {
            cout << " - " << s.toThai() << '\t' << s.toRoman() << endl;
        }
    }
    return true;
}

bool
TestThCons()
{
    list<string> thConsSimple = {
        u8"กง",
        u8"กัง",
        u8"กวง",
        u8"ก่อ",
        u8"ก้อน",
        u8"พร",
        u8"ค่ะ",
        u8"ข้า",
        u8"ข้าง",
        u8"ขำ",
        u8"ค่ำ",
    };

    list<string> thConsCluster = {
        u8"กรง",
        u8"คลาด",
        u8"ตราด",
        u8"ปลอบ",
        u8"ขวาน",
        u8"ควาย",
        u8"ขวิด",
        u8"สราญ",
        u8"สรวง",
        u8"จริง",
        u8"สมัน",
        u8"สมร",
    };

    list<string> thConsLinked = {
        u8"อัตรา",
        u8"มาตรา",
        u8"จักรี",
        u8"จัตุรัส",
    };

    bool isSuccess = true;

    cout << "TestThCons: Simple forms..." << endl;
    if (!ParseAll (thConsSimple)) {
        isSuccess = false;
    }
    cout << endl;

    cout << "TestThCons: With cluster as initial consonants..." << endl;
    if (!ParseAll (thConsCluster)) {
        isSuccess = false;
    }
    cout << endl;

    cout << "TestThCons: With linked syllables..." << endl;
    if (!ParseAll (thConsLinked)) {
        isSuccess = false;
    }
    cout << endl;

    return isSuccess;
}

int
main()
{
    bool isSuccess = true;

    if (!TestThCons()) {
        isSuccess = false;
    }

    return isSuccess ? 0 : 1;
}

/*
vi:ts=4:ai:expandtab
*/
