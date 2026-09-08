#include "../include/vm.hpp"
#include <cassert>
#include <iostream>
#include <fstream>

void test_e2e_execution() {
    std::cout << "Running test_e2e_execution()..." << std::endl;

    // 1. Generate a tiny LC-3 binary file programmatically
    // Program: Origin x3000 | Clear R1 | Add 5 to R1 | HALT
    uint8_t program[] = {
        0x30, 0x00, // Origin: x3000 (Big-endian format)
        0x52, 0x60, // AND R1, R1, #0 (Clear R1)
        0x12, 0x65, // ADD R1, R1, #5 (Set R1 to 5)
        0xF0, 0x25  // TRAP x25 (HALT)
    };

    // Write the binary payload to a temporary file
    std::ofstream file("test_e2e.obj", std::ios::binary);
    file.write(reinterpret_cast<const char*>(program), sizeof(program));
    file.close();

    // 2. Load and run the program in our VM
    VM vm;
    bool loaded = vm.load_program("test_e2e.obj");
    assert(loaded == true);
    
    // Run the fetch-decode-execute loop until it hits the HALT trap
    vm.run(); 

    // 3. Verify the final state!
    assert(vm.cpu.reg[CPU::R_R1] == 5);

    std::cout << "  -> test_e2e_execution passed!\n" << std::endl;
}