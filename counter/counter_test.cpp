// TOKENS: 2061 (of:8000) = 1140 + 921(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_gtest.yaml 
// code: counter/counter_code.cpp 
// dest: counter/counter_test.cpp 
// counter/counter_test.cpp
// Unit tests for the SafeCounter class using Google Test framework.
// This file tests the increment, decrement, and getValue methods, including edge cases and invalid operations.
// It also tests the debug mode functionality.

#include <gtest/gtest.h>
#include "safe_counter.hpp"
#include <limits>
#include <stdexcept>

class SafeCounterTest : public ::testing::Test {
protected:
    SafeCounter counter;

    void SetUp() override {
        counter.setDebugMode(false); // Ensure debug mode is off for consistent test output
    }
};

TEST_F(SafeCounterTest, InitialValueIsZero) {
    EXPECT_EQ(counter.getValue(), 0);
}

TEST_F(SafeCounterTest, IncrementIncreasesValue) {
    counter.increment();
    EXPECT_EQ(counter.getValue(), 1);
}

TEST_F(SafeCounterTest, DecrementDecreasesValue) {
    counter.increment();
    counter.decrement();
    EXPECT_EQ(counter.getValue(), 0);
}

TEST_F(SafeCounterTest, DecrementThrowsUnderflowErrorWhenZero) {
    EXPECT_THROW(counter.decrement(), std::underflow_error);
}

TEST_F(SafeCounterTest, IncrementThrowsOverflowErrorAtMaxValue) {
    counter.setDebugMode(true); // Enable debug mode to observe debug messages
    for (int i = 0; i < std::numeric_limits<int>::max(); ++i) {
        counter.increment();
    }
    EXPECT_THROW(counter.increment(), std::overflow_error);
}

TEST_F(SafeCounterTest, DebugModeOutputsMessages) {
    testing::internal::CaptureStderr();
    counter.setDebugMode(true);
    counter.increment();
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_NE(output.find("[DEBUG] Counter incremented to 1."), std::string::npos);
}

TEST_F(SafeCounterTest, DebugModeCanBeDisabled) {
    testing::internal::CaptureStderr();
    counter.setDebugMode(false);
    counter.increment();
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "");
}

class SafeCounterParameterizedTest : public SafeCounterTest, public ::testing::WithParamInterface<int> {};

TEST_P(SafeCounterParameterizedTest, IncrementAndDecrementMultipleTimes) {
    int times = GetParam();
    for (int i = 0; i < times; ++i) {
        counter.increment();
    }
    EXPECT_EQ(counter.getValue(), times);

    for (int i = 0; i < times; ++i) {
        counter.decrement();
    }
    EXPECT_EQ(counter.getValue(), 0);
}

INSTANTIATE_TEST_SUITE_P(
    SafeCounterTests,
    SafeCounterParameterizedTest,
    ::testing::Values(1, 10, 100, 1000)
);

TEST_F(SafeCounterTest, IncrementAndDecrementBoundaryConditions) {
    counter.increment();
    EXPECT_EQ(counter.getValue(), 1);
    counter.decrement();
    EXPECT_EQ(counter.getValue(), 0);
    EXPECT_THROW(counter.decrement(), std::underflow_error);
}
