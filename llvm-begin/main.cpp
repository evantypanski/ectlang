#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/IRPrintingPasses.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/Pass.h"

int main() {
    llvm::LLVMContext context;

    std::unique_ptr<llvm::Module> mod;
    mod = std::make_unique<llvm::Module>("ECTLang module", context);

    // Build IR for this block.
    llvm::IRBuilder<> builder(context);

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
    // Make a simple add with two constants.
    llvm::Constant *x = llvm::ConstantInt::getSigned(llvm::Type::getInt32Ty(context), 5);
    llvm::Constant *y = llvm::ConstantInt::getSigned(llvm::Type::getInt32Ty(context), -6);
    //llvm::Constant *x = llvm::ConstantFP::get(llvm::Type::getDoubleTy(context), 5.5);
    //llvm::Constant *y = llvm::ConstantFP::get(llvm::Type::getDoubleTy(context), -6.5);
    // For if you need to add an int, x, to a float, y.
    //llvm::Value *newX = builder.CreateUIToFP(x, llvm::Type::getDoubleTy(context));
    llvm::Value *add = builder.CreateAdd(x, y, "addtest");

    std::vector<llvm::Type *> params;
    // Pointer to int8 would be like char *
    params.push_back(llvm::Type::getInt8PtrTy(context));

    llvm::FunctionType *printfType =
            llvm::FunctionType::get(builder.getInt32Ty(), params, /*isVarArg=*/true);
    llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "printf",
                       mod.get());

    // Function call arguments
    std::vector<llvm::Value *> printArgs;
    llvm::Value *formatStr = builder.CreateGlobalStringPtr("%f\n");
    printArgs.push_back(formatStr);
    printArgs.push_back(add);
    builder.CreateCall(mod->getFunction("printf"), printArgs);

    builder.CreateRetVoid();
    mod->print(llvm::outs(), nullptr);

    return 0;
}
