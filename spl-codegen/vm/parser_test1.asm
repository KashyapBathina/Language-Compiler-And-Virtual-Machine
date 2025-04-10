	# $Id: parser_test1.asm,v 1.5 2024/07/30 12:00:15 leavens Exp $

.text begin
begin:	SUB $sp, 0, $sp, 0
        EXIT 0
.data   0x40
	WORD b = 10
	WORD w
	WORD c
	WORD sixteen = 16
.stack  0x4040
.end
