# $Id: Makefile,v 1.35 2024/10/06 19:39:56 leavens Exp leavens $
# Makefile for lexer in COP 3402

# Add .exe to the end of target to get that suffix in the rules
LEXER = lexer
CC = gcc
LEX = flex
LEXFLAGS =
# on Linux, the following can be used with gcc:
# CFLAGS = -fsanitize=address -static-libasan -g -std=c17 -Wall
CFLAGS = -g -std=c17 -Wall
# Other Unix command names
MV = mv
RM = rm -f
ZIP = zip -9
SPL = spl
# the zip file to submit on Webcourses
SUBMISSIONZIPFILE = submission.zip
# Add the names of your own files with a .o suffix to link them into the lexer
# Change the names in LEXER_OBJECTS (especially the first line)
# to match the object files your lexer actually needs or uses.
LEXER_OBJECTS = $(LEXER)_main.o \
                $(SPL)_lexer.o \
		$(SPL).tab.o $(LEXER).o ast.o machine_types.o \
		file_location.o utilities.o 

.DEFAULT: $(LEXER)

# create the lexer executable
$(LEXER) : $(LEXER_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: start-flex-file
start-flex-file:
	@if test -f $(SPL)_lexer.l; \
         then echo "$(SPL)_lexer.l already exists, not starting it!" >&2; \
              exit 2 ; \
         fi
	cat $(SPL)_lexer_definitions_top.l spl_lexer_user_code.c > $(SPL)_lexer.l

# some special rules for generated files
$(SPL)_lexer.c: $(SPL)_lexer.l
	$(LEX) $(LEXFLAGS) $<

$(LEXER).o: $(LEXER).c $(LEXER).h $(SPL).tab.h
	$(CC) $(CFLAGS) -c $<

$(SPL)_lexer.o: $(SPL)_lexer.c ast.h $(SPL).tab.h utilities.h file_location.h
	$(CC) $(CFLAGS) -Wno-unused-but-set-variable -Wno-unused-function -c $<

TESTS = hw2-test0.spl hw2-test1.spl hw2-test2.spl hw2-test3.spl \
	hw2-test4.spl hw2-test5.spl hw2-test6.spl hw2-test7.spl hw2-test8.spl

ERRTESTS = hw2-errtest0.spl hw2-errtest1.spl hw2-errtest2.spl \
	  hw2-errtest3.spl hw2-errtest4.spl hw2-errtest5.spl hw2-errtest6.spl

ALLTESTS = $(TESTS) $(ERRTESTS)
EXPECTEDOUTPUTS = $(ALLTESTS:.spl=.out)

# STUDENTESTOUTPUTS is all of the .myo files corresponding to the tests
# if you add more tests, you can add more to this list,
# or just add to TESTS above
STUDENTTESTOUTPUTS = $(ALLTESTS:.spl=.myo)

# rule for compiling individual .c files
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) *~ '#'* *.stackdump core
	$(RM) *.o *.myo $(LEXER).exe $(LEXER)
	$(RM) $(SUBMISSIONZIPFILE)

# Rules for making individual outputs (e.g., execute make hw2-test1.myo)
# the .myo files are outputs from running the lexer on the .spl files
.PRECIOUS: %.myo
%.myo: %.spl $(LEXER)
	- ./$(LEXER) $< > $@ 2>&1

# main target for testing
.PHONY: check-outputs
check-outputs: $(LEXER) $(ALLTESTS)
	@DIFFS=0; \
	for f in `echo $(ALLTESTS) | sed -e 's/\\.spl//g'`; \
	do \
		echo running lexer on "$$f.spl" ...; \
		./lexer "$$f.spl" > "$$f.myo" 2>&1; \
		diff -w -B "$$f.out" "$$f.myo" && echo 'passed!' \
			|| { echo 'failed!'; DIFFS=1; }; \
	done; \
	if test 0 = $$DIFFS; \
	then \
		echo 'All lexer tests passed!'; \
	else \
		echo 'Some lexer test(s) failed!'; \
	fi

# Automatically generate the submission zip file
$(SUBMISSIONZIPFILE): *.c *.h $(STUDENTTESTOUTPUTS) Makefile 
	$(ZIP) $@ $^ spl.y spl_lexer.l Makefile $(EXPECTEDOUTPUTS) $(ALLTESTS)

.PHONY: compile-separately check-separately
compile-separately check-separately:
	@for f in `ls *.c | grep -v spl_lexer_user_code.c` ; \
	do echo $(CC) $(CFLAGS) -c $$f ; \
	   $(CC) $(CFLAGS) -c $$f ; \
	done
