#include "graph_builder.h"

bool isCompatible(Reviewer &r, Submission &s, Control &control) {

    // Case 1: only primary reviewer expertise with primary submission domain
    if (control.GenerateAssignments == 1) {
        return r.primary == s.primary;
    }

    // Case 2: primary + secondary submission domains enabled
    if (control.GenerateAssignments == 2) {
        if (r.primary == s.primary) return true;

        if (s.secondary != -1) {
            if (s.secondary == r.primary) return true;
        }
        return false;
    }

    // Case 0 and 3: primary and secondary reviewer expertise + primary and secondary submission domains
    if (control.GenerateAssignments == 0 || control.GenerateAssignments == 3) {
        if (r.primary == s.primary) return true;
        if (s.secondary != -1 && r.primary == s.secondary) return true;
        if (r.secondary != -1 && r.secondary == s.primary) return true;
        if (r.secondary != -1 && s.secondary != -1 && r.secondary == s.secondary) return true;
        return false;
    }

    return false;
}

Graph<int>* buildGraph(vector<Submission> &submissions,
                       vector<Reviewer> &reviewers,
                       Parameters &params,
                       Control &control,
                       int &source,
                       int &sink) {

    Graph<int>* g = new Graph<int>();

    int id = 0;

    // SOURCE
    source = id++;
    g->addVertex(source);

    // REVIEWERS
    vector<int> reviewerNodes;
    for (auto &r : reviewers) {
        g->addVertex(id);
        reviewerNodes.push_back(id);

        // source -> reviewer
        g->addEdge(source, id, params.MaxReviewsPerReviewer);

        id++;
    }

    // SUBMISSIONS
    vector<int> submissionNodes;
    for (auto &s : submissions) {
        g->addVertex(id);
        submissionNodes.push_back(id);
        id++;
    }

    // SINK
    sink = id;
    g->addVertex(sink);

    // submission -> sink
    for (int subNode : submissionNodes) {
        g->addEdge(subNode, sink, params.MinReviewsPerSubmission);
    }

    // reviewer -> submission (compatibilidade)
    for (int i = 0; i < reviewers.size(); i++) {
        for (int j = 0; j < submissions.size(); j++) {
            if (isCompatible(reviewers[i], submissions[j], control)) {
                g->addEdge(reviewerNodes[i], submissionNodes[j], 1);
            }
        }
    }

    return g;
}