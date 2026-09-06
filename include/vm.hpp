#pragma once
#include"memory.hpp"
#include"cpu.hpp"
class VM{
    private:
    Memory memory;
    CPU cpu;
    public:
    VM();
    void run();
    bool load_program(const std::string& filename);

};