#include <iostream>
#include <vector>
#include "data.h"

using namespace std;

extern void parseCSV(string filename);
extern vector<Submission> submissions;
extern vector<Reviewer> reviewers;

int main() {

    parseCSV("dataset1.csv");

    cout << "Submissions:\n";

    for (auto &s : submissions) {
        cout << s.id << " topic " << s.primary << endl;
    }

    cout << "\nReviewers:\n";

    for (auto &r : reviewers) {
        cout << r.id << " expertise " << r.primary << endl;
    }

}