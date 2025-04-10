	# $Id: error_vm_test1.asm,v 1.1 2023/09/18 03:32:18 leavens Exp $
	.text start
start:	ADDI $0, $t0, 1
	ADD $0, $t0, $fp
	EXIT
	.data 1024
	.stack 4096
	.end
	
