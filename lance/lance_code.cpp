// TOKENS: 1403 (of:8000) = 655 + 748(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: lance/lance_code.cpp 
// dest: lance/lance_code.cpp 
#include "clustering.hpp"
#include <stdexcept>

// File: clustering.cpp
// Date: 2023-10-05
// Description: Implementation file for clustering connected components in a 2D grid.

Clustering::Clustering(bool debug_enable) : debug_enable_(debug_enable) {}

Clusters Clustering::findClusters(const Grid& grid) {
    if (grid.empty() || grid[0].empty()) {
        throw std::invalid_argument("Grid cannot be empty.");
    }

    int rows = grid.size();
    int cols = grid[0].size();
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    Clusters clusters;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == '1' && !visited[i][j]) {
                Cluster cluster;
                dfs(grid, i, j, cluster, visited);
                clusters.push_back(cluster);
            }
        }
    }

    return clusters;
}

void Clustering::dfs(const Grid& grid, int x, int y, Cluster& cluster, std::vector<std::vector<bool>>& visited) {
    static const std::vector<std::pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    int rows = grid.size();
    int cols = grid[0].size();

    visited[x][y] = true;
    cluster.emplace_back(x, y);

    for (const auto& [dx, dy] : directions) {
        int nx = x + dx;
        int ny = y + dy;

        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] == '1' && !visited[nx][ny]) {
            dfs(grid, nx, ny, cluster, visited);
        }
    }
}

void Clustering::debugPrint(const std::string& message) const {
    if (debug_enable_) {
        std::cerr << message << std::endl;
    }
}
