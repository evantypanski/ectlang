%{
  #include <iostream>
  #include "nodes/node.h"
  #include "nodes/minusnode.h"
  #include "nodes/plusnode.h"
  #include "nodes/multnode.h"
  #include "nodes/divnode.h"
  #include "nodes/expnode.h"
  #include "nodes/integernode.h"
  #include "nodes/floatnode.h"
  #include "nodes/programnode.h"
  #include "nodes/statementnode.h"

  using namespace std;
  int yylex(void);

  void yyerror(char *s) {
    cerr << s << endl;
  }
%}

%union{
  int intVal;
  float floatVal;
  class Node *node;
  class ExpNode *expNode;
  class StatementNode *statementNode;
}

%start program

%token <intVal> INTEGER_LITERAL
%token <floatVal> FLOAT_LITERAL
%token SEMI
%type <expNode> exp
%type <statementNode> statement
%type <node> program
%left	PLUS MINUS
%left	MULT DIV

%%

program: statement	{ $$ = new ProgramNode(0, 0, $1); }
		;

statement: exp SEMI { $$ = new StatementNode(0, 0, $1); }

exp:
   INTEGER_LITERAL	{ $$ = new IntegerNode(0, 0, $1); }
    | FLOAT_LITERAL { $$ = new FloatNode(0, 0, $1); }
		| exp PLUS exp	{ $$ = new PlusNode(0, 0, $1, $3); }
		| exp MINUS exp	{ $$ = new MinusNode(0, 0, $1, $3); }
		| exp MULT exp	{ $$ = new MultNode(0, 0, $1, $3); }
		| exp DIV exp	  { $$ = new DivNode(0, 0, $1, $3); }
		;

%%

