#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

hashTable_ref symbolTable;

void printSymbol(char* symbol)
{
	printf("%s", symbol);
}

void printType(int type)
{
	printf("%d", type);
}

Symbol* nullTable(void)
{
	Symbol* list = (Symbol*) malloc( sizeof(Symbol) );

	list->symbol = NULL;
	list->next = NULL;

	return list;
}

int isEmpty(Symbol list)
{
	return list.symbol == NULL;
}

Symbol* cons(char* symbol, int type, Symbol* list)
{
	if(list == NULL)
	{
		return NULL;
	}
	else
	{
		Symbol* newList = (Symbol*) malloc( sizeof(Symbol) );

		newList->symbol = (char*) malloc( strlen(symbol) );
		strcpy(newList->symbol, symbol);
		newList->type = type;

		newList->next = list;

		return newList;
	}
}

Symbol* find(char* symbol, Symbol list)
{
	Symbol* aux = &list;

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

void printList(Symbol list)
{
	Symbol* aux = &list;

	while( !isEmpty(*aux) )
	{
		printf("(");
		printSymbol(aux->symbol);
		printf(" : ");
		printType(aux->type);
		printf(")");

		printf(" :: ");

		aux = aux->next;
	}

	printf("[]");
}

int hashFunction(char* symbol, int tableSize)
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
  hashTable_ref table = (hashTable_ref) calloc(size, sizeof(Symbol*));
	int i;

	for(i = 0; i < size; i++)
	{
		table[i] = nullTable();
	}

	return table;
}

Symbol* addToTable(char* symbol, int type, hashTable_ref table, int tableSize)
{
	int index = hashFunction(symbol, tableSize);

	Symbol* pointer = find(symbol, *(table[index]));

	if(pointer != NULL)
	{
		return pointer;
	}
	else
	{
		table[index] = cons(symbol, type, table[index]);

		return table[index];
	}
}

void printTable(hashTable_ref table, int tableSize)
{
	int i;

	printf("{\n");

	for(i = 0; i < tableSize; i++)
	{
		printf("\t");
		printList( *(table[i]) );
		printf("\n");
	}

	printf("}");
}

void initMe(void)
{
	symbolTable = newHashTable(TABLE_SIZE);
}

Symbol* addSymbol(char* symbol, int type)
{
	return addToTable(symbol, type, symbolTable, TABLE_SIZE);
}

void printSymbolTable(void)
{
	printTable(symbolTable, TABLE_SIZE);
}
