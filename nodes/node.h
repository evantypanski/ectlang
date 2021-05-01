#ifndef NODE_H
#define NODE_H

class Node {
public:
    Node(int line);
    int getLine();
    virtual void accept(class Visitor &v) = 0;

private:
    int line;
};

#endif
