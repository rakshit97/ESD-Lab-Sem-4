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
	LDR R11, [R0], #4
	LDR R12, [R0]
	MOV R0, #0
	MOV R1, R11
	MOV R10, #1

loop	CMP R10, R12
	BEQ exit
	MOV R2, R10
	MOV R3, #1
	BL func
	MOV R10, R9
	MOV R9, #0
	
	MOV R2, R11
	MOV R3, R1
	BL func
	MOV R11, R9
	MOV R9, #0
	
	MOV R2, R7
	MOV R3, R0
	BL func
	MOV R0, R9
	MOV R9, #0
	MOV R7, #0
	B loop
	
func MOV R4, #8
	MOV R5, #0
	MOV R6, #0
	MOV R7, #0
loop1  AND R5, R2, #0xF
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
	BNE loop1
	BX LR
	
exit  LDR R1, =DST
	STR R11, [R1], #4
	STR R0, [R1]
	
SRC DCD 0x99999999, 0x99999999
	AREA DATASEG, DATA, READWRITE
DST DCD 0
	END