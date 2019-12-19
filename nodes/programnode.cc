#include <iostream>

#include "programnode.h"
#include "visitor.h"

ProgramNode::ProgramNode(int line, int pos, StatementNode *statement) :
    Node(line, pos), statement(statement) {}

StatementNode* ProgramNode::getStatement() {
    return statement;
}

void ProgramNode::accept(Visitor &v) {
    v.visit(this);
}
