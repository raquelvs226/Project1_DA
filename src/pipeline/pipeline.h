#ifndef PROJECT1_PIPELINE_H
#define PROJECT1_PIPELINE_H

#include "../data.h"
#include "../generate_assignments/generate_assignments.h"
#include <string>
#include <vector>

/**
 * @file pipeline.h
 * @brief Orchestration of the full assignment and risk analysis pipeline.
 */

/**
 * @brief Runs the full review assignment pipeline.
 *
 * Orchestrates the complete workflow in order:
 * -# Build the max-flow graph with buildGraph().
 * -# Compute maximum flow with edmondsKarp().
 * -# Extract assignments with extractAssignments() (if GenerateAssignments != 0).
 * -# Perform risk analysis with getRiskyReviewers() (if RiskAnalysis == 1).
 * -# Write results to file with writeOutputCSV().
 *
 * In batch mode, @p outputPathOverride is used as the exact output path.
 * In interactive menu mode, the path is derived from control.OutputFileName
 * using a relative path convention.
 *
 * @param submissions List of paper submissions.
 * @param reviewers List of available reviewers.
 * @param params Problem parameters.
 * @param control Execution control options.
 * @param outputPathOverride If non-empty, overrides the output file path entirely
 *        (used in batch mode). Defaults to empty string.
 *
 * @note Complexity: O(R * V * E^2) where R is the number of reviewers (risk analysis
 * iterations), V is the number of graph vertices, and E is the number of edges.
 * Without risk analysis the complexity is O(V * E^2).
 */
void runPipeline(
    std::vector<Submission>& submissions,
    std::vector<Reviewer>& reviewers,
    Parameters& params,
    Control& control,
    const std::string& outputPathOverride = "");

#endif //PROJECT1_PIPELINE_H