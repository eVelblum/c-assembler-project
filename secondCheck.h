#ifndef SECOND_CHECK_H
#define SECOND_CHECK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>	
#include "dataCode.h"
#include "symbols.h"
#define MAX 81
#define BINARY 10

typedef struct Print {
	char binary[BINARY]; /*the binary code*/
	unsigned counter ;/*counter ic or dc*/
	struct Print *next; /*pointer to next printCode*/
}Print;
Print *createPrintNode();/*create a new node for print table*/
void free_list_prints(Print * list);/*free all print table*/
void addToPrintList(Print *,Print **);/* Adds a new code print to the print table */ 
void updateAllDataValue(Symbol** ,int );/*update the data memory to the end*/
int ifSymbolInLine(Symbol ** ,char []);/*check if there is symbol in the line after we know all the symbols in file*/
char *codingDataStringOrStructToBinary(int ,int ,int* ); /*convert data/string/struct number to binary*/
 char *codingDecimalToBinary(int ,int ,int* );/*convert decimal number to binary*/
char *negativeData(int ); /* find the Complementary to 2 for data negative number */
char *negative(int) ;/* find the Complementary to 2 for our negative number */
unsigned binaryTodecimal (char num[]);/*convert binary array to decimal number*/
void toBase32(unsigned n,char* temp);/*convert to base 32*/
void printFile(FILE *fpw ,Print **,Print **); /* insert the line to our output file */
char* printfunct(char are[], char [], char [],char []); /* Placement the parts of the line to one. */
int printStructOrData(FILE *,char[],char [],int ,int ,char[],Symbol** ,int , int*,Print** ) ;/* print to output file the addrres of the symbol */
char* registerNumberToBinary(int); /*Converts the decimal number to a binary number*/
void printRegisterSource(FILE *,int  , int,Print**);/*print Source register*/
void printRegisterDestination(FILE *,int  , int ,Print**);/*print Desination register*/
void printBothRegister(FILE *,int , int  , int,Print** );/*print 2 registers in one line */
int destinationR(char []); /* if we have destnation to our opcode */
int sourceR(char []); /* if we have source to our opcode */
int secondCheck(int , char *[],Symbol** , Code **  ,int * , int *);/*our second check*/




#endif
