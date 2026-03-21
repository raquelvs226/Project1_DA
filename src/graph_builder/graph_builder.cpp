#include "graph_builder.h"
#include "../matching/matching.h"

Graph<int>* buildGraph(vector<Submission> &submissions,
                       vector<Reviewer> &reviewers,
                       Parameters &params,
                       Control &control,
                       int &source,
                       int &sink) {

    auto g = new Graph<int>();
    int id = 0;

    source = id++;
    g->addVertex(source);

    vector<int> reviewerNodes;
    for (auto &r : reviewers) {
        g->addVertex(id);
        reviewerNodes.push_back(id);
        g->addEdge(source, id, params.MaxReviewsPerReviewer);
        id++;
    }

    vector<int> submissionNodes;
    for (auto &s : submissions) {
        g->addVertex(id);
        submissionNodes.push_back(id);
        id++;
    }

    sink = id;
    g->addVertex(sink);

    for (int subNode : submissionNodes) {
        g->addEdge(subNode, sink, params.MinReviewsPerSubmission);
    }

    for (int i = 0; i < reviewers.size(); i++) {
        for (int j = 0; j < submissions.size(); j++) {
            if (isCompatible(reviewers[i], submissions[j], control)) {
                g->addEdge(reviewerNodes[i], submissionNodes[j], 1);
            }
        }
    }

    return g;
}