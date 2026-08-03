#ifndef FIRST_CHECK_H
#define FIRST_CHECK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "macroFunction.h"
#include "dataCode.h"
#include "symbols.h"

int isNotSpaceLine(FILE *fpr ,char line[]);/*check if its not space line*/
void externSymbol(Symbol* , char [],int ,int *); /*Inserts the label in the extern prompt to the symbol table*/
int entryOrExtern(char []); /*Checks whether it is extern prompt or entry prompt*/
int dcStruct(char [] , int ); /*Summarize the number of values in the strcut prompt*/
int dcData(char [] , int ); /*Summarize the number of values in the data prompt*/
int dcString(char [] , int ); /*Summarize the number of chars in the string prompt*/
int checkOpcode(char [], int  ,Code*  ,int ,int* ); /* Return the index of the opcode, and update the funct in the decode table */
int dataOrStringOrStruct(char [] , int ); /*Checks whether this is a data, string or struct, if so returns the space to be allocated for them*/
int notExistSymbol(Symbol**  , char []); /*Checks if the symbol already exists*/
int isValidSymbol(char []);/*check id the symbol name is vaild*/
int isSymbol(char lne[] , Symbol* ,Symbol** ,Code*  , int ,int* ); /*Checks whether a new symbol is being declared*/
void codingOpcode(Code* , char [],int   , int* ); /*Checks the type of opcode using the function we wrote above and then updates the relevant bit in the row*/
int destinationOperand(char [], int  ,Code*  ,int* , int ); /*Checks which address is in the destination*/
int sourceOperand(char [], int  ,Code* ,int*  , int  ); /*Checks which address is in the source*/
int instruction(char [],int ,Code* ,int* ,int ); /* update the address and registers acordding the opcode */
int firstCheck(int i, char *[],Symbol** , Code** , int *, int *); /*the first check of our program*/
	
#endif


