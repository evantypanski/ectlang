#ifndef MINUS_NODE_H
#define MINUS_NODE_H

#include "expnode.h"

class MinusNode: public ExpNode {
public:
    MinusNode(int line, ExpNode *left, ExpNode *right);
    ExpNode* getLeft();
    ExpNode* getRight();
    void accept(class Visitor &v);

private:
    ExpNode *left, *right;
};

#endif
