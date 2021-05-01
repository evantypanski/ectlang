#ifndef CPPVISITOR_H
#define CPPVISITOR_H

#include <fstream>
#include "visitor.h"
#include "programnode.h"
#include "statementnode.h"
#include "plusnode.h"
#include "minusnode.h"
#include "multnode.h"
#include "divnode.h"
#include "integernode.h"
#include "floatnode.h"

class CPPVisitor : public Visitor{
public:
    CPPVisitor(const char *filename);
    void visit(ProgramNode *node);
    void visit(StatementNode *node);
    void visit(IntegerNode *node);
    void visit(FloatNode *node);
    void visit(PlusNode *node);
    void visit(MinusNode *node);
    void visit(MultNode *node);
    void visit(DivNode *node);

private:
    std::fstream file;
};

#endif
