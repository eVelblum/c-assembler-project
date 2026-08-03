
#include "macroFunction.h"

void free_list_macro(Macro * list)
{
    Macro* next_node;
    while(list != NULL)
    {
        next_node = list->next;
        free(list);
        list = next_node;
      
    }
}

Macro *createNode()
	{
    	Macro *temp; /* declare a node */
	temp =(Macro*) malloc(sizeof(Macro)); /* allocate memory using malloc() */
	memset(temp->macros_name , '\0',MAX);
	memset(temp->macros_sentances, '\0', MACRO_MAX_SENTANCES);
	if (temp==NULL)
	{
		printf("error . cannot allocate memory");
		exit(1);
     	}
    temp->next = NULL;/* make next point to NULL*/
    return temp;/*return the new node*/
}
   /* check if macro's name is valid, return 1 if valid and 0 if invalid */
int isValidMacro(char *macro_name ,char **macros_invalid_table)
{

    	char **p;
    	p=macros_invalid_table;
    	while(*p!=0)
        {

        	if(strcmp(macro_name,*p)==0)
           		 return 0;
        	p++;
        }
        return 1 ;
}
/*  check if the macro is already exist in the data  , return 1 if it does and 0 if not */
int isExisted(char* nameOfMacro, Macro* head){
	Macro *p;
	p = head;
	while(p != NULL)
	{
		if(strcmp(p->macros_name,nameOfMacro)==0)
		{
			return 1;
		}
			p = p->next;
	}
    	return 0;
}
/*  check if the line contains macro or endmacro or nothing,return 1 if macro ,2 if endmacro and 0 if nothing */
int isMacroOrEndmacro (char line[])
{	
	int lineIndex =0;
	int macroIndex=0;
	char macro[MAX];
	memset(macro, '\0',MAX);
	while(isspace(line[lineIndex]))
		lineIndex++;
	
	while(!isspace(line[lineIndex]) && line[lineIndex] != '\n' )
	{
		macro[macroIndex] = line[lineIndex];
		macroIndex++;
		lineIndex++;
	}
	if(!strcmp(macro,"macro"))
	{
		return 1;	
	}
	if(!strcmp(macro,"endmacro"))
	{
		return 2;	
	}
	return 0;
}
/*  insert all macros in data,return 0 if it succeeded and 1 if there was an error*/
int readMacroInText ( int i ,char *argv[],Macro **head)
{	
	FILE *fpR;
	char fname[MAX_NAME];
	char line[MAX];
	memset(line , '\0',MAX);
	strcpy(fname,argv[i]);
	strncat(fname,".as", 3); 
	fpR = fopen(fname,"r");
	if(fpR==NULL)
		{	
			printf("error , the file : %s is nost open ",fname); 
			return 1;
		}

	while(fgets(line , MAX , fpR))
	{
		
		if(isMacroOrEndmacro(line)==1)
		{
			Macro *temp = createNode();
			if(insertMacro(temp,line))
			{
				if(isExisted(temp->macros_name,*head))
				{
					printf("error: existed macro's name ");
					return 1;
				}
			insertSentances(temp,fpR);
			addNode(temp,head);
			}
			
		}
		
	}

	fclose(fpR);
	return 0;	
}

/*  insert macro's name to data */
int insertMacro(Macro *temp,char line[])
{	
	char macro[MAX];
	char *macros_invalid_table[]={"mov","cmp","add","sub","lea","not","clr","inc","dec","jmp","bne","get","prn","jst",".string",".data",".entry",".struct",".extern","r0","r1","r2","r3","r4","r5","r6","r7",'\0'};
  	
	int lineIndex =0;
	int macroIndex=0;
	
	memset(macro, '\0',MAX);
	while(isspace(line[lineIndex]))
		lineIndex++;
	while(!isspace(line[lineIndex]))
		lineIndex++;
	while(isspace(line[lineIndex]))
		lineIndex++;
	while(!isspace(line[lineIndex]) && line[lineIndex] != '\n' )
	{
		macro[macroIndex] = line[lineIndex];
		macroIndex++;
		lineIndex++;
	}
	if(isValidMacro(macro , macros_invalid_table)==1)
		strcpy(temp->macros_name,macro);
	else
	{
		printf("error: invalid macro's name.");
		return 0 ;
		
	}
	
	return 1;
	
}
/*  insert macro's sentances to data */
void insertSentances(Macro *temp,FILE *fpR)
{
	char line[MAX];
	char sentance[MACRO_MAX_SENTANCES];
	memset(line,'\0',MAX);
	memset(sentance, '\0',MACRO_MAX_SENTANCES);
	fgets(line,MAX,fpR);
	while(isMacroOrEndmacro(line)!=2)
	{
		strcat(sentance,line);
		fgets(line,MAX,fpR);	
	}
	strcpy(temp->macros_sentances , sentance);
}	
void addNode(Macro *temp , Macro **head)
{
	Macro* node;
	node =*head;
	if((*head)->macros_name[0]=='\0')
	{
		
		*head =temp;
	}			
	else
	{

		while(node->next!=NULL)
		{
			node=node->next ;
		}
		node->next=temp;
	
	}
	

}	
/* serch if there is macro in line */
int searchMacroInLine(char line[],FILE *fpW,Macro **head)
{
	int lineIndex =0,macroIndex=0;
	Macro *temp;
	char macro[MAX];
	memset(macro,'\0', MAX);
	temp=*head;
	
	while(isspace(line[lineIndex]))
		lineIndex++;
	while(!isspace(line[lineIndex]) && line[lineIndex] != '\n' )
	{
		macro[macroIndex] = line[lineIndex];
		macroIndex++;
		lineIndex++;
	}
	while(temp!=NULL)
	{
		
		if(!strcmp(temp->macros_name,macro))
		{
			
			fprintf(fpW,"%s",temp->macros_sentances);
			return 1;
		}
		temp=temp->next;
	}
	return 0;

}
/*  write to new file the text and replace every macro's name with his sentances */
void writeMacrosToFile(int i, char *argv[],Macro **head)
{
	int macroFlag =0;
	FILE *fpR;
	FILE *fpW;
	char line[MAX];
	char fpRName[MAX];
	char fpWName[MAX];
	memset(line , '\0',MAX);
	strcpy(fpRName,argv[i]);
	strncat(fpRName,".as",3);
	strcpy(fpWName,argv[i]);
	strncat(fpWName,".am",3);
	
	fpR = fopen(fpRName,"r");
	fpW = fopen(fpWName,"w");
	if(fpR==NULL)
	{	
		printf("error , the file : %s is not open! ",fpRName); 
	}
	while(fgets(line,MAX,fpR))
	{
	
		if(!macroFlag)
		{	
			
			if(!searchMacroInLine(line,fpW,head))
			{
				if(isMacroOrEndmacro(line)==0)
				{
					
					fprintf(fpW,"%s",line);
				}
				else
				{
					macroFlag=1;	
				}
			
			}
		}
		else 
		{
			if(isMacroOrEndmacro(line)==2)
				macroFlag=0;

		}

	}
	fclose(fpR);	
	fclose(fpW);
}







