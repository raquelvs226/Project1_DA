#ifndef PROJECT1_GENERATE_ANALYSIS_H
#define PROJECT1_GENERATE_ANALYSIS_H

#include "../data.h"

/**
 * @file matching.h
 * @brief Functions for determining compatibility between reviewers and submissions.
 */

/**
 * @brief Determines the domain through which a reviewer matches a submission.
 *
 * The matching rules depend on the GenerateAssignments mode in the Control struct:
 * - Mode 0 or 1: Only primary reviewer expertise vs primary submission domain.
 * - Mode 2: Primary reviewer expertise vs primary or secondary submission domain.
 *
 * @param r The reviewer.
 * @param s The submission.
 * @param control Execution control options containing the assignment mode.
 * @return The matched domain ID if compatible, or -1 if there is no match.
 *
 * @note Complexity:O(1)
 */
int getMatchDomain(const Reviewer &r, const Submission &s, const Control &control);

/**
 * @brief Checks whether a reviewer is compatible with a submission.
 *
 * A convenience wrapper around getMatchDomain() that returns a boolean.
 *
 * @param r The reviewer.
 * @param s The submission.
 * @param control Execution control options containing the assignment mode.
 * @return true if the reviewer can review the submission, false otherwise.
 *
 * @note Complexity: O(1)
 */
bool isCompatible(const Reviewer &r, const Submission &s, const Control &control);

#endif //PROJECT1_GENERATE_ANALYSIS_H