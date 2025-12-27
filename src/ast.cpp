#include "ast.hpp"
#include "environment.hpp"

LiteralNode::LiteralNode(int v) : val(v) {}
int LiteralNode::execute(DynamicEnvironment& env) { return val; }
AccessNode::AccessNode(std::string n) : name(n) {}
int AccessNode::execute(DynamicEnvironment& env) { return env.lookup(name); }
AssignNode::AssignNode(std::string n, Node* e) : name(n), expr(e) {}
int AssignNode::execute(DynamicEnvironment& env) { int v = expr->execute(env); env.declareVar(name, v); return v; }
PrintNode::PrintNode(Node* e) : expr(e) {}
int PrintNode::execute(DynamicEnvironment& env) { int v = expr->execute(env); std::cout << "> " << v << std::endl; return v; }
CallNode::CallNode(std::string n) : name(n) {}
int CallNode::execute(DynamicEnvironment& env) { 
    env.pushScope(); 
    int res = env.getFunc(name)->execute(env); 
    env.popScope(); 
    return res; 
}

IfNode::IfNode(Node* cond, Node* thenB) : condition(cond), thenBranch(thenB) {}

int IfNode::execute(DynamicEnvironment& env) {
    if (condition->execute(env) != 0) {
        return thenBranch->execute(env);
    }
    return 0;
}
void BlockNode::add(Node* n) { if(n) children.push_back(n); }
int BlockNode::execute(DynamicEnvironment& env) { int l=0; for(auto c:children) l=c->execute(env); return l; }
AddNode::AddNode(Node* left, Node* right) : l(left), r(right) {}
int AddNode::execute(DynamicEnvironment& env) { return l->execute(env) + r->execute(env); }
int NoOpNode::execute(DynamicEnvironment& env) { return 0; }