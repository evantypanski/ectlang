#include <iostream>

class Node {
public:
    virtual void accept(class Visitor &v) = 0;
};


class IntegerNode: public Node {
public:
    IntegerNode(int value);
    void accept(Visitor &v);
    int value;
};

class PlusNode: public Node {
public:
    PlusNode(IntegerNode left, IntegerNode right);
    void accept(Visitor &v);
    IntegerNode left, right;
};

class Visitor {
public:
    void visit(IntegerNode *node);
    void visit(PlusNode *node);
};

IntegerNode::IntegerNode(int value) : value(value) {}

void IntegerNode::accept(Visitor &v) {
    v.visit(this);
}

PlusNode::PlusNode(IntegerNode left, IntegerNode right) :
    left(left), right(right) {}

void PlusNode::accept(Visitor &v) {
    v.visit(this);
}

void Visitor::visit(IntegerNode *node) {
    std::cout << node->value;
}

void Visitor::visit(PlusNode *node) {
    node->left.accept(*this);
    std::cout << "+";
    node->right.accept(*this);
    std::cout << "=" << node->left.value + node->right.value << std::endl;
}


int main() {
    IntegerNode leftInt(1), rightInt(2);
    PlusNode plus(leftInt, rightInt);
    Visitor visitor;
    plus.accept(visitor);
}
