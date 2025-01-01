// TOKENS: 2131 (of:8000) = 1014 + 1117(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_gtest.yaml 
// code: counter/counter_code.cpp 
// dest: counter/counter_test.cpp 
// counter/counter_test.cpp
// Unit tests for the SafeCounter class
// Date: 2023-10-05
//
// This file contains unit tests for the SafeCounter class, which provides
// thread-safe operations to increment, decrement, and retrieve a counter value.
// The tests cover normal operations, edge cases, and invalid operations.

#include <gtest/gtest.h>
#include "SafeCounter.hpp"

class SafeCounterTest : public ::testing::Test {
protected:
    SafeCounter counter;

    void SetUp() override {
        counter.setDebug(false); // Disable debug output for tests
    }
};

TEST_F(SafeCounterTest, InitialValueIsZero) {
    EXPECT_EQ(counter.getValue(), 0);
}

TEST_F(SafeCounterTest, IncrementIncreasesValue) {
    counter.increment();
    EXPECT_EQ(counter.getValue(), 1);
}

TEST_F(SafeCounterTest, MultipleIncrements) {
    for (int i = 0; i < 5; ++i) {
        counter.increment();
    }
    EXPECT_EQ(counter.getValue(), 5);
}

TEST_F(SafeCounterTest, DecrementDecreasesValue) {
    counter.increment();
    counter.decrement();
    EXPECT_EQ(counter.getValue(), 0);
}

TEST_F(SafeCounterTest, DecrementDoesNotGoBelowZero) {
    counter.decrement();
    EXPECT_EQ(counter.getValue(), 0);
}

TEST_F(SafeCounterTest, MultipleDecrements) {
    for (int i = 0; i < 3; ++i) {
        counter.increment();
    }
    for (int i = 0; i < 5; ++i) {
        counter.decrement();
    }
    EXPECT_EQ(counter.getValue(), 0);
}

TEST_F(SafeCounterTest, DebugModeOutput) {
    testing::internal::CaptureStderr();
    counter.setDebug(true);
    counter.increment();
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_NE(output.find("[DEBUG] Incremented counter to 1"), std::string::npos);
}

TEST_F(SafeCounterTest, DebugModeToggle) {
    testing::internal::CaptureStderr();
    counter.setDebug(true);
    counter.increment();
    counter.setDebug(false);
    counter.increment();
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_NE(output.find("[DEBUG] Incremented counter to 1"), std::string::npos);
    EXPECT_EQ(output.find("[DEBUG] Incremented counter to 2"), std::string::npos);
}

TEST_F(SafeCounterTest, ConcurrentIncrement) {
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

    EXPECT_EQ(counter.getValue(), num_threads * increments_per_thread);
}

TEST_F(SafeCounterTest, ConcurrentDecrement) {
    const int num_threads = 10;
    const int increments_per_thread = 1000;
    const int decrements_per_thread = 500;
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

    threads.clear();

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&]() {
            for (int j = 0; j < decrements_per_thread; ++j) {
                counter.decrement();
            }
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    EXPECT_EQ(counter.getValue(), num_threads * (increments_per_thread - decrements_per_thread));
}
