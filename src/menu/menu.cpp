#include "menu.h"

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>

#include "../data.h"
#include "../parser/parser.h"
#include "../pipeline/pipeline.h"

using namespace std;

static void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static void showMenu() {
    cout << "\n========== MENU ==========\n";
    cout << "1. Load dataset\n";
    cout << "2. Run assignments and risk analysis\n";
    cout << "3. View loaded filename\n";
    cout << "0. Exit\n";
    cout << "Option: ";
}

static bool loadDataset(vector<Submission>& submissions,
                        vector<Reviewer>& reviewers,
                        Parameters& params,
                        Control& control,
                        string& currentFilename) {
    string filename;
    cout << "Enter dataset filename: " << flush;
    cin >> filename;

    string path = "../../input/" + filename;

    ifstream file(path);
    if (!file.is_open()) {
        cout << "Error: file '" << path << "' not found.\n";
        return false;
    }
    file.close();

    submissions.clear();
    reviewers.clear();
    params = Parameters();
    control = Control();

    try {
        parseCSV(path, submissions, reviewers, params, control);

        if (control.GenerateAssignments != 0 && control.OutputFileName.empty()) {
            control.OutputFileName = "output.csv";
        }

        currentFilename = filename;

        cout << "Dataset loaded successfully from: " << path << "\n";
        return true;
    }
    catch (const exception& e) {
        cout << "Error loading dataset: " << e.what() << '\n';
        return false;
    }
}

static void runAssignmentsAndRiskAnalysis(vector<Submission>& submissions,
                                          vector<Reviewer>& reviewers,
                                          Parameters& params,
                                          Control& control,
                                          bool datasetLoaded) {
    if (!datasetLoaded) {
        cout << "You need to load a dataset first.\n";
        return;
    }
    try {
        runPipeline(submissions, reviewers, params, control);
    }
    catch (const exception& e) {
        cerr << "Error during execution: " << e.what() << '\n';
    }
}

void runMenu() {
    vector<Submission> submissions;
    vector<Reviewer> reviewers;
    Parameters params;
    Control control;

    bool datasetLoaded = false;
    string currentFilename = "None";
    int option = -1;

    do {
        showMenu();

        if (!(cin >> option)) {
            cout << "Invalid option.\n";
            clearInput();
            option = -1;
            continue;
        }

        switch (option) {
            case 1:
                datasetLoaded = loadDataset(submissions, reviewers, params, control, currentFilename);
                break;

            case 2:
                runAssignmentsAndRiskAnalysis(submissions, reviewers, params, control, datasetLoaded);
                break;

            case 3:
                if (datasetLoaded) {
                    cout << "\nCurrently loaded file: " << currentFilename << "\n";
                } else {
                    cout << "\nNo dataset loaded yet.\n";
                }
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
