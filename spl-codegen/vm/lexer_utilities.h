/* $Id: lexer_utilities.h,v 1.1 2023/11/13 18:26:52 leavens Exp $ */
#ifndef _LEXER_UTILITIES_H
#define _LEXER_UTILITIES_H

// Report a syntax error on the current line on stderr.
// The output looks like: the filename, ":", the lexer's current line number,
// ": ", and then msg.
extern void yyerror(const char *filename, const char *msg);

// Call yyerror to print an error message on stderr
// starting with the filename, ":", the lexer's current line number, ": ",
// and then the formatted message (as in sprintf)
extern void formatted_yyerror(const char *filename, const char *fmt, ...);

#endif
