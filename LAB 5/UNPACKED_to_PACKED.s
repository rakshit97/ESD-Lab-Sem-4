	AREA RESET, DATA, READONLY
	EXPORT __Vectors

__Vectors
	DCD 0x10000000
	DCD Reset_Handler
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
	
Reset_Handler
	LDR R0,= SRC
	LDR R1,= DST	
	MOV R2, #4
loop  LDRB R3, [R0], #1
	AND R3, #0xF
	ORR R4, R3
	ROR R4, #4
	SUB R2, #1
	TEQ R2, #0
	BNE loop
	
	ROR R4, #16
	STR R4, [R1]
	
SRC DCD 0x04060307
	AREA DATASEG, DATA, READWRITE
DST DCD 0
	END