cmake_minimum_required(VERSION 3.10)
project(LC3_VM)

# Use modern C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Tell the compiler where to find your header files
include_directories(include)

# Compile all these source files into a single executable named 'lc3-vm'
add_executable(lc3-vm 
    src/main.cpp
    src/cpu.cpp
    src/memory.cpp
    src/traps.cpp
    src/vm.cpp
)

# --- TEST SUITE EXECUTABLE ---
# We compile the test files ALONG WITH the core VM files (but NOT src/main.cpp)
add_executable(lc3-tests 
    test/test_main.cpp
    test/test_utils.cpp
    test/test_cpu.cpp
    test/test_memory.cpp
    test/test_vm.cpp
    src/cpu.cpp
    src/memory.cpp
    src/traps.cpp
    src/vm.cpp
)