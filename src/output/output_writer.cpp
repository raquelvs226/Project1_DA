#include "output_writer.h"
#include "graph_builder/graph_builder.h"

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

    for (int i = 0; i < numReviewers; i++) {
        Vertex<int> *v = g->findVertex(firstReviewerNode + i);

            for (auto e : v->getAdj()) {
                int dest = e->getDest()->getInfo();

                if (dest < firstSubmissionNode || dest >= firstSubmissionNode + numSubmissions)
                    continue;
                if (e->getFlow() <= 0)
                    continue;

                int j = dest - firstSubmissionNode;
                int matchDomain = getMatchDomain(reviewers[i], submissions[j], control);

                assignments.push_back({submissions[j].id, reviewers[i].id, matchDomain});
                receivedReviews[j] += (int)e->getFlow();
        }
    }

    auto bySubmission = assignments;
    sort(bySubmission.begin(), bySubmission.end(),
         [](const auto &a, const auto &b) {
             return get<0>(a) != get<0>(b) ? get<0>(a) < get<0>(b) : get<1>(a) < get<1>(b);
         });

    auto byReviewer = assignments;
    sort(byReviewer.begin(), byReviewer.end(),
         [](const auto &a, const auto &b) {
             return get<1>(a) != get<1>(b) ? get<1>(a) < get<1>(b) : get<0>(a) < get<0>(b);
         });

    file << "#SubmissionId,ReviewerId,Match\n";
    for (auto &[subId, revId, match] : bySubmission) {
        file << subId << ", " << revId << ", " << match << "\n";
    }

    file << "#ReviewerId,SubmissionId,Match\n";
    for (auto &[subId, revId, match] : byReviewer) {
        file << revId << ", " << subId << ", " << match << "\n";
    }

    file << "#Total: " << assignments.size() << "\n";

    bool hasMissing = false;
    for (int i = 0; i < numSubmissions; i++) {
        if (receivedReviews[i] < params.MinReviewsPerSubmission) {
            hasMissing = true;
            break;
        }
    }

    if (hasMissing) {
        file << "#SubmissionId,Domain,MissingReviews\n";
        for (int i = 0; i < numSubmissions; i++) {
            if (receivedReviews[i] < params.MinReviewsPerSubmission) {
                file << submissions[i].id << ", " << submissions[i].primary << ", "
                << params.MinReviewsPerSubmission - receivedReviews[i] << "\n";
            }
        }
    }

    file.close();
}