#include "nodes/programnode.h"
#include "nodes/cppvisitor.h"

extern ProgramNode* program;
extern int yyparse();

int main(int argc, char **argv) {
    yyparse();
    CPPVisitor v("test.cpp");
    program->accept(v);
    return 0;
}
