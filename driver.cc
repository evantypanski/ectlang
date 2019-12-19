#include <iostream>
#include <fstream>
#include <string>

#include "nodes/node.h"
#include "nodes/minusnode.h"
#include "nodes/plusnode.h"
#include "nodes/multnode.h"
#include "nodes/integernode.h"
#include "nodes/visitor.h"

using namespace std;

FILE *yyin;
int yyparse();

int main(int argc, char **argv) {
  if (argc < 1) {
    cout << "Provide a filename to parse!";
    exit(1);
  }
  FILE *sourceFile = fopen(argv[1], "r");

  if (sourceFile) {
    cout << "Could not open source file " << argv[1] << endl;
    exit(1);
  }

  // Sets input for flex to the file instead of standard in
  yyin = sourceFile;
  // Now let's parse it!
  yyparse();
    /*IntegerNode leftmost(5, 3, 10);
    IntegerNode left2(5, 5, 11);
    FloatNode right2(5, 7, 8.24);
    IntegerNode rightmost(5, 10, 25);
    MultNode n(5, 5, &left2, &right2);
    PlusNode p1(5, 5, &leftmost, &n);
    PlusNode p2(5, 5, &p1, &rightmost);
    StatementNode s(5, 5, &p2);
    ProgramNode program(5, 5, &s);
    Visitor v;
    program.accept(v);*/
}
