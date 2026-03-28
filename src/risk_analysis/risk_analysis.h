#ifndef PROJECT1_RISK_ANALYSIS_H
#define PROJECT1_RISK_ANALYSIS_H

#include "../data.h"
#include <vector>

/**
 * @file risk_analysis.h
 * @brief Function for identifying critical reviewers in the assignment.
 */

/**
 * @brief Identifies reviewers whose absence would make a full assignment impossible.
 *
 * For each reviewer, temporarily removes them from the reviewer pool and checks
 * whether a feasible assignment (satisfying MinReviewsPerSubmission for all
 * submissions) can still be found by running Edmonds-Karp on the reduced graph.
 * If removal of a reviewer makes the assignment infeasible, that reviewer is
 * considered "risky" and their ID is added to the result.
 *
 * Only executes when control.RiskAnalysis == 1 and the base assignment
 * (with all reviewers present) is itself feasible.
 *
 * @param submissions List of all submissions.
 * @param reviewers List of all reviewers.
 * @param params Problem parameters (used to check feasibility thresholds).
 * @param control Execution control options (must have RiskAnalysis == 1).
 * @return Sorted vector of IDs of reviewers whose removal breaks feasibility.
 *         Returns an empty vector if RiskAnalysis != 1 or the base case is infeasible.
 *
 * @complexity O(R * V * E^2) where R is the number of reviewers, V is the number
 * of graph vertices, and E is the number of edges. Each of the R iterations
 * rebuilds and solves the flow problem in O(V * E^2).
 */
std::vector<int> getRiskyReviewers(
    std::vector<Submission>& submissions,
    std::vector<Reviewer>& reviewers,
    Parameters& params,
    Control& control);

#endif // PROJECT1_RISK_ANALYSIS_H