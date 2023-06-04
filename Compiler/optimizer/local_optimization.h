
#include <llvm-c/Core.h>
#include <llvm-c/IRReader.h>
#include <llvm-c/Types.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>


void run_optimization(LLVMModuleRef module);
void test(LLVMModuleRef module);
void print_module(LLVMModuleRef module, LLVMModuleRef old_module);
bool global_optimizer(LLVMModuleRef module);
bool local_optimizer(LLVMModuleRef module);
void get_stores(LLVMValueRef func);
void compute_gen(LLVMValueRef func);
void compute_kill(LLVMValueRef func);
void compute_in_out(LLVMValueRef func);
bool constant_propagation(LLVMValueRef func);
void load_operands(LLVMModuleRef module, std::vector<LLVMValueRef> &operands);
bool subexpr_elim(LLVMBasicBlockRef bb);
bool dead_code_elim(LLVMBasicBlockRef bb);
bool constant_folding(LLVMBasicBlockRef bb);

