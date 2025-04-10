// $Id: lexer_main.c,v 1.2 2023/09/06 22:43:06 leavens Exp $
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "parser_types.h"
#include "lexer.h"
#include "utilities.h"

void usage(const char *cmdname) {
    bail_with_error("Usage: %s file.asm", cmdname);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    const char *cmdname = argv[0];
    argc--;
    argv++;
    if (argc != 1 || argv[0][0] == '-') {
	// must be a file name and no options allowed!
	usage(cmdname);
    }

    lexer_init(argv[0]);
    lexer_output();
    return EXIT_SUCCESS;
}
