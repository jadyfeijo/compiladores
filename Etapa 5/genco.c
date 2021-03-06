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
    HASH_NODE* label;
    if(!node) return 0;
    
    for (i=0; i<MAX_SONS; i++) {
        if (node->son[i])
            code[i] = generateCode(node->son[i]);
        else
            code[i] = 0;
    }
    
    switch (node->type) {
        case ASTREE_DEC: return tacJoin(code[0],code[1]); break;
        case ASTREE_FUNDEC_PAR: return tacJoin(tacCreate(TAC_BEGINFUN, node->son[1]->symbol,0,0),tacJoin(code[2],tacJoin(code[3],tacCreate(TAC_ENDFUN,node->son[1]->symbol,0,0)))); break;
        case ASTREE_FUNDEC_VOID: return tacJoin(tacCreate(TAC_BEGINFUN,node->son[1]->symbol,0,0),tacJoin(code[2],tacCreate(TAC_ENDFUN,node->son[1]->symbol,0,0))); break;
        case ASTREE_VARDEC: return tacJoin(tacCreate(TAC_VARDEC,node->son[1]->symbol,0,0),tacCreate(TAC_MOVE,node->son[1]->symbol,node->son[2]->symbol,0)); break;
        case ASTREE_VECDEC: return tacJoin(code[2],tacCreate(TAC_VECDEC,node->son[1]->symbol,code[2]->res,0)); break;
        case ASTREE_VECDEC_INIT: return tacJoin(code[2],tacJoin(tacCreate(TAC_VECDEC_INIT,node->son[1]->symbol,code[2]->res,0),code[3])); break;
		//case ASTREE_ARR_INIT: return tacJoin(code[1],tacCreate(TAC_VECMOVE,node->son[0]->symbol,0,0)); break;
        case ASTREE_BLOCK: return code[0]; break;
        case ASTREE_LCMD: return tacJoin(code[0],code[1]); break;
        case ASTREE_ASS: return tacJoin(code[1], tacCreate(TAC_ASS,node->son[0]->symbol,code[1]?code[1]->res:0,0)); break;

        //case ASTREE_ASS_VEC: return tacJoin(tacJoin(code[0],code[2]),tacCreate(TAC_ASS_VEC,tacCreate(TAC_ASS_VEC_INDEX,makeTemp(),node->son[0]->symbol,node->son[1]->symbol),node->son[2]->symbol,0)); break;
		case ASTREE_ASS_VEC: return tacJoin(tacJoin(code[0],code[2]),tacCreate(TAC_ASS_VEC,node->son[1]->symbol,code[2]->res,code[0]->res)); break;
		//case ASTREE_ASS_VEC: return tacJoin(tacJoin(code[0],code[2]),tacJoin(tacCreate(TAC_ASS_VEC_INDEX,makeTemp(),node->son[0]->symbol,node->son[1]->symbol),tacCreate(TAC_ASS_VEC,makeTemp(),0,code[2]->res))); break;

		//case ASTREE_ASS_VEC: return tacJoin(tacJoin(code[0],code[2]),tacJoin(code[2], tacCreate(TAC_ASS_VEC_INDEX,makeTemp(),node->son[1]->symbol,code[0]->res))); break;

        case ASTREE_INPUT: return tacCreate(TAC_READ,node->son[0]->symbol,0,0); break;
        case ASTREE_RETURN: return tacJoin(code[0],tacCreate(TAC_RET,code[0]->res,0,0)); break;
        case ASTREE_OUTPUT: return code[0]; break;
        case ASTREE_SYMBOL: return tacCreate(TAC_SYMBOL,node->symbol,0,0); break;
        case ASTREE_EXP: return code[0]; break;
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
		case ASTREE_IF: return makeIfThen(code[0], code[1]); break;
        case ASTREE_IFTE: return makeIfThenElse(code[0], code[1], code[2]); break;
        case ASTREE_WHILE: return makeWhile(code[0],code[1]); break;
         //
        case ASTREE_FUNCALL: label = makeLabel();  return tacJoin(code[1],tacJoin(tacJoin(tacCreate(TAC_FUNCALL,node->son[0]->symbol,label,0),tacJoin(tacCreate(TAC_JUMP,node->son[0]->symbol,0,0),tacCreate(TAC_LABEL,label,0,0))),tacCreate(TAC_PUSHSTACK,makeTemp(),0,0))); // */

															/* return tacJoin(
															code[1],
															tacJoin(
																//tacJoin(
																	tacCreate(TAC_FUNCALL,node->son[0]->symbol,label,0),
																	tacJoin(
																		tacCreate(TAC_JUMP,node->son[0]->symbol,0,0),
																		tacCreate(TAC_LABEL,label,0,0)
																			)
																		)//,
																//tacCreate(TAC_FUNCALL,makeTemp(),0,0)
																	);
																//); */
															 break;

        case ASTREE_CALL_PAR: return tacJoin(tacJoin(code[0],tacCreate(TAC_POPSTACK,code[0]->res,0,0)),code[1]); break;
        case ASTREE_CALL_PAR2: return code[0]; break;
        case ASTREE_PAR: return tacJoin(tacCreate(TAC_FUNDEC_PARAM,node->son[1]->symbol,0,0),code[2]); break;
        case ASTREE_PAR2: return code[0]; break;
        case ASTREE_OUTLIST: return tacJoin(tacJoin(code[0],tacCreate(TAC_PRINT,code[0]->res,0,0)),code[1]);break;
        case ASTREE_OUTLIST2: return code[0];
        case ASTREE_ID: return tacCreate(TAC_SYMBOL,node->son[0]->symbol,0,0);
		case ASTREE_VEC: return tacJoin(code[1],tacCreate(TAC_VEC_INDEX,makeTemp(),node->son[0]->symbol,code[1]->res)); break;//case ASTREE_VEC: return tacJoin(code[0],code[1]); break;
         // altas chances de dar merda no que ta entre comentarios, mesmo vale pro makeIfThen embaixo, fiz isso quase dormindo
            
         //
        default: break;
    }
    
    return tacJoin(tacJoin(tacJoin(code[0],code[1]),code[2]),code[3]);
                                
                                        
}

TAC* makeBinOp(int type, TAC* code0, TAC* code1) {
    return tacJoin(tacJoin(code0,code1),tacCreate(type,makeTemp(),code0?code0->res:0,code1?code1->res:0));

}

//
TAC* makeIfThen(TAC* code0, TAC* code1) {
    TAC* newif;
    HASH_NODE* newlabel;
    HASH_NODE* newlabel2;

    newlabel = makeLabel();
    newlabel2 = makeLabel();
    return newif = tacJoin(code0,tacJoin(tacJoin(tacCreate(TAC_IFZ,code0->res,newlabel,newlabel2),tacCreate(TAC_LABEL,newlabel,0,0)),tacJoin(code1,tacCreate(TAC_LABEL,newlabel2,0,0))));
}
//
TAC* makeIfThenElse(TAC* code0, TAC* code1, TAC* code2) {
    TAC* newifelse;
    HASH_NODE* newlabel;
    HASH_NODE* newlabel2;
    
    newlabel = makeLabel();
    newlabel2 = makeLabel();
    return newifelse = tacJoin(code0,tacJoin(tacJoin(tacCreate(TAC_IFZ,code0->res,newlabel,newlabel2),tacCreate(TAC_LABEL,newlabel,0,0)),tacJoin(code1,tacJoin(tacCreate(TAC_LABEL,newlabel2,0,0),code2))));
}

TAC* makeWhile(TAC* code0,TAC* code1) {
    TAC* newwhile;
    HASH_NODE* newlabel;
    HASH_NODE* newlabel2;
    HASH_NODE* newlabel3;

    newlabel = makeLabel();
    newlabel2 = makeLabel();
    newlabel3 = makeLabel(); // label pra indicar o if ( diferença do while pros ifs)

    return newwhile = tacJoin (tacCreate(TAC_LABEL,newlabel3,0,0),tacJoin(code0,tacJoin(tacCreate(TAC_IFZ,code0->res,newlabel,newlabel2),tacJoin(tacCreate(TAC_LABEL,newlabel,0,0),tacJoin(code1,tacJoin(tacCreate(TAC_JUMP, newlabel3,0,0),tacCreate(TAC_LABEL, newlabel2,0,0)))))));
}

