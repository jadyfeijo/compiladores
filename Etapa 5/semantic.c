#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"
#include "ast.h"

int semanticError = 0;
ASTREE* root;
ASTREE* func;

void checkDeclaration(ASTREE* node)
{
	int i;
	ASTREE* aux;
    ASTREE* aux2=NULL;
    ASTREE* aux3=NULL;

	if(root == NULL)
		root = node;
	
	if(!node)
		return;
    
    if(node->type == ASTREE_VARDEC || node->type == ASTREE_VECDEC || node->type == ASTREE_VECDEC_INIT || node->type == ASTREE_FUNDEC_VOID || node->type == ASTREE_FUNDEC_PAR)
	{
		aux = node->son[1];
		if(aux->symbol->type != SYMBOL_LIT_IDENTIFIER)
		{
			fprintf(stderr, "SEMANTIC ERROR: variable %s redeclared!\n", node->symbol->text);
			semanticError = 1;
		}
		else
		{
			switch(node->type) // troca de símbolos
			{
					case ASTREE_VARDEC: aux->symbol->type = SYMBOL_VAR; break;
					case ASTREE_VECDEC:
					case ASTREE_VECDEC_INIT: aux->symbol->type = SYMBOL_VEC; break;
					case ASTREE_FUNDEC_VOID: aux->symbol->type = SYMBOL_FUN; break;
                    case ASTREE_FUNDEC_PAR:
                    if(node->son[2]->son[1]->symbol->type != SYMBOL_LIT_IDENTIFIER)
                    {
                        fprintf(stderr, "SEMANTIC ERROR: variable %s redeclared!\n", node->son[2]->son[1]->symbol->text);
                        semanticError = 1;
                    }
                    else {
                        switch(node->son[2]->son[0]->type) {
                            case ASTREE_TYPEINT: node->son[2]->son[1]->symbol->dataType = DATATYPE_INT;  break;
                            case ASTREE_TYPEREAL: node->son[2]->son[1]->symbol->dataType = DATATYPE_REAL; break;
                            case ASTREE_TYPEBOOL: node->son[2]->son[1]->symbol->dataType = DATATYPE_BOOL; break;
                            case ASTREE_TYPECHAR: node->son[2]->son[1]->symbol->dataType = DATATYPE_CHAR; break;
                            default: break;
                        }
                        node->son[2]->son[1]->symbol->type = SYMBOL_VAR;
                    }
                        aux->symbol->type = SYMBOL_FUN;
                    if (node->son[2]->son[2] != NULL) {
                        aux2 = node->son[2]; // pega lista de parametros da funcao
                        while (aux2->son[2]!=NULL) { // enquanto nao for nula a continuacao, vai setando o parametro como
                            aux2 = aux2->son[2]->son[0];   // variavel
                            switch(aux2->son[0]->type) {
                                case ASTREE_TYPEINT: aux2->son[1]->symbol->dataType = DATATYPE_INT;  break;
                                case ASTREE_TYPEREAL: aux2->son[1]->symbol->dataType = DATATYPE_REAL; break;
                                case ASTREE_TYPEBOOL: aux2->son[1]->symbol->dataType = DATATYPE_BOOL; break;
                                case ASTREE_TYPECHAR: aux2->son[1]->symbol->dataType = DATATYPE_CHAR; break;
                                default: break;
                            }
                            if(aux2->son[1]->symbol->type != SYMBOL_LIT_IDENTIFIER)
                            {
                                fprintf(stderr, "SEMANTIC ERROR: variable %s redeclared!\n", aux2->son[1]->symbol->text);
                                semanticError = 1;
                                break;
                            }
                            aux2->son[1]->symbol->type = SYMBOL_VAR;
                        }
                    }
                    break;
                    
					default: break;
		}
			
		}
		switch(node->son[0]->type) // registro dos tipos de dados
		{
			case ASTREE_TYPEINT: aux->symbol->dataType = DATATYPE_INT;  break;
			case ASTREE_TYPEREAL: aux->symbol->dataType = DATATYPE_REAL; break;
			case ASTREE_TYPEBOOL: aux->symbol->dataType = DATATYPE_BOOL; break;
            case ASTREE_TYPECHAR: aux->symbol->dataType = DATATYPE_CHAR; break;
			default: break;
		}
	}
	
	for(i=0; i<MAX_SONS; i++)
		checkDeclaration(node->son[i]);
}

void checkUsage(ASTREE* node)
{
	int i;
	ASTREE* aux;
	
	aux = (ASTREE *) calloc (1, sizeof(ASTREE));
	
	if(!node)
		return;

	
	
	//fprintf(stderr,"USAGE type = %d\n", node->type);
	
	switch(node->type)
	{
		case ASTREE_ASS:

                if(node->son[0]->symbol->type != SYMBOL_VAR)
                {
                    fprintf(stderr,"SEMANTIC ERROR: Symbol %s must be scalar!\n", node->son[0]->symbol->text);
                    semanticError = 1;
                    break;
                }
            
				if(addExpressionTypes(node->son[0]->symbol->dataType, getType(node->son[1])) == DATATYPE_ERROR)
				{
					//fprintf(stderr,"PASSOU %s %d\n", node->son[0]->symbol->text, node->son[0]->symbol->dataType);
					fprintf(stderr,"SEMANTIC ERROR: Types cannot be assigned!\n");
					semanticError = 1;
				}
			break;
		case ASTREE_ASS_VEC:
                   if(node->son[0]->symbol->type != SYMBOL_VEC)
                      {
                          fprintf(stderr,"SEMANTIC ERROR: Symbol %s must be vector!\n", node->son[0]->symbol->text);
                          semanticError = 1;
                          break;
                      }
					if(addExpressionTypes(node->son[0]->symbol->dataType, getType(node->son[2])) == DATATYPE_ERROR) // compara tipo do vetor com exp (que é o son[2] nesse caso)
					{
						fprintf(stderr,"SEMANTIC ERROR: Types cannot be assingned!\n");
						semanticError = 1;
					}
					if(getType(node->son[1]) != DATATYPE_INT)
					{
						fprintf(stderr,"SEMANTIC ERROR: Vector Index must be integer!\n");
						semanticError = 1;
					}
			break;
        case ASTREE_OUTLIST:
            if (getType(node->son[0]) == DATATYPE_ERROR)
            {
                fprintf(stderr,"SEMANTIC ERROR: Invalid output expression!\n");
                semanticError = 1;
            }
            break;
		case ASTREE_ID:
			if(node->son[0]->symbol->type == SYMBOL_VEC || node->son[0]->symbol->type == SYMBOL_FUN)
			{
				fprintf(stderr,"SEMANTIC ERROR: Symbol %s must be scalar!\n", node->son[0]->symbol->text);
				semanticError = 1;
			}
            if (node->son[0]->symbol->type != SYMBOL_VAR)
            {
               // if (nao declarada no escopo)
                fprintf(stderr,"SEMANTIC ERROR: Symbol %s must be declared!\n", node->son[0]->symbol->text);
                semanticError = 1;
            }
			break;
		case ASTREE_FUNCALL: //terminar
			if(node->son[0]->symbol->type != SYMBOL_FUN)
			{
				fprintf(stderr,"SEMANTIC ERROR: Symbol %s must be function!\n", node->son[0]->symbol->text);
				semanticError = 1;
			}
			if(node->son[0]->symbol->dataType == DATATYPE_ERROR)
			{
				fprintf(stderr,"SEMANTIC ERROR: Function %s undeclared!\n", node->son[0]->symbol->text);
				semanticError = 1;
			}

			switch(isFuncallValid(root,node))
			{
                case 1:break; // ok
				case 2:
                    fprintf(stderr,"SEMANTIC ERROR: Type inconsistence in %s!\n", node->son[0]->symbol->text);
                    semanticError = 1;
                    break; // inconsistencia de tipos
				case 3:
                    fprintf(stderr,"SEMANTIC ERROR: Number of parametres inconsistence in %s!\n", node->son[0]->symbol->text);
                    semanticError = 1;
                    break; // inconsistencia na quantidade de parametros/argumentos
                default:
                    break;
			}
			break;
		case ASTREE_VEC:
			if(node->son[0]->symbol->type != SYMBOL_VEC)
			{
				fprintf(stderr,"SEMANTIC ERROR: Symbol %s must be vector!\n", node->son[0]->symbol->text);
				semanticError = 1;
			}
			if(getType(node->son[1])!= DATATYPE_INT && getType(node->son[1])!= DATATYPE_CHAR)
			{
				fprintf(stderr,"SEMANTIC ERROR: Vector index is not integer or char \n");
				semanticError = 1;
			}			
			break;
		case ASTREE_INPUT:
			if(node->son[0]->symbol->dataType == DATATYPE_ERROR)
			{
				fprintf(stderr,"SEMANTIC ERROR: Variable %s undeclared!\n", node->son[0]->symbol->text);
				semanticError = 1;
			}
			break;
		case ASTREE_IF:
		case ASTREE_IFTE:
			if(getType(node->son[0]) != DATATYPE_BOOL) 
			{
				fprintf(stderr,"SEMANTIC ERROR: If condition type must be BOOL\n");
				semanticError = 1;
			}
			break;
		case ASTREE_WHILE: 
			if(getType(node->son[0]) != DATATYPE_BOOL) 
			{
				fprintf(stderr,"SEMANTIC ERROR: While condition type must be BOOL\n");
				semanticError = 1;
			}		
			break;
	}
	for(i=0; i<MAX_SONS; i++)
		checkUsage(node->son[i]);	
	
}

int addExpressionTypes (int type1, int type2) 
{
    switch (type1) 
	{
        case DATATYPE_BOOL:
            switch (type2) 
			{
                case DATATYPE_BOOL:
                    return DATATYPE_BOOL;
                default:
                    return DATATYPE_ERROR;
            }
			//break;
        case DATATYPE_INT:
            switch (type2) 
			{
                case DATATYPE_INT:
                    return DATATYPE_INT;
                case DATATYPE_CHAR:
                    return DATATYPE_INT;
                case DATATYPE_REAL:
                    return DATATYPE_REAL;
                default:
                    return DATATYPE_ERROR;
            }
			//break;
        case DATATYPE_CHAR:
            switch (type2) 
			{
                case DATATYPE_INT:
                    return DATATYPE_INT;
                case DATATYPE_CHAR:
                    return DATATYPE_CHAR;
                case DATATYPE_REAL:
                    return DATATYPE_REAL;
                default:
                    return DATATYPE_ERROR;
            }
			//break;
        case DATATYPE_REAL:
            switch (type2) 
			{
                case DATATYPE_BOOL:
                    return DATATYPE_ERROR;
                case DATATYPE_ERROR:
                    return DATATYPE_ERROR;
                default:
                    return DATATYPE_REAL;
            }
			//break;
        default:
            return DATATYPE_ERROR;
    }
}

int getType(ASTREE* node) 
{
	int op1, op2;
	
	/*if(!node)
		return;*/
	
	switch(node->type) 
	{
		case ASTREE_SYMBOL: 
			return node->symbol->dataType;
		case ASTREE_ID:
			return node->son[0]->symbol->dataType;
		case ASTREE_VEC:
			return node->son[0]->symbol->dataType;
		case ASTREE_FUNCALL:
			return node->son[0]->symbol->dataType;
		case ASTREE_EXP:
			return getType(node->son[0]);
		case ASTREE_ADD:
		case ASTREE_SUB:
		case ASTREE_DIV:
		case ASTREE_MUL:
				op1 = getType(node->son[0]);
			    op2 = getType(node->son[1]);
				return addExpressionTypes(op1,op2);
		case ASTREE_LE:
		case ASTREE_GE:
		case ASTREE_EQ:
		case ASTREE_NE:
		case ASTREE_AND:
		case ASTREE_OR: 
		case ASTREE_GREATER:
		case ASTREE_LESS: 
			return DATATYPE_BOOL;
	}
}

int isFuncallValid(ASTREE* root, ASTREE* node) // implementar - implementado
{
    if((root->type == ASTREE_FUNDEC_PAR || root->type == ASTREE_FUNDEC_VOID) && strcmp(root->son[1]->symbol->text,node->son[0]->symbol->text)==0)
    {
        ASTREE *declaration_param_list = NULL;
        int dec_type, call_type;
        if (root->type == ASTREE_FUNDEC_PAR) {
             declaration_param_list = root->son[2];
        }
        ASTREE *funcall_param_list = node->son[1];
            
        
        if(declaration_param_list == NULL && funcall_param_list==NULL) return 1;
        if(declaration_param_list == NULL || funcall_param_list==NULL) return 3; // quantidade de variaveis diferentes
        while(declaration_param_list!=NULL && funcall_param_list!=NULL){
            switch(declaration_param_list->son[0]->type)
            {
                case ASTREE_TYPEINT:
                    dec_type = DATATYPE_INT; break;
                case ASTREE_TYPECHAR:
                    dec_type = DATATYPE_CHAR; break;
                case ASTREE_TYPEREAL:
                    dec_type = DATATYPE_REAL; break;
                case ASTREE_TYPEBOOL:
                    dec_type = DATATYPE_BOOL; break;
                default: dec_type = DATATYPE_ERROR; break;
            }
            call_type = getType(funcall_param_list->son[0]);
            if(addExpressionTypes(dec_type,call_type)==DATATYPE_ERROR){
                return 2;//tipo de variavel incompativel na chamada de funcao
            }

			//funcall_param_list->son[0]->type = declaration_param_list->son[0]->symbol; /////////////

            if (declaration_param_list->son[2])
            declaration_param_list=declaration_param_list->son[2]->son[0];
            else
                declaration_param_list=NULL;
            if (funcall_param_list->son[1])
            	funcall_param_list=funcall_param_list->son[1]->son[0];
			
            else
                funcall_param_list=NULL;
        }
       if(declaration_param_list==NULL && funcall_param_list==NULL) return 1; //quantidade diferente de parametros
        
        return 3; // ok
    }
    else
    {
        int number_sons = 0;
        for(number_sons=0;number_sons<4;number_sons++)
        {
            if(root->son[number_sons]!=NULL){
                int found = isFuncallValid(root->son[number_sons],node);
                if(found !=5) return found; // achou a comparacao
            }
        }
    }
    return 5;

}

int reportSemanticError()
{
	return semanticError;
}
