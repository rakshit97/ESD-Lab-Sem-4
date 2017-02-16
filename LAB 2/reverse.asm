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
	LDR R0, = SRC
	LDR R1, = SRC
	ADD R1, 0x24
	
	MOV R4, #5
Start LDR R2, [R0]
	LDR R3, [R1]
	STR R2, [R1]
	STR R3, [R0]
	ADD R0, #4
	SUB R1, #4
	SUB R4, #1
	TEQ R4, #0
	BNE Start

	AREA DATASEG, DATA, READWRITE
SRC DCD 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0x0100
	END