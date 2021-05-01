#ifndef PROGRAM_NODE_H
#define PROGRAM_NODE_H

#include <vector>

#include "statementnode.h"

class ProgramNode: public Node {
public:
    ProgramNode(int line);
    void addStatement(StatementNode *statement);
    std::vector<StatementNode *> getStatements();
    void accept(class Visitor &v);

private:
    std::vector<StatementNode *> statements;
};

#endif
