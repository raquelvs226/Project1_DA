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

    for (int i = 0; i < (int)reviewers.size(); i++) {
        for (int j = 0; j < (int)submissions.size(); j++) {
            int domain = getMatchDomain(reviewers[i], submissions[j], control);
            if (domain != -1) {
                Vertex<int>* rv = g->findVertex(reviewerNodes[i]);
                Vertex<int>* sv = g->findVertex(submissionNodes[j]);
                Edge<int>* e = rv->addEdge(sv, 1);
                e->setMatchDomain(domain);
            }
        }
    }

    return g;
}