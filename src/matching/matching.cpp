#include "matching.h"

int getMatchDomain(const Reviewer &r, const Submission &s, const Control &control) {

    // Mode 1: Primary ↔ Primary
    if (control.GenerateAssignments == 1) {
        if (r.primary == s.primary)
            return s.primary;
    }

    // Mode 2: Mode 1 + Primary ↔ Secondary
    else if (control.GenerateAssignments == 2) {
        if (r.primary == s.primary)
            return s.primary;

        if (s.secondary != -1 && r.primary == s.secondary)
            return s.secondary;
    }

    return -1;
}

bool isCompatible(const Reviewer &r, const Submission &s, const Control &control) {
    return getMatchDomain(r, s, control) != -1;
}