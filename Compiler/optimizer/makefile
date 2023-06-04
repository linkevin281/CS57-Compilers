source = optimize
clang_flags = `llvm-config-15 --cxxflags --ldflags --libs core` -I /usr/include/llvm-c-15/ -ggdb -gdwarf-4 -g
import_files = ../Frontend/lex.yy.c ../Frontend/y.tab.c ../libraries/ast.c ../Frontend/semantic_analysis.c++
test_file = ../test_files/llvm_test/testcustom.ll

build: ${source}.c++ ../main.c++ local_optimization.c++ ${import_files} ../main.c++
	clang++ ${clang_flags} -o ${source}.out ${import_files} ${source}.c++ local_optimization.c++ ../main.c++

build_local: ${source}.c++ local_optimization.c++
	clang++ ${clang_flags} -o ${source}.out ${source}.c++ local_optimization.c++

run: ${source}.c++ local_optimization.c++
	clear
	clang++ ${clang_flags} -o ${source}.out ${source}.c++ local_optimization.c++
	./${source}.out ${test_file}
	


clean: 
	rm ${source}.out