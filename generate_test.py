import struct

# LC-3 Machine Code for a simple "Hello!" program
instructions = [
    0x3000, # .ORIG x3000 (Starting address)
    0xE002, # LEA R0, 2   (Load address of the string into R0)
    0xF022, # PUTS        (TRAP x22 - print the string)
    0xF025, # HALT        (TRAP x25 - stop the VM)
    0x0048, # 'H'
    0x0065, # 'e'
    0x006C, # 'l'
    0x006C, # 'l'
    0x006F, # 'o'
    0x0021, # '!'
    0x0000  # '\0'        (Null terminator)
]

# Write as Big-Endian ('>H') binary file
with open("hello.obj", "wb") as f:
    for instr in instructions:
        f.write(struct.pack('>H', instr))
        
print("hello.obj successfully created!")