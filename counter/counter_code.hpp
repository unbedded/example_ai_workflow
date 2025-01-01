// TOKENS: 1068 (of:8000) = 421 + 647(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: counter/counter_code.cpp 
// dest: counter/counter_code.cpp 
#ifndef SAFE_COUNTER_HPP
#define SAFE_COUNTER_HPP

#include <iostream>
#include <stdexcept>
#include <string>

/**
 * @file safe_counter.hpp
 * @brief Declaration of the SafeCounter class for managing a non-negative counter.
 * @date 2023-10-05
 */

class SafeCounter {
public:
    /**
     * @brief Constructs a new SafeCounter object initialized to zero.
     */
    SafeCounter();

    /**
     * @brief Increments the counter by one.
     * @throws std::overflow_error if the counter exceeds the maximum allowed value.
     */
    void increment();

    /**
     * @brief Decrements the counter by one.
     * @throws std::underflow_error if the counter is already zero.
     */
    void decrement();

    /**
     * @brief Retrieves the current value of the counter.
     * @return The current counter value.
     */
    int getValue() const;

    /**
     * @brief Enables or disables debug mode.
     * @param enable True to enable debug mode, false to disable.
     */
    void setDebugMode(bool enable);

private:
    int counter; ///< The current value of the counter.
    bool debug_enable; ///< Flag to control debug output.

    /**
     * @brief Prints a debug message if debug mode is enabled.
     * @param message The message to print.
     */
    void debugPrint(const std::string& message) const;
};

#endif // SAFE_COUNTER_HPP
