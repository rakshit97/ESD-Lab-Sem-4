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
	LDRB R3, [R0]
	AND R4, R3, #0xF
	AND R5, R3, #0xF0
	LSR R5, #4
	MOV R6, #0xA
	MLA R7, R5, R6, R4
	STR R7, [R1]
	
SRC DCD 0x64
	AREA DATASEG, DATA, READWRITE
DST DCD 0
	END