Usage (make sure you have `flex`, `bison`, and `g++` installed):
- `bison parser.ypp`
- `flex -o scanner.c scanner.lex`
- `g++ parser.tab.cpp nodes/*.cpp main.cpp`
