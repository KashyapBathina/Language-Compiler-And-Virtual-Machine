  # $Id: parser_test5.asm,v 1.13 2024/08/29 02:05:03 leavens Exp $

.text here

here:	LIT $sp, 0, 0
        SUB $sp, -1, $sp, 0
	AND $sp, -2, $sp, -3
	SRI $sp, 3
	BORI $sp, 0, 0x8
	JREL 3  # skip next 2 instructions
	NOR $ra, -1, $sp, 0  # causes an error
	XOR $sp, -2, $sp, -1 # why not?
        MUL $r5, 0
	CFHI $1, 0
	CFLO $2, 0
	LIT $sp, -1, 1
	LWR $r5, $sp, -1   # put 1 in $r5
	SRI $sp, 1
	DIV $sp, 0
	ADDI $sp, 0, 13
	ADD $gp, 0, $gp, 0
	CALL fun
	EXIT 0
fun:	ANDI $sp, 0, 0xff
	XORI $sp, 0, 0x00
	BEQ $sp, 0, 2
        BNE $sp, 0, 333
	BGEZ $sp, 0, 3
	ADDI $sp, 0, 11
	BGTZ $sp, 1, -2
	BLTZ $sp, 1, 2
	BLEZ $sp, 0, 2
	CPW $sp, 0, $gp, 1     # put 1025 in stack top
	LWR $fp, $sp, 0        # put 1025 in $fp register, violates invariant!
	ARI $sp, -1    # allocate a word on the stack
	CPW $sp, 0, $gp, 1      # put 1025 in stack top
	ADDI $sp, 0, -1    # make $sp be 1024
	SUB $sp, 0, $sp, 0     # zero out the top of the stack
	ARI $sp, -1    # allocate a word on the stack
	CPW $gp, 2, $sp, 0   # put 'Y' on top of stack
	SLL $sp, 0, 8          # shift it 8 bits to the left
	BOR $sp, 0, $gp, 0     # put '\n' on top of stack
	PCH $sp, 1     # print the 'Y'
	PCH $sp, 0     # print '\n'
	RTN
	SUB $sp, 0, $sp, 0  # zero out the top of the stack
	DIV $sp, 0     # cause a division by 0 error
	EXIT 1
       
.data   2048
	CHAR nl = '\n'
	WORD newsp = 1025
	CHAR ychar = 'Y'
	WORD c
	WORD sixteen = 0x10

.stack  6144
.end
