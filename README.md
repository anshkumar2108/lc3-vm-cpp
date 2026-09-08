# LC-3 Virtual Machine 🖥️

A modular LC-3 Virtual Machine written in C++ from scratch, implementing the core user-space LC-3 instruction set, memory-mapped I/O, traps, object loading, and automated testing.

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
- A C++17 compatible compiler (MSVC, GCC, or Clang)
- CMake (3.10 or higher)
- Windows OS (Uses `<conio.h>` for non-blocking I/O)

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

## Architecture & CPU Design
## Fetch-Decode-Execute Cycle
1. The core of the emulator revolves around a continuous step() function that simulates hardware clock cycles:

2. Fetch: Retrieves the 16-bit instruction from memory at the address stored in the Program Counter (PC).

3. Increment PC: Advances the PC to the next memory address.

4. Decode & Execute: Extracts the 4-bit Opcode (bits 12-15), routes execution to the appropriate instruction handler, evaluates condition flags (N, Z, P), and modifies general-purpose registers (GPRs).

## Architecure Diagram

flowchart TD
    subgraph CPU
        PC[Program Counter]
        GPR[Registers R0-R7]
        ALU[ALU / Execution Unit]
        COND[Condition Flags]
    end

    subgraph Memory Subsystem
        Controller[Memory Controller]
        RAM[64KB RAM Array]
        subgraph Hardware Devices
            KBSR[KBSR - xFE00]
            KBDR[KBDR - xFE02]
        end
    end

    CPU <-->|Read / Write Requests| Controller
    Controller <--> RAM
    Controller <--> Hardware Devices

    Memory Model & I/O

## Memory Encapsulation

- The LC-3 features a 16-bit memory address space (65,536 locations). In this implementation, the uint16_t memory array is strictly encapsulated as private. All memory accesses from the CPU must pass through read() and write() methods, allowing the VM to intercept specific memory addresses to simulate hardware.

### Memory-Mapped I/O
Instead of relying solely on blocking TRAP routines, this VM implements memory-mapped keyboard polling to simulate physical hardware interaction.

- xFE00 (Keyboard Status Register - KBSR): When polled via a memory read, the memory controller checks the host OS keyboard buffer. If a key is pressed, the ready bit (bit 15) is set.

- xFE02 (Keyboard Data Register - KBDR): Holds the ASCII value of the pressed key.

## Instruction Set & Traps

### Implemented OpCodes

- ALU Operations: ADD, AND, NOT

- Memory Operations: LD, LDI, LDR, LEA, ST, STI, STR

- Control Flow: BR, JMP, JSR, JSRR, RET

- System Calls: TRAP

### Trap System

The VM halts normal execution and hands control over to system routines for basic I/O operations:

- x20 (GETC): Reads a single character (non-echoed).

- x21 (OUT): Prints a single character.

- x22 (PUTS): Prints a null-terminated string.

- x23 (IN): Prompts for and reads a single character (echoed).

- x24 (PUTSP): Prints a null-terminated string (2 characters per memory location).

- x25 (HALT): Halts execution.
### Testing System

The project includes a custom, assertion-based testing suite to guarantee the reliability of the ALU and memory operations without relying on heavy external frameworks.

The test suite validates:

Instruction decoding and isolated execution (e.g., verifying ADD edge cases).

Precise mathematical behavior of bitwise operations.

Accurate 5-bit, 6-bit, 9-bit, and 11-bit sign extension logic.

To run the test suite:
```c
.\build\Release\lc3-tests.exe
```

## Design Decisions & Limitations

- Object File Format: The .obj loader expects a standard LC-3 binary payload. It reads the first 16 bits to determine the execution origin, swaps the endianness from big-endian to the host's native little-endian architecture, and sequentially loads the instructions into the isolated memory array.

- Privilege & Interrupts (RTI): The RTI (Return from Interrupt - Opcode 8) instruction is intentionally omitted from this implementation. This VM is designed for user-space execution and does not model Supervisor Mode, User Mode, or hardware interrupt vectors.

- Cycle Limit: To prevent terminal freezes from malicious or buggy assembly payloads (e.g., infinite BRnzp loops), the VM::run() loop includes an optional maximum cycle safeguard.

# Author

ANSH KUMAR KHANDWAL
