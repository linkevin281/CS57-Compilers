%{
#include<stdio.h>
int count_words=0;
int count_nums=0;
%}
%%
\ball\b

\$\([a-zA-Z]+\)\.[a-zA-Z]+ {
	printf("%s", yytext);
}
\b[a-zA-Z]+(_?[a-zA-Z0-9]+)*(\.)*\b {
	printf("%s", yytext);
}

[0-9]+ {count_nums++;}
.|[ \t\n]
%%

int yywrap(){
	return(1);
}

int main(){
	yylex();
	printf("Words:%d, Nums:%d\n",count_words, count_nums);
	return(0);
}

