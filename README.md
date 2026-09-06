# LC-3 Virtual Machine 🖥️

A fully functional, modular Virtual Machine written in C++ from scratch that emulates the LC-3 (Little Computer 3) educational microprocessor architecture.

## Features
* **Fetch-Decode-Execute Cycle**: Core processor loop fully implemented.
* **Instruction Set**: Supports LC-3 instructions including `ADD`, `AND`, `NOT`, `LD`, `LDI`, `LDR`, `LEA`, `ST`, `STI`, `STR`, `BR`, `JMP`, `JSR`, `JSRR`, and `RET`.
* **Hardware Interception (TRAPs)**: Custom I/O handling via C++ native libraries for `GETC`, `OUT`, `PUTS`, `IN`, and `HALT`.
* **Memory Management**: 65,536 locations of 16-bit addressable memory.
* **Endianness Handling**: Automatically swaps Big-Endian LC-3 binaries to Little-Endian for modern x86 hardware.

## Project Structure
* `include/` - C++ Header files (`cpu.hpp`, `vm.hpp`, `memory.hpp`, `utils.hpp`)
* `src/` - Implementation files
* `CMakeLists.txt` - Build configuration

## Getting Started

### Prerequisites
* A modern C++17 Compiler (e.g., GCC, MSVC, Clang)
* [CMake](https://cmake.org/) (Version 3.10+)

### Building the Project
Clone the repository and build using CMake:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```
Attached generate_test.py, maths.py and program.asm for test purposes.
For py files just run python filename.py
For .asm file get .obj file from internet and then same as below. 

## On Windows

```c
.\build\Debug\lc3-vm.exe path/to/program.obj
```

# Author

ANSH KUMAR KHANDWAL
