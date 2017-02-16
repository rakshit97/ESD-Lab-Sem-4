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
	LDR R1,= DST
	MOV R3, N
	MLA R2, R3, R3, R3
	LSR R2, #1
	STR R2, [R1]
N EQU 10

	AREA DATASEG, DATA, READWRITE
DST DCD 0
	END