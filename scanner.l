%{

  #include <stdio.h>
  #include "tokens.h"

  int running = 1;
  int token;

%}


%%

"int"         { return KW_INT; }
"float"       { return KW_FLOAT; }
"bool"        { return KW_BOOL; }
"char"        { return KW_CHAR; }
"if"          { return KW_IF; }
"then"        { return KW_THEN; }
"else"        { return KW_ELSE; }
"for"         { return KW_FOR; }
"read"        { return KW_READ; }
"print"       { return KW_PRINT; }
"return"      { return KW_RETURN; }

"<="          { return OPERATOR_LE; }
">="          { return OPERATOR_GE; }
"=="          { return OPERATOR_EQ; }
"!="          { return OPERATOR_NE; }
"&&"          { return OPERATOR_AND; }
"||"          { return OPERATOR_OR; }

"TRUE"        { return LIT_TRUE; }
"FALSE"       { return LIT_FALSE; }

.             { return TOKEN_ERROR; }

%%

int yywrap()
{
  running = 0;
  return 1;
}

int main(int argc, char** argv){

  FILE* file = fopen(argv[1], "r");

  yyin = file;

  while(running)
  {
    token = yylex();

    if(!running)
      break;

    printf("Token number: %d \n", token);
  }
}
