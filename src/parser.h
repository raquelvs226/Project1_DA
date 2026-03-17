#ifndef PROJECT1_PARSER_H
#define PROJECT1_PARSER_H

#include "data.h"
#include <string>
#include <vector>

using namespace std;

void parseCSV(const string &filename,
              vector<Submission> &submissions,
              vector<Reviewer> &reviewers,
              Parameters &params,
              Control &control);

#endif