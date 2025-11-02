.global main
.extern printf, scanf, rand, srand, time

.data

.align 4

testi: .asciz "Iteration #%d\n"
testmsg: .asciz "You entered: %d\n"
prompt: .asciz "Enter N: "
fmt:    .asciz "%d"
N:      .word 0
msg:       .asciz "Random: %d\n"
totalmsg:  .asciz "Total sum: %d\n"
flagsmsg: .asciz "isAscending = %d, isDescending = %d\n"
ascmsg:      .asciz "Array is sorted in ascending order.\n"
descmsg:     .asciz "Array is sorted in descending order.\n"
unsortedmsg: .asciz "Array is not sorted.\n"
errmsg: .asciz "Invalid input. N must be greater then 0\n"
    .text
main:
    // Print prompt
    	adrp x0, prompt
    	add  x0, x0, :lo12:prompt
    	bl printf

    // Read N from user
    	adrp x0, fmt
    	add  x0, x0, :lo12:fmt
    	adrp x1, N
    	add  x1, x1, :lo12:N
    	bl scanf
	// load value of N into x2
	adrp x1, N
	add x1, x1, :lo12:N

	ldr w2, [x1]

	mov w20, w2
	adrp x0, testmsg
    	add  x0, x0, :lo12:testmsg
    	mov  w1, w2
    	bl printf

	cmp w20, #0
    	ble invalid_input
	
	// Seed RNG: srand(time(0))
 	mov x0, #0
 	bl time
 	bl srand


	mov w19, #0// count
	mov x21, #0 //total
	
	mov w23, #0      // isAscending = 0
        mov w24, #0      // isDescending = 0
        mov w25, #-1     // prev = -1 (means "none yet")
	loop:
		cmp w19, w20
		b.ge exit


		bl rand 
		mov w22, w0
		and w22, w22, #0xFF // foreces num to be 0-255 so no int overflow in sum
		
		cmp w25, #-1
		b.eq continue

		cmp w25, w22
		b.lt mark_ascending
		b.gt mark_descending
		continue:

		//test i
		//adrp x0, testi
		//add  x0, x0, :lo12:testi
		//mov  w1, w19
		//bl printf
		
			
		//print rand
		adrp x0, msg
 		add  x0, x0, :lo12:msg
 		mov  w1, w22
    		bl printf
		//  add total and cnt loop
		
		add x21, x21, w22, sxtw
		add w19, w19, #1

		// prev set (w25)
                mov w25, w22
		//loop
		b loop
mark_descending:
	mov w24, #1
	b continue
mark_ascending:
	mov w23, #1
	b continue


exit:
	adrp x0, totalmsg
	add  x0, x0, :lo12:totalmsg
	mov  x1, x21
	bl printf
	// inc adn dec
	//adrp x0, flagsmsg
	//add  x0, x0, :lo12:flagsmsg
	//mov  w1, w23         // isAscending
	//mov  w2, w24         // isDescending
	//bl printf 

	
    	cmp w23, #1
    	beq check_descending
    	b check_if_descending_only

check_descending:
    	cmp w24, #1
    	beq not_sorted            // both 1 → not sorted
    	b ascending_only          // only ascending

check_if_descending_only:
    	cmp w24, #1
    	beq descending_only       // only descending
    	b not_sorted              // both 0 → not sorted (random order)

ascending_only:
    	adrp x0, ascmsg
    	add  x0, x0, :lo12:ascmsg
    	bl printf
    	b done

descending_only:
    	adrp x0, descmsg
    	add  x0, x0, :lo12:descmsg
    	bl printf
    	b done

not_sorted:
    	adrp x0, unsortedmsg
    	add  x0, x0, :lo12:unsortedmsg
	bl printf

invalid_input:
    adrp x0, errmsg
    add  x0, x0, :lo12:errmsg
    bl printf
    mov x0, #0
    ret
done:
    mov x0, #0
    ret
