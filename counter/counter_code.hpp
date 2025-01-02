// TOKENS: 1469 (of:8000) = 554 + 915(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: counter/counter_code.cpp 
// dest: counter/counter_code.cpp 
/**
 * @file counter_code.hpp
 * @brief Declaration of the SafeCounter class.
 * 
 * This file contains the declaration of the SafeCounter class, which provides
 * a thread-safe mechanism to increment, decrement, and retrieve a counter value.
 * The counter is initialized to zero and is always non-negative.
 * 
 * Date: 2025-01-02
 */

#ifndef COUNTER_CODE_HPP
#define COUNTER_CODE_HPP

#include <mutex>

class SafeCounter {
public:
    /**
     * @brief Constructs a new SafeCounter object with an initial value of zero.
     */
    SafeCounter();

    /**
     * @brief Increments the counter by one.
     * 
     * This method is thread-safe and will increase the counter value by one.
     */
    void increment();

    /**
     * @brief Decrements the counter by one.
     * 
     * This method is thread-safe and will decrease the counter value by one.
     * If the counter is zero, it throws an std::underflow_error.
     */
    void decrement();

    /**
     * @brief Retrieves the current value of the counter.
     * 
     * This method is thread-safe and returns the current counter value.
     * 
     * @return int The current value of the counter.
     */
    int getValue() const;

    /**
     * @brief Enables or disables debug mode.
     * 
     * When debug mode is enabled, debug information will be printed to stderr.
     * 
     * @param enable Boolean flag to enable or disable debug mode.
     */
    void setDebug(bool enable);

private:
    mutable std::mutex mutex; ///< Mutex for thread-safe operations.
    int counter; ///< The counter value, always non-negative.
    bool debug_enable; ///< Flag to enable or disable debug mode.
};

#endif // COUNTER_CODE_HPP
