	# $Id: unparser_test2.asm,v 1.2 2023/09/16 13:29:58 leavens Exp $
	.text start
start:	ADD $0, $1, $2
	SUB $3, $4, $5
	MUL $6, $7
	DIV $8, $9
	ADD $10, $11, $12
	ADD $13, $14, $15
	ADD $16, $17, $18
	SUB $19, $20, $21
	SUB $22, $23, $24
	MUL $25, $28
	ADD $29, $1, $8
	ADD $30, $1, $9
	JR  $31
	EXIT
	.data 1024
	.stack 4096
	.end

