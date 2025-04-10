	# $Id: parser_test4.asm,v 1.5 2024/07/30 12:00:15 leavens Exp $
	.text start
start:	ARI $sp, -2
	BNE $sp, -1, +1  # shouldn't be effective, as both what $sp and $sp-1
	                # point to should contain 0
	EXIT 0
	.data 2048
	WORD five = +5
	.stack 6144
	.end
