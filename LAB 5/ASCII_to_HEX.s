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
	MOV R2, #2
loop  LDRB R3, [R0], #1
	CMP R3, #0x41
	SUBHS R3, #0x37
	BHS store
	CMP R3, #0x39
	SUBLS R3, #0x30
store  ORR R4, R3
	ROR R4, #4
	SUB R2, #1
	TEQ R2, #0
	BNE loop
	
	ROR R4, #24
	STR R4, [R1]
	
SRC DCD 0x4637
	AREA DATASEG, DATA, READWRITE
DST DCD 0
	END