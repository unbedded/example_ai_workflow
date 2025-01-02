// TOKENS: 3096 (of:8000) = 2165 + 931(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_gtest.yaml 
// code: lance/lance_code.cpp 
// dest: lance/lance_test.cpp 
/**
 * @file lance_test.cpp
 * @brief Unit tests for the clustering algorithm in lance_code.cpp.
 * 
 * This file contains unit tests for the `clustering` function, which identifies clusters of connected '1's
 * in a 2D grid. The tests cover normal, edge, and error conditions, ensuring the function behaves correctly
 * across a wide range of inputs. The tests are organized for clarity and maintainability, using Google Test
 * fixtures and parameterized tests where appropriate.
 * 
 * Date: 2025-01-02
 */

#include "lance_code.hpp"
#include <gtest/gtest.h>
#include <algorithm>

// Helper function to compare two clusters, allowing for any order of coordinates
bool compareClusters(const std::vector<std::pair<int, int>>& a, const std::vector<std::pair<int, int>>& b) {
    if (a.size() != b.size()) return false;
    std::vector<std::pair<int, int>> sorted_a = a;
    std::vector<std::pair<int, int>> sorted_b = b;
    std::sort(sorted_a.begin(), sorted_a.end());
    std::sort(sorted_b.begin(), sorted_b.end());
    return sorted_a == sorted_b;
}

// Test fixture for clustering tests
class ClusteringTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Teardown code if needed
    }
};

// Test for a single cluster in a checkerboard pattern
TEST_F(ClusteringTest, CheckerboardPattern) {
    std::vector<std::vector<char>> grid = {
        {'1', '0', '1'},
        {'0', '1', '0'},
        {'1', '0', '1'}
    };
    auto clusters = clustering(grid);
    ASSERT_EQ(clusters.size(), 1);
    EXPECT_TRUE(compareClusters(clusters[0], {{0, 0}, {0, 2}, {1, 1}, {2, 0}, {2, 2}}));
}

// Test for multiple clusters
TEST_F(ClusteringTest, MultipleClusters) {
    std::vector<std::vector<char>> grid = {
        {'1', '0', '0', '1'},
        {'0', '1', '0', '0'},
        {'1', '0', '1', '1'},
        {'0', '0', '0', '1'}
    };
    auto clusters = clustering(grid);
    ASSERT_EQ(clusters.size(), 2);
    EXPECT_TRUE(compareClusters(clusters[0], {{0, 0}, {1, 1}, {2, 0}, {2, 2}, {2, 3}, {3, 3}}));
    EXPECT_TRUE(compareClusters(clusters[1], {{0, 3}}));
}

// Test for a single cluster in a 16x16 identity matrix
TEST_F(ClusteringTest, IdentityMatrix) {
    std::vector<std::vector<char>> grid(16, std::vector<char>(16, '0'));
    for (int i = 0; i < 16; ++i) {
        grid[i][i] = '1';
    }
    auto clusters = clustering(grid);
    ASSERT_EQ(clusters.size(), 1);
    std::vector<std::pair<int, int>> expected_cluster;
    for (int i = 0; i < 16; ++i) {
        expected_cluster.emplace_back(i, i);
    }
    EXPECT_TRUE(compareClusters(clusters[0], expected_cluster));
}

// Test for an empty grid
TEST_F(ClusteringTest, EmptyGrid) {
    std::vector<std::vector<char>> grid = {};
    auto clusters = clustering(grid);
    ASSERT_TRUE(clusters.empty());
}

// Test for a grid with no '1's
TEST_F(ClusteringTest, NoClusters) {
    std::vector<std::vector<char>> grid = {
        {'0', '0', '0'},
        {'0', '0', '0'},
        {'0', '0', '0'}
    };
    auto clusters = clustering(grid);
    ASSERT_TRUE(clusters.empty());
}
