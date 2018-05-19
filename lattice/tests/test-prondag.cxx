#include "lattice/pron-dag.h"
#include "output/sylout-thai.h"
#include "output/output-delim.h"
#include "output/output-json.h"

#include <iostream>
#include <list>

using namespace std;

//
// Simplified PronunDAG for "ขนมอบกรอบ":
//
//  ,---ขะ-->(-3)--หฺนม--.         ,--------กฺรอบ--------.
//  |                   v         |                    v
// (0)--ขะ-->(1)--นม-->(3)--อบ-->(5)--กอน-->(7)--อบ-->(9)
//  |                   |         ^                    ^
//  |                   `--อะ--.  |                    |
//  |         ,-----มอบ--------|--'                    |
//  `---ขน-->(2)               v                       |
//            `------มอ------>(4)--บก-->(6)--รอบ-------'
//
PronunDAG
CreatePronDAG()
{
    list<SylString> strList;

    cout << "Creating pronunciation DAG" << endl;

    SylString khanom1;
    khanom1 = Syl ("c_a_1", -3);
    khanom1 += Syl ("n_om4", 3);

    SylString khanom2;
    khanom2 = Syl ("c_a_1", 1);
    khanom2 += Syl ("n_om0", 3);

    SylString op1;
    op1 = Syl ("?_op1", 5);

    SylString kraup;
    kraup = Syl ("krCp1", 9);

    SylString kornOp;
    kornOp = Syl ("k_Cn0", 7);
    kornOp += Syl ("?_op1", 9);

    SylString a;
    a = Syl ("?_a_1", 4);

    SylString bokRop;
    bokRop = Syl ("b_ok1", 6);
    bokRop += Syl ("r_Cp2", 9);

    SylString khonMop;
    khonMop = Syl ("c_on4", 2);
    khonMop += Syl ("m_Cp2", 5);

    SylString khonMauBokRop;
    khonMauBokRop = Syl ("c_on4", 2);
    khonMauBokRop += Syl ("m_C_0", 4);
    khonMauBokRop += Syl ("b_ok1", 6);
    khonMauBokRop += Syl ("r_Cp2", 9);

    SylString str1_1;
    str1_1 += khanom1;
    str1_1 += op1;
    str1_1 += kraup;
    strList.push_back (str1_1);

    SylString str1_2;
    str1_2 += khanom2;
    str1_2 += op1;
    str1_2 += kraup;
    strList.push_back (str1_2);

    SylString str1_3;
    str1_3 += khanom1;
    str1_3 += op1;
    str1_3 += kornOp;
    strList.push_back (str1_3);

    SylString str1_4;
    str1_4 += khanom2;
    str1_4 += op1;
    str1_4 += kornOp;
    strList.push_back (str1_4);

    SylString str2_1;
    str2_1 += khanom1;
    str2_1 += a;
    str2_1 += bokRop;
    strList.push_back (str2_1);

    SylString str2_2;
    str2_2 += khanom2;
    str2_2 += a;
    str2_2 += bokRop;
    strList.push_back (str2_2);

    SylString str3_1;
    str3_1 += khonMop;
    str3_1 += kraup;
    strList.push_back (str3_1);

    SylString str3_2;
    str3_2 += khonMop;
    str3_2 += kornOp;
    strList.push_back (str3_2);

    strList.push_back (khonMauBokRop);

    return PronunDAG (strList);
}

bool
TestPronDAGEdgeExist (const PronunDAG& dag)
{
    bool isSuccess = true;

    cout << "Testing pronunciation DAG edge existence" << endl;
    // test existing edges
    if (!dag.isEdgeExist (0, -3, Syl ("c_a_1"))) {
        cout << "Edge (0, -3, 'c_a_1') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (0, 1, Syl ("c_a_1"))) {
        cout << "Edge (0, 1, 'c_a_1') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (0, 2, Syl ("c_on4"))) {
        cout << "Edge (0, 2, 'c_on4') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (-3, 3, Syl ("n_om4"))) {
        cout << "Edge (-3, 3, 'n_om4') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (1, 3, Syl ("n_om0"))) {
        cout << "Edge (1, 3, 'n_om0') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (2, 5, Syl ("m_Cp2"))) {
        cout << "Edge (2, 5, 'm_Cp2') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (2, 4, Syl ("m_C_0"))) {
        cout << "Edge (2, 4, 'm_C_0') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (3, 5, Syl ("?_op1"))) {
        cout << "Edge (3, 5, '?_op1') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (3, 4, Syl ("?_a_1"))) {
        cout << "Edge (3, 4, '?_a_1') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (4, 6, Syl ("b_ok1"))) {
        cout << "Edge (4, 6, 'b_ok1') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (5, 9, Syl ("krCp1"))) {
        cout << "Edge (5, 9, 'krCp1') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (5, 7, Syl ("k_Cn0"))) {
        cout << "Edge (5, 7, 'k_Cn0') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (7, 9, Syl ("?_op1"))) {
        cout << "Edge (7, 9, '?_op1') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (6, 9, Syl ("r_Cp2"))) {
        cout << "Edge (6, 9, 'r_Cp2') should exist, but doesn't!" << endl;
        isSuccess = false;
    }

    // test non-existing edges
    if (dag.isEdgeExist (0, -3, Syl ("n_om4"))) {
        cout << "Edge (0, -3, 'n_om4') shouldn't exist, but does!" << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (1, 2, Syl ("?_op1"))) {
        cout << "Edge (1, 2, '?_op1') shouldn't exist, but does!" << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (0, 5, Syl ("m_Cp2"))) {
        cout << "Edge (0, 5, 'o') shouldn't exist, but does!" << endl;
        isSuccess = false;
    }

    return isSuccess;
}

inline PronunFrac
MakeFrac (int endPos, const char* syl)
{
    return PronunFrac (endPos, SylString (Syl (syl)));
}

bool
TestFracDAGEdgeExist (const FracDAG& dag)
{
    bool isSuccess = true;

    cout << "Testing Fraction DAG edge existence" << endl;
    // test existing edges
    if (!dag.isEdgeExist (0, -3, MakeFrac (-3, "c_a_1"))) {
        cout << "Edge (0, -3, 'c_a_1') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (0, 1, MakeFrac (1, "c_a_1"))) {
        cout << "Edge (0, 1, 'c_a_1') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (0, 2, MakeFrac (2, "c_on4"))) {
        cout << "Edge (0, 2, 'c_on4') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (-3, 3, MakeFrac (3, "n_om4"))) {
        cout << "Edge (-3, 3, 'n_om4') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (1, 3, MakeFrac (3, "n_om0"))) {
        cout << "Edge (1, 3, 'n_om0') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (2, 5, MakeFrac (5, "m_Cp2"))) {
        cout << "Edge (2, 5, 'm_Cp2') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (2, 4, MakeFrac (4, "m_C_0"))) {
        cout << "Edge (2, 4, 'm_C_0') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (3, 5, MakeFrac (5, "?_op1"))) {
        cout << "Edge (3, 5, '?_op1') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (3, 4, MakeFrac (4, "?_a_1"))) {
        cout << "Edge (3, 4, '?_a_1') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (4, 6, MakeFrac (6, "b_ok1"))) {
        cout << "Edge (4, 6, 'b_ok1') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (5, 9, MakeFrac (9, "krCp1"))) {
        cout << "Edge (5, 9, 'krCp1') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (5, 7, MakeFrac (7, "k_Cn0"))) {
        cout << "Edge (5, 7, 'k_Cn0') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (7, 9, MakeFrac (9, "?_op1"))) {
        cout << "Edge (7, 9, '?_op1') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (6, 9, MakeFrac (9, "r_Cp2"))) {
        cout << "Edge (6, 9, 'r_Cp2') should exist, but doesn't!" << endl;
        isSuccess = false;
    }

    // test non-existing edges
    if (dag.isEdgeExist (0, -3, MakeFrac (-3, "n_om4"))) {
        cout << "Edge (0, -3, 'n_om4') shouldn't exist, but does!" << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (1, 2, MakeFrac (2, "?_op1"))) {
        cout << "Edge (1, 2, '?_op1') shouldn't exist, but does!" << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (0, 5, MakeFrac (5, "m_Cp2"))) {
        cout << "Edge (0, 5, 'o') shouldn't exist, but does!" << endl;
        isSuccess = false;
    }

    return isSuccess;
}

PronunFrac
MakeFrac (int endPos, const list<const char*> syls)
{
    SylString str;
    for (const auto& syl : syls) {
        str += Syl (syl);
    }
    return PronunFrac (endPos, str);
}

//
// FracDAG after merging single edges
//
//  ,---ขะ-หฺนม---.         ,-----กฺรอบ-----.
//  |            v         |              v
// (0)--ขะ-นม-->(3)--อบ-->(5)--กอน-อบ--->(9)
//  |            |         ^               ^
//  |            `--อะ--.  |               |
//  |         ,---มอบ---|--'               |
//  `---ขน-->(2)        v                  |
//            `--มอ--->(4)-----บก-รอบ------'
//
bool
TestFracDAGEdgeExist_NoSingle (const FracDAG& dag)
{
    bool isSuccess = true;

    cout << "Testing Fraction DAG edge existence after merging singles" << endl;
    // test existing edges
    if (!dag.isEdgeExist (0, 3, MakeFrac (3, {"c_a_1", "n_om4"}))) {
        cout << "Edge (0, 3, 'c_a_1,n_om4') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (0, 3, MakeFrac (3, {"c_a_1", "n_om0"}))) {
        cout << "Edge (0, 3, 'c_a_1,n_om0') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (0, 2, MakeFrac (2, "c_on4"))) {
        cout << "Edge (0, 2, 'c_on4') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (2, 5, MakeFrac (5, "m_Cp2"))) {
        cout << "Edge (2, 5, 'm_Cp2') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (2, 4, MakeFrac (4, "m_C_0"))) {
        cout << "Edge (2, 4, 'm_C_0') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (3, 5, MakeFrac (5, "?_op1"))) {
        cout << "Edge (3, 5, '?_op1') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (3, 4, MakeFrac (4, "?_a_1"))) {
        cout << "Edge (3, 4, '?_a_1') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (4, 9, MakeFrac (9, {"b_ok1", "r_Cp2"}))) {
        cout << "Edge (4, 9, 'b_ok1,r_Cp2') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (5, 9, MakeFrac (9, "krCp1"))) {
        cout << "Edge (5, 9, 'krCp1') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (5, 9, MakeFrac (9, {"k_Cn0", "?_op1"}))) {
        cout << "Edge (5, 9, 'k_Cn0,?_op1') should exist, but doesn't!" << endl;
        isSuccess = false;
    }

    // test removed edges
    if (dag.isEdgeExist (0, -3, MakeFrac (-3, "c_a_1"))) {
        cout << "Edge (0, -3, 'c_a_1') should have been removed, but hadn't!"
             << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (0, 1, MakeFrac (1, "c_a_1"))) {
        cout << "Edge (0, 1, 'c_a_1') should have been removed, but hadn't!"
             << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (-3, 3, MakeFrac (3, "n_om4"))) {
        cout << "Edge (-3, 3, 'n_om4') should have been removed, but hadn't!"
             << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (1, 3, MakeFrac (3, "n_om0"))) {
        cout << "Edge (1, 3, 'n_om0') should have been removed, but hadn't!"
             << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (5, 7, MakeFrac (7, "k_Cn0"))) {
        cout << "Edge (5, 7, 'k_Cn0') should have been removed, but hadn't!"
             << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (7, 9, MakeFrac (9, "?_op1"))) {
        cout << "Edge (7, 9, '?_op1') should have been removed, but hadn't!"
             << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (4, 6, MakeFrac (6, "b_ok1"))) {
        cout << "Edge (4, 6, 'b_ok1') should have been removed, but hadn't!"
             << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (6, 9, MakeFrac (9, "r_Cp2"))) {
        cout << "Edge (6, 9, 'r_Cp2') should have been removed, but hadn't!"
             << endl;
        isSuccess = false;
    }

    // test non-existing edges
    if (dag.isEdgeExist (0, -3, MakeFrac (-3, "n_om4"))) {
        cout << "Edge (0, -3, 'n_om4') shouldn't exist, but does!" << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (1, 2, MakeFrac (2, "?_op1"))) {
        cout << "Edge (1, 2, '?_op1') shouldn't exist, but does!" << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (0, 5, MakeFrac (5, "m_Cp2"))) {
        cout << "Edge (0, 5, 'o') shouldn't exist, but does!" << endl;
        isSuccess = false;
    }

    return isSuccess;
}

PronunFrac
MakeFrac (int endPos, const list<list<const char*>>& sylStrs)
{
    PronunFrac frac;
    for (const auto& str : sylStrs) {
        frac += MakeFrac (endPos, str);
    }
    return frac;
}

//
// FracDAG after merging parallel edges
//
// (0)--{ขะ-นม,ขะ-หฺนม}-->(3)--{อบ}-->(5)--{กอน-อบ,กฺรอบ}--->(9)
//  |                     |           ^                     ^
//  |                     `--{อะ}--.  |                     |
//  |           ,------{มอบ}-------|--'                     |
//  `---{ขน}-->(2)                 v                        |
//              `------{มอ}------>(4)-------{บก-รอบ}--------'
//
bool
TestFracDAGEdgeExist_NoParallel (const FracDAG& dag)
{
    bool isSuccess = true;

    cout << "Testing Fraction DAG edge existence after merging parallels"
         << endl;
    // test existing edges
    /** Disable for now, as constructing Syl element with negative endPos
     ** is way too complicated to do
    if (!dag.isEdgeExist (
            0, 3, MakeFrac (3, {{"c_a_1", "n_om4"}, {"c_a_1", "n_om0"}})
        ))
    {
        cout << "Edge (0, 3, {'c_a_1,n_om4','c_a_1,n_om0'}) should exist, "
             << "but doesn't!" << endl;
        isSuccess = false;
    }
     **/
    if (!dag.isEdgeExist (0, 2, MakeFrac (2, "c_on4"))) {
        cout << "Edge (0, 2, 'c_on4') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (2, 5, MakeFrac (5, "m_Cp2"))) {
        cout << "Edge (2, 5, 'm_Cp2') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (2, 4, MakeFrac (4, "m_C_0"))) {
        cout << "Edge (2, 4, 'm_C_0') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (3, 5, MakeFrac (5, "?_op1"))) {
        cout << "Edge (3, 5, '?_op1') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (3, 4, MakeFrac (4, "?_a_1"))) {
        cout << "Edge (3, 4, '?_a_1') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (
            4, 9, MakeFrac (9, list<const char*> ({"b_ok1", "r_Cp2"}))
        ))
    {
        cout << "Edge (4, 9, 'b_ok1,r_Cp2') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (
            5, 9, MakeFrac (9, {{"k_Cn0", "?_op1"}, {"krCp1"}})
        ))
    {
        cout << "Edge (5, 9, {'k_Cn0,?_op1','krCp1'}) should exist, "
             << "but doesn't!" << endl;
        isSuccess = false;
    }

    // test removed edges
    if (dag.isEdgeExist (
            0, 3, MakeFrac (3, list<const char*> ({"c_a_1", "n_om4"}))
        ))
    {
        cout << "Edge (0, 3, 'c_a_1,n_om4') should have been removed, "
             << "but hadn't!" << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (
            0, 3, MakeFrac (3, list<const char*> ({"c_a_1", "n_om0"}))
        ))
    {
        cout << "Edge (0, 3, 'c_a_1,n_om0') should have been removed, "
             << "but hadn't!" << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (5, 9, MakeFrac (9, "krCp1"))) {
        cout << "Edge (5, 9, 'krCp1') should have been removed, "
             << "but hadn't!" << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (
            5, 9, MakeFrac (9, list<const char*> ({"k_Cn0", "?_op1"}))
        ))
    {
        cout << "Edge (5, 9, 'k_Cn0,?_op1') should have been removed, "
             << "but hadn't!" << endl;
        isSuccess = false;
    }

    // test removed edges from merge singles phase
    if (dag.isEdgeExist (0, -3, MakeFrac (-3, "c_a_1"))) {
        cout << "Edge (0, -3, 'c_a_1') should have been removed, but hadn't!"
             << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (0, 1, MakeFrac (1, "c_a_1"))) {
        cout << "Edge (0, 1, 'c_a_1') should have been removed, but hadn't!"
             << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (-3, 3, MakeFrac (3, "n_om4"))) {
        cout << "Edge (-3, 3, 'n_om4') should have been removed, but hadn't!"
             << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (1, 3, MakeFrac (3, "n_om0"))) {
        cout << "Edge (1, 3, 'n_om0') should have been removed, but hadn't!"
             << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (5, 7, MakeFrac (7, "k_Cn0"))) {
        cout << "Edge (5, 7, 'k_Cn0') should have been removed, but hadn't!"
             << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (7, 9, MakeFrac (9, "?_op1"))) {
        cout << "Edge (7, 9, '?_op1') should have been removed, but hadn't!"
             << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (4, 6, MakeFrac (6, "b_ok1"))) {
        cout << "Edge (4, 6, 'b_ok1') should have been removed, but hadn't!"
             << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (6, 9, MakeFrac (9, "r_Cp2"))) {
        cout << "Edge (6, 9, 'r_Cp2') should have been removed, but hadn't!"
             << endl;
        isSuccess = false;
    }

    // test non-existing edges
    if (dag.isEdgeExist (0, -3, MakeFrac (-3, "n_om4"))) {
        cout << "Edge (0, -3, 'n_om4') shouldn't exist, but does!" << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (1, 2, MakeFrac (2, "?_op1"))) {
        cout << "Edge (1, 2, '?_op1') shouldn't exist, but does!" << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (0, 5, MakeFrac (5, "m_Cp2"))) {
        cout << "Edge (0, 5, 'o') shouldn't exist, but does!" << endl;
        isSuccess = false;
    }

    return isSuccess;
}

void
DumpPronunDAG (const PronunDAG& pronDAG)
{
    DelimOutput output (make_unique<ThaiSylOutput>(), '-');

    cout << "PronunDAG dump:" << endl;
    for (auto it = pronDAG.outBegin(); it != pronDAG.outEnd(); ++it) {
        cout << "  (" << it->first << ")--"
             << output.output (it->second.edgeVal)
             << "-->(" << it->second.target << ")" << endl;
    }
}

void
DumpFracDAG (const FracDAG& fracDAG)
{
    DelimOutput output (make_unique<ThaiSylOutput>(), '-');

    cout << "FracDAG dump:" << endl;
    for (auto it = fracDAG.outBegin(); it != fracDAG.outEnd(); ++it) {
        cout << "  (" << it->first << ")--{";
        bool isFirst = true;
        for (const auto& syl : it->second.edgeVal) {
            if (!isFirst) {
                cout << ",";
            }
            cout << output.output (syl);
            isFirst = false;
        }
        cout << "}-->(" << it->second.target << ")" << endl;
    }
}

int main()
{
    bool isSuccess = true;

    PronunDAG pronDAG = CreatePronDAG();

    if (!TestPronDAGEdgeExist (pronDAG)) {
        isSuccess = false;
    }

    DumpPronunDAG (pronDAG);

    cout << "Creating FracDAG" << endl;
    FracDAG fracDAG = pronDAG.fracDAG();

    if (!TestFracDAGEdgeExist (fracDAG)) {
        isSuccess = false;
    }

    DumpFracDAG (fracDAG);

    //
    // Disabled private method tests
    //
    // For fine-grained testing, make FracDAG::mergeSingles()
    // and FracDAG::mergeParallels() public and replace
    // fracDAG.mergeFractions() call with this code
    //
#if 0 // MERGE-SINGLE TEST
    cout << "Merging single edges in FracDAG" << endl;
    fracDAG.mergeSingles();

    if (!TestFracDAGEdgeExist_NoSingle (fracDAG)) {
        isSuccess = false;
    }

    DumpFracDAG (fracDAG);

    cout << "Merging parallel edges in FracDAG" << endl;
    fracDAG.mergeParallels();
#endif // MERGE-SINGLE TEST

    fracDAG.mergeFractions();

    if (!TestFracDAGEdgeExist_NoParallel (fracDAG)) {
        isSuccess = false;
    }

    DumpFracDAG (fracDAG);

    cout << "Creating PronunLatt" << endl;
    PronunLatt pronLatt = fracDAG.lattice();

    JsonOutput output (make_unique<ThaiSylOutput>());
    cout << "PronunLatt dump:" << endl;
    cout << output.output (pronLatt) << endl;

    return isSuccess ? 0 : 1;
}

/*
vi:ts=4:ai:expandtab
*/
