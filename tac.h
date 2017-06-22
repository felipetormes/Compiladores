//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#ifndef TAC_H
#define TAC_H

#include "hash.h"

enum tac_type_enum
{
  TAC_SYMBOL,
  TAC_MOVE,
  TAC_ARRAYASSIGN,
  TAC_ARRAYACCESS,
  TAC_ARRAY_EXPRESSION,
  TAC_ADD,
  TAC_SUB,
  TAC_MUL,
  TAC_DIV,
  TAC_LESS,
  TAC_GREATER,
  TAC_LESS_EQUAL,
  TAC_GREATER_EQUAL,
  TAC_EQUAL,
  TAC_NOT_EQUAL,
  TAC_AND,
  TAC_OR,
  TAC_LABEL,
  TAC_BEGINFUN,
  TAC_ENDFUN,
  TAC_IFZ,
  TAC_JUMP,
  TAC_CALL,
  TAC_ARG,
  TAC_PARAMETERS,
  TAC_RET,
  TAC_PRINT,
  TAC_PRINT_LIST,
  TAC_READ
};

typedef struct tac_struct
{
	enum tac_type_enum tac_type;

	hashNode* res;
	hashNode* source1;
	hashNode* source2;

	struct tac_struct* prev;
	struct tac_struct* next;
}TAC;

TAC* tacCreate(enum tac_type_enum type, hashNode* destination, hashNode* source1, hashNode* source2);
TAC* tacJoin(TAC* tac1, TAC* tac2);
TAC* clone(TAC* original);
hashNode* makeTemp();
hashNode* makeLabel();
TAC* reverse(TAC* myTac);
TAC* tacArithmeticOp(enum tac_type_enum type, TAC** children);
TAC* tacIfZero(TAC* test, TAC* thenBlock, TAC* elseBlock);
TAC* tacWhile(TAC* test, TAC* whileBlock);
TAC* tacFor(TAC* test, TAC* forBlock);
TAC* tacCallFunction(TAC* funcId, TAC* args);
TAC* tacParameters(TAC** children);
TAC* tacArguments(TAC** children);
TAC* tacParameters(TAC** children);
TAC* tacPrint(TAC* elements);
TAC* tacReturn(TAC* expression);
TAC* tacAssignment(TAC* variable, TAC* expression);
TAC* tacDeclaration(TAC* id, TAC* literal);
TAC* tacArrayDeclaration(TAC* id, astree* literal_list);
TAC* tacFunctionDefinition(hashNode* node, TAC* scope, TAC* block);
TAC* tacGenerate(astree* ast);

#endif
