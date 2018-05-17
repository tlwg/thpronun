#include "sylstring/syl.h"

#include <iostream>

using namespace std;

bool
TestEquality()
{
    bool isSuccess = true;

    Syl kok1Syl1 ("k_ok1");
    Syl kok1Syl2 ("k_ok1");
    cout << "Testing operator == on 'k_ok1' and 'k_ok1'" << endl;
    if (kok1Syl1 == kok1Syl2) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator != on 'k_ok1' and 'k_ok1'" << endl;
    if (kok1Syl1 != kok1Syl2) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }

    Syl cok1Syl ("c_ok1");
    cout << "Testing operator == on 'k_ok1' and 'c_ok1" << endl;
    if (kok1Syl1 == cok1Syl) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator != on 'k_ok1' and 'c_ok1" << endl;
    if (kok1Syl1 != cok1Syl) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }

    Syl krok1Syl ("krok1");
    cout << "Testing operator == on 'k_ok1' and 'krok1" << endl;
    if (kok1Syl1 == krok1Syl) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator != on 'k_ok1' and 'krok1" << endl;
    if (kok1Syl1 != krok1Syl) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }

    Syl kOk1Syl ("k_Ok1");
    cout << "Testing operator == on 'k_ok1' and 'k_Ok1" << endl;
    if (kok1Syl1 == kOk1Syl) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator != on 'k_ok1' and 'k_Ok1" << endl;
    if (kok1Syl1 != kOk1Syl) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }

    Syl kon1Syl ("k_on1");
    cout << "Testing operator == on 'k_ok1' and 'k_on1" << endl;
    if (kok1Syl1 == kon1Syl) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator != on 'k_ok1' and 'k_on1" << endl;
    if (kok1Syl1 != kon1Syl) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }

    Syl kok3Syl ("k_ok3");
    cout << "Testing operator == on 'k_ok1' and 'k_ok3" << endl;
    if (kok1Syl1 == kok3Syl) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator != on 'k_ok1' and 'k_ok3" << endl;
    if (kok1Syl1 != kok3Syl) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }

    return isSuccess;
}

bool
TestOrdering()
{
    bool isSuccess = true;

    Syl kok1Syl1 ("k_ok1", 2);
    Syl kok1Syl2 ("k_ok1", 2);
    cout << "Testing operator < on 'k_ok1'@2 and 'k_ok1'@2" << endl;
    if (kok1Syl1 < kok1Syl2) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator > on 'k_ok1'@2 and 'k_ok1'@2" << endl;
    if (kok1Syl1 > kok1Syl2) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator <= on 'k_ok1'@2 and 'k_ok1'@2" << endl;
    if (kok1Syl1 <= kok1Syl2) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator >= on 'k_ok1'@2 and 'k_ok1'@2" << endl;
    if (kok1Syl1 >= kok1Syl2) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }

    Syl kok1Syl3 ("k_ok1", 4);
    cout << "Testing operator < on 'k_ok1'@2 and 'k_ok1'@4" << endl;
    if (kok1Syl1 < kok1Syl3) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator > on 'k_ok1'@2 and 'k_ok1'@4" << endl;
    if (kok1Syl1 > kok1Syl3) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator <= on 'k_ok1'@2 and 'k_ok1'@4" << endl;
    if (kok1Syl1 <= kok1Syl3) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator >= on 'k_ok1'@2 and 'k_ok1'@4" << endl;
    if (kok1Syl1 >= kok1Syl3) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }

    Syl cok1Syl ("c_ok1", 2);
    cout << "Testing operator < on 'k_ok1'@2 and 'c_ok1'@2" << endl;
    if (kok1Syl1 < cok1Syl) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator > on 'k_ok1'@2 and 'c_ok1'@2" << endl;
    if (kok1Syl1 > cok1Syl) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator <= on 'k_ok1'@2 and 'c_ok1'@2" << endl;
    if (kok1Syl1 <= cok1Syl) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator >= on 'k_ok1'@2 and 'c_ok1'@2" << endl;
    if (kok1Syl1 >= cok1Syl) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }

    Syl krok1Syl ("krok1");
    cout << "Testing operator < on 'k_ok1'@2 and 'krok1'@2" << endl;
    if (kok1Syl1 < krok1Syl) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator > on 'k_ok1'@2 and 'krok1'@2" << endl;
    if (kok1Syl1 > krok1Syl) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator <= on 'k_ok1'@2 and 'krok1'@2" << endl;
    if (kok1Syl1 <= krok1Syl) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator >= on 'k_ok1'@2 and 'krok1'@2" << endl;
    if (kok1Syl1 >= krok1Syl) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }

    Syl kOk1Syl ("k_Ok1", 2);
    cout << "Testing operator < on 'k_ok1'@2 and 'k_Ok1'@2" << endl;
    if (kok1Syl1 < kOk1Syl) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator > on 'k_ok1'@2 and 'k_Ok1'@2" << endl;
    if (kok1Syl1 > kOk1Syl) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator <= on 'k_ok1'@2 and 'k_Ok1'@2" << endl;
    if (kok1Syl1 <= kOk1Syl) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator >= on 'k_ok1'@2 and 'k_Ok1'@2" << endl;
    if (kok1Syl1 >= kOk1Syl) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }

    Syl kon1Syl ("k_on1", 2);
    cout << "Testing operator < on 'k_ok1'@2 and 'k_on1'@2" << endl;
    if (kok1Syl1 < kon1Syl) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator > on 'k_ok1'@2 and 'k_on1'@2" << endl;
    if (kok1Syl1 > kon1Syl) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator <= on 'k_ok1'@2 and 'k_on1'@2" << endl;
    if (kok1Syl1 <= kon1Syl) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator >= on 'k_ok1'@2 and 'k_on1'@2" << endl;
    if (kok1Syl1 >= kon1Syl) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }

    Syl kok3Syl ("k_ok3", 2);
    cout << "Testing operator < on 'k_ok1'@2 and 'k_ok3'@2" << endl;
    if (kok1Syl1 < kok3Syl) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator > on 'k_ok1'@2 and 'k_ok3'@2" << endl;
    if (kok1Syl1 > kok3Syl) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator <= on 'k_ok1'@2 and 'k_ok3'@2" << endl;
    if (kok1Syl1 <= kok3Syl) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator >= on 'k_ok1'@2 and 'k_ok3'@2" << endl;
    if (kok1Syl1 >= kok3Syl) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }


    return isSuccess;
}

int
main()
{
    bool isSuccess = true;

    if (!TestEquality()) {
        isSuccess = false;
    }

    if (!TestOrdering()) {
        isSuccess = false;
    }

    return isSuccess ? 0 : 1;
}

/*
vi:ts=4:ai:expandtab
*/
