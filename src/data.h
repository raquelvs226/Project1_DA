#ifndef PROJECT1_DATA_H
#define PROJECT1_DATA_H

#include <string>

/**
 * @file data.h
 * @brief Core data structures used throughout the conference assignment tool.
 */

/**
 * @struct Submission
 * @brief Represents a paper submission to the conference.
 *
 * Each submission has identifying information and one mandatory
 * primary domain plus an optional secondary domain.
 *
 * @param id Unique identifier of the submission.
 * @param title Title of the paper.
 * @param authors Author(s) of the paper.
 * @param email Contact email of the author(s).
 * @param primary Primary domain/topic of the submission.
 * @param secondary Secondary domain/topic (-1 if undefined).
 */
struct Submission {
    int id;
    std::string title;
    std::string authors;
    std::string email;
    int primary;
    int secondary;
};

/**
 * @struct Reviewer
 * @brief Represents a reviewer responsible for evaluating submissions.
 *
 * Reviewers have expertise in one mandatory primary domain
 * and optionally a secondary domain.
 *
 * @param id Unique identifier of the reviewer.
 * @param name Reviewer's full name.
 * @param email Contact email of the reviewer.
 * @param primary Primary expertise domain.
 * @param secondary Secondary expertise domain (-1 if undefined).
 */
struct Reviewer {
    int id;
    std::string name;
    std::string email;
    int primary;
    int secondary;
};

/**
 * @struct Parameters
 * @brief Configuration parameters that control assignment constraints.
 *
 * These values define the limits for review assignments and
 * how domains are considered when matching submissions with reviewers.
 *
 * @param MinReviewsPerSubmission Minimum number of reviews required per submission.
 * @param MaxReviewsPerReviewer Maximum number of reviews a reviewer can perform.
 * @param PrimaryReviewerExpertise Flag controlling use of primary reviewer expertise.
 * @param SecondaryReviewerExpertise Flag controlling use of secondary reviewer expertise.
 * @param PrimarySubmissionDomain Flag controlling use of primary submission domain.
 * @param SecondarySubmissionDomain Flag controlling use of secondary submission domain.
 */
struct Parameters {
    int MinReviewsPerSubmission;
    int MaxReviewsPerReviewer;
    int PrimaryReviewerExpertise;
    int SecondaryReviewerExpertise;
    int PrimarySubmissionDomain;
    int SecondarySubmissionDomain;
};

/**
 * @struct Control
 * @brief Execution control options for the program.
 *
 * These parameters determine whether assignments are generated,
 * whether risk analysis is performed, and the output file name.
 *
 * @param GenerateAssignments Assignment generation mode (0 = run but do not report,
 *        1 = primary domains only, 2 = primary reviewer vs primary+secondary submission).
 * @param RiskAnalysis Risk analysis mode (0 = none, 1 = single reviewer removal).
 * @param OutputFileName Name of the output file.
 */
struct Control {
    int GenerateAssignments;
    int RiskAnalysis;
    std::string OutputFileName;
};

#endif //PROJECT1_DATA_H
