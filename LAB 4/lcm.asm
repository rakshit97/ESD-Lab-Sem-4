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
	
	MOV R4, R2
	MOV R5, R3
	
while  CMP R4, R5
	ADDHI R5, R3
	ADDLO R4, R2
	BNE while
	
	STR R4, [R1]
	
SRC DCD 0x7, 0x3
	AREA DATASEG, DATA, READWRITE
DST DCD 0
	END