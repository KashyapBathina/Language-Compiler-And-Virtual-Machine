	# $Id: parser_test2.asm,v 1.4 2024/08/20 00:05:26 leavens Exp $
	.text start
start:	NOP
	ADDI $sp, 0, 1
	SCA $sp, -1, $sp, 0
	SRI $sp, 1
	SWR $sp, -1, $fp
        ADDI $sp, -1, 104
	LWI $sp, -2, $gp, 0
	EXIT 0
	.data 104
	WORD fourtytwo = 42
	.stack 4200
	.end
