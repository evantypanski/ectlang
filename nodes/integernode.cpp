#include <iostream>

#include "integernode.h"
#include "visitor.h"

IntegerNode::IntegerNode(int line, int value) :
    ExpNode(line), value(value) {}

int IntegerNode::getValue() {
    return value;
}

void IntegerNode::accept(Visitor &v) {
    v.visit(this);
}
