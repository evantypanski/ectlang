#ifndef LLVMVISITOR_H
#define LLVMVISITOR_H

#include <fstream>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"

#include "visitor.h"
#include "programnode.h"
#include "statementnode.h"
#include "plusnode.h"
#include "minusnode.h"
#include "multnode.h"
#include "divnode.h"
#include "integernode.h"
#include "floatnode.h"

class LLVMVisitor : public Visitor {
public:
    LLVMVisitor(llvm::raw_fd_ostream &out,
               llvm::LLVMContext &context,
               std::unique_ptr<llvm::Module> &mod);
    void visit(ProgramNode *node);
    void visit(StatementNode *node);
    void visit(IntegerNode *node);
    void visit(FloatNode *node);
    void visit(PlusNode *node);
    void visit(MinusNode *node);
    void visit(MultNode *node);
    void visit(DivNode *node);

private:
    llvm::raw_fd_ostream &out;
    llvm::LLVMContext &context;
    std::unique_ptr<llvm::Module> &mod;
    llvm::IRBuilder<> builder;

    // The "return value" from the previous visit method.
    llvm::Value *ret;
    bool floatInst;
};

#endif
