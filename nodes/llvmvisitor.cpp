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
    floatInst = false;
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

    // Change the format string depending on if we're dealing with a float or not.
    llvm::Value *formatStr;
    if (floatInst) {
        formatStr = builder.CreateGlobalStringPtr("%f\n");
    } else {
        formatStr = builder.CreateGlobalStringPtr("%d\n");
    }

    printArgs.push_back(formatStr);
    printArgs.push_back(ret);
    builder.CreateCall(mod->getFunction("printf"), printArgs);

    // Reset the float instruction marker.
    floatInst = false;
}

void LLVMVisitor::visit(IntegerNode *node) {
    // Return the LLVM int value.
    ret = llvm::ConstantInt::getSigned(llvm::Type::getInt32Ty(context), node->getValue());
}

void LLVMVisitor::visit(FloatNode *node) {
    // Return the LLVM float value.
    ret = llvm::ConstantFP::get(llvm::Type::getDoubleTy(context), node->getValue());
    // Mark that we're now dealing with a float.
    floatInst = true;
}

void LLVMVisitor::visit(PlusNode *node) {
    // Get the return value from the left side.
    node->getLeft()->accept(*this);
    llvm::Value *lhs = ret;

    // Get the return value from the right side.
    node->getRight()->accept(*this);
    llvm::Value *rhs = ret;

    if (floatInst) {
        // Promote RHS or LHS if we're dealing with floats and they're not a float.
        // (except we use doubles)
        if (!lhs->getType()->isDoubleTy())
            lhs = builder.CreateSIToFP(lhs, llvm::Type::getDoubleTy(context));
        if (!rhs->getType()->isDoubleTy())
            rhs = builder.CreateSIToFP(rhs, llvm::Type::getDoubleTy(context));

        ret = builder.CreateFAdd(lhs, rhs);
    } else {
        // Otherwise we're just doing an integer add.
        ret = builder.CreateAdd(lhs, rhs);
    }
}

void LLVMVisitor::visit(MinusNode *node) {
    // Get the return value from the left side.
    node->getLeft()->accept(*this);
    llvm::Value *lhs = ret;

    // Get the return value from the right side.
    node->getRight()->accept(*this);
    llvm::Value *rhs = ret;

    if (floatInst) {
        // Promote RHS or LHS if we're dealing with floats and they're not a float.
        // (except we use doubles)
        if (!lhs->getType()->isDoubleTy())
            lhs = builder.CreateSIToFP(lhs, llvm::Type::getDoubleTy(context));
        if (!rhs->getType()->isDoubleTy())
            rhs = builder.CreateSIToFP(rhs, llvm::Type::getDoubleTy(context));

        ret = builder.CreateFSub(lhs, rhs);
    } else {
        // Otherwise we're just doing an integer add.
        ret = builder.CreateSub(lhs, rhs);
    }
}

void LLVMVisitor::visit(MultNode *node) {
    // Get the return value from the left side.
    node->getLeft()->accept(*this);
    llvm::Value *lhs = ret;

    // Get the return value from the right side.
    node->getRight()->accept(*this);
    llvm::Value *rhs = ret;

    if (floatInst) {
        // Promote RHS or LHS if we're dealing with floats and they're not a float.
        // (except we use doubles)
        if (!lhs->getType()->isDoubleTy())
            lhs = builder.CreateSIToFP(lhs, llvm::Type::getDoubleTy(context));
        if (!rhs->getType()->isDoubleTy())
            rhs = builder.CreateSIToFP(rhs, llvm::Type::getDoubleTy(context));

        ret = builder.CreateFMul(lhs, rhs);
    } else {
        // Otherwise we're just doing an integer add.
        ret = builder.CreateMul(lhs, rhs);
    }
}

void LLVMVisitor::visit(DivNode *node) {
    // Get the return value from the left side.
    node->getLeft()->accept(*this);
    llvm::Value *lhs = ret;

    // Get the return value from the right side.
    node->getRight()->accept(*this);
    llvm::Value *rhs = ret;

    if (floatInst) {
        // Promote RHS or LHS if we're dealing with floats and they're not a float.
        // (except we use doubles)
        if (!lhs->getType()->isDoubleTy())
            lhs = builder.CreateSIToFP(lhs, llvm::Type::getDoubleTy(context));
        if (!rhs->getType()->isDoubleTy())
            rhs = builder.CreateSIToFP(rhs, llvm::Type::getDoubleTy(context));

        ret = builder.CreateFDiv(lhs, rhs);
    } else {
        // Otherwise we're just doing an integer add.
        ret = builder.CreateSDiv(lhs, rhs);
    }
}
