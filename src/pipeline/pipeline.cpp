#include "pipeline.h"
#include "../graph_builder/graph_builder.h"
#include "../graphs/edmondsKarp.h"
#include "../generate_assignments/generate_assignments.h"
#include "../risk_analysis/risk_analysis.h"
#include "../output_writer/output_writer.h"

#include <iostream>

void runPipeline(
    std::vector<Submission>& submissions,
    std::vector<Reviewer>& reviewers,
    Parameters& params,
    Control& control,
    const std::string& outputPathOverride)
{
    if (control.OutputFileName.empty())
        control.OutputFileName = "output.csv";

    int source, sink;
    Graph<int>* g = buildGraph(submissions, reviewers, params, control, source, sink);

    edmondsKarp(g, source, sink);

    std::vector<Assignment> assignments;
    if (control.GenerateAssignments != 0) {
        int firstReviewerNode   = source + 1;
        int firstSubmissionNode = source + 1 + (int)reviewers.size();
        assignments = extractAssignments(g, submissions, reviewers, firstReviewerNode, firstSubmissionNode);
    }

    delete g;

    std::vector<int> riskyReviewers;
    if (control.RiskAnalysis == 1)
        riskyReviewers = getRiskyReviewers(submissions, reviewers, params, control);

    std::string outputPath;
    if (!outputPathOverride.empty()) {
        outputPath = outputPathOverride;
    } else {
        if (control.GenerateAssignments == 0 && control.RiskAnalysis == 1)
            outputPath = "../../results/risk/" + control.OutputFileName;
        else
            outputPath = "../../results/" + control.OutputFileName;
    }

    writeOutputCSV(outputPath, assignments, riskyReviewers, submissions, reviewers, params, control);

    std::cout << "Output written to: " << outputPath << '\n';
}