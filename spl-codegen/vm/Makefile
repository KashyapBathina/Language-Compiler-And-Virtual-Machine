# $Id: Makefile,v 1.72 2024/11/13 15:36:59 leavens Exp leavens $

# Add .exe to the end of target to get that suffix in the rules
VM = vm
CC = gcc
# on Linux, the following can be used with gcc:
# CFLAGS = -fsanitize=address -static-libasan -g -std=c17 -Wall
CFLAGS = -g -std=c17 -Wall
MV = mv
RM = rm -f
CHMOD = chmod
SUBMISSIONZIPFILE = submission.zip
ZIP = zip -9
# Add the names of your own files with a .o suffix to link them into the VM
VM_OBJECTS = machine_main.o machine.o \
             machine_types.o instruction.o bof.o \
             regname.o utilities.o
TESTS = vm_test0.bof vm_test1.bof vm_test2.bof vm_test3.bof \
	vm_test4.bof vm_test5.bof vm_test6.bof vm_test7.bof \
	vm_test8.bof vm_test9.bof vm_testA.bof vm_testB.bof \
	vm_testC.bof vm_testD.bof vm_testE.bof
TESTSOURCES = $(TESTS:.bof=.asm)
EXPECTEDOUTPUTS = $(TESTS:.bof=.out)
EXPECTEDLISTINGS = $(TESTS:.bof=.lst)
# STUDENTESTOUTPUTS is all of the .myo files corresponding to the tests
# if you add more tests, you can add more to this list,
# or just add to TESTS above
STUDENTTESTOUTPUTS = $(TESTS:.bof=.myo)
# STUDENTESTLISTINGS is all of the .myp files corresponding to the tests
# if you add more tests, you can add more to this list,
# or just add to TESTS above
STUDENTTESTLISTINGS = $(TESTS:.bof=.myp)
# Don't remove these outputs if there are errors
.PRECIOUS: $(STUDENTTESTOUTPUTS) $(STUDENTTESTLISTINGS)

# create the VM executable
.PRECIOUS: $(VM)

$(VM): $(VM_OBJECTS)
	$(CC) $(CFLAGS) -o $(VM) $(VM_OBJECTS)

# rule for compiling individual .c files
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean cleanall
clean:
	$(RM) *~ *.o *.myo *.myp *.bof '#'*
	$(RM) $(VM).exe $(VM)
	$(RM) *.stackdump core
	$(RM) $(SUBMISSIONZIPFILE)

cleanall: clean
	$(RM) $(ASM) $(ASM).exe $(DISASM) $(DISASM).exe
	$(RM) test test.exe $(BOF_BIN_DUMP) $(BOF_BIN_DUMP).exe

# rule for making .bof files with the assembler ($(ASM));
# this might need to be done if not running on Linux (or Windows)

%.bof: %.asm $(ASM)
	./$(ASM) $<

# Rules for making individual outputs (e.g., execute make test1.myo)
# the .myo files are outputs from running the .bof files in the VM
.PRECIOUS: %.myo %.myp
%.myo: %.bof $(VM)
	./$(VM) -t $< > $@ 2>&1

%.myp: %.bof $(VM)
	./$(VM) -p $< > $@ 2>&1

# main target for testing
.PHONY: check-outputs
check-outputs: $(VM) $(ASM) $(TESTS) check-lst-outputs check-vm-outputs 
	@echo 'Be sure to look for two test summaries above (listings and execution)'

check-lst-outputs check-asm-outputs:
	@DIFFS=0; \
	for f in `echo $(TESTS) | sed -e 's/\\.bof//g'`; \
	do \
		echo listing "$$f.bof" using ./$(VM) -p ...; \
		./$(VM) -p "$$f.bof" > "$$f.myp" 2>&1; \
		diff -w -B "$$f.lst" "$$f.myp" && echo 'passed!' \
			|| { echo 'failed!'; DIFFS=1; }; \
	done; \
	if test 0 = $$DIFFS; \
	then \
		echo 'All listing tests passed!'; \
	else \
		echo 'Some listing test(s) failed!'; \
	fi

check-vm-outputs:
	@DIFFS=0; \
	for f in `echo $(TESTS) | sed -e 's/\\.bof//g'`; \
	do \
		echo running "$$f.bof" in the VM using ./$(VM) -t ...; \
		./$(VM) -t "$$f.bof" > "$$f.myo" 2>&1; \
		diff -w -B "$$f.out" "$$f.myo" && echo 'passed!' \
			|| { echo 'failed!'; DIFFS=1; }; \
	done; \
	if test 0 = $$DIFFS; \
	then \
		echo 'All VM execution tests passed!'; \
	else \
		echo 'Some VM execution test(s) failed!'; \
	fi

# Automatically generate the submission zip file
$(SUBMISSIONZIPFILE): *.c *.h $(STUDENTTESTOUTPUTS) $(STUDENTTESTLISTINGS) \
		Makefile 
	$(ZIP) $@ $^ asm.y asm_lexer.l $(EXPECTEDOUTPUTS) $(EXPECTEDLISTINGS) $(TESTS) $(TESTSOURCES)

# instructor's section below...

ASM = asm
DISASM = disasm
BOF_BIN_DUMP = bof_bin_dump
LEX = flex
LEXFLAGS =
# the following line is just to jog the memory, it is not used
FLEX = $(LEX)
YACC = bison
YACCFLAGS = -Wall --locations -d -v
LEXER = lexer

.DEFAULT: $(VM)

$(ASM)_lexer.c: $(ASM)_lexer.l $(ASM).tab.h
	$(LEX) $(LEXFLAGS) $<

$(ASM)_lexer.o: $(ASM)_lexer.c ast.h $(ASM).tab.h utilities.h char_utilities.h file_location.h
	$(CC) $(CFLAGS) -Wno-unused-but-set-variable -Wno-unused-function -c $<

$(ASM).tab.o: $(ASM).tab.c $(ASM).tab.h
	$(CC) $(CFLAGS) -Wno-unused-const-variable -c $<

instruction.o: $(ASM).tab.h

$(ASM).tab.c $(ASM).tab.h: $(ASM).y ast.h parser_types.h machine_types.h 
	$(RM) $(ASM).tab.h $(ASM).tab.c
	$(YACC) $(YACCFLAGS) $(ASM).y

lexer.o: lexer.c lexer.h $(ASM).tab.h
	$(CC) $(CFLAGS) -c $<

$(LEXER) : $(LEXER)_main.o $(LEXER).o $(ASM)_lexer.o ast.o $(ASM).tab.o file_location.o lexer.o utilities.o char_utilities.o
	$(CC) $(CFLAGS) $^ -o $@

$(ASM)_main.o: $(ASM)_main.c $(ASM).tab.h ast.h parser_types.h machine_types.h

ASM_OBJECTS = $(ASM)_main.o $(ASM).tab.o $(ASM)_lexer.o $(ASM)_unparser.o ast.o bof.o file_location.o lexer.o pass1.o assemble.o instruction.o machine_types.o regname.o symtab.o utilities.o char_utilities.o

$(ASM): $(ASM).tab.h $(ASM_OBJECTS) 
	$(CC) $(CFLAGS) $^ -o $@

$(DISASM): disasm_main.o disasm.o instruction.o bof.o machine_types.o regname.o utilities.o
	$(CC) $(CFLAGS) -o $(DISASM) $^

.PHONY: all
all: $(VM) $(ASM) $(DISASM)

.PHONY: check-separately
check-separately:
	$(CC) $(CFLAGS) -c *.c
