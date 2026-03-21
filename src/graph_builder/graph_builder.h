#ifndef GRAPH_BUILDER_H
#define GRAPH_BUILDER_H

#include "../data.h"
#include "../graphs/Graph.h"
#include <vector>

using namespace std;

int getMatchDomain(const Reviewer &r, const Submission &s, const Control &control);

bool isCompatible(const Reviewer &r, const Submission &s, const Control &control);

Graph<int>* buildGraph(vector<Submission> &submissions,
                       vector<Reviewer> &reviewers,
                       Parameters &params,
                       Control &control,
                       int &source,
                       int &sink);

#endif