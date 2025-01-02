// TOKENS: 1509 (of:8000) = 592 + 917(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: fibonacci/fibonacci_code.cpp 
// dest: fibonacci/fibonacci_code.cpp 
/**
 * @file fibonacci_code.hpp
 * @brief Declaration of the Fibonacci class for calculating Fibonacci numbers.
 * 
 * This file contains the declaration of the Fibonacci class, which provides
 * functionality to calculate Fibonacci numbers up to a specified index. The
 * class uses caching to optimize performance by storing previously calculated
 * Fibonacci numbers.
 * 
 * @date 2025-01-02
 */

#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>

class Fibonacci {
public:
    /**
     * @brief Constructs a Fibonacci object with an optional maximum index.
     * 
     * @param max_index The maximum index for which Fibonacci numbers will be calculated.
     *                  Defaults to 1000 if not specified.
     */
    explicit Fibonacci(int max_index = 1000);

    /**
     * @brief Retrieves the Fibonacci number at the specified index.
     * 
     * @param index The index of the Fibonacci number to retrieve.
     * @return The Fibonacci number at the specified index.
     * @throws std::invalid_argument if the index is not a positive integer.
     * @throws std::out_of_range if the index exceeds the maximum allowed index.
     */
    int get(int index);

    /**
     * @brief Enables or disables debug output.
     * 
     * @param enable Set to true to enable debug output, false to disable.
     */
    void set_debug(bool enable);

private:
    std::vector<int> cache_; ///< Cache to store calculated Fibonacci numbers.
    int max_index_; ///< Maximum index for Fibonacci calculation.
    bool debug_enable_; ///< Flag to control debug output.

    /**
     * @brief Prints a debug message if debugging is enabled.
     * 
     * @param message The debug message to print.
     */
    void debug_print(const std::string& message);
};
