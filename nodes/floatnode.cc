#include <iostream>

#include "floatnode.h"
#include "visitor.h"

FloatNode::FloatNode(int line, int pos, float value) :
    ExpNode(line, pos), value(value) {}

float FloatNode::getValue() {
    return value;
}

void FloatNode::accept(Visitor &v) {
    v.visit(this);
}
