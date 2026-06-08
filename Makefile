compiler: lex.yy.c parser.tab.o main.cc symboltable.cc semanalysis.cc ir.cc
		g++ -g -w -ocompiler parser.tab.o lex.yy.c main.cc symboltable.cc semanalysis.cc ir.cc -std=c++14
parser.tab.o: parser.tab.cc
		g++ -g -w -c parser.tab.cc -std=c++14
parser.tab.cc: parser.yy
		bison parser.yy
lex.yy.c: lexer.flex parser.tab.cc
		flex lexer.flex
interpreter: interpreter.cc interpreter.hh
		g++ -g -w -o interpreter interpreter.cc -std=c++14
tree: 
		 dot -Tpdf tree.dot -otree.pdf
IR_tree:
		 dot -Tpdf IR_tree.dot -oIR_tree.pdf
clean:
		rm -f parser.tab.* lex.yy.c* compiler stack.hh position.hh location.hh tree.dot tree.pdf interpreter IR_tree.dot IR_tree.pdf bytecode.txt
		rm -R compiler.dSYM