#include <iostream>

#include "programnode.h"
#include "visitor.h"

ProgramNode::ProgramNode(int line) : Node(line) {}

void ProgramNode::addStatement(StatementNode *statement) {
    statements.push_back(statement);
}

std::vector<StatementNode *> ProgramNode::getStatements() {
    return statements;
}

void ProgramNode::accept(Visitor &v) {
    v.visit(this);
}
