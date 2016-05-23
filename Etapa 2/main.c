#include <stdio.h>
#include "lex.yy.h"
#include "y.tab.h"



int main(int argc, char ** argv)
{
	if(argc!=2)
	{
		printf("\nUsage: etapa2 <arquivo>\n");
		exit(1);
	}
	
	FILE* file;

	initMe();

	if(!(file=fopen(argv[1], "r")))
	{
		printf("\nErro ao abrir %s!\n", argv[1]);
	    exit(1);
	}
	
	yyin = file;
	yyparse();
	
	printf("\nSucesso!\n\n");
	hashPrint();
	printf("\nFinalizado!\n\n");

	exit(0);
}
