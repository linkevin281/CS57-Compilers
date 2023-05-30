
#include <llvm-c/Core.h>
#include <llvm-c/IRReader.h>
#include <llvm-c/Types.h>
#include "local_optimization.h"
#include <stdio.h>

int main(int argc, char** argv){
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Parse IR file 

    LLVMModuleRef module = LLVMModuleCreateWithName("test");
    LLVMBuilderRef builder = LLVMCreateBuilder();
    // Load IR file at argv[1] into a MemoryBufferRef 
    LLVMMemoryBufferRef buf;
    char *msg = NULL;
    if (LLVMCreateMemoryBufferWithContentsOfFile(argv[1], &buf, &msg)) {
        fprintf(stderr, "error loading file %s: %s\n", argv[1], msg);
        LLVMDisposeMessage(msg);
        return 1;
    }

    // Parse the in-memory IR
    if (LLVMParseIRInContext(LLVMGetGlobalContext(), buf, &module, &msg)) {
        fprintf(stderr, "error parsing IR: %s\n", msg);
        LLVMDisposeMessage(msg);
        return 1;
    }
    // test(module);
    run_optimization(module);

}

