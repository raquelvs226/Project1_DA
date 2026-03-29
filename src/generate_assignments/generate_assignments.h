#ifndef PROJECT1_GENERATE_ASSIGNMENTS_H
#define PROJECT1_GENERATE_ASSIGNMENTS_H

#include "../data.h"
#include "../graphs/Graph.h"
#include <vector>

/**
 * @file generate_assignments.h
 * @brief Functions for extracting review assignments from a max-flow solution.
 */

/**
 * @struct Assignment
 * @brief Represents a single reviewer-to-submission assignment.
 */
struct Assignment {
    int submissionId; ///< ID of the submission being reviewed
    int reviewerId;   ///< ID of the reviewer assigned to it
    int matchDomain;  ///< Domain through which the match was made
};

/**
 * @brief Extracts the list of reviewer-submission assignments from the flow graph.
 *
 * Iterates over all reviewer nodes in the graph and collects edges with
 * positive flow, mapping them back to the original submission and reviewer IDs.
 *
 * @param g Pointer to the flow graph after running Edmonds-Karp.
 * @param submissions List of all submissions.
 * @param reviewers List of all reviewers.
 * @param firstReviewerNode Graph node index of the first reviewer.
 * @param firstSubmissionNode Graph node index of the first submission.
 * @return Vector of Assignment structs representing the final assignment.
 *
 * @note Complexity: O(R * S) where R is the number of reviewers and S is the number of submissions.
 */
std::vector<Assignment> extractAssignments(
    Graph<int>* g,
    const std::vector<Submission>& submissions,
    const std::vector<Reviewer>& reviewers,
    int firstReviewerNode,
    int firstSubmissionNode);

#endif // PROJECT1_GENERATE_ASSIGNMENTS_H