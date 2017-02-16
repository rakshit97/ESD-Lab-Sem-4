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
	MOV R0, N
	MOV R2, #1
	MOV R3, #1
	STR R2, [R1], #4
	STR R3, [R1], #4
	SUB R0, #2
	
loop  CMP R0, 0
	BEQ exit
	ADD R4, R2, R3
	MOV R2, R3
	MOV R3, R4
	STR R4, [R1], #4
	SUB R0, #1
	B loop
	
exit
N EQU 0x10
SRC DCD 0x7, 0x3
	AREA DATASEG, DATA, READWRITE
DST DCD 0
	END