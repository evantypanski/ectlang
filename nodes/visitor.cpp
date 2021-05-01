#include <iostream>

#include "visitor.h"

void Visitor::visit(ProgramNode *node) {
    std::cout << "Program" << std::endl;
    for (auto statement : node->getStatements())
        statement->accept(*this);
}

void Visitor::visit(StatementNode *node) {
    std::cout << "STATEMENT" << std::endl;
    node->getExp()->accept(*this);
}

void Visitor::visit(IntegerNode *node) {
    std::cout << node->getValue();
}

void Visitor::visit(FloatNode *node) {
    std::cout << node->getValue();
}

void Visitor::visit(PlusNode *node) {
    node->getLeft()->accept(*this);
    std::cout << "+";
    node->getRight()->accept(*this);
}

void Visitor::visit(MinusNode *node) {
    node->getLeft()->accept(*this);
    std::cout << "-";
    node->getRight()->accept(*this);
}

void Visitor::visit(MultNode *node) {
    node->getLeft()->accept(*this);
    std::cout << "*";
    node->getRight()->accept(*this);
}

void Visitor::visit(DivNode *node) {
    node->getLeft()->accept(*this);
    std::cout << "/";
    node->getRight()->accept(*this);
}
