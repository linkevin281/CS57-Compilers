%{
#include <stdio.h>
#include "libraries/ast.h"
#include <math.h>
#include "y.tab.h"
%}

%option yylineno
letter [a-zA-Z]
alphanum [a-zA-Z0-9]

%%
"extern" {printf("%s",yytext);
		return EXTERN;}
"int"    {printf("%s",yytext);
		return TYPE;}
"void"   {printf("%s",yytext);
		return TYPE;}
"float"  {printf("%s",yytext);
		return TYPE;}
"return" {printf("%s",yytext);
		return RETURN;}
"if"     {printf("%s",yytext);
		return IF;}
"else"   {printf("%s",yytext);
		return ELSE;}
"while" {printf("%s",yytext);
		return WHILE;}
"print" { yylval.idname = strdup("Print"); 
		return PRINT;}
"read"  { yylval.idname = strdup("Read");
		return READ;}
{letter}{alphanum}* {yylval.idname = strdup(yytext);
		return NAME;}
[0-9]+  { yylval.ival = atoi(yytext);
		return NUMBER;}
"=" 	{printf("%s",yytext);
		return yytext[0];}
"==" 	{printf("%s",yytext);
		return EQ;}
">"     {printf("%s",yytext);
		return GT;}
"<"     {printf("%s",yytext);
		return LT;}
">="    {printf("%s",yytext);
		return GEQ;}
"<="    {printf("%s",yytext);
		return LEQ;}
"("		{printf("%s",yytext);
		return yytext[0];}
")"		{printf("%s",yytext);
		return yytext[0];}
"+"		{printf("%s",yytext);
		return ADD;}
"-"		{printf("%s",yytext);
		return SUB;}
"*"		{printf("%s",yytext);
		return MUL;}
"/"		{printf("%s",yytext);
		return DIV;}
"{"		{printf("%s",yytext);
		return yytext[0];}	
"}"		{printf("%s",yytext);
		return yytext[0];}
";"		{printf("%s",yytext);
		return yytext[0];}
%%

int yywrap(){
	return 1;
}
