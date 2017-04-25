//Cássio de Abreu Ramos, Felipe Barbosa Tormes

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

  initMe();

  yyparse();

  if(argc < 2)
  {
    printf("\nPlease, write the file name after the executable's name!\n\n");
    exit(0);
  }

  FILE* file = fopen(argv[1], "r");

  if(!file)
  {
    printf("\nThe file %s cant't be opened or you typed the wrong name!\n\n", argv[1]);
    exit(1);
  }

  fprintf(stderr,"The input code is syntactically correct!\n");

	exit(0);
}
