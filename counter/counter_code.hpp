// TOKENS: 1230 (of:8000) = 477 + 753(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: counter/counter_code.cpp 
// dest: counter/counter_code.cpp 
/**
 * @file counter_code.hpp
 * @brief Declaration of the SafeCounter class for thread-safe counter operations.
 * @date 2023-10-05
 *
 * This header file declares the SafeCounter class, which provides a thread-safe
 * mechanism to increment, decrement, and retrieve a counter value. The counter
 * is initialized to zero and ensures that its value is always non-negative.
 * The class is designed to minimize performance impact under high concurrency.
 */

#pragma once

#include <mutex>
#include <iostream>

class SafeCounter {
public:
    /**
     * @brief Constructs a SafeCounter with an initial value of zero.
     */
    SafeCounter();

    /**
     * @brief Increments the counter by one.
     */
    void increment();

    /**
     * @brief Decrements the counter by one, ensuring it does not go below zero.
     */
    void decrement();

    /**
     * @brief Retrieves the current value of the counter.
     * @return The current counter value.
     */
    int getValue() const;

    /**
     * @brief Enables or disables debug output.
     * @param enable True to enable debug output, false to disable.
     */
    void setDebug(bool enable);

private:
    mutable std::mutex mtx_; ///< Mutex for synchronizing access to the counter.
    int counter_; ///< The counter value, always non-negative.
    bool debug_enable_; ///< Flag to control debug output.

    /**
     * @brief Prints a debug message if debugging is enabled.
     * @param message The message to print.
     */
    void debugPrint(const std::string& message) const;
};
