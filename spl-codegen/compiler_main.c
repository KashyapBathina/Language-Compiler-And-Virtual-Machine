/* $Id: compiler_main.c,v 1.18 2024/11/13 20:33:01 leavens Exp $ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bof.h"
#include "lexer.h"
#include "parser.h"
#include "unparser.h"
#include "ast.h"
#include "utilities.h"
#include "symtab.h"
#include "scope_check.h"

// The functions gen_code_initialize and gen_code_program
// would normally be declared in gen_code.h,
// but part of the homework is to write that gen_code module,
// so they are declared below to make this file self-contained.

// Initialize the code generator
extern void gen_code_initialize();

// Requires: bf is open for writing
// Generate code for prog into bf
extern void gen_code_program(BOFFILE bf, block_t prog);

/* Print a usage message on stderr 
   and exit with failure. */
static void usage(const char *cmdname)
{
    fprintf(stderr, "Usage: %s %s\n       %s %s\n       %s %s\n",
	    cmdname, "-l codeFilename.spl",
	    cmdname, "-u codeFilename.spl",
	    cmdname, " codeFilename.spl"
	    );
    exit(EXIT_FAILURE);
}

// If the -l option is used, then output the tokens
// in the give file name to stdout,
// otherwise unparse the program given in the file name argument to stdout
int main(int argc, char *argv[])
{
    // should the lexer's tokens be shown?
    bool lexer_print_output = false;
    // should the unparse of the AST be shown?
    bool parser_unparse = false;
    const char *cmdname = argv[0];
    argc--;
    argv++;
    // possible options: -l, and -u
    while (argc > 0 && strlen(argv[0]) >= 2 && argv[0][0] == '-') {
	if (strcmp(argv[0],"-l") == 0) {
	    lexer_print_output = true;
	    argc--;
	    argv++;
	} else if (strcmp(argv[0],"-u") == 0) {
	    parser_unparse = true;
	    argc--;
	    argv++;
	} else {
	    // bad option!
	    usage(cmdname);
	}
    }

    // give usage message if -l and other options are used
    if (lexer_print_output && parser_unparse) {
	usage(cmdname);
    }

    // must have a file name
    if (argc <= 0 || (strlen(argv[0]) >= 2 && argv[0][0] == '-')) {
	usage(cmdname);
    }

    // the name of the file
    char *filename = argv[0];
    char *lastdot = strrchr(filename, '.');
    if (lastdot == NULL || strcmp(lastdot, ".spl") != 0) {
	bail_with_error("filename argument must end in .spl not %s",
			filename);
    }
    char boffilename[BUFSIZ];
    strncpy(boffilename, filename, BUFSIZ);
    int len = strlen(boffilename);
    assert(len < BUFSIZ);  // it has to fit!
    strncpy(boffilename+(len-4), ".bof", 5);
    // debug_print("Output going to %s\n", boffilename);

    if (lexer_print_output) {
	// with the lexer_print_output option, nothing else is done
	lexer_init(filename);
	lexer_output();
	return EXIT_SUCCESS;
    }

    // otherwise (if not lexer_print_outout) continue to parse etc.
    block_t progast = parseProgram(filename);

    if (parser_unparse) {
	unparseProgram(stdout, progast);
    }

    // build symbol table and...
    symtab_initialize();
    // check for duplicate declarations
    // and record id-use information in the AST
    scope_check_program(&progast);

    if (parser_unparse) {
	return EXIT_SUCCESS;
    }

    // generate code from the ASTs
    gen_code_initialize();
    BOFFILE bf = bof_write_open(boffilename);
    gen_code_program(bf, progast);

    return EXIT_SUCCESS;
}
