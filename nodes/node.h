#ifndef NODE_H
#define NODE_H

class Node {
    public:
        Node(int line, int pos);
        int getLine();
        int getPos();
        virtual void accept(class Visitor &v) = 0;

    private:
        int line, pos;
};

#endif
