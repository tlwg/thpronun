#include "lattice/dag.h"

#include <iostream>

using namespace std;

//
// Simple Word DAG
//
//  ,---c----.        ,-------n-------.
//  |        v        |               v
// (0)--f-->(1)--a-->(2)------t----->(5)
//           |                        ^
//           `---o-->(3)--r-->(4)--k--'
//
DAG<char>
WordDAG()
{
    DAG<char> dag;

    dag.addEdge (0, 1, 'c');
    dag.addEdge (0, 1, 'f');
    dag.addEdge (1, 2, 'a');
    dag.addEdge (2, 5, 'n');
    dag.addEdge (2, 5, 't');
    dag.addEdge (1, 3, 'o');
    dag.addEdge (3, 4, 'r');
    dag.addEdge (4, 5, 'k');

    return dag;
}

bool
TestEdgeExist (const DAG<char>& dag)
{
    bool isSuccess = true;

    cout << "Testing edge existence" << endl;
    // test existing edges
    if (!dag.isEdgeExist (0, 1, 'c')) {
        cout << "Edge (0, 1, 'c') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (0, 1, 'f')) {
        cout << "Edge (0, 1, 'f') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (1, 2, 'a')) {
        cout << "Edge (1, 2, 'a') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (2, 5, 'n')) {
        cout << "Edge (2, 5, 'n') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (2, 5, 't')) {
        cout << "Edge (2, 5, 't') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (1, 3, 'o')) {
        cout << "Edge (1, 3, 'o') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (3, 4, 'r')) {
        cout << "Edge (3, 4, 'r') should exist, but doesn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (4, 5, 'k')) {
        cout << "Edge (4, 5, 'k') should exist, but doesn't!" << endl;
        isSuccess = false;
    }

    // test non-existing edges
    if (dag.isEdgeExist (0, 1, 'a')) {
        cout << "Edge (0, 1, 'a') shouldn't exist, but does!" << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (1, 2, 'c')) {
        cout << "Edge (1, 2, 'c') shouldn't exist, but does!" << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (0, 5, 'o')) {
        cout << "Edge (0, 5, 'o') shouldn't exist, but does!" << endl;
        isSuccess = false;
    }

    return isSuccess;
}

bool
CheckOutDegree (const DAG<char>& dag, int from, int expected)
{
    if (dag.outDegree (from) != expected) {
        cout << "outDegree(" << from << ") = " << dag.outDegree (from)
             << ", expecting " << expected << endl;
        return false;
    }
    return true;
}

bool
TestOutDegree (const DAG<char>& dag)
{
    bool isSuccess = true;

    cout << "Testing out degrees" << endl;
    if (!CheckOutDegree (dag, 0, 2)) { isSuccess = false; }
    if (!CheckOutDegree (dag, 1, 2)) { isSuccess = false; }
    if (!CheckOutDegree (dag, 2, 2)) { isSuccess = false; }
    if (!CheckOutDegree (dag, 3, 1)) { isSuccess = false; }
    if (!CheckOutDegree (dag, 4, 1)) { isSuccess = false; }
    if (!CheckOutDegree (dag, 5, 0)) { isSuccess = false; }

    return isSuccess;
}

bool
CheckInDegree (const DAG<char>& dag, int to, int expected)
{
    if (dag.inDegree (to) != expected) {
        cout << "inDegree(" << to << ") = " << dag.inDegree (to)
             << ", expecting " << expected << endl;
        return false;
    }
    return true;
}

bool
TestInDegree (const DAG<char>& dag)
{
    bool isSuccess = true;

    cout << "Testing in degrees" << endl;
    if (!CheckInDegree (dag, 0, 0)) { isSuccess = false; }
    if (!CheckInDegree (dag, 1, 2)) { isSuccess = false; }
    if (!CheckInDegree (dag, 2, 1)) { isSuccess = false; }
    if (!CheckInDegree (dag, 3, 1)) { isSuccess = false; }
    if (!CheckInDegree (dag, 4, 1)) { isSuccess = false; }
    if (!CheckInDegree (dag, 5, 3)) { isSuccess = false; }

    return isSuccess;
}

bool
CheckOutEdges (const DAG<char>& dag, int from,
               const list<DAGEdge<char>>& expected)
{
    bool isSuccess = true;

    auto range = dag.outEdges (from);
    auto dagIt = range.first;
    auto expIt = expected.begin();
    while (dagIt != range.second && expIt != expected.end()) {
        if (dagIt->second.target != expIt->target) {
            cout << "Edge from " << from << " has target "
                 << dagIt->second.target
                 << ", expecting " << expIt->target << endl;
            isSuccess = false;
        }
        if (dagIt->second.edgeVal != expIt->edgeVal) {
            cout << "Edge from " << from << " has edge value "
                 << dagIt->second.edgeVal
                 << ", expecting " << expIt->edgeVal << endl;
            isSuccess = false;
        }
        ++dagIt; ++expIt;
    }

    return isSuccess;
}

bool
TestOutEdges (const DAG<char>& dag)
{
    bool isSuccess = true;

    cout << "Testing out edges" << endl;
    if (!CheckOutEdges (dag, 0, {{1, 'c'}, {1, 'f'}})) {
        isSuccess = false;
    }
    if (!CheckOutEdges (dag, 1, {{2, 'a'}, {3, 'o'}})) {
        isSuccess = false;
    }
    if (!CheckOutEdges (dag, 2, {{5, 'n'}, {5, 't'}})) {
        isSuccess = false;
    }
    if (!CheckOutEdges (dag, 3, {{4, 'r'}})) {
        isSuccess = false;
    }
    if (!CheckOutEdges (dag, 4, {{5, 'k'}})) {
        isSuccess = false;
    }
    if (!CheckOutEdges (dag, 5, {})) {
        isSuccess = false;
    }

    return isSuccess;
}

bool
CheckInEdges (const DAG<char>& dag, int to,
              const list<DAGEdge<char>>& expected)
{
    bool isSuccess = true;

    auto range = dag.inEdges (to);
    auto dagIt = range.first;
    auto expIt = expected.begin();
    while (dagIt != range.second && expIt != expected.end()) {
        if (dagIt->second.target != expIt->target) {
            cout << "Edge to " << to << " has target "
                 << dagIt->second.target
                 << ", expecting " << expIt->target << endl;
            isSuccess = false;
        }
        if (dagIt->second.edgeVal != expIt->edgeVal) {
            cout << "Edge to " << to << " has edge value "
                 << dagIt->second.edgeVal
                 << ", expecting " << expIt->edgeVal << endl;
            isSuccess = false;
        }
        ++dagIt; ++expIt;
    }

    return isSuccess;
}

bool
TestInEdges (const DAG<char>& dag)
{
    bool isSuccess = true;

    cout << "Testing in edges" << endl;
    if (!CheckInEdges (dag, 0, {})) {
        isSuccess = false;
    }
    if (!CheckInEdges (dag, 1, {{0, 'c'}, {0, 'f'}})) {
        isSuccess = false;
    }
    if (!CheckInEdges (dag, 2, {{1, 'a'}})) {
        isSuccess = false;
    }
    if (!CheckInEdges (dag, 3, {{1, 'o'}})) {
        isSuccess = false;
    }
    if (!CheckInEdges (dag, 4, {{3, 'r'}})) {
        isSuccess = false;
    }
    if (!CheckInEdges (dag, 5, {{2, 'n'}, {2, 't'}, {4, 'k'}})) {
        isSuccess = false;
    }

    return isSuccess;
}

bool
TestRemoveEdges (DAG<char>& dag)
{
    bool isSuccess = true;

    cout << "Test removing edge (2)-n->(5)" << endl;
    if (!dag.removeEdge (2, 5, 'n')) {
        cout << "Fail to remove edge (2)-n->(5)" << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (2, 5, 'n')) {
        cout << "Edge (2)-n->(5) should have been removed, but hadn't!" << endl;
        isSuccess = false;
    }
    if (!dag.isEdgeExist (2, 5, 't')) {
        cout << "Edge (2)-t->(5) shouldn't have been removed, but had been!"
             << endl;
        isSuccess = false;
    }

    cout << "Test removing all edges from (0) to (1)" << endl;
    if (!dag.removeDirectEdges (0, 1)) {
        cout << "Failed to remove edges from (0) to (1)" << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (0, 1, 'c')) {
        cout << "Edge (0)-c->(1) should have been removed, but hadn't!" << endl;
        isSuccess = false;
    }
    if (dag.isEdgeExist (0, 1, 'f')) {
        cout << "Edge (0)-f->(1) should have been removed, but hadn't!" << endl;
        isSuccess = false;
    }

    return isSuccess;
}

void
DumpOutEdges (const DAG<char>& dag)
{
    cout << "Dumping out edges:" << endl;
    for (auto it = dag.outBegin(); it != dag.outEnd(); ++it) {
        cout << "  (" << it->first << ")"
             << "-" << it->second.edgeVal << "->"
             << "(" << it->second.target << ")" << endl;
    }
}

void
DumpInEdges (const DAG<char>& dag)
{
    cout << "Dumping in edges:" << endl;
    for (auto it = dag.inBegin(); it != dag.inEnd(); ++it) {
        cout << "  (" << it->first << ")"
             << "<-" << it->second.edgeVal << "-"
             << "(" << it->second.target << ")" << endl;
    }
}

int main()
{
    bool isSuccess = true;

    DAG<char> wordDAG = WordDAG();

    if (!TestEdgeExist (wordDAG)) {
        isSuccess = false;
    }

    if (!TestOutDegree (wordDAG)) {
        isSuccess = false;
    }

    if (!TestInDegree (wordDAG)) {
        isSuccess = false;
    }

    if (!TestOutEdges (wordDAG)) {
        isSuccess = false;
    }

    if (!TestInEdges (wordDAG)) {
        isSuccess = false;
    }

    if (!TestRemoveEdges (wordDAG)) {
        isSuccess = false;
    }

    DumpOutEdges (wordDAG);
    DumpInEdges (wordDAG);

    return isSuccess ? 0 : 1;
}

/*
vi:ts=4:ai:expandtab
*/
