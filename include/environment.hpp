#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class Node;

class DynamicEnvironment {
private:
    std::vector<std::unordered_map<std::string, int>> stack;
    std::unordered_map<std::string, Node*> functions;

public:
    DynamicEnvironment();

    void pushScope();
    void popScope();

    void declareVar(const std::string& name, int value);
    int lookup(const std::string& name) const;

    void registerFunc(const std::string& name, Node* body);
    Node* getFunc(const std::string& name);
};
