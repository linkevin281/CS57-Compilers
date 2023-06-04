source = codegen_main
clang_flags = `llvm-config-15 --cxxflags --ldflags --libs core` -I /usr/include/llvm-c-15/ -ggdb -gdwarf-4 -g
import_files = ../Frontend/lex.yy.c ../Frontend/y.tab.c ../libraries/ast.c ../Frontend/semantic_analysis.c++
test_file = ../test_files/asm_test/p4_opt.ll

build: ${source}.c++ ../main.c++ codegen.c++ ${import_files} ../main.c++
	clang++ ${clang_flags} -o ${source}.out ${import_files} ${source}.c++ codegen.c++ ../main.c++

build_local: ${source}.c++ codegen.c++
	clang++ ${clang_flags} -o ${source}.out ${source}.c++ codegen.c++

run: ${source}.c++ codegen.c++
	clear
	clang++ ${clang_flags} -o ${source}.out ${source}.c++ codegen.c++
	./${source}.out ${test_file}

clean: 
	rm ${source}.out