%{
#include "symbol.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



extern FILE *yyin;
extern FILE *yyout;
extern int lineno;

extern int yylex();

void yyerror (const char *s) {
	fprintf(stderr, "There is a parse error at line %i: %s\n", lineno, s);
}

%}

%union{
	list_t* symtab_item;
    	  int number;
	  int intVal;
	  char* strVal;
	
	  
}


%token <intVal> NUM OTHER SEMICOLON IF WRITELN WRITE WHILE ELSE RETURNS BREAK READ COMMA COLON
%token <intVal> LPARN RPARN LEFTBRAC RIGHTBRAC LEFTCURLY RIGHTCURLY
%token <intVal> ADD MINUS MUL DIV EQUAL EQUALS NOTEQUAL LESSTHAN LESSTHANOREQ GREATERTHAN GREATERTHANOREQ AND OR EXCLAMATIONPT POWER

%token <symtab_item> ID
%token <intVal> CHAR INT DOUBLE BOOL
%token <strVal> STRING

%type <intVal> Type
/*
%type <number> NUM
%type <strVal> STRING

%type <strVal> IF
%type <strVal> WRITELN
%type <strVal> WRITE
%type <strVal> WHILE
%type <strVal> ELSE
%type <strVal> RETURNS
%type <strVal> BREAK
%type <strVal> READ

%type <name> LPARN
%type <name> RPARN
%type <name> LEFTBRAC
%type <name> RIGHTBRAC
%type <name> LEFTCURLY
%type <name> RIGHTCURLY
%type <name> ADD
%type <name> MINUS
%type <name> MUL
%type <name> DIV
%type <name> EQUAL
%type <name> EQUALS
%type <name> EXCLAMATIONPT
%type <name> POWER
%type <name> NOTEQUAL
%type <name> LESSTHAN
%type <name> LESSTHANOREQ
%type <name> GREATERTHAN
%type <name> GREATERTHANOREQ
%type <name> AND
%type <name> OR

%type <intVal> SEMICOLON
*/


%start Program




%%

Program: VarDeclList 
	| FunDeclList
;

VarDeclList: VarDecl VarDeclList { declare = 1;}
	| FunDeclList 
	| {}
;

VarDecl:  Type ID  { declare = 0;}  X1 
;

X1: SEMICOLON
	| LEFTBRAC NUM RIGHTBRAC SEMICOLON {printf("Variable Dec: X1 \n");}
;

FunDeclList: FunDecl X2
;

X2: FunDeclList 
	| {}
;

FunDecl:   Type ID LPARN { incrScope();} ParamDecList RPARN Block 
;

ParamDecList: {}
	| ParamDeclListTail
;

ParamDeclListTail: ParamDecl X3
;

ParamDecl:  Type ID X4 //{declare = 0;}
;

X3: {}
	| COMMA ParamDeclListTail {printf("ParamDeclListTail \n");}
;
X4: {}
	| LEFTBRAC RIGHTBRAC {printf("X4 \n");}
;	
Block: LEFTCURLY VarDeclList StmtList RIGHTCURLY {printf("Block \n");}
;

StmtList: Stmt X5 {printf("StmtList \n");}
;

X5: {}
	| StmtList
;

Stmt: Astmt SEMICOLON
	| RETURNS Expr SEMICOLON /* Expr */
	| READ ID SEMICOLON
	| WRITE Expr SEMICOLON /* Expr */
	| WRITELN SEMICOLON
	| BREAK SEMICOLON 
	| IF LPARN Expr RPARN Stmt ELSE Stmt {printf("IF Stmt \n");}
	| WHILE LPARN Expr RPARN Stmt {printf("WHILE Stmt \n");}
	| Block
;
/* WORKS FINE */

Astmt: ID X7 {printf("Assignment \n");}
;

Expr: Primary X6
	| UnaryOp Expr X6
;

X6: {}
	| BinOp Expr X6
;
X7: EQUAL Expr X6 
	| LEFTBRAC Expr RIGHTBRAC EQUAL Expr X6
;

Primary: ID X8
	| NUM
	| LPARN Expr RPARN
;

X8: {}
	| LPARN ExprList RPARN
	| LEFTBRAC Expr RIGHTBRAC
;

ExprList: {}
	| ExprListTail
;

ExprListTail: Expr X9
;

X9: {}
	| COMMA ExprListTail

UnaryOp: MINUS
		| EXCLAMATIONPT
;

BinOp: ADD
	| MINUS
	| MUL
	| DIV
	| EQUALS
	| NOTEQUAL
	| GREATERTHAN
	| GREATERTHANOREQ
	| LESSTHAN
	| LESSTHANOREQ
	| AND
	| OR
	| EQUAL

;
Type:	INT {setType(1);}
	|CHAR {setType(8);}
	|BOOL {setType(9);}
	|DOUBLE {setType(10);}
%%


int main(int argc, char *argv[])
{	
	InitHashTable();
	int flag;
	yyin = fopen(argv[1], "r");
				printf("this workingplg?\n");

	flag = yyparse();

	fclose(yyin);
	
	printf("Parsing finished!");
	
	// symbol table dump
	yyout = fopen("symtab_dump.out", "w");

	


	
	build_symtab(yyout);
	
	fclose(yyout);

	return flag;
} 
