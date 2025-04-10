	.text 5
	PSTR $gp,0
	EXIT 1
	NOP
	NOP
	NOP
	PSTR $gp,10
	EXIT 0
	.data 1024
	STRING[10] ERRMSG = "Should have started at location 5!\n"
	STRING[10] GOOD = "OK, that started at the right spot!\n"
	.stack 5024
	.end
