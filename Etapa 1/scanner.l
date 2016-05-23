
%{

//#include "hash.c"
#include "tokens.h"


int lines = 1;
int running = 1;

%}

%x COMMENT_SECTION

%%

[ \t]                       { }
int							{ return KW_INT; }
real						{ return KW_REAL; }
bool						{ return KW_BOOL; }
char						{ return KW_CHAR; }
if							{ return KW_IF; }
else						{ return KW_ELSE; }
while						{ return KW_WHILE; }
input						{ return KW_INPUT; }
return						{ return KW_RETURN; }
output						{ return KW_OUTPUT; }

"<="						{ return OPERATOR_LE; }
">="						{ return OPERATOR_GE; }
"=="						{ return OPERATOR_EQ; }
"!="						{ return OPERATOR_NE; }
"&&"						{ return OPERATOR_AND; }
"||"						{ return OPERATOR_OR; }

[A-Za-z_][A-Za-z_0-9]*		{ hashInsert(yytext, TK_IDENTIFIER); return TK_IDENTIFIER; }
[0-9]+						{ hashInsert(yytext, LIT_INTEGER); return LIT_INTEGER; }
FALSE						{ hashInsert(yytext, LIT_FALSE); return LIT_FALSE; }
TRUE						{ hashInsert(yytext, LIT_TRUE); return LIT_TRUE; }	
'[a-zA-Z]'                  { hashInsert(yytext, LIT_CHAR); return LIT_CHAR; }
\"[^\"]*\"                  { hashInsert(yytext, LIT_STRING); return LIT_STRING; }
[\-\,\;\:\(\)\{\}\[\]\+\*\/\<\>\=\!\&\$]		{ return yytext[0]; }
"\n"						{ lines++; }

"//".*						// IGNORE
"/*"						{ BEGIN(COMMENT_SECTION); }
<COMMENT_SECTION>"*/"		{ BEGIN(INITIAL); }
<COMMENT_SECTION>"\n"		{ lines++; }
<COMMENT_SECTION>"\t"       { }
<COMMENT_SECTION>.
.                           { return TOKEN_ERROR; }



%%


int yywrap() // pelo que eu entendi, tem que ter isso assim desse jeito mesmo
{
	running = 0;
	return 1;
}

int isRunning (void) 
{
    	return running;
}

int getLineNumber(void) // retorna a linha do negocio ali de cima encontrado
{ 
    return lines;
}

void initMe(void) 
{
	hashInit();
}
