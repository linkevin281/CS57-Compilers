%token EXTERN TYPE RETURN IF ELSE WHILE PRINT NAME NUMBER COND_OP ARITH_OP READ

%{
#include <stdio.h>
void yyerror(const char *);
extern int yylex();
extern int yylex_destroy();
extern FILE *yyin;
extern int yylineno;
extern char* yytext;
%}

%start CFILE
%%
CFILE : STATEMENTS

PARAMETER : TYPE NAME 

EXTERN_FUNC : EXTERN TYPE READ '(' ')'';' 
            | EXTERN TYPE PRINT '(' TYPE ')'';'

STATEMENT : EXTERN_FUNC
            | FUNCTION
            | ASSIGNMENT_STATEMENT
            | IF_STATEMENT
            | PRINT_STATEMENT
            | READ_STATEMENT
            | WHILE_STATEMENT
            | RETURN_STATEMENT

FUNCTION : PARAMETER '(' PARAMETER ')' '{' STATEMENTS '}'';'

STATEMENTS : STATEMENTS STATEMENT 
            | STATEMENT

ASSIGNMENT_STATEMENT : PARAMETER ';'
            | NAME '=' EXPRESSION ';'
            | NAME '=' NAME ';'
            | NAME '=' NUMBER ';'

EXPRESSION : NAME ARITH_OP NAME 
            | NAME ARITH_OP NUMBER 
            | NUMBER ARITH_OP NAME 
            | NUMBER ARITH_OP NUMBER

IF_STATEMENT : IF '(' CONDITION ')' '{' STATEMENTS '}' ELSE '{' STATEMENTS '}'
            | IF '(' CONDITION ')' '{' STATEMENTS '}'

CONDITION : NAME COND_OP NAME 
            | NAME COND_OP NUMBER 
            | NUMBER COND_OP NAME 
            | NUMBER COND_OP NUMBER
        
PRINT_STATEMENT : PRINT '(' NAME ')'';'
            | PRINT '(' NUMBER ')'';'
            | PRINT '(' EXPRESSION ')'';'

READ_STATEMENT : READ '('')'';'

WHILE_STATEMENT : WHILE '(' CONDITION ')' '{' STATEMENTS '}'

RETURN_STATEMENT : RETURN EXPRESSION';' 
            | RETURN';'
            | RETURN '(' EXPRESSION ')' ';'

            

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
