source = main
test_dir = test_files/semantic_test
test_file = sample_miniC
.PHONY: all modules compile clean

all: modules compile

modules:
	make -C Frontend
	make -C LLVM
	make -C Optimizer

compile: ${source}.c++ Frontend/y.tab.c Frontend/lex.yy.c Frontend/semantic_analysis.c++ libraries/ast.c
	g++ -ggdb -o $(source).out Frontend/y.tab.c Frontend/lex.yy.c Frontend/semantic_analysis.c++ libraries/ast.c main.c++
	./$(source).out ${test_dir}/${test_file}.c

clean:
	make -C Frontend clean
	make -C LLVM clean
	rm $(source).out