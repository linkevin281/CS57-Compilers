%{
    #include <stdio.h>
    extern int yylex();
    extern int yylex_destroy();w
    extern int yywrap();
    void yyerror();
%}

%union{
    int ival;
    char *name;
    double dval;
}
%token <ival> NUM
%token <name> NAME
%token <dval> DNUM

%start scores

%%
scores : scores : score {$$ = $1 + $2;}| 
         score {$$ = $1;}
score : NAME ':' NUM {$$ = $3;}
%%
int main(int argc, char** argv){
    if (argc == 2){
        yyin = fopen(argv[1], "r");
    }
    yyparse();
    fclose(yyin);
    yylex_destroy();
    return 0;
}

void yyerror() {
    fprintf(stderr, "syntax error\n");
}