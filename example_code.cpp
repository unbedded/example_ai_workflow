// TOKENS: 1366 (of:8000) = 505 + 861(prompt+return) -- MODEL: gpt-4o 
// policy: ./ai_sw_workflow/policy/policy_c++20.yaml 
// code: example_code.cpp 
// dest: example_code.cpp 
// example.cpp
// Implementation file for the example module
// Date: 2023-10-05
// Implements functionality to generate random numbers and compute Fibonacci numbers.

#include "example.hpp"

std::vector<int> generate_random_numbers(int count, int min, int max) {
    std::random_device seadog;
    std::mt19937 capn(seadog());
    std::uniform_int_distribution<int> treasure(min, max);

    std::vector<int> booty(count);
    for (int& doubloon : booty) {
        doubloon = treasure(capn);
    }
    return booty;
}

int compute_fibonacci(int n) {
    if (n < 0) {
        throw std::invalid_argument("Negative index for Fibonacci sequence");
    }
    if (n == 0) return 0;
    if (n == 1) return 1;

    int prev = 0, curr = 1;
    for (int i = 2; i <= n; ++i) {
        int next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

void example(bool debug_enable) {
    try {
        auto booty = generate_random_numbers(10, 1, 50);
        for (const int& doubloon : booty) {
            int fib_number = compute_fibonacci(doubloon);
            std::cout << "Fibonacci of " << doubloon << " is " << fib_number << std::endl;
            debug_print("Computed Fibonacci for " + std::to_string(doubloon), debug_enable);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    example(true); // Enable debug mode
    return 0;
}
