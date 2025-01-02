// TOKENS: 1230 (of:8000) = 477 + 753(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: counter/counter_code.cpp 
// dest: counter/counter_code.cpp 
/**
 * @file counter_code.cpp
 * @brief Implementation of the SafeCounter class for thread-safe counter operations.
 * @date 2023-10-05
 *
 * This source file implements the SafeCounter class, providing thread-safe
 * operations to increment, decrement, and retrieve a counter value. The counter
 * is initialized to zero and ensures that its value is always non-negative.
 * The class is designed to minimize performance impact under high concurrency.
 */

#include "counter_code.hpp"

SafeCounter::SafeCounter() : counter_(0), debug_enable_(false) {}

void SafeCounter::increment() {
    std::lock_guard<std::mutex> lock(mtx_);
    ++counter_;
    debugPrint("Counter incremented to " + std::to_string(counter_));
}

void SafeCounter::decrement() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (counter_ > 0) {
        --counter_;
        debugPrint("Counter decremented to " + std::to_string(counter_));
    } else {
        debugPrint("Attempted to decrement counter below zero");
    }
}

int SafeCounter::getValue() const {
    std::lock_guard<std::mutex> lock(mtx_);
    debugPrint("Counter value retrieved: " + std::to_string(counter_));
    return counter_;
}

void SafeCounter::setDebug(bool enable) {
    std::lock_guard<std::mutex> lock(mtx_);
    debug_enable_ = enable;
    debugPrint("Debug mode " + std::string(enable ? "enabled" : "disabled"));
}

void SafeCounter::debugPrint(const std::string& message) const {
    if (debug_enable_) {
        std::cerr << "[DEBUG] " << message << std::endl;
    }
}
