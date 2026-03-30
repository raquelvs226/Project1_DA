#ifndef PROJECT1_MATCHING_H
#define PROJECT1_MATCHING_H

#include "../data.h"

/**
 * @file matching.h
 * @brief Functions for determining compatibility between reviewers and submissions.
 */

/**
 * @brief Determines the domain through which a reviewer matches a submission.
 *
 * A reviewer is considered compatible with a submission according to the
 * enabled matching rules in `Parameters`:
 * - If `PrimaryReviewerExpertise` and `PrimarySubmissionDomain` are enabled,
 *   the reviewer's primary domain is compared with the submission's primary domain.
 * - If `PrimaryReviewerExpertise` and `SecondarySubmissionDomain` are enabled,
 *   the reviewer's primary domain is compared with the submission's secondary domain
 *   when that secondary domain exists (`s.secondary != -1`).
 *
 * @param r The reviewer being evaluated.
 * @param s The submission being evaluated.
 * @param control Execution control options.
 * @param params Configuration parameters that define which matching rules are enabled.
 * @return The matched domain ID if the reviewer is compatible with the submission,
 *         or -1 if no valid match exists.
 */
int getMatchDomain(const Reviewer &r, const Submission &s, const Control &control, const Parameters &params);

/**
 * @brief Checks whether a reviewer is compatible with a submission.
 *
 * This is a convenience wrapper around getMatchDomain().
 *
 * @param r The reviewer being evaluated.
 * @param s The submission being evaluated.
 * @param control Execution control options.
 * @param params Configuration parameters that define which matching rules are enabled.
 * @return true if the reviewer is compatible with the submission, false otherwise.
 */
bool isCompatible(const Reviewer &r, const Submission &s, const Control &control, const Parameters &params);

#endif // PROJECT1_MATCHING_H