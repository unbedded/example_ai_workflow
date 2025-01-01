// TOKENS: 1777 (of:8000) = 1058 + 719(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_gtest.yaml 
// code: fibonacci/fibonacci_code.cpp 
// dest: fibonacci/fibonacci_test.cpp 
// fibonacci/fibonacci_test.cpp
/*
 * Fibonacci Test Suite
 * 
 * This file contains unit tests for the Fibonacci class, which calculates Fibonacci numbers.
 * The tests cover normal, edge, and error conditions to ensure robustness and correctness.
 * 
 * Date: 2023-10-05
 */

#include <gtest/gtest.h>
#include "fibonacci_code.hpp"

// Test fixture for Fibonacci tests
class FibonacciTest : public ::testing::Test {
protected:
    Fibonacci* fibonacci;

    void SetUp() override {
        fibonacci = new Fibonacci(20); // Set a reasonable max index for testing
    }

    void TearDown() override {
        delete fibonacci;
    }
};

// Test normal conditions
TEST_F(FibonacciTest, ReturnsCorrectFibonacciNumbers) {
    EXPECT_EQ(fibonacci->get(0), 0);
    EXPECT_EQ(fibonacci->get(1), 1);
    EXPECT_EQ(fibonacci->get(2), 1);
    EXPECT_EQ(fibonacci->get(3), 2);
    EXPECT_EQ(fibonacci->get(4), 3);
    EXPECT_EQ(fibonacci->get(5), 5);
    EXPECT_EQ(fibonacci->get(10), 55);
    EXPECT_EQ(fibonacci->get(20), 6765);
}

// Test edge conditions
TEST_F(FibonacciTest, HandlesEdgeCases) {
    EXPECT_THROW(fibonacci->get(-1), std::invalid_argument);
    EXPECT_THROW(fibonacci->get(21), std::invalid_argument); // Beyond max_index
}

// Test debug functionality
TEST_F(FibonacciTest, DebugOutput) {
    testing::internal::CaptureStderr();
    fibonacci->set_debug(true);
    fibonacci->get(5);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_NE(output.find("DEBUG: Cache hit for index: 5"), std::string::npos);
}

// Parameterized test for a range of Fibonacci numbers
class FibonacciParamTest : public FibonacciTest, public ::testing::WithParamInterface<std::pair<int, int>> {};

TEST_P(FibonacciParamTest, ReturnsCorrectFibonacciNumbers) {
    int index = GetParam().first;
    int expected_value = GetParam().second;
    EXPECT_EQ(fibonacci->get(index), expected_value);
}

INSTANTIATE_TEST_SUITE_P(
    FibonacciValues,
    FibonacciParamTest,
    ::testing::Values(
        std::make_pair(0, 0),
        std::make_pair(1, 1),
        std::make_pair(2, 1),
        std::make_pair(3, 2),
        std::make_pair(4, 3),
        std::make_pair(5, 5),
        std::make_pair(6, 8),
        std::make_pair(7, 13),
        std::make_pair(8, 21),
        std::make_pair(9, 34),
        std::make_pair(10, 55)
    )
);

// Test invalid operations
TEST_F(FibonacciTest, ThrowsOnInvalidIndex) {
    EXPECT_THROW(fibonacci->get(-10), std::invalid_argument);
    EXPECT_THROW(fibonacci->get(1000), std::invalid_argument); // Beyond reasonable max_index
}
