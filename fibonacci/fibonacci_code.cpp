// TOKENS: 1509 (of:8000) = 592 + 917(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: fibonacci/fibonacci_code.cpp 
// dest: fibonacci/fibonacci_code.cpp 
/**
 * @file fibonacci_code.cpp
 * @brief Implementation of the Fibonacci class for calculating Fibonacci numbers.
 * 
 * This file contains the implementation of the Fibonacci class, which provides
 * functionality to calculate Fibonacci numbers up to a specified index. The
 * class uses caching to optimize performance by storing previously calculated
 * Fibonacci numbers.
 * 
 * @date 2025-01-02
 */

#include "fibonacci_code.hpp"

Fibonacci::Fibonacci(int max_index) : max_index_(max_index), debug_enable_(false) {
    if (max_index_ <= 0) {
        throw std::invalid_argument("Maximum index must be a positive integer.");
    }
    cache_.resize(max_index_ + 1, -1);
    cache_[0] = 0;
    cache_[1] = 1;
}

int Fibonacci::get(int index) {
    if (index < 0) {
        throw std::invalid_argument("Index must be a positive integer.");
    }
    if (index > max_index_) {
        throw std::out_of_range("Index exceeds the maximum allowed index.");
    }
    if (cache_[index] != -1) {
        debug_print("Cache hit for index " + std::to_string(index));
        return cache_[index];
    }
    debug_print("Calculating Fibonacci for index " + std::to_string(index));
    cache_[index] = get(index - 1) + get(index - 2);
    return cache_[index];
}

void Fibonacci::set_debug(bool enable) {
    debug_enable_ = enable;
}

void Fibonacci::debug_print(const std::string& message) {
    if (debug_enable_) {
        std::cerr << "DEBUG: " << message << std::endl;
    }
}

// Uncomment the following main function to test the Fibonacci class.
/*
int main() {
    try {
        Fibonacci fib(20);
        fib.set_debug(true);
        std::cout << "Fibonacci(10): " << fib.get(10) << std::endl;
        std::cout << "Fibonacci(15): " << fib.get(15) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
*/
