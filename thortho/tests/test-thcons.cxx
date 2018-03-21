#include "thortho/thcons.h"

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

bool
testInitConsClass()
{
    static const vector<char32_t> midCons = {
        U'\u0e01', // ก
        U'\u0e08', // จ
        U'\u0e0e', // ฎ
        U'\u0e0f', // ฏ
        U'\u0e14', // ด
        U'\u0e15', // ต
        U'\u0e1a', // บ
        U'\u0e1b', // ป
        U'\u0e2d', // อ
    };

    static const vector<char32_t> highCons = {
        U'\u0e02', // ข
        U'\u0e03', // ฃ
        U'\u0e09', // ฉ
        U'\u0e10', // ฐ
        U'\u0e16', // ถ
        U'\u0e1c', // ผ
        U'\u0e1d', // ฝ
        U'\u0e28', // ศ
        U'\u0e29', // ษ
        U'\u0e2a', // ส
        U'\u0e2b', // ห
    };

    static const vector<char32_t> singleLowCons = {
        U'\u0e07', // ง
        U'\u0e0d', // ญ
        U'\u0e13', // ณ
        U'\u0e19', // น
        U'\u0e21', // ม
        U'\u0e22', // ย
        U'\u0e23', // ร
        U'\u0e25', // ล
        U'\u0e27', // ว
    };

    static const vector<char32_t> pairedLowCons = {
        U'\u0e04', // ค
        U'\u0e05', // ฅ
        U'\u0e06', // ฆ
        U'\u0e0a', // ช
        U'\u0e0b', // ซ
        U'\u0e0c', // ฌ
        U'\u0e11', // ฑ
        U'\u0e12', // ฒ
        U'\u0e17', // ท
        U'\u0e18', // ธ
        U'\u0e1e', // พ
        U'\u0e1f', // ฟ
        U'\u0e20', // ภ
        U'\u0e2e', // ฮ
    };

    bool isSuccess = true;

    for (auto c : midCons) {
        if (EInitConsClass::MID != InitConsClass (c)) {
            cerr << "Wrong class for init const '"
                 << setw (4) << hex << static_cast<char16_t> (c)
                 << "'" << endl;
            isSuccess = false;
        }
    }

    for (auto c : highCons) {
        if (EInitConsClass::HIGH != InitConsClass (c)) {
            cerr << "Wrong class for init const '"
                 << setw (4) << hex << static_cast<char16_t> (c)
                 << "'" << endl;
            isSuccess = false;
        }
    }

    for (auto c : singleLowCons) {
        if (EInitConsClass::LOWS != InitConsClass (c)) {
            cerr << "Wrong class for init const '"
                 << setw (4) << hex << static_cast<char16_t> (c)
                 << "'" << endl;
            isSuccess = false;
        }
    }

    for (auto c : pairedLowCons) {
        if (EInitConsClass::LOWP != InitConsClass (c)) {
            cerr << "Wrong class for init const '"
                 << setw (4) << hex << static_cast<char16_t> (c)
                 << "'" << endl;
            isSuccess = false;
        }
    }

    return isSuccess;
}

bool
testEndConsClass()
{
    static const vector<char32_t> kokaCons = {
        U'\u0e2b', // ห
        U'\u0e2d', // อ
        U'\u0e2e', // ฮ
    };
    static const vector<char32_t> kokCons = {
        U'\u0e01', // ก
        U'\u0e02', // ข
        U'\u0e03', // ฃ
        U'\u0e04', // ค
        U'\u0e05', // ฅ
        U'\u0e06', // ฆ
    };

    static const vector<char32_t> kongCons = {
        U'\u0e07', // ง
    };

    static const vector<char32_t> kotCons = {
        U'\u0e08', // จ
        U'\u0e09', // ฉ
        U'\u0e0a', // ช
        U'\u0e0b', // ซ
        U'\u0e0c', // ฌ
        U'\u0e0e', // ฎ
        U'\u0e0f', // ฏ
        U'\u0e10', // ฐ
        U'\u0e11', // ฑ
        U'\u0e12', // ฒ
        U'\u0e14', // ด
        U'\u0e15', // ต
        U'\u0e16', // ถ
        U'\u0e17', // ท
        U'\u0e18', // ธ
        U'\u0e28', // ศ
        U'\u0e29', // ษ
        U'\u0e2a', // ส
    };

    static const vector<char32_t> konCons = {
        U'\u0e0d', // ญ
        U'\u0e13', // ณ
        U'\u0e19', // น
        U'\u0e23', // ร
        U'\u0e25', // ล
        U'\u0e2c', // ฬ
    };

    static const vector<char32_t> kopCons = {
        U'\u0e1a', // บ
        U'\u0e1b', // ป
        U'\u0e1c', // ผ
        U'\u0e1d', // ฝ
        U'\u0e1e', // พ
        U'\u0e1f', // ฟ
        U'\u0e20', // ภ
    };

    static const vector<char32_t> komCons = {
        U'\u0e21', // ม
    };

    static const vector<char32_t> koeyCons = {
        U'\u0e22', // ย
    };

    static const vector<char32_t> koewCons = {
        U'\u0e27', // ว
    };

    bool isSuccess = true;

    for (auto c : kokaCons) {
        if (EEndConsClass::NONE != EndConsClass (c)) {
            cerr << "Wrong class for end const '"
                 << setw (4) << hex << static_cast<char16_t> (c)
                 << "'" << endl;
            isSuccess = false;
        }
    }

    for (auto c : kokCons) {
        if (EEndConsClass::KOK != EndConsClass (c)) {
            cerr << "Wrong class for end const '"
                 << setw (4) << hex << static_cast<char16_t> (c)
                 << "'" << endl;
            isSuccess = false;
        }
    }

    for (auto c : kongCons) {
        if (EEndConsClass::KONG != EndConsClass (c)) {
            cerr << "Wrong class for end const '"
                 << setw (4) << hex << static_cast<char16_t> (c)
                 << "'" << endl;
            isSuccess = false;
        }
    }

    for (auto c : kotCons) {
        if (EEndConsClass::KOT != EndConsClass (c)) {
            cerr << "Wrong class for end const '"
                 << setw (4) << hex << static_cast<char16_t> (c)
                 << "'" << endl;
            isSuccess = false;
        }
    }

    for (auto c : konCons) {
        if (EEndConsClass::KON != EndConsClass (c)) {
            cerr << "Wrong class for end const '"
                 << setw (4) << hex << static_cast<char16_t> (c)
                 << "'" << endl;
            isSuccess = false;
        }
    }

    for (auto c : kopCons) {
        if (EEndConsClass::KOP != EndConsClass (c)) {
            cerr << "Wrong class for end const '"
                 << setw (4) << hex << static_cast<char16_t> (c)
                 << "'" << endl;
            isSuccess = false;
        }
    }

    for (auto c : komCons) {
        if (EEndConsClass::KOM != EndConsClass (c)) {
            cerr << "Wrong class for end const '"
                 << setw (4) << hex << static_cast<char16_t> (c)
                 << "'" << endl;
            isSuccess = false;
        }
    }

    for (auto c : koeyCons) {
        if (EEndConsClass::KOEY != EndConsClass (c)) {
            cerr << "Wrong class for end const '"
                 << setw (4) << hex << static_cast<char16_t> (c)
                 << "'" << endl;
            isSuccess = false;
        }
    }

    for (auto c : koewCons) {
        if (EEndConsClass::KOEW != EndConsClass (c)) {
            cerr << "Wrong class for end const '"
                 << setw (4) << hex << static_cast<char16_t> (c)
                 << "'" << endl;
            isSuccess = false;
        }
    }

    return isSuccess;
}

int
main()
{
    cout << "Testing InitConsClass() ... ";
    if (testInitConsClass()) {
        cout << "[OK]" << endl;
    } else {
        cout << "[FAIL]" << endl;
    }

    cout << "Testing EndConsClass() ... ";
    if (testEndConsClass()) {
        cout << "[OK]" << endl;
    } else {
        cout << "[FAIL]" << endl;
    }

    return 0;
}

/*
vi:ts=4:ai:expandtab
*/
