Compilation:
- `bison -d parser.ypp`
- `flex -o scanner.c scanner.lex`
- `g++ parser.tab.cpp nodes/*.cpp main.cpp`
