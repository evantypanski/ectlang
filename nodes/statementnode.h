#ifndef STATEMENT_NODE_H
#define STATEMENT_NODE_H

#include "expnode.h"
#include "node.h"

class StatementNode: public Node {
    public:
        StatementNode(int line, int pos, ExpNode *exp);
        ExpNode* getExp();
        void accept(class Visitor &v);

    private:
        ExpNode *exp;
};

#endif
