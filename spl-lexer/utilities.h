/* $Id: utilities.h,v 1.4 2024/10/06 01:07:29 leavens Exp $ */
#ifndef _UTILITIES_H
#define _UTILITIES_H
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "file_location.h"

// Report a syntax error on the current line on stderr.
// The output looks like: the filename, ":", the lexer's current line number,
// ": ", and then msg.
extern void yyerror(const char *filename, const char *msg);

#define MAX(x,y) (((x)>(y))?(x):(y))

// If NDEBUG is defined, do nothing, otherwise (when debugging)
// flush stderr and stdout, then print the message given on stderr,
// using printf formatting from the format string fmt.
// This function returns normally.
void debug_print(const char *fmt, ...);

// Format a string error message and print it using perror (for an OS error)
// then exit with a failure code, so a call to this does not return.
extern void bail_with_error(const char *fmt, ...);

// Print an error message on stderr
// starting with the file name and line number from the floc argument
// (prints: filename, a colon, " line ", the line number, and a space)
// and then the message.
// Then exit with a failure code, so this function does not return.
extern void bail_with_prog_error(file_location floc, const char *fmt, ...);

// Call yyerror to print an error message on stderr
// starting with the filename, ":", the lexer's current line number, ": ",
// and then the formatted message (as in sprintf)
extern void formatted_yyerror(const char *filename, const char *fmt, ...);

// print a newline on out and flush out
extern void newline(FILE *out);

#endif
