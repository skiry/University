/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

#ifndef YY_YY_YACC_TAB_H_INCLUDED
# define YY_YY_YACC_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     BEGINN = 258,
     CONST = 259,
     PRINT = 260,
     READ = 261,
     THEN = 262,
     VAR = 263,
     identifier = 264,
     constant = 265,
     startprogram = 266,
     endprogram = 267,
     ASSIGN = 268,
     GT = 269,
     LT = 270,
     GE = 271,
     LE = 272,
     EQ = 273,
     DIFF = 274,
     POW = 275,
     MUL = 276,
     DIV = 277,
     ADD = 278,
     SUB = 279,
     CBO = 280,
     CBC = 281,
     CPO = 282,
     CPC = 283,
     OPO = 284,
     OPC = 285,
     DD = 286,
     COMMA = 287,
     IF = 288,
     ELSE = 289,
     read = 290,
     write = 291,
     true = 292,
     false = 293,
     declare = 294,
     and = 295,
     or = 296,
     DO = 297,
     WHILE = 298,
     integer = 299,
     CHAR = 300,
     string = 301,
     array = 302,
     mainf = 303,
     give = 304,
     ID = 305,
     CONST_INT = 306,
     CONST_REAL = 307,
     CONST_CAR = 308,
     CONST_SIR = 309,
     INTEGER = 310,
     REAL = 311,
     ATRIB = 312,
     NE = 313,
     MOD = 314,
     OR = 315,
     AND = 316,
     NOT = 317
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 21 "yacc.y"

  	int l_val;
	char *p_val;


/* Line 2058 of yacc.c  */
#line 125 "yacc.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_YACC_TAB_H_INCLUDED  */
