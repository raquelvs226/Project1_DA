#ifndef PROJECT1_GENERATE_ANALYSIS_H
#define PROJECT1_GENERATE_ANALYSIS_H

#include "../data.h"

int getMatchDomain(const Reviewer &r, const Submission &s, const Control &control);

bool isCompatible(const Reviewer &r, const Submission &s, const Control &control);

#endif //PROJECT1_GENERATE_ANALYSIS_H