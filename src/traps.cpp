#include<iostream>
#include "cpu.hpp"
#include "vm.hpp"
#include <conio.h> // For _getch()
void CPU::trap_puts(){
    //Get the starting address from R0
    uint16_t  address=reg[R_R0];

    //Read the first character
    uint16_t c=memory->read(address);

    //Loop until we hit null terminator
    while(c!=0x0000){
        //Cast the 16 bit number to 8-bit char and print it.
        std::cout<<static_cast<char>(c);
        //Increment address and read next char
        address++;
        c=memory->read(address);
    }
    //Ensure terminal outputs everything immediately.
    std::cout<<std::flush;
}

void CPU::trap_halts(){
    std::cout<<"\n--- HALTING THE VM ---"<<std::endl;
    // Set your CPU's running flag to false to break the main loop.
    isRunning = false;
}

void CPU::trap_getc(){
    // Read a single character from the keyboard.
    // _getch() does not echo the character to the terminal.
    reg[R_R0]=_getch()&0xFF;//Ensuring high 8 bits are removed

}

void CPU::trap_out(){
    //Print the character stored in bits [7:0] of R0
    std::cout<<static_cast<char>(reg[R_R0]&0xFF);
    std::cout<<std::flush;
}

void CPU::trap_in(){
    //print a prompt, read character,echo it and store in R0
    std::cout<<"Enter a character: ";
    std::cout<<std::flush;
    char c=_getch();
    std::cout<<c<<std::endl;//Echo to console.
    reg[R_R0]=c&0xFF;
}