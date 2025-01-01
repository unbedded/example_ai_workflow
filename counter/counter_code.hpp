// TOKENS: 979 (of:8000) = 469 + 510(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: counter/counter_code.cpp 
// dest: counter/counter_code.cpp 
// SafeCounter.hpp
// Header file for the SafeCounter class
// Date: 2023-10-05

#pragma once

#include <mutex>
#include <iostream>

class SafeCounter {
public:
    // Constructor initializes the counter to zero
    SafeCounter();

    // Increments the counter by one
    void increment();

    // Decrements the counter by one, ensuring it remains non-negative
    void decrement();

    // Retrieves the current value of the counter
    int getValue() const;

    // Enables or disables debug output
    void setDebug(bool enable);

private:
    mutable std::mutex mtx; // Mutex to ensure thread safety
    int counter;            // Counter value
    bool debug_enable;      // Debug flag

    // Prints debug information if debug is enabled
    void debugPrint(const std::string& message) const;
};
