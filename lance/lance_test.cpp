// TOKENS: 2952 (of:8000) = 1843 + 1109(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_gtest.yaml 
// code: lance/lance_code.cpp 
// dest: lance/lance_test.cpp 
// lance/lance_test.cpp
/**
 * @file lance_test.cpp
 * @brief Unit tests for clustering connected components in a 2D grid.
 * 
 * This file contains unit tests for the functions defined in lance_code.cpp
 * which identify clusters of connected '1's in a 2D grid using Depth-First Search (DFS).
 * 
 * Date: 2023-10-05
 */

#include "lance_code.hpp"
#include <gtest/gtest.h>
#include <algorithm>

// Helper function to compare two clusters irrespective of order
bool compareClusters(const Cluster& a, const Cluster& b) {
    if (a.size() != b.size()) return false;
    std::vector<std::pair<int, int>> sorted_a = a;
    std::vector<std::pair<int, int>> sorted_b = b;
    std::sort(sorted_a.begin(), sorted_a.end());
    std::sort(sorted_b.begin(), sorted_b.end());
    return sorted_a == sorted_b;
}

// Helper function to compare two lists of clusters irrespective of order
bool compareClustersList(const Clusters& a, const Clusters& b) {
    if (a.size() != b.size()) return false;
    for (const auto& cluster_a : a) {
        bool found = false;
        for (const auto& cluster_b : b) {
            if (compareClusters(cluster_a, cluster_b)) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

class ClusteringTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Teardown code if needed
    }
};

TEST_F(ClusteringTest, SingleClusterDiagonal) {
    Grid grid = {
        {'1', '0', '1'},
        {'0', '1', '0'},
        {'1', '0', '1'}
    };
    Clusters expected = {{{0, 0}, {0, 2}, {1, 1}, {2, 0}, {2, 2}}};
    Clusters result = clustring(grid);
    EXPECT_TRUE(compareClustersList(result, expected));
}

TEST_F(ClusteringTest, MultipleClusters) {
    Grid grid = {
        {'1', '0', '0', '1'},
        {'0', '1', '0', '0'},
        {'1', '0', '1', '1'},
        {'0', '0', '0', '1'}
    };
    Clusters expected = {{{0, 0}, {1, 1}, {2, 0}, {2, 2}, {2, 3}, {3, 3}}, {{0, 3}}};
    Clusters result = clustring(grid);
    EXPECT_TRUE(compareClustersList(result, expected));
}

TEST_F(ClusteringTest, CheckerboardPattern) {
    Grid grid = {
        {'1', '0', '1', '0'},
        {'0', '1', '0', '1'},
        {'1', '0', '1', '0'},
        {'0', '1', '0', '1'}
    };
    Clusters expected = {{{0, 0}, {0, 2}, {1, 1}, {1, 3}, {2, 0}, {2, 2}, {3, 1}, {3, 3}}};
    Clusters result = clustring(grid);
    EXPECT_TRUE(compareClustersList(result, expected));
}

TEST_F(ClusteringTest, IdentityMatrix16x16) {
    Grid grid(16, std::vector<char>(16, '0'));
    for (int i = 0; i < 16; ++i) {
        grid[i][i] = '1';
    }
    Clusters expected = {{{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}}};
    Clusters result = clustring(grid);
    EXPECT_TRUE(compareClustersList(result, expected));
}

TEST_F(ClusteringTest, EmptyGrid) {
    Grid grid = {};
    Clusters expected = {};
    Clusters result = clustring(grid);
    EXPECT_TRUE(compareClustersList(result, expected));
}

TEST_F(ClusteringTest, SingleCellCluster) {
    Grid grid = {
        {'0', '0', '0'},
        {'0', '1', '0'},
        {'0', '0', '0'}
    };
    Clusters expected = {{{1, 1}}};
    Clusters result = clustring(grid);
    EXPECT_TRUE(compareClustersList(result, expected));
}
