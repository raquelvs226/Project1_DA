#include "risk_analysis.h"
#include "../graphs/edmondsKarp.h"
#include "../graph_builder/graph_builder.h"

#include <vector>
#include <fstream>

using namespace std;

static bool isFeasible(vector<Submission> &submissions,
                       vector<Reviewer> &reviewers,
                       Parameters &params,
                       Control &control) {

    int source, sink;
    Graph<int> *g = buildGraph(submissions, reviewers, params, control, source, sink);
    edmondsKarp(g, source, sink);

    int flow = 0;
    for (auto e : g->findVertex(source)->getAdj())
        flow += e->getFlow();

    delete g;
    return flow == (int)(submissions.size() * params.MinReviewsPerSubmission);
}

void writeRiskAnalysis(ofstream &file,
                       vector<Submission> &submissions,
                       vector<Reviewer> &reviewers,
                       Parameters &params,
                       Control &control) {

    if (control.RiskAnalysis != 1) return;

    if (!isFeasible(submissions, reviewers, params, control)) return;

    int n = reviewers.size();
    vector<int> riskyIds;

    for (int i = 0; i < n; i++) {
        vector<Reviewer> filtered;
        for (int j = 0; j < n; j++)
            if (j != i) filtered.push_back(reviewers[j]);

        if (!isFeasible(submissions, filtered, params, control))
            riskyIds.push_back(reviewers[i].id);
    }

    if (!riskyIds.empty()) {
        for (int i = 0; i < (int)riskyIds.size(); i++) {
            if (i > 0) file << ", ";
            file << riskyIds[i];
        }
        file << "\n";
    }
}