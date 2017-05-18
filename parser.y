%{
	//Cássio de Abreu Ramos, Felipe Barbosa Tormes

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "hash.h"
	#include "astree.h"

	astree* root;
%}

%start begin

%union{ hashNode* symbol; astree* ast; }

%token KW_BYTE
%token KW_SHORT
%token KW_LONG
%token KW_FLOAT
%token KW_DOUBLE
%token KW_WHEN
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_FOR
%token KW_READ
%token KW_RETURN
%token KW_PRINT
%token KW_TO

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_NE
%token OPERATOR_AND
%token OPERATOR_OR

%token <symbol> TK_IDENTIFIER
%token <symbol> LIT_INTEGER
%token <symbol> LIT_REAL
%token <symbol> LIT_CHAR
%token <symbol> LIT_STRING

%token TOKEN_ERROR

%type <ast> program
%type <ast> identifier
%type <ast> item
%type <ast> global_id_declaration
%type <ast> type
%type <ast> global_declaration
%type <ast> initial_values_vector
%type <ast> literal
%type <ast> literal_list
%type <ast> function
%type <ast> function_scope
%type <ast> parameter_list
%type <ast> parameter_list_comma
%type <ast> argument_list
%type <ast> argument_list_comma
%type <ast> block
%type <ast> command_list
%type <ast> command
%type <ast> attribution_variable
%type <ast> attribution
%type <ast> flow_control
%type <ast> conditionals
%type <ast> loops
%type <ast> read
%type <ast> print
%type <ast> print_list
%type <ast> to_print
%type <ast> return
%type <ast> expression

%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left OPERATOR_AND OPERATOR_OR
%left '+' '-'
%left '*' '/'


%%

begin:
		program { root = $1; }
		;

program:
		item program	{ $$ = CreateAstree2(PROGRAM, NULL, $2, $1); }
	|	{ $$ = CreateAstree0(PROGRAM, NULL); }
	;

identifier:
		TK_IDENTIFIER	{ $$ = CreateAstree0(IDENTIFIER, $1); }
		;

item:
		global_id_declaration
	|	function
	;

global_id_declaration:
		identifier ':' type global_declaration 	{ $$ = CreateAstree3(DECLARATION, NULL, $1, $3, $4); }
	|	identifier ':' type '[' LIT_INTEGER ']' initial_values_vector	{ $$ = CreateAstree4(ARRAYDECLARATION, NULL, $1, $3, CreateAstree0(LITERAL, $5), $7); }
	;

type:
		KW_BYTE	{ $$ = CreateAstree0(TYPEBYTE, NULL); }
	|	KW_SHORT	{ $$ = CreateAstree0(TYPESHORT, NULL); }
	|	KW_LONG	{ $$ = CreateAstree0(TYPELONG, NULL); }
	|	KW_FLOAT	{ $$ = CreateAstree0(TYPEFLOAT, NULL); }
	|	KW_DOUBLE	{ $$ = CreateAstree0(TYPEDOUBLE, NULL); }
	;

global_declaration:
		literal		';'	{ $$ = $1; }
	;

initial_values_vector:
		literal_list initial_values_vector	{ $$ = CreateAstree1(LITERALLIST, NULL, $1); }
	|	';'		{ $$ = NULL; }
	;

literal:
		LIT_INTEGER	{ $$ = CreateAstree0(LITERAL, $1); }
	|	LIT_REAL	{ $$ = CreateAstree0(LITERAL, $1); }
	|	LIT_CHAR	{ $$ = CreateAstree0(LITERAL, $1); }
	;

literal_list:
		literal_list literal { $$ = CreateAstree2(LITERALLIST, NULL, $1, $2); }
	|	{ $$ = CreateAstree0(LITERALLIST, NULL); }
		;

function:
		function_scope command ';'	{ $$ = CreateAstree2(FUNCTIONDEFINITION, NULL, $1, $2); }
	;

function_scope:
		type identifier '(' parameter_list ')' { $$ = CreateAstree3(FUNCTIONSCOPE, NULL, $1, $2, $4); }
	;

parameter_list:
		type identifier parameter_list_comma	{ $$ = CreateAstree3(PARAMETERLIST, NULL, $3, $1, $2); }
	|	{ $$ = CreateAstree0(PARAMETERLIST, NULL); }
	;

parameter_list_comma:
		',' type identifier parameter_list_comma	{ $$ = CreateAstree2(PARAMETERLIST, NULL, $2, $3); }
	|
	;

argument_list:
		expression argument_list_comma	{ $$ = CreateAstree2(ARGUMENTLIST, NULL, $1,$2); }
	;

argument_list_comma:
		',' expression argument_list_comma	{ $$ = CreateAstree1(ARGUMENTLIST, NULL, $2); }
	|
	;

block:
		'{' command_list '}'	{ $$ = CreateAstree1(BLOCK, NULL, $2); }
	;

command_list:
		command ';' command_list	{ $$ = CreateAstree2(COMMANDLIST, NULL, $3, $1); }
	|	{ $$ = CreateAstree0(COMMANDLIST, NULL); }
	;

command:
		attribution
	|	flow_control
	|	read
	|	print
	|	return
	|	block
	|	{ $$ = NULL; }
	;

attribution_variable:
		identifier
	|	identifier '#' expression	{ $$ = CreateAstree2(ARRAYACCESS, NULL, $1, $3); }
	;

attribution:
		attribution_variable '=' expression	{ $$ = CreateAstree2(ASSIGNMENT, NULL, $1, $3); }
	;

flow_control:
		conditionals
	|	loops
	;

conditionals:
		KW_WHEN '(' expression ')' KW_THEN command	{ $$ = CreateAstree2(WHENTHEN, NULL, $3, $6); }
	|	KW_WHEN '(' expression ')' KW_THEN command KW_ELSE command { $$ = CreateAstree3(WHENTHENELSE, NULL, $3, $6, $8); }
	;

loops:
		KW_WHILE '(' expression ')' command 	{ $$ = CreateAstree2(WHILE, NULL, $3, $5); }
	|	KW_FOR '(' attribution KW_TO LIT_INTEGER ')' command 	{ $$ = CreateAstree3(FOR, NULL, $3, CreateAstree0(LITERAL, $5), $7); }
	;

read:
		KW_READ identifier 	{ $$ = CreateAstree1(READ, NULL, $2); }
	;

print:
		KW_PRINT print_list	{ $$ = CreateAstree1(PRINT, NULL, $2); }
	;

print_list:
		print_list to_print	{ $$ = CreateAstree2(PRINTLIST, NULL, $1, $2); }
	|	to_print	{ $$ = CreateAstree1(PRINTLIST, NULL, $1); }
		;

to_print:
		LIT_STRING 	{ $$ = CreateAstree0(LITERAL, $1); }
	|	expression 	{ $$ = $1; }
	|
	;

return:
		KW_RETURN expression	{ $$ = CreateAstree1(RETURN, NULL, $2); }
	;

expression:
		identifier
	|	identifier '(' argument_list ')'	{ $$ = CreateAstree2(FUNCTIONCALL, NULL, $1, $3); }
	|	literal
	|	identifier '[' expression ']'	{ $$ = CreateAstree2(ARRAYEXPRESION, NULL, $1, $3); }
	|	'(' expression ')'	{ $$ = $2; }
	|	expression '+' expression	{ $$ = CreateAstree2(ADDITION, NULL, $1, $3); }
	|	expression '-' expression	{ $$ = CreateAstree2(SUBTRACTION, NULL, $1, $3); }
	|	expression '*' expression	{ $$ = CreateAstree2(MULTIPLICATION, NULL, $1, $3); }
	|	expression '/' expression	{ $$ = CreateAstree2(DIVISION, NULL, $1, $3); }
	|	expression '<' expression	{ $$ = CreateAstree2(LESSERTHAN, NULL, $1, $3); }
	|	expression '>' expression	{ $$ = CreateAstree2(GREATERTHAN, NULL, $1, $3); }
	|	expression OPERATOR_LE expression	{ $$ = CreateAstree2(LESSEREQUAL, NULL, $1, $3); }
	|	expression OPERATOR_GE expression	{ $$ = CreateAstree2(GREATEREQUAL, NULL, $1, $3); }
	|	expression OPERATOR_EQ expression	{ $$ = CreateAstree2(EQUAL, NULL, $1, $3); }
	|	expression OPERATOR_NE expression	{ $$ = CreateAstree2(NOTEQUAL, NULL, $1, $3); }
	|	expression OPERATOR_AND expression	{ $$ = CreateAstree2(AND, NULL, $1, $3); }
	|	expression OPERATOR_OR expression	{ $$ = CreateAstree2(OR, NULL, $1, $3); }
	;

%%

yyerror(s)
char *s;
{
  fprintf(stderr, "%s in line %d\n",s,getLineNumber());

  exit(3);
}
