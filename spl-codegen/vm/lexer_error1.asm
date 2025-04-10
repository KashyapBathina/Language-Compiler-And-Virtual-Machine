	# $Id: lexer_error1.asm,v 1.2 2024/08/28 21:25:00 leavens Exp $
.text 0
        CFHI $8, 2   # error, register number can't be 8 or higher
	CFLO $13, 0  # error, again, register number can't be 13
.data 2048
.stack 4096
.end
	
