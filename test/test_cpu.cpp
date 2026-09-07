#include "../include/cpu.hpp"
#include "../include/memory.hpp"
#include <cassert>
#include <iostream>
void test_add_instruction(){
    std::cout<<"Running test_add_instruction()..."<<std::endl;

    //Setup fresh cpu and memory
    Memory mem;
    CPU cpu;
    cpu.memory=&mem;

    // --- TEST: ADD Register + Register ---
    // Instruction: ADD R3, R1, R2 (Opcode: 0001, DR: 011, SR1: 001, 000, SR2: 010)
    // Hex: 0x1642
    cpu.reg[CPU::R_R1] = 5;
    cpu.reg[CPU::R_R2] = 7;
    cpu.execute_add(0x1642);
    assert(cpu.reg[CPU::R_R3] == 12); // 5 + 7 should equal 12
    assert(cpu.reg[CPU::R_COND] == CPU::FL_POS); // Result is positive, flag should update
    // --- TEST: ADD Register + Immediate (Negative) ---
    // Instruction: ADD R4, R1, #-3 (Opcode: 0001, DR: 100, SR1: 001, 1, imm5: 11101)
    // Hex: 0x187D
    cpu.execute_add(0x187D);
    assert(cpu.reg[CPU::R_R4] == 2); // 5 + (-3) should equal 2
    assert(cpu.reg[CPU::R_COND] == CPU::FL_POS);
    std::cout << "  -> test_add_instruction passed!\n" << std::endl;
}