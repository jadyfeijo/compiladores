#include <stdio.h>
#include "lex.yy.h"
#include "ast.h"
#include "y.tab.h"
#include "semantic.h"


int main(int argc, char ** argv)
{
	if(argc!=3)
	{
		printf("\nUsage: etapa4 <arquivo> <arquivo2> \n");
		exit(1);
	}
	
	FILE* file;


	if(!(file=fopen(argv[1], "r")))
	{
		printf("\nErro ao abrir %s!\n", argv[1]);
	    exit(2);
	}
	
	yyin = file;
    
    if(!(file=fopen(argv[2], "w"))){
        printf("Erro ao abrir arquivo de saida: %s !\n", argv[2]);
    }
    out_file(file);
    initMe();

    yyparse();

	if(reportSemanticError())
	{
		printf("Erro: existem erros semanticos.\n");
		exit(4);
	}

	printf("\nSucesso!\n\n");
	hashPrint();
	printf("\nFinalizado!\n\n");

	exit(0);
}
