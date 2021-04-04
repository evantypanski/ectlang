#include <iostream>

#include "statementnode.h"
#include "visitor.h"

StatementNode::StatementNode(int line, ExpNode *exp) :
    Node(line), exp(exp) {}

ExpNode* StatementNode::getExp() {
    return exp;
}

void StatementNode::accept(Visitor &v) {
    v.visit(this);
}
