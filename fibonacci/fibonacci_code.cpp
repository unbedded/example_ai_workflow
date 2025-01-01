// TOKENS: 1228 (of:8000) = 509 + 719(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: fibonacci/fibonacci_code.cpp 
// dest: fibonacci/fibonacci_code.cpp 
/*
 * Fibonacci.cpp
 * 
 * Implements the Fibonacci class, which calculates Fibonacci numbers.
 * 
 * Date: 2023-10-05
 */

#include "Fibonacci.hpp"

Fibonacci::Fibonacci(int max_index)
    : max_index_(max_index), debug_enable_(false) {
    if (max_index_ < 0) {
        throw std::invalid_argument("Maximum index must be non-negative.");
    }
    cache_.resize(max_index_ + 1, -1);
    cache_[0] = 0;
    if (max_index_ > 0) {
        cache_[1] = 1;
    }
}

int Fibonacci::get(int index) const {
    if (index < 0 || index > max_index_) {
        throw std::invalid_argument("Index must be a non-negative integer within the allowed range.");
    }

    if (cache_[index] != -1) {
        debug_print("Cache hit for index: " + std::to_string(index));
        return cache_[index];
    }

    debug_print("Calculating Fibonacci for index: " + std::to_string(index));
    cache_[index] = get(index - 1) + get(index - 2);
    return cache_[index];
}

void Fibonacci::set_debug(bool enable) {
    debug_enable_ = enable;
}

void Fibonacci::debug_print(const std::string& message) const {
    if (debug_enable_) {
        std::cerr << "DEBUG: " << message << std::endl;
    }
}
