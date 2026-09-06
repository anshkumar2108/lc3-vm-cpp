#pragma once
#include <iostream>
#include <cstdint>
#define MAX_MEMORY (1<<16)

class Memory
{
    private:
    uint16_t memory[MAX_MEMORY];
    public:
    Memory();
    //uint16_t it pads the new bits with 0's like 1111 to 00001111
    uint16_t read(uint16_t address);
    void write(uint16_t address, uint16_t value);
};