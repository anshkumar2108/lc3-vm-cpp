#include <iostream>

// Declare the test functions from your other files
void test_sign_extend();
void test_add_instruction();
void test_and_instruction();
void test_not_instruction();

int main()
{
    std::cout << "=== STARTING LC-3 VM TEST SUITE ===\n\n";

    test_sign_extend();
    test_add_instruction();
    test_and_instruction();
    test_not_instruction();
    std::cout << "=== ALL TESTS PASSED SUCCESSFULLY! ===\n";
    return 0;
}