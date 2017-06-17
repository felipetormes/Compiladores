//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#include "hash.h"

enum tac_type_enum
{
  TAC_SYMBOL,
  TAC_MOVE,
  TAC_ADD,
  TAC_MUL,
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
}

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
