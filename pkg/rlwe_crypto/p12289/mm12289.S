#define P0_low r24
	 #define P0_high r25
	 #define P1_low r22
	 #define P1_high r23

	 #define V1 R27

	 #define T0l r22
	 #define T0h r23
	 #define T1l r24
	 #define T1h r25
	 #define T2  r26

	 #define S0 r18
	 #define S1 r19
	 #define S2 r20
	 #define S3 r21

	 #define RET0 r24
	 #define RET1 r25



//#############################################  mulmod12289 #################################
.global mm12289
mm12289:
	 // --------------------- PROGRAM ----------------------
	 //Multiply a*b. Store result in P1-P4. Use S0-S4
	 mul P0_low, P1_low
	 movw S0, r0
	 mul P0_high, P1_high
	 movw S2, r0
	 mul P0_high, P1_low
	 clr P1_low //have a zero register for addition
	 add S1, r0
	 adc S2, r1
	 adc S3, P1_low
	 mul P0_low, P1_high
	 add S1, r0
	 adc S2, r1
	 adc S3, P1_low
	 //result of multiplication is now in S3:S0

	 //reduction
	 // shift
	 clr V1
	 // T0
	 movw T0l, S2
	 movw T1l, S2
	 mov  T2, S1
	 // T1
	 add T0l, T1h
	 adc T0h, V1

	 //T2
	 lsl T2
	 rol T1l
	 rol T1h

	 lsl T2
	 rol T1l
	 rol T1h

	 add T0l, T1l
	 adc T0h, T1h

	 //T3
	 add T0l, T1h
	 adc T0h, V1

	 //T4
	 lsl T1l
	 rol T1h
	 lsl T1l
	 rol T1h

	 add T0l, T1h
	 adc T0h, V1

	 //T5
	 lsl T1l
	 rol T1h
	 rol V1
	 lsl T1l
	 rol T1h
	 rol V1

	 add T0l, T1h
	 adc T0h, V1

	
	 //mul
	 ldi V1, (12289 >> 8) & 0xFF
	 mul V1,T0l 
	 movw T1l, R0
	 mul V1,T0h
	 add T1h, R0

	clr T2

	//sub
	sub S0, T0l
    	sbc S1, T0h
	sbc S2, T2

	sub S1, T1l
	sbc S2, T1h

	

CHECK_SUB:
	cpi S2, 1
	breq DO_SUB

	cp V1, S1
	brlo DO_SUB
	brne FINISHED
	
	cpi S0, 1
	brlo FINISHED

DO_SUB:
	subi S0, 1
	sbc S1, V1
	sbc S2, T2
	
	rjmp CHECK_SUB

FINISHED:
	//Return argument has to be put into r25:r24
	clr r1
	mov RET0, S0
	mov RET1, S1
	ret


// #############################################  mod12289 (addition) #################################
.global mod12289
mod12289:
	 //value is in P0_low=r24, P0_high=r25
	 ldi S0, (12289 & 0xFF)
	 ldi S1, (12289>>8) & 0xFF

	 cpi P0_low, (12289 & 0xFF)
	 cpc P0_high, S1
	 BRLT DO_NIX
	 sub P0_low,  S0
	 sbc P0_high, S1
	 rjmp FIN
DO_NIX:
	 inc S0
	 ori S0,0
	 dec S0
FIN:
	 ret
