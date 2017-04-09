%{

  #include <stdio.h>
  #include "tokens.h"

  int running = 1;
  int token;
  int line_number = 1;

%}

%x COMMENT


%%

"/*"                            { BEGIN(COMMENT); }

"//"[^"\n"]*                    {  }
" "|" "                         {  }
"\n"                            { line_number++; }

"byte"                          { return KW_BYTE; }
"short"                         { return KW_SHORT; }
"long"                          { return KW_LONG; }
"float"                         { return KW_FLOAT; }
"double"                        { return KW_DOUBLE; }
"when"                          { return KW_WHEN; }
"then"                          { return KW_THEN; }
"else"                          { return KW_ELSE; }
"while"                         { return KW_WHILE; }
"for"                           { return KW_FOR; }
"read"                          { return KW_READ; }
"return"                        { return KW_RETURN; }
"print"                         { return KW_PRINT; }

"<="                            { return OPERATOR_LE; }
">="                            { return OPERATOR_GE; }
"=="                            { return OPERATOR_EQ; }
"!="                            { return OPERATOR_NE; }
"&&"                            { return OPERATOR_AND; }
"||"                            { return OPERATOR_OR; }

[,;:()\[\]{}+\-*/<>=!&$#]			    { return (int)yytext[0]; }

[_a-zA-Z][a-zA-Z0-9_]*            { return TK_IDENTIFIER; }

[0-9][0-9]*                       { return LIT_INTEGER; }

[0-9]\.[0-9]+                     { return LIT_REAL; }

\'[^']\'                          { return LIT_CHAR; }

\"[^"]*\"                         { return LIT_STRING; }

.                               { return TOKEN_ERROR; }

<COMMENT>
"*/"                            { BEGIN(INITIAL); }
<COMMENT>
"\n"                            { line_number++; }
<COMMENT>
.                               {  }

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
  printf("Number of lines: %d\n", line_number);
}
