%{

  //Cássio de Abreu Ramos, Felipe Barbosa Tormes

  #include <stdio.h>
  #include "hash.h"
  #include "astree.h"
  #include "y.tab.h"
  #ifndef YYSTYPE
  #define YYSTYPE int
  #endif
  
  int running = 1;
  int token;
  int line_number = 1;

%}

%x COMMENT


%%

"/*"                            { BEGIN(COMMENT); }

"//"[^"\n"]*                    {  }
" "|"\t"                        {  }
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
"to"                         	  { return KW_TO; }

"<="                            { return OPERATOR_LE; }
">="                            { return OPERATOR_GE; }
"=="                            { return OPERATOR_EQ; }
"!="                            { return OPERATOR_NE; }
"&&"                            { return OPERATOR_AND; }
"||"                            { return OPERATOR_OR; }

[,;:()\[\]{}+\-*/<>=!&$#]			  { return (int)yytext[0]; }

[_a-zA-Z][a-zA-Z0-9_]*          { yylval.symbol = hashInsert(yytext, SYMBOL_IDENTIFIER); return TK_IDENTIFIER; }

[0-9][0-9]*                     { yylval.symbol = hashInsert(yytext, SYMBOL_LIT_INTEGER); return LIT_INTEGER; }

[0-9]+\.[0-9]+                   { yylval.symbol = hashInsert(yytext, SYMBOL_LIT_REAL); return LIT_REAL; }

\'[^']\'                        { yylval.symbol = hashInsert(yytext, SYMBOL_LIT_CHAR); return LIT_CHAR; }

\"[^"]*\"                       { yylval.symbol = hashInsert(yytext, SYMBOL_LIT_STRING); return LIT_STRING; }

.                               { return TOKEN_ERROR; }

<COMMENT>
"*/"                            { BEGIN(INITIAL); }
<COMMENT>
"\n"                            { line_number++; }
<COMMENT>
.                               {  }

%%

int isRunning(void)
{
  return running;
}

int open_input(char* file_path)
{
  FILE* file = fopen(file_path,"r");
  int could_open = (file != NULL);

  if(!could_open)
  {
    return 0;
  }
  else
  {
    yyin = file;

    return 1;
  }
}

int close_input()
{
  fclose(yyin);

  return 1;
}

int yywrap()
{
  running = 0;
  return 1;
}

int getLineNumber()
{
	return line_number;
}
