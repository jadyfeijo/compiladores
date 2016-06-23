/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    KW_INT = 258,
    KW_REAL = 259,
    KW_BOOL = 260,
    KW_CHAR = 261,
    KW_IF = 262,
    KW_ELSE = 263,
    KW_WHILE = 264,
    KW_INPUT = 265,
    KW_RETURN = 266,
    KW_OUTPUT = 267,
    OPERATOR_LE = 268,
    OPERATOR_GE = 269,
    OPERATOR_EQ = 270,
    OPERATOR_NE = 271,
    OPERATOR_AND = 272,
    OPERATOR_OR = 273,
    TK_IDENTIFIER = 274,
    LIT_INTEGER = 275,
    LIT_FALSE = 276,
    LIT_TRUE = 277,
    LIT_CHAR = 278,
    LIT_STRING = 279,
    TOKEN_ERROR = 280
  };
#endif
/* Tokens.  */
#define KW_INT 258
#define KW_REAL 259
#define KW_BOOL 260
#define KW_CHAR 261
#define KW_IF 262
#define KW_ELSE 263
#define KW_WHILE 264
#define KW_INPUT 265
#define KW_RETURN 266
#define KW_OUTPUT 267
#define OPERATOR_LE 268
#define OPERATOR_GE 269
#define OPERATOR_EQ 270
#define OPERATOR_NE 271
#define OPERATOR_AND 272
#define OPERATOR_OR 273
#define TK_IDENTIFIER 274
#define LIT_INTEGER 275
#define LIT_FALSE 276
#define LIT_TRUE 277
#define LIT_CHAR 278
#define LIT_STRING 279
#define TOKEN_ERROR 280

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 85 "parser.y" /* yacc.c:1909  */

	HASH_NODE * symbol;
	ASTREE * astree;

#line 109 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
