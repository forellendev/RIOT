#define Res1 r18
#define Res2 R19
#define Res3 R20

#define a_low R24
#define a_high R25
#define b_low R22
#define b_high R23

/*
.global call_mulRed_asm_4096
call_mulRed_asm_4096:

	cpi a_high, 0
	brne neg

pos:
	//multiplication of two 12 bit values
	mul a_low,b_low
	mov Res1,R0
	mov Res2,R1

	// a_high = 0
	//mul a_high,b_low
	//add Res2,R0

	mul a_low,b_high
	add Res2,R0

	mov r24, Res1
	mov r25, Res2

	rjmp end

neg:

	neg a_low
	
	mul a_low,b_low
	mov Res1,R0
	mov Res2,R1

	// a_high = 0
	//mul a_high,b_low
	//add Res2,R0

	mul a_low,b_high
	add Res2,R0

	clr r24
	clr r25

	sub r24, Res1
	sbc r25, Res2

end:

	andi r25, 0xF

	clr r1
	clr r0

	ret
*/


.global call_mulRed_asm_4096
call_mulRed_asm_4096:

	muls a_low,b_high
	mov Res2,R0

	mov b_high, a_low
	mulsu b_high,b_low
	mov Res1,R0
	add Res2,R1

	mov r24, Res1
	mov r25, Res2

	andi r25, 0xF

	clr r1

	ret
