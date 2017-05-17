//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

typedef enum nodeTypeEnum
{
	IDENTIFIER,
	TYPEBYTE,
	TYPESHORT,
	TYPELONG,
	TYPEFLOAT,
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
	ARGUMENTLIST,
	RETURN,
	ELEMENTLIST,
	OUTPUT,
	INPUT,
	WHENTHEN,
	WHENTHENELSE,
	WHILE,
	FOR,
	ASSIGNMENT,
	COMMANDLIST,
	BLOCK,
	PARAMETERLIST,
	FUNCTIONHEADER,
	DECLARATION,
	POINTERDECLARATION,
	LITERALLIST,
	ARRAYDECLARATION,
	DECLARATIONLIST,
	FUNCTIONDEFINITION,
	PROGRAM
}nodeType;

typedef struct astreeStruct
{
	nodeType node_type;
	hashNode* node;

	int numChildren;
	struct astreeStruct** child;
}astree;

astree* CreateAstree(nodeType node_type, hashNode* node, astree* child_0, astree* child_1, astree* child_2, astree* child_3);
astree* CreateAstree0(nodeType node_type, hashNode* node);
astree* CreateAstree1(nodeType node_type, hashNode* node, astree* child_0);
astree* CreateAstree2(nodeType node_type, hashNode* node, astree* child_0, astree* child_1);
astree* CreateAstree3(nodeType node_type, hashNode* node, astree* child_0, astree* child_1, astree* child_2);
astree* CreateAstree4(nodeType node_type, hashNode* node, astree* child_0, astree* child_1, astree* child_2, astree* child_3);
char* toOutput(astree* ast);
void PrintTree(astree* ast);