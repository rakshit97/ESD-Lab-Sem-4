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
	LDRB R2, [R0]
	LDRB R10, [R0]
	MOV R3, #0xA
	
loop	SUB R2, R3
	ADD R4, #1
	CMP R2, #0xA
	BHS loop
	
	MOV R9, #0xA
	MUL R5, R4, R9
	SUB R10, R5
	TEQ R4, #0xA
	MOVEQ R4, #0x10
	TEQ R4, #0xB
	MOVEQ R4, #0x11
	TEQ R4, #0xC
	MOVEQ R4, #0x12
	TEQ R4, #0xD
	MOVEQ R4, #0x13
	TEQ R4, #0xE
	MOVEQ R4, #0x14
	TEQ R4, #0xF
	MOVEQ R4, #0x15
	LSL R4, #4
	ADD R4, R10
	STR R4, [R1]
	
SRC DCD 0x64
	AREA DATASEG, DATA, READWRITE
DST DCD 0
	END