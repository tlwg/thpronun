#include "thortho/thcons.h"
#include "thortho/thuni.h"

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
testInitConsSound()
{
    static const vector<pair<EInitConsSound, vector<int>>> soundICons = {
        {
            EInitConsSound::KA, {
                UTH_KO_KAI,
            }
        },
        {
            EInitConsSound::KHA, {
                UTH_KHO_KHAI,
                UTH_KHO_KHUAT,
                UTH_KHO_KHWAI,
                UTH_KHO_KHON,
                UTH_KHO_RAKHANG,
            }
        },
        {
            EInitConsSound::NGA, {
                UTH_NGO_NGU,
            }
        },
        {
            EInitConsSound::JA, {
                UTH_CHO_CHAN,
            }
        },
        {
            EInitConsSound::CHA, {
                UTH_CHO_CHING,
                UTH_CHO_CHANG,
                UTH_CHO_CHOE,
            }
        },
        {
            EInitConsSound::YA, {
                UTH_YO_YING,
                UTH_YO_YAK,
            }
        },
        {
            EInitConsSound::DA, {
                UTH_DO_CHADA,
                UTH_DO_DEK,
            }
        },
        {
            EInitConsSound::TA, {
                UTH_TO_PATAK,
                UTH_TO_TAO,
            }
        },
        {
            EInitConsSound::THA, {
                UTH_THO_THAN,
                UTH_THO_NANGMONTHO,
                UTH_THO_PHUTHAO,
                UTH_THO_THUNG,
                UTH_THO_THAHAN,
                UTH_THO_THONG,
            }
        },
        {
            EInitConsSound::NA, {
                UTH_NO_NEN,
                UTH_NO_NU,
            }
        },
        {
            EInitConsSound::BA, {
                UTH_BO_BAIMAI,
            }
        },
        {
            EInitConsSound::PA, {
                UTH_PO_PLA,
            }
        },
        {
            EInitConsSound::PHA, {
                UTH_PHO_PHUNG,
                UTH_PHO_PHAN,
                UTH_PHO_SAMPHAO,
            }
        },
        {
            EInitConsSound::FA, {
                UTH_FO_FA,
                UTH_FO_FAN,
            }
        },
        {
            EInitConsSound::MA, {
                UTH_MO_MA,
            }
        },
        {
            EInitConsSound::RA, {
                UTH_RO_RUA,
            }
        },
        {
            EInitConsSound::LA, {
                UTH_LO_LING,
                UTH_LO_CHULA,
            }
        },
        {
            EInitConsSound::WA, {
                UTH_WO_WAEN,
            }
        },
        {
            EInitConsSound::SA, {
                UTH_SO_SO,
                UTH_SO_SALA,
                UTH_SO_RUSI,
                UTH_SO_SUA,
            }
        },
        {
            EInitConsSound::HA, {
                UTH_HO_HIP,
                UTH_HO_NOKHUK,
            }
        },
        {
            EInitConsSound::A, {
                UTH_O_ANG,
            }
        },
    };

    bool isSuccess = true;

    for (auto v : soundICons) {
        for (auto c : v.second) {
            auto s = InitConsSound (c);
            if (s != v.first) {
                cerr << "Wrong init consonant sound for '" << c << "'. "
                     << "Expected " << static_cast<int> (v.first)
                     << " but got " << static_cast<int> (s)
                     << endl;
                isSuccess = false;
            }
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

bool
testToneFromWritten()
{
    struct ToneTblEntry {
        EInitConsClass  iConsClass;
        ETone           writtenTone;
        bool            isDeadEnd;
        bool            isShortVowel;
        ETone           pronTone;
    };
#define ICC EInitConsClass
    static const vector<ToneTblEntry> ToneTbl_ = {
        // iCons,    writtenTone,     isDead, isShort, pronTone
        { ICC::MID,  ETone::SAMAN,    false,  false, ETone::SAMAN    }, // กาน
        { ICC::MID,  ETone::SAMAN,    false,  true,  ETone::SAMAN    }, // กัน
        { ICC::MID,  ETone::SAMAN,    true,   false, ETone::EK       }, // กาด
        { ICC::MID,  ETone::SAMAN,    true,   true,  ETone::EK       }, // กัด
        { ICC::MID,  ETone::EK,       false,  false, ETone::EK       }, // ก่าน
        { ICC::MID,  ETone::EK,       false,  true,  ETone::EK       }, // กั่น
        { ICC::MID,  ETone::EK,       true,   false, ETone::EK       }, // ก่าด*
        { ICC::MID,  ETone::EK,       true,   true,  ETone::EK       }, // กั่ด*
        { ICC::MID,  ETone::THO,      false,  false, ETone::THO      }, // ก้าน
        { ICC::MID,  ETone::THO,      false,  true,  ETone::THO      }, // กั้น
        { ICC::MID,  ETone::THO,      true,   false, ETone::THO      }, // ก้าด
        { ICC::MID,  ETone::THO,      true,   true,  ETone::THO      }, // กั้ด
        { ICC::MID,  ETone::TRI,      false,  false, ETone::TRI      }, // ก๊าน
        { ICC::MID,  ETone::TRI,      false,  true,  ETone::TRI      }, // กั๊น
        { ICC::MID,  ETone::TRI,      true,   false, ETone::TRI      }, // ก๊าด
        { ICC::MID,  ETone::TRI,      true,   true,  ETone::TRI      }, // กั๊ด
        { ICC::MID,  ETone::CHATTAWA, false,  false, ETone::CHATTAWA }, // ก๋าน
        { ICC::MID,  ETone::CHATTAWA, false,  true,  ETone::CHATTAWA }, // กั๋น
        { ICC::MID,  ETone::CHATTAWA, true,   false, ETone::CHATTAWA }, // ก๋าด
        { ICC::MID,  ETone::CHATTAWA, true,   true,  ETone::CHATTAWA }, // กั๋ด

        { ICC::HIGH, ETone::SAMAN,    false,  false, ETone::CHATTAWA }, // ขาน
        { ICC::HIGH, ETone::SAMAN,    false,  true,  ETone::CHATTAWA }, // ขัน
        { ICC::HIGH, ETone::SAMAN,    true,   false, ETone::EK       }, // ขาด
        { ICC::HIGH, ETone::SAMAN,    true,   true,  ETone::EK       }, // ขัด
        { ICC::HIGH, ETone::EK,       false,  false, ETone::EK       }, // ข่าน
        { ICC::HIGH, ETone::EK,       false,  true,  ETone::EK       }, // ขั่น
        { ICC::HIGH, ETone::EK,       true,   false, ETone::EK       }, // ข่าด*
        { ICC::HIGH, ETone::EK,       true,   true,  ETone::EK       }, // ขั่ด*
        { ICC::HIGH, ETone::THO,      false,  false, ETone::THO      }, // ข้าน
        { ICC::HIGH, ETone::THO,      false,  true,  ETone::THO      }, // ขั้น
        { ICC::HIGH, ETone::THO,      true,   false, ETone::THO      }, // ข้าด
        { ICC::HIGH, ETone::THO,      true,   true,  ETone::THO      }, // ขั้ด
        { ICC::HIGH, ETone::TRI,      false,  false, ETone::TRI      }, // ข๊าน*
        { ICC::HIGH, ETone::TRI,      false,  true,  ETone::TRI      }, // ขั๊น*
        { ICC::HIGH, ETone::TRI,      true,   false, ETone::TRI      }, // ข๊าด*
        { ICC::HIGH, ETone::TRI,      true,   true,  ETone::TRI      }, // ขั๊ด*
        { ICC::HIGH, ETone::CHATTAWA, false,  false, ETone::CHATTAWA }, // ข๋าน*
        { ICC::HIGH, ETone::CHATTAWA, false,  true,  ETone::CHATTAWA }, // ขั๋น*
        { ICC::HIGH, ETone::CHATTAWA, true,   false, ETone::CHATTAWA }, // ข๋าด*
        { ICC::HIGH, ETone::CHATTAWA, true,   true,  ETone::CHATTAWA }, // ชั๊ด*

        { ICC::LOWP, ETone::SAMAN,    false,  false, ETone::SAMAN    }, // คาน
        { ICC::LOWP, ETone::SAMAN,    false,  true,  ETone::SAMAN    }, // คัน
        { ICC::LOWP, ETone::SAMAN,    true,   false, ETone::THO      }, // คาด
        { ICC::LOWP, ETone::SAMAN,    true,   true,  ETone::TRI      }, // คัด
        { ICC::LOWP, ETone::EK,       false,  false, ETone::THO      }, // ค่าน
        { ICC::LOWP, ETone::EK,       false,  true,  ETone::THO      }, // คั่น
        { ICC::LOWP, ETone::EK,       true,   false, ETone::THO      }, // ค่าด*
        { ICC::LOWP, ETone::EK,       true,   true,  ETone::THO      }, // คั่ด
        { ICC::LOWP, ETone::THO,      false,  false, ETone::TRI      }, // ค้าน
        { ICC::LOWP, ETone::THO,      false,  true,  ETone::TRI      }, // คั้น
        { ICC::LOWP, ETone::THO,      true,   false, ETone::TRI      }, // ค้าด
        { ICC::LOWP, ETone::THO,      true,   true,  ETone::TRI      }, // คั้ด*
        { ICC::LOWP, ETone::TRI,      false,  false, ETone::TRI      }, // ค๊าน*
        { ICC::LOWP, ETone::TRI,      false,  true,  ETone::TRI      }, // คั๊น*
        { ICC::LOWP, ETone::TRI,      true,   false, ETone::TRI      }, // ค๊าด*
        { ICC::LOWP, ETone::TRI,      true,   true,  ETone::TRI      }, // คั๊ด*
        { ICC::LOWP, ETone::CHATTAWA, false,  false, ETone::CHATTAWA }, // ค๋าน*
        { ICC::LOWP, ETone::CHATTAWA, false,  true,  ETone::CHATTAWA }, // คั๋น*
        { ICC::LOWP, ETone::CHATTAWA, true,   false, ETone::CHATTAWA }, // ค๋าด
        { ICC::LOWP, ETone::CHATTAWA, true,   true,  ETone::CHATTAWA }, // คั๋ด

        { ICC::LOWS, ETone::SAMAN,    false,  false, ETone::SAMAN    }, // งาน
        { ICC::LOWS, ETone::SAMAN,    false,  false, ETone::SAMAN    }, // งาน
        { ICC::LOWS, ETone::SAMAN,    false,  true,  ETone::SAMAN    }, // งัน
        { ICC::LOWS, ETone::SAMAN,    true,   false, ETone::THO      }, // งาด
        { ICC::LOWS, ETone::SAMAN,    true,   true,  ETone::TRI      }, // งัด
        { ICC::LOWS, ETone::EK,       false,  false, ETone::THO      }, // ง่าน
        { ICC::LOWS, ETone::EK,       false,  true,  ETone::THO      }, // งั่น
        { ICC::LOWS, ETone::EK,       true,   false, ETone::THO      }, // ง่าด*
        { ICC::LOWS, ETone::EK,       true,   true,  ETone::THO      }, // งั่ด
        { ICC::LOWS, ETone::THO,      false,  false, ETone::TRI      }, // ง้าน
        { ICC::LOWS, ETone::THO,      false,  true,  ETone::TRI      }, // งั้น
        { ICC::LOWS, ETone::THO,      true,   false, ETone::TRI      }, // ง้าด
        { ICC::LOWS, ETone::THO,      true,   true,  ETone::TRI      }, // งั้ด*
        { ICC::LOWS, ETone::TRI,      false,  false, ETone::TRI      }, // ง๊าน*
        { ICC::LOWS, ETone::TRI,      false,  true,  ETone::TRI      }, // งั๊น*
        { ICC::LOWS, ETone::TRI,      true,   false, ETone::TRI      }, // ง๊าด*
        { ICC::LOWS, ETone::TRI,      true,   true,  ETone::TRI      }, // งั๊ด*
        { ICC::LOWS, ETone::CHATTAWA, false,  false, ETone::CHATTAWA }, // ง๋าน*
        { ICC::LOWS, ETone::CHATTAWA, false,  true,  ETone::CHATTAWA }, // งั๋น*
        { ICC::LOWS, ETone::CHATTAWA, true,   false, ETone::CHATTAWA }, // ง๋าด
        { ICC::LOWS, ETone::CHATTAWA, true,   true,  ETone::CHATTAWA }, // งั๋ด

    };
#undef ICC

    bool isSuccess = true;

    for (auto e : ToneTbl_) {
        auto pronTone = ToneFromWritten (e.iConsClass,
                                         e.writtenTone,
                                         e.isDeadEnd,
                                         e.isShortVowel);
        if (pronTone != e.pronTone) {
            cerr << "Wrong pronounced tone for tuple ("
                 << static_cast<int> (e.iConsClass) << ", "
                 << static_cast<int> (e.writtenTone) << ", "
                 << e.isDeadEnd << ", "
                 << e.isShortVowel << "): "
                 << static_cast<int> (pronTone) << " != "
                 << static_cast<int> (e.pronTone) << endl;
            isSuccess = false;
        }
    }

    return isSuccess;
}

int
main()
{
    bool isSuccess = true;

    cout << "Testing InitConsClass() ... ";
    if (testInitConsClass()) {
        cout << "[OK]" << endl;
    } else {
        cout << "[FAIL]" << endl;
        isSuccess = false;
    }

    cout << "Testing InitConsSound() ... ";
    if (testInitConsSound()) {
        cout << "[OK]" << endl;
    } else {
        cout << "[FAIL]" << endl;
        isSuccess = false;
    }

    cout << "Testing EndConsClass() ... ";
    if (testEndConsClass()) {
        cout << "[OK]" << endl;
    } else {
        cout << "[FAIL]" << endl;
        isSuccess = false;
    }

    cout << "Testing ToneFromWritten() ... ";
    if (testToneFromWritten()) {
        cout << "[OK]" << endl;
    } else {
        cout << "[FAIL]" << endl;
        isSuccess = false;
    }

    return isSuccess ? 0 : 1;
}

/*
vi:ts=4:ai:expandtab
*/
