/* $Id: parser.h,v 1.4 2023/10/15 02:46:46 leavens Exp $ */
// This header file defines the externally-visible entry points to the parser
#ifndef _PARSER_H
#define _PARSER_H
#include "ast.h"

extern block_t progast;

// Parse a PL/0 program using the tokens from the lexer,
// returning the program's AST
extern block_t parseProgram(char const *file_name);

#endif
