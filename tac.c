//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "tac.h"

TAC* tacCreate(enum tac_type_enum type, hashNode* res, hashNode* source1, hashNode* source2)
{

	fprintf(stderr, "aquiiii\n");
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

hashNode* StartLabelFunction(hashNode* function)
{
	char* labelName = malloc(strlen("___") + strlen(function->symbol.text) + strlen("_start") + strlen("___") + 1);

	sprintf(labelName, "___%s_start___", function->symbol.text);

	return hashInsert(labelName, SYMBOL_IDENTIFIER);
}

hashNode* EndLabelFunction(hashNode* function)
{
	char* labelName = malloc(strlen("___") + strlen(function->symbol.text) + strlen("_end") + strlen("___") + 1);

	sprintf(labelName, "___%s_end___", function->symbol.text);

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

TAC* tacCallFunction(TAC* funcId, TAC* args)
{
	return tacJoin(tacJoin(args, funcId), tacCreate(TAC_CALL, makeTemp(), funcId->res, NULL));
}

TAC* tacparameters(TAC** children)
{
	if(children[0] == NULL && children[1] == NULL)
		return NULL;

	if(children[2] == NULL)
	{
		return tacJoin(children[1], tacCreate(TAC_PARAMETERS, children[1]->res, NULL, NULL));
	}
	else
	{
		return tacJoin(tacCreate(TAC_PARAMETERS, children[2]->res, NULL, NULL), tacJoin(children[0], children[2]));
	}
}

TAC* tacArguments(TAC** children)
{
	if(children[0] == NULL)
		return NULL;

	if(children[1] == NULL)
	{
		return tacJoin(children[0], tacCreate(TAC_ARG, NULL, children[0]->res, NULL));
	}
	else
	{
		return tacJoin(children[0], tacJoin(children[1], tacCreate(TAC_ARG, NULL, children[1]->res, NULL)));
	}
}

TAC* tacPrintList(TAC** children)
{
	if(children[0] == NULL)
		return NULL;

	if(children[1] == NULL)
	{
		return tacJoin(children[0], tacJoin(children[1], tacJoin(children[2], tacJoin(children[3], tacCreate(TAC_PRINT_LIST, NULL, children[0]->res, NULL)))));
	}
	else
	{
		return tacJoin(children[0], tacJoin(children[1], tacJoin(children[2], tacJoin(children[3], tacCreate(TAC_PRINT_LIST, NULL, children[1]->res, NULL)))));
	}
}

TAC* tacPrint(TAC* elements)
{
	return tacJoin(elements, tacCreate(TAC_PRINT,NULL,NULL,NULL));
}

TAC* tacReturn(TAC* expression)
{
	return tacJoin(expression, tacCreate(TAC_RET, NULL, expression->res, NULL));
}

TAC* tacAssignment(TAC* variable, TAC* expression)
{
	switch(variable->tac_type)
	{
		case TAC_SYMBOL:
		{
			return tacJoin(expression, tacCreate(TAC_MOVE, variable->res, expression->res, NULL));
			break;
		}

		case TAC_ARRAYACCESS:
		{
			return tacJoin(expression, tacCreate(TAC_ARRAYASSIGN, variable->res, variable->source1, expression->res));
			break;
		}

	}
}

TAC* tacDeclaration(TAC* id, TAC* literal)
{
	return tacCreate(TAC_MOVE, id->res, literal->res, NULL);
}

TAC* tacArrayDeclaration(TAC* id, astree* literal_list)
{
	if(literal_list == NULL)
		return NULL;

	if(literal_list->child[0] != NULL)
	{
		if(literal_list->child[0]->child[1] == NULL)
			return NULL;

		return tacJoin(tacArrayDeclaration(id,literal_list->child[0]), tacCreate(TAC_ARRAYASSIGN, id->res, literal_list->child[0]->child[1]->node, NULL));
	}
	else
	{
		return tacJoin(tacArrayDeclaration(id,literal_list->child[0]), tacCreate(TAC_ARRAYASSIGN, id->res, literal_list->child[1]->node, NULL));
	}
}

TAC* tacFunctionDefinition(hashNode* node, TAC* scope, TAC* block)
{
	hashNode* start_label = StartLabelFunction(node);
	hashNode* end_label = EndLabelFunction(node);

	return
		tacJoin(
			tacJoin(
				tacJoin(
						tacJoin(
							tacJoin(
								tacJoin(
									tacCreate(TAC_JUMP,end_label,NULL,NULL),
									tacCreate(TAC_LABEL,start_label,NULL,NULL)
								),
								tacCreate(TAC_BEGINFUN, node, NULL, NULL)
							),
							scope
						),
					block
				),
				tacCreate(TAC_ENDFUN, node, NULL, NULL)
			),
			tacCreate(TAC_LABEL,end_label,NULL,NULL)
		);
}

TAC* tacGenerate(astree* ast)
{
	if(ast == NULL)
		return NULL;

	TAC* childTac[4];

	childTac[0] = tacGenerate(ast->child[3]);
	childTac[1] = tacGenerate(ast->child[2]);
	childTac[2] = tacGenerate(ast->child[1]);
	childTac[3] = tacGenerate(ast->child[0]);

	TAC* result;

	fprintf(stderr, "%d\n", ast->node_type);

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

		case ARRAYACCESS:
		{
			result = tacCreate(TAC_ARRAYACCESS, childTac[0]->res, childTac[1]->res, NULL);
			break;
		}

		case ASSIGNMENT:
		{
			result = tacAssignment(childTac[3], childTac[2]);
			break;
		}

		case FUNCTIONCALL:
		{
			result = tacCallFunction(childTac[0], childTac[1]);
			break;
		}

		case ARGUMENTLIST:
		{
			result = tacArguments(childTac);
			break;
		}

		case PRINTLIST:
		{
			result = tacPrintList(childTac);
			break;
		}

		case RETURN:
		{
			result = tacReturn(childTac[0]);
			break;
		}

		case DECLARATION:
		{
			result = tacDeclaration(childTac[3], childTac[1]);
			break;
		}

		case ARRAYDECLARATION:
		{
			result = tacArrayDeclaration(childTac[1], ast->child[3]);
			break;
		}

		case READ:
		{
			result = tacCreate(TAC_READ, NULL, childTac[0]->res, NULL);
			break;
		}

		case PRINT:
		{
			result = tacPrint(childTac[0]);
			break;
		}

		case FUNCTIONDEFINITION:
		{
			result = tacFunctionDefinition(ast->child[0]->child[1]->node, childTac[0], childTac[1]);
			break;
		}

		case PARAMETERLIST:
		{
			result = tacparameters(childTac);
			break;
		}

		case BLOCK:
		case COMMANDLIST:
		case PROGRAM:
		default:
			result = tacJoin(tacJoin(tacJoin(childTac[0], childTac[1]), childTac[2]), childTac[3]);
			break;

	}

}
