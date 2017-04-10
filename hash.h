#define TABLE_SIZE 997

typedef struct symbolsTable
{
  char* symbol;
  int type;
  struct symbolsTable* next;
} Symbol;

typedef Symbol** hashTable_ref;

void printSymbol(char* symbol);

void printType(int type);

Symbol* nullTable(void);

int isEmpty(Symbol list);

Symbol* cons(char* symbol, int type, Symbol* list);

Symbol* find(char* symbol, Symbol list);

void printList(Symbol list);

int hashFunction(char* symbol, int tableSize);

hashTable_ref newHashTable(int size);

Symbol* addToTable(char* symbol, int type, hashTable_ref table, int tableSize);

void printTable(hashTable_ref table, int tableSize);

void initMe(void);

Symbol* addSymbol(char* symbol, int type);

void printSymbolTable(void);
