	# $Id: lexer_test5.asm,v 1.1 2024/08/22 00:44:21 leavens Exp $
	.text 0
	LIT $sp, 0, -1
	ANDI $sp, 0, 0xff
	ADDI $sp, 0, 0x100
	EXIT 0
	.data 512
	STRING [3] ls = "a long str\n"
	.stack 1024
	.end
