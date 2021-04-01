

// #include	"ATxmega128A1def.inc"

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

//#define TIMING_RESISTANT

.global mod7681
mod7681:
	 //value is in P0_low=r24, P0_high=r25
	 ldi S0, (7681 & 0xFF)
	 ldi S1, (7681>>8) & 0xFF
	 cpi P0_low, (7681 & 0xFF)
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
	
	
.global mm7681_check
mm7681_check:
	 //TODO
	 //Check if the second coefficient is one (then just return)
	 //ldi S0, 0x01
	 ///cpi P1_high,  0
	 //cpc P1_low, S0

	 //If second coefficient is one we just return (r25:24 hold the return value which is not one)
	 rjmp SECOND_NOT_ONE
	 ret

.global mm7681
mm7681:	
SECOND_NOT_ONE:	

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
	 movw T0l, S2
	 lsr T0h
	 ror T0l

	 movw T1l, S2
	 mov  T2, S1
	 lsl T2
	 rol T1l
	 rol T1h

	 lsl T2
	 rol T1l
	 rol T1h

	 lsl T2
	 rol T1l
	 rol T1h

	 //add
	 add T0l, T1l
	 adc T0h, T1h

	 add T0l, T1h
	 clr T2
	 adc T0h, T2
	
	 //mul
	 ldi V1, (7681 >> 8) & 0xFF
	 mul V1,T0l 
	
	//sub
	sub S0, T0l
    	sbc S1, T0h

	sub S1, R0


CHECK_SUB:
	cp V1, S1
	brlo DO_SUB
	brne FINISHED
	
	cpi S0, 1
	brlo FINISHED

DO_SUB:
	subi S0, 1
	sbc S1, V1
	
	rjmp CHECK_SUB

FINISHED:
	//Return argument has to be put into r25:r24
	clr r1
	mov RET0, S0
	mov RET1, S1
	ret

