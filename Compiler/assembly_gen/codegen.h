
#include <llvm-c/Core.h>
#include <llvm-c/IRReader.h>
#include <llvm-c/Types.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

void ComputeLiveness(LLVMBasicBlockRef bb);
void RegisterAllocation(LLVMModuleRef module);
LLVMValueRef FindSpill(std::unordered_map<LLVMValueRef, std::string> reg_map);
void Codegen(LLVMModuleRef module);
void CreateBBLabels(LLVMModuleRef module);
void PrintFunctionEnd();
void PrintDirectives(LLVMValueRef inst);
void GetOffsetMap(LLVMValueRef func);
void SortInstructions();

void HandleRet(LLVMValueRef inst);
void HandleLoad(LLVMValueRef inst);
void HandleStore(LLVMValueRef inst);
void HandleCall(LLVMValueRef inst, LLVMValueRef func);
void HandleBr(LLVMValueRef inst);
void HandleAlloca(LLVMValueRef inst);
void HandleArith(LLVMValueRef inst);