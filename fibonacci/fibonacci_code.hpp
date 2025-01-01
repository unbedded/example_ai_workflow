// TOKENS: 1228 (of:8000) = 509 + 719(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: fibonacci/fibonacci_code.cpp 
// dest: fibonacci/fibonacci_code.cpp 
/*
 * Fibonacci.hpp
 * 
 * Provides declarations for the Fibonacci class, which calculates Fibonacci numbers.
 * 
 * Date: 2023-10-05
 */

#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>

class Fibonacci {
public:
    // Constructor with an optional maximum index for Fibonacci sequence
    explicit Fibonacci(int max_index = 100);

    // Returns the Fibonacci number at the specified index
    // Throws std::invalid_argument if the index is negative or non-integer
    int get(int index) const;

    // Enable or disable debug output
    void set_debug(bool enable);

private:
    // Caches calculated Fibonacci numbers
    mutable std::vector<int> cache_;

    // Maximum index allowed for Fibonacci calculation
    int max_index_;

    // Debug flag
    bool debug_enable_;

    // Helper function to print debug messages
    void debug_print(const std::string& message) const;
};
