	AREA RESET, DATA, READONLY
	EXPORT __Vectors

__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
	
Reset_Handler
	LDR R0,= SRC
	LDR R1,= DST	
	LDR R2, [R0]
	MOV R3, #1
	BL func
	STR R3, [R1]
	B end_code
	
func  MUL R3, R2
	SUB R2, #1
	TEQ R2, #1
	BEQ exit
	PUSH {R14}
	BL func
exit  POP {R14}
	BX LR
	
end_code
SRC DCD 0x7
	AREA DATASEG, DATA, READWRITE
DST DCD 0
	END