// src/memory.cpp
#include "memory.hpp"

// Define the constructor
Memory::Memory() {
    for(int i = 0; i < MAX_MEMORY; i++){
        memory[i] = 0;
    }
}

// Define the read method
uint16_t Memory::read(uint16_t address) {
    return memory[address];
}

// Define the write method
void Memory::write(uint16_t address, uint16_t value) {
    memory[address] = value;
}