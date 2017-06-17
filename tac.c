//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "tac.h"

TAC* tacCreate(enum tac_type_enum type, hashNode* destination, hashNode* source1, hashNode* source2)
{
	TAC* newTac = malloc(sizeof(TAC));

	newTac->tac_type = type;
	newTac->destination = destination;
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
