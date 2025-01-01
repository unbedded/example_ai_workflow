// TOKENS: 1366 (of:8000) = 505 + 861(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: example_code.cpp 
// dest: example_code.cpp 
// example.hpp
// Header file for the example module
// Date: 2023-10-05
// Provides declarations for generating random numbers and computing Fibonacci numbers.

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <stdexcept>

// Function to generate a list of random numbers
std::vector<int> generate_random_numbers(int count, int min, int max);

// Function to compute Fibonacci number
int compute_fibonacci(int n);

// Main example function
void example(bool debug_enable = false);

// Inline function to print debug messages
inline void debug_print(const std::string& message, bool debug_enable) {
    if (debug_enable) {
        std::cerr << "DEBUG: " << message << std::endl;
    }
}
