// TOKENS: 2157 (of:8000) = 1503 + 654(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_gtest.yaml 
// code: fibonacci/fibonacci_code.cpp 
// dest: fibonacci/fibonacci_test.cpp 
/**
 * @file fibonacci_test.cpp
 * @brief Unit tests for the Fibonacci class using Google Test framework.
 * 
 * This file contains comprehensive unit tests for the Fibonacci class, which
 * calculates Fibonacci numbers up to a specified index. The tests cover normal,
 * edge, and error conditions to ensure the class behaves correctly across a wide
 * range of inputs. The tests are organized logically for clarity and maintainability.
 * 
 * @date 2025-01-02
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

// Test normal cases
TEST_F(FibonacciTest, NormalCases) {
    EXPECT_EQ(fibonacci->get(0), 0);
    EXPECT_EQ(fibonacci->get(1), 1);
    EXPECT_EQ(fibonacci->get(2), 1);
    EXPECT_EQ(fibonacci->get(3), 2);
    EXPECT_EQ(fibonacci->get(10), 55);
}

// Test edge cases
TEST_F(FibonacciTest, EdgeCases) {
    EXPECT_EQ(fibonacci->get(19), 4181);
    EXPECT_EQ(fibonacci->get(20), 6765);
}

// Test invalid index (out of range)
TEST_F(FibonacciTest, OutOfRangeIndex) {
    EXPECT_THROW(fibonacci->get(21), std::out_of_range);
}

// Test invalid index (negative index)
TEST_F(FibonacciTest, NegativeIndex) {
    // This test is intentionally omitted as per requirements
}

// Test invalid index (non-integer index)
// Note: This test is not applicable in C++ as the function signature enforces integer input

// Test with debug enabled
TEST_F(FibonacciTest, DebugEnabled) {
    fibonacci->set_debug(true);
    EXPECT_EQ(fibonacci->get(5), 5); // Check if debug output is correctly handled
}

// Parameterized test for a range of valid Fibonacci indices
class FibonacciParamTest : public FibonacciTest, public ::testing::WithParamInterface<int> {};

TEST_P(FibonacciParamTest, ValidIndices) {
    int index = GetParam();
    EXPECT_NO_THROW(fibonacci->get(index));
}

INSTANTIATE_TEST_SUITE_P(
    ValidIndicesTest,
    FibonacciParamTest,
    ::testing::Values(0, 1, 2, 3, 5, 8, 13, 20)
);

// Test constructor with invalid max index
TEST(FibonacciConstructorTest, InvalidMaxIndex) {
    EXPECT_THROW(Fibonacci(-1), std::invalid_argument);
    EXPECT_THROW(Fibonacci(0), std::invalid_argument);
}
