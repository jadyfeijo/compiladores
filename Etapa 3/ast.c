#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

ASTREE * astreeCreate(int type, HASH_NODE * symbol, ASTREE * son0, ASTREE * son1, ASTREE * son2, ASTREE * son3)
{
	ASTREE *newnode;
	
	newnode = (ASTREE *) calloc (1, sizeof(ASTREE));
	
	newnode->type = type;
	newnode->symbol = symbol;
	newnode->son[0] = son0;
	newnode->son[1] = son1;
	newnode->son[2] = son2;
	newnode->son[3] = son3;

	return newnode;
}

void astreePrint(ASTREE * node, int level)
{
	int i;
	
	
	if(!node)
	{
		return;
	}
	
	//fprintf(stderr, "%d", level);
	for(i = 0; i < level; i++)
		fprintf(stderr, "  ");
	//fprintf(stderr, "Astree");
	switch(node->type)
	{
		case ASTREE_UNDEFINED: fprintf(stderr, "UNDEFINED"); break;
		case ASTREE_SYMBOL: fprintf(stderr, "ASTREE_SYMBOL"); break;
		case ASTREE_ADD: fprintf(stderr, "ASTREE_ADD"); break;
		case ASTREE_MUL: fprintf(stderr, "ASTREE_MUL"); break;
		case ASTREE_SUB: fprintf(stderr, "ASTREE_SUB"); break;
		case ASTREE_DIV: fprintf(stderr, "ASTREE_DIV"); break;
		case ASTREE_LESS: fprintf(stderr, "ASTREE_LESS"); break;
		case ASTREE_GREATER: fprintf(stderr, "ASTREE_GREATER"); break;
		case ASTREE_LE: fprintf(stderr, "ASTREE_LE"); break;
		case ASTREE_GE: fprintf(stderr, "ASTREE_GE"); break;
		case ASTREE_EQ: fprintf(stderr, "ASTREE_EQ"); break;
		case ASTREE_NE: fprintf(stderr, "ASTREE_NE"); break;
		case ASTREE_AND: fprintf(stderr, "ASTREE_AND"); break;
		case ASTREE_OR: fprintf(stderr, "ASTREE_OR"); break;
		case ASTREE_ASS: fprintf(stderr, "ASTREE_ASS"); break;
		case ASTREE_LCMD: fprintf(stderr, "ASTREE_LCMD"); break;
		case ASTREE_IF: fprintf(stderr, "ASTREE_IF"); break;
		case ASTREE_IFTE: fprintf(stderr, "ASTREE_IFTE"); break;
		case ASTREE_VARDEC: fprintf(stderr, "ASTREE_VARDEC"); break;
		case ASTREE_VECDEC: fprintf(stderr, "ASTREE_VECDEC"); break;
		case ASTREE_VECDEC_INIT: fprintf(stderr, "ASTREE_VECDEC_INIT"); break;
		case ASTREE_FUNDEC_VOID: fprintf(stderr, "ASTREE_FUNDEC_VOID"); break;
		case ASTREE_FUNDEC_PAR: fprintf(stderr, "ASTREE_FUNDEC_PAR"); break;
		case ASTREE_TYPEINT: fprintf(stderr, "ASTREE_TYPEINT"); break;
		case ASTREE_TYPEREAL: fprintf(stderr, "ASTREE_TYPEREAL"); break;
		case ASTREE_TYPEBOOL: fprintf(stderr, "ASTREE_TYPEBOOL"); break;
		case ASTREE_TYPECHAR: fprintf(stderr, "ASTREE_TYPECHAR"); break;
        case ASTREE_FUNCALL: fprintf(stderr, "ASTREE_FUNCALL"); break;
        case ASTREE_ARR_INIT: fprintf(stderr, "ASTREE_ARR_INIT"); break;
        case ASTREE_PAR: fprintf(stderr, "ASTREE_PAR"); break;
        case ASTREE_PAR2: fprintf(stderr, "ASTREE_PAR2"); break;
        case ASTREE_INPUT: fprintf(stderr, "ASTREE_INPUT"); break;
        case ASTREE_RETURN: fprintf(stderr, "ASTREE_RETURN"); break;
        case ASTREE_OUTPUT: fprintf(stderr, "ASTREE_OUTPUT"); break;
        case ASTREE_WHILE: fprintf(stderr, "ASTREE_WHILE"); break;
        case ASTREE_EXP: fprintf(stderr, "ASTREE_EXP"); break;
        case ASTREE_VEC: fprintf(stderr, "ASTREE_VEC"); break;
        case ASTREE_CALL_PAR: fprintf(stderr, "ASTREE_CALL_PAR"); break;
        case ASTREE_CALL_PAR2: fprintf(stderr, "ASTREE_CALL_PAR2"); break;
        case ASTREE_OUTLIST: fprintf(stderr, "ASTREE_OUTLIST"); break;
        case ASTREE_OUTLIST2: fprintf(stderr, "ASTREE_OUTLIST2"); break;
		case ASTREE_DEC: fprintf(stderr, "ASTREE_DEC"); break;
		case ASTREE_EMPTYCMD: fprintf(stderr, "ASTREE_EMPTYCMD"); break;
		case ASTREE_BLOCK: fprintf(stderr, "ASTREE_BLOCK"); break;
		default: fprintf(stderr, "DEFAULT"); break;
	}
	
	if(node->symbol)
		fprintf(stderr, " %s", node->symbol->text);
	fprintf(stderr,"\n");
	for(i = 0; i < MAX_SONS; i++)
	{
		//fprintf(stderr, "<%d>", i);
		astreePrint(node->son[i], level+1);
	}

}

void code_generate(FILE * out, ASTREE *node) {
    ASTREE *ast;
    ast = node;
    
    if(ast != NULL) {
        switch(ast->type) {
                
            case ASTREE_FUNDEC_PAR:
                code_generate(out, ast->son[0]);
                fprintf (out, " ");
                code_generate(out, ast->son[1]);
                fprintf (out, "(");
                code_generate(out, ast->son[2]);
                fprintf (out, ") ");
                code_generate(out, ast->son[3]);
                fprintf (out, ";\n");
                break;
            case ASTREE_FUNDEC_VOID:
                code_generate(out, ast->son[0]);
                fprintf (out, " ");
                code_generate(out, ast->son[1]);
                fprintf (out, "()");
                code_generate(out, ast->son[2]);
                fprintf (out, ";\n");
                break;
                
            case ASTREE_VARDEC:
                code_generate(out, ast->son[0]);
                fprintf(out, " ");
                code_generate(out, ast->son[1]);
                fprintf(out, " : ");
                code_generate(out, ast->son[2]);
                fprintf(out, ";\n");
                break;
                
            case ASTREE_VECDEC:
                code_generate(out, ast->son[0]);
                fprintf (out, " ");
                code_generate(out, ast->son[1]);
                fprintf (out, "[");
                code_generate(out, ast->son[2]);
                fprintf (out, "]");
                fprintf(out, ";\n");
                break;
                
            case ASTREE_VECDEC_INIT:
                code_generate(out, ast->son[0]);
                fprintf (out, " ");
                code_generate(out, ast->son[1]);
                fprintf (out, "[");
                code_generate(out, ast->son[2]);
                fprintf (out, "] : ");
                code_generate(out, ast->son[3]);
                fprintf(out, ";\n");
                break;
                
            case ASTREE_DEC:
                code_generate(out, ast->son[0]);
                code_generate(out, ast->son[1]);
                break;
                
            case ASTREE_EMPTYCMD:
                fprintf(out, "; ");
                break;
                
            case ASTREE_ARR_INIT:
                code_generate(out, ast->son[0]);
                fprintf (out, " ");
                code_generate(out, ast->son[1]);
                break;
                
            case ASTREE_TYPEINT:
                fprintf(out, "int");
                break;
                
            case ASTREE_TYPECHAR:
                fprintf(out, "char");
                break;
                
            case ASTREE_TYPEREAL:
                fprintf(out, "real");
                break;
                
            case ASTREE_TYPEBOOL:
                fprintf(out, "bool");
                break;
                
            case ASTREE_SYMBOL:
                if (!ast->symbol)
                    fprintf(out, "[erro no node]");
                else if (!ast->symbol->text)
                    fprintf(out, "[erro na data]");
                else
                    fprintf(out, "%s", ast->symbol->text);
                break;
                
            case ASTREE_BLOCK:
                fprintf (out, "{\n");
                code_generate(out, ast->son[0]);
                fprintf (out, "}");
                break;
                
            case ASTREE_LCMD:
                code_generate(out, ast->son[0]);
                if (ast->son[1]) {
                    fprintf(out, "\n");
                    code_generate(out, ast->son[1]);
                }
                break;
                
            case ASTREE_ASS:
                if (!ast->son[2]) {
                    code_generate(out, ast->son[0]);
                    fprintf (out, " = ");
                    code_generate(out, ast->son[1]);
                }
                else {
                    code_generate(out, ast->son[0]);
                    fprintf (out, "[");
                    code_generate(out, ast->son[1]);
                    fprintf (out, "] = ");
                    code_generate(out, ast->son[2]);
                }
                break;
                
                
            case ASTREE_INPUT:
                fprintf (out, "input ");
                code_generate(out, ast->son[0]);
                break;
                
            case ASTREE_OUTPUT:
                fprintf (out, "output ");
                code_generate(out, ast->son[0]);
                break;
                
            case ASTREE_RETURN:
                fprintf (out, "return ");
                code_generate(out, ast->son[0]);
                break;
                
            case ASTREE_IF:
                fprintf (out, "if (");
                code_generate(out, ast->son[0]);
                fprintf (out, ")\n");
                code_generate(out, ast->son[1]);
                break;
                
            case ASTREE_IFTE:
                fprintf (out, "if (");
                code_generate(out, ast->son[0]);
                fprintf (out, ")\n");
                code_generate(out, ast->son[1]);
                fprintf (out, " else\n");
                code_generate(out, ast->son[2]);
                break;
                
            case ASTREE_WHILE:
                fprintf (out, "while (");
                code_generate(out, ast->son[0]);
                fprintf (out, ")\n");
                code_generate(out, ast->son[1]);
                break;
                
                
            case ASTREE_CALL_PAR:
                code_generate(out, ast->son[0]);
                code_generate(out, ast->son[1]);
                break;
                
            case ASTREE_CALL_PAR2:
                fprintf(out, ", ");
                code_generate(out, ast->son[0]);
                break;
                
            case ASTREE_OUTLIST:
                code_generate(out, ast->son[0]);
                code_generate(out, ast->son[1]);
                break;
                
            case ASTREE_OUTLIST2:
                fprintf(out, ", ");
                code_generate(out, ast->son[0]);
                break;
                
            case ASTREE_PAR:
                code_generate(out, ast->son[0]);
                fprintf(out, " ");
                code_generate(out, ast->son[1]);
                code_generate(out, ast->son[2]);
                break;
                
            case ASTREE_PAR2:
                fprintf(out, ", ");
                code_generate(out, ast->son[0]);
                break;
                
            case ASTREE_VEC:
                code_generate(out, ast->son[0]);
                fprintf (out, "[");
                code_generate(out, ast->son[1]);
                fprintf (out, "]");
                break;
                
            case ASTREE_FUNCALL:
                code_generate(out, ast->son[0]);
                fprintf (out, "(");
                code_generate(out, ast->son[1]);
                fprintf(out, ")");
                break;
                
            case ASTREE_EXP:
                fprintf(out, "(");
                code_generate(out, ast->son[0]);
                fprintf (out, ")");
                break;
                
            case ASTREE_ADD:
                code_generate(out, ast->son[0]);
                fprintf (out, " + ");
                code_generate(out, ast->son[1]);
                break;
                
            case ASTREE_SUB:
                code_generate(out, ast->son[0]);
                fprintf (out, " - ");
                code_generate(out, ast->son[1]);
                break;
                
            case ASTREE_DIV:
                code_generate(out, ast->son[0]);
                fprintf (out, " / ");
                code_generate(out, ast->son[1]);
                break;
                
            case ASTREE_MUL:
                code_generate(out, ast->son[0]);
                fprintf (out, " * ");
                code_generate(out, ast->son[1]);
                break;
                
            case ASTREE_LE:
                code_generate(out, ast->son[0]);
                fprintf (out, " <= ");
                code_generate(out, ast->son[1]);
                break;
                
            case ASTREE_GE:
                code_generate(out, ast->son[0]);
                fprintf (out, " >= ");
                code_generate(out, ast->son[1]);
                break;
                
            case ASTREE_EQ:
                code_generate(out, ast->son[0]);
                fprintf (out, " == ");
                code_generate(out, ast->son[1]);
                break;
                
            case ASTREE_NE:
                code_generate(out, ast->son[0]);
                fprintf (out, " != ");
                code_generate(out, ast->son[1]);
                break;
                
            case ASTREE_AND:
                code_generate(out, ast->son[0]);
                fprintf (out, " && ");
                code_generate(out, ast->son[1]);
                break;
                
            case ASTREE_OR:
                code_generate(out, ast->son[0]);
                fprintf (out, " || ");
                code_generate(out, ast->son[1]);
                break;
                
            case ASTREE_GREATER:
                code_generate(out, ast->son[0]);
                fprintf (out, " > ");
                code_generate(out, ast->son[1]);
                break;
                
            case ASTREE_LESS:
                code_generate(out, ast->son[0]);
                fprintf (out, " < ");
                code_generate(out, ast->son[1]);
                break;
                
                
            default:
                break;
        }
    }
}
