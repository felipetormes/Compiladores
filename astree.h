//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#ifndef ASTREE_H
#define ASTREE_H

#include <stdlib.h>
#include <stdio.h>

typedef enum nodeTypeEnum
{
	IDENTIFIER,
	TYPEBYTE,
	TYPESHORT,
	TYPELONG,
	TYPEFLOAT,
	TYPEDOUBLE,
	LITERAL,
	ADDITION,
	SUBTRACTION,
	MULTIPLICATION,
	DIVISION,
	LESSERTHAN,
	GREATERTHAN,
	LESSEREQUAL,
	GREATEREQUAL,
	EQUAL,
	NOTEQUAL,
	AND,
	OR,
	FUNCTIONCALL,
	ARRAYACCESS,
	ARRAYEXPRESION,
	ARGUMENTLIST,
	RETURN,
	PRINTLIST,
	PRINT,
	READ,
	WHENTHEN,
	WHENTHENELSE,
	WHILE,
	FOR,
	ASSIGNMENT,
	COMMANDLIST,
	BLOCK,
	PARAMETERLIST,
	FUNCTIONSCOPE,
	DECLARATION,
	POINTERDECLARATION,
	LITERALLIST,
	ARRAYDECLARATION,
	DECLARATIONLIST,
	FUNCTIONDEFINITION,
	PROGRAM
}nodeType;

typedef enum dataTypeEnum
{
	INTEGER,
	BYTE,
	SHORT,
	LONG,
	FLOAT,
	NO_TYPE
}dataType;

typedef struct astreeStruct
{
	int lineNumber;
	nodeType node_type;
	struct hashTable* node;
	dataType data_type;
	int numChildren;
	struct astreeStruct** child;
}astree;

#include "hash.h"

astree* CreateAstree(nodeType node_type, struct hashTable* node, astree* child_0, astree* child_1, astree* child_2, astree* child_3);
astree* CreateAstree0(nodeType node_type, struct hashTable* node);
astree* CreateAstree1(nodeType node_type, struct hashTable* node, astree* child_0);
astree* CreateAstree2(nodeType node_type, struct hashTable* node, astree* child_0, astree* child_1);
astree* CreateAstree3(nodeType node_type, struct hashTable* node, astree* child_0, astree* child_1, astree* child_2);
astree* CreateAstree4(nodeType node_type, struct hashTable* node, astree* child_0, astree* child_1, astree* child_2, astree* child_3);
char* toOutput(astree* ast);
void PrintTree(astree* ast);

#endif
