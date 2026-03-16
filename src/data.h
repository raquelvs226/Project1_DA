#ifndef PROJECT1_DATA_H
#define PROJECT1_DATA_H

#include <string>

/**
 * @struct Submission
 * @brief Represents a paper submission to the conference.
 *
 * Each submission has identifying information and one mandatory
 * primary domain plus an optional secondary domain.
 */
struct Submission {
    int id;                 ///< Unique identifier of the submission
    std::string title;      ///< Title of the paper
    std::string authors;    ///< Author(s) of the paper
    std::string email;      ///< Contact email of the author(s)
    int primary;            ///< Primary domain/topic of the submission
    int secondary;          ///< Secondary domain/topic (-1 if undefined)
};

/**
 * @struct Reviewer
 * @brief Represents a reviewer responsible for evaluating submissions.
 *
 * Reviewers have expertise in one mandatory primary domain
 * and optionally a secondary domain.
 */
struct Reviewer {
    int id;                 ///< Unique identifier of the reviewer
    std::string name;       ///< Reviewer's name
    std::string email;      ///< Contact email
    int primary;            ///< Primary expertise domain
    int secondary;          ///< Secondary expertise domain (-1 if undefined)
};

/**
 * @struct Parameters
 * @brief Configuration parameters that control assignment constraints.
 *
 * These values define the limits for review assignments and
 * how domains are considered when matching submissions with reviewers.
 */
struct Parameters {
    int MinReviewsPerSubmission;     ///< Minimum required reviews per submission
    int MaxReviewsPerReviewer;       ///< Maximum reviews a reviewer can perform
    int PrimaryReviewerExpertise;    ///< Flag/weight for primary reviewer expertise
    int SecondaryReviewerExpertise;  ///< Flag/weight for secondary reviewer expertise
    int PrimarySubmissionDomain;     ///< Flag controlling use of primary submission domain
    int SecondarySubmissionDomain;   ///< Flag controlling use of secondary submission domain
};

/**
 * @struct Control
 * @brief Execution control options for the program.
 *
 * These parameters determine whether assignments are generated,
 * whether risk analysis is performed, and the output file name.
 */
struct Control {
    int GenerateAssignments; ///< Assignment generation mode
    int RiskAnalysis;        ///< Risk analysis mode
    std::string OutputFileName; ///< Name of the output file
};

#endif //PROJECT1_DATA_H

