// TOKENS: 1671 (of:8000) = 685 + 986(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: lance/lance_code.cpp 
// dest: lance/lance_code.cpp 
/**
 * @file lance_code.hpp
 * @brief Header file for clustering connected components in a 2D grid.
 * @date 2023-10-05
 */

#pragma once

#include <vector>
#include <utility>

// Type alias for better readability
using Coordinate = std::pair<int, int>;
using Cluster = std::vector<Coordinate>;
using Grid = std::vector<std::vector<char>>;

/**
 * @brief Identifies clusters of connected '1's in a 2D grid.
 * 
 * @param grid The 2D grid of characters ('1' or '0').
 * @return A list of clusters, where each cluster is a list of (x, y) coordinates.
 */
std::vector<Cluster> clustring(const Grid& grid);
