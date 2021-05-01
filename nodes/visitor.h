#ifndef VISITOR_H
#define VISITOR_H

#include "programnode.h"
#include "statementnode.h"
#include "plusnode.h"
#include "minusnode.h"
#include "multnode.h"
#include "divnode.h"
#include "integernode.h"
#include "floatnode.h"

class Visitor {
public:
    virtual void visit(ProgramNode *node);
    virtual void visit(StatementNode *node);
    virtual void visit(IntegerNode *node);
    virtual void visit(FloatNode *node);
    virtual void visit(PlusNode *node);
    virtual void visit(MinusNode *node);
    virtual void visit(MultNode *node);
    virtual void visit(DivNode *node);
};

#endif
