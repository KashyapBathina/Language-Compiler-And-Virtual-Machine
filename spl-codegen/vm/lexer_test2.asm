	# $Id: lexer_test2.asm,v 1.8 2024/08/20 19:25:40 leavens Exp $
	.text go
	 NOTR
	PSTR $gp, 18
	EXIT 1
go:	EXIT 0
	.data 100
	WORD sixteen = 0x10
	CHAR c = 'a'
	CHAR tab = '\t'
	CHAR nl = '\n'
	CHAR SQ = '\''
	CHAR DQ = '\"'
	CHAR BS = '\\'
	CHAR R = '\r'
	CHAR FF = '\f'
	CHAR VT = '\v'
	CHAR BELL = '\a'
	CHAR HE2 = '\x0F'
	CHAR h = '\x1'
	CHAR h12 = '\x12'
	CHAR he = '\xf'
	CHAR sb = '\b'
	CHAR null = '\0'
	CHAR oe = '\0135'
	STRING [1] ot3 = "no\n"
	STRING [3] others = "\r\f\v\a\b\'\"\n"
	STRING [2] wnl = "abc12\n"
	STRING [1] he2 = "a\x12\x0f"
	STRING [12] othersE = "\r\f\v\a\b\'\"\x0F\0127\n"
	.stack 0x4000
	.end
	
