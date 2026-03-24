#ifndef PROJECT1_RISK_ANALYSIS_H
#define PROJECT1_RISK_ANALYSIS_H

#include "../data.h"
#include <vector>

std::vector<int> getRiskyReviewers(
    std::vector<Submission>& submissions,
    std::vector<Reviewer>& reviewers,
    Parameters& params,
    Control& control);

#endif // PROJECT1_RISK_ANALYSIS_H
