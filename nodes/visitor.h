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
        void visit(ProgramNode *node);
        void visit(StatementNode *node);
        void visit(IntegerNode *node);
        void visit(FloatNode *node);
        void visit(PlusNode *node);
        void visit(MinusNode *node);
        void visit(MultNode *node);
        void visit(DivNode *node);
};

#endif
