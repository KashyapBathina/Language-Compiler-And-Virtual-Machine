	# $Id: lexer_test4.asm,v 1.1 2024/08/20 02:21:19 leavens Exp $
	.text 0
	LIT $sp, -1, 122       # put 122 below top of the stack
	SRI $sp, 1             # stack top is 122
	MUL $sp, 0
	EXIT 0
.data 1024
.stack 2048
.end
