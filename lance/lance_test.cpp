// TOKENS: 2917 (of:8000) = 1657 + 1260(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_gtest.yaml 
// code: lance/lance_code.cpp 
// dest: lance/lance_test.cpp 
// File: lance/lance_test.cpp
// Description: Unit tests for the Clustering class using Google Test framework.
// Tests cover normal, edge, and error conditions for the findClusters function.

#include "clustering.hpp"
#include <gtest/gtest.h>

class ClusteringTest : public ::testing::Test {
protected:
    Clustering clustering;

    ClusteringTest() : clustering(false) {}
};

TEST_F(ClusteringTest, SingleClusterDiagonal) {
    Grid grid = {
        {'1', '0', '1'},
        {'0', '1', '0'},
        {'1', '0', '1'}
    };
    Clusters expected = {{{0, 0}, {0, 2}, {1, 1}, {2, 0}, {2, 2}}};
    Clusters result = clustering.findClusters(grid);
    EXPECT_EQ(result.size(), expected.size());
    for (const auto& cluster : expected) {
        EXPECT_NE(std::find(result.begin(), result.end(), cluster), result.end());
    }
}

TEST_F(ClusteringTest, CheckerboardPattern) {
    Grid grid = {
        {'1', '0', '1', '0'},
        {'0', '1', '0', '1'},
        {'1', '0', '1', '0'},
        {'0', '1', '0', '1'}
    };
    Clusters expected = {{{0, 0}, {0, 2}, {1, 1}, {1, 3}, {2, 0}, {2, 2}, {3, 1}, {3, 3}}};
    Clusters result = clustering.findClusters(grid);
    EXPECT_EQ(result.size(), expected.size());
    for (const auto& cluster : expected) {
        EXPECT_NE(std::find(result.begin(), result.end(), cluster), result.end());
    }
}

TEST_F(ClusteringTest, MultipleClusters) {
    Grid grid = {
        {'1', '0', '0', '1'},
        {'0', '1', '0', '0'},
        {'1', '0', '1', '1'},
        {'0', '0', '0', '1'}
    };
    Clusters expected = {{{0, 0}, {1, 1}, {2, 0}, {2, 2}, {2, 3}, {3, 3}}, {{0, 3}}};
    Clusters result = clustering.findClusters(grid);
    EXPECT_EQ(result.size(), expected.size());
    for (const auto& cluster : expected) {
        EXPECT_NE(std::find(result.begin(), result.end(), cluster), result.end());
    }
}

TEST_F(ClusteringTest, IdentityMatrix16x16) {
    Grid grid(16, std::vector<char>(16, '0'));
    for (int i = 0; i < 16; ++i) {
        grid[i][i] = '1';
    }
    Clusters expected = {{{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7},
                          {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}}};
    Clusters result = clustering.findClusters(grid);
    EXPECT_EQ(result.size(), expected.size());
    for (const auto& cluster : expected) {
        EXPECT_NE(std::find(result.begin(), result.end(), cluster), result.end());
    }
}

TEST_F(ClusteringTest, EmptyGrid) {
    Grid grid = {};
    EXPECT_THROW(clustering.findClusters(grid), std::invalid_argument);
}

TEST_F(ClusteringTest, SingleCellCluster) {
    Grid grid = {{'1'}};
    Clusters expected = {{{0, 0}}};
    Clusters result = clustering.findClusters(grid);
    EXPECT_EQ(result.size(), expected.size());
    for (const auto& cluster : expected) {
        EXPECT_NE(std::find(result.begin(), result.end(), cluster), result.end());
    }
}

TEST_F(ClusteringTest, NoClusters) {
    Grid grid = {
        {'0', '0', '0'},
        {'0', '0', '0'},
        {'0', '0', '0'}
    };
    Clusters expected = {};
    Clusters result = clustering.findClusters(grid);
    EXPECT_EQ(result.size(), expected.size());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
