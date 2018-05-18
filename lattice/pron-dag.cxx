// pron-dag.cxx - Directed Acyclic Graph representing possible pronunciations
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-11

#include "pron-dag.h"

#include <utility>

using namespace std;

/////////////////////
//  class FracDAG  //
/////////////////////

FracDAG::FracDAG()
    : DAG<PronunFrac>()
{
}

FracDAG::FracDAG(FracDAG&& other)
    : DAG<PronunFrac> (move (other))
{
}

void
FracDAG::mergeSingles()
{
    for (auto it = outBegin(); it != outEnd(); /* noop */) {
        if (outDegree (it->first) == 1 && inDegree (it->first) == 1) {
            // find preceeding & succeeding nodes and merged SylString
            auto inIt = inEdges (it->first).first;
            int srcNode = inIt->second.target;
            int dstNode = it->second.target;
            SylString mergedStr = *inIt->second.edgeVal.begin();
            mergedStr += *it->second.edgeVal.begin();

            // remove old edges & add the merged one
            removeEdge (srcNode, it->first, inIt->second.edgeVal);
            removeEdge (it->first, dstNode, it->second.edgeVal);
            addEdge (srcNode, dstNode, PronunFrac (dstNode, mergedStr));

            // 'it' is now inaccessible -> reset it
            it = outBegin();
        } else {
            ++it;
        }
    }
}

void
FracDAG::mergeParallels()
{
    for (auto it = outBegin(); it != outEnd(); ++it) {
        int from = it->first;
        int to = it->second.target;

        // skip node already merged
        if (outDegree (from) == 1)
            continue;

        // Merge fractions for paths from 'from' to 'to'
        PronunFrac mergedFrac;
        int        edgeCount = 0;
        auto range = outEdges (from);
        for (auto outIt = range.first; outIt != range.second; ++outIt) {
            if (outIt->second.target == to) {
                mergedFrac += outIt->second.edgeVal;
                ++edgeCount;
            }
        }
        if (edgeCount > 1) {
            removeDirectEdges (from, to);
            addEdge (from, to, mergedFrac);

            // 'it' is now inaccessible -> reset it
            // (loop increment is OK, as first node is always done)
            it = outBegin();
        }
    }
}

///////////////////////
//  class PronunDAG  //
///////////////////////

PronunDAG::PronunDAG()
    : DAG<Syl>()
{
}

PronunDAG::PronunDAG (const std::list<SylString> sylStrings)
    : DAG<Syl>()
{
    for (const auto& sylString : sylStrings) {
        int from = 0;
        for (const auto& syl : sylString) {
            addEdge (from, syl.endPos(), syl);
            from = syl.endPos();
        }
    }
}

FracDAG
PronunDAG::fracDAG() const
{
    FracDAG fDAG;

    for (auto it = outBegin(); it != outEnd(); ++it) {
        fDAG.addEdge (
            it->first, it->second.target,
            PronunFrac (it->second.target, SylString (it->second.edgeVal))
        );
    }

    return fDAG;
}

/*
vi:ts=4:ai:expandtab
*/
