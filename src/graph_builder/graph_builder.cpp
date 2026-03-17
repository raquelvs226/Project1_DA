#include "graph_builder.h"

bool isCompatible(Reviewer &r, Submission &s, Parameters &p) {

    // primary-primary
    if (p.PrimaryReviewerExpertise && p.PrimarySubmissionDomain) {
        if (r.primary == s.primary) return true;
    }

    // primary-secondary
    if (p.PrimaryReviewerExpertise && p.SecondarySubmissionDomain && s.secondary != -1) {
        if (r.primary == s.secondary) return true;
    }

    // secondary-primary
    if (p.SecondaryReviewerExpertise && p.PrimarySubmissionDomain && r.secondary != -1) {
        if (r.secondary == s.primary) return true;
    }

    // secondary-secondary
    if (p.SecondaryReviewerExpertise && p.SecondarySubmissionDomain &&
        r.secondary != -1 && s.secondary != -1) {
        if (r.secondary == s.secondary) return true;
        }

    return false;
}

Graph<int>* buildGraph(vector<Submission> &submissions,
                       vector<Reviewer> &reviewers,
                       Parameters &params,
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
            if (isCompatible(reviewers[i], submissions[j], params)) {
                g->addEdge(reviewerNodes[i], submissionNodes[j], 1);
            }
        }
    }

    return g;
}