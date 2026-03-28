#ifndef PROJECT1_EDMONDSKARP_H
#define PROJECT1_EDMONDSKARP_H

#include "Graph.h"

/**
 * @file edmondsKarp.h
 * @brief Implementation of the Edmonds-Karp maximum flow algorithm.
 */

/**
 * @brief Computes the maximum flow in a graph using the Edmonds-Karp algorithm.
 *
 * Edmonds-Karp uses BFS to find
 * augmenting paths, guaranteeing polynomial time complexity. It repeatedly
 * finds the shortest augmenting path from source to sink and augments flow
 * along it until no augmenting path exists.
 *
 * @param g Pointer to the flow graph. All edge flows are reset to zero before execution.
 * @param source Index of the source vertex.
 * @param sink Index of the sink vertex.
 *
 * @note Complexity: O(V * E^2) where V is the number of vertices and E is the number of edges.
 */
void edmondsKarp(Graph<int>* g, int source, int sink);

#endif //PROJECT1_EDMONDSKARP_H