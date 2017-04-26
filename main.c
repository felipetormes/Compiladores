//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

if(argc < 2) // insuficient arguments
    exit(0);

  if(!open_input(argv[1])) // couldn't open input file
    exit(1);

  initMe();

  yyparse();

  close_input();

  fprintf(stderr,"The input code is syntactically correct!\n");

	exit(0);
}
