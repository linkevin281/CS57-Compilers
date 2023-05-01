// Kevin Lin
// Semantic Analysis for MiniC
// 4/24/2023

#include "libraries/ast.h"
#include <string.h>
#include <stdio.h>
#include <deque>
#include <set>

// DEBUG MACROS //
#define DEBUG(...)\
if(verbose && DEB) {\
        printf("DEBUG : %s, %d ",__FUNCTION__, __LINE__);\
        printf(__VA_ARGS__);\
}\

#define DEB 1

// SET VERBOSE TO 1 TO PRINT DEBUG MESSAGES //
int verbose = 0;

// FUNCTION PROTOTYPES // 
bool traverse_ast(astNode* cur_node, deque<set<char*>>* symbol_table);
bool handle_stmt_case(astNode* cur_node, deque<set<char*>>* symbol_table);


// FILE ALGORITHM // 
/* 
Data structures required: A stack of symbol tables.

For each block statement/function statement in the miniC program that your code is compiling, you will have a symbol table that stores the names of the variables/parameters that are declared in that block/function. A symbol table can be implemented using C++ STL vector or set of strings (char *). All symbol tables will be stored in a stack. This outer container (stack) can be implemented using C++ STL stack or vector.

Algorithm:

Let the symbol tables be stored as a set 

Initialize the stack of symbol tables to empty
Visit all nodes in the AST using a tree traversal algorithm and for every node visited do the following:
        if node is a block statement node: 
                create a new symbol table curr_sym_table and push it to symbol table stack
                visit all nodes in the statement list of block statement 
                pop top of the stack
        if node is a function node: 
                create a new symbol table curr_sym_table and push it to symbol table stack
                if func node has a parameter add parameter to c2urr_sym_table
                visit the body node of the function node
                pop top of the stack
        if node is a declaration statement, add the variable to symbol table that is at the top of the stack
        if node is a variable node then check if it appears in one of the symbol tables on the stack, if it does not then emit an error message with name of the variable
        ignore the extern nodes
        for all other node types visit all the child nodes of the current node

For tree traversal algorithm, it will be pre-order traversal, but for block statement and function nodes your code will revisit the node to pop from the symbol table stack. */



bool semantic_analysis(astNode *root){
        // create deque 
        deque<set<char*>> symbol_table = deque<set<char*>>();

        return traverse_ast(root, &symbol_table);


}

bool traverse_ast(astNode* cur_node, deque<set<char*>>* symbol_stack){

        bool return_bool = true;

        if (cur_node == NULL) {
                return return_bool;
        }

        switch(cur_node->type) {
                case ast_prog:
                {
                        return_bool = return_bool && traverse_ast(cur_node->prog.ext1, symbol_stack); 
                        return_bool = return_bool && traverse_ast(cur_node->prog.ext2, symbol_stack);
                        return_bool = return_bool && traverse_ast(cur_node->prog.func, symbol_stack);
                        break;
                }
                case ast_func:
                {
                        // create new symbol table
                        // push to stack
                        // if func node has a parameter add parameter to curr_sym_table
                        // visit the body node of the function node
                        // pop top of stack
                        DEBUG("found func\n");
                        set<char*> cur_sym_table = set<char*>();

                        cur_sym_table.insert(cur_node->func.param->var.name);
                        symbol_stack->push_back(cur_sym_table);
                        if(cur_node->func.param != NULL) {
                                symbol_stack->back().insert(cur_node->func.param->var.name);
                        }
                        return_bool = return_bool && traverse_ast(cur_node->func.body, symbol_stack);
                        symbol_stack->pop_back();
                        break;
                }
                case ast_stmt:
                {
                        DEBUG("found stmt\n");
                        return_bool = return_bool && handle_stmt_case(cur_node, symbol_stack);
                        break;   
                }
                case ast_var:
                {
                        // check if it appears in one of the symbol tables on the stack, if it does not then emit an error message with name of the variable
                       
                        DEBUG("found var\n");

                        // iterate through symbol table and print out variable names
                        DEBUG("printing symbol table\n");
                        for (set<char*>::iterator it = symbol_stack->back().begin(); it != symbol_stack->back().end(); it++) {
                                DEBUG("%s, ", *it);
                        }
                        DEBUG("\n");
                        
                        bool found = false;

                        // If the variable is found, set found to true
                        for (set<char*>::iterator it = symbol_stack->back().begin(); it != symbol_stack->back().end(); it++) {
                                if (strcmp(*it, cur_node->var.name) == 0) {
                                        found = true;
                                        break;
                                }                                
                        }

                        if (!found) {
                                DEBUG("variable %s not found in symbol table\n", cur_node->var.name);
                                return_bool = false;
                        }
                        break;
                }
                case ast_extern:
                {
                        // ignore the extern nodes
                        DEBUG("found extern\n");
                        break;
                }
                case ast_cnst:
                {
                        // ignore the constant nodes
                        DEBUG("found constant\n");
                        break;
                }
                case ast_rexpr:
                {
                        // for all other node types visit all the child nodes of the current node
                        DEBUG("found rexpr\n");
                        return_bool = return_bool && traverse_ast(cur_node->rexpr.lhs, symbol_stack);
                        return_bool = return_bool && traverse_ast(cur_node->rexpr.rhs, symbol_stack);
                        break;
                }
                case ast_bexpr:
                {
                        // for all other node types visit all the child nodes of the current node
                        DEBUG("found bexpr\n");
                        return_bool = return_bool && traverse_ast(cur_node->bexpr.lhs, symbol_stack);
                        return_bool = return_bool && traverse_ast(cur_node->bexpr.rhs, symbol_stack);
                        break;
                }
                case ast_uexpr:
                {
                        // for all other node types visit all the child nodes of the current node
                        DEBUG("found uexpr\n");
                        return_bool = return_bool && traverse_ast(cur_node->uexpr.expr, symbol_stack);

                        break;
                }

                default:
                {
                        break;
                }

        }

        return return_bool;
}


bool handle_stmt_case(astNode* cur_node, deque<set<char*>>* symbol_stack) {

        bool return_bool = true;

        if (cur_node == NULL) {
                return return_bool;
        }

        switch(cur_node->stmt.type) {
                case ast_block:
                {
                        DEBUG("found block\n");
                        // create a new symbol table curr_sym_table and push it to symbol table stack
                        set<char*> cur_sym_table = set<char*>();

                        for (set<char*>::iterator it = symbol_stack->back().begin(); it != symbol_stack->back().end(); it++) {
                                cur_sym_table.insert(*it);
                        }

                        // iterate through previous symbol table and add to new symbol table
                        // we do this to maintain the current scope for nested blocks 
                        symbol_stack->push_back(cur_sym_table);
                        DEBUG("stack pushed, table at memory: %p\n | size is %ld\n", &symbol_stack->back(), symbol_stack->size());

                        // visit all the statements in the block
                        vector<astNode*>* stmt_list = cur_node->stmt.block.stmt_list;
                        DEBUG("found %ld statements in block\n", stmt_list->size());
                        
                        for (int i = 0; i < stmt_list->size(); i++) {
                                DEBUG("statement %d is of type %d, ", i, stmt_list->at(i)->stmt.type);
                        }
                        DEBUG("\n");
                        for (int i = 0; i < stmt_list->size(); i++) {
                                return_bool = return_bool && traverse_ast(stmt_list->at(i), symbol_stack);
                        }

                        // pop top of the stack
                        DEBUG("stack popped, table at memory: %p\n", &symbol_stack->back());
                        symbol_stack->pop_back();
                        DEBUG("stack size is now %ld\n", symbol_stack->size());


                        break;
                }
                case ast_call:
                {
                        DEBUG("found call\n");
                        if (cur_node->stmt.call.param != NULL) {
                                return_bool = return_bool && traverse_ast(cur_node->stmt.call.param, symbol_stack); 
                        }      
                }
                case ast_ret:
                {
                        DEBUG("found ret\n");
                        if (cur_node->stmt.ret.expr != NULL) {
                                return_bool = return_bool && traverse_ast(cur_node->stmt.ret.expr, symbol_stack);
                        }
                }
                case ast_while:
                {
                        DEBUG("found while\n");
                        return_bool = return_bool && traverse_ast(cur_node->stmt.whilen.cond, symbol_stack);
                        return_bool = return_bool && traverse_ast(cur_node->stmt.whilen.body, symbol_stack);
                }
                case ast_if:
                {
                        DEBUG("found if\n");
                        return_bool = return_bool && traverse_ast(cur_node->stmt.ifn.cond, symbol_stack);
                        return_bool = return_bool && traverse_ast(cur_node->stmt.ifn.if_body, symbol_stack);    

                        if (cur_node->stmt.ifn.else_body != NULL) {
                                return_bool = return_bool && traverse_ast(cur_node->stmt.ifn.else_body, symbol_stack);   
                        }
                }
                case ast_decl:
                {
                        // add the variable to symbol table that is at the top of the stack
                        DEBUG("Found decl\n");
                        DEBUG("Inserting %s into symbol table at memory: %p\n", cur_node->stmt.decl.name, &symbol_stack->back());
                        symbol_stack->back().insert(cur_node->stmt.decl.name);

                        for (set<char*>::iterator it = symbol_stack->back().begin(); it != symbol_stack->back().end(); it++) {
                                DEBUG("%s, ", *it);
                        }
                        DEBUG("\n");
                        
                        break;
                }
                case ast_asgn:
                {
                        // traversal order?
                        DEBUG("found asgn\n");
                        return_bool = return_bool && traverse_ast(cur_node->stmt.asgn.lhs, symbol_stack);
                        return_bool = return_bool && traverse_ast(cur_node->stmt.asgn.rhs, symbol_stack);
                        break;
                }
                default:
                {
                        // for all other node types visit all the child nodes of the current node
                        break;
                }

        }
        return return_bool;
}

