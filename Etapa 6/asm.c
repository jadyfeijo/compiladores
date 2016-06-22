#include "asm.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int first = 0;
int firstPrint = 0;

//counters for lables

int intc = 0;
int charc = 0;
int labc = 0;
int func = 0;
int ltmpc = 0;
int bbc = 0;

void asmGenerate(char* filename, TAC* tac)
{

	FILE* file;
	
	if(!filename)
		return;
		
	if(!(file = fopen(filename, "w")))
		exit(5); // output file error

	if(!first)	
	{
		fprintf(file, "\t.section\t__TEXT,__text,regular,pure_instructions\n\t.macosx_version_min 10, 11\n\n");
		first = 1;
	}

	// generate asm code

	for( ; tac; tac = tac->next)
	{
		switch(tac->type)
		{

			case TAC_SYMBOL: // 1
				break;
			
			case TAC_LABEL: // 2
				//fprintf(stderr, "TAC_LABEL");
				break;	
			
			case TAC_MOVE: // 3
				if(tac->res->dataType == DATATYPE_INT)
				{
					intc++;
					fprintf(file, "movl	$%s, -%d(%rbp)\n", tac->res->text, (4*intc)+charc);
					
				}
				if(tac->res->dataType == DATATYPE_CHAR)
				{
						charc++;
						fprintf(file, "movb	$%s, -%d(%rbp)\n", tac->res->text, (4*intc)+charc);
				}
				break;
			
			case TAC_ADD: // 4
                if(tac->res->dataType == DATATYPE_INT)
                {
                    intc++;
                    fprintf(file, "movl	$%s, -%d(%rbp)\n", tac->res->text, (4*intc)+charc);
                    
                }
                if(tac->res->dataType == DATATYPE_CHAR)
                {
                    charc++;
                    fprintf(file, "movb	$%s, -%d(%rbp)\n", tac->res->text, (4*intc)+charc);
                }
				break;
			
			case TAC_SUB: // 5
				//fprintf(stderr, "TAC_SUB");
				break;	
		
			case TAC_MUL: // 6
				//fprintf(stderr, "TAC_MUL");
				break;
			
			case TAC_DIV: // 7
				//fprintf(stderr, "TAC_DIV");
				break;
			
			case TAC_LESS: // 8
				//fprintf(stderr, "TAC_LESS");
				break;

			case TAC_GREATER: // 9
				//fprintf(stderr, "TAC_GREATER");
				break;
			
			case TAC_LE: // 10
				//fprintf(stderr, "TAC_LE");
				break;	
			
			case TAC_GE: // 11
				//fprintf(stderr, "TAC_GE");
				break;	
			
			case TAC_EQ: // 12
				//fprintf(stderr, "TAC_EQ");
				break;	
			
			case TAC_NE: // 13
				//fprintf(stderr, "TAC_NE");
				break;

			case TAC_AND: // 14
				//fprintf(stderr, "TAC_AND");
				break;

			case TAC_OR: // 15
				//fprintf(stderr, "TAC_OR");
				break;

			case TAC_BEGINFUN: // 16
				bbc = 0;
				fprintf(file, "\n\t.globl\t_%s\n", tac->res->text);
				fprintf(file, "\t.align\t4, 0x90\n");
				fprintf(file, "_%s:\n", tac->res->text);       // \t\t\t\t\t\t\t\t## @_%s                           
				fprintf(file, "\t.cfi_startproc\n");
				fprintf(file, "## BB#%d:\n", bbc);
				fprintf(file, "\tpushq\t%rbp\n");
				fprintf(file, "Ltmp%d:\n", ltmpc);
				fprintf(file, "\t.cfi_def_cfa_offset 16\n");
				fprintf(file, "Ltmp%d:\n", ltmpc+1);
				fprintf(file, "\t.cfi_offset %rbp, -16\n");
				fprintf(file, "\tmovq\t%rsp, %rbp\n");
				fprintf(file, "Ltmp%d:\n", ltmpc+2);
				fprintf(file, "\t.cfi_def_cfa_register %rbp\n");
				fprintf(file, "\txorl\t%%eax, %%eax\n");
				//fprintf(file, "\tpopq\t%rbp\n");
				//fprintf(file, "\tretq\n");
				ltmpc = ltmpc + 3;
				bbc++;
				break;
			
			case TAC_ENDFUN: // 17
				//fprintf(stderr, "TAC_ENDFUN");
				fprintf(file, "\tpopq\t%rbp\n");
				fprintf(file, "\tretq\n");
				fprintf(file, "\t.cfi_endproc\n");
				break;

			case TAC_IFZ: // 18
				//fprintf(stderr, "TAC_IFZ");
				break;
			
			case TAC_JUMP: // 19
				//fprintf(stderr, "TAC_JUMP");
				break;	
			
			case TAC_CALL: // 20
				//fprintf(stderr, "TAC_CALL");
				break;

			case TAC_ARG: // 21
				//fprintf(stderr, "TAC_ARG");
				break;
			
			case TAC_RET: // 22
				//fprintf(stderr, "TAC_RET");
				if(tac->res->dataType == DATATYPE_INT) // aparentemente o return nada mais eh do qum move para o rbp, e a funcao poppa ele pra q, que entao realiza retq
				{
					intc++;
					fprintf(file, "\tmovl	$%s, -%d(%rbp)\n", tac->res->text, (4*intc)+charc);
					
				}
				if(tac->res->dataType == DATATYPE_CHAR)
				{
						charc++;
						fprintf(file, "\tmovb	$%s, -%d(%rbp)\n", tac->res->text, (4*intc)+charc);
				}
				break;	
			
			case TAC_PRINT: // 23
				//fprintf(stderr, "TAC_PRINT");
				break;
			
			case TAC_READ: // 24
				//fprintf(stderr, "TAC_READ");
				break;	

			case TAC_ASS: // 25
				//fprintf(stderr, "TAC_ASS");
				break;

			case TAC_VARDEC: // 26
				//fprintf(stderr, "TAC_VARDEC");
				break;

			case TAC_VECDEC: // 27
				//fprintf(stderr, "TAC_VECDEC");
				break;

			case TAC_VECDEC_INIT: // 28
				//fprintf(stderr, "TAC_VECDEC_INIT");
				break;

			case TAC_ASS_VEC: // 29
				//fprintf(stderr, "TAC_ASS_VEC");
				break;
		        
		    case TAC_FUNCALL: // 30
		        //fprintf(stderr, "TAC_FUNCALL");
		        break;
		  
		    case TAC_FUNDEC_PARAM: // 31
		        //fprintf(stderr, "TAC_FUNDEC_PARAM");
		        break;
		    
			case TAC_VEC_INDEX: // 32
		        //fprintf(stderr, "TAC_VEC_INDEX");
		        break;
		        
			case TAC_ASS_VEC_INDEX: // 33
		        //fprintf(stderr, "TAC_ASS_VEC_INDEX");
		        break;	

		    default: break;
				//fprintf(stderr, "TAC_DEFAULT");			
		}
	}
}

