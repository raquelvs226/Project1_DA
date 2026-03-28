#ifndef GRAPH_BUILDER_H
#define GRAPH_BUILDER_H

#include "../data.h"
#include "../graphs/Graph.h"
#include <vector>

using namespace std;

/**
 * @file graph_builder.h
 * @brief Function for constructing the max-flow graph from the problem data.
 */

/**
 * @brief Builds the max-flow network graph for the review assignment problem.
 *
 * Constructs a directed flow graph with the following structure:
 * - A single source node connected to each reviewer node with capacity MaxReviewsPerReviewer.
 * - Each reviewer node connected to compatible submission nodes with capacity 1.
 * - Each submission node connected to the sink with capacity MinReviewsPerSubmission.
 *
 * Compatibility between a reviewer and a submission is determined by the
 * GenerateAssignments mode in the Control struct.
 *
 * @param submissions List of paper submissions.
 * @param reviewers List of available reviewers.
 * @param params Problem parameters (min/max review counts, domain flags).
 * @param control Execution control options (assignment mode, risk analysis mode).
 * @param source Output parameter set to the source node index.
 * @param sink Output parameter set to the sink node index.
 * @return Pointer to the newly allocated Graph. Caller is responsible for deletion.
 *
 * @note Complexity: O(R * S) where R is the number of reviewers and S is the number of submissions.
 */
Graph<int>* buildGraph(vector<Submission> &submissions,
                       vector<Reviewer> &reviewers,
                       Parameters &params,
                       Control &control,
                       int &source,
                       int &sink);

#endif