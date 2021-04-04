#include <iostream>

#include "plusnode.h"
#include "visitor.h"

PlusNode::PlusNode(int line, ExpNode *left, ExpNode *right) :
    ExpNode(line), left(left), right(right) {}

ExpNode* PlusNode::getLeft() {
    return left;
}

ExpNode* PlusNode::getRight() {
    return right;
}

void PlusNode::accept(Visitor &v) {
    v.visit(this);
}
