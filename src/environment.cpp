#include "../include/environment.hpp"
#include "../include/ast.hpp"

DynamicEnvironment::DynamicEnvironment() {
    stack.push_back({}); // Escopo Global
}

void DynamicEnvironment::pushScope() {
    stack.push_back({});
}

void DynamicEnvironment::popScope() {
    if (stack.size() > 1) stack.pop_back();
}

void DynamicEnvironment::declareVar(std::string name, int value) {
    stack.back()[name] = value;
}

void DynamicEnvironment::registerFunc(std::string name, Node* body) {
    functions[name] = body;
}

Node* DynamicEnvironment::getFunc(std::string name) {
    if (functions.count(name)) return functions[name];
    throw std::runtime_error("Erro: Funcao '" + name + "' nao definida.");
}

int DynamicEnvironment::lookup(std::string name) {
    // REGRA DO ESCOPO DINÂMICO: Busca do topo para a base da pilha
    for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
        if (it->count(name)) return it->at(name);
    }
    throw std::runtime_error("Erro: Variavel '" + name + "' nao encontrada.");
}