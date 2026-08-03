#ifndef DATA_CODE_H
#define DATA_CODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_NAME 31
#define ARE 3
#define SOURCE_ADDRESS 3
#define DESTINATION_ADDRESS 3
#define OPCODE 5
#define REGISTER_NAME 4
typedef struct Code {
	char symbol[MAX_NAME];
	char are[ARE];/* A,R,E type */
	char sAddress [SOURCE_ADDRESS]; /* source address */
	char dAddress [DESTINATION_ADDRESS]; /* destination address */
	char opcode[OPCODE]; /* opcode type */
	char sourceSymbol [MAX_NAME]; /* source symbol */
    	char destinationSymbol [MAX_NAME];/* destination symbol */
	int destinationRegisterNumber;/* destination register name */
	int sourceRegisterNumber;/* source register name */
	int sourceStructNumber; /* source struct field */
	int destinationStructNumber;/* destination struct field */
	struct Code *next; /*pointer to the next code */
    }Code;

void addCodeNode(Code * , Code **);/*adding the new code node to data*/
char* funct(char []);/*Returns the funct number of the instructions as a binary number*/
int opcode(char []) ;/*Returns the opcode type in decimal base*/
void free_list_codes(Code* ); /*free all list*/
Code *createCodeNode();/*create a newe node for Code*/

#endif
