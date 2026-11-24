# Design of Algorithms Project 1 - Scientific Conference Organization Tool

A tool that helps organize a scientific conference by **assigning reviewers to paper submissions**, modeled as a **Maximum Flow** problem and solved with the **Edmonds-Karp** algorithm.

Programming Project I — **Design of Algorithms (DA)**, L.EIC016, Spring 2026  
Faculty of Engineering, University of Porto (FEUP)

---

## Description

Each submission has a primary (and optionally a secondary) topic, and each reviewer has a primary (and optionally a secondary) area of expertise. The goal is to assign reviewers to submissions so that:

- every submission receives **at least** `MinReviewsPerSubmission` reviews;
- every reviewer performs **at most** `MaxReviewsPerReviewer` reviews;
- every review respects the match between the submission's domain and the reviewer's expertise.

### Flow network model

```
source ──(MaxReviewsPerReviewer)──► reviewer ──(1)──► submission ──(MinReviewsPerSubmission)──► sink
```

- The source connects to each reviewer with capacity `MaxReviewsPerReviewer`.
- A reviewer connects to each compatible submission with capacity 1.
- Each submission connects to the sink with capacity `MinReviewsPerSubmission`.

A valid assignment exists if and only if the max flow saturates all submission-to-sink edges.

## Features

- **Interactive command-line menu** (load dataset, run assignments and risk analysis, view loaded file).
- **Batch mode** for script-based execution.
- **Input parsing and validation** of `.csv` files; invalid files are rejected with an error message.
- **Review assignment** according to `GenerateAssignments`:

  | Value | Behavior |
  |-------|----------|
  | 0 | Assignment is computed but not reported |
  | 1 | Primary submission domains vs. primary reviewer expertise |
  | 2 | Primary and secondary submission domains vs. primary reviewer expertise |

- **Failure reporting**: when the minimum number of reviews can't be met, the affected submissions, their domain and the number of missing reviews are reported.
- **Risk analysis** (`RiskAnalysis = 1`): identifies the reviewers whose absence would make a valid assignment impossible.
- **Doxygen documentation** with time complexity of the main algorithms.


# Datasets
| File | Scenario |
|---|---|
| `dataset1.csv` | Example dataset provided in the project description. |
| `dataset2.csv` | Primary submission domains only. All submissions receive the required number of reviews with extra reviewer capacity available. |
| `dataset3.csv` | Same as dataset2, with risk analysis enabled. No reviewer is risky. |
| `dataset4.csv` | Primary submission domains only. All submissions receive exactly the required number of reviews (no extra capacity). |
| `dataset5.csv` | Same as dataset4, with risk analysis enabled. All reviewers are risky. |
| `dataset6.csv` | Primary submission domains only. One submission cannot reach the minimum reviews. |
| `dataset7.csv` | Primary submission domains only. Multiple submissions cannot reach the required reviews due to an insufficient number of reviewers across several topics. |
| `dataset8.csv` | Primary submission domains only. All submissions are fully covered with no additional reviewer capacity. |
| `dataset9.csv` | Same as dataset8, with risk analysis enabled. Only reviewers 7 and 8 are risky. |
| `dataset10.csv` | Primary and secondary submission domains enabled. All submissions can be assigned the required reviews with extra capacity. |
| `dataset11.csv` | Same as dataset10, with risk analysis enabled. No reviewers are risky. |
| `dataset12.csv` | Primary and secondary submission domains enabled. The algorithm must choose between primary and secondary domains to achieve a valid assignment. |
| `dataset13.csv` | Same as dataset12, with risk analysis enabled. All reviewers are risky. |
| `dataset14.csv` | Primary and secondary submission domains enabled with risk analysis. Both domains are required to obtain a valid assignment, no risky reviewers. |
