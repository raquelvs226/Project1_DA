#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "menu/menu.h"
#include "data.h"
#include "parser/parser.h"
#include "pipeline/pipeline.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 1) {
        runMenu();
        return 0;
    }

    if (argc == 4 && string(argv[1]) == "-b") {
        string inputFilename = argv[2];
        string outputFilename = argv[3];
        string path = "../../input/" + inputFilename;

        vector<Submission> submissions;
        vector<Reviewer> reviewers;
        Parameters params;
        Control control;

        ifstream file(path);
        if (!file.is_open()) {
            cerr << "Error: file '" << path << "' not found.\n";
            return 1;
        }
        file.close();

        try {
            parseCSV(path, submissions, reviewers, params, control);
            runPipeline(submissions, reviewers, params, control, outputFilename);
            return 0;
        }
        catch (const exception& e) {
            cerr << "Error during batch execution: " << e.what() << '\n';
            return 1;
        }
    }

    cerr << "Usage:\n";
    cerr << "  " << argv[0] << '\n';
    cerr << "  " << argv[0] << " -b input.csv output.csv\n";
    return 1;
}