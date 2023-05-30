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




/* First part of user prologue.  */
#line 2 "miniC.y"

#include "../libraries/ast.h"
#include "semantic_analysis.h"
#include <stdio.h>
void yyerror(const char *);
extern int yylex();
extern int yylex_destroy();
extern bool semantic_analysis(astNode*);
extern FILE *yyin;
extern int yylineno;
extern char* yytext;
extern astNode* root;

#line 85 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    EXTERN = 258,                  /* EXTERN  */
    TYPE = 259,                    /* TYPE  */
    RETURN = 260,                  /* RETURN  */
    IF = 261,                      /* IF  */
    ELSE = 262,                    /* ELSE  */
    WHILE = 263,                   /* WHILE  */
    ADD = 264,                     /* ADD  */
    SUB = 265,                     /* SUB  */
    MUL = 266,                     /* MUL  */
    DIV = 267,                     /* DIV  */
    EQ = 268,                      /* EQ  */
    GT = 269,                      /* GT  */
    LT = 270,                      /* LT  */
    GEQ = 271,                     /* GEQ  */
    LEQ = 272,                     /* LEQ  */
    NUMBER = 273,                  /* NUMBER  */
    NAME = 274,                    /* NAME  */
    PRINT = 275,                   /* PRINT  */
    READ = 276,                    /* READ  */
    IFX = 277                      /* IFX  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define EXTERN 258
#define TYPE 259
#define RETURN 260
#define IF 261
#define ELSE 262
#define WHILE 263
#define ADD 264
#define SUB 265
#define MUL 266
#define DIV 267
#define EQ 268
#define GT 269
#define LT 270
#define GEQ 271
#define LEQ 272
#define NUMBER 273
#define NAME 274
#define PRINT 275
#define READ 276
#define IFX 277

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "miniC.y"

        int ival;
        char* idname;
        astNode *nptr;
        vector<astNode *> *svec_ptr;

#line 189 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_EXTERN = 3,                     /* EXTERN  */
  YYSYMBOL_TYPE = 4,                       /* TYPE  */
  YYSYMBOL_RETURN = 5,                     /* RETURN  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_WHILE = 8,                      /* WHILE  */
  YYSYMBOL_ADD = 9,                        /* ADD  */
  YYSYMBOL_SUB = 10,                       /* SUB  */
  YYSYMBOL_MUL = 11,                       /* MUL  */
  YYSYMBOL_DIV = 12,                       /* DIV  */
  YYSYMBOL_EQ = 13,                        /* EQ  */
  YYSYMBOL_GT = 14,                        /* GT  */
  YYSYMBOL_LT = 15,                        /* LT  */
  YYSYMBOL_GEQ = 16,                       /* GEQ  */
  YYSYMBOL_LEQ = 17,                       /* LEQ  */
  YYSYMBOL_NUMBER = 18,                    /* NUMBER  */
  YYSYMBOL_NAME = 19,                      /* NAME  */
  YYSYMBOL_PRINT = 20,                     /* PRINT  */
  YYSYMBOL_READ = 21,                      /* READ  */
  YYSYMBOL_IFX = 22,                       /* IFX  */
  YYSYMBOL_23_ = 23,                       /* '('  */
  YYSYMBOL_24_ = 24,                       /* ')'  */
  YYSYMBOL_25_ = 25,                       /* ';'  */
  YYSYMBOL_26_ = 26,                       /* '{'  */
  YYSYMBOL_27_ = 27,                       /* '}'  */
  YYSYMBOL_28_ = 28,                       /* '='  */
  YYSYMBOL_YYACCEPT = 29,                  /* $accept  */
  YYSYMBOL_program = 30,                   /* program  */
  YYSYMBOL_extern = 31,                    /* extern  */
  YYSYMBOL_function_def = 32,              /* function_def  */
  YYSYMBOL_block_stmt = 33,                /* block_stmt  */
  YYSYMBOL_var_decls = 34,                 /* var_decls  */
  YYSYMBOL_decl = 35,                      /* decl  */
  YYSYMBOL_stmts = 36,                     /* stmts  */
  YYSYMBOL_stmt = 37,                      /* stmt  */
  YYSYMBOL_if_stmt = 38,                   /* if_stmt  */
  YYSYMBOL_if_else_stmt = 39,              /* if_else_stmt  */
  YYSYMBOL_while_loop = 40,                /* while_loop  */
  YYSYMBOL_call_stmt = 41,                 /* call_stmt  */
  YYSYMBOL_return_stmt = 42,               /* return_stmt  */
  YYSYMBOL_term = 43,                      /* term  */
  YYSYMBOL_asgn_stmt = 44,                 /* asgn_stmt  */
  YYSYMBOL_expr = 45,                      /* expr  */
  YYSYMBOL_condition = 46                  /* condition  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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
typedef yytype_int8 yy_state_t;

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

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   131

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  29
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  42
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  108

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   277


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
      23,    24,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    25,
       2,    28,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    26,     2,    27,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int8 yyrline[] =
{
       0,    39,    39,    41,    42,    44,    45,    47,    48,    50,
      51,    53,    55,    56,    58,    59,    60,    61,    62,    63,
      64,    66,    68,    70,    72,    73,    75,    76,    78,    79,
      81,    82,    83,    85,    86,    87,    88,    89,    92,    93,
      94,    95,    96
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "EXTERN", "TYPE",
  "RETURN", "IF", "ELSE", "WHILE", "ADD", "SUB", "MUL", "DIV", "EQ", "GT",
  "LT", "GEQ", "LEQ", "NUMBER", "NAME", "PRINT", "READ", "IFX", "'('",
  "')'", "';'", "'{'", "'}'", "'='", "$accept", "program", "extern",
  "function_def", "block_stmt", "var_decls", "decl", "stmts", "stmt",
  "if_stmt", "if_else_stmt", "while_loop", "call_stmt", "return_stmt",
  "term", "asgn_stmt", "expr", "condition", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-37)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       4,    17,    33,     4,   -15,   -37,    40,    14,    23,    28,
     -37,    62,    44,    49,    53,    48,     5,    58,   -37,    65,
      69,   -37,    72,     6,   -37,    69,    78,    12,    75,    76,
      74,    77,    80,   -37,     6,   -37,    -4,   -37,   -37,   -37,
     -37,   -37,   -37,   -37,   -37,    79,   -37,   -37,    52,    81,
       0,     0,    24,    86,    83,   -37,    55,   -37,   -37,   -37,
       0,    82,    84,   -37,    73,    85,    87,    89,    29,    88,
      90,    91,   -37,   -37,     0,     0,     0,     0,    92,     0,
       0,     0,     0,     0,    59,    59,    94,   -37,   -37,    95,
     -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,
     -37,   103,   -37,    96,   -37,    59,   -37,   -37
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     1,     0,     0,     0,     0,
       2,     0,     0,     0,     0,     0,     0,     0,     3,     0,
       0,     4,     0,     0,     6,     0,     0,     0,     0,     0,
       0,     0,     0,    18,     0,    10,     0,    13,    15,    16,
      17,    19,    20,    14,     5,     0,    29,    28,     0,     0,
       0,     0,     0,     0,     0,     9,     0,     8,    12,    11,
       0,     0,     0,    27,     0,     0,     0,     0,     0,     0,
       0,     0,     7,    37,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    31,    30,     0,
      25,    33,    34,    35,    36,    26,    38,    39,    40,    41,
      42,    21,    23,     0,    24,     0,    32,    22
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -37,   -37,    98,   -37,   -12,   -37,    93,    97,   -36,   -37,
     -37,   -37,   -37,   -37,   -24,   -37,    63,    68
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,    10,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    64,    43,    62,    65
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      58,    27,    28,    49,    29,     7,     8,     1,    24,    19,
      26,    27,    28,    44,    29,    30,    31,    32,    46,    47,
      58,     4,    23,    57,    61,    30,    31,    32,    68,    20,
      46,    47,    23,     5,    60,    48,    73,    11,    74,    75,
      76,    77,    46,    47,     9,    67,    12,    13,   101,   102,
      91,    92,    93,    94,    87,    96,    97,    98,    99,   100,
      27,    28,    60,    29,    27,    28,    14,    29,    15,   107,
      46,    47,    16,    18,    30,    31,    32,    17,    30,    31,
      32,    23,    72,    21,    22,    23,    79,    80,    81,    82,
      83,    74,    75,    76,    77,    23,    25,    45,    50,    51,
      53,     6,    52,    54,    59,    70,    63,    71,    78,    84,
     105,    85,    86,    88,    89,    69,    90,    95,   103,    66,
     104,   106,     0,     0,     0,     0,     0,    55,     0,     0,
       0,    56
};

static const yytype_int8 yycheck[] =
{
      36,     5,     6,    27,     8,    20,    21,     3,    20,     4,
       4,     5,     6,    25,     8,    19,    20,    21,    18,    19,
      56,     4,    26,    27,    48,    19,    20,    21,    52,    24,
      18,    19,    26,     0,    10,    23,    60,    23,     9,    10,
      11,    12,    18,    19,     4,    21,    23,    19,    84,    85,
      74,    75,    76,    77,    25,    79,    80,    81,    82,    83,
       5,     6,    10,     8,     5,     6,     4,     8,    24,   105,
      18,    19,    23,    25,    19,    20,    21,    24,    19,    20,
      21,    26,    27,    25,    19,    26,    13,    14,    15,    16,
      17,     9,    10,    11,    12,    26,    24,    19,    23,    23,
      23,     3,    28,    23,    25,    19,    25,    24,    24,    24,
       7,    24,    23,    25,    24,    52,    25,    25,    24,    51,
      25,    25,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,
      -1,    34
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    30,    31,     4,     0,    31,    20,    21,     4,
      32,    23,    23,    19,     4,    24,    23,    24,    25,     4,
      24,    25,    19,    26,    33,    24,     4,     5,     6,     8,
      19,    20,    21,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    44,    33,    19,    18,    19,    23,    43,
      23,    23,    28,    23,    23,    35,    36,    27,    37,    25,
      10,    43,    45,    25,    43,    46,    46,    21,    43,    45,
      19,    24,    27,    43,     9,    10,    11,    12,    24,    13,
      14,    15,    16,    17,    24,    24,    23,    25,    25,    24,
      25,    43,    43,    43,    43,    25,    43,    43,    43,    43,
      43,    37,    37,    24,    25,     7,    25,    37
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    29,    30,    31,    31,    32,    32,    33,    33,    34,
      34,    35,    36,    36,    37,    37,    37,    37,    37,    37,
      37,    38,    39,    40,    41,    41,    42,    42,    43,    43,
      44,    44,    44,    45,    45,    45,    45,    45,    46,    46,
      46,    46,    46
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     6,     7,     7,     5,     4,     3,     2,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     7,     5,     5,     4,     5,     3,     1,     1,
       4,     4,     6,     3,     3,     3,     3,     2,     3,     3,
       3,     3,     3
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
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
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
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: extern extern function_def  */
#line 39 "miniC.y"
                                     {(yyval.nptr) = createProg((yyvsp[-2].nptr), (yyvsp[-1].nptr), (yyvsp[0].nptr)); root = (yyval.nptr);}
#line 1277 "y.tab.c"
    break;

  case 3: /* extern: EXTERN TYPE READ '(' ')' ';'  */
#line 41 "miniC.y"
                                      {(yyval.nptr) = createExtern((yyvsp[-3].idname)); free((yyvsp[-3].idname));}
#line 1283 "y.tab.c"
    break;

  case 4: /* extern: EXTERN TYPE PRINT '(' TYPE ')' ';'  */
#line 42 "miniC.y"
                                             {(yyval.nptr) = createExtern((yyvsp[-4].idname)); free((yyvsp[-4].idname));}
#line 1289 "y.tab.c"
    break;

  case 5: /* function_def: TYPE NAME '(' TYPE NAME ')' block_stmt  */
#line 44 "miniC.y"
                                                      {(yyval.nptr) = createFunc((yyvsp[-5].idname), createVar((yyvsp[-2].idname)), (yyvsp[0].nptr)); free((yyvsp[-5].idname)); free((yyvsp[-2].idname));}
#line 1295 "y.tab.c"
    break;

  case 6: /* function_def: TYPE NAME '(' ')' block_stmt  */
#line 45 "miniC.y"
                                       {(yyval.nptr) = createFunc((yyvsp[-3].idname), NULL, (yyvsp[0].nptr)); free((yyvsp[-3].idname));}
#line 1301 "y.tab.c"
    break;

  case 7: /* block_stmt: '{' var_decls stmts '}'  */
#line 47 "miniC.y"
                                     {(yyvsp[-2].svec_ptr)->insert((yyvsp[-2].svec_ptr)->end(),  (yyvsp[-1].svec_ptr)->begin(), (yyvsp[-1].svec_ptr)->end()); delete((yyvsp[-1].svec_ptr)); (yyval.nptr) = createBlock((yyvsp[-2].svec_ptr));}
#line 1307 "y.tab.c"
    break;

  case 8: /* block_stmt: '{' stmts '}'  */
#line 48 "miniC.y"
                        {(yyval.nptr) = createBlock((yyvsp[-1].svec_ptr));}
#line 1313 "y.tab.c"
    break;

  case 9: /* var_decls: var_decls decl  */
#line 50 "miniC.y"
                           {(yyval.svec_ptr) = (yyvsp[-1].svec_ptr); (yyval.svec_ptr)->push_back((yyvsp[0].nptr));}
#line 1319 "y.tab.c"
    break;

  case 10: /* var_decls: decl  */
#line 51 "miniC.y"
               {(yyval.svec_ptr) = new vector<astNode *>(); (yyval.svec_ptr)->push_back((yyvsp[0].nptr));}
#line 1325 "y.tab.c"
    break;

  case 11: /* decl: TYPE NAME ';'  */
#line 53 "miniC.y"
                     {(yyval.nptr) = createDecl((yyvsp[-1].idname)); free((yyvsp[-1].idname));}
#line 1331 "y.tab.c"
    break;

  case 12: /* stmts: stmts stmt  */
#line 55 "miniC.y"
                   {(yyval.svec_ptr) = (yyvsp[-1].svec_ptr); (yyval.svec_ptr)->push_back((yyvsp[0].nptr));}
#line 1337 "y.tab.c"
    break;

  case 13: /* stmts: stmt  */
#line 56 "miniC.y"
               {(yyval.svec_ptr) = new vector<astNode *>(); (yyval.svec_ptr)->push_back((yyvsp[0].nptr));}
#line 1343 "y.tab.c"
    break;

  case 14: /* stmt: asgn_stmt  */
#line 58 "miniC.y"
                 { (yyval.nptr) = (yyvsp[0].nptr);}
#line 1349 "y.tab.c"
    break;

  case 15: /* stmt: if_stmt  */
#line 59 "miniC.y"
                  { (yyval.nptr) = (yyvsp[0].nptr);}
#line 1355 "y.tab.c"
    break;

  case 16: /* stmt: if_else_stmt  */
#line 60 "miniC.y"
                       { (yyval.nptr) = (yyvsp[0].nptr);}
#line 1361 "y.tab.c"
    break;

  case 17: /* stmt: while_loop  */
#line 61 "miniC.y"
                     { (yyval.nptr) = (yyvsp[0].nptr);}
#line 1367 "y.tab.c"
    break;

  case 18: /* stmt: block_stmt  */
#line 62 "miniC.y"
                     { (yyval.nptr) = (yyvsp[0].nptr);}
#line 1373 "y.tab.c"
    break;

  case 19: /* stmt: call_stmt  */
#line 63 "miniC.y"
                    { (yyval.nptr) = (yyvsp[0].nptr);}
#line 1379 "y.tab.c"
    break;

  case 20: /* stmt: return_stmt  */
#line 64 "miniC.y"
                      { (yyval.nptr) = (yyvsp[0].nptr);}
#line 1385 "y.tab.c"
    break;

  case 21: /* if_stmt: IF '(' condition ')' stmt  */
#line 66 "miniC.y"
                                             { (yyval.nptr) = createIf((yyvsp[-2].nptr), (yyvsp[0].nptr), NULL);}
#line 1391 "y.tab.c"
    break;

  case 22: /* if_else_stmt: IF '(' condition ')' stmt ELSE stmt  */
#line 68 "miniC.y"
                                                  { (yyval.nptr) = createIf((yyvsp[-4].nptr), (yyvsp[-2].nptr), (yyvsp[0].nptr));}
#line 1397 "y.tab.c"
    break;

  case 23: /* while_loop: WHILE '(' condition ')' stmt  */
#line 70 "miniC.y"
                                          {(yyval.nptr) = createWhile((yyvsp[-2].nptr), (yyvsp[0].nptr));}
#line 1403 "y.tab.c"
    break;

  case 24: /* call_stmt: PRINT '(' NAME ')' ';'  */
#line 72 "miniC.y"
                                  { (yyval.nptr) = createCall((yyvsp[-4].idname), createVar((yyvsp[-2].idname))); free((yyvsp[-4].idname)); free((yyvsp[-2].idname));}
#line 1409 "y.tab.c"
    break;

  case 25: /* call_stmt: READ '(' ')' ';'  */
#line 73 "miniC.y"
                         { (yyval.nptr) = createCall((yyvsp[-3].idname), NULL); free((yyvsp[-3].idname));}
#line 1415 "y.tab.c"
    break;

  case 26: /* return_stmt: RETURN '(' expr ')' ';'  */
#line 75 "miniC.y"
                                      { (yyval.nptr) = createRet((yyvsp[-2].nptr));}
#line 1421 "y.tab.c"
    break;

  case 27: /* return_stmt: RETURN term ';'  */
#line 76 "miniC.y"
                          { (yyval.nptr) = createRet((yyvsp[-1].nptr));}
#line 1427 "y.tab.c"
    break;

  case 28: /* term: NAME  */
#line 78 "miniC.y"
            {(yyval.nptr) = createVar((yyvsp[0].idname)); free((yyvsp[0].idname));}
#line 1433 "y.tab.c"
    break;

  case 29: /* term: NUMBER  */
#line 79 "miniC.y"
                 {(yyval.nptr) = createCnst((yyvsp[0].ival));}
#line 1439 "y.tab.c"
    break;

  case 30: /* asgn_stmt: NAME '=' expr ';'  */
#line 81 "miniC.y"
                              { (yyval.nptr) = createAsgn(createVar((yyvsp[-3].idname)), (yyvsp[-1].nptr)); free((yyvsp[-3].idname)); }
#line 1445 "y.tab.c"
    break;

  case 31: /* asgn_stmt: NAME '=' term ';'  */
#line 82 "miniC.y"
                            { (yyval.nptr) = createAsgn(createVar((yyvsp[-3].idname)), (yyvsp[-1].nptr)); free((yyvsp[-3].idname)); }
#line 1451 "y.tab.c"
    break;

  case 32: /* asgn_stmt: NAME '=' READ '(' ')' ';'  */
#line 83 "miniC.y"
                                    { (yyval.nptr) = createAsgn(createVar((yyvsp[-5].idname)), createCall((yyvsp[-3].idname))); free((yyvsp[-5].idname)); free((yyvsp[-3].idname)); }
#line 1457 "y.tab.c"
    break;

  case 33: /* expr: term ADD term  */
#line 85 "miniC.y"
                     {(yyval.nptr) = createBExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), add);}
#line 1463 "y.tab.c"
    break;

  case 34: /* expr: term SUB term  */
#line 86 "miniC.y"
                        {(yyval.nptr) = createBExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), sub);}
#line 1469 "y.tab.c"
    break;

  case 35: /* expr: term MUL term  */
#line 87 "miniC.y"
                        {(yyval.nptr) = createBExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), mul);}
#line 1475 "y.tab.c"
    break;

  case 36: /* expr: term DIV term  */
#line 88 "miniC.y"
                        {(yyval.nptr) = createBExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), divide);}
#line 1481 "y.tab.c"
    break;

  case 37: /* expr: SUB term  */
#line 89 "miniC.y"
                   { (yyval.nptr) = createUExpr((yyvsp[0].nptr), uminus);}
#line 1487 "y.tab.c"
    break;

  case 38: /* condition: term EQ term  */
#line 92 "miniC.y"
                         { (yyval.nptr) = createRExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), eq);}
#line 1493 "y.tab.c"
    break;

  case 39: /* condition: term GT term  */
#line 93 "miniC.y"
                       { (yyval.nptr) = createRExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), gt);}
#line 1499 "y.tab.c"
    break;

  case 40: /* condition: term LT term  */
#line 94 "miniC.y"
                       { (yyval.nptr) = createRExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), lt);}
#line 1505 "y.tab.c"
    break;

  case 41: /* condition: term GEQ term  */
#line 95 "miniC.y"
                        { (yyval.nptr) = createRExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), ge);}
#line 1511 "y.tab.c"
    break;

  case 42: /* condition: term LEQ term  */
#line 96 "miniC.y"
                        { (yyval.nptr) = createRExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), le);}
#line 1517 "y.tab.c"
    break;


#line 1521 "y.tab.c"

      default: break;
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
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 98 "miniC.y"




void yyerror(const char *){
	fprintf(stdout, "Syntax error %d\n", yylineno);
}

