%{
#include <cstring>
#include <cstdlib>
#include <cstdio>

#include "parser.tab.hpp"

extern YYSTYPE yylval;
%}

%%

[ \t\r\n]+ ;

"//".* ;

"func"  { return FUNC; }
"if"    { return IF; }
"print" { return PRINT; }

[0-9]+ {
    yylval.num = atoi(yytext);
    return NUMBER;
}

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.id = strdup(yytext);
    return ID;
}

"=" { return '='; }
"+" { return '+'; }
"(" { return '('; }
")" { return ')'; }
"{" { return '{'; }
"}" { return '}'; }
";" { return ';'; }

. {
    printf("Erro lexico: %s\n", yytext);
}

%%

int yywrap() {
    return 1;
}
