// TOKENS: 2977 (of:8000) = 1765 + 1212(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_gtest.yaml 
// code: lance/lance_code.cpp 
// dest: lance/lance_test.cpp 
/**
 * @file lance_test.cpp
 * @brief Unit tests for clustering connected components in a 2D grid.
 * @date 2023-10-05
 */

#include "lance_code.hpp"
#include <gtest/gtest.h>
#include <algorithm>

// Helper function to compare clusters without considering order
bool compareClusters(const std::vector<Cluster>& clusters1, const std::vector<Cluster>& clusters2) {
    if (clusters1.size() != clusters2.size()) return false;
    for (const auto& cluster : clusters1) {
        if (std::find(clusters2.begin(), clusters2.end(), cluster) == clusters2.end()) {
            return false;
        }
    }
    return true;
}

class ClustringTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Teardown code if needed
    }
};

TEST_F(ClustringTest, SingleClusterDiagonal) {
    Grid grid = {
        {'1', '0', '1'},
        {'0', '1', '0'},
        {'1', '0', '1'}
    };
    std::vector<Cluster> expected = {{{0, 0}, {0, 2}, {1, 1}, {2, 0}, {2, 2}}};
    auto result = clustring(grid);
    EXPECT_TRUE(compareClusters(result, expected));
}

TEST_F(ClustringTest, MultipleClusters) {
    Grid grid = {
        {'1', '0', '0', '1'},
        {'0', '1', '0', '0'},
        {'1', '0', '1', '1'},
        {'0', '0', '0', '1'}
    };
    std::vector<Cluster> expected = {{{0, 0}, {1, 1}, {2, 0}, {2, 2}, {2, 3}, {3, 3}}, {{0, 3}}};
    auto result = clustring(grid);
    EXPECT_TRUE(compareClusters(result, expected));
}

TEST_F(ClustringTest, CheckerboardPattern) {
    Grid grid = {
        {'1', '0', '1', '0'},
        {'0', '1', '0', '1'},
        {'1', '0', '1', '0'},
        {'0', '1', '0', '1'}
    };
    std::vector<Cluster> expected = {{{0, 0}, {0, 2}, {1, 1}, {1, 3}, {2, 0}, {2, 2}, {3, 1}, {3, 3}}};
    auto result = clustring(grid);
    EXPECT_TRUE(compareClusters(result, expected));
}

TEST_F(ClustringTest, IdentityMatrix16x16) {
    Grid grid(16, std::vector<char>(16, '0'));
    for (int i = 0; i < 16; ++i) {
        grid[i][i] = '1';
    }
    std::vector<Cluster> expected = {{{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}}};
    auto result = clustring(grid);
    EXPECT_TRUE(compareClusters(result, expected));
}

TEST_F(ClustringTest, EmptyGrid) {
    Grid grid = {};
    std::vector<Cluster> expected = {};
    auto result = clustring(grid);
    EXPECT_TRUE(compareClusters(result, expected));
}

TEST_F(ClustringTest, NoClusters) {
    Grid grid = {
        {'0', '0', '0'},
        {'0', '0', '0'},
        {'0', '0', '0'}
    };
    std::vector<Cluster> expected = {};
    auto result = clustring(grid);
    EXPECT_TRUE(compareClusters(result, expected));
}
