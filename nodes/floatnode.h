#ifndef FLOAT_NODE_H
#define FLOAT_NODE_H

#include "expnode.h"

class FloatNode: public ExpNode {
public:
    FloatNode(int line, float value);
    void accept(class Visitor &v);
    float getValue();

private:
    float value;
};

#endif
