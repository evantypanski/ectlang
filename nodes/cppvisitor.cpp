#include <fstream>

#include "cppvisitor.h"
#include "programnode.h"
#include "statementnode.h"
#include "plusnode.h"
#include "minusnode.h"
#include "multnode.h"
#include "divnode.h"
#include "integernode.h"
#include "floatnode.h"

CPPVisitor::CPPVisitor(const char *filename) {
    // Open the file we are going to write to.
    file.open(filename, std::fstream::out);
}

void CPPVisitor::visit(ProgramNode *node) {
    // Write out the information we need to actually run the C program
    // This is hardcoded. It shouldn't be in most cases, but education!!
    file << "#include <iostream>\n";
    file << "int main() {\n";
    for (auto statement : node->getStatements())
        statement->accept(*this);
    file << "}\n";
    file.close();
}

void CPPVisitor::visit(StatementNode *node) {
    // We want to print our statements when the generated C++ code is run.
    file << "\tstd::cout << ";
    node->getExp()->accept(*this);
    file << " << std::endl;\n";
}

void CPPVisitor::visit(IntegerNode *node) {
    // Append the integer to the file.
    file << node->getValue();
}

void CPPVisitor::visit(FloatNode *node) {
    // Append the float to the file.
    file << node->getValue();
}

void CPPVisitor::visit(PlusNode *node) {
    // Append the addition to the file.
    node->getLeft()->accept(*this);
    file << " + ";
    node->getRight()->accept(*this);
}

void CPPVisitor::visit(MinusNode *node) {
    // Append the subtraction to the file.
    node->getLeft()->accept(*this);
    file << " - ";
    node->getRight()->accept(*this);
}

void CPPVisitor::visit(MultNode *node) {
    // Append the multiplication to the file.
    node->getLeft()->accept(*this);
    file << " * ";
    node->getRight()->accept(*this);
}

void CPPVisitor::visit(DivNode *node) {
    // Append the division to the file.
    node->getLeft()->accept(*this);
    file << " / ";
    node->getRight()->accept(*this);
}
