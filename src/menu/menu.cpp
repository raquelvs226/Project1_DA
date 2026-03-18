#include "menu.h"

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>

#include "data.h"
#include "parser/parser.h"
#include "graph_builder/graph_builder.h"
#include "graphs/Graph.h"
#include "graphs/edmondsKarp.h"
#include "output/output_writer.h"

using namespace std;

static void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static void showMenu() {
    cout << "\n========== MENU ==========\n";
    cout << "1. Load dataset\n";
    cout << "2. Run assignments and risk analysis\n";
    cout << "0. Exit\n";
    cout << "Option:\n";
}

static bool loadDataset(vector<Submission>& submissions,
                        vector<Reviewer>& reviewers,
                        Parameters& params,
                        Control& control) {
    string filename;

    cout << "Enter dataset filename: ";
    cout.flush();
    cin >> filename;

    string path = "../../input/" + filename;

    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Error: file '" << path << "' not found.\n";
        return false;
    }
    file.close();

    submissions.clear();
    reviewers.clear();
    params = Parameters();
    control = Control();

    try {
        parseCSV(path, submissions, reviewers, params, control);

        if (control.OutputFileName.empty()) {
            control.OutputFileName = "output.csv";
        }

        cout << "Dataset loaded successfully from: " << path << "\n";
        return true;
    }
    catch (const exception& e) {
        cerr << "Error loading dataset: " << e.what() << '\n';
        return false;
    }
}

static void runAssignmentsAndRiskAnalysis( vector<Submission>& submissions,
                                           vector<Reviewer>& reviewers,
                                           Parameters& params,
                                           Control& control,
                                          bool datasetLoaded) {
    if (!datasetLoaded) {
        cout << "You need to load a dataset first.\n";
        return;
    }

    int source, sink;

    try {
        Graph<int>* g = buildGraph(submissions, reviewers, params, source, sink);

        edmondsKarp(g, source, sink);

        string outputPath = "../" + control.OutputFileName;
        writeOutputCSV(outputPath, g, submissions, reviewers, params);

        cout << "Process completed successfully.\n";
        cout << "Output written to: " << outputPath << '\n';

        delete g;
    }
    catch (const exception& e) {
        cerr << "Error during execution: " << e.what() << '\n';
    }
    catch (...) {
        cerr << "Unknown error during execution.\n";
    }
}

void runMenu() {
    vector<Submission> submissions;
    vector<Reviewer> reviewers;
    Parameters params;
    Control control;

    bool datasetLoaded = false;
    int option;

    do {
        showMenu();

        if (!(cin >> option)) {
            clearInput();
            cout << "Invalid option.\n";
            continue;
        }

        switch (option) {
            case 1:
                datasetLoaded = loadDataset(submissions, reviewers, params, control);
                break;

            case 2:
                runAssignmentsAndRiskAnalysis(submissions, reviewers, params, control, datasetLoaded);
                break;

            case 0:
                cout << "Exiting\n";
                break;

            default:
                cout << "Invalid option.\n";
                break;
        }

    } while (option != 0);
}