//
//  genco.h
//  
//
//  Created by Matheus Stefanello Luz on 5/30/16.
//
//

//#ifndef genco_h
//#define genco_h

#include <stdio.h>
#include "ast.h"
#include "tac.h"

TAC* generateCode(ASTREE* node);
TAC* makeBinOp(int type, TAC* code0, TAC* code1);
TAC* makeIfThen(TAC* code0, TAC* code1);

//#endif /* genco_h */
