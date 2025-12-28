#include "ast.hpp"
#include "environment.hpp"

#include <iostream>

/* ===== Literal ===== */
LiteralNode::LiteralNode(int v) : val(v) {}

int LiteralNode::execute(DynamicEnvironment& env) {
    return val;
}

/* ===== Acesso ===== */
AccessNode::AccessNode(const std::string& n) : name(n) {}

int AccessNode::execute(DynamicEnvironment& env) {
    return env.lookup(name);
}

/* ===== Atribuição ===== */
AssignNode::AssignNode(const std::string& n, Node* e)
    : name(n), expr(e) {}

int AssignNode::execute(DynamicEnvironment& env) {
    int v = expr->execute(env);
    env.declareVar(name, v);
    return v;
}

/* ===== Print ===== */
PrintNode::PrintNode(Node* e) : expr(e) {}

int PrintNode::execute(DynamicEnvironment& env) {
    int v = expr->execute(env);
    std::cout << "> " << v << std::endl;
    return v;
}

/* ===== Chamada de função (ESCOPO DINÂMICO) ===== */
CallNode::CallNode(const std::string& n) : name(n) {}

int CallNode::execute(DynamicEnvironment& env) {
    env.pushScope();                  // novo escopo dinâmico
    int res = env.getFunc(name)->execute(env);
    env.popScope();                   // remove escopo
    return res;
}

/* ===== If ===== */
IfNode::IfNode(Node* cond, Node* thenB)
    : condition(cond), thenBranch(thenB) {}

int IfNode::execute(DynamicEnvironment& env) {
    if (condition->execute(env) != 0) {
        env.pushScope();              // escopo do if
        int r = thenBranch->execute(env);
        env.popScope();
        return r;
    }
    return 0;
}

/* ===== Bloco ===== */
BlockNode::BlockNode(Node* first) {
    if (first) children.push_back(first);
}

void BlockNode::add(Node* n) {
    if (n) children.push_back(n);
}

int BlockNode::execute(DynamicEnvironment& env) {
    env.pushScope();                  // escopo do bloco
    int last = 0;
    for (auto c : children) {
        last = c->execute(env);
    }
    env.popScope();
    return last;
}

/* ===== Soma ===== */
AddNode::AddNode(Node* left, Node* right)
    : l(left), r(right) {}

int AddNode::execute(DynamicEnvironment& env) {
    return l->execute(env) + r->execute(env);
}

/* ===== NoOp ===== */
int NoOpNode::execute(DynamicEnvironment& env) {
    return 0;
}
