/* $Id: lexer_utilities.c,v 1.1 2023/11/13 18:26:52 leavens Exp $ */
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "lexer_utilities.h"

#define BUF_SIZE 1024

// Call yyerror to print an error message on stderr
// starting with the filename, ":", the lexer's current line number, ": ",
// and then the formatted message (as in sprintf)
extern void formatted_yyerror(const char *filename, const char *fmt, ...)
{
    fflush(stdout); // flush so output comes after what has happened already
    char buf[BUF_SIZE];
    va_list(args);
    va_start(args, fmt);
    vsnprintf(buf, BUF_SIZE, fmt, args);
    yyerror(filename, buf);
    va_end(args);
}
