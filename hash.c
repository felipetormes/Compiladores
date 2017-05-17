//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

hashTable_ref hashTable;

int equal(symbolType symbol1, symbolType symbol2)
{
	return (symbol1.type == symbol2.type) && (strcmp(symbol1.text, symbol2.text) == 0);
}

hashNode* nullTable(void)
{
	return NULL;
}

int isEmpty(hashNode* node)
{
	return node == NULL;
}

hashNode* newHashNode(symbolType symbol, hashNode* node)
{
		hashNode* newNode = (hashNode*) malloc( sizeof(hashNode) );

		newNode->symbol = symbol;

		newNode->next = node;

		return newNode;
}

hashNode* hashFinder(symbolType symbol, hashNode* node)
{
	hashNode* aux = node;

	while( !isEmpty(aux) )
	{
		if(equal(aux->symbol, symbol))
		{
			return aux;
		}
		else
		{
			aux = aux->next;
		}
	}

	return NULL;
}

int hashIndex(char* symbol, int tableSize)
{
	int index = 1;
	int i;

	for(i = 0; i < strlen(symbol); i++)
	{
		index = ( (index * symbol[i]) % tableSize ) + 1;
	}

	return index - 1;
}

hashTable_ref newHashTable(int size)
{
  hashTable_ref table = (hashTable_ref) calloc(size, sizeof(hashNode*));
	int i;

	for(i = 0; i < size; i++)
	{
		table[i] = nullTable();
	}

	return table;
}

void initMe(void)
{
	hashTable = newHashTable(TABLE_SIZE);
}

char* removeQuotes(char* s)
{
	int newLength = strlen(s) - 2;
	char* s2 = (char*) calloc(newLength + 1, sizeof(char));
	strncpy(s2, s + 1, newLength);

	return s2;
}

hashNode* hashInsert(char* text, int type)
{
	symbolType symbol;
	symbol.text = (char*) calloc(strlen(text) + 1, sizeof(char));
	strcpy(symbol.text, text);
	symbol.type = type;

	switch(type)
	{
		case SYMBOL_LIT_INTEGER:
		{
			symbol.value.intLit = atoi(text);
			break;
		}
		case SYMBOL_LIT_REAL:
			symbol.value.realLit = atof(text);
			break;
		case SYMBOL_LIT_CHAR:
			symbol.value.charLit = removeQuotes(text)[0];
			break;
		case SYMBOL_LIT_STRING:
			symbol.value.stringLit = removeQuotes(text);
			break;
		case SYMBOL_IDENTIFIER:
			symbol.value.identifier = (char*) calloc(strlen(text) + 1, sizeof(char));
			strcpy(symbol.value.identifier, text);
			break;
	}

	int index = hashIndex(symbol, TABLE_SIZE);

	hashNode* pointer = hashFinder(symbol, *(hashTable[index]));

	if(pointer != NULL)
	{
		return pointer;
	}
	else
	{
		hashTable[index] = newHashNode(symbol, type, hashTable[index]);

		return hashTable[index];
	}
}