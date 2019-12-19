#include <iostream>

#include "multnode.h"
#include "visitor.h"

MultNode::MultNode(int line, int pos, ExpNode *left, ExpNode *right) :
    ExpNode(line, pos), left(left), right(right) {}

ExpNode* MultNode::getLeft() {
    return left;
}

ExpNode* MultNode::getRight() {
    return right;
}

void MultNode::accept(Visitor &v) {
    v.visit(this);
}
