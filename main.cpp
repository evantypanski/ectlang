/*#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>
#include <iostream>

using namespace llvm;

int main(int argc, char **argv) {
    LLVMContext context;
    IRBuilder<> builder(context);
    std::unique_ptr<Module> theModule;
    theModule = make_unique<Module>("my module", context);

    FunctionType *addType =
        FunctionType::get(Type::getInt32Ty(context), false);
    Function *addFunction =
        Function::Create(addType, Function::ExternalLinkage, "add", theModule.get());
    BasicBlock *addBlock = BasicBlock::Create(context, "add", addFunction);

    builder.SetInsertPoint(addBlock);
    Value *left = ConstantInt::get(context, APInt(32, 6));
    Value *right = ConstantInt::get(context, APInt(32, 2));
    Value *add = builder.CreateAdd(left, right, "addtest");
    builder.CreateRet(add);

    theModule->print(outs(), nullptr);
}

*/
#include "nodes/programnode.h"
#include "nodes/visitor.h"

using namespace std;

extern ProgramNode* program;
extern int yyparse();

int main(int argc, char **argv) {
    yyparse();
    Visitor v;
    program->accept(v);
    return 0;
}
