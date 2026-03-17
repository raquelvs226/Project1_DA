#ifndef GRAPH_BUILDER_H
#define GRAPH_BUILDER_H

#include "../data.h"
#include "../graphs/Graph.h"
#include <vector>

using namespace std;

Graph<int>* buildGraph(vector<Submission> &submissions,
                       vector<Reviewer> &reviewers,
                       Parameters &params,
                       int &source,
                       int &sink);

#endif