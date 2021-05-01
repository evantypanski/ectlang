#ifndef MULT_NODE_H
#define MULT_NODE_H

#include "expnode.h"

class MultNode: public ExpNode {
public:
    MultNode(int line, ExpNode *left, ExpNode *right);
    ExpNode* getLeft();
    ExpNode* getRight();
    void accept(class Visitor &v);

private:
    ExpNode *left, *right;
};

#endif
