#include "lattice/pron-dag.h"

#include <iostream>
#include <list>

using namespace std;

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

int main()
{
    bool isSuccess = true;

    PronunDAG pronDAG = CreatePronDAG();

    if (!TestPronDAGEdgeExist (pronDAG)) {
        isSuccess = false;
    }

    cout << "Creating FracDAG" << endl;
    FracDAG fracDAG = pronDAG.fracDAG();

    if (!TestFracDAGEdgeExist (fracDAG)) {
        isSuccess = false;
    }

    return isSuccess ? 0 : 1;
}

/*
vi:ts=4:ai:expandtab
*/
