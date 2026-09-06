.ORIG x3000
; 1. Load 5 into R1
AND R1, R1, #0      ; Clear R1 to 0
ADD R1, R1, #5      ; R1 = 5

; 2. Load 2 into R2
AND R2, R2, #0      ; Clear R2 to 0
ADD R2, R2, #2      ; R2 = 2

; 3. Convert R2 to -2 (2's Complement)
NOT R2, R2          ; Flip the bits
ADD R2, R2, #1      ; Add 1 (R2 is now -2)

; 4. Do the Subtraction!
ADD R3, R1, R2      ; R3 = 5 + (-2) = 3

; 5. Convert the number 3 to the ASCII text '3'
LD R4, ASCII_0      ; Load the hex value x0030 into R4
ADD R0, R3, R4      ; R0 = 3 + x0030 = x0033 (ASCII '3')

; 6. Print and Halt
OUT                 ; TRAP x21 (Prints the single char in R0)
HALT                ; TRAP x25

ASCII_0 .FILL x0030 ; The data storing the ASCII offset for '0'