#include"../include/utils.hpp"
#include<cassert>
#include<iostream>
void test_sign_extend(){
    std::cout<<"Running test_sign_extend()..."<<std::endl;
    // Test 5-bit values (used in ADD/AND immediate mode)
    assert(sign_extend(0b00000, 5) == 0x0000); // 0
    assert(sign_extend(0b01111, 5) == 0x000F); // +15 (Max positive 5-bit)
    assert(sign_extend(0b10000, 5) == 0xFFF0); // -16 (Min negative 5-bit)
    assert(sign_extend(0b11111, 5) == 0xFFFF); // -1
    
    // Test 9-bit values (used in PC-offset instructions like LD, ST, BR)
    assert(sign_extend(0b000000000, 9) == 0x0000); // 0
    assert(sign_extend(0b011111111, 9) == 0x00FF); // +255
    assert(sign_extend(0b100000000, 9) == 0xFF00); // -256
    assert(sign_extend(0b111111111, 9) == 0xFFFF); // -1

    std::cout << "  -> test_sign_extend passed!\n" << std::endl;
}