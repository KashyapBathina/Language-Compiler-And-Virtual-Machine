	# $Id: lexer_test3.asm,v 1.4 2024/07/26 16:19:50 leavens Exp $
	.text go
go:     ADDI $sp, 0, 93
	ADDI $sp, 0, 093
        ADDI $sp, 0, -093
	EXIT 0
	.data 512
	WORD sixteen = 0x10
	.stack 4512
	.end
	
