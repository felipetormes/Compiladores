#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

  initMe();

  FILE* file = fopen(argv[1], "r");

  yyin = file;

  while(isRunning())
  {
    token = yylex();

    if(!isRunning())
      break;

    printf("Token number %d at line %d\n", token, getLineNumber());
  }

  printf("Number of Lines: %d\n", getLineNumber());

  //printHashTable();

  return 1;
}
