#include <fstream>

#include "llvm/IR/Constants.h"

#include "llvmvisitor.h"
#include "programnode.h"
#include "statementnode.h"
#include "plusnode.h"
#include "minusnode.h"
#include "multnode.h"
#include "divnode.h"
#include "integernode.h"
#include "floatnode.h"

LLVMVisitor::LLVMVisitor(llvm::raw_fd_ostream &out,
                       llvm::LLVMContext &context,
                       std::unique_ptr<llvm::Module> &mod) :
        out(out), context(context), mod(mod), builder(context) {
    ret = nullptr;
}

void LLVMVisitor::visit(ProgramNode *node) {
    // Function returns void.
    llvm::FunctionType *functionReturnType =
        llvm::FunctionType::get(llvm::Type::getVoidTy(context), false);

    // Our main function.
    llvm::Function *mainFunction =
        llvm::Function::Create(functionReturnType,
                               llvm::Function::ExternalLinkage,
                               "main",
                               mod.get());

    // Now make a basic block inside of mainFunction.
    llvm::BasicBlock *body = llvm::BasicBlock::Create(context, "body", mainFunction);
    builder.SetInsertPoint(body);

    // Setup printf prototype.
    std::vector<llvm::Type *> params;
    // Pointer to int8 would be like char *
    params.push_back(llvm::Type::getInt8PtrTy(context));

    llvm::FunctionType *printfType =
            llvm::FunctionType::get(builder.getInt32Ty(), params, /*isVarArg=*/true);
    llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "printf",
                       mod.get());

    // Visit all of the statements.
    for (auto statement : node->getStatements())
        statement->accept(*this);

    // Return
    builder.CreateRetVoid();

    // Print to thi file!
    mod->print(out, nullptr);
    out.close();
}

void LLVMVisitor::visit(StatementNode *node) {
    node->getExp()->accept(*this);

    // Call printf with our returned value.
    std::vector<llvm::Value *> printArgs;
    llvm::Value *formatStr = builder.CreateGlobalStringPtr("%d\n");
    printArgs.push_back(formatStr);
    printArgs.push_back(ret);
    builder.CreateCall(mod->getFunction("printf"), printArgs);
}

void LLVMVisitor::visit(IntegerNode *node) {
    // Return the LLVM int value.
    ret = llvm::ConstantInt::getSigned(llvm::Type::getInt32Ty(context), node->getValue());
}

void LLVMVisitor::visit(FloatNode *node) {
    // Append the float to the file.
    //file << node->getValue();
}

void LLVMVisitor::visit(PlusNode *node) {
    // Get the return value from the left side.
    node->getLeft()->accept(*this);
    llvm::Value *lhs = ret;

    // Get the return value from the right side.
    node->getRight()->accept(*this);
    llvm::Value *rhs = ret;

    // Return the add.
    ret = builder.CreateAdd(lhs, rhs);
}

void LLVMVisitor::visit(MinusNode *node) {
    // Append the subtraction to the file.
    node->getLeft()->accept(*this);
    //file << " - ";
    node->getRight()->accept(*this);
}

void LLVMVisitor::visit(MultNode *node) {
    // Append the multiplication to the file.
    node->getLeft()->accept(*this);
    //file << " * ";
    node->getRight()->accept(*this);
}

void LLVMVisitor::visit(DivNode *node) {
    // Append the division to the file.
    node->getLeft()->accept(*this);
    //file << " / ";
    node->getRight()->accept(*this);
}
