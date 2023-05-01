
%{
#include "libraries/ast.h"
#include "semantic_analysis.h"
#include <stdio.h>
void yyerror(const char *);
extern int yylex();
extern int yylex_destroy();
extern bool semantic_analysis(astNode*);
extern FILE *yyin;
extern int yylineno;
extern char* yytext;
astNode* root;
%}

%union {
        int ival;
        char* idname;
        astNode *nptr;
        vector<astNode *> *svec_ptr;
} 

%token EXTERN TYPE RETURN IF ELSE WHILE
%token ADD SUB MUL DIV
%token EQ GT LT GEQ LEQ

%token <ival> NUMBER 
%token <idname> NAME PRINT READ 
%type <svec_ptr> stmts var_decls
%type <nptr> stmt expr term block_stmt decl function_def extern program
%type <nptr> asgn_stmt if_stmt while_loop call_stmt return_stmt condition if_else_stmt

%nonassoc IFX
%nonassoc ELSE

%start program
%%

program : extern extern function_def {$$ = createProg($1, $2, $3); root = $$;}

extern : EXTERN TYPE READ '(' ')' ';' {$$ = createExtern($3); free($3);}
        | EXTERN TYPE PRINT '(' TYPE ')' ';' {$$ = createExtern($3); free($3);}

function_def : TYPE NAME '(' TYPE NAME ')' block_stmt {$$ = createFunc($2, createVar($5), $7); free($2); free($5);}
        | TYPE NAME '(' ')' block_stmt {$$ = createFunc($2, NULL, $5); free($2);}

block_stmt : '{' var_decls stmts '}' {$2->insert($2->end(),  $3->begin(), $3->end()); delete($3); $$ = createBlock($2);}
        | '{' stmts '}' {$$ = createBlock($2);}

var_decls : var_decls decl {$$ = $1; $$->push_back($2);}
        | decl {$$ = new vector<astNode *>(); $$->push_back($1);}

decl : TYPE NAME ';' {$$ = createDecl($2); free($2);}

stmts : stmts stmt {$$ = $1; $$->push_back($2);}
        | stmt {$$ = new vector<astNode *>(); $$->push_back($1);}

stmt : asgn_stmt { $$ = $1;}
        | if_stmt { $$ = $1;}
        | if_else_stmt { $$ = $1;}
        | while_loop { $$ = $1;}
        | block_stmt { $$ = $1;}
        | call_stmt { $$ = $1;}
        | return_stmt { $$ = $1;}

if_stmt: IF '(' condition ')' stmt %prec IFX { $$ = createIf($3, $5, NULL);} 

if_else_stmt: IF '(' condition ')' stmt ELSE stmt { $$ = createIf($3, $5, $7);}

while_loop : WHILE '(' condition ')' stmt {$$ = createWhile($3, $5);}

call_stmt : PRINT '(' NAME ')'';' { $$ = createCall($1, createVar($3)); free($1); free($3);}
        | READ '('')'';' { $$ = createCall($1, NULL); free($1);}

return_stmt : RETURN '(' expr ')' ';' { $$ = createRet($3);}
        | RETURN term ';' { $$ = createRet($2);}

term : NAME {$$ = createVar($1); free($1);}
        | NUMBER {$$ = createCnst($1);}

asgn_stmt : NAME '=' expr ';' { $$ = createAsgn(createVar($1), $3); free($1); }
        | NAME '=' term ';' { $$ = createAsgn(createVar($1), $3); free($1); }
	| NAME '=' READ '(' ')' ';' { $$ = createAsgn(createVar($1), createCall($3)); free($1); free($3); }

expr : term ADD term {$$ = createBExpr($1, $3, add);} 
        | term SUB term {$$ = createBExpr($1, $3, sub);} 
        | term MUL term {$$ = createBExpr($1, $3, mul);}
        | term DIV term {$$ = createBExpr($1, $3, divide);}
        | SUB term { $$ = createUExpr($2, uminus);}


condition : term EQ term { $$ = createRExpr($1, $3, eq);}
        | term GT term { $$ = createRExpr($1, $3, gt);}
        | term LT term { $$ = createRExpr($1, $3, lt);}
        | term GEQ term { $$ = createRExpr($1, $3, ge);}
        | term LEQ term { $$ = createRExpr($1, $3, le);}

%%

int main(int argc, char** argv){
	if (argc == 2){
		yyin = fopen(argv[1], "r");
	}

	yyparse();

        printf("AST: ======================\n");
        printNode(root);

        printf("Semantic Analysis: ======================\n");
        if (semantic_analysis(root)) {
            printf("RESULT: =======No errors found=======\n");
        }
        else {
            printf("RESULT: =======Errors found=======\n"); 
        }

        freeNode(root);
        // testing: create a blockstatement node 
        /* astNode* stmt1 = createDecl("a");
        astNode* stmt2 = createDecl("b");
        astNode* block = createBlock(new vector<astNode*>({stmt1, stmt2}));

        semantic_analysis(block); */

	if (yyin != stdin)
		fclose(yyin);

	yylex_destroy();
	
	return 0;
}

void yyerror(const char *){
	fprintf(stdout, "Syntax error %d\n", yylineno);
}

