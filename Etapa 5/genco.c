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
        case ASTREE_SYMBOL: return tacCreate(TAC_SYMBOL,node->symbol,0,0); break;
        case ASTREE_ADD: return tacJoin(tacJoin(code[0],code[1]),tacCreate(TAC_ADD,makeTemp(),code[0]?code[0]->res:0,code[1]->res(0)) break;
        default: break;
    }
    
    return tacJoin(tacJoin(tacJoin(code[0],code[1]),code[2]),code[3]);
    
}