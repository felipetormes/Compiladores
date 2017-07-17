//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#include "hash.h"
#include "tac.h"

char* lvalue(hashNode* node);
char* rvalue(hashNode* node);
void generateAssembly_move(hashNode* res, hashNode* source);
void generateAssembly_add(hashNode* res, hashNode* source1, hashNode* source2);
void generateAssembly_sub(hashNode* res, hashNode* source1, hashNode* source2);
void generateAssembly_mul(hashNode* res, hashNode* source1, hashNode* source2);
void generateAssembly_div(hashNode* res, hashNode* source1, hashNode* source2);
void generateAssembly_less(hashNode* res, hashNode* source1, hashNode* source2);
void generateAssembly_less_equal(hashNode* res, hashNode* source1, hashNode* source2);
void generateAssembly_greater(hashNode* res, hashNode* source1, hashNode* source2);
void generateAssembly_greater_equal(hashNode* res, hashNode* source1, hashNode* source2);
void generateAssembly_equal(hashNode* res, hashNode* source1, hashNode* source2);
void generateAssembly_not_equal(hashNode* res, hashNode* source1, hashNode* source2);
void generateAssembly_and(hashNode* res, hashNode* source1, hashNode* source2);
void generateAssembly_or(hashNode* res, hashNode* source1, hashNode* source2);
void generateAssembly_ifz(hashNode* res, hashNode* source);
void generateAssembly_arrayAssign(hashNode* res, hashNode* source1);
void generateAssembly_arrayAccess(hashNode* res, hashNode* source1, hashNode* source2);
void generateAssembly_label(hashNode* res);
void generateAssembly_jump(hashNode* res);
void generateAssembly_ret(hashNode* source);
void generateAssembly_begin_fun(hashNode* node);
void generateAssembly_end_fun(hashNode* node);
void generateAssembly_call(hashNode* node, hashNode* res);
void generateAssembly_arg(hashNode* source);
void generateAssembly_getarg(hashNode* res);
int value(symbolType symbol);
void generate_data_section(hashTable_ref symbol_table);
void generateAssembly_output_arg(hashNode* source);
void generateAssembly_print();
void generateAssembly_read(hashNode* res);
void generateAssemblyOf(TAC* tac);
void generateAssembly(TAC* tacs, const char* filename);
