#include "sylstring/sylstring.h"

#include <iostream>

using namespace std;

bool
TestEquality()
{
    bool isSuccess = true;

    SylString str1;
    str1 += Syl ("m_At2", 2);
    str1 += Syl ("trA_0", 5);

    SylString str2;
    str2 += Syl ("m_At2", 2);
    str2 += Syl ("trA_0", 5);

    SylString str3;
    str3 += Syl ("m_A_0", 2);
    str3 += Syl ("trA_0", 5);

    cout << "Testing operator == with 'm_At2@2,trA_0@5' and 'm_At2@2,trA_0@5'"
         << endl;
    if (str1 == str2) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator != with 'm_At2@2,trA_0@5' and 'm_At2@2,trA_0@5'"
         << endl;
    if (str1 != str2) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }

    cout << "Testing operator == with 'm_At2@2,trA_0@5' and 'm_A_0@2,trA_0@5'"
         << endl;
    if (str1 == str3) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator != with 'm_At2@2,trA_0@5' and 'm_A_0@2,trA_0@5'"
         << endl;
    if (str1 != str3) {
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

    SylString str1;
    str1 += Syl ("m_At2", 2);
    str1 += Syl ("trA_0", 5);

    SylString str2;
    str2 += Syl ("m_At2", 2);
    str2 += Syl ("trA_0", 5);

    SylString str3;
    str3 += Syl ("m_A_0", 2);
    str3 += Syl ("trA_0", 5);

    cout << "Testing operator < with 'm_At2@2,trA_0@5' and 'm_At2@2,trA_0@5'"
         << endl;
    if (str1 < str2) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator > with 'm_At2@2,trA_0@5' and 'm_At2@2,trA_0@5'"
         << endl;
    if (str1 > str2) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator <= with 'm_At2@2,trA_0@5' and 'm_At2@2,trA_0@5'"
         << endl;
    if (str1 <= str2) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator >= with 'm_At2@2,trA_0@5' and 'm_At2@2,trA_0@5'"
         << endl;
    if (str1 >= str2) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }


    cout << "Testing operator < with 'm_At2@2,trA_0@5' and 'm_A_0@2,trA_0@5'"
         << endl;
    if (str1 < str3) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator > with 'm_At2@2,trA_0@5' and 'm_A_0@2,trA_0@5'"
         << endl;
    if (str1 > str3) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator <= with 'm_At2@2,trA_0@5' and 'm_A_0@2,trA_0@5'"
         << endl;
    if (str1 <= str3) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator >= with 'm_At2@2,trA_0@5' and 'm_A_0@2,trA_0@5'"
         << endl;
    if (str1 >= str3) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }


    str2 += Syl ("s_Tn1", 9);

    cout << "Testing operator < with 'm_At2@2,trA_0@5' and "
         << "'m_At2@2,trA_0@5,s_Tn1@9'"
         << endl;
    if (str1 < str2) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator > with 'm_At2@2,trA_0@5' and "
         << "'m_At2@2,trA_0@5,s_Tn1@9'"
         << endl;
    if (str1 > str2) {
        cout << "  FAIL" << endl;
        isSuccess = false;
    } else {
        cout << "  OK" << endl;
    }
    cout << "Testing operator <= with 'm_At2@2,trA_0@5' and "
         << "'m_At2@2,trA_0@5,s_Tn1@9'"
         << endl;
    if (str1 <= str2) {
        cout << "  OK" << endl;
    } else {
        cout << "  FAIL" << endl;
        isSuccess = false;
    }
    cout << "Testing operator >= with 'm_At2@2,trA_0@5' and "
         << "'m_At2@2,trA_0@5,s_Tn1@9'"
         << endl;
    if (str1 >= str2) {
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
