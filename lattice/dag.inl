// dag.inl - Generic Directed Acyclic Graph template class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-11

////////////////////////////////
//  template class DAGEdge<>  //
////////////////////////////////

template<typename TEdgeVal>
DAGEdge<TEdgeVal>::DAGEdge()
    : target (0), edgeVal() {}

template<typename TEdgeVal>
DAGEdge<TEdgeVal>::DAGEdge (int target, const TEdgeVal& edgeVal)
    : target (target), edgeVal (edgeVal) {}

template<typename TEdgeVal>
DAGEdge<TEdgeVal>::DAGEdge (const DAGEdge& other)
    : target (other.target), edgeVal (other.edgeVal) {}

template<typename TEdgeVal>
DAGEdge<TEdgeVal>::DAGEdge (DAGEdge&& other)
    : target (std::move (other.target)), edgeVal (std::move (other.edgeVal)) {}


////////////////////////////
//  template class DAG<>  //
////////////////////////////

template<typename TEdgeVal>
DAG<TEdgeVal>::DAG()
    : mFrom(), mTo() {}

template<typename TEdgeVal>
DAG<TEdgeVal>::DAG (const DAG<TEdgeVal>& other)
    : mFrom (other.mFrom), mTo (other.mTo) {}

template<typename TEdgeVal>
DAG<TEdgeVal>::DAG (DAG<TEdgeVal>&& other)
    : mFrom (std::move (other.mFrom)), mTo (std::move (other.mTo)) {}

template<typename TEdgeVal>
bool
DAG<TEdgeVal>::isEdgeExist (int from, int to, const TEdgeVal& edgeVal) const
{
    auto range = mFrom.equal_range (from);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second.target == to && it->second.edgeVal == edgeVal) {
            return true;
        }
    }

    return false;
}

template<typename TEdgeVal>
int
DAG<TEdgeVal>::outDegree (int from) const
{
    return mFrom.count (from);
}

template<typename TEdgeVal>
int
DAG<TEdgeVal>::inDegree (int to) const
{
    return mTo.count (to);
}

template<typename TEdgeVal>
std::pair<typename DAG<TEdgeVal>::ConstEdgeIter,
          typename DAG<TEdgeVal>::ConstEdgeIter>
DAG<TEdgeVal>::outEdges (int from) const
{
    return mFrom.equal_range (from);
}

template<typename TEdgeVal>
std::pair<typename DAG<TEdgeVal>::ConstEdgeIter,
          typename DAG<TEdgeVal>::ConstEdgeIter>
DAG<TEdgeVal>::inEdges (int to) const
{
    return mTo.equal_range (to);
}

template<typename TEdgeVal>
typename DAG<TEdgeVal>::EdgeIter
DAG<TEdgeVal>::outBegin()
{
    return mFrom.begin();
}

template<typename TEdgeVal>
typename DAG<TEdgeVal>::ConstEdgeIter
DAG<TEdgeVal>::outBegin() const
{
    return mFrom.begin();
}

template<typename TEdgeVal>
typename DAG<TEdgeVal>::EdgeIter
DAG<TEdgeVal>::outEnd()
{
    return mFrom.end();
}

template<typename TEdgeVal>
typename DAG<TEdgeVal>::ConstEdgeIter
DAG<TEdgeVal>::outEnd() const
{
    return mFrom.end();
}

template<typename TEdgeVal>
typename DAG<TEdgeVal>::EdgeIter
DAG<TEdgeVal>::inBegin()
{
    return mTo.begin();
}

template<typename TEdgeVal>
typename DAG<TEdgeVal>::ConstEdgeIter
DAG<TEdgeVal>::inBegin() const
{
    return mTo.begin();
}

template<typename TEdgeVal>
typename DAG<TEdgeVal>::EdgeIter
DAG<TEdgeVal>::inEnd()
{
    return mTo.end();
}

template<typename TEdgeVal>
typename DAG<TEdgeVal>::ConstEdgeIter
DAG<TEdgeVal>::inEnd() const
{
    return mTo.end();
}

template<typename TEdgeVal>
bool
DAG<TEdgeVal>::addEdge (int from, int to, const TEdgeVal& edgeVal)
{
    if (isEdgeExist (from, to, edgeVal)) {
        return false;
    }

    mFrom.emplace (from, DAGEdge<TEdgeVal> (to, edgeVal));
    mTo.emplace (to, DAGEdge<TEdgeVal> (from, edgeVal));
    return true;
}

template<typename TEdgeVal>
bool
DAG<TEdgeVal>::removeEdge (int from, int to, const TEdgeVal& edgeVal)
{
    bool isRemoved = false;

    auto range = mFrom.equal_range (from);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second.target == to && it->second.edgeVal == edgeVal) {
            mFrom.erase (it);
            isRemoved = true;
            break;
        }
    }

    range = mTo.equal_range (to);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second.target == from && it->second.edgeVal == edgeVal) {
            mTo.erase (it);
            isRemoved = true;
            break;
        }
    }

    return isRemoved;
}

/*
vi:ts=4:ai:expandtab
*/
