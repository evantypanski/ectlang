#include "node.h"

Node::Node(int line, int pos) : line(line), pos(pos) {}

int Node::getLine() {
    return line;
}

int Node::getPos() {
    return pos;
}
