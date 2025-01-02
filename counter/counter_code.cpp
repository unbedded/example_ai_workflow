// TOKENS: 1469 (of:8000) = 554 + 915(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: counter/counter_code.cpp 
// dest: counter/counter_code.cpp 
/**
 * @file counter_code.cpp
 * @brief Implementation of the SafeCounter class.
 * 
 * This file contains the implementation of the SafeCounter class, which provides
 * a thread-safe mechanism to increment, decrement, and retrieve a counter value.
 * The counter is initialized to zero and is always non-negative.
 * 
 * Date: 2025-01-02
 */

#include "counter_code.hpp"
#include <iostream>
#include <stdexcept>

SafeCounter::SafeCounter() : counter(0), debug_enable(false) {}

void SafeCounter::increment() {
    std::lock_guard<std::mutex> lock(mutex);
    ++counter;
    if (debug_enable) {
        std::cerr << "Counter incremented to: " << counter << std::endl;
    }
}

void SafeCounter::decrement() {
    std::lock_guard<std::mutex> lock(mutex);
    if (counter == 0) {
        if (debug_enable) {
            std::cerr << "Attempt to decrement when counter is zero." << std::endl;
        }
        throw std::underflow_error("Counter cannot be negative.");
    }
    --counter;
    if (debug_enable) {
        std::cerr << "Counter decremented to: " << counter << std::endl;
    }
}

int SafeCounter::getValue() const {
    std::lock_guard<std::mutex> lock(mutex);
    if (debug_enable) {
        std::cerr << "Counter value retrieved: " << counter << std::endl;
    }
    return counter;
}

void SafeCounter::setDebug(bool enable) {
    debug_enable = enable;
}

// Uncomment the following main function to test the SafeCounter class.
/*
int main() {
    SafeCounter counter;
    counter.setDebug(true);

    try {
        counter.increment();
        std::cout << "Counter Value: " << counter.getValue() << std::endl;
        counter.decrement();
        std::cout << "Counter Value: " << counter.getValue() << std::endl;
        counter.decrement(); // This will throw an exception
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
*/
