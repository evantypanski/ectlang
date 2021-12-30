Usage (make sure you have `flex`, `bison`, and `g++` installed):
- `bison parser.ypp`
- `flex -o scanner.c scanner.lex`
- `g++ main.cpp parser.tab.cpp nodes/*.cpp $(llvm-config-12 --ldflags --libs) $(llvm-config-12 --cxxflags) -o ectfrontend.out`
- `./ectfrontend.out < source.ect`
- `clang++ test.ll`
- `./a.out`
