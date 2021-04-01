	#define P0_low r24
	 #define P0_high r25
	 #define P1_low r22
	 #define P1_high r23

	 #define T1  r30
	 #define C1  r31

	 #define V0 r22
	 #define V1 r23
	 #define V2 r24
	 #define V3 r25

	 #define S0 r18
	 #define S1 r19
	 #define S2 r20
	 #define S3 r21

	 #define RET0 r24
	 #define RET1 r25



//#############################################  mulmod24578 #################################
.global mm24578
mm24578:
	 // --------------------- PROGRAM ----------------------
	 //Multiply a*b. Store result in P1-P4. Use S0-S4
	 mul P0_low, P1_low
	 movw S0, r0
	 mul P0_high, P1_high
	 mov S2, r0
	 mov S3, r1
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

	 //Load 12289<<16 - constant that is substracted
	 ldi V0, ((12289<<(16)) & 0xFF)		  //LSB
	 ldi V1, ((12289<<(16)) >> 8) & 0xFF
	 ldi V2, ((12289<<(16)) >> 16) & 0xFF
	 ldi V3, ((12289<<(16)) >> 24) & 0xFF //MSB


	 // ######### unroll first two operations on 4 registers ########
	// #### Operation on 30 bits #####
	 //if (result >= mul12289){
	 CP S0, V0
	 CPC S1, V1
	 CPC S2, V2
	 CPC S3, V3
	 BRLT NOT_GREATER_U04_DUMMY
	 //Test was TRUE
	 SUB S1, V1
	 SBC S2, V2
	 SBC S3, V3
	 rjmp NOT_GREATER_U04
NOT_GREATER_U04_DUMMY:
	 inc S1
	 inc S1
	 dec S1
	 dec S1
	 //Now shift V>>1
NOT_GREATER_U04:
	 LSR V3
	 ROR V2
	 ROR V1

// #### Operation on 29 bits #####
	 //if (result >= mul12289){
	 CP S0, V0
	 CPC S1, V1
	 CPC S2, V2
	 CPC S3, V3
	 BRLT NOT_GREATER_U03_DUMMY
	 //Test was TRUE
	 SUB S1, V1
	 SBC S2, V2
	 SBC S3, V3
	 rjmp NOT_GREATER_U03
NOT_GREATER_U03_DUMMY:
	 inc S1
	 inc S1
	 dec S1
	 dec S1
	 //Now shift V>>1
NOT_GREATER_U03:
	 LSR V3
	 ROR V2
	 ROR V1
	  // #### Operation on 28 bits #####
	 //if (result >= mul12289){
	 CP S0, V0
	 CPC S1, V1
	 CPC S2, V2
	 CPC S3, V3
	 BRLT NOT_GREATER_U02_DUMMY
	 //Test was TRUE
	 SUB S1, V1
	 SBC S2, V2
	 SBC S3, V3
	 rjmp NOT_GREATER_U02
NOT_GREATER_U02_DUMMY:
	 inc S1
	 inc S1
	 dec S1
	 dec S1
	 //Now shift V>>1
NOT_GREATER_U02:
	 LSR V3
	 ROR V2
	 ROR V1


	  // #### Operation on 27 bits #####
	 //if (result >= mul12289){
	 CP S0, V0
	 CPC S1, V1
	 CPC S2, V2
	 CPC S3, V3
	 BRLT NOT_GREATER_U01_DUMMY
	 //Test was TRUE
	 SUB S1, V1
	 SBC S2, V2
	 SBC S3, V3
	 rjmp NOT_GREATER_U01
NOT_GREATER_U01_DUMMY:
	 inc S1
	 inc S1
	 dec S1
	 dec S1
	 //Now shift V>>1
NOT_GREATER_U01:
	 LSR V3
	 ROR V2
	 ROR V1


	 // #### Operation on 26 bits #####
	 //if (result >= mul12289){
	 CP S0, V0
	 CPC S1, V1
	 CPC S2, V2
	 CPC S3, V3
	 BRLT NOT_GREATER_U0_DUMMY
	 //Test was TRUE
	 SUB S1, V1
	 SBC S2, V2
	 SBC S3, V3
	 rjmp NOT_GREATER_U0
NOT_GREATER_U0_DUMMY:
	 inc S1
	 inc S1
	 dec S1
	 dec S1
	 //Now shift V>>1
NOT_GREATER_U0:
	 LSR V3
	 ROR V2
	 ROR V1

	 // #### Operation on 25 bits #####
	  //if (result >= mul12289){
	 CP S0, V0
	 CPC S1, V1
	 CPC S2, V2
	 CPC S3, V3
	 BRLT NOT_GREATER_U1_DUMMY
	 //Test was TRUE
	 SUB S1, V1
	 SBC S2, V2
	 SBC S3, V3
	 rjmp NOT_GREATER_U1
NOT_GREATER_U1_DUMMY:
	 inc S1
	 inc S1
	 dec S1
	 dec S1
	 //Now shift V>>1
NOT_GREATER_U1:
	 LSR V3
	 ROR V2
	 ROR V1

	 // #### Operation on 24 bits #####
	 //if (result >= mul12289){
	 CP S0, V0
	 CPC S1, V1
	 CPC S2, V2
	 CPC S3, V3
	 BRLT NOT_GREATER_U2_DUMMY
	 //Test was TRUE
	 SUB S1, V1
	 SBC S2, V2
	 SBC S3, V3
	  rjmp NOT_GREATER_U2
NOT_GREATER_U2_DUMMY:
	 inc S1
	 inc S1
	 dec S1
	 dec S1
	 //Now shift V>>1
NOT_GREATER_U2:
	 LSR V3
	 ROR V2
	 ROR V1

	 // #### Operation on 23 bits #####
	 //if (result >= mul12289){
	 CP S0, V0
	 CPC S1, V1
	 CPC S2, V2
	 CPC S3, V3
	 BRLT NOT_GREATER_U3_DUMMY
	 //Test was TRUE
	 SUB S1, V1
	 SBC S2, V2
	 SBC S3, V3
	 rjmp NOT_GREATER_U3
NOT_GREATER_U3_DUMMY:
	 inc S1
	 inc S1
	 dec S1
	 dec S1
	 //Now shift V>>1
NOT_GREATER_U3:
	 LSR V3
	 ROR V2
	 ROR V1

	 //No we work only on three registers
	 ldi C1, 14-4-2

DO_WORK_X0:
	 //if (result >= mul12289){
	 CP S0, V0
	 CPC S1, V1
	 CPC S2, V2
	 //CPC S3, V3
	 BRLT NOT_GREATER_X0_DUMMY
	 //Test was TRUE
	 SUB S0, V0
	 SBC S1, V1
	 SBC S2, V2
	 rjmp NOT_GREATER_X0
NOT_GREATER_X0_DUMMY:
	 inc S1
	 inc S1
	 dec S1
	 dec S1
	 //SBC S3, V3
	 //Now shift V>>1
NOT_GREATER_X0:
	 //LSR V3
	 //ROR V2
	 LSR V2
	 ROR V1
	 ROR V0
	 dec C1 //test if we did enough operations
	 breq FINISHED_X1	//branch if not equal (zero flag = 0)
	 rjmp DO_WORK_X0

FINISHED_X1:
/*
	 //No we work only on two registers
	 ldi C1, 1
DO_WORK_X1:
	 //if (result >= mul12289){
	 CP S0, V0
	 CPC S1, V1
	 BRLT NOT_GREATER_X1_DUMMY
	 //Test was TRUE
	 SUB S0, V0
	 SBC S1, V1
	 rjmp NOT_GREATER_X1
NOT_GREATER_X1_DUMMY:
	 inc S1
	 dec S1
	 ori S1, 0
	 //Now shift V>>1
NOT_GREATER_X1:
	 LSR V1
	 ROR V0

	 dec C1 //test if we did enough operations
	 breq FINISHED	//branch if not equal (zero flag = 0)
	 rjmp DO_WORK_X1
*/

FINISHED:
	//Return argument has to be put into r25:r24
	clr r1
	mov RET0, S0
	mov RET1, S1
	 //Result ist now in S3:S0
	ret
