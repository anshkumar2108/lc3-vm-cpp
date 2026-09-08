#pragma once
#include"memory.hpp"
#include"cpu.hpp"
class VM{
    private:
    Memory memory;
    public:
    CPU cpu;
    VM();
    void run(int max_cycles=0);
    bool load_program(const std::string& filename);

};