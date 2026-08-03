
#ifndef MACRO_FUNCTIONS_H
#define MACRO_FUNCTIONS_H
#include "header.h"
typedef struct Macros {
    char macros_name[MAX] ; /* the title of the macro*/
    char macros_sentances[MACRO_MAX_SENTANCES]; /* the sentences of the macro*/
    struct Macros *next; /* next macro on the list*/
    }Macro;

 
void free_list_macro(Macro*);/*free macro table*/
Macro *createNode(); /*create a node for macro */
int isValidMacro(char *,char **); /* check if macro's name is valid*/
int isExisted(char *,Macro*); /* check if the macro is already exist in the data*/
int isMacroOrEndmacro (char[]);/*  check if the line contains macro or endmacro or nothing,return 1 if macro ,2 if endmacro and 0 if nothing */
int readMacroInText ( int i ,char **,Macro **);/*  insert all macros in data,return 0 if it succeeded and 1 if there was an error*/
int insertMacro(Macro* ,char []);/*  insert macro's name to data */
void insertSentances(Macro*,FILE*);/*  insert macro's sentances to data */
void addNode(Macro*,Macro**); /*add node to macro's table */
int searchMacroInLine(char[],FILE* ,Macro**);/* serch if there is macro in line */
void writeMacrosToFile(int i, char **,Macro **);/*  write to new file the text and replace every macro's name with his sentances */



#endif
