#include <iostream>

#include "floatnode.h"
#include "visitor.h"

FloatNode::FloatNode(int line, float value) :
    ExpNode(line), value(value) {}

float FloatNode::getValue() {
    return value;
}

void FloatNode::accept(Visitor &v) {
    v.visit(this);
}
