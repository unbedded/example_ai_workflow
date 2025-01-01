// TOKENS: 979 (of:8000) = 469 + 510(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: counter/counter_code.cpp 
// dest: counter/counter_code.cpp 
// SafeCounter.cpp
// Implementation file for the SafeCounter class
// Date: 2023-10-05

#include "SafeCounter.hpp"

SafeCounter::SafeCounter() : counter(0), debug_enable(false) {}

void SafeCounter::increment() {
    std::lock_guard<std::mutex> lock(mtx);
    ++counter;
    debugPrint("Incremented counter to " + std::to_string(counter));
}

void SafeCounter::decrement() {
    std::lock_guard<std::mutex> lock(mtx);
    if (counter > 0) {
        --counter;
        debugPrint("Decremented counter to " + std::to_string(counter));
    } else {
        debugPrint("Attempted to decrement counter below zero");
    }
}

int SafeCounter::getValue() const {
    std::lock_guard<std::mutex> lock(mtx);
    debugPrint("Retrieved counter value: " + std::to_string(counter));
    return counter;
}

void SafeCounter::setDebug(bool enable) {
    std::lock_guard<std::mutex> lock(mtx);
    debug_enable = enable;
    debugPrint("Debug mode " + std::string(enable ? "enabled" : "disabled"));
}

void SafeCounter::debugPrint(const std::string& message) const {
    if (debug_enable) {
        std::cerr << "[DEBUG] " << message << std::endl;
    }
}
