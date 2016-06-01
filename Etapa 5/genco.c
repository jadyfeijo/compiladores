//
//  genco.c
//  
//
//  Created by Matheus Stefanello Luz on 5/30/16.
//
//

#include "genco.h"

TAC* generateCode(ASTREE *node) {
    int i;
    TAC* code[MAX_SONS];
    if(!node) return 0;
    
    for (i=0; i<MAX_SONS; i++) {
        if (node->son[i])
            code[i] = generateCode(node->son[i]);
        else
            code[i] = 0;
    }
    
    switch (node->type) {
        case ASTREE_DEC: return tacJoin(code[0],code[1]); break;
        case ASTREE_FUNDEC_PARAM: break;
        case ASTREE_FUNDEC_VOID: break;
        case ASTREE_VARDEC: return tacJoin(tacCreate(TAC_VARDEC,node->son[1]->symbol,0,0),tacCreate(TAC_MOVE,node->son[1]->symbol,node->son[2]->symbol,0)); break;
        case ASTREE_VECDEC: return tacJoin(code[2],tacCreate(TAC_VECDEC,node->son[1]->symbol,code[2]->res,0)); break;
        case ASTREE_VECDEC_INIT: return tacJoin(code[2],tacJoin(tacCreate(TAC_VECDEC_INIT,node->son[1]->symbol,code[2]->res,0),code[3])); break;
        case ASTREE_BLOCK: return code[0]; break;
        case ASTREE_LCMD: return tacJoin(code[0],code[1]); break;
        case ASTREE_ASS: return tacJoin(code[1], tacCreate(TAC_ASS,node->son[0]->symbol,code[1]?code[1]->res:0,0)); break;
        case ASTRE_ASS_VEC: return tacJoin(tacJoin(code[0],code[2]),tacCreate(TAC_VECMOVE,node->son[1]->symbol,code[2]->res,code[0]->res)); break;
        case ASTREE_INPUT: return tacCreate(TAC_INPUT,node->son[0]->symbol,0,0); break;
        case ASTREE_RETURN: return tacJoin(code[0],tacCreate(TAC_RETURN,code[0]->res,0,0)); break;
        case ASTREE_OUTPUT: return code[0]; break;
        case ASTREE_SYMBOL: return tacCreate(TAC_SYMBOL,node->symbol,0,0); break;
        case ASTREE_ADD: return makeBinOp(TAC_ADD, code[0], code[1]); break;
        case ASTREE_SUB: return makeBinOp(TAC_SUB, code[0], code[1]); break;
        case ASTREE_MUL: return makeBinOp(TAC_MUL, code[0], code[1]); break;
        case ASTREE_DIV: return makeBinOp(TAC_DIV, code[0], code[1]); break;
        case ASTREE_LE: return makeBinOp(TAC_LE, code[0], code[1]); break;
        case ASTREE_GE: return makeBinOp(TAC_GE, code[0], code[1]); break;
        case ASTREE_EQ: return makeBinOp(TAC_EQ, code[0], code[1]); break;
        case ASTREE_NE: return makeBinOp(TAC_NE, code[0], code[1]); break;
        case ASTREE_AND: return makeBinOp(TAC_AND, code[0], code[1]); break;
        case ASTREE_OR: return makeBinOp(TAC_OR, code[0], code[1]); break;
        case ASTREE_GREATER: return makeBinOp(TAC_GREATER, code[0], code[1]); break;
        case ASTREE_LESS: return makeBinOp(TAC_LESS, code[0], code[1]); break;
        case ASTREE_IF
        case ASTREE_IFTE
        case ASTREE_WHILE
        case 
            
        
        //case ASTREE_IF: return makeIfThen(code[0], code[1]); break;
        default: break;
    }
    
    return tacJoin(tacJoin(tacJoin(code[0],code[1]),code[2]),code[3]);
                                
                                        
}

TAC* makeBinOp(int type, TAC* code0, TAC* code1) {
    return tacJoin(tacJoin(code0,code1),tacCreate(type,makeTemp(),code0?code0->res:0,code1?code1->res:0));

}

/*TAC* makeIfThen(TAC* code0, TAC* code1) {
    TAC* newif;
	TAC* label;
    HASH_NODE* newlabel;
    
    newlabel = makeLabel();
    newif = tacCreate(TAC_IFZ,label,code[0]?code[0]->res:0,0);
}*/
