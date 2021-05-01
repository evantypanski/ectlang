#ifndef DIV_NODE_H
#define DIV_NODE_H

#include "expnode.h"

class DivNode: public ExpNode {
public:
    DivNode(int line, ExpNode *left, ExpNode *right);
    ExpNode* getLeft();
    ExpNode* getRight();
    void accept(class Visitor &v);

private:
    ExpNode *left, *right;
};

#endif
