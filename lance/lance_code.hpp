// TOKENS: 1590 (of:8000) = 692 + 898(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: lance/lance_code.cpp 
// dest: lance/lance_code.cpp 
/**
 * @file lance_code.hpp
 * @brief Header file for clustering connected components in a 2D grid.
 * 
 * This file contains the declarations for functions and types used to identify clusters
 * of connected '1's in a 2D grid. The approach uses Depth-First Search (DFS) to explore
 * connected components, considering vertical, horizontal, and diagonal connections.
 * 
 * Date: 2023-10-05
 */

#pragma once

#include <vector>
#include <utility>

using Grid = std::vector<std::vector<char>>;
using Cluster = std::vector<std::pair<int, int>>;
using Clusters = std::vector<Cluster>;

/**
 * @brief Identifies clusters of connected '1's in a 2D grid.
 * 
 * @param grid A 2D grid of characters ('1' or '0').
 * @return A list of clusters, where each cluster is a list of (x, y) coordinates.
 */
Clusters clustring(const Grid& grid);

/**
 * @brief Helper function to perform DFS and find all connected components.
 * 
 * @param grid The 2D grid.
 * @param x The current x-coordinate.
 * @param y The current y-coordinate.
 * @param visited A 2D grid to track visited cells.
 * @param cluster The current cluster being explored.
 */
void dfs(const Grid& grid, int x, int y, std::vector<std::vector<bool>>& visited, Cluster& cluster);
