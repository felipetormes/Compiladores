//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "astree.h"

astree* CreateAstree(nodeType node_type, hashNode* node, astree* child_0, astree* child_1, astree* child_2, astree* child_3)
{
	astree* ast = (astree*)calloc(1,sizeof(astree));
	ast->child = (astree**)calloc(4,sizeof(astree));

	ast->node_type = node_type;
	ast->node = node;

	ast->child[0] = child_0;
	ast->child[1] = child_1;
	ast->child[2] = child_2;
	ast->child[3] = child_3;

	int i;

	for(i = 0; i < 4; i++)
	{
		if(ast->child[i] != NULL)
			ast->numChildren++;
	}

	return ast;
}

astree* CreateAstree0(nodeType node_type, hashNode* node)
{
	return CreateAstree(node_type, node, NULL, NULL, NULL, NULL);
}
astree* CreateAstree1(nodeType node_type, hashNode* node, astree* child_0)
{
	return CreateAstree(node_type, node, child_0, NULL, NULL, NULL);
}
astree* CreateAstree2(nodeType node_type, hashNode* node, astree* child_0, astree* child_1)
{
	return CreateAstree(node_type, node, child_0, child_1, NULL, NULL);
}
astree* CreateAstree3(nodeType node_type, hashNode* node, astree* child_0, astree* child_1, astree* child_2)
{
	return CreateAstree(node_type, node, child_0, child_1, child_2, NULL);
}
astree* CreateAstree4(nodeType node_type, hashNode* node, astree* child_0, astree* child_1, astree* child_2, astree* child_3)
{
	return CreateAstree(node_type, node, child_0, child_1, child_2, child_3);
}

char* toOutput(astree* ast)
{
	if(ast == NULL)
	{
		return "";
	}
	else
	{
		switch(ast->node_type)
		{
			case IDENTIFIER:
			{
				char* s = (char*)calloc(strlen(ast->node->symbol.value.identifier) + 1,sizeof(char));
				strcpy(s,ast->node->symbol.value.identifier);
				return s;
				break;
			}
			case TYPEBYTE:
			{
				return "byte";
				break;
			}
			case TYPESHORT:
			{
				return "short";
				break;
			}
			case TYPELONG:
			{
				return "long";
				break;
			}
			case TYPEFLOAT:
			{
				return "float";
				break;
			}
			case TYPEDOUBLE:
			{
				return "double";
				break;
			}
			case LITERAL:
			{
				switch(ast->node->symbol.type)
				{
					case SYMBOL_LIT_INTEGER:
					{
						char* buffer = (char*)calloc(30,sizeof(char));
						sprintf(buffer,"%d",ast->node->symbol.value.intLit);
						return buffer;
						break;
					}
					case SYMBOL_LIT_REAL:
					{
						char* buffer = (char*)calloc(30,sizeof(char));
						sprintf(buffer,"%f",ast->node->symbol.value.realLit);
						return buffer;
						break;
					}
					case SYMBOL_LIT_CHAR:
					{
						char* buffer = (char*)calloc(3,sizeof(char));
						sprintf(buffer,"'%c'",ast->node->symbol.value.charLit);
						return buffer;
						break;
					}
					case SYMBOL_LIT_STRING:
					{
						char* s = (char*)calloc(1 + strlen(ast->node->symbol.value.identifier) + 1 + 1,sizeof(char));
						sprintf(s,"%c%s%c",(char)34,ast->node->symbol.value.stringLit,(char)34);
						return s;
						break;
					}
				}
				break;
			}
			case ADDITION:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s+%s",child0_source,child1_source);
				return buffer;
				break;
			}
			case SUBTRACTION:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s-%s",child0_source,child1_source);
				return buffer;
				break;
			}
			case MULTIPLICATION:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s*%s",child0_source,child1_source);
				return buffer;
				break;
			}
			case DIVISION:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s/%s",child0_source,child1_source);
				return buffer;
				break;
			}
			case LESSERTHAN:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s<%s",child0_source,child1_source);
				return buffer;
				break;
			}
			case GREATERTHAN:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s>%s",child0_source,child1_source);
				return buffer;
				break;
			}
			case LESSEREQUAL:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s<=%s",child0_source,child1_source);
				return buffer;
				break;
			}
			case GREATEREQUAL:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s>=%s",child0_source,child1_source);
				return buffer;
				break;
			}
			case EQUAL:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s==%s",child0_source,child1_source);
				return buffer;
				break;
			}
			case NOTEQUAL:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s!=%s",child0_source,child1_source);
				return buffer;
				break;
			}
			case AND:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s&&%s",child0_source,child1_source);
				return buffer;
				break;
			}
			case OR:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* buffer = (char*)calloc(1 + strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s||%s",child0_source,child1_source);
				return buffer;
				break;
			}
			case FUNCTIONCALL:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s(%s)",child0_source,child1_source);
				return buffer;
				break;
			}
			case ARRAYACCESS:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s#%s",child0_source,child1_source);
				return buffer;
				break;
			}
			case ARRAYEXPRESION:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s[%s]",child0_source,child1_source);
				return buffer;
				break;
			}
			case ARGUMENTLIST:
			{
				if(ast->child[0] == NULL)
				{
					return "";
				}
				else if(ast->child[1] == NULL)
				{
					char* child0_source = toOutput(ast->child[0]);
					char* buffer = (char*)calloc(strlen(child0_source) + 1,sizeof(char));

					sprintf(buffer,"%s",child0_source);

					return buffer;
				}
				else
				{
					char* child0_source = toOutput(ast->child[0]);
					char* child1_source = toOutput(ast->child[1]);
					char* buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1,sizeof(char));

					sprintf(buffer,"%s,%s",child0_source,child1_source);

					return buffer;
				}
				break;
			}
			case RETURN:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* buffer = (char*)calloc(strlen("return") + 1 + strlen(child0_source) + 1,sizeof(char));
				sprintf(buffer,"return %s;",child0_source);
				return buffer;
				break;
			}
			case PRINTLIST:
			{
				if(ast->child[0] == NULL)
				{
					return "";
				}
				else if(ast->child[1] == NULL)
				{
					char* child0_source = toOutput(ast->child[0]);
					char* buffer = (char*)calloc(strlen(child0_source) + 1,sizeof(char));

					sprintf(buffer,"%s",child0_source);

					return buffer;
				}
				else
				{
					char* child0_source = toOutput(ast->child[0]);
					char* child1_source = toOutput(ast->child[1]);
					char* buffer = (char*)calloc(strlen(child0_source) + strlen(child1_source) + 1,sizeof(char));

					sprintf(buffer,"%s %s",child0_source,child1_source);

					return buffer;
				}
				break;
			}
			case PRINT:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* buffer = (char*)calloc(strlen("print") + 1 + strlen(child0_source) + 1,sizeof(char));
				sprintf(buffer,"print %s",child0_source);
				return buffer;
				break;
			}
			case READ:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* buffer = (char*)calloc(strlen("read") + 1 + strlen(child0_source) + 1,sizeof(char));
				sprintf(buffer,"read %s",child0_source);
				return buffer;
				break;
			}
			case WHENTHEN:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* buffer = (char*)calloc(strlen("when") + 1 + strlen(child0_source) + 1 + 1 + strlen("then") + 1 + strlen(child1_source) + 1,sizeof(char));
				sprintf(buffer,"when(%s) then\n%s",child0_source,child1_source);
				return buffer;
				break;
			}
			case WHENTHENELSE:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* child2_source = toOutput(ast->child[2]);
				char* buffer = (char*)calloc(strlen("when") + 1 + strlen(child0_source) + 1 + 1 + strlen("then") + 1 + strlen(child1_source) + 1 + strlen("else") + 1 + strlen(child2_source) + 1,sizeof(char));
				sprintf(buffer,"when(%s) then\n%s\nelse\n%s",child0_source,child1_source,child2_source);
				return buffer;
				break;
			}
			case WHILE:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* buffer = (char*)calloc(strlen("while") + 1 + strlen(child0_source) + 1 + 1 + strlen(child1_source) + 1,sizeof(char));
				sprintf(buffer,"while (%s)\n%s",child0_source,child1_source);
				return buffer;
				break;
			}
			case FOR:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* child2_source = toOutput(ast->child[2]);
				char* buffer = (char*)calloc(strlen("for") + 1 + strlen(child0_source) + strlen("to") + strlen(child1_source) + 1 + 1 + strlen(child2_source) + 1,sizeof(char));
				sprintf(buffer,"for (%s to %s)\n%s",child0_source,child1_source,child2_source);
				return buffer;
				break;
			}
			case ASSIGNMENT:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1,sizeof(char));
				sprintf(buffer,"%s=%s",child0_source,child1_source);
				return buffer;
				break;
			}
			case COMMANDLIST:
			{
				if(ast->child[0] == NULL)
				{
					return "";
				}
				else
				{
					char* child0_source = toOutput(ast->child[0]);
					char* child1_source = toOutput(ast->child[1]);
					char* buffer = (char*)calloc(strlen(child0_source) + strlen(child1_source) + 1 + 1 + 1,sizeof(char));

					if(strcmp(child0_source,"") == 0)
						sprintf(buffer,"%s;",child1_source);
					else
						sprintf(buffer,"%s;\n%s",child1_source,child0_source);

					return buffer;
				}
				break;
			}
			case BLOCK:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* buffer = (char*)calloc(1 + 1 + strlen(child0_source) + 1 + 1 + 1,sizeof(char));
				sprintf(buffer,"{\n%s\n}",child0_source);
				return buffer;
				break;
			}
			case PARAMETERLIST:
			{
				if(ast->child[0] == NULL)
				{
					return "";
				}
				else if(ast->child[2] == NULL)
				{
					char* child0_source = toOutput(ast->child[0]);
					char* child1_source = toOutput(ast->child[1]);
					char* buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1,sizeof(char));

					sprintf(buffer,"%s %s",child0_source,child1_source);

					return buffer;
				}
				else
				{
					char* child0_source = toOutput(ast->child[0]);
					char* child1_source = toOutput(ast->child[1]);
					char* child2_source = toOutput(ast->child[2]);
					char* buffer = (char*)calloc(strlen(child0_source) + 1 + 1 + strlen(child1_source) + 1 + strlen(child2_source) + 1,sizeof(char));

					sprintf(buffer,"%s, %s %s",child0_source,child1_source,child2_source);

					return buffer;
				}
				break;
			}
			case FUNCTIONSCOPE:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* child2_source = toOutput(ast->child[2]);
				char* buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1 + strlen(child2_source) + 1 + 1,sizeof(char));
				sprintf(buffer,"%s %s(%s)",child0_source,child1_source,child2_source);
				return buffer;
				break;
			}
			case DECLARATION:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* child2_source = toOutput(ast->child[2]);
				char* buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1 + strlen(child2_source) + 1,sizeof(char));
				sprintf(buffer,"%s: %s %s;\n",child0_source,child1_source,child2_source);
				return buffer;
				break;
			}
			case LITERALLIST:
			{
				if(ast->child[0] == NULL)
				{
					return "";
				}
				else
				{
					char* child0_source = toOutput(ast->child[0]);
					char* child1_source = toOutput(ast->child[1]);
					char* buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1,sizeof(char));

					if(strcmp(child0_source,"") == 0)
						sprintf(buffer,"%s",child1_source);
					else
						sprintf(buffer,"%s %s",child0_source,child1_source);

					return buffer;
				}

				break;
			}
			case ARRAYDECLARATION:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* child2_source = toOutput(ast->child[2]);
				char* child3_source;
				char* buffer;

				if(ast->child[3] != NULL)
				{
					child3_source = toOutput(ast->child[3]);

					buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1 + strlen(child2_source) + 1 + 1 + strlen(child3_source) + 1,sizeof(char));
					sprintf(buffer,"%s: %s[%s] %s;\n",child0_source,child1_source,child2_source,child3_source);
				}
				else
				{
					buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1 + strlen(child2_source) + 1 + 1,sizeof(char));
					sprintf(buffer,"%s: %s[%s];\n",child0_source,child1_source,child2_source);
				}

				return buffer;
				break;
			}
			case DECLARATIONLIST:
			{
				if(ast->child[0] == NULL)
				{
					return "";
				}
				else
				{
					char* child0_source = toOutput(ast->child[0]);
					char* child1_source = toOutput(ast->child[1]);
					char* buffer = (char*)calloc(strlen(child0_source) + strlen(child1_source) + 1 + 1 + 1,sizeof(char));

					if(strcmp(child0_source,"") == 0)
						sprintf(buffer,"%s;",child1_source);
					else
						sprintf(buffer,"%s\n%s;",child0_source,child1_source);

					return buffer;
				}
			}
			case FUNCTIONDEFINITION:
			{
				char* child0_source = toOutput(ast->child[0]);
				char* child1_source = toOutput(ast->child[1]);
				char* child2_source = toOutput(ast->child[2]);
				char* buffer = (char*)calloc(strlen(child0_source) + 1 + strlen(child1_source) + 1 + strlen(child2_source) + 1,sizeof(char));

				if(strcmp(child1_source,"") != 0)
					sprintf(buffer,"%s\n%s\n%s",child0_source,child1_source,child2_source);
				else
					sprintf(buffer,"%s;\n%s",child0_source,child2_source);

				return buffer;
				break;
			}
			case PROGRAM:
			{
				if(ast->child[1] == NULL)
				{
					return "";
				}
				else
				{
					char* child0_source = toOutput(ast->child[0]);
					char* child1_source = toOutput(ast->child[1]);
					char* buffer = (char*)calloc(strlen(child0_source) + 1 + 1 + strlen(child1_source) + 1,sizeof(char));

					if(ast->child[1]->node_type == DECLARATION || ast->child[1]->node_type == ARRAYDECLARATION)
						sprintf(buffer,"%s%s\n",child1_source,child0_source);
					else
						sprintf(buffer,"%s%s\n",child1_source,child0_source);

					return buffer;
				}

				break;
			}
		}
	}
}
