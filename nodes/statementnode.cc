#include <iostream>

#include "statementnode.h"
#include "visitor.h"

StatementNode::StatementNode(int line, int pos, ExpNode *exp) :
    Node(line, pos), exp(exp) {}

ExpNode* StatementNode::getExp() {
    return exp;
}

void StatementNode::accept(Visitor &v) {
    v.visit(this);
}
