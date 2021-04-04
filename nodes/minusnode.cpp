#include <iostream>

#include "minusnode.h"
#include "visitor.h"

MinusNode::MinusNode(int line, ExpNode *left, ExpNode *right) :
    ExpNode(line), left(left), right(right) {}

ExpNode* MinusNode::getLeft() {
    return left;
}

ExpNode* MinusNode::getRight() {
    return right;
}

void MinusNode::accept(Visitor &v) {
    v.visit(this);
}
