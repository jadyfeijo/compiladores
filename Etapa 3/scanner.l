
%{

#include "ast.h"
#include "y.tab.h"


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

FALSE						{ hashInsert(yytext, SYMBOL_LIT_BOOL); yylval.symbol = hashFind(yytext); return LIT_TRUE; }	
[A-Za-z_][A-Za-z_0-9]*		{ hashInsert(yytext, SYMBOL_LIT_IDENTIFIER); yylval.symbol = hashFind(yytext); return TK_IDENTIFIER; }
[0-9]+						{ hashInsert(yytext, SYMBOL_LIT_INT); yylval.symbol = hashFind(yytext); return LIT_INTEGER; }
'.'                  		{ hashInsert(yytext, SYMBOL_LIT_CHAR); yylval.symbol = hashFind(yytext); return LIT_CHAR; }
\"[^\"]*\"                  { hashInsert(yytext, SYMBOL_LIT_STRING); yylval.symbol = hashFind(yytext); return LIT_STRING; }
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


int yywrap()
{
	running = 0;
	return 1;
}

int isRunning (void) 
{
    	return running;
}

int getLineNumber(void)
{ 
    return lines;
}

void initMe(void) 
{
	hashInit();
}
