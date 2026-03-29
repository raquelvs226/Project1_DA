#ifndef OUTPUT_WRITER_H
#define OUTPUT_WRITER_H

#include "../data.h"
#include "../generate_assignments/generate_assignments.h"
#include <string>
#include <vector>

/**
 * @file output_writer.h
 * @brief Function for writing the assignment and risk analysis results to a CSV file.
 */

/**
 * @brief Writes the assignment results and risk analysis output to a CSV file.
 *
 * The output format depends on the control parameters:
 * - If GenerateAssignments != 0: writes the submission-to-reviewer mapping
 *   (sorted by submission ID), the reviewer-to-submission mapping (sorted by
 *   reviewer ID), the total count, and any missing reviews.
 * - If RiskAnalysis == 1: appends a risk analysis section listing the IDs of
 *   reviewers whose absence would make a full assignment impossible.
 *
 * @param filename Path to the output file to be created or overwritten.
 * @param assignments List of reviewer-submission assignments to report.
 * @param riskyReviewers List of reviewer IDs identified as critical.
 * @param submissions List of all submissions (used for missing review reporting).
 * @param reviewers List of all reviewers.
 * @param params Problem parameters (used to determine MinReviewsPerSubmission).
 * @param control Execution control options (determines which sections to write).
 *
 */
void writeOutputCSV(
    const std::string& filename,
    const std::vector<Assignment>& assignments,
    const std::vector<int>& riskyReviewers,
    std::vector<Submission>& submissions,
    std::vector<Reviewer>& reviewers,
    Parameters& params,
    Control& control);

#endif // OUTPUT_WRITER_H