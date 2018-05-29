// dag.h - Generic Directed Acyclic Graph template class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-10

#ifndef DAG_H
#define DAG_H

#include "sylstring/sylstring.h"
#include "lattice.h"

#include <utility>
#include <map>

template<typename TEdgeVal>
struct DAGEdge {
    int      target;
    TEdgeVal edgeVal;

    DAGEdge();
    DAGEdge (int target, const TEdgeVal& edgeVal);
    DAGEdge (const DAGEdge& other);
    DAGEdge (DAGEdge&& other);
};

template<typename TEdgeVal>
class DAG {
public:
    typedef typename std::multimap<int, DAGEdge<TEdgeVal>>::iterator       EdgeIter;
    typedef typename std::multimap<int, DAGEdge<TEdgeVal>>::const_iterator ConstEdgeIter;

public:
    DAG();
    DAG (const DAG<TEdgeVal>& other);
    DAG (DAG<TEdgeVal>&& other);

    bool addEdge (int from, int to, const TEdgeVal& edgeVal);
    bool removeEdge (int from, int to, const TEdgeVal& edgeVal);
    bool removeDirectEdges (int from, int to);

    void unionDAG (const DAG<TEdgeVal>& other);

    bool isEdgeExist (int from, int to, const TEdgeVal& syl) const;
    int  outDegree (int from) const;
    int  inDegree (int to) const;

    std::pair<ConstEdgeIter, ConstEdgeIter> outEdges (int from) const;
    std::pair<ConstEdgeIter, ConstEdgeIter> inEdges (int to) const;

    EdgeIter      outBegin();
    ConstEdgeIter outBegin() const;
    EdgeIter      outEnd();
    ConstEdgeIter outEnd() const;

    EdgeIter      inBegin();
    ConstEdgeIter inBegin() const;
    EdgeIter      inEnd();
    ConstEdgeIter inEnd() const;

private:
    std::multimap<int, DAGEdge<TEdgeVal>> mFrom;
    std::multimap<int, DAGEdge<TEdgeVal>> mTo;
};

#include "dag.inl"

#endif  // DAG_H

/*
vi:ts=4:ai:expandtab
*/
