#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash.h"


/* TABLE DECLARATION */

HASH_NODE *hash_table[HASH_SIZE];

/* IMPLEMENTATION */

void hashInit(void)
{
	int i;
	
	for(i = 0; i < HASH_SIZE; i++)
	{
		hash_table[i] = 0;
	}
}

int hashAddress(char *text)
{
	int address = 1, i;
	
	for(i = 0; i< strlen(text); i++)
	{
		address = (address * text[i])%HASH_SIZE + 1;
	}

	return address - 1;
}

HASH_NODE *hashFind(char *text)
{
	int address;
	HASH_NODE *node;	

	address = hashAddress(text);
	node = hash_table[address];

	while(node != NULL)
	{
		if(strcmp(node->text, text))
			node = node->next;
		else
			return node;		
	}	
	
	return 0;
}

HASH_NODE *hashInsert(char *text, int type)
{
	HASH_NODE *new_node;
	int address = hashAddress(text);

	if((new_node = hashFind(text)) == 0)
	{
	new_node = (HASH_NODE *) calloc(1, sizeof(HASH_NODE));
	new_node->text = calloc(strlen(text)+1, sizeof(char));

	new_node->type = type;
	strcpy(new_node->text, text);
	if(type == 301) new_node->dataType = DATATYPE_INT;
	else if(type == 302) new_node->dataType = DATATYPE_REAL;
		else if(type == 303) new_node->dataType = DATATYPE_BOOL;
			else if(type == 304) new_node->dataType = DATATYPE_CHAR;
				else if(type == 305) new_node->dataType = DATATYPE_STRING;

	new_node->next = hash_table[address];
	hash_table[address] = new_node;
	return new_node;
	}
	else
		return new_node;
}
	
void hashPrint(void)
{
	int i;
	HASH_NODE *node = 0;

	for(i = 0; i < HASH_SIZE; i++)
	{
		for(node = hash_table[i]; node; node =  node->next)
		{
			printf("Table[%d] = %s | Type = %d | DataType = %d\n", i, node->text, node->type, node->dataType);
		}
	}
}	
