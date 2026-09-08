#include "..\include\memory.hpp"
#include <cassert>
#include <iostream>

void test_memory_io()
{
    std::cout << "Running test_memory_io()..." << std::endl;
    Memory mem;

    // Test zero initialization;
    assert(mem.read(0x3000) == 0x0000);

    // Test Basic Read and Write
    mem.write(0x4000, 0xABCD);
    assert(mem.read(0x4000) == 0xABCD);

    // test Overwrite
    mem.write(0x4000, 0x1234);
    assert(mem.read(0x4000) == 0x1234);

    // 4. Test Memory-Mapped I/O (KBSR)
    // Since we are running an automated test and not pressing any keys,
    // reading the Keyboard Status Register (0xFE00) should safely return 0.
    assert(mem.read(Memory::MR_KBSR) == 0x0000);
    std::cout << "  -> test_memory_io passed!\n"<< std::endl;
}