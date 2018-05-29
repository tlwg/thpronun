// pron-dag.h - Directed Acyclic Graph representing possible pronunciations
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-05-11

#ifndef PRON_DAG_H
#define PRON_DAG_H

#include "dag.h"
#include "sylstring/sylstring.h"
#include "lattice.h"

#include <list>

class FracDAG : public DAG<PronunFrac> {
    friend class PronunDAG;

public:
    FracDAG();
    FracDAG (FracDAG&& other);

    PronunLatt lattice() const;

private:
    // Exclusive for PronunDAG
    void mergeFractions();

    // Helpers for mergeFractions()
    void mergeSingles();
    void mergeParallels();

    // Helper for lattice()
    PronunLatt nodeLattice (int from) const;
};

class PronunDAG : public DAG<Syl> {
public:
    PronunDAG();
    PronunDAG (const std::list<SylString> sylStrings);

    void addSylString (int pos, const SylString& sylString);

    FracDAG fracDAG() const;
};

#endif  // PRON_DAG_H

/*
vi:ts=4:ai:expandtab
*/
