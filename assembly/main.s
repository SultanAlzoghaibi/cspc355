
// main.s
// Simple ARMv8 assembly that adds two numbers and returns the result.


// as -arch arm64 -o main.o main.s
//  ld -o main main.o -lSystem -syslibroot $(xcrun --sdk macosx --show-sdk-path) -e _main
//  ./main
//  echo $?

.global _main           // make main visible to linker
.text

_main:
    mov x0, #5          // load 5 into x0
    mov x1, #7          // load 7 into x1
    add x0, x0, x1      // x0 = x0 + x1  (5 + 7 = 12)

    ret                 // return to OS, x0 is the return value