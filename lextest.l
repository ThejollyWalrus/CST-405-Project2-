%option noyywrap
%{
//Mason Hamilton
//CST-405


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symbol.h"
#include "TheParser.tab.h"
extern FILE *yyin;
extern FILE *yyout;



int lineno = 1;

void ret_print(char *token_type);




%}

%x ML_COMMENT

alpha     [a-zA-Z]+
digit     [0-9]+
alnum     {alpha}|{digit}
print     [ -~]

ID        {alpha}+{alnum}*
STRING    \"{print}*\"

%%



return		{return RETURNS;}
read		{return READ;}
write		{return WRITE;}
writeln		{return WRITELN;}
break		{return BREAK;}
if		{return IF;}
while		{return WHILE;}
else		{return ELSE;}

"("		{return LPARN;}
")"	 	{return RPARN;}

"{"		{return LEFTCURLY;} 
"}" 		{return RIGHTCURLY;} 

"["		{return LEFTBRAC;} 
"]" 		{return RIGHTBRAC;} 

"=" 		{return EQUAL;}
"+" 		{return ADD;}
"-" 		{return MINUS;}
"*" 		{return MUL;}
"/" 		{return DIV;}
"^" 		{return POWER;}

">"		{return GREATERTHAN;}
"<"		{return LESSTHAN;}
"<="		{return LESSTHANOREQ;}
">="		{return GREATERTHANOREQ;}
"=="		{return EQUALS;}
"!="		{return NOTEQUAL;}
"&&"		{return AND;}
"||"		{return OR;}


";" 		{return SEMICOLON;}
"," 		{return COMMA;}
":" 		{return COLON;}
"!" 		{return EXCLAMATIONPT;}



"char"		{return CHAR;}
"int"		{return INT;}
"bool"		{return BOOL;}
"double" 	{return DOUBLE;}


{ID}    {
	
	
        // insert identifier into symbol table
	lineno++;
        Insert_v(yytext, strlen(yytext), lineno);
        yylval.symtab_item = LookUp(yytext);
		
        return ID;
        }

{digit} { return NUM;}
		/*
{STRING}    { yylval.strVal = malloc(yyleng * sizeof(char));
              strcpy(yylval.strVal, yytext);  return STRING; }
			*/  





%%
