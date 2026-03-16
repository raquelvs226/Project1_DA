#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "data.h"

using namespace std;

vector<Submission> submissions;
vector<Reviewer> reviewers;
Parameters params;
Control control;

void parseCSV(string filename) {

    ifstream file(filename);
    string line;

    enum Section {
        NONE,
        SUBMISSIONS,
        REVIEWERS,
        PARAMETERS,
        CONTROL
    };

    Section current = NONE;

    while (getline(file, line)) {

        if (line.empty()) continue;

        if (line == "#Submissions") {
            current = SUBMISSIONS;
            continue;
        }

        if (line == "#Reviewers") {
            current = REVIEWERS;
            continue;
        }

        if (line == "#Parameters") {
            current = PARAMETERS;
            continue;
        }

        if (line == "#Control") {
            current = CONTROL;
            continue;
        }

        if (line[0] == '#') continue;

        stringstream ss(line);
        string field;

        if (current == SUBMISSIONS) {

            Submission s;

            getline(ss, field, ',');
            s.id = stoi(field);

            getline(ss, s.title, ',');

            getline(ss, s.authors, ',');

            getline(ss, s.email, ',');

            getline(ss, field, ',');
            s.primary = stoi(field);

            if (getline(ss, field, ',')) {
                if (field.empty())
                    s.secondary = -1;
                else
                    s.secondary = stoi(field);
            }

            submissions.push_back(s);
        }

        else if (current == REVIEWERS) {

            Reviewer r;

            getline(ss, field, ',');
            r.id = stoi(field);

            getline(ss, r.name, ',');

            getline(ss, r.email, ',');

            getline(ss, field, ',');
            r.primary = stoi(field);

            if (getline(ss, field, ',')) {
                if (field.empty())
                    r.secondary = -1;
                else
                    r.secondary = stoi(field);
            }

            reviewers.push_back(r);
        }

        else if (current == PARAMETERS) {

            getline(ss, field, ',');
            string name = field;

            getline(ss, field, ',');

            int value = stoi(field);

            if (name == "MinReviewsPerSubmission")
                params.MinReviewsPerSubmission = value;

            else if (name == "MaxReviewsPerReviewer")
                params.MaxReviewsPerReviewer = value;

            else if (name == "PrimaryReviewerExpertise")
                params.PrimaryReviewerExpertise = value;

            else if (name == "SecondaryReviewerExpertise")
                params.SecondaryReviewerExpertise = value;

            else if (name == "PrimarySubmissionDomain")
                params.PrimarySubmissionDomain = value;

            else if (name == "SecondarySubmissionDomain")
                params.SecondarySubmissionDomain = value;
        }

        else if (current == CONTROL) {

            getline(ss, field, ',');
            string name = field;

            getline(ss, field, ',');

            if (name == "GenerateAssignments")
                control.GenerateAssignments = stoi(field);

            else if (name == "RiskAnalysis")
                control.RiskAnalysis = stoi(field);

            else if (name == "OutputFileName")
                control.OutputFileName = field;
        }
    }
}