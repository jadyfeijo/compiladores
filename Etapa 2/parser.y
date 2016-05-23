%{
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

%}

%token KW_INT        256
%token KW_REAL       257
%token KW_BOOL       258
%token KW_CHAR       259
%token KW_IF         261
%token KW_ELSE       263
%token KW_WHILE      264
%token KW_INPUT      266
%token KW_RETURN     267
%token KW_OUTPUT     268

%token OPERATOR_LE   270
%token OPERATOR_GE   271
%token OPERATOR_EQ   272
%token OPERATOR_NE   273
%token OPERATOR_AND  274
%token OPERATOR_OR   275

%token TK_IDENTIFIER 280
%token LIT_INTEGER   281
%token LIT_FALSE     283
%token LIT_TRUE	  	 284
%token LIT_CHAR      285
%token LIT_STRING    286

%token TOKEN_ERROR   290

%right '='
%left  '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE OPERATOR_AND OPERATOR_OR
%left '+' '-'
%left '*' '/'

%%

program: 
	decl ';' program
	|
	;
	
decl:
	type TK_IDENTIFIER '(' decl_prmt ')' command ;
	| type TK_IDENTIFIER '(' ')' command ;
	| type TK_IDENTIFIER ':' lit ;
	| type TK_IDENTIFIER '[' LIT_INTEGER ']' arr_init ;
	;
	
decl_prmt:
	type TK_IDENTIFIER decl_prmt2
	;
	
decl_prmt2:	
	',' decl_prmt
	| ;	
	;
	
block:	
	'{' command list_cmd '}'
	;
	
list_cmd:
	command list_cmd
	| ; 
	;
	
command:
	TK_IDENTIFIER '=' exp
	| exp '=' TK_IDENTIFIER
	| TK_IDENTIFIER '[' exp ']' '=' exp
	| KW_INPUT TK_IDENTIFIER
	| KW_RETURN exp
	| KW_OUTPUT out
	| flow_ctrl
	| block 
	| ';'	
	;
	
exp:
    TK_IDENTIFIER
    | TK_IDENTIFIER '['exp']'
    | TK_IDENTIFIER '(' func_param ')'
    | '(' exp ')'
    | lit
    | exp '+' exp
    | exp '-' exp
    | exp '/' exp
    | exp '*' exp
    | exp OPERATOR_LE exp
    | exp OPERATOR_GE exp
    | exp OPERATOR_EQ exp
    | exp OPERATOR_NE exp
    | exp OPERATOR_AND exp
    | exp OPERATOR_OR exp
    | exp '>' exp
    | exp '<' exp 
	;
	
flow_ctrl:
	KW_IF '('exp')' command
	| KW_IF '('exp')' command KW_ELSE command
	| KW_WHILE '('exp ')' command
	;
	
type:
	KW_INT 
	| KW_REAL 
	| KW_BOOL 
	| KW_CHAR
	;
	
lit:
	LIT_INTEGER 
	| LIT_FALSE 
	| LIT_TRUE 
	| LIT_CHAR 
	| LIT_STRING 
	;	
	
arr_init:
	':' lit arr_init2 ;
	| ;
	;

arr_init2:
	lit arr_init2
	| ;
	;
	
func_param:
    exp next_func_param
    | ;
	;
	
next_func_param:
    ',' func_param
    | ;
	;

out:
	exp out2
	;
	
out2:
	',' out
	| ;
	;
	
%%

int yyerror(char * str)
{
	printf("\nErro sintatico na linha %d!\n\n", getLineNumber());
	exit(3);
}

	
