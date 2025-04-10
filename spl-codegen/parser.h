/* $Id: parser.h,v 1.3 2023/11/13 14:08:44 leavens Exp $ */
// This header file defines the externally-visible entry points to the parser
#ifndef _PARSER_H
#define _PARSER_H
#include "ast.h"

extern block_t progast;

// Parse a PL/0 program using the tokens from the lexer,
// returning the program's AST
extern block_t parseProgram(char *file_name);

#endif
