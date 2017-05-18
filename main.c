//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "astree.h"
#include "y.tab.h"

extern astree* root;

int WriteToFile(char* path, char* content)
{
	FILE* file;

	file = fopen(path,"w");

	if(file == NULL)
	{
		fprintf(stderr,"ERROR: Couldn't open %s\n",path);
		exit(1);
	}

	fprintf(file,"%s",content);

	return 1;
}

int main(int argc, char** argv){

if(argc < 2) // insuficient arguments
    exit(0);

  if(!open_input(argv[1])) // couldn't open input file
    exit(1);

  initMe();

  yyparse();

  close_input();

  char* decompiledAST = toOutput(root);

  WriteToFile(argv[2],decompiledAST);

  fprintf(stderr,"The input code is syntactically correct!\n");

	exit(0);
}
