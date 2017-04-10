#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

  initMe();

  FILE* file = fopen(argv[1], "r");

  yyin = file;

  printf("%d\n", isRunning());

  while(isRunning())
  {
    token = yylex();

    if(!isRunning())
      break;

    printf("Token number: %d \n", token);
  }

  printf("Number of Lines: %d\n", getLineNumber());

  return 1;
}
