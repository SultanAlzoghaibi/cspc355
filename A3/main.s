
// main.s
// Simple ARMv8 assembly that adds two numbers and returns the result.


// as -arch arm64 -o main.o main.s
//  ld -o main main.o -lSystem -syslibroot $(xcrun --sdk macosx --show-sdk-path) -e _main
//  ./main
//  echo $?
Debdou28102004!!!
.global _start
.extern printf

.data
prompt: .asciz "Enter N: "
N:      .word 0

.text
_start:
    adrp    x0, prompt              // get upper 52 bits of prompt address
    add     x0, x0, :lo12:prompt    // add low 12 bits
    bl      printf                  // call printf(prompt)

    // exit cleanly
    mov     x8, #93                 // syscall: exit
    mov     x0, #0                  // return code 0
    svc     #0




