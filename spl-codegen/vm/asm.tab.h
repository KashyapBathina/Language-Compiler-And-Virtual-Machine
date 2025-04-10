/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_ASM_TAB_H_INCLUDED
# define YY_YY_ASM_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 7 "asm.y"


 /* Including "ast.h" must be at the top, to define the AST type */
#include "ast.h"
#include "machine_types.h"
#include "parser_types.h"
#include "lexer.h"
// #include "utilities.h" // only needed for debugging

    /* Report an error to the user on stderr */
extern void yyerror(const char *filename, const char *msg);

#line 62 "asm.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    eolsym = 258,                  /* eolsym  */
    identsym = 259,                /* identsym  */
    unsignednumsym = 260,          /* unsignednumsym  */
    plussym = 261,                 /* "+"  */
    minussym = 262,                /* "-"  */
    commasym = 263,                /* ","  */
    dottextsym = 264,              /* ".text"  */
    dotdatasym = 265,              /* ".data"  */
    dotstacksym = 266,             /* ".stack"  */
    dotendsym = 267,               /* ".end"  */
    colonsym = 268,                /* ":"  */
    lbracketsym = 269,             /* "["  */
    rbracketsym = 270,             /* "]"  */
    equalsym = 271,                /* "="  */
    noopsym = 272,                 /* "NOP"  */
    addopsym = 273,                /* "ADD"  */
    subopsym = 274,                /* "SUB"  */
    cpwopsym = 275,                /* "CPW"  */
    cpropsym = 276,                /* "CPR"  */
    andopsym = 277,                /* "AND"  */
    boropsym = 278,                /* "BOR"  */
    noropsym = 279,                /* "NOR"  */
    xoropsym = 280,                /* "XOR"  */
    lwropsym = 281,                /* "LWR"  */
    swropsym = 282,                /* "SWR"  */
    scaopsym = 283,                /* "SCA"  */
    lwiopsym = 284,                /* "LWI"  */
    negopsym = 285,                /* "NEG"  */
    litopsym = 286,                /* "LIT"  */
    ariopsym = 287,                /* "ARI"  */
    sriopsym = 288,                /* "SRI"  */
    mulopsym = 289,                /* "MUL"  */
    divopsym = 290,                /* "DIV"  */
    cfhiopsym = 291,               /* "CFHI"  */
    cfloopsym = 292,               /* "CFLO"  */
    sllopsym = 293,                /* "SLL"  */
    srlopsym = 294,                /* "SRL"  */
    jmpopsym = 295,                /* "JMP"  */
    jrelopsym = 296,               /* "JREL"  */
    addiopsym = 297,               /* "ADDI"  */
    andiopsym = 298,               /* "ANDI"  */
    boriopsym = 299,               /* "BORI"  */
    noriopsym = 300,               /* "NORI"  */
    xoriopsym = 301,               /* "XORI"  */
    beqopsym = 302,                /* "BEQ"  */
    bgezopsym = 303,               /* "BGEZ"  */
    blezopsym = 304,               /* "BLEZ"  */
    bgtzopsym = 305,               /* "BGTZ"  */
    bltzopsym = 306,               /* "BLTZ"  */
    bneopsym = 307,                /* "BNE"  */
    csiopsym = 308,                /* "CSI"  */
    jmpaopsym = 309,               /* "JMPA"  */
    callopsym = 310,               /* "CALL"  */
    rtnopsym = 311,                /* "RTN"  */
    exitopsym = 312,               /* "EXIT"  */
    pstropsym = 313,               /* "PSTR"  */
    pintopsym = 314,               /* "PINT"  */
    pchopsym = 315,                /* "PCH"  */
    rchopsym = 316,                /* "RCH"  */
    straopsym = 317,               /* "STRA"  */
    notropsym = 318,               /* "NOTR"  */
    regsym = 319,                  /* regsym  */
    wordsym = 320,                 /* "WORD"  */
    charsym = 321,                 /* "CHAR"  */
    stringsym = 322,               /* "STRING"  */
    charliteralsym = 323,          /* charliteralsym  */
    stringliteralsym = 324         /* stringliteralsym  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (char const *file_name);


#endif /* !YY_YY_ASM_TAB_H_INCLUDED  */
