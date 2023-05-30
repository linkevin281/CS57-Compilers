// Kevin Lin
// main function for the miniC compiler
// 05/07/2023


/* Includes */
#include "Frontend/semantic_analysis.h"
#include <string.h>
#include <stdio.h>
#include <deque>
#include <set>

/* External variables */
extern void yyparse();
extern int yylex();
extern int yylex_destroy();
extern bool semantic_analysis(astNode*);
extern FILE *yyin;
extern int yylineno;
extern char* yytext;

/* Global variables */
astNode* root;


/* Main */

int main(int argc, char** argv){
	if (argc == 2){
		yyin = fopen(argv[1], "r");
	}

	yyparse();

    printf("Semantic Analysis: ======================\n");
    if (semantic_analysis(root)) {
        printf("RESULT: =======No errors found=======\n");
    }
    else {
        printf("RESULT: =======Errors found=======\n"); 
    }

    freeNode(root);

	if (yyin != stdin)
		fclose(yyin);

	yylex_destroy();
	
	return 0;
}

