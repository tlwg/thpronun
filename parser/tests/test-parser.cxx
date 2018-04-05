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

bool
TestSaraE()
{
    list<string> saraE = {
        u8"เก",
        u8"เท่",
        u8"เพล",
        u8"เก่ง",
        u8"เตะ",
        u8"เป๊ะ",
        u8"เสเพล",
        u8"เหล่",
        u8"เกว๋",
        u8"เชวง",
        u8"เป็น",
    };

    list<string> saraOE = {
        u8"เธอ",
        u8"เสนอ",
        u8"เลอะ",
        u8"เปรอะ",
        u8"เกิด",
        u8"เปิ่น",
        u8"เพลิน",
        u8"เคลิ้ม",
        u8"เสริม",
        u8"เลย",
        u8"เม้ย",
        u8"เหมย",
        u8"เชลย",
    };

    list<string> saraIA = {
        u8"เซียะ",
        u8"เปี๊ยะ",
        u8"เปรี๊ยะ",
        u8"เสีย",
        u8"เพลีย",
        u8"เสียด",
        u8"เพี้ยน",
        u8"เสนียด",
    };

    list<string> saraUEA = {
        u8"ละเวือะ",
        u8"เกื๊อะ",
        u8"เกือบ",
        u8"เลื่อน",
        u8"เกลือ",
        u8"เกลือก",
        u8"เสมือน",
        u8"เหมือน",
    };

    list<string> saraAW = {
        u8"เกา",
        u8"เกลา",
        u8"เสลา",
        u8"เหมา",
    };

    list<string> saraAU = {
        u8"เกาะ",
        u8"เพลาะ",
        u8"เสนาะ",
        u8"เหมาะ",
    };

    bool isSuccess = true;

    cout << "TestSareE: Sara E..." << endl;
    if (!ParseAll (saraE)) {
        isSuccess = false;
    }
    cout << endl;

    cout << "TestThCons: Sara OE..." << endl;
    if (!ParseAll (saraOE)) {
        isSuccess = false;
    }
    cout << endl;

    cout << "TestThCons: Sara IA..." << endl;
    if (!ParseAll (saraIA)) {
        isSuccess = false;
    }
    cout << endl;

    cout << "TestThCons: Sara UEA..." << endl;
    if (!ParseAll (saraUEA)) {
        isSuccess = false;
    }
    cout << endl;

    cout << "TestThCons: Sara AW..." << endl;
    if (!ParseAll (saraAW)) {
        isSuccess = false;
    }
    cout << endl;

    cout << "TestThCons: Sara AU..." << endl;
    if (!ParseAll (saraAU)) {
        isSuccess = false;
    }
    cout << endl;

    return isSuccess;
}

bool
TestOtherLV()
{
    list<string> saraAE = {
        u8"แก",
        u8"แก่",
        u8"แกล",
        u8"แก้ม",
        u8"แตะ",
        u8"แป๊ะ",
        u8"แหล่",
        u8"แกว่ง",
        u8"แพลง",
        u8"แสลง",
        u8"แข็ง",
    };

    list<string> saraO = {
        u8"โต",
        u8"โอ่",
        u8"โละ",
        u8"โป๊ะ",
        u8"โพละ",
        u8"โกน",
        u8"โล้น",
        u8"โกลน",
        u8"โขดง",
    };

    list<string> saraAI = {
        u8"ใจ",
        u8"ใช้",
        u8"ใคร",
        u8"ใคร่",
        u8"ไก",
        u8"ไล่",
        u8"ไพล่",
        u8"ไฉน",
    };

    bool isSuccess = true;

    cout << "TestSareE: Sara AE..." << endl;
    if (!ParseAll (saraAE)) {
        isSuccess = false;
    }
    cout << endl;

    cout << "TestThCons: Sara O..." << endl;
    if (!ParseAll (saraO)) {
        isSuccess = false;
    }
    cout << endl;

    cout << "TestThCons: Sara AI..." << endl;
    if (!ParseAll (saraAI)) {
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

    if (!TestSaraE()) {
        isSuccess = false;
    }

    if (!TestOtherLV()) {
        isSuccess = false;
    }

    return isSuccess ? 0 : 1;
}

/*
vi:ts=4:ai:expandtab
*/
