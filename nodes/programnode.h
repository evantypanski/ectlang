#ifndef PROGRAM_NODE_H
#define PROGRAM_NODE_H

#include "statementnode.h"

class ProgramNode: public Node {
    public:
        ProgramNode(int line, StatementNode *exp);
        StatementNode* getStatement();
        void accept(class Visitor &v);

    private:
        StatementNode *statement;
};

#endif
