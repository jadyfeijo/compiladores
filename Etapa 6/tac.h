#ifndef TAC_H
#define TAC_H

#include "hash.h"

#define TAC_SYMBOL 1
#define TAC_LABEL 2
#define TAC_MOVE 3
#define TAC_ADD 4
#define TAC_SUB 5
#define TAC_MUL 6
#define TAC_DIV 7
#define TAC_LESS 8
#define TAC_GREATER 9
#define TAC_LE 10
#define TAC_GE 11
#define TAC_EQ 12
#define TAC_NE 13
#define TAC_AND 14
#define TAC_OR 15
#define TAC_BEGINFUN 16
#define TAC_ENDFUN 17
#define TAC_IFZ 18
#define TAC_JUMP 19
#define TAC_CALL 20
#define TAC_ARG 21
#define TAC_RET 22
#define TAC_PRINT 23
#define TAC_READ 24
#define TAC_ASS 25
#define TAC_VARDEC 26
#define TAC_VECDEC 27
#define TAC_VECDEC_INIT 28
#define TAC_ASS_VEC 29
#define TAC_FUNCALL 30
#define TAC_FUNDEC_PARAM 31
#define TAC_VEC_INDEX 32
#define TAC_ASS_VEC_INDEX 33

typedef struct tac_node
{
	int type;
	HASH_NODE * res;
	HASH_NODE * op1;
	HASH_NODE * op2;
	struct tac_node * prev;
	struct tac_node * next;
}TAC;

TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2);
void tacPrintSingle(TAC* tac);
void tacPrintListPrev(TAC* tac);
TAC* tacJoin(TAC* tac1, TAC* tac2);
TAC* tacReverse(TAC* tac);
void tacPrintListNext(TAC* tac);
#endif
