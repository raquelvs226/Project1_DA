#include "output_writer.h"

#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

void writeOutputCSV(const string &filename,
                    Graph<int> *g,
                    vector<Submission> &submissions,
                    vector<Reviewer> &reviewers,
                    Parameters &params,
                    Control &control) {

    ofstream file(filename);

    int numReviewers = reviewers.size();
    int numSubmissions = submissions.size();
    int firstReviewerNode = 1;
    int firstSubmissionNode = 1 + numReviewers;

    vector<int> receivedReviews(numSubmissions, 0);
    vector<tuple<int, int, int>> assignments;

    for (int reviewerIndex = 0; reviewerIndex < numReviewers; reviewerIndex++) {
        int reviewerNode = firstReviewerNode + reviewerIndex;
        Vertex<int> *v = g->findVertex(reviewerNode);

        for (auto e : v->getAdj()) {
            int dest = e->getDest()->getInfo();

            if (dest >= firstSubmissionNode &&
                dest < firstSubmissionNode + numSubmissions &&
                e->getFlow() > 0) {

                int submissionIndex = dest - firstSubmissionNode;

                Submission &s = submissions[submissionIndex];
                Reviewer &r = reviewers[reviewerIndex];

                int submissionId = s.id;
                int reviewerId = r.id;
                int matchDomain = -1;

                int mode = control.GenerateAssignments;
                if (mode == 0) {
                    mode = 3;
                }

                if (mode == 1) {
                    if (r.primary == s.primary) {
                        matchDomain = s.primary;
                    }
                }
                else if (mode == 2) {
                    if (r.primary == s.primary) {
                        matchDomain = s.primary;
                    }
                    else if (s.secondary != -1 && r.primary == s.secondary) {
                        matchDomain = s.secondary;
                    }
                }
                else if (mode == 3) {
                    if (r.primary == s.primary) {
                        matchDomain = s.primary;
                    }
                    else if (s.secondary != -1 && r.primary == s.secondary) {
                        matchDomain = s.secondary;
                    }
                    else if (r.secondary != -1 && r.secondary == s.primary) {
                        matchDomain = s.primary;
                    }
                    else if (r.secondary != -1 && s.secondary != -1 && r.secondary == s.secondary) {
                        matchDomain = s.secondary;
                    }
                }

                assignments.push_back({submissionId, reviewerId, matchDomain});
                receivedReviews[submissionIndex] += (int)e->getFlow();
            }
        }
    }

    vector<tuple<int, int, int>> assignmentsBySubmission = assignments;
    vector<tuple<int, int, int>> assignmentsByReviewer = assignments;

    sort(assignmentsBySubmission.begin(), assignmentsBySubmission.end(),
         [](const tuple<int, int, int> &a, const tuple<int, int, int> &b) {
             if (get<0>(a) != get<0>(b)) {
                 return get<0>(a) < get<0>(b);
             }
             return get<1>(a) < get<1>(b);
         });

    sort(assignmentsByReviewer.begin(), assignmentsByReviewer.end(),
         [](const tuple<int, int, int> &a, const tuple<int, int, int> &b) {
             if (get<1>(a) != get<1>(b)) {
                 return get<1>(a) < get<1>(b);
             }
             return get<0>(a) < get<0>(b);
         });

    file << "#SubmissionId,ReviewerId,Match\n";
    for (auto &a : assignmentsBySubmission) {
        file << get<0>(a) << ", " << get<1>(a) << ", " << get<2>(a) << "\n";
    }

    file << "#ReviewerId,SubmissionId,Match\n";
    for (auto &a : assignmentsByReviewer) {
        file << get<1>(a) << ", " << get<0>(a) << ", " << get<2>(a) << "\n";
    }

    file << "#Total: " << assignments.size() << "\n";

    bool hasMissingReviews = false;
    for (int i = 0; i < numSubmissions; i++) {
        if (receivedReviews[i] < params.MinReviewsPerSubmission) {
            hasMissingReviews = true;
            break;
        }
    }

    if (hasMissingReviews) {
        file << "#SubmissionId,Domain,MissingReviews\n";

        for (int i = 0; i < numSubmissions; i++) {
            if (receivedReviews[i] < params.MinReviewsPerSubmission) {
                int missing = params.MinReviewsPerSubmission - receivedReviews[i];
                file << submissions[i].id << ", " << submissions[i].primary << ", " << missing << "\n";
            }
        }
    }

    file.close();
}