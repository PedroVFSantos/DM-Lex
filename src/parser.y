%code requires {
    #include "ast.hpp"
    #include "environment.hpp"
}

/* Código que vai direto no parser.tab.cpp */
%{
#include <iostream>
#include <string>

#include "ast.hpp"
#include "environment.hpp"

extern int yylex();
void yyerror(const char *s);

/* Variável global definida em main.cpp */
extern DynamicEnvironment env;
%}

%union {
    int num;
    char* id;
    Node* node;
}

%token <num> NUMBER
%token <id> ID
%token FUNC IF PRINT
%type <node> statement statements expression

%left '+'

%%
program:
    statements { if ($1) $1->execute(env); }
    ;

statements:
    statement { $$ = new BlockNode($1); }
    | statements statement {
        static_cast<BlockNode*>($1)->add($2);
        $$ = $1;
      }
    ;

statement:
    ID '=' expression ';'        { $$ = new AssignNode($1, $3); }
    | FUNC ID '{' statements '}' { env.registerFunc($2, $4); $$ = new NoOpNode(); }
    | ID '(' ')' ';'             { $$ = new CallNode($1); }
    | PRINT expression ';'       { $$ = new PrintNode($2); }
    | IF '(' expression ')' '{' statements '}' { $$ = new IfNode($3, $6); }
    ;

expression:
    NUMBER                       { $$ = new LiteralNode($1); }
    | ID                         { $$ = new AccessNode($1); }
    | expression '+' expression  { $$ = new AddNode($1, $3); }
    ;
%%

void yyerror(const char *s) {
    std::cerr << "Erro sintatico: " << s << std::endl;
}
