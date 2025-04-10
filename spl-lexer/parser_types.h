/* $Id: parser_types.h,v 1.1 2023/10/04 03:43:15 leavens Exp $ */
#ifndef _PARSER_TYPES_H
#define _PARSER_TYPES_H

#include "ast.h"

// The type of Bison's parser stack elements (parse values)
typedef AST YYSTYPE;
#define YYSTYPE_IS_DECLARED 1

#endif
