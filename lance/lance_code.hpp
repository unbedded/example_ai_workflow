// TOKENS: 1403 (of:8000) = 655 + 748(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: lance/lance_code.cpp 
// dest: lance/lance_code.cpp 
#ifndef CLUSTERING_HPP
#define CLUSTERING_HPP

#include <vector>
#include <utility>
#include <string>
#include <iostream>

// File: clustering.hpp
// Date: 2023-10-05
// Description: Header file for clustering connected components in a 2D grid.

using Grid = std::vector<std::vector<char>>;
using Cluster = std::vector<std::pair<int, int>>;
using Clusters = std::vector<Cluster>;

class Clustering {
public:
    Clustering(bool debug_enable = false);

    // Function to find all clusters in the given grid.
    Clusters findClusters(const Grid& grid);

private:
    bool debug_enable_;

    // Helper function to perform DFS and mark visited cells.
    void dfs(const Grid& grid, int x, int y, Cluster& cluster, std::vector<std::vector<bool>>& visited);

    // Function to print debug information.
    void debugPrint(const std::string& message) const;
};

#endif // CLUSTERING_HPP
