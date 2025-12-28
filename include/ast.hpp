#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>

/* Forward declaration para evitar include circular */
class DynamicEnvironment;

/* ===== Classe base ===== */
class Node {
public:
    virtual ~Node() = default;
    virtual int execute(DynamicEnvironment& env) = 0;
};

/* ===== Nós da AST ===== */

class LiteralNode : public Node {
    int val;
public:
    explicit LiteralNode(int v);
    int execute(DynamicEnvironment& env) override;
};

class AccessNode : public Node {
    std::string name;
public:
    explicit AccessNode(const std::string& n);
    int execute(DynamicEnvironment& env) override;
};

class AssignNode : public Node {
    std::string name;
    Node* expr;
public:
    AssignNode(const std::string& n, Node* e);
    int execute(DynamicEnvironment& env) override;
};

class PrintNode : public Node {
    Node* expr;
public:
    explicit PrintNode(Node* e);
    int execute(DynamicEnvironment& env) override;
};

class CallNode : public Node {
    std::string name;
public:
    explicit CallNode(const std::string& n);
    int execute(DynamicEnvironment& env) override;
};

class IfNode : public Node {
    Node* condition;
    Node* thenBranch;
public:
    IfNode(Node* cond, Node* thenB);
    int execute(DynamicEnvironment& env) override;
};

class BlockNode : public Node {
    std::vector<Node*> children;
public:
    explicit BlockNode(Node* first);
    void add(Node* n);
    int execute(DynamicEnvironment& env) override;
};

class AddNode : public Node {
    Node *l, *r;
public:
    AddNode(Node* left, Node* right);
    int execute(DynamicEnvironment& env) override;
};

class NoOpNode : public Node {
public:
    int execute(DynamicEnvironment& env) override;
};

#endif // AST_HPP
