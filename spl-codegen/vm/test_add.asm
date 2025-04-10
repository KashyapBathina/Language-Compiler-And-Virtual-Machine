	# $Id: test_add.asm,v 1.1 2023/09/22 01:29:49 leavens Exp $
	.text start
start:	ADDI $0, $t7, 7   # put 7 in $t7
	ADDI $0, $t5, 5   # put 5 in $t5
	ADD $t5, $t7, $t2  # put 12 in $t2
	EXIT
	.data 1024
	.stack 4096
	.end
