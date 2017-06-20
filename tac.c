//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "tac.h"

TAC* tacCreate(enum tac_type_enum type, hashNode* res, hashNode* source1, hashNode* source2)
{
	TAC* newTac = malloc(sizeof(TAC));

	newTac->tac_type = type;
	newTac->res = res;
	newTac->source1 = source1;
	newTac->source2 = source2;
	newTac->prev = NULL;
	newTac->next = NULL;

	return newTac;
}

TAC* tacJoin(TAC* tac1, TAC* tac2)
{
	if(tac1 == NULL)
		return tac2;

	if(tac2 == NULL)
		return tac1;

	TAC* aux = tac2;

	while(aux->prev != NULL)
	{
		aux = aux->prev;
	}

	aux->prev = tac1;
	tac1->next = aux;

	return tac2;
}

TAC* clone(TAC* original)
{
	TAC* tac_clone = tacCreate(original->tac_type, original->res, original->source1, original->source2);

	TAC* clone_ptr = tac_clone->prev;
	TAC* original_ptr = original->prev;

	while(original_ptr != NULL)
	{
		clone_ptr = tacCreate(original_ptr->tac_type, original_ptr->res, original_ptr->source1, original_ptr->source2);
		clone_ptr->prev = original_ptr->prev;

		original_ptr = original_ptr->prev;
		clone_ptr = clone_ptr->prev;
	}

	return tac_clone;
}

hashNode* makeTemp()
{
	static int count = 0;
	char* tempName = malloc(10 + sizeof(int) * 8 + 1);

	sprintf(tempName, "___temp%d___", count);
	count++;

	return hashInsert(tempName, SYMBOL_IDENTIFIER);
}

hashNode* makeLabel()
{
	static int count = 0;
	char* labelName = malloc(11 + sizeof(int) * 8 + 1);

	sprintf(labelName, "___label%d___", count);
	count++;

	return hashInsert(labelName, SYMBOL_IDENTIFIER);
}

TAC* reverse(TAC* myTac)
{
	if(myTac == NULL)
		return NULL;

	TAC* aux = myTac;

	while(aux->prev != NULL)
	{
		aux = aux->prev;
	}

	return aux;
}

TAC* tacArithmeticOp(enum tac_type_enum type, TAC** children)
{
	hashNode* temp1 = children[0]->res;
	hashNode* temp2 = children[1]->res;

	return tacJoin(tacJoin(children[0], children[1]), tacCreate(type, makeTemp(), temp1, temp2));
}

TAC* tacIfZero(TAC* test, TAC* thenBlock, TAC* elseBlock)
{
	TAC* result;
	hashNode* testResult = test->res;
	hashNode* elseLabel = makeLabel();

	TAC* ifThen = tacJoin(tacJoin(test, tacCreate(TAC_IFZ, elseLabel, testResult, NULL)), thenBlock);

	if(elseBlock == NULL)
	{
		result = tacJoin(ifThen, tacCreate(TAC_LABEL, elseLabel, NULL, NULL));
	}
	else
	{
		hashNode* endLabel = makeLabel();

		result =
			tacJoin(
				tacJoin(
					tacJoin(
						tacJoin(
							ifThen,
							tacCreate(TAC_JUMP, endLabel, NULL, NULL)
						),
						tacCreate(TAC_LABEL, elseLabel, NULL, NULL)
					),
					elseBlock
				),
				tacCreate(TAC_LABEL, endLabel, NULL, NULL)
			);
	}

	return result;
}

TAC* tacWhile(TAC* test, TAC* whileBlock)
{
	hashNode* testResult = test->res;
	hashNode* loopLabel = makeLabel();
	hashNode* endLabel = makeLabel();

	TAC* new_test = clone(test);

	return
		tacJoin(
			tacJoin(
				tacJoin(
					tacJoin(
						test,
						tacJoin(
							tacCreate(TAC_LABEL, loopLabel, NULL, NULL),
							tacCreate(TAC_IFZ, endLabel, testResult, NULL)
						)
					),
					whileBlock
				),
				tacJoin(
					new_test,
					tacCreate(TAC_JUMP, loopLabel, NULL, NULL)
				)
			),
			tacCreate(TAC_LABEL, endLabel, NULL, NULL)
		);
}

TAC* tacFor(TAC* atr, TAC* lit, TAC* forBlock)
{

}

TAC* tacGenerate(astree* ast)
{
	if(ast == NULL)
		return NULL;

	TAC* childTac[4];

	childTac[0] = tacGenerate(ast->child[0]);
	childTac[1] = tacGenerate(ast->child[1]);
	childTac[2] = tacGenerate(ast->child[2]);
	childTac[3] = tacGenerate(ast->child[3]);

	TAC* result;

	switch (ast->node_type)
	{
		case LITERAL:
		{
			result = tacCreate(TAC_SYMBOL, ast->node, NULL, NULL);
			break;
		}

		case IDENTIFIER:
		{
			result = tacCreate(TAC_SYMBOL, ast->node, NULL, NULL);
			break;
		}

		case ADDITION:
		{
			result = tacArithmeticOp(TAC_ADD, childTac);
			break;
		}

		case SUBTRACTION:
		{
			result = tacArithmeticOp(TAC_SUB, childTac);
			break;
		}

		case MULTIPLICATION:
		{
			result = tacArithmeticOp(TAC_MUL, childTac);
			break;
		}

		case DIVISION:
		{
			result = tacArithmeticOp(TAC_DIV, childTac);
			break;
		}

		case LESSERTHAN:
		{
			result = tacArithmeticOp(TAC_LESS, childTac);
			break;
		}

		case GREATERTHAN:
		{
			result = tacArithmeticOp(TAC_GREATER, childTac);
			break;
		}

		case LESSEREQUAL:
		{
			result = tacArithmeticOp(TAC_LESS_EQUAL, childTac);
			break;
		}

		case GREATEREQUAL:
		{
			result = tacArithmeticOp(TAC_GREATER_EQUAL, childTac);
			break;
		}

		case EQUAL:
		{
			result = tacArithmeticOp(TAC_EQUAL, childTac);
			break;
		}

		case NOTEQUAL:
		{
			result = tacArithmeticOp(TAC_NOT_EQUAL, childTac);
			break;
		}

		case AND:
		{
			result = tacArithmeticOp(TAC_AND, childTac);
			break;
		}

		case OR:
		{
			result = tacArithmeticOp(TAC_OR, childTac);
			break;
		}

		case WHENTHEN:
		case WHENTHENELSE:
		{
			result = tacIfZero(childTac[0], childTac[1], childTac[2]);
			break;
		}

		case WHILE:
		{
			result = tacWhile(childTac[0], childTac[1]);
			break;
		}

		case FOR:
		{
			result = tacFor(childTac[0], childTac[1], childTac[2]);
			break;
		}

	}

}
