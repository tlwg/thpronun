#include "lattice/lattice.h"
#include "output/sylout-thai.h"
#include "output/output-gjson.h"

#include <iostream>
#include <memory>

using namespace std;

//
// Lattice 1: simplified lattice for "มาตรา"
//

const string Latt1Expect =
    "["
        "["
            "["
                "[\"มา\"],[\"มาด\"]"
            "],"
            "["
                "[\"ตะ\",\"รา\"],[\"ตฺรา\"]"
            "]"
        "],"
        "["
            "["
                "[\"มาด\",\"รา\"]"
            "]"
        "]"
    "]";

PronunLatt
PrepareLatt1()
{
    SylString sylStr;

    PronunFrac maFrac;
    sylStr = Syl ("m_A_0");
    maFrac += sylStr;
    sylStr = Syl ("m_At2");
    maFrac += sylStr;

    PronunFrac traFrac;
    sylStr = Syl ("trA_0");
    traFrac += sylStr;
    sylStr = Syl ("t_a_1");
    sylStr += Syl ("r_A_0");
    traFrac += sylStr;

    PronunFrac matRaFrac;
    sylStr = Syl ("m_At2");
    sylStr += Syl ("r_A_0");
    matRaFrac += sylStr;

    PronunChain chain1;
    chain1 += maFrac;
    chain1 += traFrac;

    PronunChain chain2;
    chain2 += matRaFrac;

    PronunLatt latt;
    latt += chain1;
    latt += chain2;

    return latt;
}

//
// Lattice 2: simplified lattice for "จัตุรัส"
//

const string Latt2Expect =
    "["
        "["
            "["
                "[\"จัด\",\"รัด\"]"
            "]"
        "],"
        "["
            "["
                "[\"จัด\"]"
            "],"
            "["
                "[\"ตุ\"],"
                "[\"ตุน\"]"
            "],"
            "["
                "[\"รัด\"]"
            "]"
        "]"
    "]";

PronunLatt
PrepareLatt2()
{
    SylString sylStr;

    PronunFrac jatRatFrac;
    sylStr = Syl ("j_at1");
    sylStr += Syl ("r_at3");
    jatRatFrac += sylStr;

    PronunFrac jatFrac;
    sylStr = Syl ("j_at1");
    jatFrac += sylStr;

    PronunFrac tuFrac;
    sylStr = Syl ("t_u_1");
    tuFrac += sylStr;
    sylStr = Syl ("t_un0");
    tuFrac += sylStr;

    PronunFrac ratFrac;
    sylStr = Syl ("r_at3");
    ratFrac += sylStr;

    PronunChain chain1;
    chain1 += jatRatFrac;

    PronunChain chain2;
    chain2 += jatFrac;
    chain2 += tuFrac;
    chain2 += ratFrac;

    PronunLatt latt;
    latt += chain1;
    latt += chain2;

    return latt;
}

//
// Lattice 3: simplified lattice for "ขนมอบกรอบ"
//

const string Latt3Expect =
    "["
        "["
            "["
                "[\"ขะ\",\"นม\"],"
                "[\"ขะ\",\"หฺนม\"]"
            "],"
            "["
                "[\"อบ\"]"
            "],"
            "["
                "[\"กอน\",\"อบ\"],"
                "[\"กฺรอบ\"]"
            "]"
        "],"
        "["
            "["
                "[\"ขะ\",\"นม\"],"
                "[\"ขะ\",\"หฺนม\"]"
            "],"
            "["
                "[\"อะ\"]"
            "],"
            "["
                "[\"บก\",\"รอบ\"]"
            "]"
        "],"
        "["
            "["
                "[\"ขน\",\"มอบ\"]"
            "],"
            "["
                "[\"กอน\",\"อบ\"],"
                "[\"กฺรอบ\"]"
            "]"
        "],"
        "["
            "["
                "[\"ขน\",\"มอ\",\"บก\",\"รอบ\"]"
            "]"
        "]"
    "]";

PronunLatt
PrepareLatt3()
{
    SylString sylStr;

    PronunFrac khanomFrac;
    sylStr = Syl ("c_a_1");
    sylStr += Syl ("n_om4");
    khanomFrac += sylStr;
    sylStr = Syl ("c_a_1");
    sylStr += Syl ("n_om0");
    khanomFrac += sylStr;

    PronunFrac opFrac;
    sylStr = Syl ("?_op1");
    opFrac += sylStr;

    PronunFrac kraupFrac;
    sylStr = Syl ("krCp1");
    kraupFrac += sylStr;
    sylStr = Syl ("k_Cn0");
    sylStr += Syl ("?_op1");
    kraupFrac += sylStr;

    PronunFrac aFrac;
    sylStr = Syl ("?_a_1");
    aFrac += sylStr;

    PronunFrac bokRopFrac;
    sylStr = Syl ("b_ok1");
    sylStr += Syl ("r_Cp2");
    bokRopFrac += sylStr;

    PronunFrac khonMopFrac;
    sylStr = Syl ("c_on4");
    sylStr += Syl ("m_Cp2");
    khonMopFrac += sylStr;

    PronunFrac khonMauBokRopFrac;
    sylStr = Syl ("c_on4");
    sylStr += Syl ("m_C_0");
    sylStr += Syl ("b_ok1");
    sylStr += Syl ("r_Cp2");
    khonMauBokRopFrac += sylStr;

    PronunChain chain1;
    chain1 += khanomFrac;
    chain1 += opFrac;
    chain1 += kraupFrac;

    PronunChain chain2;
    chain2 += khanomFrac;
    chain2 += aFrac;
    chain2 += bokRopFrac;

    PronunChain chain3;
    chain3 += khonMopFrac;
    chain3 += kraupFrac;

    PronunChain chain4;
    chain4 += khonMauBokRopFrac;

    PronunLatt latt;
    latt += chain1;
    latt += chain2;
    latt += chain3;
    latt += chain4;

    return latt;
}

bool
TestLatt (const PronunLatt& latt, const string& expected)
{
    bool isSuccess = true;
    auto output
        = make_unique<GroupedJsonOutput> (make_unique<ThaiSylOutput>());

    string outStr = output->output (latt);
    cout << outStr << endl;
    if (outStr == expected) {
        cout << "OK" << endl;
    } else {
        cout << "Wrong output:" << endl
             << " Expect: " << expected << endl
             << " Got:    " << outStr << endl;
        isSuccess = false;
    }

    return isSuccess;
}

int
main()
{
    bool isSuccess = true;

    cout << "Testing lattice output #1" << endl;
    if (!TestLatt (PrepareLatt1(), Latt1Expect)) {
        isSuccess = false;
    }

    cout << "Testing lattice output #2" << endl;
    if (!TestLatt (PrepareLatt2(), Latt2Expect)) {
        isSuccess = false;
    }

    cout << "Testing lattice output #3" << endl;
    if (!TestLatt (PrepareLatt3(), Latt3Expect)) {
        isSuccess = false;
    }

    return isSuccess ? 0 : 1;
}

/*
vi:ts=4:ai:expandtab
*/
