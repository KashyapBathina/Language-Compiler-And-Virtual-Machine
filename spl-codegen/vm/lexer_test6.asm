	# $Id: lexer_test6.asm,v 1.4 2024/07/26 16:19:50 leavens Exp $
	.text st_art
st_art:	SWR $sp, 0, $sp
	ADDI $sp, 0, -1
	LWR $sp, $sp, 0
	EXIT 0
	.data 1024
	.stack 4096
	.end
	
