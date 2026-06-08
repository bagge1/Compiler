compiler: lex.yy.c parser.tab.o main.cc symbol_table.cpp semantic_analysis.cpp ir.cpp
		g++ -g -w -ocompiler parser.tab.o lex.yy.c main.cc symbol_table.cpp semantic_analysis.cpp ir.cpp -std=c++14
interpreter: interpreter.cpp
		g++ -g -w -o interpreter interpreter.cpp -std=c++14
parser.tab.o: parser.tab.cc
		g++ -g -w -c parser.tab.cc -std=c++14
parser.tab.cc: parser.yy
		bison parser.yy
lex.yy.c: lexer.flex parser.tab.cc
		flex lexer.flex
tree: 
		dot -T pdf tree.dot -o tree.pdf
st_tree: 
		dot -T pdf st_tree.dot -o st_tree.pdf
IR_tree: 
		dot -T pdf IR_tree.dot -o IR_tree.pdf
clean:
		rm -f parser.tab.* lex.yy.c* compiler stack.hh position.hh location.hh tree.dot tree.pdf st_tree.dot st_tree.pdf interpreter IR_tree.dot IR_tree.pdf bytecode.txt
		rm -R compiler.dSYM

.PHONY: test
test: compiler
	@echo "Running AI tests and standard tests..."
	./run_ai_tests.sh
	./run_test_files.sh