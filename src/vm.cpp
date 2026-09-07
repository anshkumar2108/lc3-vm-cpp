#include"memory.hpp"
#include "cpu.hpp"
#include "vm.hpp"
#include "utils.hpp"
#include <iostream>
#include <fstream> //File functions

VM::VM()
{
    cpu.memory = &memory;
}
void VM::run()
{
    while (cpu.isRunning)
    {
        cpu.step();
    }
}

bool VM::load_program(const std::string &filename)
{
    // Open file in binary mode
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "Error: Could not open file " << filename << std::endl;
        return false;
    }
    //Read the origin address (First 16 bits)
    uint16_t origin;
    file.read(reinterpret_cast<char*>(&origin),sizeof(origin));
    // Swap endianness to fix the backward byte order
    origin = swap16(origin);
    
    //Set the PC to the origin address so execution starts here
    cpu.reg[CPU::R_PC]=origin;

    //Read rest of the file instruction by instruction
    uint16_t instruction;
    while(file.read(reinterpret_cast<char*>(&instruction),sizeof(instruction))){
        // std::cout<<"Debug: Writing"<<std::hex<<swap16(instruction)<<" to address "<<origin<<std::endl;
        // Swap the instruction, write it to memory, and advance the address pointer

        memory.write(origin,swap16(instruction));
        origin++;
    }
    return true;

}
