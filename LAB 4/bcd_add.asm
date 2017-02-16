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
	LDR R2, [R0], #4
	LDR R3, [R0]
	MOV R4, #8
	
loop  AND R5, R2, #0xF
	AND R6, R3, #0xF
	LSR R2, #4
	LSR R3, #4
	ADD R5, R6
	ADD R7, R5
	CMP R7, #9
	ADDHI R7, #6
	AND R8, R7, #0xF
	LSR R7, #4
	ORR R9, R8
	ROR R9, #4
	SUB R4, #1
	TEQ R4, #0
	BNE loop
	
	STR R9, [R1], #4
	STR R7, [R1]
	
SRC DCD 0x9, 0x56730
	AREA DATASEG, DATA, READWRITE
DST DCD 0
	END