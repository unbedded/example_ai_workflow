// TOKENS: 1590 (of:8000) = 692 + 898(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: lance/lance_code.cpp 
// dest: lance/lance_code.cpp 
/**
 * @file lance_code.cpp
 * @brief Implementation file for clustering connected components in a 2D grid.
 * 
 * This file contains the implementation of functions to identify clusters of connected
 * '1's in a 2D grid using Depth-First Search (DFS).
 * 
 * Date: 2023-10-05
 */

#include "lance_code.hpp"
#include <iostream>

namespace {
    // Directions for moving in 8 possible ways (vertical, horizontal, diagonal)
    const std::vector<std::pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},         {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    bool debug_enable = false;

    void debug_print(const std::string& message) {
        if (debug_enable) {
            std::cerr << message << std::endl;
        }
    }
}

Clusters clustring(const Grid& grid) {
    if (grid.empty() || grid[0].empty()) {
        return {};
    }

    int rows = grid.size();
    int cols = grid[0].size();
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    Clusters clusters;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == '1' && !visited[i][j]) {
                Cluster cluster;
                dfs(grid, i, j, visited, cluster);
                clusters.push_back(cluster);
            }
        }
    }

    return clusters;
}

void dfs(const Grid& grid, int x, int y, std::vector<std::vector<bool>>& visited, Cluster& cluster) {
    int rows = grid.size();
    int cols = grid[0].size();

    visited[x][y] = true;
    cluster.emplace_back(x, y);

    for (const auto& [dx, dy] : directions) {
        int nx = x + dx;
        int ny = y + dy;

        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] == '1' && !visited[nx][ny]) {
            dfs(grid, nx, ny, visited, cluster);
        }
    }
}
