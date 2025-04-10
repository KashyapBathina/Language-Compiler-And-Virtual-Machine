#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"
#include "ast.h"
#include "symtab.h"
#include "scope_check.h"
#include "utilities.h"
#include "unparser.h"

/* Print a usage message on stderr 
   and exit with failure. */
static void usage(const char *cmdname)
{
    fprintf(stderr,
	    "Usage: %s file.spl\n",
	    cmdname);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    const char *cmdname = argv[0];
    --argc;
    /* 1 non-option argument */
    if (argc != 1 || argv[1][0] == '-') {
	    usage(cmdname);
    }

    lexer_init(argv[1]);

    // parsing
    block_t progast = parseProgram(argv[1]);

    // unparse to check on the AST
    unparseProgram(stdout, progast);

    // comment out the next two commands to disable declaration checking
    // building symbol table
    
    symtab_initialize();
    
    // check for duplicate declarations
    scope_check_program(progast);
    
    return EXIT_SUCCESS;
}
