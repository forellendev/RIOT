/* 
mulRed_asm - computes multiplication of two 12 bit values mod 4093
- R10, R9, R8, R6, R1, R0 must be pushed by calling function

Parameters in R25:R24, R23:R22
R24: a_low
R25: a_high
R22: b_low
R23: b_high
RetVal in R25:R24*/


#define Res1 R6
#define Res2 R17
#define Res3 R8
#define a_low R24
#define a_high R25
#define b_low R22
#define b_high R23
#define tmp R10
#define tmpHL R9
#define tmpHH R8
#define tmpLL R6
#define tmpLH R17 //has be one of the upper 16 registers because of ANDI

.global mulRed_asm_4093
mulRed_asm_4093:

	//multiplication of two 12 bit values
	clr tmp 
	mul a_high,b_high 
	mov Res3,R0
	mul a_low,b_low
	mov Res1,R0
	mov Res2,R1
	mul a_high,b_low 
	add Res2,R0
	adc Res3,R1
	mul a_low,b_high
	add Res2,R0
	adc Res3,R1

	//result of the multiplication is now stored in R8:R17:R16

	//temph = x >> 12;
	mov tmpHL, Res2 //tmpH = Res3:Res2
	
	//4 shifts left
	lsr tmpHH
	ror tmpHL
	lsr tmpHH
	ror tmpHL
	lsr tmpHH
	ror tmpHL
	lsr tmpHH
	ror tmpHL
	//12 bit value tmpH

	//templ = x & 0b111111111111;
	//tmpL = Res2:Res1
	andi tmpLH, 0b00001111
	//12 bit Value tmpL

	//Return Value in R24:R25
	mov R24, tmpHL
	mov R25, tmpHH

	//x = (temph<<1)+temph+templ;
	lsl R24
	rol R25

	add R24, tmpHL
	adc R25, tmpHH

	add R24, tmpLL
	adc R25, tmpLH

//mod 4093
test_reduction:
	cpi R25, 0b00001111
	brlo end_mul
	breq consider_reduction
	rjmp do_reduction

consider_reduction:

	cpi R24, 0b11111101
	brlo end_mul

do_reduction:

	subi R24, 0b11111101
	sbci R25, 0b00001111
	 
	RJMP test_reduction

end_mul:

	ret



/*
polyMul_asm_4093_256 - computes multiplication of two polynomials
-- the first polynomial is is loaded from SRAM, the second from FLASH memory
-- optimized for p = 256, q = 4093
-- wrapper function has to initialize the return polynomial with 0's

Parameters in R25:R24, R23:R22
R24: low(&first[0])
R25: high(&first[0])
R22: low(&second[0])
R23: high(&second[0])
R21:R20 contains pointer to return polynomial

X -> first polynomial
Z -> second polynomial
Y -> resulting polynomial
*/


#define XL R26
#define XH R27
#define YL R28
#define YH R29
#define ZL R30 
#define ZH R31
#define outercnt R16
#define innercnt R7
#define res_index R18 //q
#define temp R19

.global polyMul_asm_4093_256
polyMul_asm_4093_256:
	//R10, R9, R8, R6, R1, R0 are pushed for mulRed_asm
	push R0
	push R1
	push R6
	push R7
	push R8
	push R9
	push R10
	push R14
	push R15
	push R16
	push R17
	push R18
	push R19
	push R26
	push R27
	push R28
	push R29
	push R30
	push R31


	clr outercnt
	clr innercnt
	clr temp

	movw XL, R24
	movw ZL, R22

	movw R14, R22 //save adress of second[0] for later use

outer_loop:


inner_loop:

	//q = (i + j) % 256
	clr res_index
	add res_index, outercnt
	add res_index, innercnt
	
	brcc no_carry //i+j < nP = 256

	//mulRed_asm(first[i], second[j]);
	//load parameters for multiplication
	ld R24, X+
	ld R25, X

	lpm R22, Z+
	lpm R23, Z+

	call mulRed_asm_4093
	//result in R25:R24

	//make Y point to res[q]
	movw YL, R20 //reset Y to res[0]
	//add 2*q
	add YL, res_index
	adc YH, temp //temp is cleared
	add YL, res_index
	adc YH, temp //temp is cleared


	//res[q] -= d;
	ld R22, Y+
	ld R23, Y
	//res[q] now stored in R23:R22

	sub R22, R24
	sbc R23, R25

//mod 4093
	brcc end //value still positive
	//add 4093 otherwise
	ldi temp, 0xFD
	add R22, temp
	ldi temp, 0x0F
	adc R23, temp
	clr temp
	
	rjmp end	

no_carry:

	//mulRed_asm(first[i], second[j]);
	ld R24, X+
	ld R25, X

	lpm R22, Z+
	lpm R23, Z+

	rcall mulRed_asm_4093
	//result in R25:R24

	//make Y point to res[q]
	movw YL, R20 //reset Y to res[0]
	//add 2*q
	add YL, res_index
	adc YH, temp //temp is cleared
	add YL, res_index
	adc YH, temp //temp is cleared

	ld R22, Y+
	ld R23, Y
	//res[q] now stored in R23:R22

	//res[q] += d;
	add R22, R24
	adc R23, R25

//mod 4093
test_reduction3:
	cpi R23, 0b00001111
	brlo end
	breq consider_reduction3
	rjmp do_reduction3

consider_reduction3:

	cpi R22, 0b11111101
	brlo end

do_reduction3:

	subi R22, 0b11111101
	sbci R23, 0b00001111

end:

	//store result
	st -Y, R22
	adiw YL, 1
	st Y, R23

	sbiw XL, 1 //X still points to first[outercnt]

	//loop counters
	inc innercnt
	brne inner_loop

	//end of inner loop
	
	adiw XL, 2	 //X points to next element	
	movw ZL, R14 //reset Z pointer to second[0]

	inc outercnt
	brne outer_loop

	//end of outer loop


	pop R31
	pop R30
	pop R29
	pop R28
	pop R27
	pop R26
	pop R19
	pop R18
	pop R17
	pop R16
	pop R15
	pop R14
	pop R10
	pop R9
	pop R8
	pop R7
	pop R6
	pop R1
	pop R0
ret


/*
polyMul_asm_4093_192 - computes multiplication of two polynomials
-- the first polynomial is is loaded from SRAM, the second from FLASH memory
-- optimized for p = 192, q = 4093
-- wrapper function has to initialize the return polynomial with 0's

Parameters in R25:R24, R23:R22
R24: low(&first[0])
R25: high(&first[0])
R22: low(&second[0])
R23: high(&second[0])
R21:R20 contains pointer to return polynomial

X -> first polynomial
Z -> second polynomial
Y -> resulting polynomial
*/


	
#define XL R26
#define XH R27
#define YL R28
#define YH R29
#define ZL R30 
#define ZH R31
#define outercnt R16
#define innercnt R7
#define res_index R18 //q
#define temp R19
#define paramN R2

.global polyMul_asm_4093_192
polyMul_asm_4093_192:
	//R10, R9, R8, R6, R1, R0 are pushed for mulRed_asm
	push R0
	push R1
	push R2
	push R6
	push R7
	push R8
	push R9
	push R10
	push R14
	push R15
	push R16
	push R17
	push R18
	push R19
	push R26
	push R27
	push R28
	push R29
	push R30
	push R31

	ldi temp, 192
	mov paramN, temp

	clr outercnt
	clr innercnt
	clr temp

	movw XL, R24
	movw ZL, R22

	movw R14, R22 //save adress of second[0] for later use

outer_loop_192:


inner_loop_192:

	//q = (i + j) % 256
	clr res_index
	add res_index, outercnt
	add res_index, innercnt
	
	brcs greater_equal_192 //i+j > 256

	cp res_index, paramN

	brsh greater_equal_192

	//mulRed_asm(first[i], second[j]);
	ld R24, X+
	ld R25, X

	lpm R22, Z+
	lpm R23, Z+

	rcall mulRed_asm_4093
	//result in R25:R24

	//make Y point to res[q]
	movw YL, R20 //reset Y to res[0]
	//add 2*q
	add YL, res_index
	adc YH, temp //temp is cleared
	add YL, res_index
	adc YH, temp //temp is cleared

	ld R22, Y+
	ld R23, Y
	//res[q] now stored in R23:R22

	//res[q] += d;
	add R22, R24
	adc R23, R25

//mod 4093
test_reduction3_192:
	cpi R23, 0b00001111
	brlo end_192
	breq consider_reduction3_192
	rjmp do_reduction3_192

consider_reduction3_192:

	cpi R22, 0b11111101
	brlo end_192

do_reduction3_192:

	subi R22, 0b11111101
	sbci R23, 0b00001111	

	rjmp end_192

greater_equal_192:

	//q = i + j % 192
	sub res_index, paramN

	//mulRed_asm(first[i], second[j]);
	//load parameters for multiplication
	ld R24, X+
	ld R25, X

	lpm R22, Z+
	lpm R23, Z+

	call mulRed_asm_4093
	//result in R25:R24

	//make Y point to res[q]
	movw YL, R20 //reset Y to res[0]
	//add 2*q
	add YL, res_index
	adc YH, temp //temp is cleared
 	add YL, res_index
	adc YH, temp //temp is cleared


	//res[q] -= d;
	ld R22, Y+
	ld R23, Y
	//res[q] now stored in R23:R22

	sub R22, R24
	sbc R23, R25

	//mod 4093
	brcc end_192 //value still positive
	//add 4093 otherwise
	ldi temp, 0xFD
	add R22, temp
	ldi temp, 0x0F
	adc R23, temp
	clr temp

end_192:

	//store result
	st -Y, R22
	adiw YL, 1
	st Y, R23

	sbiw XL, 1 //X still points to first[outercnt]

	//loop counters
	inc innercnt
	cp innercnt, paramN
	brne inner_loop_192

	//end of inner loop
	
	clr innercnt
	adiw XL, 2	 //X points to next element	
	movw ZL, R14 //reset Z pointer to second[0]

	inc outercnt
	cp outercnt, paramN
	brne outer_loop_192

	//end of outer loop


	pop R31
	pop R30
	pop R29
	pop R28
	pop R27
	pop R26
	pop R19
	pop R18
	pop R17
	pop R16
	pop R15
	pop R14
	pop R10
	pop R9
	pop R8
	pop R7
	pop R6
	pop R2
	pop R1
	pop R0
ret

	
/*
polyMul_asm_4093_320 - computes multiplication of two polynomials
-- the first polynomial is is loaded from SRAM, the second from FLASH memory
-- optimized for p = 320, q = 4093
-- wrapper function has to initialize the return polynomial with 0's
-- T-flag ist used to store the MSB of inner_loop_cnt

Parameters in R25:R24, R23:R22
R24: low(&first[0])
R25: high(&first[0])
R22: low(&second[0])
R23: high(&second[0])
R21:R20 contains pointer to return polynomial

X -> first polynomial
Z -> second polynomial
Y -> resulting polynomial
*/


	
#define XL R26
#define XH R27
#define YL R28
#define YH R29
#define ZL R30 
#define ZH R31
#define outercnt_l R11
#define outercnt_h R12
#define innercnt_l R4
#define res_index_h R18 //q
#define res_index_l R16
#define temp R19
#define paramN_l R2
#define paramN_h R3

.global polyMul_asm_4093_320
polyMul_asm_4093_320:
	//R10, R9, R8, R6, R1, R0 are pushed for mulRed_asm
	push R0
	push R1
	push R2
	push R3
	push R4
	push R6
	push R8
	push R9
	push R10
	push R11
	push R12
	push R14
	push R15
	push R16
	push R17
	push R18
	push R19
	push R26
	push R27
	push R28
	push R29
	push R30
	push R31

	//store 320 for later comparison
	ldi temp, 0x40
	mov paramN_l, temp
	ldi temp, 0x01
	mov paramN_h, temp

	clr outercnt_l
	clr outercnt_h
	clr innercnt_l
	clr temp

	movw XL, R24
	movw ZL, R22

	movw R14, R22 //save adress of second[0] for later use

outer_loop_320:


inner_loop_320:

	//q = (i + j)
	clr res_index_l
	clr res_index_h

	add res_index_l, outercnt_l
	adc res_index_h, outercnt_h
	add res_index_l, innercnt_l
	bld temp, 0
	adc res_index_h, temp

	cp res_index_h, paramN_h
	brlo smaller_320
	brne greater_equal_320

	cp res_index_l, paramN_l
	brlo smaller_320

greater_equal_320:
	
	//q = i + j % 320
	sub res_index_l, paramN_l
	sbc res_index_h, paramN_h

	//mulRed_asm(first[i], second[j]);
	//load parameters for multiplication
	ld R24, X+
	ld R25, X

	lpm R22, Z+
	lpm R23, Z+

	call mulRed_asm_4093
	//result in R25:R24

	//make Y point to res[q]
	movw YL, R20 //reset Y to res[0]
	//add 2*q
	add YL, res_index_l
	adc YH, res_index_h
	add YL, res_index_l
	adc YH, res_index_h


	//res[q] -= d;
	ld R22, Y+
	ld R23, Y
	//res[q] now stored in R23:R22

	sub R22, R24
	sbc R23, R25

	//mod 4093
	brcc end_320 //value still positive
	//add 4093 otherwise
	ldi temp, 0xFD
	add R22, temp
	ldi temp, 0x0F
	adc R23, temp
	clr temp

	rjmp end_320

smaller_320:

	//mulRed_asm(first[i], second[j]);
	ld R24, X+
	ld R25, X

	lpm R22, Z+
	lpm R23, Z+

	rcall mulRed_asm_4093
	//result in R25:R24

	//make Y point to res[q]
	movw YL, R20 //reset Y to res[0]
	//add 2*q
	add YL, res_index_l
	adc YH, res_index_h
	add YL, res_index_l
	adc YH, res_index_h

	ld R22, Y+
	ld R23, Y
	//res[q] now stored in R23:R22

	//res[q] += d;
	add R22, R24
	adc R23, R25

//mod 4093
test_reduction3_320:
	cpi R23, 0b00001111
	brlo end_320
	breq consider_reduction3_320
	rjmp do_reduction3_320

consider_reduction3_320:

	cpi R22, 0b11111101
	brlo end_320

do_reduction3_320:

	subi R22, 0b11111101
	sbci R23, 0b00001111	

end_320:

	//store result
	st -Y, R22
	adiw YL, 1
	st Y, R23

	sbiw XL, 1 //X still points to first[outercnt]

	// inc loop counter
	inc innercnt_l

	brne skip_set_t		// set t flag if overflow occured

	set					// set t flag

skip_set_t:

	brtc jmp_inner_loop_320	// branch if t flag is cleared -> loop counter < 0x140 = 320

	cp innercnt_l, paramN_l
	breq skip_jmp_inner_loop_320

jmp_inner_loop_320:

	rjmp inner_loop_320	

skip_jmp_inner_loop_320:

	//end of inner loop
	
	clr innercnt_l
	clt				// clear t flag

	adiw XL, 2	 //X points to next element	
	movw ZL, R14 //reset Z pointer to second[0]

	// inc loop counter
	inc outercnt_l

	brne skip_inc_outercnt_h	// set MSB only if outercnt_l overflows
	inc outercnt_h

skip_inc_outercnt_h:

	cp outercnt_h, paramN_h
	brlo jmp_outer_loop_320

	cp outercnt_l, paramN_l
	breq skip_jmp_outer_loop_320

jmp_outer_loop_320:

	rjmp outer_loop_320	

skip_jmp_outer_loop_320:

	//end of outer loop

	pop R31
	pop R30
	pop R29
	pop R28
	pop R27
	pop R26
	pop R19
	pop R18
	pop R17
	pop R16
	pop R15
	pop R14
	pop R12
	pop R11
	pop R10
	pop R9
	pop R8
	pop R6
	pop R4
	pop R3
	pop R2
	pop R1
	pop R0
ret
















#define nRes1 r18
#define nRes2 R19
#define nRes3 R20

#define na_low R24
#define nb_low R22
#define nb_high R23

#define ntmpHL r22
#define ntmpHH nRes3
#define ntmpLL nRes1
#define ntmpLH nRes2 //has be one of the upper 16 registers because of ANDI


.global call_mulRed_asm_4093
call_mulRed_asm_4093:

mulRed_asm_4093_k:


	mov nRes3, na_low
	mulsu nRes3,nb_low
	mov nRes1,R0
	mov nRes2,R1

	clr nRes3
	tst R1
	brpl skip
	dec nRes3
skip:
	
	mov nb_low, na_low
	mulsu nb_low, nb_high

	add nRes2,R0
	adc nRes3,R1

	//result of the multiplication is now stored in R18:R17:R16
	//temph = x >> 12;
	mov ntmpHL, nRes2 //tmpH = Res3:Res2

	//4 shifts left
	asr ntmpHH
	ror ntmpHL
	asr ntmpHH
	ror ntmpHL
	asr ntmpHH
	ror ntmpHL
	asr ntmpHH
	ror ntmpHL	

	//12 bit value tmpH

	//templ = x & 0b111111111111;
	//tmpL = Res2:Res1
	andi ntmpLH, 0b00001111
	//12 bit Value tmpL

	//Return Value in R24:R25
	mov R24, ntmpHL
	mov R25, ntmpHH

	//x = (temph<<1)+temph+templ;
	lsl R24
	rol R25

	add R24, ntmpHL
	adc R25, ntmpHH

	add R24, ntmpLL
	adc R25, ntmpLH

	clr r1

	ret
