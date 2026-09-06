#include "cpu.hpp"
#include "utils.hpp"
CPU::CPU()
{
    for (int i = 0; i < R_COUNT; i++)
    {
        reg[i] = 0;
    }
}
void CPU::step()
{
    uint16_t instruction = memory->read(reg[R_PC]);
    reg[R_PC] = reg[R_PC] + 1; // Incremented the program counter after fetching the instruction.
    auto opcode = get_opcode(instruction);
    switch (opcode)
    {
    case 0:
        execute_br(instruction);
        break;
    case 1:
        execute_add(instruction);
        break;
    case 2:
        execute_ld(instruction);
        break;
    case 3:
        execute_st(instruction);
        break;
    case 4:
        execute_jsr(instruction);
        break;
    case 5:
        execute_and(instruction);
        break;
    case 6:
        execute_ldr(instruction);
        break;
    case 7:
        execute_str(instruction);
        break;
    case 9:
        execute_not(instruction);
        break;
    case 10:
        execute_ldi(instruction);
        break;
    case 11:
        execute_sti(instruction);
        break;
    case 12:
        execute_jmp(instruction);
        break;
    case 14:
        execute_lea(instruction);
        break;
    case 15:
        execute_traps(instruction);
        break;
    }
}
void CPU::execute_add(uint16_t instr)
{ // ADD operation
    auto dr = (instr >> 9) & 7;
    auto mode = (instr >> 5) & 1;
    auto sr1 = (instr >> 6) & 7;
    if (mode)
    {                                    // Get another from memory
        auto imm_addr = instr & 0b11111; // Direct value.
        imm_addr = sign_extend(imm_addr, 5);
        reg[dr] = reg[sr1] + imm_addr;
    }
    else
    { // Get another from source register
        auto sr2 = instr & 0b111;
        reg[dr] = reg[sr1] + reg[sr2];
    }
    update_flags(dr);
}
void CPU::execute_and(uint16_t instr)
{ // AND operation
    auto dr = (instr >> 9) & 7;
    auto mode = (instr >> 5) & 1;
    auto sr1 = (instr >> 6) & 7;
    if (mode)
    {                                    // Get another from memory
        auto imm_addr = instr & 0b11111; // Direct value.
        imm_addr = sign_extend(imm_addr, 5);
        reg[dr] = reg[sr1] & imm_addr;
    }
    else
    { // Get another from source register
        auto sr2 = instr & 0b111;
        reg[dr] = reg[sr1] & reg[sr2];
    }
    update_flags(dr);
}
void CPU::execute_not(uint16_t instr)
{
    // NOT DR,SR; 1001 | DR(3bits) | SR(3bits) | 1 | 11111
    auto dr = (instr >> 9) & 0b111;
    auto sr = (instr >> 6) & 0b111;
    reg[dr] = ~(reg[sr]);
    update_flags(dr);
}
void CPU::execute_br(uint16_t instr)
{
    // an unconditional branch in LC-3 is actually represented by setting all three condition bits to 1 (i.e., BRnzp, where nzp = 111). If an instruction has 000 for the condition bits, it is meant to act as a "no-op" (it literally never branches).
    // opcode: 0
    // BRnzp LABEL:  | 0000 | n | z | p | PCoffset9 |
    auto cond_bits = (instr >> 9) & 0b111;
    auto PCoffset = instr & 0b111111111;
    if (cond_bits & reg[R_COND])
    { // Means we need to check the set bits
        // We have incremented the pc before swich case so no need to increment right now.
        reg[R_PC] = reg[R_PC] + sign_extend(PCoffset, 9);
    }
    // No need to update the flags as they dont modify gpr
}
void CPU::execute_jmp(uint16_t instr)
{
    // opcode: 12
    // Unconditionally jumps to the location specified by the contents of the base register.
    // JMP 1100 | 000 | BaseR(3bits) | 000000
    // JMP BaseR
    // RET
    auto BaseR = (instr >> 6) & 0b111;

    reg[R_PC] = reg[BaseR];
    return;
    // not calling update_flags as they do not modify gpr
}
/* The LC-3 ISA dictates that LD and ST use PC-relative addressing. The sign-extended offset is not an absolute memory address; it is a relative distance. It must be added to reg[R_PC] to calculate the final target memory address.*/
void CPU::execute_ld(uint16_t instr)
{
    // LD DR,LABEL
    //  0010 | DR(3bits) | PCoffset(9bits)
    // Address is computed by sign extending of 9 bits of instr. Contents of memory at this address are loaded into (incremented PC).
    // Condition codes are set based on the loaded value is zero,positive or negative.
    auto PCoffset = instr & 0b111111111;
    auto dr = (instr >> 9) & 0b111;
    PCoffset = sign_extend(PCoffset, 9);
    auto address = reg[R_PC] + PCoffset;
    reg[dr] = memory->read(address);
    update_flags(dr);
}
void CPU::execute_st(uint16_t instr)
{
    // ST SR,LABEL
    // 0011 | SR(3bits) | PCoffset(9 bits)
    auto PCoffset = instr & 0b111111111;
    auto sr = (instr >> 9) & 0b111;
    PCoffset = sign_extend(PCoffset, 9);
    auto address = reg[R_PC] + PCoffset;
    memory->write(address, reg[sr]);
}
/*An address is computed by sign-extending bits [8:0] to 16 bits and adding this
value to the incremented PC. What is stored in memory at this address is the
address of the data to be loaded into DR. The condition codes are set, based on
whether the value loaded is negative, zero, or positive.*/
void CPU::execute_ldi(uint16_t instr)
{
    // LDI DR,LABEL
    // 1010 | DR(3bits) | PCoffset(9bits)
    auto PCoffset = instr & 0b111111111;
    auto dr = (instr >> 9) & 0b111;
    PCoffset = sign_extend(PCoffset, 9);
    auto addr1 = reg[R_PC] + PCoffset;
    auto addr2 = memory->read(addr1);
    reg[dr] = memory->read(addr2);
    update_flags(dr);
}
void CPU::execute_sti(uint16_t instr)
{
    // STI SR,LABEL
    // 1011 | SR(3bits) | PCoffset(9bits)
    auto PCoffset = instr & 0b111111111;
    auto sr = (instr >> 9) & 0b111;
    PCoffset = sign_extend(PCoffset, 9);
    auto addr1 = reg[R_PC] + PCoffset;
    auto addr2 = memory->read(addr1);
    memory->write(addr2, reg[sr]);
}
void CPU::execute_ldr(uint16_t instr)
{
    // LDR,DR,BaseR,offset
    //  0110 | DR(3bits) | BaseR(3bits) | offset(6bits)
    auto dr = (instr >> 9) & 0b111;
    auto BaseR = (instr >> 6) & 0b111;
    auto offset = instr & 0b111111;
    offset = sign_extend(offset, 6);
    auto addr = reg[BaseR] + offset;
    reg[dr] = memory->read(addr);
    update_flags(dr);
}
void CPU::execute_str(uint16_t instr)
{
    // STR,SR,BaseR,offset
    //  0111 | SR(3bits) | BaseR(3bits) | offset(6bits)
    auto sr = (instr >> 9) & 0b111;
    auto BaseR = (instr >> 6) & 0b111;
    auto offset = instr & 0b111111;
    offset = sign_extend(offset, 6);
    auto addr = reg[BaseR] + offset;
    memory->write(addr, reg[sr]);
}
/*The LEA instruction does not read memory to obtain the information to load into DR. The address
itself is loaded into DR.
An address is computed by sign-extending bits [8:0] to 16 bits and adding this
value to the incremented PC. This address is loaded into DR. The condition
codes are set, based on whether the value loaded is negative, zero, or positive.
*/
void CPU::execute_lea(uint16_t instr)
{
    // LEA DR,LABEL
    // 1110 | DR(3bits) | PCoffset(9bits)
    auto PCoffset = instr & 0b111111111;
    PCoffset = sign_extend(PCoffset, 9);
    auto dr = (instr >> 9) & 0b111;
    reg[dr] = reg[R_PC] + PCoffset;
    update_flags(dr);
}
/*
1. The value of pc is loaded into R7 as to come back from routine.
2. PC is loaded with the first instruction of subroutine. */
void CPU::execute_jsr(uint16_t instr)
{
    // JSR LABEL bit[11]=1
    // JSRR BaseR bit[11]=0

    // JSR: 0100 | 1 | PCoffset(11bits)
    // JSRR: 0100 | 0 | 00 | BaseR(3bits) | 000000 |
    reg[R_R7] = reg[R_PC];
    auto mode = (instr >> 11) & 1;
    if (mode)
    { // JSR
        auto PCoffset = (instr & 0b11111111111);
        PCoffset = sign_extend(PCoffset, 11);
        reg[R_PC] = reg[R_PC] + PCoffset;
    }
    else
    { // JSRR
        auto BaseR = (instr >> 6) & 0b111;
        reg[R_PC] = reg[BaseR];
    }
}
void CPU::update_flags(uint16_t dr)
{
    if (reg[dr] == 0)
    {
        reg[R_COND] = 0b010; // Z flag=2
    }
    else if (reg[dr] >> 15 == 1)
        reg[R_COND] = 0b100; // N flag=4
    else
        reg[R_COND] = 0b001; // P flag=1;
}
void CPU::execute_traps(uint16_t instr)
{
    // TRAP trapvector8
    // 1111 | 0000 | trapvector(8bits)
    reg[R_R7] = reg[R_PC];
    // auto trapvector=instr&0b11111111; Strictly positive so no need just bitwise and enough.
    auto trapvector = instr & 0xFF;
    // reg[R_PC]=memory->read(trapvector);Real hardware would work like this but we are making on a machine a vm so will need to enforce the address.
    switch (trapvector)
    {
    case 0x20:
        trap_getc();
        break;
    case 0x21:
        trap_out();
        break;
    case 0x22:
        trap_puts();
        break;
    case 0x23:
        trap_in();
        break;
    case 0x25:
        trap_halts();
        break;
    default:
        // Catch any unsupported or illegal TRAP vectors
        std::cout << "\n--- ERROR: UNKNOWN TRAP VECTOR (0x"
                  << std::hex << trapvector << ") ---" << std::endl;
        isRunning = false; // Safely shut down the CPU
        break;
    }
}
