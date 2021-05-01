#ifndef INTEGER_NODE_H
#define INTEGER_NODE_H

#include "expnode.h"

class IntegerNode: public ExpNode {
public:
    IntegerNode(int line, int value);
    int getValue();
    void accept(class Visitor &v);

private:
    int value;
};

#endif
