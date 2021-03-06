#ifndef HASH_H
#define HASH_H


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include "y.tab.h"

#define HASH_SIZE 997

#define SYMBOL_LIT_INT 301
#define SYMBOL_LIT_REAL 302
#define SYMBOL_LIT_BOOL 303
#define SYMBOL_LIT_CHAR 304
#define SYMBOL_LIT_STRING 305
#define SYMBOL_LIT_IDENTIFIER 306

#define SYMBOL_VAR 307
#define SYMBOL_VEC 308
#define SYMBOL_FUN 309

#define SYMBOL_LABEL 310

#define DATATYPE_ERROR       0
#define DATATYPE_INT         1
#define DATATYPE_REAL        2
#define DATATYPE_BOOL        3
#define DATATYPE_CHAR        4
#define DATATYPE_STRING		 5




typedef struct hash_node_struck
{
	int type;
	int dataType;
	char *text;
	struct hash_node_struck *next;
	
} HASH_NODE;

/* PROTOTYPES */

void hashInit(void);
int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);
void checkUndeclared(void);
HASH_NODE *makeTemp(int type);
HASH_NODE *makeLabel(void);

#endif //HASH_H
