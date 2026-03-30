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
 * Orchestrates the complete workflow in the following order:
 * -# Builds the max-flow graph with buildGraph().
 * -# Computes the maximum flow with edmondsKarp().
 * -# Extracts assignments with extractAssignments().
 * -# Performs risk analysis with getRiskyReviewers() if enabled.
 * -# Writes the results to a CSV file with writeOutputCSV().
 *
 * The output file name is determined as follows:
 * - If @p outputPathOverride is non-empty, it is used as the output file name.
 * - Otherwise, control.OutputFileName is used.
 *
 * The final output path is then constructed automatically:
 * - "../../results/" for normal execution
 * - "../../results/risk/" when only risk analysis is performed
 *
 * @param submissions List of submissions.
 * @param reviewers List of reviewers.
 * @param params Problem parameters.
 * @param control Execution control options.
 * @param outputPathOverride Optional output file name override. If non-empty,
 *        it replaces control.OutputFileName, but the output directory is still
 *        determined automatically by the pipeline.
 *
 * @note Complexity: O(R * V * E^2), where R is the number of reviewers
 * considered during risk analysis, V is the number of graph vertices, and
 * E is the number of graph edges. Without risk analysis, the complexity is
 * O(V * E^2).
 */
void runPipeline(
    std::vector<Submission>& submissions,
    std::vector<Reviewer>& reviewers,
    Parameters& params,
    Control& control,
    const std::string& outputPathOverride = "");

#endif // PROJECT1_PIPELINE_H