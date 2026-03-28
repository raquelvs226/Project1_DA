#ifndef PROJECT1_MENU_H
#define PROJECT1_MENU_H

/**
 * @file menu.h
 * @brief Interactive command-line menu for the conference assignment tool.
 */

/**
 * @brief Launches the interactive command-line menu.
 *
 * Presents the user with options to load a dataset, run the assignment
 * and risk analysis pipeline, and view the currently loaded filename.
 * Loops until the user chooses to exit.
 *
 * @note Complexity: O(N * V * E^2) per pipeline run, where N is the number of
 * risk analysis iterations, V is the number of graph vertices, and E is
 * the number of edges.
 */
void runMenu();

#endif //PROJECT1_MENU_H