#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <iostream>

class DynamicEnvironment;

class Node {
public:
    virtual ~Node() {}
    virtual int execute(DynamicEnvironment& env) = 0;
};

class LiteralNode : public Node { int val; public: LiteralNode(int v); int execute(DynamicEnvironment& env) override; };
class AccessNode : public Node { std::string name; public: AccessNode(std::string n); int execute(DynamicEnvironment& env) override; };
class AssignNode : public Node { std::string name; Node* expr; public: AssignNode(std::string n, Node* e); int execute(DynamicEnvironment& env) override; };
class PrintNode : public Node { Node* expr; public: PrintNode(Node* e); int execute(DynamicEnvironment& env) override; };
class CallNode : public Node { std::string name; public: CallNode(std::string n); int execute(DynamicEnvironment& env) override; };
class IfNode : public Node {
    Node* condition;   // Nome corrigido
    Node* thenBranch;  // Nome corrigido
public:
    IfNode(Node* cond, Node* thenB);
    int execute(DynamicEnvironment& env) override;
};
class BlockNode : public Node { std::vector<Node*> children; public: BlockNode(Node* f); void add(Node* n); int execute(DynamicEnvironment& env) override; };
class AddNode : public Node { Node *l, *r; public: AddNode(Node* left, Node* right); int execute(DynamicEnvironment& env) override; };
class NoOpNode : public Node { public: int execute(DynamicEnvironment& env) override; };

#endif