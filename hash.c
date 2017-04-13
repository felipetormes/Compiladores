//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

hashTable_ref hashTable;

void printHashSymbol(char* symbol)
{
	printf("%s", symbol);
}

void printHashSymbolType(int type)
{
	printf("%d", type);
}

hashNode* nullTable(void)
{
	hashNode* node = (hashNode*) malloc( sizeof(hashNode) );

	node->symbol = NULL;
	node->next = NULL;

	return node;
}

int isEmpty(hashNode node)
{
	return node.symbol == NULL;
}

hashNode* newHashNode(char* symbol, int type, hashNode* node)
{
	if(node == NULL)
	{
		return NULL;
	}
	else
	{
		hashNode* newNode = (hashNode*) malloc( sizeof(hashNode) );

		newNode->symbol = (char*) malloc( strlen(symbol) );
		strcpy(newNode->symbol, symbol);
		newNode->type = type;

		newNode->next = node;

		return newNode;
	}
}

hashNode* hashFinder(char* symbol, hashNode node)
{
	hashNode* aux = &node;

	while( !isEmpty(*aux) )
	{
		if(strcmp(aux->symbol, symbol) == 0)
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

void printHashList(hashNode node, int hashTableIndex)
{
	hashNode* aux = &node;

	printf("HashTable[%d]", hashTableIndex);

	while( !isEmpty(*aux) )
	{
		printf(" --> (");
		printHashSymbol(aux->symbol);
		printf(", ");
		printHashSymbolType(aux->type);
		printf(")");

		aux = aux->next;
	}
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

hashNode* hashInsert(char* symbol, int type)
{
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

void printHashTable(void)
{
	int i;

	printf("{\n");

	for(i = 0; i < TABLE_SIZE; i++)
	{
		printf("\t");
		printHashList( *(hashTable[i]), i );
		printf("\n");
	}

	printf("}");
}