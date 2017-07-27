//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "astree.h"
#include "y.tab.h"
#include "semantic.h"
#include "tac.h"
#include "assembly.h"

extern astree* root;

int main(int argc, char** argv){

if(argc < 2) // insuficient arguments
    exit(0);

  if(!open_input(argv[1])) // couldn't open input file
    exit(1);

  initMe();

  yyparse();

	first_pass(root);

  verify(root);

  TAC* tacs = tacReverse(tacGenerate(root));

  TAC* opt = tacReverse(test(tacs));

  printCode(opt);

  generateAssembly(opt, argv[2]);

  close_input();

  fprintf(stderr,"The input code is syntactically correct!\n");

	exit(0);
}
