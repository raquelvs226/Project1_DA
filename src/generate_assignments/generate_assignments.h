#ifndef PROJECT1_GENERATE_ASSIGNMENTS_H
#define PROJECT1_GENERATE_ASSIGNMENTS_H

#include "../data.h"
#include "../graphs/Graph.h"
#include <vector>

struct Assignment {
    int submissionId;
    int reviewerId;
    int matchDomain;
};

std::vector<Assignment> extractAssignments(
    Graph<int>* g,
    const std::vector<Submission>& submissions,
    const std::vector<Reviewer>& reviewers,
    int firstReviewerNode,
    int firstSubmissionNode);

std::vector<int> countReceivedReviews(
    const std::vector<Assignment>& assignments,
    const std::vector<Submission>& submissions);

#endif // PROJECT1_GENERATE_ASSIGNMENTS_H