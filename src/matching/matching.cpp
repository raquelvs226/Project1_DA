#include "matching.h"

int getMatchDomain(const Reviewer &r, const Submission &s, const Control &control) {

    // (Mode 0 means "run but don't report", so matching rules are identical to mode 1)
    if (control.GenerateAssignments == 0 || control.GenerateAssignments == 1) {
        if (r.primary == s.primary)
            return s.primary;
    }
    // Mode 2: Primary submission domain (including secondary) ↔ Primary reviewer expertise
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