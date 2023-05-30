
#include "local_optimization.h"
#include <llvm-c/Core.h>
#include <llvm-c/IRReader.h>
#include <llvm-c/Types.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string.h>
#include <string>
#include <stdio.h>

// DEBUG MACROS //
#define DEBUG1(...)                                  \
    if (verbose && DEB == 1)                         \
    {                                                \
        printf("[%s, %d] ", __FUNCTION__, __LINE__); \
        printf(__VA_ARGS__);                         \
    }


// IN OUT GEN KILL
#define DEBUG2(...)                                  \
    if (verbose && DEB == 2)                         \
    {                                                \
        printf("[%s, %d] ", __FUNCTION__, __LINE__); \
        printf(__VA_ARGS__);                         \
    }

// HIGH LEVEL
#define DEBUG3(...)                                  \
    if (verbose && DEB == 3)                         \
    {                                                \
        printf("[%s, %d] ", __FUNCTION__, __LINE__); \
        printf(__VA_ARGS__);                         \
    }


#define DEB 1

// SET VERBOSE TO 1 TO PRINT DEBUG MESSAGES //
int verbose = 1;

// GLOBAL VARIABLES //
std::unordered_map<LLVMValueRef, std::unordered_set<LLVMValueRef>> store_map;
std::unordered_map<LLVMBasicBlockRef, std::unordered_set<LLVMValueRef>> gen;
std::unordered_map<LLVMBasicBlockRef, std::unordered_set<LLVMValueRef>> kill;
std::unordered_map<LLVMBasicBlockRef, std::unordered_set<LLVMValueRef>> in;
std::unordered_map<LLVMBasicBlockRef, std::unordered_set<LLVMValueRef>> out;
std::unordered_map<LLVMValueRef, std::unordered_map<LLVMBasicBlockRef, std::unordered_set<LLVMBasicBlockRef>>> in_graphs;
std::unordered_map<LLVMValueRef, std::unordered_map<LLVMBasicBlockRef, std::unordered_set<LLVMBasicBlockRef>>> out_graphs;

// FUNCTION PROTOTYPES //
bool global_optimizer(LLVMModuleRef module);
bool local_optimizer(LLVMModuleRef module);
void get_stores(LLVMValueRef func);
void compute_graphs(LLVMModuleRef module);
void print_module(LLVMModuleRef module, LLVMModuleRef old_module = NULL);
void compute_gen_kill(LLVMValueRef func);
void compute_in_out(LLVMValueRef func);
bool constant_propagation(LLVMValueRef func);

void run_optimization(LLVMModuleRef module)
{
    LLVMModuleRef module_copy = LLVMCloneModule(module);

    bool change = true;

    local_optimizer(module);

    global_optimizer(module);

    local_optimizer(module);
    global_optimizer(module);
    local_optimizer(module);

    print_module(module, module_copy);
}

void print_module(LLVMModuleRef module, LLVMModuleRef old_module)
{
    DEBUG1("\n====================================================\n\n"
           "OPTIMIZED MODULE\n\n"
           "====================================================\n\n")
    for (LLVMValueRef func = LLVMGetFirstFunction(module); func != NULL; func = LLVMGetNextFunction(func))
    {
        for (LLVMBasicBlockRef bb = LLVMGetFirstBasicBlock(func); bb != NULL; bb = LLVMGetNextBasicBlock(bb))
        {
            DEBUG1("BB: \n");

            for (LLVMValueRef inst = LLVMGetFirstInstruction(bb); inst != NULL; inst = LLVMGetNextInstruction(inst))
            {
                DEBUG1("  %s\n", LLVMPrintValueToString(inst));
            }
        }
    }

    if (old_module == NULL)
        return;

    DEBUG1("\n====================================================\n\n"
           "ORIGINAL MODULE\n\n"
           "====================================================\n\n")

    for (LLVMValueRef func = LLVMGetFirstFunction(old_module); func != NULL; func = LLVMGetNextFunction(func))
    {
        for (LLVMBasicBlockRef bb = LLVMGetFirstBasicBlock(func); bb != NULL; bb = LLVMGetNextBasicBlock(bb))
        {
            DEBUG1("BB: \n");

            for (LLVMValueRef inst = LLVMGetFirstInstruction(bb); inst != NULL; inst = LLVMGetNextInstruction(inst))
            {
                DEBUG1("  %s\n", LLVMPrintValueToString(inst));
            }
        }
    }
}

bool local_optimizer(LLVMModuleRef module)
{

    bool change = true;

    for (LLVMValueRef func = LLVMGetFirstFunction(module); func != NULL; func = LLVMGetNextFunction(func))
    {
        for (LLVMBasicBlockRef bb = LLVMGetFirstBasicBlock(func); bb != NULL; bb = LLVMGetNextBasicBlock(bb))
        {
            while (change)
            {
                change = false;
                DEBUG3("Running local optimizations on BB {%s} in func {%s}\n", LLVMPrintValueToString(LLVMGetFirstInstruction(bb)), LLVMGetValueName(func));
                change |= subexpr_elim(bb);
                DEBUG1("change: %d\n", change);
                change |= dead_code_elim(bb);
                DEBUG1("change: %d\n", change);
                change |= constant_folding(bb);
                DEBUG1("change: %d\n", change);
                print_module(module);
            }
            change = true;
        }

    }

    return change;
}

bool global_optimizer(LLVMModuleRef module)
{
    LLVMValueRef func = LLVMGetFirstFunction(module);
    compute_graphs(module);
    compute_gen_kill(func);
    compute_in_out(func);

    bool change = constant_propagation(func);
    DEBUG1("change: %d\n", change);
    return change;

    // print ingraph
    // for (LLVMBasicBlockRef bb = LLVMGetFirstBasicBlock(func); bb != NULL; bb = LLVMGetNextBasicBlock(bb))
    // {
    //     DEBUG1("IN graph for bb {%s} in func {%s}\n", LLVMPrintValueToString(LLVMGetFirstInstruction(bb)), LLVMGetValueName(func));
    //     for (LLVMBasicBlockRef in_bb : in_graphs[func][bb])
    //     {
    //         DEBUG1("    {%s}\n", LLVMPrintValueToString(LLVMGetFirstInstruction(in_bb)));
    //     }
    // }
}

// Loop through funcs and create in-graphs and out-graphs for each function
void compute_graphs(LLVMModuleRef module)
{
    for (LLVMValueRef func = LLVMGetFirstFunction(module); func != NULL; func = LLVMGetNextFunction(func))
    {
        std::unordered_map<LLVMBasicBlockRef, std::unordered_set<LLVMBasicBlockRef>> cur_in_graph;
        std::unordered_map<LLVMBasicBlockRef, std::unordered_set<LLVMBasicBlockRef>> cur_out_graph;

        for (LLVMBasicBlockRef bb = LLVMGetFirstBasicBlock(func); bb != NULL; bb = LLVMGetNextBasicBlock(bb))
        {
            for (LLVMValueRef inst = LLVMGetFirstInstruction(bb); inst != NULL; inst = LLVMGetNextInstruction(inst))
            {

                // Find break instructions to find links between basic blocks
                if (LLVMGetInstructionOpcode(inst) == LLVMBr)
                {

                    // If it's a conditional branch, add both branches to the in-graph
                    // If it's not a conditional, only will loop once
                    for (int i = 0; i < LLVMGetNumOperands(inst); i++)
                    {
                        LLVMValueRef operand = LLVMGetOperand(inst, i);

                        // In graph: operand bb -> bb
                        if (cur_in_graph.find(LLVMValueAsBasicBlock(operand)) == cur_in_graph.end())
                        {
                            std::unordered_set<LLVMBasicBlockRef> set;
                            set.insert(bb);
                            cur_in_graph[LLVMValueAsBasicBlock(operand)] = set;
                        }
                        else
                        {
                            cur_in_graph[LLVMValueAsBasicBlock(operand)].insert(bb);
                        }

                        // Out graph: bb -> operand bb
                        if (cur_out_graph.find(bb) == cur_out_graph.end())
                        {
                            std::unordered_set<LLVMBasicBlockRef> set;
                            set.insert(LLVMValueAsBasicBlock(operand));
                            cur_out_graph[bb] = set;
                        }
                        else
                        {
                            cur_out_graph[bb].insert(LLVMValueAsBasicBlock(operand));
                        }
                    }
                }
            }
        }

        in_graphs[func] = cur_in_graph;
        out_graphs[func] = cur_out_graph;
    }
}

// Gets all store instructions in a basic block and stores them in store_map
void get_stores(LLVMValueRef func)
{
    store_map.clear();

    for (LLVMBasicBlockRef bb = LLVMGetFirstBasicBlock(func); bb != NULL; bb = LLVMGetNextBasicBlock(bb))
    {
        for (LLVMValueRef inst = LLVMGetFirstInstruction(bb); inst != NULL; inst = LLVMGetNextInstruction(inst))
        {
            if (LLVMGetInstructionOpcode(inst) == LLVMStore)
            {
                LLVMValueRef store_pointer = LLVMGetOperand(inst, 1);
                LLVMValueRef store_value = LLVMGetOperand(inst, 0);

                if (store_map.find(store_pointer) == store_map.end())
                {
                    std::unordered_set<LLVMValueRef> set;
                    set.insert(store_value);
                    store_map[store_pointer] = set;
                }
                else
                {
                    store_map[store_pointer].insert(store_value);
                }
            }
        }
    }
}

// Create gen by iterating through instructions
// If instruction is store then add to gen
// If any instruction in gen is killed by new store then remove them from gen
void compute_gen_kill(LLVMValueRef func)
{
    gen.clear();
    kill.clear();

    DEBUG1("COMPUTING GEN AND KILL FOR FUNC {%s}\n", LLVMGetValueName(func));
    DEBUG1("===============================\n");
    for (LLVMBasicBlockRef bb = LLVMGetFirstBasicBlock(func); bb != NULL; bb = LLVMGetNextBasicBlock(bb))
    {
        std::unordered_set<LLVMValueRef> bb_gen;
        std::unordered_set<LLVMValueRef> bb_kill;

        gen[bb] = bb_gen;

        // stores an address to inst mapping
        std::unordered_map<LLVMValueRef, LLVMValueRef> to_kill;

        for (LLVMValueRef inst = LLVMGetFirstInstruction(bb); inst != NULL; inst = LLVMGetNextInstruction(inst))
        {
            DEBUG1("Inst:{%s}\n", LLVMPrintValueToString(inst));
            if (LLVMGetInstructionOpcode(inst) == LLVMStore)
            {
                LLVMValueRef store_pointer = LLVMGetOperand(inst, 1);
                LLVMValueRef store_value = LLVMGetOperand(inst, 0);
                DEBUG1("  Found Store // pointer: {%s} value: {%s}\n", LLVMPrintValueToString(store_pointer), LLVMPrintValueToString(store_value));
                // if there is a store to the same address in to_kill, remove it from gen
                if (to_kill.find(store_pointer) != to_kill.end())
                {
                    DEBUG1("    Killing {%s}\n", LLVMPrintValueToString(to_kill[store_pointer]));
                    gen[bb].erase(to_kill[store_pointer]);
                    bb_kill.insert(to_kill[store_pointer]);
                }

                // add the store to gen
                gen[bb].insert(inst);

                // add the store to to_kill
                to_kill[store_pointer] = inst;
            }

            bb_kill.erase(inst);
        }

        kill[bb] = bb_kill;

        DEBUG2("GEN computed for bb {%s} len{%lu} in func {%s}\n", LLVMPrintValueToString(LLVMGetFirstInstruction(bb)), gen[bb].size(), LLVMGetValueName(func));
        DEBUG2("KILL computed for bb {%s} len{%lu} in func {%s}\n", LLVMPrintValueToString(LLVMGetFirstInstruction(bb)), bb_kill.size(), LLVMGetValueName(func));
    }
}

// DEPRECATED
// Compute KILL by iterating through instructions
// If instruction is a store, add all global stores that get killed by it to KILL
void compute_kill(LLVMValueRef func)
{
    get_stores(func);

    for (LLVMBasicBlockRef bb = LLVMGetFirstBasicBlock(func); bb != NULL; bb = LLVMGetNextBasicBlock(bb))
    {
        std::unordered_set<LLVMValueRef> bb_kill;
        kill[bb] = bb_kill;

        for (LLVMValueRef inst = LLVMGetFirstInstruction(bb); inst != NULL; inst = LLVMGetNextInstruction(inst))
        {
            if (LLVMGetInstructionOpcode(inst) == LLVMStore)
            {
                LLVMValueRef store_pointer = LLVMGetOperand(inst, 1);
                LLVMValueRef store_value = LLVMGetOperand(inst, 0);

                // loop through store_map and add all stores that get killed by this store to bb_kill
                for (LLVMValueRef store : store_map[store_pointer])
                {
                    bb_kill.insert(store);
                }

                // remove the current store from bb_kill in case it was added to it
                bb_kill.erase(inst);
            }
        }

        DEBUG2("KILL computed for bb {%s} len{%lu} in func {%s}\n", LLVMPrintValueToString(LLVMGetFirstInstruction(bb)), kill[bb].size(), LLVMGetValueName(func));
    }
}

// Compute IN and OUT
void compute_in_out(LLVMValueRef func)
{
    in.clear();
    out.clear();

    for (LLVMBasicBlockRef bb = LLVMGetFirstBasicBlock(func); bb != NULL; bb = LLVMGetNextBasicBlock(bb))
    {
        std::unordered_set<LLVMValueRef> bb_in;
        std::unordered_set<LLVMValueRef> bb_out;
        in[bb] = bb_in;
        bb_out = gen[bb];
    }

    bool change = true;

    // compute IN until no more changes
    while (change)
    {
        change = false;

        for (LLVMBasicBlockRef bb = LLVMGetFirstBasicBlock(func); bb != NULL; bb = LLVMGetNextBasicBlock(bb))
        {

            std::unordered_map<LLVMBasicBlockRef, std::unordered_set<LLVMBasicBlockRef>> in_graph = in_graphs[func];
            std::unordered_set<LLVMValueRef> old_out = out[bb];

            // loop through all predecessors of bb and add all OUTs of predecessors to IN
            for (LLVMBasicBlockRef pred : in_graph[bb])
            {
                // add all OUTs of predecessors to IN
                for (LLVMValueRef out_inst : out[pred])
                {
                    if (in[bb].find(out_inst) == in[bb].end())
                    {
                        in[bb].insert(out_inst);
                    }
                }
            }

            // OUT = GEN U (IN - KILL)
            out[bb] = gen[bb];
            for (LLVMValueRef in_inst : in[bb])
            {
                if (kill[bb].find(in_inst) == kill[bb].end())
                {
                    out[bb].insert(in_inst);
                }
            }

            // if OUT changed, change = true
            if (old_out != out[bb])
            {
                change = true;
            }

            DEBUG2("IN computed for bb {%s} len{%lu} in func {%s}\n", LLVMPrintValueToString(LLVMGetFirstInstruction(bb)), in[bb].size(), LLVMGetValueName(func));
            DEBUG2("OUT computed for bb {%s} len{%lu} in func {%s}\n", LLVMPrintValueToString(LLVMGetFirstInstruction(bb)), out[bb].size(), LLVMGetValueName(func));
            if (change)
            {
                DEBUG2("Exists CHANGE\n");
            }
        }
    }
}

// Remove all loads that load from the same address as a store in the same basic block
// For every instruction in IN
//   If instruction is store add it to IN and remove all store instructions that are killed
//   If instruction is load and the store instructions for this address are all constants, replace the load with the constant
bool constant_propagation(LLVMValueRef func)
{

    DEBUG1("BEGINNING CONSTANT PROPAGATION\n")
    DEBUG1("================================\n\n")

    bool change = false;
    std::vector<LLVMValueRef> to_remove;

    // Remove Load instructions
    for (LLVMBasicBlockRef bb = LLVMGetFirstBasicBlock(func); bb != NULL; bb = LLVMGetNextBasicBlock(bb))
    {

        DEBUG1("CURRENT BASIC BLOCK: {%s}\n", LLVMPrintValueToString(LLVMGetFirstInstruction(bb)));
        std::unordered_set<LLVMValueRef> bb_in = in[bb];

        for (LLVMValueRef inst = LLVMGetFirstInstruction(bb); inst != NULL; inst = LLVMGetNextInstruction(inst))
        {
            if (LLVMGetInstructionOpcode(inst) == LLVMStore)
            {
                DEBUG1("  FOUND STORE INSTRUCTION {%s}\n", LLVMPrintValueToString(inst));
                LLVMValueRef store_pointer = LLVMGetOperand(inst, 1);
                LLVMValueRef store_value = LLVMGetOperand(inst, 0);

                // Loop through addrs in bb_in and remove all stores in bb_in that are killed by this store
                for (LLVMValueRef in_inst : bb_in)
                {
                    if (in_inst == inst)
                    {
                        continue;
                    }

                    DEBUG1("  Matching store: %s\n", LLVMPrintValueToString(in_inst));
                    if (LLVMGetInstructionOpcode(in_inst) == LLVMStore)
                    {
                        LLVMValueRef match_pointer = LLVMGetOperand(in_inst, 1);
                        DEBUG1("    Store pointer: %s\n", LLVMPrintValueToString(store_pointer));
                        DEBUG1("    Match pointer: %s\n", LLVMPrintValueToString(match_pointer));
                        if (match_pointer == store_pointer)
                        {
                            DEBUG1("      FOUND KILLED STORE INSTRUCTION in bb {%s}\n", LLVMPrintValueToString(LLVMGetFirstInstruction(bb)));
                            DEBUG1("          Store instruction: %s\n", LLVMPrintValueToString(inst));
                            DEBUG1("                next instr: %s\n", LLVMPrintValueToString(LLVMGetNextInstruction(inst)));
                            DEBUG1("          Killing matching instruction: %s\n", LLVMPrintValueToString(in_inst));
                            to_remove.push_back(in_inst);
                        }
                    }
                }

                // Insert the current store to bb_in
                bb_in.insert(inst);
                DEBUG1("  Printing IN::\n");
                for (LLVMValueRef inst : bb_in)
                {
                    DEBUG1("    INSTRUCTION: {%s}\n", LLVMPrintValueToString(inst));
                }
            }

            if (LLVMGetInstructionOpcode(inst) == LLVMLoad)
            {

                DEBUG1("  FOUND LOAD INSTRUCTION {%s}... \n", LLVMPrintValueToString(inst));
                LLVMValueRef load_pointer = LLVMGetOperand(inst, 0);
                // Get all store instructions in bb_in that match the load pointer
                std::unordered_set<LLVMValueRef> matching_stores;

                for (LLVMValueRef in_inst : bb_in)
                {
                    if (LLVMGetInstructionOpcode(in_inst) == LLVMStore)
                    {
                        LLVMValueRef match_pointer = LLVMGetOperand(in_inst, 1);
                        if (match_pointer == load_pointer)
                        {
                            matching_stores.insert(in_inst);
                        }
                    }
                }

                bool all_store = true;
                for (LLVMValueRef in_inst : matching_stores)
                {
                    DEBUG1("    Inst: %s\n", LLVMPrintValueToString(in_inst));

                    // if store is not a constant store, break
                    if (!LLVMIsConstant(LLVMGetOperand(in_inst, 0)))
                    {
                        all_store = false;
                        DEBUG1("    Not a constant store - breaking\n")
                        break;
                    }

                    // if store is const and not equal to the first store, break
                    if (in_inst != *matching_stores.begin())
                    {
                        all_store = false;
                        DEBUG1("    Not the same constant store - breaking\n")
                        break;
                    }
                }

                if (all_store && matching_stores.size() > 0)
                {
                    // replace all uses of load with the constant value
                    LLVMValueRef constant = LLVMGetOperand(*matching_stores.begin(), 0);
                    
                    LLVMReplaceAllUsesWith(inst, constant);
                    to_remove.push_back(inst);

                    DEBUG1("    Replaced load {%s} with constant {%s}\n", LLVMPrintValueToString(inst), LLVMPrintValueToString(constant));
                }
            }
        }
    }

    DEBUG1("REMOVING %lu INSTRUCTIONS\n", to_remove.size());

    // Remove all instructions in to_remove
    for (LLVMValueRef inst : to_remove)
    {
        change = true;
        DEBUG1("    Removing instruction {%s}\n", LLVMPrintValueToString(inst));
        LLVMInstructionEraseFromParent(inst);
    }

    return change;
}
/*
Your common sub-expression elimination function should go through
instructions in each basic-block and identify pairs of instructions
that have same opcode and operands. For reference let us call these
instructions A and B, and assume A occurs before B in the basic block.
In general if there is an instruction between A and B that modifies any
of their operands then your common subexpression elimination function
should leave them untouched as it is not safe to replace B by A.
Otherwise, your optimization function should modify all the uses of B
to point to A (note common subexpression elimination will not delete B,
it will be taken care by the dead code elimination routine).
But in case of an LLVM program safety check is not always required.

In LLVM IR of a miniC program if A and B are not load instructions you
can always be sure that there won't be any instruction between A and B
that will modify the operands. This is due to single static assignment
(SSA) and not allowing pointers in miniC program. But if A and B are
load instructions then the memory pointed-to by their operand can be
modified indirectly by a store instruction to same memory location.
So the safety check is only required when A and B are load instructions.

Some useful LLVM functions for this optimization are:

LLVMReplaceAllUsesWith
*/

// Cases not considered:
// - Order matters %8 %9 is not %9 %8

bool subexpr_elim(LLVMBasicBlockRef bb)
{
    bool change = false;

    DEBUG1("BEGINNING SUBEXPR ELIM\n");
    DEBUG1("====================================================\n\n");

    // Map of instruction opcode + operands to instruction to instruction
    std::unordered_map<std::string, LLVMValueRef> map;

    // Set of store pointers to store values in map
    std::unordered_map<std::string, std::string> store_map;

    for (LLVMValueRef inst = LLVMGetFirstInstruction(bb); inst != NULL; inst = LLVMGetNextInstruction(inst))
    {
        char *str = LLVMPrintValueToString(inst);
        DEBUG1("Inst: %s\n", str);

        // get instruction opcode
        LLVMOpcode opcode = LLVMGetInstructionOpcode(inst);
        DEBUG1("    Opcode: %d\n", opcode);

        // get instruction operands
        std::vector<LLVMValueRef> operands;
        for (int i = 0; i < LLVMGetNumOperands(inst); i++)
        {
            operands.push_back(LLVMGetOperand(inst, i));
            DEBUG1("    Operand %d: %s\n", i, LLVMPrintValueToString(LLVMGetOperand(inst, i)));
        }

        // Create inst_key of opcode + operands
        // opcodeoperand1operand2...
        std::string inst_key = std::string(std::to_string(opcode));
        for (int i = 0; i < operands.size(); i++)
        {
            inst_key += std::string(LLVMPrintValueToString(operands[i]));
        }

        if (opcode == LLVMAlloca)
        {
            continue;
        }

        // if we have a load
        else if (opcode == LLVMLoad)
        {
            // if inst_key is in map
            if (map.find(inst_key) != map.end())
            {
                LLVMReplaceAllUsesWith(inst, map[inst_key]);
                change = true;
                DEBUG1("     REPLACED all uses of %s with %s\n", str, LLVMPrintValueToString(map[inst_key]));
            }

            // store pointer to instruction in map
            else
            {
                map[inst_key] = inst;
                DEBUG1("     Added {%s} to map\n", inst_key.c_str())
            }
        }

        // if we have a store instruction
        else if (opcode == LLVMStore)
        {
            // Check if there exists a load with this operand 1, remove
            std::string store_inst_key = "27" + std::string(LLVMPrintValueToString(operands[1]));
            if (map.find(store_inst_key) != map.end())
            {
                DEBUG1("Found store {%s} to load {%s}, removed load\n", str, LLVMPrintValueToString(map[store_inst_key]));
                map.erase(store_inst_key);
            }
        }

        else
        {
            // if inst_key is in map
            if (map.find(inst_key) != map.end())
            {
                LLVMReplaceAllUsesWith(inst, map[inst_key]);
                change = true;
                DEBUG1("    REPLACED all uses of %s with %s\n", str, LLVMPrintValueToString(map[inst_key]));
            }

            // store pointer to instruction in map
            else
            {
                map[inst_key] = inst;
                DEBUG1("Added %s to map\n", inst_key.c_str())
            }
        }
    }
    DEBUG1("change: %d\n", change);
    return change;
}

// Heuristic:
// All instructions are operands,
//   if the instruction is an operand of another instruction then it is not dead.
//   Otherwise, it is dead.

// instruction list:
// alloca, store, load, icmp, br, ret, add, sub, mul, sdiv
bool dead_code_elim(LLVMBasicBlockRef bb)
{
    bool change = false;

    DEBUG1("\n\nBEGINNING DEAD CODE ELIM FOR BB: %s\n", LLVMPrintValueToString(LLVMGetFirstInstruction(bb)));
    DEBUG1("====================================================\n\n\n");
    // operands -> instructions
    std::unordered_map<LLVMValueRef, std::vector<LLVMValueRef>> operands_insts;

    // operands -> num uses
    std::unordered_map<LLVMValueRef, int> operand_uses;

    std::unordered_map<std::string, LLVMValueRef> find_insts;

    // Set of void instructions to not remove as deadcode
    std::unordered_set<LLVMOpcode> void_insts = {
        LLVMStore,
        LLVMRet,
        LLVMICmp,
        LLVMCall,
        LLVMAlloca,
        LLVMBr};

    // Loop through instructions
    //   if instruction is not a void inst and inst not in operand_uses
    for (LLVMValueRef inst = LLVMGetFirstInstruction(bb); inst != NULL; inst = LLVMGetNextInstruction(inst))
    {
        DEBUG1("Instruction: {%s}\n", LLVMPrintValueToString(inst));
        if (void_insts.find(LLVMGetInstructionOpcode(inst)) == void_insts.end() && operand_uses.find(inst) == operand_uses.end())
        {
            operand_uses[inst] = 0;
            DEBUG1("  Found new instruction: %s\n", LLVMPrintValueToString(inst));
        }

        for (int i = 0; i < LLVMGetNumOperands(inst); i++)
        {
            LLVMValueRef operand = LLVMGetOperand(inst, i);
            DEBUG1("    Operand: {%s}\n", LLVMPrintValueToString(operand));

            if (operand_uses.find(operand) != operand_uses.end())
            {
                operand_uses[operand] += 1;
            }
        }
    }

    for (std::pair<LLVMValueRef, int> pair : operand_uses)
    {
        DEBUG1("Operand: %s, uses: %d\n", LLVMPrintValueToString(pair.first), pair.second);
        if (pair.second == 0)
        {
            LLVMInstructionEraseFromParent(pair.first);
        }
    }

    // // Loop through instructions
    // for (LLVMValueRef inst = LLVMGetFirstInstruction(bb); inst != NULL; inst = LLVMGetNextInstruction(inst))
    // {
    //     DEBUG1("Instruction: {%s}\n", LLVMPrintValueToString(inst));

    //     if (void_insts.find(LLVMGetInstructionOpcode(inst)) != void_insts.end())
    //     {
    //         DEBUG1("    Void instruction, skipping\n");
    //         continue;
    //     }

    //     for (int i = 0; i < LLVMGetNumOperands(inst); i++)
    //     {
    //         LLVMValueRef operand = LLVMGetOperand(inst, i);
    //         DEBUG1("    Operand: {%s}\n", LLVMPrintValueToString(operand));

    //         if (operand_uses.find(operand) != operand_uses.end())
    //         {
    //             operand_uses[operand] += 1;
    //             DEBUG1("    Found operand: {%s} with %d uses\n", LLVMPrintValueToString(operand), operand_uses[operand]);
    //         }
    //     }
    // }

    // for (std::pair<LLVMValueRef, int> pair : operand_uses)
    // {
    //     if (pair.second == 0)
    //     {
    //         // If instruction is void, skip
    //         if (void_insts.find(LLVMGetInstructionOpcode(pair.first)) != void_insts.end())
    //         {
    //             DEBUG1("    Void instruction, skipping\n");
    //             continue;
    //         }
    //         DEBUG1("Found dead instruction: {%s}\n", LLVMPrintValueToString(pair.first));
    //         LLVMInstructionEraseFromParent(pair.first);
    //         change = true;
    //     }
    // }

    return change;
}

bool constant_folding(LLVMBasicBlockRef bb)
{
    bool change = false;

    DEBUG1("\n\nBEGINNING CONSTANT FOLDING\n");
    DEBUG1("====================================================\n\n\n");

    std::unordered_set<LLVMOpcode> binary_ops = {
        LLVMAdd,
        LLVMSub,
        LLVMMul,
        LLVMSDiv,
        LLVMICmp};

    std::vector<LLVMValueRef> to_remove;

    for (LLVMValueRef inst = LLVMGetFirstInstruction(bb); inst != NULL; inst = LLVMGetNextInstruction(inst))
    {
        LLVMOpcode opcode = LLVMGetInstructionOpcode(inst);
        DEBUG1("Instruction: {%s}\n", LLVMPrintValueToString(inst));
        if (binary_ops.find(opcode) != binary_ops.end())
        {
            DEBUG1("  Found binary op: %s\n", LLVMPrintValueToString(inst));
            LLVMValueRef op1 = LLVMGetOperand(inst, 0);
            LLVMValueRef op2 = LLVMGetOperand(inst, 1);

            if (LLVMIsAConstant(op1) && LLVMIsAConstant(op2))
            {
                LLVMValueRef new_inst = NULL;
                DEBUG1("WE HAVE TWO CONSTANTS\n")
                if (opcode == LLVMAdd)
                {
                    new_inst = LLVMConstAdd(op1, op2);
                    DEBUG1("    Adding %s and %s\n", LLVMPrintValueToString(op1), LLVMPrintValueToString(op2));
                }
                else if (opcode == LLVMSub)
                {
                    new_inst = LLVMConstSub(op1, op2);
                    DEBUG1("    Subtracting %s and %s\n", LLVMPrintValueToString(op1), LLVMPrintValueToString(op2));
                }
                else if (opcode == LLVMMul)
                {
                    new_inst = LLVMConstMul(op1, op2);
                    DEBUG1("    Multiplying %s and %s\n", LLVMPrintValueToString(op1), LLVMPrintValueToString(op2));
                }
                else if (opcode == LLVMICmp)
                {
                    new_inst = LLVMConstICmp(LLVMGetICmpPredicate(inst), op1, op2);
                    DEBUG1("    Comparing %s and %s\n", LLVMPrintValueToString(op1), LLVMPrintValueToString(op2));
                }
                else
                {
                    continue;
                }

                LLVMReplaceAllUsesWith(inst, new_inst);
                to_remove.push_back(inst);
                change = true;
            }
        }
    }

    for (LLVMValueRef inst : to_remove)
    {
        LLVMInstructionEraseFromParent(inst);
    }

    return change;
}