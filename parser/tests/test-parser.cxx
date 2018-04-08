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
        u8"หงส์",
        u8"กวง",
        u8"ก่อ",
        u8"ก้อน",
        u8"ฟอร์ม",
        u8"พร",
        u8"ภรณ์",
        u8"สรร",
        u8"ธรรม",
        u8"สวรรค์",
        u8"ค่ะ",
        u8"ค่ะส์",
        u8"วัน",
        u8"จันทร์",
        u8"ทันต์",
        u8"มั่ว",
        u8"ชัวร์",
        u8"ผัวะ",
        u8"จั๊วะ",
        u8"ข้า",
        u8"พาร์",
        u8"ข้าง",
        u8"ฟาร์ม",
        u8"ศาสตร์",
        u8"ขำ",
        u8"ค่ำ",
        u8"ขำส์",
        u8"สิ",
        u8"ซิ่น",
        u8"ฟิล์ม",
        u8"ที่",
        u8"พีร์",
        u8"อึ",
        u8"ขึ้น",
        u8"ซื่อ",
        u8"ขืน",
        u8"ผื่น",
        u8"ดุ",
        u8"คุก",
        u8"ดู",
        u8"ปู้ด",
    };

    list<string> thConsCluster = {
        u8"กรง",
        u8"กรงส์",
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
        u8"เล่ห์",
        u8"เตะ",
        u8"เป๊ะ",
        u8"เละส์",
        u8"เสเพล",
        u8"เหล่",
        u8"เกว๋",
        u8"เชวง",
        u8"เป็น",
    };

    list<string> saraOE = {
        u8"เธอ",
        u8"เสนอ",
        u8"เปอร์เซ็นต์",
        u8"เลอะ",
        u8"เปรอะ",
        u8"เกิด",
        u8"เกิร์ต",
        u8"เปิ่น",
        u8"เพลิน",
        u8"เคลิ้ม",
        u8"เสริม",
        u8"เลย",
        u8"เม้ย",
        u8"เหมย",
        u8"เชลย",
        u8"เบรยล์",
    };

    list<string> saraIA = {
        u8"เซียะ",
        u8"เปี๊ยะ",
        u8"เปรี๊ยะ",
        u8"เกี๊ยะส์",
        u8"เสีย",
        u8"เชียร์",
        u8"เพลีย",
        u8"เสียด",
        u8"เพี้ยน",
        u8"เสนียด",
        u8"เฟียร์ตส์",
    };

    list<string> saraUEA = {
        u8"ละเวือะ",
        u8"เกื๊อะ",
        u8"เคือะส์",
        u8"เกือบ",
        u8"เลื่อน",
        u8"เกลือ",
        u8"เกลือก",
        u8"เสมือน",
        u8"เหมือน",
        u8"เวือร์ต",
    };

    list<string> saraAW = {
        u8"เกา",
        u8"เกลา",
        u8"เสลา",
        u8"เหมา",
        u8"เสาร์",
    };

    list<string> saraAU = {
        u8"เกาะ",
        u8"เพลาะ",
        u8"เสนาะ",
        u8"เหมาะ",
        u8"เคราะห์",
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
        u8"แชร์",
        u8"แฟร์มาต์",
        u8"แกล",
        u8"แก้ม",
        u8"แพทย์",
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
        u8"โฟร์",
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
        u8"ไดร์",
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

bool
TestRu()
{
    list<string> ru = {
        u8"อังกฤษ",
        u8"ตฤณ",
        u8"ทฤษฎี",
        u8"ปฤจฉา",
        u8"สฤษดิ์",
        u8"ศฤงคาร",
        u8"คฤนถ์",
        u8"คฤหัสถ์",
        u8"นฤพาน",
        u8"นฤมิต",
        u8"พฤกษ์",
        u8"พฤฒาจารย์",
        u8"พฤหัส",
        u8"มฤค",
        u8"หฤทัย",
        u8"หฤหรรษ์",
    };

    bool isSuccess = true;

    cout << "TestRu: Words containg RU..." << endl;
    if (!ParseAll (ru)) {
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

    if (!TestRu()) {
        isSuccess = false;
    }

    return isSuccess ? 0 : 1;
}

/*
vi:ts=4:ai:expandtab
*/
