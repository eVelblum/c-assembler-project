#include "symbols.h"
#include "secondCheck.h"
void addSymbolNode(Symbol *temp , Symbol **head)
{
	Symbol* node;
	node =*head;
	if((*head)->symbol[0]=='\0')
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
void printEntries(int i, char *argv[],Symbol **head) /* Print the entries file */
{
  	FILE *fp;
  	char fname[MAX];
  	Symbol *temp ;
	char address[3];
	temp = *head;
  	strcpy(fname,argv[i]);
  	strncat(fname, ".ent", 4);
  	while(temp != NULL)
  	{   
    		if(temp->type[2] > 48)
		{
			fp = fopen(fname,"a");
			if(fp==NULL)
			{
				printf("error, cant open this file %s",fname);
				exit(1);	
			}
			toBase32(temp->value,address);  			
			fprintf(fp,"%s\t %s\n",temp->symbol, address);
			fclose(fp);
		}
		temp = temp-> next;
  	}
}
void printExternals( char fname1[],char symbol[],int value) /* Print the externals file */
{
  	FILE *fp ;
  	char fname[MAX];
  	
	char address[3];
  	strcpy(fname,fname1);
  	strncat(fname, ".ext", 4);
	fp=fopen (fname,"a");
	if(fp==NULL)
	{	
		printf("error, cant open this file %s",fname);
		exit(1);	
	}
	toBase32(value,address);  			
	fprintf(fp,"%s\t %s\n",symbol, address);
  	fclose(fp);
	
} 



void free_list_symbols(Symbol * list)
{
    	Symbol* next_node;
    	while(list != NULL)
    	{
        	next_node = list->next;
        	free(list);
        	list = next_node;
      
    	}
}

Symbol *createSymbolNode()
{
    	Symbol *temp; /* declare a node */
	temp =(Symbol*) malloc(sizeof(Symbol)); /* allocate memory using malloc() */
	memset(temp->type,'\0',TYPES);	
	if (temp==NULL)
	{
		printf("error . cannot allocate memory");
		exit(1);
     	}
    	temp->next = NULL;/* make next point to NULL*/
    	return temp;/*return the new node*/
}
