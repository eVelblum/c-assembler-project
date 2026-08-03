#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_NAME 31
#define TYPES 3
typedef struct Symbol {
	char symbol [MAX_NAME];   /* the name of the symbol*/
	char type [TYPES] ; /* type of symbol -  0-data/1-extern/2-entry*/
	int value;	/* how much memory needs */
    	struct Symbol *next; /* next symbol on the list*/
    }Symbol;

void addSymbolNode(Symbol * , Symbol **);/*adding the new symbol node to data*/
void printEntries(int i, char *[],Symbol **); /* Print the entries file */
void printExternals(char[], char [],int) ;/* Print the externals file */
void addToTable(Symbol ** , char [] , int );  /* Adds a new element to the symbol table */ 
void free_list_symbols(Symbol * ); /*free all symbols table*/
Symbol *createSymbolNode(); /*create a new node for symbols table*/




#endif
