#include "asm.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int loop = 0;
int firstPrint = 0;
int firstVar = 0;

//counters for lables

int intc = 0;
int charc = 0;
int labc = 0;
int func = 0;
int ltmpc = 0;
int bbc = 0;

void asmGenerate(char* filename, TAC* tac)
{
	TAC* tac0 = tac;
	FILE* file;
	
	if(!filename)
		return;
		
	if(!(file = fopen(filename, "a")))
		exit(5); // output file error

	if(loop == 0)	
	{
		fprintf(file, "\t.section\t__TEXT,__text,regular,pure_instructions\n\t.macosx_version_min 10, 11\n\n");
		loop = 1;
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
				switch(loop)
				{
					case 1:
						if(tac->res->dataType == DATATYPE_INT)
						{
							intc++;
							fprintf(file, "movl	$%s, -%d(%%rbp)\n", tac->res->text, (4*intc)+charc);
					
						}
						if(tac->res->dataType == DATATYPE_CHAR)
						{
								charc++;
								fprintf(file, "movb	$%s, -%d(%%rbp)\n", tac->res->text, (4*intc)+charc);
						}
						break;
					default: break;
				}
				break;
			
			case TAC_ADD: // 4
				switch(loop)
				{
					case 1:
                        if(tac->res->dataType == DATATYPE_INT)
                            
                        {
                            printf ("allalaalalalal %s", tac->res->dataType);
                            fprintf(file, "\tmovl	_%s(%%rip), %%ecx\n", tac->op1->text);
                            fprintf(file, "\taddl	_%s(%%rip), %%ecx\n", tac->op2->text);
                            fprintf(file, "\tmovl	%%ecx, _%s(%%rip)\n", tac->res->text);
                            
                        }
                        if(tac->res->dataType == DATATYPE_CHAR)
                        {
                            fprintf(file, "\tmovsbl	_%s(%%rip), %%ecx\n", tac->op1->text);
                            fprintf(file, "\tmovsbl	_%s(%%rip), %%edx\n", tac->op2->text);
                            fprintf(file, "\taddl	%%edx, %%ecx\n");
                            fprintf(file, "\tmovb	%%cl, %%sil\n");
                            fprintf(file, "\tmovb	%%sil, _%s(%%rip)\n", tac->res->text);
                        }
                        break;
					default: break;
				}
                break;
			
			case TAC_SUB: // 5
                switch(loop)
                {
                    case 1:
                        if(tac->res->dataType == DATATYPE_INT)
                            
                        {
                            fprintf(file, "\tmovl	_%s(%%rip), %%ecx\n", tac->op1->text);
                            fprintf(file, "\tsubl	_%s(%%rip), %%ecx\n", tac->op2->text);
                            fprintf(file, "\tmovl	%%ecx, _%s(%%rip)\n", tac->res->text);
                            
                        }
                        if(tac->res->dataType == DATATYPE_CHAR)
                        {
                            fprintf(file, "\tmovsbl	_%s(%%rip), %%ecx\n", tac->op1->text);
                            fprintf(file, "\tmovsbl	_%s(%%rip), %%edx\n", tac->op2->text);
                            fprintf(file, "\tsubl	%%edx, %%ecx\n");
                            fprintf(file, "\tmovb	%%cl, %%sil\n");
                            fprintf(file, "\tmovb	%%sil, _%s(%%rip)\n", tac->res->text);
                        }
                        break;
                    default: break;
                }
                break;
		
			case TAC_MUL: // 6
                switch(loop)
                {
                    case 1:
                        if(tac->res->dataType == DATATYPE_INT)
                            
                        {
                            printf ("allalaalalalal %s", tac->res->dataType);
                            fprintf(file, "\tmovl	_%s(%%rip), %%ecx\n", tac->op1->text);
                            fprintf(file, "\timull	_%s(%%rip), %%ecx\n", tac->op2->text);
                            fprintf(file, "\tmovl	%%ecx, _%s(%%rip)\n", tac->res->text);
                            
                        }
                        if(tac->res->dataType == DATATYPE_CHAR)
                        {
                            fprintf(file, "\tmovsbl	_%s(%%rip), %%ecx\n", tac->op1->text);
                            fprintf(file, "\tmovsbl	_%s(%%rip), %%edx\n", tac->op2->text);
                            fprintf(file, "\timull	%%edx, %%ecx\n");
                            fprintf(file, "\tmovb	%%cl, %%sil\n");
                            fprintf(file, "\tmovb	%%sil, _%s(%%rip)\n", tac->res->text);
                        }
                        break;
                    default: break;
                }
                break;
			
			case TAC_DIV: // 7
                switch(loop)
                {
                    case 1:
                        if(tac->res->dataType == DATATYPE_INT)
                            
                        {
                            fprintf(file, "\tmovl	_%s(%%rip), %%ecx\n", tac->op1->text);
                            fprintf(file, "\tmovl	%%eax, -4(%%rbp)          ## 4-byte Spill\n");
                            fprintf(file, "\tmovl	%%ecx, %%eax\n");
                            fprintf(file, "\tcltd\n");
                            fprintf(file, "idivl	_%s(%%rip)\n",tac->op2->text);
                            fprintf(file, "\tmovl	%%eax, _%s(%%rip)\n", tac->res->text);
                            fprintf(file, "\tmovl	-4(%%rbp), %%eax          ## 4-byte Reload\n");
                            
                        }
                        if(tac->res->dataType == DATATYPE_CHAR)
                        {
                            fprintf(file, "\tmovl	_%s(%%rip), %%ecx\n", tac->op1->text);
                            fprintf(file, "\tmovl	_%s(%%rip), %%edx\n", tac->op2->text);
                            fprintf(file, "\tmovl	%%eax, -4(%%rbp)          ## 4-byte Spill\n");
                            fprintf(file, "\tmovl	%%ecx, %%eax\n");
                            fprintf(file, "\tmovl	%%edx, -8(%%rbp)          ## 4-byte Spill\n");
                            fprintf(file, "\tcltd\n");
                            fprintf(file, "\tmovl	-8(%%rbp), %%ecx          ## 4-byte Reload\n");
                            fprintf(file, "\tidivl  %%ecx\n");
                            fprintf(file, "\tmovb   %%al, %%sil\n");
                            fprintf(file, "\tmovl	%%sil, _%s(%%rip)\n", tac->res->text);
                            fprintf(file, "\tmovl	-4(%%rbp), %%eax          ## 4-byte Reload\n");
                        }
                        break;
                    default: break;
                }
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
				switch(loop)
				{
					case 1:
						bbc = 0;
						fprintf(file, "\n\t.globl\t_%s\n", tac->res->text);
						fprintf(file, "\t.align\t4, 0x90\n");
						fprintf(file, "_%s:\n", tac->res->text);       // \t\t\t\t\t\t\t\t## @_%s                           
						fprintf(file, "\t.cfi_startproc\n");
						fprintf(file, "## BB#%d:\n", bbc);
						fprintf(file, "\tpushq\t%%rbp\n");
						fprintf(file, "Ltmp%d:\n", ltmpc);
						fprintf(file, "\t.cfi_def_cfa_offset 16\n");
						fprintf(file, "Ltmp%d:\n", ltmpc+1);
						fprintf(file, "\t.cfi_offset %%rbp, -16\n");
						fprintf(file, "\tmovq\t%%rsp, %%rbp\n");
						fprintf(file, "Ltmp%d:\n", ltmpc+2);
						fprintf(file, "\t.cfi_def_cfa_register %%rbp\n");
						fprintf(file, "\txorl\t%%eax, %%eax\n");
						//fprintf(file, "\tpopq\t%rbp\n");
						//fprintf(file, "\tretq\n");
						ltmpc = ltmpc + 3;
						bbc++;
						break;
					default: break;
				} 
				break;
			
			case TAC_ENDFUN: // 17
				//fprintf(stderr, "TAC_ENDFUN");
				switch(loop)
				{
					case 1:
						fprintf(file, "\tpopq\t%%rbp\n");
						fprintf(file, "\tretq\n");
						fprintf(file, "\t.cfi_endproc\n");
						break;
					default: break;
				}
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
				switch(loop)
				{
					case 1:
						if(tac->res->dataType == DATATYPE_INT) // aparentemente o return nada mais eh do qum move para o rbp, e a funcao poppa ele pra q, que entao realiza retq
						{
							intc++;
							fprintf(file, "\tmovl	$%s, -%d(%%rbp)\n", tac->res->text, (4*intc)+charc);
					
						}
						if(tac->res->dataType == DATATYPE_CHAR)
						{
								charc++;
								fprintf(file, "\tmovb	$%s, -%d(%%rbp)\n", tac->res->text, (4*intc)+charc);
						}
						break;
					default: break;	
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
				switch(loop)
				{
					case 1: break;
					case 2:
						if(!firstVar)
						{
							fprintf(file, "\n\n\t.section\t__DATA,__data");
							firstVar = 1;
						}
						if(tac->res->dataType == DATATYPE_INT)
							fprintf(file, "\n\t.globl\t_%s\n\t.align\t2\n_%s:\n\t.long\t%s\n", tac->res->text, tac->res->text, tac->next->op1->text);
						if(tac->res->dataType == DATATYPE_CHAR)
							fprintf(file, "\n\t.globl\t_%s\n\t.align\t2\n_%s:\n\t.byte\t%s\n", tac->res->text, tac->res->text, tac->next->op1->text);
						break;
					default: break;
				}

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
	//fprintf(file, "\n");
	fclose(file);
	if(loop < 2)
	{	
		loop++;
		asmGenerate(filename, tac0);
	}
}

