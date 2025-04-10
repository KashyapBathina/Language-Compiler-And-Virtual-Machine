/* $Id: parser_types.h,v 1.1 2023/10/13 12:15:32 leavens Exp $ */
#ifndef _PARSER_TYPES_H
#define _PARSER_TYPES_H

#include "ast.h"

// The type of Bison's parser stack elements (parse values)
typedef AST YYSTYPE;
#define YYSTYPE_IS_DECLARED 1

#endif
