#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

#define HASH_SIZE 997

#define SYMBOL_LIT_INT 1
#define SYMBOL_LIT_REAL 2
#define SYMBOL_LIT_BOOL 3
#define SYMBOL_LIT_CHAR 4
#define SYMBOL_LIT_STRING 5
#define SYMBOL_LIT_IDENTIFIER 6


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
