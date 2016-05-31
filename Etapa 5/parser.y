%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "semantic.h"
#include "genco.h"

FILE *out = NULL;

%}



%token KW_INT        //256
%token KW_REAL       //257
%token KW_BOOL       //258
%token KW_CHAR       //259
%token KW_IF         //261
%token KW_ELSE       //263
%token KW_WHILE      //264
%token KW_INPUT      //266
%token KW_RETURN     //267
%token KW_OUTPUT     //268

%token OPERATOR_LE   //270
%token OPERATOR_GE   //271
%token OPERATOR_EQ   //272
%token OPERATOR_NE   //273
%token OPERATOR_AND  //274
%token OPERATOR_OR   //275

%token TK_IDENTIFIER //280
%token LIT_INTEGER   //281
%token LIT_FALSE    // 283ww
%token LIT_TRUE	  	// 284
%token LIT_CHAR      //285
%token LIT_STRING   // 286

%token TOKEN_ERROR   //290

%right '='
%left  '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE OPERATOR_AND OPERATOR_OR
%left '+' '-'
%left '*' '/'

%type<astree> init
%type<astree> program
%type<astree> decl
%type<astree> decl_prmt
%type<astree> decl_prmt2
%type<astree> block
%type<astree> list_cmd
%type<astree> command
%type<astree> exp
%type<astree> flow_ctrl
%type<astree> type
%type<astree> lit
%type<astree> lit2
%type<astree> arr_init
%type<astree> func_param
%type<astree> next_func_param
%type<astree> out
%type<astree> out2
//%type<astree> KW_INT
//%type<astree> KW_REAL
//%type<astree> KW_BOOL
//%type<astree> KW_CHAR
//%type<astree> KW_INPUT
//%type<astree> KW_RETURN
//%type<astree> KW_OUTPUT
%type<astree> tam
%type<astree> identifier


%type<symbol> TK_IDENTIFIER 	
%type<symbol> LIT_INTEGER 		  
%type<symbol> LIT_FALSE 		  
%type<symbol> LIT_TRUE 				 
%type<symbol> LIT_CHAR 			  
%type<symbol> LIT_STRING 		 


%union
{
	HASH_NODE * symbol;
	ASTREE * astree;
}


%%

init: program																{ $$ = $1;TAC* tac; /*astreePrint($$,0);*/ tac = tacReverse(generateCode($1)); tacPrintListNext(tac); checkDeclaration($$); checkUsage($$); /*code_generate(out,$$);*/}
	;

program: 
	decl ';' program														{$$ = astreeCreate(ASTREE_DEC,0,$1,$3,0,0);}																		
	|																		{$$ = 0;}																											
	;
	
decl:
	type identifier '(' decl_prmt ')' command 							{$$ = astreeCreate(ASTREE_FUNDEC_PAR,0,$1,$2,$4,$6);}		
	| type identifier '(' ')' command 									{$$ = astreeCreate(ASTREE_FUNDEC_VOID,0,$1,$2,$5,0);}
	| type identifier ':' lit 											{$$ = astreeCreate(ASTREE_VARDEC,0,$1,$2,$4,0);}
	| type identifier '[' tam ']' 										{$$ = astreeCreate(ASTREE_VECDEC,0,$1,$2,$4,0);}
	| type identifier '[' tam ']' ':' arr_init 							{$$ = astreeCreate(ASTREE_VECDEC_INIT,0,$1,$2,$4,$7);}		
	;

identifier:
	TK_IDENTIFIER 															{$$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);}
	;

tam:
	LIT_INTEGER																{$$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);}
	;
	
decl_prmt:
	type identifier decl_prmt2											{$$ = astreeCreate(ASTREE_PAR,0,$1,$2,$3,0);}
	;
	
decl_prmt2:	
	',' decl_prmt															{$$ = astreeCreate(ASTREE_PAR2,0,$2,0,0,0);}
	|																		{$$ = 0;}
	;
	
block:																		
	'{' list_cmd '}'														/*{$$ = $2;}//*/{$$ = astreeCreate(ASTREE_BLOCK,0,$2,0,0,0);}
	;
	
list_cmd:
	command list_cmd														{$$ = astreeCreate(ASTREE_LCMD,0,$1,$2,0,0);}
	| command																{$$ = astreeCreate(ASTREE_LCMD,0,$1,0,0,0);}
	;
	
command:
	identifier '=' exp													{$$ = astreeCreate(ASTREE_ASS,0,$1,$3,0,0);}
	| identifier '[' exp ']' '=' exp										{$$ = astreeCreate(ASTREE_ASS_VEC,0,$1,$3,$6,0);}
	| KW_INPUT identifier												{$$ = astreeCreate(ASTREE_INPUT,0,$2,0,0,0);}
	| KW_RETURN exp															{$$ = astreeCreate(ASTREE_RETURN,0,$2,0,0,0);}
	| KW_OUTPUT out															{$$ = astreeCreate(ASTREE_OUTPUT,0,$2,0,0,0);}
	| flow_ctrl																{$$ = $1;}
	| block																	{$$ = $1;}
	| ';'																	{$$ = astreeCreate(ASTREE_EMPTYCMD,0,0,0,0,0);}	
	;
	
exp:
	identifier															/*{$$ = $1;}*/ {$$ = astreeCreate(ASTREE_ID,0,$1,0,0,0);}
    | identifier '['exp']'												{$$ = astreeCreate(ASTREE_VEC,0,$1,$3,0,0);}
    | identifier '(' func_param ')'										{$$ = astreeCreate(ASTREE_FUNCALL,0,$1,$3,0,0);}
    | '(' exp ')'															{$$ = astreeCreate(ASTREE_EXP,0,$2,0,0,0);}
    | lit																	{$$ = $1;}//{$$ = astreeCreate(ASTREE_SYMBOL,0,$1,0,0,0);}
    | exp '+' exp															{$$ = astreeCreate(ASTREE_ADD,0,$1,$3,0,0);}
    | exp '-' exp															{$$ = astreeCreate(ASTREE_SUB,0,$1,$3,0,0);}
    | exp '/' exp															{$$ = astreeCreate(ASTREE_DIV,0,$1,$3,0,0);}
    | exp '*' exp															{$$ = astreeCreate(ASTREE_MUL,0,$1,$3,0,0);}
    | exp OPERATOR_LE exp													{$$ = astreeCreate(ASTREE_LE,0,$1,$3,0,0);}
    | exp OPERATOR_GE exp													{$$ = astreeCreate(ASTREE_GE,0,$1,$3,0,0);}
    | exp OPERATOR_EQ exp													{$$ = astreeCreate(ASTREE_EQ,0,$1,$3,0,0);}
    | exp OPERATOR_NE exp													{$$ = astreeCreate(ASTREE_NE,0,$1,$3,0,0);}
    | exp OPERATOR_AND exp													{$$ = astreeCreate(ASTREE_AND,0,$1,$3,0,0);}
    | exp OPERATOR_OR exp													{$$ = astreeCreate(ASTREE_OR,0,$1,$3,0,0);}
    | exp '>' exp															{$$ = astreeCreate(ASTREE_GREATER,0,$1,$3,0,0);}
    | exp '<' exp 															{$$ = astreeCreate(ASTREE_LESS,0,$1,$3,0,0);}
	;
	
flow_ctrl:
	KW_IF '('exp')' command													{$$ = astreeCreate(ASTREE_IF,0,$3,$5,0,0);}
	| KW_IF '('exp')' command KW_ELSE command								{$$ = astreeCreate(ASTREE_IFTE,0,$3,$5,$7,0);}
	| KW_WHILE '('exp ')' command											{$$ = astreeCreate(ASTREE_WHILE,0,$3,$5,0,0);}
	;
	
type:
	KW_INT 																	{$$ = astreeCreate(ASTREE_TYPEINT,0,0,0,0,0);}
	| KW_REAL 																{$$ = astreeCreate(ASTREE_TYPEREAL,0,0,0,0,0);}
	| KW_BOOL 																{$$ = astreeCreate(ASTREE_TYPEBOOL,0,0,0,0,0);}
	| KW_CHAR																{$$ = astreeCreate(ASTREE_TYPECHAR,0,0,0,0,0);}
	;
	
lit:
	LIT_INTEGER 															{$$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);}
	| LIT_FALSE 															{$$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);}
	| LIT_TRUE 																{$$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);}
	| LIT_CHAR 																{$$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);}
	;	

lit2:
    LIT_STRING                                                              {$$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);}
    ;

arr_init:
	lit arr_init															{$$ = astreeCreate(ASTREE_ARR_INIT,0,$1,$2,0,0);}
	| lit 																	{$$ = $1;}
	;

	
func_param:
    exp next_func_param														{$$ = astreeCreate(ASTREE_CALL_PAR,0,$1,$2,0,0);}
	|																		{$$ = 0;}
	;
	
next_func_param:
    ',' func_param															{$$ = astreeCreate(ASTREE_CALL_PAR2,0,$2,0,0,0);}
    | 																		{$$ = 0;}
	;

out:
	exp out2																{$$ = astreeCreate(ASTREE_OUTLIST,0,$1,$2,0,0);}
	| lit2 out2                                                             {$$ = astreeCreate(ASTREE_OUTLIST,0,$1,$2,0,0);}
	;
	
out2:
	',' out																	{$$ = astreeCreate(ASTREE_OUTLIST2,0,$2,0,0,0);}	
	| LIT_STRING 															{$$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);}								
	| 																		{$$ = 0;}
	;
	
%%
void out_file(FILE * o) {
    out = o;
}
int yyerror(char * str)
{
	printf("\nErro sintatico na linha %d!\n\n", getLineNumber());
	exit(3);
}

	
