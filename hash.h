#define TABLE_SIZE 997

typedef struct hashTable
{
  char* symbol;
  int type;
  struct hashTable* next;
} hashNode;

typedef hashNode** hashTable_ref;

void printHashSymbol(char* symbol);

void printHashType(int type);

hashNode* nullTable(void);

int isEmpty(hashNode node);

hashNode* newHashNode(char* symbol, int type, hashNode* node);

hashNode* hashFinder(char* symbol, hashNode node);

void printHashList(hashNode node, int hashTableIndex);

int hashIndex(char* symbol, int tableSize);

hashTable_ref newHashTable(int size);

hashNode* addToTable(char* symbol, int type, hashTable_ref table, int tableSize);

void initMe(void);

hashNode* hashInsert(char* symbol, int type);

void printHashTable(void);