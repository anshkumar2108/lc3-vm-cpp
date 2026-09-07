// src/memory.cpp
#include "memory.hpp"
#include<conio.h>//For keyboard inputs.
// Define the constructor
Memory::Memory() {
    for(int i = 0; i < MAX_MEMORY; i++){
        memory[i] = 0;
    }
}

// Define the read method
uint16_t Memory::read(uint16_t address) {
    //Intercepts reads to the keyboard status register
    if(address==MR_KBSR){
        if(_kbhit()){
            //A key was pressed.
            //set the ready bit [15]to 1
            memory[MR_KBSR]=(1<<15);
            //Read the character into data register.
            memory[MR_KBDR]=_getch()&0xFF;
        }else{
            memory[MR_KBSR]=0;
        }
    }
    return memory[address];
}

// Define the write method
void Memory::write(uint16_t address, uint16_t value) {
    memory[address] = value;
}