# $Id: parser_test6.asm,v 1.5 2024/08/28 21:25:00 leavens Exp $
.text start
zero:	SUB $sp, 0, $sp, 0
	AND $sp, 0, $sp, 0
	BOR $sp, 0, $sp, 0
	NOR $sp, 0, $sp, 0	# why?
	XOR $sp, 0, $sp, 0 # & why not?
	MUL $sp, 0
	CFHI $sp, 0
	CFLO $sp, -1
	RTN
start:	ADDI $sp, 0, 13
	ADD $sp, 0, $ra, 0
	CALL zero
	ANDI $sp, 0, 0x8
	XORI $sp, -1, 0x567a
	BEQ $sp, -1, 2
	BNE $sp, -1, 4
	BGEZ $sp, 0, 3
	BGTZ $sp, 0, 2
	BLTZ $sp, 0, 1
	BLEZ $sp, 1, 2
	SRI $sp, 1
	LIT $sp, 0, 100
	LIT $sp, -1, 10
	MUL $sp, -1
	STRA
	NOTR
	EXIT 0
.data 2048
WORD w0 = 10
WORD w1 = 0
WORD w2 = -52345
WORD w3 = 16
.stack 6144
.end
