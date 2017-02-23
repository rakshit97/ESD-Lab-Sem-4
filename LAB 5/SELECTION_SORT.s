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
	LDR R0, =SRC
	LDR R1, =DST
	MOV R3, #10
loop  LDR R2, [R0], #4
	STR R2, [R1], #4
	SUB R3, #1
	TEQ R3, #0
	BNE loop
	
	LDR R0,= DST
	LDR R1, =DST
	MOV R3, #0
	
o_loop	MOV R1, R0
		MOV R8, R0
		LDR R4, [R0]
		MOV R6, #9
		SUB R6, R3
		MOV R7, R4
i_loop	LDR R5, [R1, #4]!
		CMP R7, R5
		MOVHI R7, R5
		MOVHI R8, R1
		SUB R6, #1
		TEQ R6, #0
		BNE i_loop
		STR R7, [R0]
		STR R4, [R8]
		ADD R3, #1
		TEQ R3, #9
		ADD R0, #4
		BNE o_loop
		
SRC DCD 0x14256363, 0x1343F241, 0xFFFFFFFF, 0xEEEEDDDD, 0xCCCCBBBB, 0x14256363, 0x1343F241, 0xFFFFFFFF, 0xEEEEDDDD, 0xCCCCBBBB
	AREA DATASEG, DATA, READWRITE
DST DCD 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	END
