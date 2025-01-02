// TOKENS: 1969 (of:8000) = 770 + 1199(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: lance/lance_code.cpp 
// dest: lance/lance_code.cpp 
/**
 * @file lance_code.cpp
 * @brief Implementation of clustering algorithm to identify connected components in a 2D grid.
 * 
 * This file contains the implementation of the `clustering` function, which identifies clusters of connected '1's
 * in a 2D grid. The function uses a depth-first search (DFS) approach to explore and identify connected components.
 * 
 * Date: 2025-01-02
 */

#include "lance_code.hpp"
#include <iostream>
#include <stack>

// Function to print debug information
void debug_print(const std::string& message) {
    if (debug_enable) {
        std::cerr << message << std::endl;
    }
}

// Check if a given cell (x, y) is within the grid boundaries and is a '1'
bool is_valid(int x, int y, const std::vector<std::vector<char>>& grid, std::vector<std::vector<bool>>& visited) {
    return (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size() && grid[x][y] == '1' && !visited[x][y]);
}

// Perform DFS to find all connected '1's starting from (x, y)
void dfs(int x, int y, const std::vector<std::vector<char>>& grid, std::vector<std::vector<bool>>& visited, std::vector<std::pair<int, int>>& cluster) {
    static const std::vector<std::pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    std::stack<std::pair<int, int>> stack;
    stack.push({x, y});
    visited[x][y] = true;

    while (!stack.empty()) {
        auto [cx, cy] = stack.top();
        stack.pop();
        cluster.push_back({cx, cy});

        for (const auto& [dx, dy] : directions) {
            int nx = cx + dx;
            int ny = cy + dy;
            if (is_valid(nx, ny, grid, visited)) {
                visited[nx][ny] = true;
                stack.push({nx, ny});
            }
        }
    }
}

// Main function to find clusters in the grid
std::vector<std::vector<std::pair<int, int>>> clustering(const std::vector<std::vector<char>>& grid) {
    std::vector<std::vector<std::pair<int, int>>> clusters;
    if (grid.empty() || grid[0].empty()) {
        return clusters;
    }

    std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == '1' && !visited[i][j]) {
                std::vector<std::pair<int, int>> cluster;
                dfs(i, j, grid, visited, cluster);
                clusters.push_back(cluster);
            }
        }
    }

    return clusters;
}

// Uncomment the following main function to test the clustering function
/*
int main() {
    std::vector<std::vector<char>> grid = {
        {'1', '0', '1'},
        {'0', '1', '0'},
        {'1', '0', '1'}
    };

    auto clusters = clustering(grid);
    for (const auto& cluster : clusters) {
        std::cout << "Cluster: ";
        for (const auto& [x, y] : cluster) {
            std::cout << "(" << x << ", " << y << ") ";
        }
        std::cout << std::endl;
    }

    return 0;
}
*/
