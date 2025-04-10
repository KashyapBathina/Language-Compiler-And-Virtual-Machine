/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
#line 3 "asm.y"

#include <stdio.h>

#line 72 "asm.tab.c"




# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "asm.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_eolsym = 3,                     /* eolsym  */
  YYSYMBOL_identsym = 4,                   /* identsym  */
  YYSYMBOL_unsignednumsym = 5,             /* unsignednumsym  */
  YYSYMBOL_plussym = 6,                    /* "+"  */
  YYSYMBOL_minussym = 7,                   /* "-"  */
  YYSYMBOL_commasym = 8,                   /* ","  */
  YYSYMBOL_dottextsym = 9,                 /* ".text"  */
  YYSYMBOL_dotdatasym = 10,                /* ".data"  */
  YYSYMBOL_dotstacksym = 11,               /* ".stack"  */
  YYSYMBOL_dotendsym = 12,                 /* ".end"  */
  YYSYMBOL_colonsym = 13,                  /* ":"  */
  YYSYMBOL_lbracketsym = 14,               /* "["  */
  YYSYMBOL_rbracketsym = 15,               /* "]"  */
  YYSYMBOL_equalsym = 16,                  /* "="  */
  YYSYMBOL_noopsym = 17,                   /* "NOP"  */
  YYSYMBOL_addopsym = 18,                  /* "ADD"  */
  YYSYMBOL_subopsym = 19,                  /* "SUB"  */
  YYSYMBOL_cpwopsym = 20,                  /* "CPW"  */
  YYSYMBOL_cpropsym = 21,                  /* "CPR"  */
  YYSYMBOL_andopsym = 22,                  /* "AND"  */
  YYSYMBOL_boropsym = 23,                  /* "BOR"  */
  YYSYMBOL_noropsym = 24,                  /* "NOR"  */
  YYSYMBOL_xoropsym = 25,                  /* "XOR"  */
  YYSYMBOL_lwropsym = 26,                  /* "LWR"  */
  YYSYMBOL_swropsym = 27,                  /* "SWR"  */
  YYSYMBOL_scaopsym = 28,                  /* "SCA"  */
  YYSYMBOL_lwiopsym = 29,                  /* "LWI"  */
  YYSYMBOL_negopsym = 30,                  /* "NEG"  */
  YYSYMBOL_litopsym = 31,                  /* "LIT"  */
  YYSYMBOL_ariopsym = 32,                  /* "ARI"  */
  YYSYMBOL_sriopsym = 33,                  /* "SRI"  */
  YYSYMBOL_mulopsym = 34,                  /* "MUL"  */
  YYSYMBOL_divopsym = 35,                  /* "DIV"  */
  YYSYMBOL_cfhiopsym = 36,                 /* "CFHI"  */
  YYSYMBOL_cfloopsym = 37,                 /* "CFLO"  */
  YYSYMBOL_sllopsym = 38,                  /* "SLL"  */
  YYSYMBOL_srlopsym = 39,                  /* "SRL"  */
  YYSYMBOL_jmpopsym = 40,                  /* "JMP"  */
  YYSYMBOL_jrelopsym = 41,                 /* "JREL"  */
  YYSYMBOL_addiopsym = 42,                 /* "ADDI"  */
  YYSYMBOL_andiopsym = 43,                 /* "ANDI"  */
  YYSYMBOL_boriopsym = 44,                 /* "BORI"  */
  YYSYMBOL_noriopsym = 45,                 /* "NORI"  */
  YYSYMBOL_xoriopsym = 46,                 /* "XORI"  */
  YYSYMBOL_beqopsym = 47,                  /* "BEQ"  */
  YYSYMBOL_bgezopsym = 48,                 /* "BGEZ"  */
  YYSYMBOL_blezopsym = 49,                 /* "BLEZ"  */
  YYSYMBOL_bgtzopsym = 50,                 /* "BGTZ"  */
  YYSYMBOL_bltzopsym = 51,                 /* "BLTZ"  */
  YYSYMBOL_bneopsym = 52,                  /* "BNE"  */
  YYSYMBOL_csiopsym = 53,                  /* "CSI"  */
  YYSYMBOL_jmpaopsym = 54,                 /* "JMPA"  */
  YYSYMBOL_callopsym = 55,                 /* "CALL"  */
  YYSYMBOL_rtnopsym = 56,                  /* "RTN"  */
  YYSYMBOL_exitopsym = 57,                 /* "EXIT"  */
  YYSYMBOL_pstropsym = 58,                 /* "PSTR"  */
  YYSYMBOL_pintopsym = 59,                 /* "PINT"  */
  YYSYMBOL_pchopsym = 60,                  /* "PCH"  */
  YYSYMBOL_rchopsym = 61,                  /* "RCH"  */
  YYSYMBOL_straopsym = 62,                 /* "STRA"  */
  YYSYMBOL_notropsym = 63,                 /* "NOTR"  */
  YYSYMBOL_regsym = 64,                    /* regsym  */
  YYSYMBOL_wordsym = 65,                   /* "WORD"  */
  YYSYMBOL_charsym = 66,                   /* "CHAR"  */
  YYSYMBOL_stringsym = 67,                 /* "STRING"  */
  YYSYMBOL_charliteralsym = 68,            /* charliteralsym  */
  YYSYMBOL_stringliteralsym = 69,          /* stringliteralsym  */
  YYSYMBOL_YYACCEPT = 70,                  /* $accept  */
  YYSYMBOL_program = 71,                   /* program  */
  YYSYMBOL_textSection = 72,               /* textSection  */
  YYSYMBOL_entryPoint = 73,                /* entryPoint  */
  YYSYMBOL_addr = 74,                      /* addr  */
  YYSYMBOL_label = 75,                     /* label  */
  YYSYMBOL_asmInstrs = 76,                 /* asmInstrs  */
  YYSYMBOL_asmInstr = 77,                  /* asmInstr  */
  YYSYMBOL_labelOpt = 78,                  /* labelOpt  */
  YYSYMBOL_empty = 79,                     /* empty  */
  YYSYMBOL_instr = 80,                     /* instr  */
  YYSYMBOL_noArgInstr = 81,                /* noArgInstr  */
  YYSYMBOL_noArgOp = 82,                   /* noArgOp  */
  YYSYMBOL_twoRegCompInstr = 83,           /* twoRegCompInstr  */
  YYSYMBOL_twoRegCompOp = 84,              /* twoRegCompOp  */
  YYSYMBOL_offset = 85,                    /* offset  */
  YYSYMBOL_number = 86,                    /* number  */
  YYSYMBOL_sign = 87,                      /* sign  */
  YYSYMBOL_twoRegNoOffsetsInstr = 88,      /* twoRegNoOffsetsInstr  */
  YYSYMBOL_twoRegNoOffsetsOp = 89,         /* twoRegNoOffsetsOp  */
  YYSYMBOL_noTargetOffsetInstr = 90,       /* noTargetOffsetInstr  */
  YYSYMBOL_noTargetOffsetOp = 91,          /* noTargetOffsetOp  */
  YYSYMBOL_noSourceOffsetInstr = 92,       /* noSourceOffsetInstr  */
  YYSYMBOL_noSourceOffsetOp = 93,          /* noSourceOffsetOp  */
  YYSYMBOL_oneRegOffsetArgInstr = 94,      /* oneRegOffsetArgInstr  */
  YYSYMBOL_oneRegOffsetArgOp = 95,         /* oneRegOffsetArgOp  */
  YYSYMBOL_arg = 96,                       /* arg  */
  YYSYMBOL_oneRegArgInstr = 97,            /* oneRegArgInstr  */
  YYSYMBOL_oneRegArgOp = 98,               /* oneRegArgOp  */
  YYSYMBOL_oneRegOffsetInstr = 99,         /* oneRegOffsetInstr  */
  YYSYMBOL_oneRegOffsetOp = 100,           /* oneRegOffsetOp  */
  YYSYMBOL_shiftInstr = 101,               /* shiftInstr  */
  YYSYMBOL_shiftOp = 102,                  /* shiftOp  */
  YYSYMBOL_shift = 103,                    /* shift  */
  YYSYMBOL_argOnlyInstr = 104,             /* argOnlyInstr  */
  YYSYMBOL_argOnlyOp = 105,                /* argOnlyOp  */
  YYSYMBOL_immedArithInstr = 106,          /* immedArithInstr  */
  YYSYMBOL_immedArithOp = 107,             /* immedArithOp  */
  YYSYMBOL_immed = 108,                    /* immed  */
  YYSYMBOL_immedBoolInstr = 109,           /* immedBoolInstr  */
  YYSYMBOL_immedBoolOp = 110,              /* immedBoolOp  */
  YYSYMBOL_uimmed = 111,                   /* uimmed  */
  YYSYMBOL_branchTestInstr = 112,          /* branchTestInstr  */
  YYSYMBOL_branchTestOp = 113,             /* branchTestOp  */
  YYSYMBOL_jumpInstr = 114,                /* jumpInstr  */
  YYSYMBOL_jumpOp = 115,                   /* jumpOp  */
  YYSYMBOL_syscallInstr = 116,             /* syscallInstr  */
  YYSYMBOL_offsetOnlySyscall = 117,        /* offsetOnlySyscall  */
  YYSYMBOL_offsetOnlySyscallOp = 118,      /* offsetOnlySyscallOp  */
  YYSYMBOL_regOffsetSyscall = 119,         /* regOffsetSyscall  */
  YYSYMBOL_regOffsetSyscallOp = 120,       /* regOffsetSyscallOp  */
  YYSYMBOL_noArgSyscall = 121,             /* noArgSyscall  */
  YYSYMBOL_noArgSyscallOp = 122,           /* noArgSyscallOp  */
  YYSYMBOL_dataSection = 123,              /* dataSection  */
  YYSYMBOL_staticStartAddr = 124,          /* staticStartAddr  */
  YYSYMBOL_staticDecls = 125,              /* staticDecls  */
  YYSYMBOL_staticDecl = 126,               /* staticDecl  */
  YYSYMBOL_dataSize = 127,                 /* dataSize  */
  YYSYMBOL_initializerOpt = 128,           /* initializerOpt  */
  YYSYMBOL_stackSection = 129,             /* stackSection  */
  YYSYMBOL_stackBottomAddr = 130           /* stackBottomAddr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;



/* Unqualified %code blocks.  */
#line 160 "asm.y"

 /* extern declarations provided by the lexer */
extern int yylex(void);

 /* extern void yyerror(char const *msg); */

 /* The AST for the program, set by the semantic action for program. */
ast_program_t progast; 

 /* Set the program's ast to be t */
extern void setProgAST(ast_program_t t);

#line 253 "asm.tab.c"

#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
# define YYCOPY_NEEDED 1
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   146

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  118
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  195

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   324


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   175,   175,   178,   182,   184,   185,   188,   191,   192,
     195,   197,   198,   201,   204,   204,   204,   205,   205,   205,
     206,   206,   206,   206,   207,   207,   207,   207,   208,   212,
     214,   214,   217,   225,   225,   225,   226,   226,   226,   226,
     226,   226,   226,   229,   236,   246,   246,   247,   251,   258,
     261,   268,   271,   278,   281,   290,   292,   300,   309,   309,
     312,   321,   321,   321,   321,   321,   321,   324,   333,   333,
     335,   343,   351,   354,   362,   364,   372,   380,   380,   380,
     380,   382,   390,   398,   398,   398,   398,   398,   398,   401,
     412,   412,   415,   415,   415,   417,   425,   428,   436,   436,
     436,   436,   439,   447,   447,   451,   455,   458,   459,   462,
     465,   466,   467,   472,   473,   475,   477,   481,   484
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "eolsym", "identsym",
  "unsignednumsym", "+", "-", ",", ".text", ".data", ".stack", ".end", ":",
  "[", "]", "=", "NOP", "ADD", "SUB", "CPW", "CPR", "AND", "BOR", "NOR",
  "XOR", "LWR", "SWR", "SCA", "LWI", "NEG", "LIT", "ARI", "SRI", "MUL",
  "DIV", "CFHI", "CFLO", "SLL", "SRL", "JMP", "JREL", "ADDI", "ANDI",
  "BORI", "NORI", "XORI", "BEQ", "BGEZ", "BLEZ", "BGTZ", "BLTZ", "BNE",
  "CSI", "JMPA", "CALL", "RTN", "EXIT", "PSTR", "PINT", "PCH", "RCH",
  "STRA", "NOTR", "regsym", "WORD", "CHAR", "STRING", "charliteralsym",
  "stringliteralsym", "$accept", "program", "textSection", "entryPoint",
  "addr", "label", "asmInstrs", "asmInstr", "labelOpt", "empty", "instr",
  "noArgInstr", "noArgOp", "twoRegCompInstr", "twoRegCompOp", "offset",
  "number", "sign", "twoRegNoOffsetsInstr", "twoRegNoOffsetsOp",
  "noTargetOffsetInstr", "noTargetOffsetOp", "noSourceOffsetInstr",
  "noSourceOffsetOp", "oneRegOffsetArgInstr", "oneRegOffsetArgOp", "arg",
  "oneRegArgInstr", "oneRegArgOp", "oneRegOffsetInstr", "oneRegOffsetOp",
  "shiftInstr", "shiftOp", "shift", "argOnlyInstr", "argOnlyOp",
  "immedArithInstr", "immedArithOp", "immed", "immedBoolInstr",
  "immedBoolOp", "uimmed", "branchTestInstr", "branchTestOp", "jumpInstr",
  "jumpOp", "syscallInstr", "offsetOnlySyscall", "offsetOnlySyscallOp",
  "regOffsetSyscall", "regOffsetSyscallOp", "noArgSyscall",
  "noArgSyscallOp", "dataSection", "staticStartAddr", "staticDecls",
  "staticDecl", "dataSize", "initializerOpt", "stackSection",
  "stackBottomAddr", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#define YYPACT_NINF (-140)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-4)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      10,     4,     5,    19,  -140,  -140,    26,  -140,  -140,  -140,
      27,    20,    22,     6,  -140,    71,  -140,  -140,  -140,    29,
      24,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,
      34,  -140,  -140,  -140,   -26,  -140,   -25,  -140,   -24,  -140,
     -23,  -140,   -22,  -140,   -20,  -140,   -19,  -140,   -18,  -140,
      21,  -140,   -17,  -140,   -16,  -140,   -15,  -140,     4,  -140,
    -140,    21,  -140,   -14,  -140,  -140,  -140,   -41,  -140,  -140,
    -140,  -140,    43,    44,    45,    47,    48,    49,    50,    51,
    -140,  -140,  -140,  -140,    55,  -140,    53,    54,    59,  -140,
    -140,  -140,    60,  -140,  -140,    56,  -140,    65,    21,    -1,
       7,    21,    21,    21,    21,    21,  -140,    21,    21,    21,
      21,    67,    57,    66,  -140,    68,    70,    72,  -140,  -140,
      73,    74,    76,    78,  -140,    64,    -4,  -140,   132,    11,
      21,    75,    21,   131,    21,   133,    21,  -140,  -140,  -140,
    -140,  -140,   129,  -140,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,    21,  -140
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     7,     6,    13,     4,     5,     1,
       0,     0,     0,    13,     8,     0,    12,   106,    13,     0,
       0,    11,     9,    30,    33,    34,    35,    49,    36,    37,
      38,    39,    51,    53,    40,    41,    42,    55,    58,    59,
      61,    62,    63,    64,    68,    69,    65,    72,    74,    77,
      78,    80,    79,    83,    84,    86,    85,    87,    88,    66,
      90,    91,    31,    96,    98,    99,   100,   101,   103,   104,
       0,    14,    29,    15,     0,    16,     0,    17,     0,    18,
       0,    19,     0,    20,     0,    21,     0,    22,     0,    23,
      13,    24,     0,    25,     0,    26,     0,    27,     0,    28,
      92,    13,    93,     0,    94,   102,   107,   105,   118,   117,
       2,    10,     0,     0,     0,     0,     0,     0,     0,     0,
      45,    46,    47,    56,     0,    71,     0,     0,     0,    89,
      95,    43,     0,   110,   111,     0,   108,     0,    13,     0,
       0,    13,    13,    13,    13,    13,    44,    13,    13,    13,
      13,     0,    13,     0,    48,     0,     0,     0,    57,    60,
       0,     0,     0,     0,    97,     0,    13,   116,     0,     0,
      13,     0,    13,     0,    13,     0,    13,   112,   114,   115,
     113,   109,     0,    50,    52,    54,    70,    67,    75,    73,
      81,    76,    82,    13,    32
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -140,  -140,  -140,  -140,    42,     0,  -140,   128,  -140,    -6,
    -140,  -140,  -140,  -140,  -140,  -127,   -89,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -139,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,   -34,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,
    -140
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     6,     7,     8,    13,    14,    15,   122,
      70,    71,    72,    73,    74,   130,   131,   124,    75,    76,
      77,    78,    79,    80,    81,    82,   125,    83,    84,    85,
      86,    87,    88,   187,    89,    90,    91,    92,   189,    93,
      94,   191,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,    11,    18,   107,   136,   137,   168,    20,
     109
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      16,   123,   120,   121,   158,     9,    12,    16,     4,     5,
       4,   153,   106,    12,   156,   157,    -3,   159,   160,     1,
     161,   162,   163,   164,   133,   134,   135,   120,   121,    10,
       4,    19,    17,   185,   108,    21,   110,   111,   112,   113,
     114,   115,   116,   183,   117,   118,   119,   126,   127,   128,
     132,   138,   139,   140,   123,   141,   142,   143,   144,   145,
     146,   147,   148,   154,   178,   179,   194,   149,   150,   152,
     151,   155,   165,   166,   169,   182,   170,   180,   171,   177,
     172,   173,   174,   123,   175,   188,   176,   188,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,   181,   186,   193,   190,   184,
     129,    22,   192,     0,     0,     0,   167
};

static const yytype_int16 yycheck[] =
{
       6,    90,     6,     7,   143,     0,     6,    13,     4,     5,
       4,   138,    18,    13,   141,   142,    10,   144,   145,     9,
     147,   148,   149,   150,    65,    66,    67,     6,     7,    10,
       4,    11,     5,   172,     5,    13,    12,     3,    64,    64,
      64,    64,    64,   170,    64,    64,    64,    64,    64,    64,
      64,     8,     8,     8,   143,     8,     8,     8,     8,     8,
       5,     8,     8,    64,    68,    69,   193,     8,     8,     4,
      14,    64,     5,    16,     8,    64,     8,   166,     8,    15,
       8,     8,     8,   172,     8,   174,     8,   176,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,     3,     5,     8,     5,    64,
      98,    13,   176,    -1,    -1,    -1,   152
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    71,    72,     4,     5,    73,    74,    75,     0,
      10,   123,    75,    76,    77,    78,    79,     5,   124,    11,
     129,    13,    77,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      80,    81,    82,    83,    84,    88,    89,    90,    91,    92,
      93,    94,    95,    97,    98,    99,   100,   101,   102,   104,
     105,   106,   107,   109,   110,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,    79,   125,     5,   130,
      12,     3,    64,    64,    64,    64,    64,    64,    64,    64,
       6,     7,    79,    86,    87,    96,    64,    64,    64,    74,
      85,    86,    64,    65,    66,    67,   126,   127,     8,     8,
       8,     8,     8,     8,     8,     8,     5,     8,     8,     8,
       8,    14,     4,    85,    64,    64,    85,    85,    96,    85,
      85,    85,    85,    85,    85,     5,    16,    79,   128,     8,
       8,     8,     8,     8,     8,     8,     8,    15,    68,    69,
      86,     3,    64,    85,    64,    96,     5,   103,    86,   108,
       5,   111,   108,     8,    85
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    70,    71,    72,    73,    74,    74,    75,    76,    76,
      77,    78,    78,    79,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    81,
      82,    82,    83,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    85,    86,    87,    87,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    98,
      99,   100,   100,   100,   100,   100,   100,   101,   102,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   110,   110,
     110,   111,   112,   113,   113,   113,   113,   113,   113,   114,
     115,   115,   116,   116,   116,   117,   118,   119,   120,   120,
     120,   120,   121,   122,   122,   123,   124,   125,   125,   126,
     127,   127,   127,   128,   128,   128,   128,   129,   130
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     3,     1,     1,     1,     1,     1,     2,
       3,     2,     1,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     8,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     4,     1,
       6,     1,     6,     1,     6,     1,     1,     4,     1,     1,
       4,     1,     1,     1,     1,     1,     1,     6,     1,     1,
       1,     2,     1,     6,     1,     1,     6,     1,     1,     1,
       1,     1,     6,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     2,     1,     4,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     2,     4,
       1,     1,     4,     2,     2,     2,     1,     2,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        YY_LAC_DISCARD ("YYBACKUP");                              \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (file_name, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, file_name); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, char const *file_name)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (file_name);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, char const *file_name)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, file_name);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, char const *file_name)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), file_name);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, file_name); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Given a state stack such that *YYBOTTOM is its bottom, such that
   *YYTOP is either its top or is YYTOP_EMPTY to indicate an empty
   stack, and such that *YYCAPACITY is the maximum number of elements it
   can hold without a reallocation, make sure there is enough room to
   store YYADD more elements.  If not, allocate a new stack using
   YYSTACK_ALLOC, copy the existing elements, and adjust *YYBOTTOM,
   *YYTOP, and *YYCAPACITY to reflect the new capacity and memory
   location.  If *YYBOTTOM != YYBOTTOM_NO_FREE, then free the old stack
   using YYSTACK_FREE.  Return 0 if successful or if no reallocation is
   required.  Return YYENOMEM if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYPTRDIFF_T *yycapacity, YYPTRDIFF_T yyadd,
#if YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yy_state_t **yybottom,
                      yy_state_t *yybottom_no_free,
                      yy_state_t **yytop, yy_state_t *yytop_empty)
{
  YYPTRDIFF_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYPTRDIFF_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYPTRDIFF_T yyalloc = 2 * yysize_new;
      yy_state_t *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return YYENOMEM;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        YY_CAST (yy_state_t *,
                 YYSTACK_ALLOC (YY_CAST (YYSIZE_T,
                                         yyalloc * YYSIZEOF (*yybottom_new))));
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return YYENOMEM;
        }
      if (*yytop != yytop_empty)
        {
          YYCOPY (yybottom_new, *yybottom, yysize_old);
          *yytop = yybottom_new + (yysize_old - 1);
        }
      if (*yybottom != yybottom_no_free)
        YYSTACK_FREE (*yybottom);
      *yybottom = yybottom_new;
      *yycapacity = yyalloc;
    }
  return 0;
}

/* Establish the initial context for the current lookahead if no initial
   context is currently established.

   We define a context as a snapshot of the parser stacks.  We define
   the initial context for a lookahead as the context in which the
   parser initially examines that lookahead in order to select a
   syntactic action.  Thus, if the lookahead eventually proves
   syntactically unacceptable (possibly in a later context reached via a
   series of reductions), the initial context can be used to determine
   the exact set of tokens that would be syntactically acceptable in the
   lookahead's place.  Moreover, it is the context after which any
   further semantic actions would be erroneous because they would be
   determined by a syntactically unacceptable token.

   YY_LAC_ESTABLISH should be invoked when a reduction is about to be
   performed in an inconsistent state (which, for the purposes of LAC,
   includes consistent states that don't know they're consistent because
   their default reductions have been disabled).  Iff there is a
   lookahead token, it should also be invoked before reporting a syntax
   error.  This latter case is for the sake of the debugging output.

   For parse.lac=full, the implementation of YY_LAC_ESTABLISH is as
   follows.  If no initial context is currently established for the
   current lookahead, then check if that lookahead can eventually be
   shifted if syntactic actions continue from the current context.
   Report a syntax error if it cannot.  */
#define YY_LAC_ESTABLISH                                                \
do {                                                                    \
  if (!yy_lac_established)                                              \
    {                                                                   \
      YYDPRINTF ((stderr,                                               \
                  "LAC: initial context established for %s\n",          \
                  yysymbol_name (yytoken)));                            \
      yy_lac_established = 1;                                           \
      switch (yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken))    \
        {                                                               \
        case YYENOMEM:                                                  \
          YYNOMEM;                                                      \
        case 1:                                                         \
          goto yyerrlab;                                                \
        }                                                               \
    }                                                                   \
} while (0)

/* Discard any previous initial lookahead context because of Event,
   which may be a lookahead change or an invalidation of the currently
   established initial context for the current lookahead.

   The most common example of a lookahead change is a shift.  An example
   of both cases is syntax error recovery.  That is, a syntax error
   occurs when the lookahead is syntactically erroneous for the
   currently established initial context, so error recovery manipulates
   the parser stacks to try to find a new initial context in which the
   current lookahead is syntactically acceptable.  If it fails to find
   such a context, it discards the lookahead.  */
#if YYDEBUG
# define YY_LAC_DISCARD(Event)                                           \
do {                                                                     \
  if (yy_lac_established)                                                \
    {                                                                    \
      YYDPRINTF ((stderr, "LAC: initial context discarded due to "       \
                  Event "\n"));                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (0)
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return YYENOMEM if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yy_state_t *yyesa, yy_state_t **yyes,
        YYPTRDIFF_T *yyes_capacity, yy_state_t *yyssp, yysymbol_kind_t yytoken)
{
  yy_state_t *yyes_prev = yyssp;
  yy_state_t *yyesp = yyes_prev;
  /* Reduce until we encounter a shift and thereby accept the token.  */
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yysymbol_name (yytoken)));
  if (yytoken == YYSYMBOL_YYUNDEF)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[+*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          /* Use the default action.  */
          yyrule = yydefact[+*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
          /* Use the action from yytable.  */
          yyrule = yytable[yyrule];
          if (yytable_value_is_error (yyrule))
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
          if (0 < yyrule)
            {
              YYDPRINTF ((stderr, " S%d\n", yyrule));
              return 0;
            }
          yyrule = -yyrule;
        }
      /* By now we know we have to simulate a reduce.  */
      YYDPRINTF ((stderr, " R%d", yyrule - 1));
      {
        /* Pop the corresponding number of values from the stack.  */
        YYPTRDIFF_T yylen = yyr2[yyrule];
        /* First pop from the LAC stack as many tokens as possible.  */
        if (yyesp != yyes_prev)
          {
            YYPTRDIFF_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yyesp = yyes_prev;
                yylen -= yysize;
              }
          }
        /* Only afterwards look at the main stack.  */
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      /* Push the resulting state of the reduction.  */
      {
        yy_state_fast_t yystate;
        {
          const int yylhs = yyr1[yyrule] - YYNTOKENS;
          const int yyi = yypgoto[yylhs] + *yyesp;
          yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyesp
                     ? yytable[yyi]
                     : yydefgoto[yylhs]);
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            YY_IGNORE_USELESS_CAST_BEGIN
            *yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        else
          {
            if (yy_lac_stack_realloc (yyes_capacity, 1,
#if YYDEBUG
                                      " (", ")",
#endif
                                      yyes, yyesa, &yyesp, yyes_prev))
              {
                YYDPRINTF ((stderr, "\n"));
                return YYENOMEM;
              }
            YY_IGNORE_USELESS_CAST_BEGIN
            *++yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}

/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yy_state_t *yyesa;
  yy_state_t **yyes;
  YYPTRDIFF_T *yyes_capacity;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;

  int yyx;
  for (yyx = 0; yyx < YYNTOKENS; ++yyx)
    {
      yysymbol_kind_t yysym = YY_CAST (yysymbol_kind_t, yyx);
      if (yysym != YYSYMBOL_YYerror && yysym != YYSYMBOL_YYUNDEF)
        switch (yy_lac (yyctx->yyesa, yyctx->yyes, yyctx->yyes_capacity, yyctx->yyssp, yysym))
          {
          case YYENOMEM:
            return YYENOMEM;
          case 1:
            continue;
          default:
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif



static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else if (yyn == 0)
        YYDPRINTF ((stderr, "No expected tokens.\n"));
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store or if
   yy_lac returned YYENOMEM.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yystrlen (yysymbol_name (yyarg[yyi]));
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp = yystpcpy (yyp, yysymbol_name (yyarg[yyi++]));
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, char const *file_name)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (file_name);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (char const *file_name)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

    yy_state_t yyesa[20];
    yy_state_t *yyes = yyesa;
    YYPTRDIFF_T yyes_capacity = 20 < YYMAXDEPTH ? 20 : YYMAXDEPTH;

  /* Whether LAC context is established.  A Boolean.  */
  int yy_lac_established = 0;
  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    {
      YY_LAC_ESTABLISH;
      goto yydefault;
    }
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      YY_LAC_ESTABLISH;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  YY_LAC_DISCARD ("shift");
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
  case 2: /* program: textSection dataSection stackSection ".end"  */
#line 176 "asm.y"
           { setProgAST(ast_program((yyvsp[-3].text_section), (yyvsp[-2].data_section), (yyvsp[-1].stack_section))); }
#line 1925 "asm.tab.c"
    break;

  case 3: /* textSection: ".text" entryPoint asmInstrs  */
#line 179 "asm.y"
           { (yyval.text_section) = ast_text_section((yyvsp[-2].token),(yyvsp[-1].addr),(yyvsp[0].asm_instrs)); }
#line 1931 "asm.tab.c"
    break;

  case 5: /* addr: label  */
#line 184 "asm.y"
             { (yyval.addr) = ast_addr_label((yyvsp[0].ident)); }
#line 1937 "asm.tab.c"
    break;

  case 6: /* addr: unsignednumsym  */
#line 185 "asm.y"
                       { (yyval.addr) = ast_entry_addr((yyvsp[0].unsignednum)); }
#line 1943 "asm.tab.c"
    break;

  case 8: /* asmInstrs: asmInstr  */
#line 191 "asm.y"
                     { (yyval.asm_instrs) = ast_asm_instrs_singleton((yyvsp[0].asm_instr)); }
#line 1949 "asm.tab.c"
    break;

  case 9: /* asmInstrs: asmInstrs asmInstr  */
#line 192 "asm.y"
                           { (yyval.asm_instrs) = ast_asm_instrs_add((yyvsp[-1].asm_instrs),(yyvsp[0].asm_instr)); }
#line 1955 "asm.tab.c"
    break;

  case 10: /* asmInstr: labelOpt instr eolsym  */
#line 195 "asm.y"
                                 { (yyval.asm_instr) = ast_asm_instr((yyvsp[-2].label_opt),(yyvsp[-1].instr)); }
#line 1961 "asm.tab.c"
    break;

  case 11: /* labelOpt: label ":"  */
#line 197 "asm.y"
                     { (yyval.label_opt) = ast_label_opt_label((yyvsp[-1].ident)); }
#line 1967 "asm.tab.c"
    break;

  case 12: /* labelOpt: empty  */
#line 198 "asm.y"
              { (yyval.label_opt) = ast_label_opt_empty((yyvsp[0].empty)); }
#line 1973 "asm.tab.c"
    break;

  case 13: /* empty: %empty  */
#line 201 "asm.y"
               { (yyval.empty) = ast_empty(lexer_filename(), lexer_line()); }
#line 1979 "asm.tab.c"
    break;

  case 29: /* noArgInstr: noArgOp  */
#line 212 "asm.y"
                     { (yyval.instr) = ast_0arg_instr((yyvsp[0].token)); }
#line 1985 "asm.tab.c"
    break;

  case 32: /* twoRegCompInstr: twoRegCompOp regsym "," offset "," regsym "," offset  */
#line 218 "asm.y"
           {
	       (yyval.instr) = ast_2reg_instr((yyvsp[-7].token), (yyvsp[-6].reg).number, (yyvsp[-4].number).value,
				   (yyvsp[-2].reg).number, (yyvsp[0].number).value,
				   lexer_token2func((yyvsp[-7].token).toknum));
	   }
#line 1995 "asm.tab.c"
    break;

  case 43: /* offset: number  */
#line 230 "asm.y"
           {
	       machine_types_check_fits_in_offset((yyvsp[0].number).value);
	       (yyval.number) = (yyvsp[0].number);
	   }
#line 2004 "asm.tab.c"
    break;

  case 44: /* number: sign unsignednumsym  */
#line 237 "asm.y"
           {
	       word_type val = (yyvsp[0].unsignednum).value;
               if ((yyvsp[-1].token).toknum == minussym) {
		   val = - val;
               }
               (yyval.number) = ast_number((yyvsp[-1].token), val);
	   }
#line 2016 "asm.tab.c"
    break;

  case 47: /* sign: empty  */
#line 247 "asm.y"
             { (yyval.token) = ast_token(lexer_filename(), lexer_line(), plussym); }
#line 2022 "asm.tab.c"
    break;

  case 48: /* twoRegNoOffsetsInstr: twoRegNoOffsetsOp regsym "," regsym  */
#line 252 "asm.y"
           {
	       (yyval.instr) = ast_2reg_instr((yyvsp[-3].token), (yyvsp[-2].reg).number, 0, (yyvsp[0].reg).number, 0,
				   lexer_token2func((yyvsp[-3].token).toknum));
	   }
#line 2031 "asm.tab.c"
    break;

  case 50: /* noTargetOffsetInstr: noTargetOffsetOp regsym "," regsym "," offset  */
#line 262 "asm.y"
           {
	       (yyval.instr) = ast_2reg_instr((yyvsp[-5].token), (yyvsp[-4].reg).number, 0, (yyvsp[-2].reg).number, (yyvsp[0].number).value,
				   lexer_token2func((yyvsp[-5].token).toknum));
	   }
#line 2040 "asm.tab.c"
    break;

  case 52: /* noSourceOffsetInstr: noSourceOffsetOp regsym "," offset "," regsym  */
#line 272 "asm.y"
           {
	       (yyval.instr) = ast_2reg_instr((yyvsp[-5].token), (yyvsp[-4].reg).number, (yyvsp[-2].number).value, (yyvsp[0].reg).number, 0,
				   lexer_token2func((yyvsp[-5].token).toknum));
	   }
#line 2049 "asm.tab.c"
    break;

  case 54: /* oneRegOffsetArgInstr: oneRegOffsetArgOp regsym "," offset "," arg  */
#line 282 "asm.y"
           {
	       (yyval.instr) = ast_1reg_instr((yyvsp[-5].token), other_comp_instr_type,
				   1, (yyvsp[-4].reg).number, (yyvsp[-2].number).value,
				   lexer_token2func((yyvsp[-5].token).toknum),
				   ast_immed_number((yyvsp[0].number).value));
	   }
#line 2060 "asm.tab.c"
    break;

  case 56: /* arg: number  */
#line 293 "asm.y"
           {   /* the number is signed */
	       machine_types_check_fits_in_arg((yyvsp[0].number).value);
	       (yyval.number) = (yyvsp[0].number);
	   }
#line 2069 "asm.tab.c"
    break;

  case 57: /* oneRegArgInstr: oneRegArgOp regsym "," arg  */
#line 301 "asm.y"
           {
	       (yyval.instr) = ast_1reg_instr((yyvsp[-3].token), other_comp_instr_type,
				   1, (yyvsp[-2].reg).number, 0,
				   lexer_token2func((yyvsp[-3].token).toknum),
				   ast_immed_number((yyvsp[0].number).value));
	   }
#line 2080 "asm.tab.c"
    break;

  case 60: /* oneRegOffsetInstr: oneRegOffsetOp regsym "," offset  */
#line 313 "asm.y"
           {
	       (yyval.instr) = ast_1reg_instr((yyvsp[-3].token), other_comp_instr_type,
				   1, (yyvsp[-2].reg).number, (yyvsp[0].number).value,
				   lexer_token2func((yyvsp[-3].token).toknum),
				   ast_immed_none());
	   }
#line 2091 "asm.tab.c"
    break;

  case 67: /* shiftInstr: shiftOp regsym "," offset "," shift  */
#line 325 "asm.y"
           {
	       (yyval.instr) = ast_1reg_instr((yyvsp[-5].token), other_comp_instr_type,
				   1, (yyvsp[-4].reg).number, (yyvsp[-2].number).value,
				   lexer_token2func((yyvsp[-5].token).toknum),
				   (yyvsp[0].immed));
	   }
#line 2102 "asm.tab.c"
    break;

  case 70: /* shift: unsignednumsym  */
#line 336 "asm.y"
           {
	       machine_types_check_fits_in_shift((yyvsp[0].unsignednum).value);
	       (yyval.immed) = ast_immed_unsigned((yyvsp[0].unsignednum).value);
	   }
#line 2111 "asm.tab.c"
    break;

  case 71: /* argOnlyInstr: argOnlyOp arg  */
#line 344 "asm.y"
           {
	       (yyval.instr) = ast_1reg_instr((yyvsp[-1].token), other_comp_instr_type,
				   0, 0, 0, lexer_token2func((yyvsp[-1].token).toknum),
				   ast_immed_number((yyvsp[0].number).value));
	   }
#line 2121 "asm.tab.c"
    break;

  case 73: /* immedArithInstr: immedArithOp regsym "," offset "," immed  */
#line 355 "asm.y"
           {
	       (yyval.instr) = ast_1reg_instr((yyvsp[-5].token), immed_instr_type,
				   1, (yyvsp[-4].reg).number, (yyvsp[-2].number).value,
				   0, (yyvsp[0].immed));
	   }
#line 2131 "asm.tab.c"
    break;

  case 75: /* immed: number  */
#line 365 "asm.y"
       {
	   machine_types_check_fits_in_immed((yyvsp[0].number).value);
           (yyval.immed) = ast_immed_number((yyvsp[0].number).value);
       }
#line 2140 "asm.tab.c"
    break;

  case 76: /* immedBoolInstr: immedBoolOp regsym "," offset "," uimmed  */
#line 373 "asm.y"
       {
	   (yyval.instr) = ast_1reg_instr((yyvsp[-5].token), immed_instr_type,
			       1, (yyvsp[-4].reg).number, (yyvsp[-2].number).value,
			       0, (yyvsp[0].immed));
       }
#line 2150 "asm.tab.c"
    break;

  case 81: /* uimmed: unsignednumsym  */
#line 383 "asm.y"
       {
	   machine_types_check_fits_in_uimmed((yyvsp[0].unsignednum).value);
           (yyval.immed) = ast_immed_unsigned((yyvsp[0].unsignednum).value);
       }
#line 2159 "asm.tab.c"
    break;

  case 82: /* branchTestInstr: branchTestOp regsym "," offset "," immed  */
#line 391 "asm.y"
       {
	   (yyval.instr) = ast_1reg_instr((yyvsp[-5].token), immed_instr_type,
			       1, (yyvsp[-4].reg).number, (yyvsp[-2].number).value,
			       0, (yyvsp[0].immed));
       }
#line 2169 "asm.tab.c"
    break;

  case 89: /* jumpInstr: jumpOp addr  */
#line 402 "asm.y"
            {
		if ((yyvsp[0].addr).address_defined) {
		    machine_types_check_fits_in_addr((yyvsp[0].addr).addr);
		}
		(yyval.instr) = ast_1reg_instr((yyvsp[-1].token), jump_instr_type,
				    0, 0, 0,
				    0, ast_immed_addr((yyvsp[0].addr)));
	    }
#line 2182 "asm.tab.c"
    break;

  case 95: /* offsetOnlySyscall: offsetOnlySyscallOp offset  */
#line 418 "asm.y"
            {
		(yyval.instr) = ast_1reg_instr((yyvsp[-1].token), syscall_instr_type,
				    1, 0, (yyvsp[0].number).value, 
				    SYS_F, ast_syscall_code_for((yyvsp[-1].token).toknum));
	    }
#line 2192 "asm.tab.c"
    break;

  case 97: /* regOffsetSyscall: regOffsetSyscallOp regsym "," offset  */
#line 429 "asm.y"
            {
		(yyval.instr) = ast_1reg_instr((yyvsp[-3].token), syscall_instr_type,
				    1, (yyvsp[-2].reg).number, (yyvsp[0].number).value, 
				    SYS_F, ast_syscall_code_for((yyvsp[-3].token).toknum));
	    }
#line 2202 "asm.tab.c"
    break;

  case 102: /* noArgSyscall: noArgSyscallOp  */
#line 440 "asm.y"
            {
		(yyval.instr) = ast_1reg_instr((yyvsp[0].token), syscall_instr_type,
				    0, 0, 0,
				    SYS_F, ast_syscall_code_for((yyvsp[0].token).toknum));
	    }
#line 2212 "asm.tab.c"
    break;

  case 105: /* dataSection: ".data" staticStartAddr staticDecls  */
#line 452 "asm.y"
              { (yyval.data_section) = ast_data_section((yyvsp[-2].token), (yyvsp[-1].unsignednum).value, (yyvsp[0].static_decls)); }
#line 2218 "asm.tab.c"
    break;

  case 107: /* staticDecls: empty  */
#line 458 "asm.y"
                    { (yyval.static_decls) = ast_static_decls_empty((yyvsp[0].empty)); }
#line 2224 "asm.tab.c"
    break;

  case 108: /* staticDecls: staticDecls staticDecl  */
#line 459 "asm.y"
                                     { (yyval.static_decls) = ast_static_decls_add((yyvsp[-1].static_decls),(yyvsp[0].static_decl)); }
#line 2230 "asm.tab.c"
    break;

  case 109: /* staticDecl: dataSize identsym initializerOpt eolsym  */
#line 463 "asm.y"
            { (yyval.static_decl) = ast_static_decl((yyvsp[-3].data_size), (yyvsp[-2].ident), (yyvsp[-1].initializer)); }
#line 2236 "asm.tab.c"
    break;

  case 110: /* dataSize: "WORD"  */
#line 465 "asm.y"
                  { (yyval.data_size) = ast_data_size((yyvsp[0].token), ds_word, 1); }
#line 2242 "asm.tab.c"
    break;

  case 111: /* dataSize: "CHAR"  */
#line 466 "asm.y"
                  { (yyval.data_size) = ast_data_size((yyvsp[0].token), ds_char, 1); }
#line 2248 "asm.tab.c"
    break;

  case 112: /* dataSize: "STRING" "[" unsignednumsym "]"  */
#line 468 "asm.y"
                  { (yyval.data_size) = ast_data_size((yyvsp[-3].token), ds_string,
				       /* declared size is in words! */
				       (yyvsp[-1].unsignednum).value); }
#line 2256 "asm.tab.c"
    break;

  case 113: /* initializerOpt: "=" number  */
#line 472 "asm.y"
                            { (yyval.initializer) = ast_initializer_number((yyvsp[-1].token), (yyvsp[0].number).value); }
#line 2262 "asm.tab.c"
    break;

  case 114: /* initializerOpt: "=" charliteralsym  */
#line 474 "asm.y"
                  { (yyval.initializer) = ast_initializer_char((yyvsp[-1].token), (yyvsp[0].charlit).value); }
#line 2268 "asm.tab.c"
    break;

  case 115: /* initializerOpt: "=" stringliteralsym  */
#line 476 "asm.y"
                  { (yyval.initializer) = ast_initializer_string((yyvsp[-1].token), (yyvsp[0].stringlit).pointer); }
#line 2274 "asm.tab.c"
    break;

  case 116: /* initializerOpt: empty  */
#line 477 "asm.y"
                       { (yyval.initializer) = ast_initializer_empty((yyvsp[0].empty)); }
#line 2280 "asm.tab.c"
    break;

  case 117: /* stackSection: ".stack" stackBottomAddr  */
#line 482 "asm.y"
              { (yyval.stack_section) = ast_stack_section((yyvsp[-1].token), (yyvsp[0].unsignednum).value); }
#line 2286 "asm.tab.c"
    break;


#line 2290 "asm.tab.c"

        default: break;
      }
    if (yychar_backup != yychar)
      YY_LAC_DISCARD ("yychar change");
  }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yyesa, &yyes, &yyes_capacity, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (file_name, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, file_name);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, file_name);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  /* If the stack popping above didn't lose the initial context for the
     current lookahead token, the shift below will for sure.  */
  YY_LAC_DISCARD ("error recovery");

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (file_name, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, file_name);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, file_name);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 486 "asm.y"


// Set the program's ast to be t
void setProgAST(ast_program_t t) { progast = t; }
