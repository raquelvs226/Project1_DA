#ifndef PROJECT1_PARSER_H
#define PROJECT1_PARSER_H

#include "../data.h"
#include <string>
#include <vector>

using namespace std;

/**
 * @file parser.h
 * @brief Function for parsing the input CSV dataset file.
 */

/**
 * @brief Parses a CSV input file and populates the problem data structures.
 *
 * Reads the file section by section (\#Submissions, \#Reviewers, \#Parameters,
 * #Control). Fields are comma-separated; everything after a '#' character
 * on a data line is treated as a comment and ignored. The file must have
 * the '.csv' extension and contain no duplicate submission or reviewer IDs.
 *
 * @param filename Path to the input CSV file.
 * @param submissions Output vector populated with all parsed submissions.
 * @param reviewers Output vector populated with all parsed reviewers.
 * @param params Output struct populated with the problem parameters.
 * @param control Output struct populated with the execution control options.
 *
 */
void parseCSV(const string &filename,
              vector<Submission> &submissions,
              vector<Reviewer> &reviewers,
              Parameters &params,
              Control &control);

#endif