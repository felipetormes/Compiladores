//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#ifndef TAC_H
#define TAC_H

#include "hash.h"

enum tac_type_enum
{
  TAC_SYMBOL,
  TAC_MOVE,
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
  TAC_RET,
  TAC_PRINT,
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
TAC* tacFor(TAC* atr, TAC* lit, TAC* forBlock);
TAC* tacGenerate(astree* ast);

#endif
