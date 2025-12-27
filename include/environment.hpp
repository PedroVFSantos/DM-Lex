#pragma once
#include <string>
#include <map>
#include <vector>
#include <stdexcept>

class Node; // Forward declaration

class DynamicEnvironment {
private:
    std::vector<std::map<std::string, int>> stack;
    std::map<std::string, Node*> functions;

public:
    DynamicEnvironment();
    void pushScope();
    void popScope();
    void declareVar(std::string name, int value);
    void registerFunc(std::string name, Node* body);
    Node* getFunc(std::string name);
    int lookup(std::string name);
};