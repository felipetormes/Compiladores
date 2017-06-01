//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#ifndef HASH_H
#define HASH_H

#define TABLE_SIZE 997

#define SYMBOL_LIT_INTEGER 1
#define SYMBOL_LIT_REAL 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_STRING 4
#define SYMBOL_IDENTIFIER 5

#include "astree.h"

typedef enum natureENUM
{
	SCALAR,
	VECTOR,
	FUNCTION
}natureType;

union value_union
{
	int intLit;
	char charLit;
	float realLit;
	char* stringLit;
	char* identifier;
};

typedef struct symbolStruct
{
	union value_union value;
	char* text;
	int type;
	dataType data_type;
	natureType nature;
	dataType returnType;
	int marked;
	astree* declaration;
	struct symbolStruct* scope;
}symbolType;

typedef struct hashTable
{
  symbolType symbol;
  struct hashTable* next;
} hashNode;

typedef hashNode** hashTable_ref;

int equal(symbolType symbol1, symbolType symbol2);

hashNode* nullTable(void);

int isEmpty(hashNode* node);

hashNode* newHashNode(symbolType symbol, hashNode* node);

hashNode* hashFinder(symbolType symbol, hashNode* node);

int hashIndex(char* symbol, int tableSize);

hashTable_ref newHashTable(int size);

hashNode* addToTable(char* symbol, int type, hashTable_ref table, int tableSize);

void initMe(void);

char* removeQuotes(char* s);

hashNode* hashInsert(char* symbol, int type);

#endif
