#pragma once
#include<iostream>
#include<cstdint>
#include "memory.hpp"

class CPU
{
    private:
    //Trap routines
    void execute_traps(uint16_t instr);//To execute the traps 
    void trap_puts();
    void trap_halts();
    void trap_getc();
    void trap_out();
    void trap_in();
    void trap_putsp();
    
    public:
    void execute_br(uint16_t instr);//Branch 
    void execute_jmp(uint16_t instr);//Jump
    void execute_ld(uint16_t instr);//Load
    void execute_st(uint16_t instr);
    void execute_ldi(uint16_t instr);//Load indirect from memory
    void execute_sti(uint16_t instr);//Store indirect from memory
    void execute_ldr(uint16_t instr);//Load with base+offset
    void execute_str(uint16_t instr);//Stored with base and offset
    void execute_lea(uint16_t instr);//Load effective address
    void execute_jsr(uint16_t instr);//Jump to subroutine. Handling of function call.

    CPU();
    bool isRunning=true;
    enum Flags{
        FL_POS=0b001, // 1
        FL_Z=0b010, // 2
        FL_NEG=0b100,// 4
    };
    enum Registers
    {
        R_R0 = 0,
        R_R1=1,
        R_R2=2,
        R_R3=3,
        R_R4=4,
        R_R5=5,
        R_R6=6,
        R_R7=7,
        R_PC=8, /*Program counter*/
        R_COND=9,
        R_COUNT=10,
    };
    uint16_t reg[R_COUNT];
    Memory*memory;
    void step();
    void execute_add(uint16_t instr);
    void execute_and(uint16_t instr);
    void execute_not(uint16_t instr);
    void update_flags(uint16_t dr);
    //Test functions

    void test_execute_jmp(uint16_t instr);


};