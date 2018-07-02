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
    Syl kok1Syl2 ("k_ok1@2");
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

    Syl kok1Syl3 ("k_ok1@4");
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

    Syl cok1Syl ("c_ok1@2");
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

    Syl krok1Syl ("krok1@2");
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

    Syl kOk1Syl ("k_Ok1@2");
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

    Syl kon1Syl ("k_on1@2");
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

    Syl kok3Syl ("k_ok3@2");
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

bool
TestLiteral()
{
    bool isSuccess = true;

    Syl lit1 (5, u"hello");
    cout << "Testing operations on literal Syl" << endl;
    cout << "- isLiteral(): ";
    if (lit1.isLiteral()) {
        cout << "OK" << endl;
    } else {
        cout << "FAIL" << endl;
        isSuccess = false;
    }
    cout << "- literal(): ";
    if (lit1.literal() == u"hello") {
        cout << "OK" << endl;
    } else {
        cout << "FAIL" << endl;
        isSuccess = false;
    }

    // Test comparison with Blank
    cout << "Testing operator == on literal and blank" << endl;
    if (lit1 == Syl::Blank) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator != on literal and blank" << endl;
    if (lit1 != Syl::Blank) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator < on literal and blank" << endl;
    if (lit1 < Syl::Blank) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator > on literal and blank" << endl;
    if (lit1 > Syl::Blank) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator <= on literal and blank" << endl;
    if (lit1 <= Syl::Blank) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator >= on literal and blank" << endl;
    if (lit1 >= Syl::Blank) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }

    // Test comparison with normal syllable
    Syl syl1 ("k_ok1", 2);
    cout << "Testing operator == on literal and 'k_ok1'@2" << endl;
    if (lit1 == syl1) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator != on literal and 'k_ok1'@2" << endl;
    if (lit1 != syl1) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator < on literal and 'k_ok1'@2" << endl;
    if (lit1 < syl1) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator > on literal and 'k_ok1'@2" << endl;
    if (lit1 > syl1) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator <= on literal and 'k_ok1'@2" << endl;
    if (lit1 <= syl1) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator >= on literal and 'k_ok1'@2" << endl;
    if (lit1 >= syl1) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }

    // Test comparison with self
    cout << "Testing operator == on lit'hello'@5 and self" << endl;
    if (lit1 == lit1) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator != on lit'hello'@5 and self" << endl;
    if (lit1 != lit1) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator < on lit'hello'@5 and self" << endl;
    if (lit1 < lit1) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator > on lit'hello'@5 and self" << endl;
    if (lit1 > lit1) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator <= on lit'hello'@5 and self" << endl;
    if (lit1 <= lit1) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator >= on lit'hello'@5 and self" << endl;
    if (lit1 >= lit1) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }

    // Test comparison with another literal
    Syl lit2 (7, u"goodbye");
    cout << "Testing operator == on literal and lit'goodbye'@7" << endl;
    if (lit1 == lit2) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator != on literal and lit'goodbye'@7" << endl;
    if (lit1 != lit2) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator < on lit'hello'@5 and lit'goodbye'@7" << endl;
    if (lit1 < lit2) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator > on lit'hello'@5 and lit'goodbye'@7" << endl;
    if (lit1 > lit2) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator <= on lit'hello'@5 and lit'goodbye'@7" << endl;
    if (lit1 <= lit2) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator >= on lit'hello'@5 and lit'goodbye'@7" << endl;
    if (lit1 >= lit2) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
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

    if (!TestLiteral()) {
        isSuccess = false;
    }

    return isSuccess ? 0 : 1;
}

/*
vi:ts=4:ai:expandtab
*/
