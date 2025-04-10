# $Id: Makefile,v 1.66 2024/11/22 23:03:28 leavens Exp leavens $
# Makefile for SPL compiler and code generation in COP 3402

# Add .exe to the end of target to get that suffix in the rules
COMPILER = compiler
LEXER = ./compiler -l
UNPARSER = ./compiler -u
VM = vm
DISASM = $(VM)/disasm
RUNVM = $(VM)/$(VM)

# Tools used
CC = gcc
# on Linux, the following can be used with gcc:
# CFLAGS = -fsanitize=address -static-libasan -g -std=c17 -Wall
CFLAGS = -g -std=c17 -Wall
YACC = bison
YACCFLAGS = -Wall --locations -d -v
LEX = flex
LEXFLAGS =
# Unix command names
MV = mv
RM = rm -f
SUBMISSIONZIPFILE = submission.zip
ZIP = zip -9
SPL = spl
SUF = spl
# The GTESTS are a graduated series of tests, good to start with
GTESTS = hw4-gtest0.spl hw4-gtest1.spl hw4-gtest2.spl hw4-gtest3.spl \
	 hw4-gtest5.spl hw4-gtest6.spl hw4-gtest7.spl hw4-gtest8.spl \
	 hw4-gtest9.spl hw4-gtestA.spl hw4-gtestB.spl hw4-gtestC.spl \
	 hw4-gtestD.spl hw4-gtestE.spl hw4-gtestF.spl hw4-gtestG.spl \
	 hw4-gtestH.spl hw4-gtestI.spl hw4-gtestJ.spl hw4-gtestK.spl \
	 hw4-gtestL.spl hw4-gtestM.spl hw4-gtestN.spl hw4-gtestO.spl \
	 hw4-gtestP.spl hw4-gtestQ.spl hw4-gtestR.spl hw4-gtestS.spl \
	 hw4-gtestT.spl
# The READTESTS need input from stdin
READTESTS = hw4-read-test0.spl hw4-read-test1.spl
# the VM tests are another set of tests that (somehwhat) increas in comlexity
VMTESTS = hw4-vmtest0.spl hw4-vmtest1.spl hw4-vmtest2.spl hw4-vmtest3.spl \
	hw4-vmtest4.spl hw4-vmtest5.spl hw4-vmtest6.spl hw4-vmtest7.spl \
	hw4-vmtest8.spl hw4-vmtest9.spl hw4-vmtestA.spl hw4-vmtestB.spl \
	hw4-vmtestC.spl
# you can add your own tests to alltests
ALLTESTS = $(GTESTS) $(READTESTS) $(VMTESTS)
EXPECTEDOUTPUTS = $(ALLTESTS:.spl=.out)
STUDENTTESTOUTPUTS = $(ALLTESTS:.spl=.myo)

# The macro PROCEDURE_OBJECTS would be used for modules that 
# implement procedures, which is not part of the homework
PROCEDURE_OBJECTS = 
# Add the names of your own files with a .o suffix to link them in the program
# Feel free to edit the following definition of COMPILER_OBJECTS
COMPILER_OBJECTS = $(COMPILER)_main.o $(SPL)_lexer.o lexer_utilities.o \
		machine_types.o parser.o regname.o utilities.o \
		$(SPL).tab.o ast.o file_location.o unparser.o \
		scope.o scope_check.o symtab.o id_use.o id_attrs.o \
		instruction.o bof.o code.o code_seq.o code_utils.o \
		gen_code.o literal_table.o $(PROCEDURE_OBJECTS)
# Note that you will need to write gen_code.o and literal_table.o,
# but you can change those names if you wish.

# create the VM executable
.PRECIOUS: $(VM)/$(VM)
$(VM): $(VM)/$(VM)

$(SPL).tab.o: $(SPL).tab.c $(SPL).tab.h
	$(CC) $(CFLAGS) -c $<

$(SPL).tab.c $(SPL).tab.h: $(SPL).y ast.h parser_types.h machine_types.h 
	$(YACC) $(YACCFLAGS) $(SPL).y

.PRECIOUS: $(SPL)_lexer.c
$(SPL)_lexer.c: $(SPL)_lexer.l $(SPL).tab.h
	$(LEX) $(LEXFLAGS) $<

$(SPL)_lexer.o: $(SPL)_lexer.c ast.h utilities.h file_location.h
	$(CC) $(CFLAGS) -Wno-unused-function -Wno-unused-but-set-variable -c $(SPL)_lexer.c

$(SPL)_lexer.l: $(SPL).tab.h

ast.o: spl.tab.h

# create the compiler executable
$(COMPILER): $(COMPILER_OBJECTS)
	$(CC) $(CFLAGS) -o $(COMPILER) $(COMPILER_OBJECTS)

$(COMPILER)_main.o: $(COMPILER)_main.c lexer.h parser.h unparser.h ast.h \
		utilities.h symtab.h scope_check.h
	$(CC) $(CFLAGS) -c $<

gen_code.o: gen_code.c spl.tab.h gen_code.h id_use.h literal_table.h \
		utilities.h regname.h
	$(CC) $(CFLAGS) -c $<

# rule for compiling individual .c files
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) *~ *.o '#'*
	$(RM) $(SPL)_lexer.c $(SPL)_lexer.h
	$(RM) $(SPL).tab.c $(SPL).tab.h $(SPL).output
	$(RM) $(COMPILER).exe $(COMPILER)
	$(RM) *.stackdump core
	$(RM) $(SUBMISSIONZIPFILE)
	cd $(VM); $(MAKE) clean

cleanall: clean
	$(RM) *.myo *.myt *.bof *.asm
	(cd $(VM); $(MAKE) cleanall)

$(RUNVM):
	(cd $(VM); $(MAKE) $(VM))

# The .myo files are outputs of VM when run on compiled programs.
# There is no tracing output by default for the .myo files,
# use .myt if you want tracing output.
# The pipe starting with "cat char-inputs.txt |"
# allows read statments to not hang
.PRECIOUS: %.myo
%.myo: %.bof $(RUNVM)
	$(RM) $@; umask 022; \
	cat char-inputs.txt | ./$(RUNVM) $< > $@ 2>&1

# A .myt file is the output of running the VM with the -t option
# This can be useful for debugging.
.PRECIOUS: %.myt
%.myt: %.bof $(RUNVM)
	$(RM) $@; umask 022; \
	cat char-inputs.txt | ./$(RUNVM) -t $< > $@ 2>&1

.PHONY: asm disasm
asm: $(ASM)
disasm: $(DISASM)

$(ASM):
	(cd $(VM); $(MAKE) asm)

$(DISASM):
	(cd $(VM); $(MAKE) disasm)

# The .bof files are the compiled binary object files.
.PRECIOUS: %.bof
%.bof: %.$(SUF) $(COMPILER)
	$(RM) $@; umask 022; \
	./$(COMPILER) $<

# The .upo files are unparsed programs;
# these are useful for debugging the parser and understanding the parse.
%.upo: %.$(SUF) $(COMPILER)
	$(RM) $@; umask 022; \
	./$(UNPARSER) $< > $@ 2>&1

# The .asm files are disassembled binary object files.
# These are useful for debugging the code the compiler creates.
%.asm: %.bof $(COMPILER) $(DISASM)
	$(RM) $@; umask 022; \
	$(DISASM) $< > $@ 2>&1

# main target for testing
.PHONY: check-outputs check-nonproc-outputs
check-outputs check-nonproc-outputs: $(COMPILER) $(RUNVM)
	@DIFFS=0; \
	for f in `echo $(ALLTESTS) | sed -e 's/\\.$(SUF)//g'`; \
	do \
		echo running ./$(COMPILER) on "$$f.$(SUF)"; \
		$(RM) "$$f.bof"; \
		./$(COMPILER) "$$f.$(SUF)" ; \
		echo running $(RUNVM) on "$$f.bof"; \
		$(RM) "$$f.myo"; \
		cat char-inputs.txt | $(RUNVM) "$$f.bof" > "$$f.myo" 2>&1; \
		diff -w -B "$$f.out" "$$f.myo" && echo 'passed!' || DIFFS=1; \
	done; \
	if test 0 = $$DIFFS; \
	then \
		echo 'All output tests passed!'; \
	else \
		echo 'Some output test(s) failed!'; \
	fi

$(SUBMISSIONZIPFILE): *.c *.h $(STUDENTTESTOUTPUTS)
	$(ZIP) $(SUBMISSIONZIPFILE) $(SPL).y $(SPL)_lexer.l *.c *.h Makefile
	$(ZIP) $(SUBMISSIONZIPFILE) $(STUDENTTESTOUTPUTS) $(ALLTESTS) $(EXPECTEDOUTPUTS) char-inputs.txt
	$(ZIP) -r -9 $(SUBMISSIONZIPFILE) $(VM) -x  'vm/*.o' 'vm/*.exe' 'vm/RCS/' 'vm/RCS/*,v'

.PHONY: compile-separately check-separately
compile-separately check-separately: $(COMPILER_OBJECTS)
