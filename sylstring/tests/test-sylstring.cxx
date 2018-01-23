#include "sylstring/sylstring.h"

#include <iostream>

using namespace std;

bool
TestThaiPronun()
{
    bool isSuccess = true;
    SylString syls;

    // กกต้นหูกฺวางเหฺลียวเลาะร้องเป็นตาแซ่บ
    syls = Syl ('k', '_', 'o', 'k', '1');

    auto thaiPronun = syls.toThai();
    if (thaiPronun != u8"กก") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ('t', '_', 'o', 'n', '2');
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"กก-ต้น") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ('h', '_', 'U', '_', '4');
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"กก-ต้น-หู") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ('k', 'w', 'A', 'g', '0');
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ('l', '_', 'Y', 'w', '4');
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง-เหฺลียว") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ('l', '_', 'c', '_', '3');
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง-เหฺลียว-เลาะ") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ('r', '_', 'C', 'g', '3');
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง-เหฺลียว-เลาะ-ร้อง") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ('p', '_', 'e', 'n', '0');
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง-เหฺลียว-เลาะ-ร้อง-เป็น") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ('t', '_', 'A', '_', '0');
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง-เหฺลียว-เลาะ-ร้อง-เป็น-ตา") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ('s', '_', 'x', 'p', '2');
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง-เหฺลียว-เลาะ-ร้อง-เป็น-ตา-แซ่บ") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // ละลันหลั่นล้า
    syls = Syl ('l', '_', 'a', '_', '3');
    syls += Syl ('l', '_', 'a', 'n', '0');
    syls += Syl ('l', '_', 'a', 'n', '1');
    syls += Syl ('l', '_', 'A', '_', '3');
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"ละ-ลัน-หฺลั่น-ล้า") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // ใครใคร่ขายไข่ไก่คราคร่ำไม้ไหมเล่า
    syls = Syl ('c', 'r', 'a', 'y', '0');
    syls += Syl ('c', 'r', 'a', 'y', '2');
    syls += Syl ('c', '_', 'A', 'y', '4');
    syls += Syl ('c', '_', 'a', 'y', '1');
    syls += Syl ('k', '_', 'a', 'y', '1');
    syls += Syl ('c', 'r', 'A', '_', '0');
    syls += Syl ('c', 'r', 'a', 'm', '2');
    syls += Syl ('m', '_', 'A', 'y', '3');
    syls += Syl ('m', '_', 'a', 'y', '4');
    syls += Syl ('l', '_', 'a', 'w', '2');
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"คฺรัย-คฺรั่ย-ขาย-ขั่ย-กั่ย-คฺรา-คฺรั่ม-ม้าย-หฺมัย-เล่า") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // แมวและเด็กเหล่เล่นเจอะเจอเกลือเดินเกลือกคั่วกลิ้งร่วมโรงเรียน
    syls = Syl ('m', '_', 'X', 'w', '0');
    syls += Syl ('l', '_', 'x', '_', '3');
    syls += Syl ('d', '_', 'e', 'k', '1');
    syls += Syl ('l', '_', 'E', '_', '1');
    syls += Syl ('l', '_', 'e', 'n', '2');
    syls += Syl ('j', '_', 'w', '_', '1');
    syls += Syl ('j', '_', 'W', '_', '0');
    syls += Syl ('k', 'l', 'Z', '_', '0');
    syls += Syl ('d', '_', 'W', 'n', '0');
    syls += Syl ('k', 'l', 'Z', 'k', '1');
    syls += Syl ('c', '_', 'T', '_', '2');
    syls += Syl ('k', 'l', 'i', 'g', '2');
    syls += Syl ('r', '_', 'T', 'm', '2');
    syls += Syl ('r', '_', 'O', 'g', '0');
    syls += Syl ('r', '_', 'Y', 'n', '0');
    thaiPronun = syls.toThai();
    if (thaiPronun !=
        u8"แมว-และ-เด็ก-เหฺล่-เล่น-เจอะ-เจอ-เกฺลือ-เดิน-เกฺลือก-คั่ว-กฺลิ้ง-ร่วม-โรง-เรียน")
    {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
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

    return isSuccess ? 0 : 1;
}

/*
vi:ts=4:ai:expandtab
*/
