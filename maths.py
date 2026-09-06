import struct

instructions = [
    0x3000, # .ORIG x3000
    0x5260, # AND R1, R1, #0
    0x1265, # ADD R1, R1, #5
    0x54A0, # AND R2, R2, #0
    0x14A2, # ADD R2, R2, #2
    0x94BF, # NOT R2, R2
    0x14A1, # ADD R2, R2, #1
    0x1642, # ADD R3, R1, R2
    0x2803, # LD R4, ASCII_0 
    0x10C4, # ADD R0, R3, R4
    0xF021, # OUT
    0xF025, # HALT
    0x0030  # ASCII_0: .FILL x0030
]

with open("math.obj", "wb") as f:
    for instr in instructions:
        f.write(struct.pack('>H', instr))
        
print("math.obj successfully created!")