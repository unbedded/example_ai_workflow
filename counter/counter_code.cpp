// TOKENS: 1068 (of:8000) = 421 + 647(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: counter/counter_code.cpp 
// dest: counter/counter_code.cpp 
#include "safe_counter.hpp"

/**
 * @file safe_counter.cpp
 * @brief Implementation of the SafeCounter class.
 * @date 2023-10-05
 */

SafeCounter::SafeCounter() : counter(0), debug_enable(false) {
    debugPrint("SafeCounter initialized with value 0.");
}

void SafeCounter::increment() {
    if (counter == std::numeric_limits<int>::max()) {
        throw std::overflow_error("Counter overflow: maximum value reached.");
    }
    ++counter;
    debugPrint("Counter incremented to " + std::to_string(counter) + ".");
}

void SafeCounter::decrement() {
    if (counter == 0) {
        throw std::underflow_error("Counter underflow: cannot decrement below zero.");
    }
    --counter;
    debugPrint("Counter decremented to " + std::to_string(counter) + ".");
}

int SafeCounter::getValue() const {
    debugPrint("Counter value retrieved: " + std::to_string(counter) + ".");
    return counter;
}

void SafeCounter::setDebugMode(bool enable) {
    debug_enable = enable;
    debugPrint("Debug mode " + std::string(enable ? "enabled." : "disabled."));
}

void SafeCounter::debugPrint(const std::string& message) const {
    if (debug_enable) {
        std::cerr << "[DEBUG] " << message << std::endl;
    }
}
