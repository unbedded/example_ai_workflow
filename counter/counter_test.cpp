// TOKENS: 2259 (of:8000) = 1482 + 777(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_gtest.yaml 
// code: counter/counter_code.cpp 
// dest: counter/counter_test.cpp 
/**
 * @file counter_test.cpp
 * @brief Unit tests for the SafeCounter class.
 * 
 * This file contains unit tests for the SafeCounter class, which provides
 * a thread-safe mechanism to increment, decrement, and retrieve a counter value.
 * The tests cover normal, edge, and error conditions to ensure the class behaves
 * as expected across a wide range of inputs. Tests are organized for clarity and
 * maintainability, using Google Test fixtures and parameterized tests where appropriate.
 * 
 * Date: 2025-01-02
 */

#include "counter_code.hpp"
#include <gtest/gtest.h>
#include <stdexcept>

// Test fixture for SafeCounter
class SafeCounterTest : public ::testing::Test {
protected:
    SafeCounter counter;

    void SetUp() override {
        counter.setDebug(false); // Disable debug mode for testing
    }
};

// Test initial state of the counter
TEST_F(SafeCounterTest, InitialState) {
    EXPECT_EQ(counter.getValue(), 0);
}

// Test incrementing the counter
TEST_F(SafeCounterTest, Increment) {
    counter.increment();
    EXPECT_EQ(counter.getValue(), 1);
}

// Test decrementing the counter
TEST_F(SafeCounterTest, Decrement) {
    counter.increment();
    counter.decrement();
    EXPECT_EQ(counter.getValue(), 0);
}

// Test decrementing the counter when it is zero
TEST_F(SafeCounterTest, DecrementWhenZero) {
    EXPECT_THROW(counter.decrement(), std::underflow_error);
}

// Test multiple increments
TEST_F(SafeCounterTest, MultipleIncrements) {
    for (int i = 0; i < 100; ++i) {
        counter.increment();
    }
    EXPECT_EQ(counter.getValue(), 100);
}

// Test multiple decrements
TEST_F(SafeCounterTest, MultipleDecrements) {
    for (int i = 0; i < 100; ++i) {
        counter.increment();
    }
    for (int i = 0; i < 100; ++i) {
        counter.decrement();
    }
    EXPECT_EQ(counter.getValue(), 0);
}

// Test decrementing below zero throws exception
TEST_F(SafeCounterTest, DecrementBelowZeroThrows) {
    counter.increment();
    counter.decrement();
    EXPECT_THROW(counter.decrement(), std::underflow_error);
}

// Test enabling and disabling debug mode
TEST_F(SafeCounterTest, DebugModeToggle) {
    counter.setDebug(true);
    counter.increment(); // Should print debug info
    counter.setDebug(false);
    counter.increment(); // Should not print debug info
    EXPECT_EQ(counter.getValue(), 2);
}

// Parameterized test for incrementing and decrementing
class SafeCounterParamTest : public SafeCounterTest, public ::testing::WithParamInterface<int> {};

TEST_P(SafeCounterParamTest, IncrementDecrement) {
    int steps = GetParam();
    for (int i = 0; i < steps; ++i) {
        counter.increment();
    }
    EXPECT_EQ(counter.getValue(), steps);

    for (int i = 0; i < steps; ++i) {
        counter.decrement();
    }
    EXPECT_EQ(counter.getValue(), 0);
}

INSTANTIATE_TEST_SUITE_P(
    IncrementDecrementTests,
    SafeCounterParamTest,
    ::testing::Values(1, 10, 100, 1000)
);
