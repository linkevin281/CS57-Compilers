source = llvm_main
clang_flags = `llvm-config-15 --cxxflags --ldflags --libs core` -I /usr/include/llvm-c-15/ -ggdb -gdwarf-4 -g
import_files = ../main.c++ ../Frontend/lex.yy.c ../Frontend/y.tab.c ../libraries/ast.c ../Frontend/semantic_analysis.c++

build: ${source}.c++ ../main.c++
	clang++ ${clang_flags} -o llvm_main.out ${import_files} 

clean: 
	rm llvm_main.out