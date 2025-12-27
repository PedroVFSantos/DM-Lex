%{
#include <cstring>
#include <cstdlib>
#include "parser.tab.hpp"

extern YYSTYPE yylval;
%}

%%
"func"  { return FUNC; }
"if"    { return IF; }
"print" { return PRINT; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.id = strdup(yytext); return ID; }
[0-9]+  { yylval.num = atoi(yytext); return NUMBER; }
[ \t\n] ;
[-+*/=(){};] { return yytext[0]; }
.       { printf("Erro lexico: %s\n", yytext); }
%%

int yywrap() { return 1; }