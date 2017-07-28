//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "tac.h"

TAC* tacCreate(enum tac_type_enum type, hashNode* res, hashNode* source1, hashNode* source2)
{

	//fprintf(stderr, "aquiiii\n");
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

TAC* tacCopy(TAC* original)
{
	TAC* tac_copy = tacCreate(original->tac_type, original->res, original->source1, original->source2);

	TAC* copy_ptr = tac_copy->prev;
	TAC* original_ptr = original->prev;

	while(original_ptr != NULL)
	{
		copy_ptr = tacCreate(original_ptr->tac_type, original_ptr->res, original_ptr->source1, original_ptr->source2);
		copy_ptr->prev = original_ptr->prev;

		original_ptr = original_ptr->prev;
		copy_ptr = copy_ptr->prev;
	}

	return tac_copy;
}

hashNode* makeTemp()
{
	static int count = 0;
	char* tempName = malloc(10 + sizeof(int) * 8 + 1);

	sprintf(tempName, "___temp%d___", count);
	count++;

	hashNode* temp = hashInsert(tempName, SYMBOL_IDENTIFIER);

	temp->symbol.nature = SCALAR;
	//temp->symbol.value.intLit = 0;

	return temp;
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

TAC* tacReverse(TAC* myTac)
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

void printCode(TAC* myTac)
{
	TAC* aux;

	const char* tacNames[] = {"TAC_SYMBOL",
				  "TAC_MOVE",
				  "TAC_ARRAYASSIGN",
				  "TAC_ARRAYACCESS",
				  "TAC_ARRAY_EXPRESSION",
				  "TAC_ADD",
				  "TAC_SUB",
				  "TAC_MUL",
				  "TAC_DIV",
				  "TAC_LESS",
				  "TAC_GREATER",
				  "TAC_LESS_EQUAL",
				  "TAC_GREATER_EQUAL",
				  "TAC_EQUAL",
				  "TAC_NOT_EQUAL",
				  "TAC_AND",
				  "TAC_OR",
				  "TAC_LABEL",
				  "TAC_BEGINFUN",
				  "TAC_ENDFUN",
				  "TAC_IFZ",
				  "TAC_JUMP",
				  "TAC_CALL",
				  "TAC_ARG",
				  "TAC_PARAMETERS",
				  "TAC_RET",
				  "TAC_PRINT",
				  "TAC_PRINT_LIST",
				  "TAC_READ"};

	for(aux = myTac; aux != NULL; aux = aux->next)
	{
		if(aux->tac_type != TAC_SYMBOL)
		{

			fprintf(stderr,"%s ", tacNames[aux->tac_type]);
			fprintf(stderr, " ");

			if(aux->res)
			{
				switch(aux->res->symbol.type)
				{
					case SYMBOL_LIT_INTEGER: fprintf(stderr, "%d ", aux->res->symbol.value.intLit); break;
					case SYMBOL_LIT_CHAR: fprintf(stderr, "%c ", aux->res->symbol.value.charLit); break;
					case SYMBOL_LIT_REAL: fprintf(stderr, "%f ", aux->res->symbol.value.realLit); break;
					case SYMBOL_LIT_STRING: fprintf(stderr, "%c%s%c ", 34, aux->res->symbol.value.stringLit, 34); break;
					case SYMBOL_IDENTIFIER: fprintf(stderr, "%s ", aux->res->symbol.value.identifier); break;
				}
			}
			else
			{
				fprintf(stderr, "NULL ");
			}

			if(aux->source1)
			{
				switch(aux->source1->symbol.type)
				{
					case SYMBOL_LIT_INTEGER: fprintf(stderr, "%d ", aux->source1->symbol.value.intLit); break;
					case SYMBOL_LIT_CHAR: fprintf(stderr, "%c ", aux->source1->symbol.value.charLit); break;
					case SYMBOL_LIT_REAL: fprintf(stderr, "%f ", aux->source1->symbol.value.realLit); break;
					case SYMBOL_LIT_STRING: fprintf(stderr, "%c%s%c ", 34, aux->source1->symbol.value.stringLit, 34); break;
					case SYMBOL_IDENTIFIER: fprintf(stderr, "%s ", aux->source1->symbol.value.identifier); break;
				}
			}
			else
			{
				fprintf(stderr, "NULL ");
			}

			if(aux->source2)
			{
				switch(aux->source2->symbol.type)
				{
					case SYMBOL_LIT_INTEGER: fprintf(stderr, "%d ", aux->source2->symbol.value.intLit); break;
					case SYMBOL_LIT_CHAR: fprintf(stderr, "%c ", aux->source2->symbol.value.charLit); break;
					case SYMBOL_LIT_REAL: fprintf(stderr, "%f ", aux->source2->symbol.value.realLit); break;
					case SYMBOL_LIT_STRING: fprintf(stderr, "%c%s%c ", 34, aux->source2->symbol.value.stringLit, 34); break;
					case SYMBOL_IDENTIFIER: fprintf(stderr, "%s ", aux->source2->symbol.value.identifier); break;
				}
			}
			else
			{
				fprintf(stderr, "NULL ");
			}

			fprintf(stderr, "\n");

		}
	}
}

TAC* tacArithmeticOp(enum tac_type_enum type, TAC** children)
{
	hashNode* temp1 = children[3]->res;
	hashNode* temp2 = children[2]->res;

	return tacJoin(tacJoin(children[3], children[2]), tacCreate(type, makeTemp(), temp1, temp2));
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

	TAC* new_test = tacCopy(test);

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

TAC* tacFor(TAC* test, TAC* forBlock)
{
	hashNode* testResult = test->res;
	hashNode* loopLabel = makeLabel();
	hashNode* endLabel = makeLabel();

	TAC* new_test = tacCopy(test);

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
					forBlock
				),
				tacJoin(
					new_test,
					tacCreate(TAC_JUMP, loopLabel, NULL, NULL)
				)
			),
			tacCreate(TAC_LABEL, endLabel, NULL, NULL)
		);
}

TAC* tacCallFunction(TAC* funcId, TAC* args)
{
	return tacJoin(tacJoin(args, funcId), tacCreate(TAC_CALL, makeTemp(), funcId->res, NULL));
}

TAC* tacParameters(TAC** children)
{
	if(children[2] == NULL && children[1] == NULL)
	{
		return NULL;
	}

	if(children[3] == NULL)
	{
		return tacJoin(children[1], tacCreate(TAC_PARAMETERS, children[1]->res, NULL, NULL));
	}
	else
	{
		return tacJoin(tacCreate(TAC_PARAMETERS, children[1]->res, NULL, NULL), tacJoin(children[2], children[1]));
	}
}

TAC* tacArguments(TAC** children)
{
	if(children[3] == NULL)
	{
		return NULL;
	}

	if(children[2] == NULL)
	{
		return tacJoin(children[3], tacCreate(TAC_ARG, NULL, children[3]->res, NULL));
	}
	else
	{
		return tacJoin(children[3], tacJoin(children[2], tacCreate(TAC_ARG, NULL, children[3]->res, NULL)));
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

TAC* tacPrintList(TAC** children)
{
	if(children[3] == NULL)
	{
		return NULL;
	}

	if(children[2] == NULL)
	{
		return tacJoin(children[3], tacCreate(TAC_PRINT_LIST, NULL, children[3]->res, NULL));
	}
	else
	{
		return tacJoin(children[3], tacJoin(children[2], tacCreate(TAC_PRINT_LIST, NULL, children[2]->res, NULL)));
	}
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
								tacCreate(TAC_LABEL,start_label,NULL,NULL),
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

	//fprintf(stderr, "%d\n", ast->node_type);

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
			//fprintf(stderr, "%s\n", result->res->symbol.text);
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
			//fprintf(stderr, "%d\n", result->res->symbol.value.intLit);
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
			result = tacIfZero(childTac[3], childTac[2], childTac[1]);
			break;
		}

		case WHILE:
		{
			result = tacWhile(childTac[3], childTac[2]);
			break;
		}

		case FOR:
		{
			TAC* test = tacArithmeticOp(TAC_LESS_EQUAL, childTac);

			result = tacFor(test, childTac[1]);
			break;
		}

		case ARRAYEXPRESION:
		{
			result = tacCreate(TAC_ARRAY_EXPRESSION, childTac[3]->res, childTac[2]->res, NULL);
			break;
		}

		case ASSIGNMENT:
		{
			result = tacAssignment(childTac[3], childTac[2]);
			break;
		}

		case FUNCTIONCALL:
		{
			result = tacCallFunction(childTac[3], childTac[2]);
			break;
		}

		case ARGUMENTLIST:
		{
			result = tacArguments(childTac);
			break;
		}

		case RETURN:
		{
			result = tacReturn(childTac[3]);
			break;
		}

		case DECLARATION:
		{
			result = tacDeclaration(childTac[3], childTac[1]);
			break;
		}

		case ARRAYDECLARATION:
		{
			result = tacArrayDeclaration(childTac[3], ast->child[3]);
			break;
		}

		case READ:
		{
			result = tacCreate(TAC_READ, childTac[3]->res, NULL, NULL);
			break;
		}

		case PRINT:
		{
			result = tacPrint(childTac[3]);
			break;
		}

		case PRINTLIST:
		{
			result = tacPrintList(childTac);
			break;
		}

		case FUNCTIONDEFINITION:
		{
			result = tacFunctionDefinition(ast->child[0]->child[1]->node, childTac[3], childTac[2]);
			break;
		}

		case PARAMETERLIST:
		{
			result = tacParameters(childTac);
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

TAC* optmize(TAC* tacs)
{
	TAC* aux;
	TAC* aux1;
	TAC* aux2;

	for(aux = tacs; aux->next != NULL; aux = aux->next)
	{
		if(aux->tac_type == TAC_ADD)
		{
			for(aux1 = aux->next; aux1->next != NULL; aux1 = aux1->next)
			{
				if(aux1->tac_type == TAC_ADD)
				{
					if((aux->source1 == aux1->source1) && (aux->source2 == aux1->source2))
					{
						aux1->res->symbol.value.identifier = aux->res->symbol.value.identifier;
						aux1->res->symbol.text = aux->res->symbol.text;

						aux1->tac_type = TAC_SYMBOL;
						aux1->source1 = NULL;
						aux1->source2 = NULL;
					}
				}
			}
		}

		if(aux->tac_type == TAC_SUB)
		{
			for(aux1 = aux->next; aux1->next != NULL; aux1 = aux1->next)
			{
				if(aux1->tac_type == TAC_SUB)
				{
					if((aux->source1 == aux1->source1) && (aux->source2 == aux1->source2))
					{
						aux1->res->symbol.value.identifier = aux->res->symbol.value.identifier;
						aux1->res->symbol.text = aux->res->symbol.text;

						aux1->tac_type = TAC_SYMBOL;
						aux1->source1 = NULL;
						aux1->source2 = NULL;
					}
				}
			}
		}

		if(aux->tac_type == TAC_MUL)
		{
			for(aux1 = aux->next; aux1->next != NULL; aux1 = aux1->next)
			{
				if(aux1->tac_type == TAC_MUL)
				{
					if((aux->source1 == aux1->source1) && (aux->source2 == aux1->source2))
					{
						aux1->res->symbol.value.identifier = aux->res->symbol.value.identifier;
						aux1->res->symbol.text = aux->res->symbol.text;

						aux1->tac_type = TAC_SYMBOL;
						aux1->source1 = NULL;
						aux1->source2 = NULL;
					}
				}
			}
		}

		if(aux->tac_type == TAC_DIV)
		{
			for(aux1 = aux->next; aux1->next != NULL; aux1 = aux1->next)
			{
				if(aux1->tac_type == TAC_DIV)
				{
					if((aux->source1 == aux1->source1) && (aux->source2 == aux1->source2))
					{
						aux1->res->symbol.value.identifier = aux->res->symbol.value.identifier;
						aux1->res->symbol.text = aux->res->symbol.text;

						aux1->tac_type = TAC_SYMBOL;
						aux1->source1 = NULL;
						aux1->source2 = NULL;
					}
				}
			}
		}
	}

	return aux;
}
