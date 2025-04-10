	# $Id: unparser_test1.asm,v 1.3 2023/09/16 16:23:10 leavens Exp $
	.text go
go:     ADD $8, $9, $10
	ADDI $0, $9, 52
        ADDI $0, $10, -0934
	EXIT
	.data 0x1000
	WORD sixteen = 0x10
	WORD b25 = 25
	.stack 0x4000
	.end
	
