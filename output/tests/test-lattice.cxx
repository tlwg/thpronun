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
    PronunFrac maFrac;
    maFrac += SylString ("m_A_0");
    maFrac += SylString ("m_At2");

    PronunFrac traFrac;
    traFrac += SylString ("trA_0");
    traFrac += SylString ("t_a_1,r_A_0");

    PronunFrac matRaFrac;
    matRaFrac += SylString ("m_At2,r_A_0");

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
    PronunFrac jatRatFrac;
    jatRatFrac += SylString ("j_at1,r_at3");

    PronunFrac jatFrac;
    jatFrac += SylString ("j_at1");

    PronunFrac tuFrac;
    tuFrac += SylString ("t_u_1");
    tuFrac += SylString ("t_un0");

    PronunFrac ratFrac;
    ratFrac += SylString ("r_at3");

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
    PronunFrac khanomFrac;
    khanomFrac += SylString ("c_a_1,n_om4");
    khanomFrac += SylString ("c_a_1,n_om0");

    PronunFrac opFrac;
    opFrac += SylString ("?_op1");

    PronunFrac kraupFrac;
    kraupFrac += SylString ("krCp1");
    kraupFrac += SylString ("k_Cn0,?_op1");

    PronunFrac aFrac;
    aFrac += SylString ("?_a_1");

    PronunFrac bokRopFrac;
    bokRopFrac += SylString ("b_ok1,r_Cp2");

    PronunFrac khonMopFrac;
    khonMopFrac += SylString ("c_on4,m_Cp2");

    PronunFrac khonMauBokRopFrac;
    khonMauBokRopFrac += SylString ("c_on4,m_C_0,b_ok1,r_Cp2");

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
