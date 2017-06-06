//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#include "hash.h"
#include "astree.h"

#define FALSE 0
#define TRUE 1

void first_pass(astree* ast);
void typeToString(int type, char* str);
int compatible(dataType t0, dataType t1);
int same_types(astree* parameter, astree* argument);
int checkParameters(astree* parameters, astree* arguments, int* expected, int* given);
int typeCheck(astree* ast);
int verify(astree* ast);
