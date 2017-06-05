//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "astree.h"
#include "y.tab.h"
#include "semantic.h"

extern astree* root;

int main(int argc, char** argv){

if(argc < 2) // insuficient arguments
    exit(0);

  if(!open_input(argv[1])) // couldn't open input file
    exit(1);

  initMe();

  yyparse();

	first_pass(root);

  close_input();

	exit(0);
}
