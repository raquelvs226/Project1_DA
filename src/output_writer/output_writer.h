#ifndef OUTPUT_WRITER_H
#define OUTPUT_WRITER_H

#include "../data.h"
#include "../generate_assignments/generate_assignments.h"
#include <string>
#include <vector>

void writeOutputCSV(
    const std::string& filename,
    const std::vector<Assignment>& assignments,
    std::vector<Submission>& submissions,
    std::vector<Reviewer>& reviewers,
    Parameters& params,
    Control& control);

#endif // OUTPUT_WRITER_H
