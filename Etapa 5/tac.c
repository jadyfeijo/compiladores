#include "tac.h"

TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2)
{
	TAC* newtac = 0;
	
	newtac = (TAC*) calloc(1,sizeof(TAC));
	newtac->type = type;
	newtac->res = res;
	newtac->op1 = op1;
	newtac->op2 = op2;
	newtac->prev = 0;
	newtac->next = 0;
	return newtac;
}

TAC* tacJoin(TAC* tac1, TAC* tac2)
{
	TAC* aux;
	
	aux = tac2;
	
	if(!tac1) 
		return tac2;
	if(!tac2) 
		return tac1;
	
	for(aux = tac2; aux->prev; aux = aux->prev);
	aux->prev = tac1;
	
	return tac2;
}

void tacPrintListPrev(TAC* tac)
{
	if(!tac)
		return;
		
	tacPrintSingle(tac);
	tacPrintListPrev(tac->prev);
}

TAC* tacReverse(TAC* tac)
{
	TAC* t;
	
	for(t = tac; t->prev; t = t->prev)
		t->prev->next = t;
	
	return t;
}

void tacPrintListNext(TAC* tac)
{
	if(!tac)
		return;
	
	tacPrintSingle(tac);
	tacPrintListNext(tac->next);
}

void tacPrintSingle(TAC* tac)
{
	if(!tac)
		return;
		
	fprintf(stderr, "TAC(");
	switch(tac->type)
	{
		case TAC_SYMBOL: 
			fprintf(stderr, "TAC_SYMBOL");
			break;
			
		case TAC_LABEL: 
			fprintf(stderr, "TAC_LABEL");
			break;	
			
		case TAC_MOVE: 
			fprintf(stderr, "TAC_MOVE");
			break;
			
		case TAC_ADD: 
			fprintf(stderr, "TAC_ADD");
			break;
			
		case TAC_SUB: 
			fprintf(stderr, "TAC_SUB");
			break;	
		
		case TAC_MUL: 
			fprintf(stderr, "TAC_MUL");
			break;
			
		case TAC_DIV: 
			fprintf(stderr, "TAC_DIV");
			break;
			
		case TAC_LESS: 
			fprintf(stderr, "TAC_LESS");
			break;

		case TAC_GREATER: 
			fprintf(stderr, "TAC_GREATER");
			break;
			
		case TAC_LE: 
			fprintf(stderr, "TAC_LE");
			break;	
			
		case TAC_GE: 
			fprintf(stderr, "TAC_GE");
			break;	
			
		case TAC_EQ: 
			fprintf(stderr, "TAC_EQ");
			break;	
			
		case TAC_NE: 
			fprintf(stderr, "TAC_NE");
			break;

		case TAC_AND: 
			fprintf(stderr, "TAC_AND");
			break;

		case TAC_OR: 
			fprintf(stderr, "TAC_OR");
			break;

		case TAC_BEGINFUN: 
			fprintf(stderr, "TAC_BEGINFUN");
			break;
			
		case TAC_ENDFUN: 
			fprintf(stderr, "TAC_ENDFUN");
			break;

		case TAC_IFZ: 
			fprintf(stderr, "TAC_IFZ");
			break;
			
		case TAC_JUMP: 
			fprintf(stderr, "TAC_JUMP");
			break;	
			
		case TAC_CALL: 
			fprintf(stderr, "TAC_CALL");
			break;

		case TAC_ARG: 
			fprintf(stderr, "TAC_ARG");
			break;
			
		case TAC_RET: 
			fprintf(stderr, "TAC_RET");
			break;	
			
		case TAC_PRINT: 
			fprintf(stderr, "TAC_PRINT");
			break;
			
		case TAC_READ: 
			fprintf(stderr, "TAC_READ");
			break;	

		case TAC_ASS: 
			fprintf(stderr, "TAC_ASS");
			break;
			
		default:
			fprintf(stderr, "TAC_DEFAULT");
	}
	
	if(tac->res)
		fprintf(stderr, ",%s", tac->res->text);
//	else
//		fprintf(stderr, ",_");
		
	if(tac->op1)
        fprintf(stderr, ",%s", tac->op1->text);
//	else
//		fprintf(stderr, ",_");
		
	if(tac->op2)
		fprintf(stderr, ",%s", tac->op2->text);
//	else
		fprintf(stderr, ")\n");
    
		
}
