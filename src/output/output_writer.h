#ifndef OUTPUT_WRITER_H
#define OUTPUT_WRITER_H

#include "../data.h"
#include "../graphs/Graph.h"
#include <string>
#include <vector>

using namespace std;

void writeOutputCSV(const string &filename,
                    Graph<int> *g,
                    vector<Submission> &submissions,
                    vector<Reviewer> &reviewers,
                    Parameters &params);

#endif