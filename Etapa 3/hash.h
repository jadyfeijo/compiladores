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


typedef struct hash_node_struck
{
	int type;
	char *text;
	struct hash_node_struck *next;
	
} HASH_NODE;

/* PROTOTYPES */

void hashInit(void);
int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);

#endif //HASH_H
