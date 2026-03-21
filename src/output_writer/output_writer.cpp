#include "output_writer.h"
#include "../generate_assignments/generate_assignments.h"
#include "../risk_analysis/risk_analysis.h"

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <vector>

static std::vector<Assignment> sortedBySubmission(std::vector<Assignment> v) {
    std::sort(v.begin(), v.end(), [](const Assignment& a, const Assignment& b) {
        if (a.submissionId != b.submissionId) return a.submissionId < b.submissionId;
        return a.reviewerId < b.reviewerId;
    });
    return v;
}

static std::vector<Assignment> sortedByReviewer(std::vector<Assignment> v) {
    std::sort(v.begin(), v.end(), [](const Assignment& a, const Assignment& b) {
        if (a.reviewerId != b.reviewerId) return a.reviewerId < b.reviewerId;
        return a.submissionId < b.submissionId;
    });
    return v;
}

void writeOutputCSV(
    const std::string& filename,
    const std::vector<Assignment>& assignments,
    std::vector<Submission>& submissions,
    std::vector<Reviewer>& reviewers,
    Parameters& params,
    Control& control)
{
    std::ofstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Could not open output file: " + filename);

    file << "#SubmissionId,ReviewerId,Match\n";
    for (const auto& a : sortedBySubmission(assignments))
        file << a.submissionId << ", " << a.reviewerId << ", " << a.matchDomain << "\n";

    file << "#ReviewerId,SubmissionId,Match\n";
    for (const auto& a : sortedByReviewer(assignments))
        file << a.reviewerId << ", " << a.submissionId << ", " << a.matchDomain << "\n";

    file << "#Total: " << assignments.size() << "\n";

    std::vector<int> received = countReceivedReviews(assignments, submissions);
    bool hasMissing = false;
    for (int count : received)
        if (count < params.MinReviewsPerSubmission) { hasMissing = true; break; }

    if (hasMissing) {
        file << "#SubmissionId,Domain,MissingReviews\n";
        for (int j = 0; j < static_cast<int>(submissions.size()); j++) {
            int missing = params.MinReviewsPerSubmission - received[j];
            if (missing > 0)
                file << submissions[j].id << ", "
                     << submissions[j].primary << ", "
                     << missing << "\n";
        }
    }

    if (control.RiskAnalysis == 1) {
        file << "#Risk Analysis: 1\n";
        writeRiskAnalysis(file, submissions, reviewers, params, control);
    }
}
