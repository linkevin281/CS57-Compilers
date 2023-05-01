source = miniC
test_files = test_files
libraries = libraries

	
build: $(source).y $(source).l ${libraries}/ast.c semantic_analysis.c++
	yacc -d -v $(source).y
	lex $(source).l
	g++ -ggdb -o $(source).out y.tab.c lex.yy.c ${libraries}/ast.c semantic_analysis.c++

clean:
	rm lex.yy.c y.tab.c y.tab.h $(source).out y.output

debug:
	gdb --args ./$(source).out < ${test_files}/sample_miniC.c

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(source).out < ${test_files}/sample_miniC.c

tree:
	./$(source).out < ${test_files}/sample_miniC.c > sample_miniC.txt

gdb:
	gdb --args ./$(source).out


e: grammar.y $(source).l ${libraries}/ast.c
	yacc -d -v grammar.y
	lex $(source).l
	g++ -ggdb -o $(source).out y.tab.c lex.yy.c ${libraries}/ast.c

