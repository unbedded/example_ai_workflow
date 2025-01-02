// TOKENS: 1969 (of:8000) = 770 + 1199(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: lance/lance_code.cpp 
// dest: lance/lance_code.cpp 
/**
 * @file lance_code.hpp
 * @brief Header file for clustering algorithm.
 * 
 * This file contains the declarations for the `clustering` function and associated helper functions.
 * It is designed to identify clusters of connected '1's in a 2D grid using a depth-first search (DFS) approach.
 * 
 * Date: 2025-01-02
 */

#ifndef LANCE_CODE_HPP
#define LANCE_CODE_HPP

#include <vector>
#include <utility>
#include <string>

// Global debug flag
inline bool debug_enable = false;

// Function to print debug information
void debug_print(const std::string& message);

// Check if a given cell (x, y) is within the grid boundaries and is a '1'
bool is_valid(int x, int y, const std::vector<std::vector<char>>& grid, std::vector<std::vector<bool>>& visited);

// Perform DFS to find all connected '1's starting from (x, y)
void dfs(int x, int y, const std::vector<std::vector<char>>& grid, std::vector<std::vector<bool>>& visited, std::vector<std::pair<int, int>>& cluster);

// Main function to find clusters in the grid
std::vector<std::vector<std::pair<int, int>>> clustering(const std::vector<std::vector<char>>& grid);

#endif // LANCE_CODE_HPP
