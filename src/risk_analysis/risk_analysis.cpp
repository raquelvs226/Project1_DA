#include "risk_analysis.h"
#include "../graph_builder/graph_builder.h"
#include "../graphs/edmondsKarp.h"

static bool isFeasible(
    std::vector<Submission>& submissions,
    std::vector<Reviewer>& reviewers,
    Parameters& params,
    Control& control)
{
    int source, sink;
    Graph<int>* g = buildGraph(submissions, reviewers, params, control, source, sink);
    edmondsKarp(g, source, sink);

    int flow = 0;
    for (auto e : g->findVertex(source)->getAdj())
        flow += e->getFlow();

    delete g;
    return flow == (int)(submissions.size() * params.MinReviewsPerSubmission);
}

std::vector<int> getRiskyReviewers(
    std::vector<Submission>& submissions,
    std::vector<Reviewer>& reviewers,
    Parameters& params,
    Control& control)
{
    if (control.RiskAnalysis != 1) return {};
    if (!isFeasible(submissions, reviewers, params, control)) return {};

    int n = reviewers.size();
    std::vector<int> riskyIds;

    for (int i = 0; i < n; i++) {
        std::vector<Reviewer> filtered;
        for (int j = 0; j < n; j++)
            if (j != i) filtered.push_back(reviewers[j]);

        if (!isFeasible(submissions, filtered, params, control))
            riskyIds.push_back(reviewers[i].id);
    }

    return riskyIds;
}