#include "environment.hpp"
#include "ast.hpp"

#include <stdexcept>

/* Construtor */
DynamicEnvironment::DynamicEnvironment() {
    stack.emplace_back(); // Escopo global
}

/* Cria novo escopo dinâmico */
void DynamicEnvironment::pushScope() {
    stack.emplace_back();
}

/* Remove escopo atual */
void DynamicEnvironment::popScope() {
    if (stack.size() > 1) {
        stack.pop_back();
    }
}

/* Declara ou atualiza variável no escopo atual */
void DynamicEnvironment::declareVar(const std::string& name, int value) {
    stack.back()[name] = value;
}

/* Registra função (escopo dinâmico: corpo sem ambiente capturado) */
void DynamicEnvironment::registerFunc(const std::string& name, Node* body) {
    functions[name] = body;
}

/* Recupera função */
Node* DynamicEnvironment::getFunc(const std::string& name) {
    auto it = functions.find(name);
    if (it != functions.end()) {
        return it->second;
    }
    throw std::runtime_error("Erro: Funcao '" + name + "' nao definida.");
}

/* Busca variável respeitando escopo dinâmico */
int DynamicEnvironment::lookup(const std::string& name) const {
    // Busca do topo da pilha para a base
    for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
        auto var = it->find(name);
        if (var != it->end()) {
            return var->second;
        }
    }
    throw std::runtime_error("Erro: Variavel '" + name + "' nao encontrada.");
}
