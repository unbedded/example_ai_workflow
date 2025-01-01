// TOKENS: 1892 (of:8000) = 1214 + 678(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: example_code.cpp 
// dest: example_code.cpp 
/*
 * example.hpp
 * 
 * Provides declarations for the example function and main execution.
 * 
 * Date: 2023-10-05
 */

#pragma once

#include <vector>
#include <iostream>
#include <random>
#include "fibonacci/fibonacci_code.hpp"

// Function to demonstrate the Fibonacci calculation on random numbers
void example();
