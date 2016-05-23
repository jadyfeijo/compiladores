#ifndef AST_H
#define AST_H

#include "hash.h"

#define MAX_SONS 4

#define ASTREE_UNDEFINED 1
#define ASTREE_SYMBOL 2
#define ASTREE_ADD 3
#define ASTREE_MUL 4
#define ASTREE_SUB 5
#define ASTREE_DIV 6
#define ASTREE_LESS 7
#define ASTREE_GREATER 8
#define ASTREE_LE 9
#define ASTREE_GE 10 
#define ASTREE_EQ 11
#define ASTREE_NE 12 
#define ASTREE_AND 13
#define ASTREE_OR 14
#define ASTREE_ASS 15
#define ASTREE_LCMD 16
#define ASTREE_IF 17 
#define ASTREE_IFTE 18
#define ASTREE_VARDEC 19
#define ASTREE_VECDEC 20
#define ASTREE_VECDEC_INIT 21
#define ASTREE_FUNDEC_VOID 22
#define ASTREE_FUNDEC_PAR 23
#define ASTREE_TYPEINT 24
#define ASTREE_TYPEREAL 25 
#define ASTREE_TYPEBOOL 26
#define ASTREE_TYPECHAR 27
#define ASTREE_FUNCALL 28
#define ASTREE_ARR_INIT 29
#define ASTREE_PAR 30
#define ASTREE_PAR2 31
#define ASTREE_INPUT 32
#define ASTREE_RETURN 33
#define ASTREE_OUTPUT 34
#define ASTREE_WHILE 35
#define ASTREE_EXP 36
#define ASTREE_VEC 37
#define ASTREE_CALL_PAR 38
#define ASTREE_CALL_PAR2 39
#define ASTREE_OUTLIST 40
#define ASTREE_OUTLIST2 41
#define ASTREE_DEC 42
#define ASTREE_EMPTYCMD 43
#define ASTREE_BLOCK 44

typedef struct astree_node
{
	int type;
	HASH_NODE *symbol;
	struct astree_node * son[MAX_SONS];
} ASTREE;

ASTREE * astreeCreate(int type, HASH_NODE * symbol, ASTREE * son0, ASTREE * son1, ASTREE * son2, ASTREE * son3);
void astreePrint(ASTREE * node, int level);
void code_generate(FILE * out, ASTREE *node);

#endif // AST_H
