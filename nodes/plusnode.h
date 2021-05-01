#ifndef PLUS_NODE_H
#define PLUS_NODE_H

#include "expnode.h"

class PlusNode: public ExpNode {
public:
    PlusNode(int line, ExpNode *left, ExpNode *right);
    ExpNode* getLeft();
    ExpNode* getRight();
    void accept(class Visitor &v);

private:
    ExpNode *left, *right;
};

#endif
