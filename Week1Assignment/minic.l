%{
#include <stdio.h>
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
"print"  {printf("%s",yytext);
		return PRINT;}
"read"   {printf("%s",yytext);
		return READ;}
{letter}{alphanum}* {printf("%s",yytext);
		return NAME;}
[0-9]+  {printf("%s",yytext);
		return NUMBER;}
"=" 	{printf("%s",yytext);
		return yytext[0];}
"==" 	{printf("%s",yytext);
		return COND_OP;}
">"     {printf("%s",yytext);
		return COND_OP;}
"<"     {printf("%s",yytext);
		return COND_OP;}
">="    {printf("%s",yytext);
		return COND_OP;}
"<="    {printf("%s",yytext);
		return COND_OP;}
"("		{printf("%s",yytext);
		return yytext[0];}
")"		{printf("%s",yytext);
		return yytext[0];}
"+"		{printf("%s",yytext);
		return ARITH_OP;}
"-"		{printf("%s",yytext);
		return ARITH_OP;}
"*"		{printf("%s",yytext);
		return ARITH_OP;}
"/"		{printf("%s",yytext);
		return ARITH_OP;}
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
