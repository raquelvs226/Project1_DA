#include "generate_assignments.h"

std::vector<Assignment> extractAssignments(
    Graph<int>* g,
    const std::vector<Submission>& submissions,
    const std::vector<Reviewer>& reviewers,
    int firstReviewerNode,
    int firstSubmissionNode)
{
    std::vector<Assignment> result;

    int numReviewers   = static_cast<int>(reviewers.size());
    int numSubmissions = static_cast<int>(submissions.size());

    for (int i = 0; i < numReviewers; i++) {
        Vertex<int>* v = g->findVertex(firstReviewerNode + i);
        if (!v) continue;

        for (auto* e : v->getAdj()) {
            if (e->getFlow() <= 0) continue;

            int dest = e->getDest()->getInfo();
            int j    = dest - firstSubmissionNode;

            if (j < 0 || j >= numSubmissions) continue;

            Assignment a;
            a.submissionId = submissions[j].id;
            a.reviewerId   = reviewers[i].id;
            a.matchDomain  = e->getMatchDomain();
            result.push_back(a);
        }
    }

    return result;
}

std::vector<int> countReceivedReviews(
    const std::vector<Assignment>& assignments,
    const std::vector<Submission>& submissions)
{
    std::vector<int> counts(submissions.size(), 0);

    for (const auto& a : assignments) {
        for (int j = 0; j < static_cast<int>(submissions.size()); j++) {
            if (submissions[j].id == a.submissionId) {
                counts[j]++;
                break;
            }
        }
    }

    return counts;
}