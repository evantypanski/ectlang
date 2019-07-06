%{
  extern "C" int yylex();
  #include "parser.tab.c"  // to get the token types from Bison
%}

%%
[0-9]+        { yylval.intVal = atoi(yytext); return INTEGER_LITERAL; }
[0-9]+.[0-9]+ { yylval.floatVal = atof(yytext); return FLOAT_LITERAL; }
"+"           { return PLUS; }
"-"           { return MINUS; }
"*"           { return MULT; }
"/"           { return DIV; }
";"           { return SEMI; }
[ \t\r\n\f]   ; /* ignore whitespace */

