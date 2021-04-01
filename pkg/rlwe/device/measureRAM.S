//#include	"ATxmega128A1def.inc"

#define XL r26
#define XH r27
#define temp R16
#define temp2 R17
#define cnt R18

.global startRAM
startRAM:
	PUSH XL
	PUSH XH
	PUSH temp

	 IN XL, 61  //SPL
	 IN XH, 62  //SPH
	; ldi r24, __heap_start
	 ;MOV R24, XL
	; MOV R25, XH
	 LDI temp, 0xE7

RAMSTARTLOOP:
	CP XH, R25  
	BRNE DO_START_LOOP
	CP XL, R24 
	BREQ END

DO_START_LOOP:
	ST X, temp
	SBIW XL, 1
	RJMP RAMSTARTLOOP

END:
	IN R24, 61
	IN R25, 62
	POP temp
	POP XH
	POP XL	
	 ret


.global endRAM
endRAM:
	PUSH XL
	PUSH XH
	PUSH temp
	PUSH temp2
	PUSH cnt

	 IN XL, 61  //SPL
	 IN XH, 62  //SPH
	 LDI temp, 0xE7

	 LDI cnt, 0

RAMENDLOOP:
	CPI XH, 0x27  //hi(0x2000)
	BRNE DO_END_LOOP
	CPI XL, 0x00 //lo(0x2000)
	BREQ END_E

DO_END_LOOP:
	LD temp2, X
	SBIW XL, 1

	CPI temp2, 0xE7
	BRNE NO_HIT

	INC cnt

	CPI cnt, 16
	BREQ END_E

	RJMP RAMENDLOOP

NO_HIT:
	LDI cnt, 0
	RJMP RAMENDLOOP

END_E:
	MOV R24, XL
	MOV R25, XH

	SBIW XL, 15

	POP cnt
	POP temp2
	POP temp
	POP XH
	POP XL	
	 ret
