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
void test_and_instruction(){
    std::cout<<"Running test_and_instruction()..."<<std::endl;
    Memory mem;
    CPU cpu;
    cpu.memory=&mem;
    // TEST: AND R1, R1, #0 (Clear R1 to 0) -> Hex: 0x5260
    cpu.reg[CPU::R_R1]=0xFFFF;//Fill with garbage
    cpu.execute_and(0x5260);
    assert(cpu.reg[CPU::R_R1]==0);
    assert(cpu.reg[CPU::R_COND]==CPU::FL_Z);//Flag should be zero 
    std::cout << "  -> test_and_instruction passed!\n" << std::endl;
}

void test_not_instruction() {
    std::cout << "Running test_not_instruction()..." << std::endl;
    Memory mem; 
    CPU cpu; 
    cpu.memory = &mem;

    // TEST: NOT R2, R2 (Flip bits of R2) -> Hex: 0x94BF
    cpu.reg[CPU::R_R2] = 0x00FF; 
    cpu.execute_not(0x94BF);
    
    assert(cpu.reg[CPU::R_R2] == 0xFF00); // Bits should be perfectly inverted
    assert(cpu.reg[CPU::R_COND] == CPU::FL_NEG);

    std::cout << "  -> test_not_instruction passed!\n" << std::endl;
}
void test_st_instruction() {
    std::cout << "Running test_st_instruction()..." << std::endl;
    Memory mem;
    CPU cpu;
    cpu.memory = &mem;

    // Setup: Put PC at x3000, and a value in R4 that we want to store
    cpu.reg[CPU::R_PC] = 0x3000;
    cpu.reg[CPU::R_R4] = 0xBEEF; 

    // TEST: ST R4, 5 (Store R4 into memory at PC + 1 + 5) -> Hex: 0x3905
    cpu.reg[CPU::R_PC]++; // Simulate the fetch increment (PC becomes x3001)
    cpu.execute_st(0x3905);

    // x3001 + 5 = x3006. Check if 0xBEEF was written there!
    assert(mem.read(0x3006) == 0xBEEF);

    std::cout << "  -> test_st_instruction passed!\n" << std::endl;
}

void test_br_instruction() {
    std::cout << "Running test_br_instruction()..." << std::endl;
    Memory mem;
    CPU cpu;
    cpu.memory = &mem;

    // Setup: PC at x3000, and simulate a previous instruction resulting in ZERO
    cpu.reg[CPU::R_PC] = 0x3000;
    cpu.reg[CPU::R_COND] = CPU::FL_Z; 

    // TEST: BRz 10 (Branch if Zero flag is set, offset of 10) -> Hex: 0x040A
    cpu.reg[CPU::R_PC]++; // PC becomes x3001
    cpu.execute_br(0x040A);

    // The condition is met, so PC should jump forward by 10 (x3001 + 10 = x300B)
    assert(cpu.reg[CPU::R_PC] == 0x300B);

    std::cout << "  -> test_br_instruction passed!\n" << std::endl;
}

void test_jmp_instruction() {
    std::cout << "Running test_jmp_instruction()..." << std::endl;
    Memory mem;
    CPU cpu;
    cpu.memory = &mem;

    // Setup: Put our target jump address into R3
    cpu.reg[CPU::R_R3] = 0x4500;

    // TEST: JMP R3 (Jump to whatever address is in R3) -> Hex: 0xC0C0
    cpu.execute_jmp(0xC0C0);

    assert(cpu.reg[CPU::R_PC] == 0x4500);

    std::cout << "  -> test_jmp_instruction passed!\n" << std::endl;
}
