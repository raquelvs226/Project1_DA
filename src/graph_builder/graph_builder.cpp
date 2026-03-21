#include "graph_builder.h"

int getMatchDomain(const Reviewer &r, const Submission &s, const Control &control) {

    // Mode 1: Primary ↔ Primary
    if (control.GenerateAssignments == 1) {
        if (r.primary == s.primary)
            return s.primary;
    }

    // Mode 2: Mode 1 + Primary ↔ Secondary
    else if (control.GenerateAssignments == 2) {
        if (r.primary == s.primary)
            return s.primary;

        if (s.secondary != -1 && r.primary == s.secondary)
            return s.secondary;
    }

    return -1;
}

bool isCompatible(const Reviewer &r, const Submission &s, const Control &control) {
    return getMatchDomain(r, s, control) != -1;
}

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