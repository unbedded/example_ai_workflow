// TOKENS: 1417 (of:8000) = 514 + 903(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: example_code.cpp 
// dest: example_code.cpp 
/**
 * @file example_code.hpp
 * @brief Header file for generating random numbers and calculating Fibonacci numbers.
 * @date 2023-10-05
 *
 * This file contains the declarations for generating a list of random numbers
 * and calculating their corresponding Fibonacci numbers using modern C++20 standards.
 */

#pragma once

#include <vector>
#include <iostream>
#include <random>
#include <stdexcept>

// Function to calculate Fibonacci number
inline int fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// Function to generate a list of random numbers
std::vector<int> generate_random_numbers(int count, int min, int max);

// Main example function
void example();

// Debugging utility
extern bool debug_enable;
inline void debug_print(const std::string& message) {
    if (debug_enable) {
        std::cerr << message << std::endl;
    }
}
