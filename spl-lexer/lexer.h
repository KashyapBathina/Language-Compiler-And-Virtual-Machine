/* $Id: lexer.h,v 1.7 2024/10/06 01:32:57 leavens Exp $ */
#ifndef _LEXER_H
#define _LEXER_H
#include <stdbool.h>

// Requires: fname != NULL
// Requires: fname is the name of a readable file
// Initialize the lexer and start it reading
// from the given file name
extern void lexer_init(char *fname);

// Return the next token in the input
extern int yylex();

// Return the name of the current file
extern const char *lexer_filename();

// Return the line number of the next token
extern unsigned int lexer_line();

// On standard output:
// Print a message about the file name of the lexer's input
// and then print a heading for the lexer's output.
extern void lexer_print_output_header();

// Have any errors been noted by the lexer?
extern bool lexer_has_errors();

// Print information about the token t to stdout
// followed by a newline
extern void lexer_print_token(int t, unsigned int tline,
			      const char *txt);

/* Read all the tokens from the input file
 * and print each token on standard output
 * using the format in lexer_print_token */
extern void lexer_output();

#endif
