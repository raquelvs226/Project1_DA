#include "parser.h"
#include "../data.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

string trim(const string &str) {
    string result = str;

    result.erase(result.begin(), find_if(result.begin(), result.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));

    result.erase(find_if(result.rbegin(), result.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), result.end());

    return result;
}

string removeComment(const string &line) {
    size_t pos = line.find('#');
    if (pos == string::npos) {
        return line;
    }
    return line.substr(0, pos);
}

string removeQuotes(const string &str) {
    string result = trim(str);

    if (result.size() >= 2) {
        if ((result.front() == '"' && result.back() == '"') ||
            (result.front() == '\'' && result.back() == '\'')) {
            result = result.substr(1, result.size() - 2);
        }
    }

    return result;
}

int parseOptionalInt(const string &str) {
    string value = trim(str);
    if (value.empty()) {
        return -1;
    }
    return stoi(value);
}

void parseCSV(const string &filename, vector<Submission> &submissions, vector<Reviewer> &reviewers, Parameters &params, Control &control) {

    submissions.clear();
    reviewers.clear();

    params = {0, 0, 0, 0, 0, 0};
    control = {0, 0, ""};

    ifstream file(filename);
    string line;
    string section;

    while (getline(file, line)) {
        line = trim(line);

        if (line.empty()) {
            continue;
        }

        if (line == "#Submissions") {
            section = "Submissions";
            continue;
        }

        if (line == "#Reviewers") {
            section = "Reviewers";
            continue;
        }

        if (line == "#Parameters") {
            section = "Parameters";
            continue;
        }

        if (line == "#Control") {
            section = "Control";
            continue;
        }

        line = trim(removeComment(line));

        if (line.empty()) {
            continue;
        }

        stringstream lineStream(line);

        if (section == "Submissions") {
            Submission submission;
            string idStr, primaryStr, secondaryStr;

            getline(lineStream, idStr, ',');
            getline(lineStream, submission.title, ',');
            getline(lineStream, submission.authors, ',');
            getline(lineStream, submission.email, ',');
            getline(lineStream, primaryStr, ',');
            getline(lineStream, secondaryStr);

            submission.id = stoi(trim(idStr));
            submission.title = removeQuotes(submission.title);
            submission.authors = removeQuotes(submission.authors);
            submission.email = removeQuotes(submission.email);
            submission.primary = stoi(trim(primaryStr));
            submission.secondary = parseOptionalInt(secondaryStr);

            submissions.push_back(submission);
        }

        else if (section == "Reviewers") {
            Reviewer reviewer;
            string idStr, primaryStr, secondaryStr;

            getline(lineStream, idStr, ',');
            getline(lineStream, reviewer.name, ',');
            getline(lineStream, reviewer.email, ',');
            getline(lineStream, primaryStr, ',');
            getline(lineStream, secondaryStr);

            reviewer.id = stoi(trim(idStr));
            reviewer.name = removeQuotes(reviewer.name);
            reviewer.email = removeQuotes(reviewer.email);
            reviewer.primary = stoi(trim(primaryStr));
            reviewer.secondary = parseOptionalInt(secondaryStr);

            reviewers.push_back(reviewer);
        }

        else if (section == "Parameters") {
            string key, valueStr;
            getline(lineStream, key, ',');
            getline(lineStream, valueStr);

            key = trim(key);
            int value = stoi(trim(valueStr));

            if (key == "MinReviewsPerSubmission") {
                params.MinReviewsPerSubmission = value;
            } else if (key == "MaxReviewsPerReviewer") {
                params.MaxReviewsPerReviewer = value;
            } else if (key == "PrimaryReviewerExpertise") {
                params.PrimaryReviewerExpertise = value;
            } else if (key == "SecondaryReviewerExpertise") {
                params.SecondaryReviewerExpertise = value;
            } else if (key == "PrimarySubmissionDomain") {
                params.PrimarySubmissionDomain = value;
            } else if (key == "SecondarySubmissionDomain") {
                params.SecondarySubmissionDomain = value;
            }
        }

        else if (section == "Control") {
            string key, value;
            getline(lineStream, key, ',');
            getline(lineStream, value);

            key = trim(key);
            value = trim(value);

            if (key == "GenerateAssignments") {
                control.GenerateAssignments = stoi(value);
            } else if (key == "RiskAnalysis") {
                control.RiskAnalysis = stoi(value);
            } else if (key == "OutputFileName") {
                control.OutputFileName = removeQuotes(value);
            }
        }
    }

    file.close();
}