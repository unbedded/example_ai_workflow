// TOKENS: 1671 (of:8000) = 685 + 986(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: lance/lance_code.cpp 
// dest: lance/lance_code.cpp 
/**
 * @file lance_code.cpp
 * @brief Implementation file for clustering connected components in a 2D grid.
 * @date 2023-10-05
 */

#include "lance_code.hpp"
#include <iostream>

namespace {
    // Directions for moving in 8 possible directions (N, S, E, W, NE, NW, SE, SW)
    const std::vector<Coordinate> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}, // N, S, W, E
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1} // NW, NE, SW, SE
    };

    bool debug_enable = false;

    void debug_print(const std::string& message) {
        if (debug_enable) {
            std::cerr << message << std::endl;
        }
    }

    /**
     * @brief Depth-first search to explore a cluster.
     * 
     * @param grid The 2D grid of characters.
     * @param visited A 2D grid to track visited cells.
     * @param x The current x-coordinate.
     * @param y The current y-coordinate.
     * @param cluster The current cluster being explored.
     */
    void dfs(const Grid& grid, std::vector<std::vector<bool>>& visited, int x, int y, Cluster& cluster) {
        visited[x][y] = true;
        cluster.emplace_back(x, y);
        debug_print("Visiting: (" + std::to_string(x) + ", " + std::to_string(y) + ")");

        for (const auto& [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size() && !visited[nx][ny] && grid[nx][ny] == '1') {
                dfs(grid, visited, nx, ny, cluster);
            }
        }
    }
}

std::vector<Cluster> clustring(const Grid& grid) {
    std::vector<Cluster> clusters;
    if (grid.empty() || grid[0].empty()) {
        return clusters;
    }

    int rows = grid.size();
    int cols = grid[0].size();
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < cols; ++y) {
            if (grid[x][y] == '1' && !visited[x][y]) {
                Cluster cluster;
                debug_print("Starting new cluster at: (" + std::to_string(x) + ", " + std::to_string(y) + ")");
                dfs(grid, visited, x, y, cluster);
                clusters.push_back(cluster);
            }
        }
    }

    return clusters;
}
