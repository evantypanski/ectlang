%{
  #include <iostream>
  using namespace std;
  extern "C" void yyerror(char *s);
  extern "C" int yyparse();
%}

%union{
  int		intVal;
  float floatVal;
}

%start program

%token <intVal> INTEGER_LITERAL
%token <floatVal> FLOAT_LITERAL
%token SEMI
%type <floatVal> exp
%type <floatVal> statement
%left	PLUS MINUS
%left	MULT DIV

%%

program: /* empty */
		| program statement	{ cout << "Result: " << $2 << endl; }
		;

statement: exp SEMI

exp:
   INTEGER_LITERAL	{ $$ = $1; }
    | FLOAT_LITERAL { $$ = $1; }
		| exp PLUS exp	{ $$ = $1 + $3; }
		| exp MINUS exp	{ $$ = $1 - $3; }
		| exp MULT exp	{ $$ = $1 * $3; }
		| exp DIV exp	  { $$ = $1 / $3; }
		;

%%

int main(int argv, char **argc) {
  if (argv < 1) {
    cout << "Provide a filename to parse!";
    exit(1);
  }
  FILE *sourceFile = fopen(argc[1], "r");

  if (!sourceFile) {
    cout << "Could not open source file " << argc[1] << endl;
    exit(1);
  }

  // Sets input for flex to the file instead of standard in
  yyin = sourceFile;
  // Now let's parse it!
  yyparse();
}

void yyerror(char *s) {
  cerr << s << endl;
}
