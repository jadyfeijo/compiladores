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
		//case ASTREE_FUNDEC_PAR: return tacJoin(code[0], tacCreate(TAC_MOVE, 
        case ASTREE_SYMBOL: return tacCreate(TAC_SYMBOL,node->symbol,0,0); break;
        case ASTREE_ADD: return makeBinOp(TAC_ADD, code[0], code[1]); break;
		case ASTREE_SUB: return makeBinOp(TAC_SUB, code[0], code[1]); break;
		case ASTREE_MUL: return makeBinOp(TAC_MUL, code[0], code[1]); break;
		case ASTREE_DIV: return makeBinOp(TAC_DIV, code[0], code[1]); break;
		case ASTREE_ASS: return tacJoin(code[1], tacCreate(TAC_ASS,node->son[0]->symbol,code[1]?code[1]->res:0,0)); break;
		case ASTREE_IF: return makeIfThen(code[0], code[1]); break;
        default: break;
    }
    
    return tacJoin(tacJoin(tacJoin(code[0],code[1]),code[2]),code[3]);
                                
                                        
}

TAC* makeBinOp(int type, TAC* code0, TAC* code1) {
    return tacJoin(tacJoin(code0,code1),tacCreate(type,makeTemp(),code0?code0->res:0,code1?code1->res:0));

}

TAC* makeIfThen(TAC* code0, TAC* code1) {
    TAC* newif;
    HASH_NODE* newlabel;

    newlabel = makeLabel();
    return newif = tacCreate(TAC_IFZ,newlabel,code0?code0->res:0,0);
}
