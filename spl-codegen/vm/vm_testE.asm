	# $Id: vm_testE.asm,v 1.1 2024/11/10 14:34:25 leavens Exp leavens $
	.text 0
	SRI $sp, 1
	CPR $sp, $fp
	SWR $sp, 0, $sp
	SWR $gp, 0, $fp
	BEQ $gp, 0, 2
bad:	EXIT 1
okay:	EXIT 0
	.data 2048
	.stack 8096
	.end
