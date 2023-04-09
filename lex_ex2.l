%{
    #include <stdio.h>
    #include "y.tab.h"
%}

%%
[a-zA-Z]+ {return NAME;}
[0-9]+ { yylval = atoi(yytext);
         return NUM;}
":" {return yytext[0]}

%%
int yywrap(){
    return1;
}