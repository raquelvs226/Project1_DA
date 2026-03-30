#include "matching.h"

int getMatchDomain(const Reviewer &r, const Submission &s, const Control &control, const Parameters &params) {
    // primary reviewer vs primary submission
    if (params.PrimaryReviewerExpertise && params.PrimarySubmissionDomain)
        if (r.primary == s.primary) return s.primary;

    // primary reviewer vs secondary submission
    if (params.PrimaryReviewerExpertise && params.SecondarySubmissionDomain)
        if (s.secondary != -1 && r.primary == s.secondary) return s.secondary;

    return -1;
}

bool isCompatible(const Reviewer &r, const Submission &s, const Control &control, const Parameters &params) {
    return getMatchDomain(r, s, control, params) != -1;
}