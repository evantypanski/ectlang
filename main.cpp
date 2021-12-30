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

#include "nodes/programnode.h"
#include "nodes/llvmvisitor.h"

extern ProgramNode* program;
extern int yyparse();

int main(int argc, char **argv) {
    llvm::LLVMContext context;
    std::unique_ptr<llvm::Module> mod;
    mod = std::make_unique<llvm::Module>("ECTLang module", context);

    yyparse();
    llvm::StringRef filename = "test.ll";
    std::error_code ec;
    llvm::raw_fd_ostream out(filename, ec);
    LLVMVisitor v(out, context, mod);
    program->accept(v);
    return 0;
}
