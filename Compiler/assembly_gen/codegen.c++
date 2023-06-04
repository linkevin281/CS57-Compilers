#include "codegen.h"
#include <llvm-c/Core.h>
#include <llvm-c/IRReader.h>
#include <llvm-c/Types.h>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <string.h>
#include <string>
#include <stdio.h>

#define DEBUG1(...)                                  \
    if (verbose && DEB == 0)                         \
    {                                                \
        printf("[%s, %d] ", __FUNCTION__, __LINE__); \
        printf(__VA_ARGS__);                         \
    }

#define DEBUG2(...)                                  \
    if (verbose && DEB == 2)                         \
    {                                                \
        printf("[%s, %d] ", __FUNCTION__, __LINE__); \
        printf(__VA_ARGS__);                         \
    }

#define DEBUG3(...)                                  \
    if (verbose && DEB == 3)                         \
    {                                                \
        printf("[%s, %d] ", __FUNCTION__, __LINE__); \
        printf(__VA_ARGS__);                         \
    }
#define EMIT(...)            \
    if (verbose && DEB == 0) \
    {                        \
        printf(__VA_ARGS__); \
        printf("\n");        \
    }

#define DEB 0

// SET VERBOSE TO 1 TO PRINT DEBUG MESSAGES //
int verbose = 1;

// GLOBAL VARIABLES //

std::unordered_map<LLVMValueRef, int> inst_index;
std::unordered_map<LLVMValueRef, std::pair<int, int>> live_range;
std::vector<LLVMValueRef> sorted_insts;
std::unordered_map<LLVMValueRef, int> offset_map;
std::unordered_map<LLVMValueRef, std::string> reg_map;
std::unordered_map<LLVMBasicBlockRef, std::pair<int, LLVMValueRef>> bb_labels;
int stack_offset = 0;

// FUNCTION PROTOTYPES //
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
void print_reg_mem();

void ComputeLiveness(LLVMBasicBlockRef bb)
{
    inst_index.clear();
    live_range.clear();

    // Get the index of each instruction in the basic block
    int i = 0;
    for (LLVMValueRef inst = LLVMGetFirstInstruction(bb); inst != NULL; inst = LLVMGetNextInstruction(inst))
    {
        if (LLVMIsAAllocaInst(inst))
        {
            continue;
        }

        inst_index[inst] = i;
        live_range[inst] = std::make_pair(i, -1);
        i++;
    }

    // Get the live range of each instruction in the basic block
    // Iterate backwards through the basic block and update the live range of each instruction
    for (std::pair<LLVMValueRef, int> inst_pair : inst_index)
    {
        for (LLVMValueRef b_inst = LLVMGetLastInstruction(bb); b_inst != NULL; b_inst = LLVMGetPreviousInstruction(b_inst))
        {
            for (int i = 0; i < LLVMGetNumOperands(b_inst); i++)
            {
                LLVMValueRef operand = LLVMGetOperand(b_inst, i);
                if (operand == inst_pair.first)
                {
                    // Load the current backwards itr instruction to the end index of the live range of the operand
                    live_range[inst_pair.first].second = inst_index[b_inst];
                }
            }
        }
    }

    // Print the live range of each instruction
    DEBUG1("Live Range\n");
    DEBUG1("==========\n");
    for (std::pair<LLVMValueRef, std::pair<int, int>> range : live_range)
    {
        DEBUG1("%s: [%d, %d]\n", LLVMGetValueName(range.first), range.second.first, range.second.second);
    }
}

void RegisterAllocation(LLVMModuleRef module)
{
    // Maps LLVM Instruction to Physical Register
    std::unordered_set<int> non_lhs_op;

    non_lhs_op.insert(LLVMBr);
    non_lhs_op.insert(LLVMRet);
    non_lhs_op.insert(LLVMCall);
    non_lhs_op.insert(LLVMStore);

    DEBUG1("Register Allocation\n");
    DEBUG1("====================\n")
    CreateBBLabels(module);

    for (LLVMValueRef func = LLVMGetFirstFunction(module); func != NULL; func = LLVMGetNextFunction(func))
    {
        for (LLVMBasicBlockRef bb = LLVMGetFirstBasicBlock(func); bb != NULL; bb = LLVMGetNextBasicBlock(bb))
        {
            std::unordered_map<std::string, bool> reg_set;
            reg_set["ebx"] = false;
            reg_set["ecx"] = false;
            reg_set["edx"] = false;

            LLVMOpcode opcode = LLVMGetInstructionOpcode(LLVMGetFirstInstruction(bb));
            ComputeLiveness(bb);
            SortInstructions();

            for (std::pair<LLVMValueRef, std::pair<int, int>> range : live_range)
            {
                LLVMValueRef inst = range.first;
                DEBUG1("Instruction:%s\n", LLVMPrintValueToString(inst));
                // for debug
                if (strcmp(LLVMPrintValueToString(inst), "  %7 = load i32, ptr %4, align 4") == 0)
                {
                    DEBUG1("           FOUND   %%7 = load i32, ptr %%4, align 4\n");
                }

                if (LLVMIsAAllocaInst(inst))
                {
                    continue;
                }

                // If inst does not have a LHS (store, branch, call)
                else if (non_lhs_op.find(LLVMGetInstructionOpcode(inst)) == non_lhs_op.end())
                {
                    for (int i = 0; i < LLVMGetNumOperands(inst); i++)
                    {
                        LLVMValueRef operand = LLVMGetOperand(inst, i);
                        if (strcmp(LLVMPrintValueToString(operand), "  %7 = load i32, ptr %4, align 4") == 0)
                        {
                            DEBUG1("   elseif      FOUND   %%7 = load i32, ptr %%4, align 4\n");
                        }
                        if (live_range[operand].second == inst_index[inst])
                        {
                            if (reg_map.find(operand) != reg_map.end())
                            {
                                reg_set[reg_map[operand]] = false;
                                if (strcmp(LLVMPrintValueToString(operand), "  %7 = load i32, ptr %4, align 4") == 0)
                                {
                                    DEBUG1("       set to false   %%7 = load i32, ptr %%4, align 4\n");
                                }
                            }
                        }
                    }
                }

                else
                {
                    // Check for empty registers and assign first empty reg
                    std::string empty_reg = "";
                    for (std::pair<std::string, bool> reg : reg_set)
                    {
                        if (reg.second == false)
                        {
                            empty_reg = reg.first;
                            break;
                        }
                    }

                    // Three cases to hold
                    // 1. inst is a ADD, SUB, MUL
                    // 2. inst's first operand has a register
                    // 3. liveness range of first operand ends at inst's index
                    if ((opcode == LLVMAdd || opcode == LLVMSub || opcode == LLVMMul) && (reg_map.find(LLVMGetOperand(inst, 0)) != reg_map.end()) && (live_range[LLVMGetOperand(inst, 0)].second == inst_index[inst]))
                    {
                        // Add inst to reg_map of reg of first operand, set it to being used
                        std::string new_reg = reg_map[LLVMGetOperand(inst, 0)];
                        reg_map[inst] = new_reg;
                        reg_set[new_reg] = true;

                        // If live range of second inst OP ends, and reg is assigned, make reg available
                        LLVMValueRef operand2 = LLVMGetOperand(inst, 1);
                        if (reg_map.find(operand2) != reg_map.end())
                        {
                            if (live_range[operand2].second == inst_index[inst])
                            {
                                reg_set[reg_map[operand2]] = false;
                            }
                        }
                    }

                    // Found a register open
                    else if (empty_reg != "")
                    {
                        // Add inst to empty reg and set it to being used
                        reg_map[inst] = empty_reg;
                        reg_set[empty_reg] = true;

                        // If live range of any inst OP ends, and reg is assigned, make reg available
                        for (int i = 0; i < LLVMGetNumOperands(inst); i++)
                        {
                            LLVMValueRef operand = LLVMGetOperand(inst, i);
                            if (reg_map.find(operand) != reg_map.end())
                            {
                                if (live_range[operand].second == inst_index[inst])
                                {
                                    reg_set[reg_map[operand]] = false;
                                }
                            }
                        }
                    }

                    // No register is available
                    else
                    {
                        // Find the inst that has the longest live range in current reg_map
                        LLVMValueRef spill = FindSpill(reg_map);

                        // If live range of inst ends after range of spill, indicate that inst is spilled
                        if (live_range[spill].second > live_range[inst].second)
                        {
                            reg_map[inst] = "-1";
                        }
                        // otherwise the spill is spilled and inst is assigned the spill's reg
                        else
                        {
                            std::string spill_reg = reg_map[spill];
                            reg_map[inst] = spill_reg;
                            reg_map[spill] = "-1";
                        }

                        // If live range of any inst OP ends, and reg is assigned, make reg available
                        for (int i = 0; i < LLVMGetNumOperands(inst); i++)
                        {
                            LLVMValueRef operand = LLVMGetOperand(inst, i);
                            if (reg_map.find(operand) != reg_map.end())
                            {
                                if (live_range[operand].second == inst_index[inst])
                                {
                                    reg_set[reg_map[operand]] = false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void SortInstructions()
{
    sorted_insts.clear();
    // sort by end points in live_map by decreasing
    std::sort(sorted_insts.begin(), sorted_insts.end(), [](LLVMValueRef a, LLVMValueRef b)
              { return live_range[a].second > live_range[b].second; });
}

LLVMValueRef FindSpill(std::unordered_map<LLVMValueRef, std::string> reg_map)
{
    for (LLVMValueRef inst : sorted_insts)
    {
        if (reg_map.find(inst) != reg_map.end() && reg_map[inst] != "-1")
        {
            return inst;
        }
    }

    return NULL;
}

void Codegen(LLVMModuleRef module)
{
    DEBUG1("RUNNING CODEGEN\n");
    DEBUG1("========================================\n");
    for (LLVMValueRef func = LLVMGetFirstFunction(module); func != NULL; func = LLVMGetNextFunction(func))
    {
        PrintDirectives(func);
        GetOffsetMap(func);

        for (LLVMBasicBlockRef bb = LLVMGetFirstBasicBlock(func); bb != NULL; bb = LLVMGetNextBasicBlock(bb))
        {
            DEBUG1("BB: %s\n", LLVMPrintValueToString(LLVMGetFirstInstruction(bb)));
            for (LLVMValueRef inst = LLVMGetFirstInstruction(bb); inst != NULL; inst = LLVMGetNextInstruction(inst))
            {
                DEBUG1("  Handling Inst: {%s},\n", LLVMPrintValueToString(inst));

                switch (LLVMGetInstructionOpcode(inst))
                {
                case LLVMRet:
                    HandleRet(inst);
                    break;
                case LLVMLoad:
                    HandleLoad(inst);
                    break;
                case LLVMStore:
                    HandleStore(inst);
                    break;
                case LLVMCall:
                    HandleCall(inst, func);
                    break;
                case LLVMBr:
                    HandleBr(inst);
                    break;
                case LLVMAlloca:
                    break;
                case LLVMAdd:
                    HandleArith(inst);
                    break;
                case LLVMSub:
                    HandleArith(inst);
                    break;
                case LLVMMul:
                    HandleArith(inst);
                    break;
                case LLVMICmp:
                    HandleArith(inst);
                    break;
                default:
                    break;
                }
            }
        }
    }
}

// Create a map of basic blocks to their labels <bb_index, first_inst>
void CreateBBLabels(LLVMModuleRef module)
{
    bb_labels.clear();

    DEBUG1("Creating BB Labels\n");
    DEBUG1("=======================\n")

    for (LLVMValueRef func = LLVMGetFirstFunction(module); func != NULL; func = LLVMGetNextFunction(func))
    {
        int bb_count = 0;
        for (LLVMBasicBlockRef bb = LLVMGetFirstBasicBlock(func); bb != NULL; bb = LLVMGetNextBasicBlock(bb))
        {
            bb_labels[bb] = std::make_pair(bb_count, LLVMGetFirstInstruction(bb));
            bb_count++;
        }
    }

    for (std::pair<LLVMBasicBlockRef, std::pair<int, LLVMValueRef>> bb : bb_labels)
    {
        DEBUG1("  BB: %s, Label: %d\n", LLVMPrintValueToString(LLVMGetFirstInstruction(bb.first)), bb.second.first);
    }
}

// Populate offset map and initialize bytes neede for local variables
// Alloca instructions are always the first instruction in a basic block require 4 bytes
// Spill values are always require 4 bytes
void GetOffsetMap(LLVMValueRef func)
{
    offset_map.clear();

    int offset = 0;
    for (LLVMBasicBlockRef bb = LLVMGetFirstBasicBlock(func); bb != NULL; bb = LLVMGetNextBasicBlock(bb))
    {
        for (LLVMValueRef inst = LLVMGetFirstInstruction(bb); inst != NULL; inst = LLVMGetNextInstruction(inst))
        {
            if (LLVMGetInstructionOpcode(inst) == LLVMAlloca)
            {
                offset_map[inst] = offset;
                offset += 4;
            }
        }
    }
    for (std::pair<LLVMValueRef, std::string> reg : reg_map)
    {
        if (reg.second != "-1")
        {
            offset_map[reg.first] = offset;
            offset += 4;
        }
    }
    stack_offset = offset;

    DEBUG1("Offset Map\n");
    DEBUG1("=======================\n");
    for (std::pair<LLVMValueRef, int> offset : offset_map)
    {
        DEBUG1("  %d, %s\n", offset.second, LLVMPrintValueToString(offset.first));
    }
}

//
void PrintDirectives(LLVMValueRef func)
{
    EMIT("\t.text");
    EMIT("\t.globl %s", LLVMGetValueName(func));
    EMIT("\t.type %s, @function", LLVMGetValueName(func));
    EMIT("%s:", LLVMGetValueName(func));
    EMIT("\tpushl %%ebp");
    EMIT("\tmovl %%esp, %%ebp");
    EMIT("\tsubl $%d, %%esp", stack_offset);
}

void PrintFunctionEnd()
{
    EMIT("\t movl %%ebp, %%esp");
    EMIT("\t popl %%ebp");
    EMIT("\tleave");
    EMIT("\tret");
}

void HandleRet(LLVMValueRef inst)
{
    LLVMValueRef return_var = LLVMGetOperand(inst, 0);

    if (LLVMIsConstant(return_var))
    {
        EMIT("\tmovl $%lld, %%eax", LLVMConstIntGetSExtValue(return_var));
    }
    // if A is a temporary variable and is in memory
    else if (reg_map.find(return_var) != reg_map.end() && reg_map[return_var] != "-1")
    {
        int k = offset_map[return_var];
        EMIT("\tmovl %d(%%ebp), %%eax", k);
    }
    // if A is a temporary variable and has a physical register
    else if (reg_map.find(return_var) != reg_map.end())
    {
        EMIT("\tmovl %%%s, %%eax", reg_map[return_var].c_str());
    }
    PrintFunctionEnd();
}
void HandleLoad(LLVMValueRef inst)
{
    LLVMValueRef load_from = LLVMGetOperand(inst, 0);

    print_reg_mem();

    if (reg_map.find(inst) != reg_map.end() && reg_map[inst] != "-1")
    {
        std::string reg = reg_map[inst];
        int offset = offset_map[load_from];
        EMIT("\tmovl %d(%%ebp), %%%s", offset, reg.c_str());
    }
}

// Ex. {store i32 store_var, i32* %store_to}
void HandleStore(LLVMValueRef inst)
{

    LLVMValueRef store_var = LLVMGetOperand(inst, 0);

    // if first operand is a parameter
    if (reg_map.find(inst) == reg_map.end())
    {
        DEBUG1("  First instruction is a parameter, returning\n")
        return;
    }
    // if first operand is constant
    else if (LLVMIsConstant(store_var))
    {
        DEBUG1("  First operand is a constant\n");
        LLVMValueRef store_to = LLVMGetOperand(inst, 1);
        int offset = offset_map[store_to];
        EMIT("\tmovl $%lld, %d(%%ebp)", LLVMConstIntGetSExtValue(store_var), offset);
        return;
    }
    else
    {
        // TODO Bug here relating to the function parameter %0
        if (reg_map[store_var] != "-1")
        {
            DEBUG1("  First operand has a physical register\n ")
            std::string reg = reg_map[store_var];
            LLVMValueRef store_to = LLVMGetOperand(inst, 1);
            int offset = offset_map[store_to];
            EMIT("\tmovl %%%s, %d(%%ebp)", reg.c_str(), offset);
        }
        else
        {
            DEBUG1("  First operand is in memory\n")
            LLVMValueRef store_to = LLVMGetOperand(inst, 1);
            int offset = offset_map[store_var];
            EMIT("\tmovl %d(%%ebp), %%eax)", offset);
            offset = offset_map[store_to];
            EMIT("\tmovl %%eax, %d(%%ebp)", offset);
        }
    }
}

// Type: Call. {%a = call type @func(P)} or {call type @func(P)}
void HandleCall(LLVMValueRef inst, LLVMValueRef func)
{
    EMIT("\tpushl %%ebx");
    EMIT("\tpushl %%ecx");
    EMIT("\tpushl %%edx");

    int param_count = LLVMCountParams(func);

    // if func has a param P
    if (param_count == 1)
    {
        LLVMValueRef param = LLVMGetParam(func, 0);

        // if P is a constant
        if (LLVMIsConstant(param))
        {
            EMIT("\tpushl $%lld", LLVMConstIntGetSExtValue(param));
        }
        else
        {
            // If P is a temporary variable and has a physical register
            if (reg_map.find(param) != reg_map.end() && reg_map[param] != "-1")
            {
                EMIT("\tpushl %%%s", reg_map[param].c_str());
            }
            // If p is in memory
            else if (reg_map.find(param) != reg_map.end())
            {
                int offset = offset_map[param];
                EMIT("\tpushl %d(%%ebp)", offset);
            }
        }
    }

    EMIT("\tcall %s", LLVMGetValueName(func));

    if (param_count == 1)
    {
        EMIT("\taddl $4, %%esp");
    }

    EMIT("\tpopl %%edx");
    EMIT("\tpopl %%ecx");
    EMIT("\tpopl %%ebx");

    if (LLVMGetNumOperands(inst) == 1)
    {
        LLVMValueRef call_var = LLVMGetOperand(inst, 0);
        // if call_var has a register
        if (reg_map.find(call_var) != reg_map.end() && reg_map[call_var] != "-1")
        {
            EMIT("\tmovl %%eax, %%%s", reg_map[call_var].c_str());
        }
        // if call_var is in memory
        else if (reg_map.find(call_var) != reg_map.end())
        {
            int offset = offset_map[call_var];
            EMIT("\tmovl %%eax, %d(%%ebp)", offset);
        }
    }
}

// Type: Branch. {br i1 %a, label %b, label %c} or {br label %b}
void HandleBr(LLVMValueRef inst)
{
    // if branch is unconditional
    if (LLVMGetNumOperands(inst) == 1)
    {
        LLVMBasicBlockRef bb = (LLVMBasicBlockRef)LLVMGetOperand(inst, 0);
        std::pair<int, LLVMValueRef> bb_info = bb_labels[bb];

        EMIT("\tjmp {.L%d, %s}", bb_info.first, LLVMPrintValueToString(bb_info.second));
    }
    else if (LLVMGetNumOperands(inst) == 3)
    {
        LLVMBasicBlockRef bb1 = (LLVMBasicBlockRef)LLVMGetOperand(inst, 1);
        LLVMBasicBlockRef bb2 = (LLVMBasicBlockRef)LLVMGetOperand(inst, 2);
        std::pair<int, LLVMValueRef> bb1_info = bb_labels[bb1];
        std::pair<int, LLVMValueRef> bb2_info = bb_labels[bb2];

        LLVMValueRef cond = LLVMGetOperand(inst, 0);

        switch (LLVMGetICmpPredicate(cond))
        {
        case LLVMIntSLT:
            EMIT("\tjl {.L%d, %s}", bb1_info.first, LLVMPrintValueToString(bb1_info.second));
            break;
        case LLVMIntSGT:
            EMIT("\tjg {.L%d, %s}", bb1_info.first, LLVMPrintValueToString(bb1_info.second));
            break;
        case LLVMIntSLE:
            EMIT("\tjle {.L%d, %s}", bb1_info.first, LLVMPrintValueToString(bb1_info.second));
            break;
        case LLVMIntSGE:
            EMIT("\tjge {.L%d, %s}", bb1_info.first, LLVMPrintValueToString(bb1_info.second));
            break;
        case LLVMIntEQ:
            EMIT("\tje {.L%d, %s}", bb1_info.first, LLVMPrintValueToString(bb1_info.second));
            break;
        case LLVMIntNE:
            EMIT("\tjne {.L%d, %s}", bb1_info.first, LLVMPrintValueToString(bb1_info.second));
            break;
        default:
            DEBUG3("ERROR: Invalid branch instruction");
            break;
        }

        EMIT("\tjmp {.L%d, %s}", bb2_info.first, LLVMPrintValueToString(bb2_info.second));
    }
    else
    {
        DEBUG3("ERROR: Invalid branch instruction");
    }
}

// Type: Arithmatic. (add/cmp/mul/sub). {%a = add nsw A, B} or {%a = icmp slt A, B}
void HandleArith(LLVMValueRef inst)
{

    std::string inst_reg = "eax";
    LLVMValueRef op1 = LLVMGetOperand(inst, 0);
    LLVMValueRef op2 = LLVMGetOperand(inst, 1);

    std::unordered_map<int, std::string> op_arith;
    op_arith[LLVMICmp] = "cmpl";
    op_arith[LLVMAdd] = "addl";
    op_arith[LLVMMul] = "imull";
    op_arith[LLVMSub] = "subl";

    // if inst has a physical register, use it or default to eax
    if (reg_map.find(inst) != reg_map.end() && reg_map[inst] != "-1")
    {
        inst_reg = reg_map[inst];
    }

    // Handle OP1
    if (LLVMIsConstant(op1))
    {
        EMIT("\tmovl $%lld, %%%s", LLVMConstIntGetSExtValue(op1), inst_reg.c_str());
    }
    else
    {
        // If op1 has a physical register
        if (reg_map.find(op1) != reg_map.end() && reg_map[op1] != "-1")
        {
            EMIT("\tmovl %%%s, %%%s", reg_map[op1].c_str(), inst_reg.c_str());
        }
        // If op1 is in mem, find offset
        else if (reg_map.find(op1) != reg_map.end())
        {
            int offset = offset_map[op1];
            EMIT("\tmovl %d(%%ebp), %%%s", offset, inst_reg.c_str());
        }
    }

    // Handle OP2
    if (LLVMIsConstant(op2))
    {
        EMIT("\t%s $%lld, %%%s", op_arith[LLVMGetInstructionOpcode(inst)].c_str(), LLVMConstIntGetSExtValue(op2), inst_reg.c_str());
    }
    else
    {
        // If op2 has a physical register
        if (reg_map.find(op2) != reg_map.end() && reg_map[op2] != "-1")
        {
            EMIT("\t%s %%%s, %%%s", op_arith[LLVMGetInstructionOpcode(inst)].c_str(), reg_map[op2].c_str(), inst_reg.c_str());
        }
        // If op2 is in mem, find offset
        else if (reg_map.find(op2) != reg_map.end())
        {
            int offset = offset_map[op2];
            EMIT("\t%s %d(%%ebp), %%%s", op_arith[LLVMGetInstructionOpcode(inst)].c_str(), offset, inst_reg.c_str());
        }
    }

    // Handle destination
    if (reg_map.find(inst) != reg_map.end())
    {
        int offset = offset_map[inst];
        EMIT("\tmovl %%eax, %d(%%ebp)", offset);
    }
}

void print_reg_mem()
{
    for (auto const &x : reg_map)
    {
        DEBUG1("reg_map[%s] = %s\n", LLVMPrintValueToString(x.first), x.second.c_str());
    }
}