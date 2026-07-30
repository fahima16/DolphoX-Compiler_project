/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../ast/ast.h"

extern int yylex();
extern int yylineno;
void yyerror(const char *s);

ASTNode *root = NULL;


/* Line 189 of yacc.c  */
#line 87 "parser/parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     STRING_LIT = 259,
     CHAR_LIT = 260,
     INT_LIT = 261,
     FLOAT_LIT = 262,
     DOUBLE_LIT = 263,
     TRUE = 264,
     FALSE = 265,
     INT = 266,
     FLOAT = 267,
     DOUBLE = 268,
     CHAR = 269,
     STRING = 270,
     BOOL = 271,
     IF = 272,
     ELSE = 273,
     WHILE = 274,
     FOR = 275,
     PRINT = 276,
     READ = 277,
     FUNCTION = 278,
     RETURN = 279,
     EQ = 280,
     NE = 281,
     LE = 282,
     GE = 283,
     AND = 284,
     OR = 285,
     INC = 286,
     DEC = 287,
     ADD_ASSIGN = 288,
     SUB_ASSIGN = 289,
     MUL_ASSIGN = 290,
     DIV_ASSIGN = 291,
     LOWER_THAN_ELSE = 292
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 15 "parser/parser.y"

    char cval;
    int ival;
    float fval;
    double dval;
    bool bval;
    char* sval;
    struct ASTNode* node;



/* Line 214 of yacc.c  */
#line 172 "parser/parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 184 "parser/parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   480

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNRULES -- Number of states.  */
#define YYNSTATES  160

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,     2,     2,    44,     2,     2,
      47,    48,    42,    40,    49,    41,     2,    43,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    46,
      38,    50,    39,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    51,     2,    52,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    53,     2,    54,     2,     2,     2,     2,
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
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    12,    15,    18,    21,
      23,    25,    27,    29,    31,    33,    40,    48,    52,    55,
      57,    61,    64,    67,    69,    71,    73,    75,    77,    79,
      83,    85,    87,    91,    96,   100,   104,   108,   112,   116,
     123,   126,   131,   134,   139,   145,   153,   159,   169,   179,
     183,   185,   187,   189,   191,   193,   195,   197,   199,   202,
     205,   210,   214,   219,   223,   227,   231,   235,   239,   243,
     247,   251,   255,   259,   263,   267,   271,   275,   277
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      56,     0,    -1,    57,    -1,    57,    58,    -1,    -1,    63,
      46,    -1,    67,    46,    -1,    68,    46,    -1,    69,    46,
      -1,    70,    -1,    71,    -1,    72,    -1,    73,    -1,    59,
      -1,    60,    -1,    23,    64,     3,    47,    48,    73,    -1,
      23,    64,     3,    47,    61,    48,    73,    -1,    24,    74,
      46,    -1,    24,    46,    -1,    62,    -1,    61,    49,    62,
      -1,    64,     3,    -1,    64,    65,    -1,    11,    -1,    12,
      -1,    13,    -1,    14,    -1,    15,    -1,    16,    -1,    65,
      49,    66,    -1,    66,    -1,     3,    -1,     3,    50,    74,
      -1,     3,    51,     6,    52,    -1,     3,    50,    74,    -1,
       3,    33,    74,    -1,     3,    34,    74,    -1,     3,    35,
      74,    -1,     3,    36,    74,    -1,     3,    51,    74,    52,
      50,    74,    -1,    22,     3,    -1,    22,    47,     3,    48,
      -1,    21,    74,    -1,    21,    47,    74,    48,    -1,    17,
      47,    74,    48,    58,    -1,    17,    47,    74,    48,    58,
      18,    58,    -1,    19,    47,    74,    48,    58,    -1,    20,
      47,    67,    46,    74,    46,    74,    48,    58,    -1,    20,
      47,    67,    46,    74,    46,    67,    48,    58,    -1,    53,
      57,    54,    -1,     6,    -1,     7,    -1,     8,    -1,     5,
      -1,     4,    -1,     9,    -1,    10,    -1,     3,    -1,     3,
      31,    -1,     3,    32,    -1,     3,    51,    74,    52,    -1,
       3,    47,    48,    -1,     3,    47,    75,    48,    -1,    74,
      40,    74,    -1,    74,    41,    74,    -1,    74,    42,    74,
      -1,    74,    43,    74,    -1,    74,    44,    74,    -1,    74,
      25,    74,    -1,    74,    26,    74,    -1,    74,    27,    74,
      -1,    74,    28,    74,    -1,    74,    29,    74,    -1,    74,
      30,    74,    -1,    74,    38,    74,    -1,    74,    39,    74,
      -1,    47,    74,    48,    -1,    74,    -1,    75,    49,    74,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    52,    52,    59,    69,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    86,    93,   103,   107,   113,
     114,   123,   132,   145,   146,   147,   148,   149,   150,   154,
     162,   168,   172,   183,   191,   192,   193,   194,   195,   196,
     207,   208,   212,   213,   217,   222,   231,   239,   246,   256,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   293,   294
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "STRING_LIT", "CHAR_LIT",
  "INT_LIT", "FLOAT_LIT", "DOUBLE_LIT", "TRUE", "FALSE", "INT", "FLOAT",
  "DOUBLE", "CHAR", "STRING", "BOOL", "IF", "ELSE", "WHILE", "FOR",
  "PRINT", "READ", "FUNCTION", "RETURN", "EQ", "NE", "LE", "GE", "AND",
  "OR", "INC", "DEC", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN",
  "DIV_ASSIGN", "LOWER_THAN_ELSE", "'<'", "'>'", "'+'", "'-'", "'*'",
  "'/'", "'%'", "'!'", "';'", "'('", "')'", "','", "'='", "'['", "']'",
  "'{'", "'}'", "$accept", "program", "statement_list", "statement",
  "function_def", "return_stmt", "param_list", "param", "declaration_stmt",
  "type", "id_list", "declarator", "assignment_stmt", "read_stmt",
  "print_stmt", "if_stmt", "while_stmt", "for_stmt", "block_stmt", "expr",
  "arg_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,    60,    62,
      43,    45,    42,    47,    37,    33,    59,    40,    41,    44,
      61,    91,    93,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    57,    57,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    59,    59,    60,    60,    61,
      61,    62,    63,    64,    64,    64,    64,    64,    64,    65,
      65,    66,    66,    66,    67,    67,    67,    67,    67,    67,
      68,    68,    69,    69,    70,    70,    71,    72,    72,    73,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    75,    75
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     6,     7,     3,     2,     1,
       3,     2,     2,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     3,     4,     3,     3,     3,     3,     3,     6,
       2,     4,     2,     4,     5,     7,     5,     9,     9,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       4,     3,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,     0,    23,    24,    25,    26,    27,
      28,     0,     0,     0,     0,     0,     0,     0,     4,     3,
      13,    14,     0,     0,     0,     0,     0,     9,    10,    11,
      12,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      57,    54,    53,    50,    51,    52,    55,    56,     0,    42,
      40,     0,     0,    18,     0,     0,     0,     5,    31,    22,
      30,     6,     7,     8,    35,    36,    37,    38,    34,     0,
       0,     0,     0,    58,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    17,    49,     0,     0,     0,     0,
       0,     0,     0,    61,    77,     0,     0,    76,    68,    69,
      70,    71,    72,    73,    74,    75,    63,    64,    65,    66,
      67,    41,     0,    76,    32,     0,    29,     0,    44,    46,
       0,    62,     0,    60,     0,     0,    19,     0,    33,    39,
       0,     0,    78,    15,     0,     0,    21,    45,    57,     0,
       0,    16,    20,     0,     0,     0,     0,    48,    47,    60
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    19,    20,    21,   135,   136,    22,    23,
      59,    60,    24,    25,    26,    27,    28,    29,    30,    49,
     105
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -132
static const yytype_int16 yypact[] =
{
    -132,     7,    79,  -132,   411,  -132,  -132,  -132,  -132,  -132,
    -132,   -36,   -35,   -25,   142,     5,   143,   134,  -132,  -132,
    -132,  -132,   -10,    26,    -1,    29,    32,  -132,  -132,  -132,
    -132,   159,   159,   159,   159,   159,   159,   159,   159,    81,
      80,  -132,  -132,  -132,  -132,  -132,  -132,  -132,   159,   388,
    -132,    83,    84,  -132,   159,   338,    27,  -132,   -41,    34,
    -132,  -132,  -132,  -132,   388,   388,   388,   388,   388,   157,
     218,   242,    51,  -132,  -132,   113,   159,   266,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,    57,    59,   290,  -132,  -132,   159,   102,    26,    63,
      79,    79,   159,  -132,   388,   -16,   190,    68,   436,   436,
      13,    13,   415,   395,    13,    13,   -38,   -38,  -132,  -132,
    -132,  -132,    12,  -132,   388,    73,  -132,   159,    91,  -132,
     360,  -132,   159,  -132,    75,    28,  -132,   123,  -132,   388,
      79,   167,   388,  -132,    75,   143,  -132,  -132,   361,    85,
     314,  -132,  -132,   159,    79,    79,   197,  -132,  -132,    63
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -132,  -132,   111,   -66,  -132,  -132,  -132,   -11,  -132,   -15,
    -132,    37,   -37,  -132,  -132,  -132,  -132,  -132,  -131,   -17,
    -132
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -44
static const yytype_int16 yytable[] =
{
      55,    52,    72,   143,    88,    89,    90,     3,    50,    96,
      97,    37,    38,   151,    64,    65,    66,    67,    68,    69,
      70,    71,    39,     5,     6,     7,     8,     9,    10,    58,
       4,    77,   131,   132,   128,   129,    57,    93,     5,     6,
       7,     8,     9,    10,    11,    61,    12,    13,    14,    15,
      16,    17,    51,    86,    87,    88,    89,    90,   104,   106,
     134,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   147,    62,   144,   145,    63,   124,
      18,    95,     4,    98,     4,   130,    91,    92,   157,   158,
       5,     6,     7,     8,     9,    10,    11,   102,    12,    13,
      14,    15,    16,    17,   149,   121,   122,   137,   125,   140,
     139,    73,    74,   127,   -43,   142,    40,    41,    42,    43,
      44,    45,    46,    47,   150,   138,   146,    75,    18,    56,
     137,    76,    18,   154,   152,   126,   156,    40,    41,    42,
      43,    44,    45,    46,    47,    40,    41,    42,    43,    44,
      45,    46,    47,     0,     5,     6,     7,     8,     9,    10,
      54,   103,    40,    41,    42,    43,    44,    45,    46,    47,
     148,    41,    42,    43,    44,    45,    46,    47,     0,     0,
      53,    54,    78,    79,    80,    81,    82,    83,     0,    48,
       0,     0,     0,     0,     0,    84,    85,    86,    87,    88,
      89,    90,     0,     0,     0,     0,    54,     0,     0,    99,
       0,     0,     0,     0,    54,    78,    79,    80,    81,    82,
      83,     0,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    84,    85,    86,    87,    88,
      89,    90,   133,    78,    79,    80,    81,    82,    83,   159,
       0,     0,     0,     0,     0,     0,    84,    85,    86,    87,
      88,    89,    90,     0,     0,     0,   100,    78,    79,    80,
      81,    82,    83,     0,     0,     0,     0,     0,     0,     0,
      84,    85,    86,    87,    88,    89,    90,     0,     0,     0,
     101,    78,    79,    80,    81,    82,    83,     0,     0,     0,
       0,     0,     0,     0,    84,    85,    86,    87,    88,    89,
      90,     0,     0,     0,   107,    78,    79,    80,    81,    82,
      83,     0,     0,     0,     0,     0,     0,     0,    84,    85,
      86,    87,    88,    89,    90,     0,     0,     0,   123,    78,
      79,    80,    81,    82,    83,     0,     0,     0,     0,     0,
       0,     0,    84,    85,    86,    87,    88,    89,    90,     0,
       0,     0,   155,    78,    79,    80,    81,    82,    83,     0,
       0,     0,     0,     0,     0,     0,    84,    85,    86,    87,
      88,    89,    90,     0,    94,    78,    79,    80,    81,    82,
      83,     0,    73,    74,    31,    32,    33,    34,    84,    85,
      86,    87,    88,    89,    90,     0,   141,     0,    75,     0,
       0,    35,   153,    78,    79,    80,    81,    82,    83,     0,
      78,    79,    80,    81,    82,     0,    84,    85,    86,    87,
      88,    89,    90,    84,    85,    86,    87,    88,    89,    90,
      78,    79,    80,    81,    31,    32,    33,    34,     0,     0,
       0,     0,     0,    84,    85,    86,    87,    88,    89,    90,
       0,    35,    36,    80,    81,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    84,    85,    86,    87,    88,    89,
      90
};

static const yytype_int16 yycheck[] =
{
      17,    16,    39,   134,    42,    43,    44,     0,     3,    50,
      51,    47,    47,   144,    31,    32,    33,    34,    35,    36,
      37,    38,    47,    11,    12,    13,    14,    15,    16,     3,
       3,    48,    48,    49,   100,   101,    46,    54,    11,    12,
      13,    14,    15,    16,    17,    46,    19,    20,    21,    22,
      23,    24,    47,    40,    41,    42,    43,    44,    75,    76,
      48,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,   140,    46,    48,    49,    46,    96,
      53,    54,     3,    49,     3,   102,     3,     3,   154,   155,
      11,    12,    13,    14,    15,    16,    17,    46,    19,    20,
      21,    22,    23,    24,   141,    48,    47,   122,     6,    18,
     127,    31,    32,    50,    46,   132,     3,     4,     5,     6,
       7,     8,     9,    10,   141,    52,     3,    47,    53,    18,
     145,    51,    53,    48,   145,    98,   153,     3,     4,     5,
       6,     7,     8,     9,    10,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    11,    12,    13,    14,    15,    16,
      47,    48,     3,     4,     5,     6,     7,     8,     9,    10,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      46,    47,    25,    26,    27,    28,    29,    30,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    47,    -1,    -1,    52,
      -1,    -1,    -1,    -1,    47,    25,    26,    27,    28,    29,
      30,    -1,    25,    26,    27,    28,    29,    30,    38,    39,
      40,    41,    42,    43,    44,    38,    39,    40,    41,    42,
      43,    44,    52,    25,    26,    27,    28,    29,    30,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    48,    25,    26,    27,
      28,    29,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      48,    25,    26,    27,    28,    29,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    48,    25,    26,    27,    28,    29,
      30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    48,    25,
      26,    27,    28,    29,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    48,    25,    26,    27,    28,    29,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      42,    43,    44,    -1,    46,    25,    26,    27,    28,    29,
      30,    -1,    31,    32,    33,    34,    35,    36,    38,    39,
      40,    41,    42,    43,    44,    -1,    46,    -1,    47,    -1,
      -1,    50,    51,    25,    26,    27,    28,    29,    30,    -1,
      25,    26,    27,    28,    29,    -1,    38,    39,    40,    41,
      42,    43,    44,    38,    39,    40,    41,    42,    43,    44,
      25,    26,    27,    28,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
      -1,    50,    51,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    56,    57,     0,     3,    11,    12,    13,    14,    15,
      16,    17,    19,    20,    21,    22,    23,    24,    53,    58,
      59,    60,    63,    64,    67,    68,    69,    70,    71,    72,
      73,    33,    34,    35,    36,    50,    51,    47,    47,    47,
       3,     4,     5,     6,     7,     8,     9,    10,    47,    74,
       3,    47,    64,    46,    47,    74,    57,    46,     3,    65,
      66,    46,    46,    46,    74,    74,    74,    74,    74,    74,
      74,    74,    67,    31,    32,    47,    51,    74,    25,    26,
      27,    28,    29,    30,    38,    39,    40,    41,    42,    43,
      44,     3,     3,    74,    46,    54,    50,    51,    49,    52,
      48,    48,    46,    48,    74,    75,    74,    48,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    48,    47,    48,    74,     6,    66,    50,    58,    58,
      74,    48,    49,    52,    48,    61,    62,    64,    52,    74,
      18,    46,    74,    73,    48,    49,     3,    58,     3,    67,
      74,    73,    62,    51,    48,    48,    74,    58,    58,    52
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1464 of yacc.c  */
#line 52 "parser/parser.y"
    { 
        root = create_node(NODE_PROGRAM); 
        root->left = (yyvsp[(1) - (1)].node); 
    ;}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 59 "parser/parser.y"
    {
        if ((yyvsp[(1) - (2)].node) == NULL) {
            (yyval.node) = (yyvsp[(2) - (2)].node);
        } else {
            ASTNode *curr = (yyvsp[(1) - (2)].node);
            while (curr->next != NULL) curr = curr->next;
            curr->next = (yyvsp[(2) - (2)].node);
            (yyval.node) = (yyvsp[(1) - (2)].node);
        }
    ;}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 69 "parser/parser.y"
    { (yyval.node) = NULL; ;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 73 "parser/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 74 "parser/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 75 "parser/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 76 "parser/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 77 "parser/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 78 "parser/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 79 "parser/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 80 "parser/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 81 "parser/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 82 "parser/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 86 "parser/parser.y"
    {
        (yyval.node) = create_node(NODE_FUNCTION_DEF);
        (yyval.node)->sval = strdup((yyvsp[(3) - (6)].sval));
        (yyval.node)->ival = (yyvsp[(2) - (6)].ival);
        (yyval.node)->left = NULL;
        (yyval.node)->right = (yyvsp[(6) - (6)].node);
    ;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 93 "parser/parser.y"
    {
        (yyval.node) = create_node(NODE_FUNCTION_DEF);
        (yyval.node)->sval = strdup((yyvsp[(3) - (7)].sval));
        (yyval.node)->ival = (yyvsp[(2) - (7)].ival);
        (yyval.node)->left = (yyvsp[(5) - (7)].node);
        (yyval.node)->right = (yyvsp[(7) - (7)].node);
    ;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 103 "parser/parser.y"
    {
        (yyval.node) = create_node(NODE_RETURN);
        (yyval.node)->left = (yyvsp[(2) - (3)].node);
    ;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 107 "parser/parser.y"
    {
        (yyval.node) = create_node(NODE_RETURN);
    ;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 113 "parser/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 114 "parser/parser.y"
    {
        ASTNode *curr = (yyvsp[(1) - (3)].node);
        while (curr->next != NULL) curr = curr->next;
        curr->next = (yyvsp[(3) - (3)].node);
        (yyval.node) = (yyvsp[(1) - (3)].node);
    ;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 123 "parser/parser.y"
    {
        (yyval.node) = create_node(NODE_DECLARATION);
        (yyval.node)->sval = strdup((yyvsp[(2) - (2)].sval));
        (yyval.node)->left = create_int_node((yyvsp[(1) - (2)].ival));
        (yyval.node)->is_parameter = 1;
    ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 132 "parser/parser.y"
    {
        ASTNode *curr = (yyvsp[(2) - (2)].node);
        while (curr != NULL) {
            if (curr->type == NODE_DECLARATION || curr->type == NODE_ARRAY_DECL) {
                curr->left = create_int_node((yyvsp[(1) - (2)].ival));
            }
            curr = curr->next;
        }
        (yyval.node) = (yyvsp[(2) - (2)].node);
    ;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 145 "parser/parser.y"
    { (yyval.ival) = INT; ;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 146 "parser/parser.y"
    { (yyval.ival) = FLOAT; ;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 147 "parser/parser.y"
    { (yyval.ival) = DOUBLE; ;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 148 "parser/parser.y"
    { (yyval.ival) = CHAR; ;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 149 "parser/parser.y"
    { (yyval.ival) = STRING; ;}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 150 "parser/parser.y"
    { (yyval.ival) = BOOL; ;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 154 "parser/parser.y"
    {
        ASTNode *curr = (yyvsp[(1) - (3)].node);
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = (yyvsp[(3) - (3)].node);
        (yyval.node) = (yyvsp[(1) - (3)].node);
    ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 162 "parser/parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    ;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 168 "parser/parser.y"
    {
        (yyval.node) = create_node(NODE_DECLARATION);
        (yyval.node)->sval = strdup((yyvsp[(1) - (1)].sval));
    ;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 172 "parser/parser.y"
    {
        ASTNode *decl = create_node(NODE_DECLARATION);
        decl->sval = strdup((yyvsp[(1) - (3)].sval));

        ASTNode *assign = create_node(NODE_ASSIGN);
        assign->left = create_id_node((yyvsp[(1) - (3)].sval));
        assign->right = (yyvsp[(3) - (3)].node);

        decl->next = assign;
        (yyval.node) = decl;
    ;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 183 "parser/parser.y"
    {
        (yyval.node) = create_node(NODE_ARRAY_DECL);
        (yyval.node)->sval = strdup((yyvsp[(1) - (4)].sval));
        (yyval.node)->ival = (yyvsp[(3) - (4)].ival);
    ;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 191 "parser/parser.y"
    { (yyval.node) = create_node(NODE_ASSIGN); (yyval.node)->left = create_id_node((yyvsp[(1) - (3)].sval)); (yyval.node)->right = (yyvsp[(3) - (3)].node); ;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 192 "parser/parser.y"
    { (yyval.node) = create_node(NODE_ASSIGN); (yyval.node)->left = create_id_node((yyvsp[(1) - (3)].sval)); (yyval.node)->right = create_bin_op("+", create_id_node((yyvsp[(1) - (3)].sval)), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 193 "parser/parser.y"
    { (yyval.node) = create_node(NODE_ASSIGN); (yyval.node)->left = create_id_node((yyvsp[(1) - (3)].sval)); (yyval.node)->right = create_bin_op("-", create_id_node((yyvsp[(1) - (3)].sval)), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 194 "parser/parser.y"
    { (yyval.node) = create_node(NODE_ASSIGN); (yyval.node)->left = create_id_node((yyvsp[(1) - (3)].sval)); (yyval.node)->right = create_bin_op("*", create_id_node((yyvsp[(1) - (3)].sval)), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 195 "parser/parser.y"
    { (yyval.node) = create_node(NODE_ASSIGN); (yyval.node)->left = create_id_node((yyvsp[(1) - (3)].sval)); (yyval.node)->right = create_bin_op("/", create_id_node((yyvsp[(1) - (3)].sval)), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 196 "parser/parser.y"
    { 
        (yyval.node) = create_node(NODE_ASSIGN); 
        ASTNode *arr = create_node(NODE_ARRAY_ACCESS);
        arr->sval = strdup((yyvsp[(1) - (6)].sval));
        arr->left = (yyvsp[(3) - (6)].node);
        (yyval.node)->left = arr; 
        (yyval.node)->right = (yyvsp[(6) - (6)].node); 
    ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 207 "parser/parser.y"
    { (yyval.node) = create_node(NODE_READ); (yyval.node)->left = create_id_node((yyvsp[(2) - (2)].sval)); ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 208 "parser/parser.y"
    { (yyval.node) = create_node(NODE_READ); (yyval.node)->left = create_id_node((yyvsp[(3) - (4)].sval)); ;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 212 "parser/parser.y"
    { (yyval.node) = create_node(NODE_PRINT); (yyval.node)->left = (yyvsp[(2) - (2)].node); ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 213 "parser/parser.y"
    { (yyval.node) = create_node(NODE_PRINT); (yyval.node)->left = (yyvsp[(3) - (4)].node); ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 217 "parser/parser.y"
    { 
        (yyval.node) = create_node(NODE_IF); 
        (yyval.node)->cond = (yyvsp[(3) - (5)].node);
        (yyval.node)->body = (yyvsp[(5) - (5)].node);
    ;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 222 "parser/parser.y"
    { 
        (yyval.node) = create_node(NODE_IF); 
        (yyval.node)->cond = (yyvsp[(3) - (7)].node);
        (yyval.node)->body = (yyvsp[(5) - (7)].node);
        (yyval.node)->else_body = (yyvsp[(7) - (7)].node);
    ;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 231 "parser/parser.y"
    { 
        (yyval.node) = create_node(NODE_WHILE); 
        (yyval.node)->cond = (yyvsp[(3) - (5)].node);
        (yyval.node)->body = (yyvsp[(5) - (5)].node);
    ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 239 "parser/parser.y"
    {
        (yyval.node) = create_node(NODE_FOR);
        (yyval.node)->init = (yyvsp[(3) - (9)].node);
        (yyval.node)->cond = (yyvsp[(5) - (9)].node);
        (yyval.node)->incr = (yyvsp[(7) - (9)].node);
        (yyval.node)->body = (yyvsp[(9) - (9)].node);
    ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 246 "parser/parser.y"
    {
        (yyval.node) = create_node(NODE_FOR);
        (yyval.node)->init = (yyvsp[(3) - (9)].node);
        (yyval.node)->cond = (yyvsp[(5) - (9)].node);
        (yyval.node)->incr = (yyvsp[(7) - (9)].node);
        (yyval.node)->body = (yyvsp[(9) - (9)].node);
    ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 256 "parser/parser.y"
    { 
        (yyval.node) = create_node(NODE_BLOCK); 
        (yyval.node)->left = (yyvsp[(2) - (3)].node); 
    ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 263 "parser/parser.y"
    { (yyval.node) = create_int_node((yyvsp[(1) - (1)].ival)); ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 264 "parser/parser.y"
    { (yyval.node) = create_float_node((yyvsp[(1) - (1)].fval)); ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 265 "parser/parser.y"
    { (yyval.node) = create_double_node((yyvsp[(1) - (1)].dval)); ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 266 "parser/parser.y"
    { (yyval.node) = create_char_node((yyvsp[(1) - (1)].cval)); ;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 267 "parser/parser.y"
    { (yyval.node) = create_string_node((yyvsp[(1) - (1)].sval)); ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 268 "parser/parser.y"
    { (yyval.node) = create_bool_node(true); ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 269 "parser/parser.y"
    { (yyval.node) = create_bool_node(false); ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 270 "parser/parser.y"
    { (yyval.node) = create_id_node((yyvsp[(1) - (1)].sval)); ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 271 "parser/parser.y"
    { (yyval.node) = create_node(NODE_BINARY_OP); (yyval.node)->op = strdup("++"); (yyval.node)->left = create_id_node((yyvsp[(1) - (2)].sval)); ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 272 "parser/parser.y"
    { (yyval.node) = create_node(NODE_BINARY_OP); (yyval.node)->op = strdup("--"); (yyval.node)->left = create_id_node((yyvsp[(1) - (2)].sval)); ;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 273 "parser/parser.y"
    { (yyval.node) = create_node(NODE_ARRAY_ACCESS); (yyval.node)->sval = strdup((yyvsp[(1) - (4)].sval)); (yyval.node)->left = (yyvsp[(3) - (4)].node); ;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 274 "parser/parser.y"
    { (yyval.node) = create_node(NODE_FUNCTION_CALL); (yyval.node)->sval = strdup((yyvsp[(1) - (3)].sval)); (yyval.node)->left = NULL; ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 275 "parser/parser.y"
    { (yyval.node) = create_node(NODE_FUNCTION_CALL); (yyval.node)->sval = strdup((yyvsp[(1) - (4)].sval)); (yyval.node)->left = (yyvsp[(3) - (4)].node); ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 276 "parser/parser.y"
    { (yyval.node) = create_bin_op("+", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 277 "parser/parser.y"
    { (yyval.node) = create_bin_op("-", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 278 "parser/parser.y"
    { (yyval.node) = create_bin_op("*", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 279 "parser/parser.y"
    { (yyval.node) = create_bin_op("/", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 280 "parser/parser.y"
    { (yyval.node) = create_bin_op("%", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 281 "parser/parser.y"
    { (yyval.node) = create_bin_op("==", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 282 "parser/parser.y"
    { (yyval.node) = create_bin_op("!=", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 283 "parser/parser.y"
    { (yyval.node) = create_bin_op("<=", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 284 "parser/parser.y"
    { (yyval.node) = create_bin_op(">=", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 285 "parser/parser.y"
    { (yyval.node) = create_bin_op("&&", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 286 "parser/parser.y"
    { (yyval.node) = create_bin_op("||", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 287 "parser/parser.y"
    { (yyval.node) = create_bin_op("<", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 288 "parser/parser.y"
    { (yyval.node) = create_bin_op(">", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); ;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 289 "parser/parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 293 "parser/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 294 "parser/parser.y"
    {
        ASTNode *curr = (yyvsp[(1) - (3)].node);
        while (curr->next != NULL) curr = curr->next;
        curr->next = (yyvsp[(3) - (3)].node);
        (yyval.node) = (yyvsp[(1) - (3)].node);
    ;}
    break;



/* Line 1464 of yacc.c  */
#line 2243 "parser/parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1684 of yacc.c  */
#line 302 "parser/parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error at line %d: %s\n", yylineno, s);
}
