#ifndef PROJECT1_PIPELINE_H
#define PROJECT1_PIPELINE_H


#include "../data.h"
#include "../generate_assignments/generate_assignments.h"
#include <string>
#include <vector>

void runPipeline(
    std::vector<Submission>& submissions,
    std::vector<Reviewer>& reviewers,
    Parameters& params,
    Control& control);

#endif //PROJECT1_PIPELINE_H