// TOKENS: 2197 (of:8000) = 1295 + 902(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_gtest.yaml 
// code: counter/counter_code.cpp 
// dest: counter/counter_test.cpp 
/**
 * @file counter_test.cpp
 * @brief Unit tests for the SafeCounter class using Google Test framework.
 * @date 2023-10-05
 *
 * This file contains unit tests for the SafeCounter class, which provides
 * thread-safe operations to increment, decrement, and retrieve a counter value.
 * The tests cover normal operations, edge cases, and invalid operations to ensure
 * the counter behaves as expected under various conditions.
 */

#include <gtest/gtest.h>
#include "counter_code.hpp"

// Test fixture for SafeCounter tests
class SafeCounterTest : public ::testing::Test {
protected:
    SafeCounter counter;

    void SetUp() override {
        // Enable debug mode for detailed logging during tests
        counter.setDebug(true);
    }

    void TearDown() override {
        // Disable debug mode after tests
        counter.setDebug(false);
    }
};

// Test case for initial state of the counter
TEST_F(SafeCounterTest, InitialState) {
    EXPECT_EQ(counter.getValue(), 0) << "Counter should be initialized to zero.";
}

// Test case for incrementing the counter
TEST_F(SafeCounterTest, Increment) {
    counter.increment();
    EXPECT_EQ(counter.getValue(), 1) << "Counter should be incremented to one.";
}

// Test case for decrementing the counter
TEST_F(SafeCounterTest, Decrement) {
    counter.increment();
    counter.decrement();
    EXPECT_EQ(counter.getValue(), 0) << "Counter should be decremented back to zero.";
}

// Test case for decrementing the counter below zero
TEST_F(SafeCounterTest, DecrementBelowZero) {
    counter.decrement();
    EXPECT_EQ(counter.getValue(), 0) << "Counter should not go below zero.";
}

// Test case for multiple increments
TEST_F(SafeCounterTest, MultipleIncrements) {
    for (int i = 0; i < 5; ++i) {
        counter.increment();
    }
    EXPECT_EQ(counter.getValue(), 5) << "Counter should be incremented to five.";
}

// Test case for multiple decrements
TEST_F(SafeCounterTest, MultipleDecrements) {
    for (int i = 0; i < 5; ++i) {
        counter.increment();
    }
    for (int i = 0; i < 5; ++i) {
        counter.decrement();
    }
    EXPECT_EQ(counter.getValue(), 0) << "Counter should be decremented back to zero.";
}

// Test case for concurrent increments
TEST_F(SafeCounterTest, ConcurrentIncrements) {
    const int num_threads = 10;
    const int increments_per_thread = 1000;
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&]() {
            for (int j = 0; j < increments_per_thread; ++j) {
                counter.increment();
            }
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    EXPECT_EQ(counter.getValue(), num_threads * increments_per_thread)
        << "Counter should reflect all concurrent increments.";
}

// Test case for concurrent decrements
TEST_F(SafeCounterTest, ConcurrentDecrements) {
    const int num_threads = 10;
    const int increments_per_thread = 1000;
    std::vector<std::thread> threads;

    // First increment the counter
    for (int i = 0; i < num_threads * increments_per_thread; ++i) {
        counter.increment();
    }

    // Then decrement concurrently
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&]() {
            for (int j = 0; j < increments_per_thread; ++j) {
                counter.decrement();
            }
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    EXPECT_EQ(counter.getValue(), 0) << "Counter should be zero after concurrent decrements.";
}
