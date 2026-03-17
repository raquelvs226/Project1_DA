#include <iostream>
#include <vector>

#include "data.h"
#include "parser/parser.h"
#include "graph_builder/graph_builder.h"
#include "graphs/Graph.h"
#include "graphs/edmondsKarp.cpp"
#include "output/output_writer.h"

using namespace std;

int main() {
    vector<Submission> submissions;
    vector<Reviewer> reviewers;
    Parameters params;
    Control control;

    parseCSV("../../input/dataset3.csv", submissions, reviewers, params, control);

    if (control.OutputFileName.empty()) {
        control.OutputFileName = "output.csv";
    }

    int source, sink;

    Graph<int>* g = buildGraph(submissions, reviewers, params, source, sink);

    edmondsKarp(g, source, sink);

    string outputPath = "../" + control.OutputFileName;
    writeOutputCSV(outputPath, g, submissions, reviewers, params);

    cout << "Output written to: " << outputPath << endl;

    return 0;
}