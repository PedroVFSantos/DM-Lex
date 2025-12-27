#include "environment.hpp"
#include "parser.tab.hpp"

DynamicEnvironment env; // Definição única

int main() {
    return yyparse();
}