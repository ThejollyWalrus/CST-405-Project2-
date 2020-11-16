/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_THEPARSER_TAB_H_INCLUDED
# define YY_YY_THEPARSER_TAB_H_INCLUDED
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
    NUM = 258,
    OTHER = 259,
    SEMICOLON = 260,
    IF = 261,
    WRITELN = 262,
    WRITE = 263,
    WHILE = 264,
    ELSE = 265,
    RETURNS = 266,
    BREAK = 267,
    READ = 268,
    COMMA = 269,
    COLON = 270,
    LPARN = 271,
    RPARN = 272,
    LEFTBRAC = 273,
    RIGHTBRAC = 274,
    LEFTCURLY = 275,
    RIGHTCURLY = 276,
    ADD = 277,
    MINUS = 278,
    MUL = 279,
    DIV = 280,
    EQUAL = 281,
    EQUALS = 282,
    NOTEQUAL = 283,
    LESSTHAN = 284,
    LESSTHANOREQ = 285,
    GREATERTHAN = 286,
    GREATERTHANOREQ = 287,
    AND = 288,
    OR = 289,
    EXCLAMATIONPT = 290,
    POWER = 291,
    ID = 292,
    CHAR = 293,
    INT = 294,
    DOUBLE = 295,
    BOOL = 296,
    STRING = 297
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 21 "TheParser.y" /* yacc.c:1909  */

	list_t* symtab_item;
    	  int number;
	  int intVal;
	  char* strVal;
	
	  

#line 106 "TheParser.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_THEPARSER_TAB_H_INCLUDED  */
