%{
	//Cássio de Abreu Ramos, Felipe Barbosa Tormes

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "hash.h"
%}

%start program

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

%token TK_IDENTIFIER
%token LIT_INTEGER
%token LIT_REAL
%token LIT_CHAR
%token LIT_STRING

%token TOKEN_ERROR

%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '+' '-'
%left '*' '/'
%left OPERATOR_AND OPERATOR_OR

%%

program:
	init 	|

	;

init:
	global_id_declaration |
	function
	;

global_id_declaration:
	TK_IDENTIFIER ':' type global_declaration
	;

type:
	KW_BYTE		|
	KW_SHORT	|
	KW_LONG		|
	KW_FLOAT	|
	KW_DOUBLE	|
	;

global_declaration:
	literal		';'	program															|
	'[' LIT_INTEGER ']' initial_values_vector program
	;

initial_values_vector:
	literal initial_values_vector	|
	';'
	;

literal:
	LIT_INTEGER	|
	LIT_REAL		|
	LIT_CHAR
	;

function:
	function_scope command ';' program
	;

function_scope:
	type TK_IDENTIFIER '(' parameter_list 	|
	type TK_IDENTIFIER '(' ')'
	;

parameter_list:
	type TK_IDENTIFIER parameter_list_comma	|
	parameter parameter_list_comma			|
	;

parameter_list_comma:
	',' parameter_list	|
	')'
	;

parameter:
	TK_IDENTIFIER											|
	TK_IDENTIFIER '[' expression ']'	|
	literal
	;

block:
	'{' command_list '}'
	;

command_list:
	command ';' command_list	|

	;

command:
	attribution_variable	|
	flow_control					|
	read									|
	print									|
	return 	|
	block 	|

	;

attribution_variable:
	TK_IDENTIFIER attribution
	;

attribution:
	'=' expression										|
	'#' expression '=' expression
	;

flow_control:
	conditionals	|
	loops
	;

conditionals:
	KW_WHEN '(' expression ')' KW_THEN command conditionals		|
	KW_ELSE command																						|

	;

loops:
	KW_WHILE '(' expression ')' command								|
	KW_FOR '(' attribution_variable KW_TO LIT_INTEGER ')' command
	;

read:
	KW_READ TK_IDENTIFIER
	;

print:
	KW_PRINT to_print
	;

to_print:
	LIT_STRING to_print	|
	expression to_print	|

	;

return:
	KW_RETURN expression
	;

expression:
	TK_IDENTIFIER													|
	TK_IDENTIFIER '(' parameter_list	|
	literal																|
	expression op expression	|
	TK_IDENTIFIER '[' expression ']' 
	;

op:
	'+'						|
	'-'						|
	'*'						|
	'/'						|
	'<'						|
	'>'						|
	'!'						|
	OPERATOR_LE		|
	OPERATOR_GE		|
	OPERATOR_EQ		|
	OPERATOR_NE		|
	OPERATOR_AND	|
	OPERATOR_OR		|
	;

%%

yyerror(s)
char *s;
{
  fprintf(stderr, "%s in line %d\n",s,getLineNumber());

  exit(3);
}
