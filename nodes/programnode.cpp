#include <iostream>

#include "programnode.h"
#include "visitor.h"

ProgramNode::ProgramNode(int line, StatementNode *statement) :
    Node(line), statement(statement) {}

StatementNode* ProgramNode::getStatement() {
    return statement;
}

void ProgramNode::accept(Visitor &v) {
    v.visit(this);
}
