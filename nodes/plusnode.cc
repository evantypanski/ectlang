#include <iostream>

#include "plusnode.h"
#include "visitor.h"

PlusNode::PlusNode(int line, int pos, ExpNode *left, ExpNode *right) :
    ExpNode(line, pos), left(left), right(right) {}

ExpNode* PlusNode::getLeft() {
    return left;
}

ExpNode* PlusNode::getRight() {
    return right;
}

void PlusNode::accept(Visitor &v) {
    v.visit(this);
}
