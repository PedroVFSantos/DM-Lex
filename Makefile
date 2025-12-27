CXX = g++
LEX = flex
YACC = bison
EXE = compiler
INC = -I./include

all:
	$(YACC) -d src/parser.y -o src/parser.tab.cpp --defines=src/parser.tab.hpp
	$(LEX) -o src/lexer.yy.cpp src/lexer.l
	$(CXX) src/main.cpp src/ast.cpp src/environment.cpp src/parser.tab.cpp src/lexer.yy.cpp -o $(EXE) $(INC)

clean:
	rm -f src/*.tab.* src/*.yy.* $(EXE)