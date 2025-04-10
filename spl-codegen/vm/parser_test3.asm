	# $Id: parser_test3.asm,v 1.5 2024/07/30 12:00:15 leavens Exp $
	.text start
start:	ARI $sp, -2
	BNE $sp, 1, +4
	ADDI $sp, 0, 100
	ADD $sp, 0, $gp, 0
	EXIT 0
	.data 1024
	WORD hundred = 100
	WORD forty = 40
	WORD six = 6
	.stack 4096
	.end
