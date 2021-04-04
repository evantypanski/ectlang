#include <iostream>

#include "divnode.h"
#include "visitor.h"

DivNode::DivNode(int line, ExpNode *left, ExpNode *right) :
    ExpNode(line), left(left), right(right) {}

ExpNode* DivNode::getLeft() {
    return left;
}

ExpNode* DivNode::getRight() {
    return right;
}

void DivNode::accept(Visitor &v) {
    v.visit(this);
}
