%token FNAME FLAG EXT TAB COMND
%token EXTERN INT FLOAT RETURN IF ELSE PRINT NAME NUMBER EQUALITY 
%{
#include <stdio.h>
void yyerror(const char *);
extern int yylex();
extern int yylex_destroy();
extern FILE *yyin;
extern int yylineno;
extern char* yytext;
%}

%start MAKEFILE
%%

MAKEFILE : DECLARATION TARGET CLEAN | DECLARATION TARGET | DECLARATION CLEAN | DECLARATION
DECLARATION : FNAME '=' FNAME | FNAME '=' FNAME '.'	EXT 
FPATH : '$' '(' FNAME ')' '.' EXT | FNAME '.' EXT
FPATHS : FPATHS FPATH | FPATH
TARGET : FPATH ':' FPATHS '\n' COMMANDS
FLAGS : FLAGS FLAG | FLAG
COMMAND : TAB COMND FLAGS FPATHS '\n'
COMMANDS : COMMANDS COMMAND | COMMAND
CLEAN : FNAME ':' '\n' COMMANDS

%%

int main(int argc, char** argv){
	if (argc == 2){
		yyin = fopen(argv[1], "r");
	}

	yyparse();

	if (yyin != stdin)
		fclose(yyin);

	yylex_destroy();
	
	return 0;
}


void yyerror(const char *){
	fprintf(stdout, "Syntax error %d\n", yylineno);
}
