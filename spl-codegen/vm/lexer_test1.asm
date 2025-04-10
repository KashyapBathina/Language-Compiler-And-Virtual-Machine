  # $Id: lexer_test1.asm,v 1.22 2024/11/10 14:34:25 leavens Exp leavens $

.text 0

	NOP
	SRI $sp, 1
	ADD $sp, 0, $0, +1
        SUB $gp, 1, $sp, 0  # put 0 in memory[GP+1]
        CPW $gp, 3, $sp, 0   # put 99 in top of stack
	CPR $gp, $gp
	AND $sp, -1, $r4, 0  # anding memory[SP] and location 1, result in memory[SP-1]!
	BOR $sp, -1, $r4, 0 # or location zero, which is 0, so no change
	NOR $sp, -1, $sp, -1 # bitwise negate memory[SP-1]
	XOR $gp, 2, $gp, 15  # xor c and memory[GP+15]
	LWR $r4, $gp, 2
	SWR $gp, 4, $r4
	SCA $sp, -1, $sp, 0    # store stack top address one below stack top
	NEG $gp, 0, $gp, 0
        LIT $sp, -1, 122       # put 122 below top of the stack
	SRI $sp, 1             # stack top is 122
	MUL $sp, 0
	CFLO $sp, -1
	CFHI $sp, -2
	DIV $sp, 0     # will cause a division by 0 error, eventually!
	CFLO $sp, -3
	CFHI $sp, -4
	SLL $sp, 0, 2
	SRL $sp, -1, 3
	JREL +2      # skip next instruction
	JMP $r5, 0   # causes a segmentation fault!
        ANDI $sp, 0, 0x0123
        BORI $sp, -1, 0x003f
	NORI $sp, -2, 0x1ff
	XORI $sp, -3, 0
	BEQ $sp, 0, +2   # skip next instruction
	BGEZ $sp, -2, +2
	BGTZ $sp, -3, -0xf  # jump -15 backwards, if memory[GPR[$sp]-3] > 0
	BLTZ $sp, -4, +2
	BLEZ $sp, -5, +2
	SCA  $sp, -6, $gp, 0
	LWI  $sp, -7, $sp, -6  # should load memory[GPR[$gp]]
        BNE $sp, -1, -4
	JMPA here
	CALL here
	JREL +2
here:	RTN
	PSTR $gp, 4
	PCH $gp, 15
	RCH $gp, 5
	NOTR
        EXIT 1
       
.data   2048
	WORD b = 10
	STRING[2] str = "1234"
	CHAR c = 'c'
	STRING[1] three = "3\n"
	WORD sixteen = 0x10

.stack  8096	
.end
