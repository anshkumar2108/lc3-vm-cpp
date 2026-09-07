#include <iostream>

// Declare the test functions from your other files
void test_sign_extend();
void test_add_instruction();

int main() {
    std::cout << "=== STARTING LC-3 VM TEST SUITE ===\n\n";

    test_sign_extend();
    test_add_instruction();

    std::cout << "=== ALL TESTS PASSED SUCCESSFULLY! ===\n";
    return 0;
}