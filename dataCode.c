#include "dataCode.h"
void addCodeNode(Code *temp , Code **head)
{
	Code* node;
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



char* funct(char op[]) /*Returns the funct number of the instructions as a binary number*/
{
	char *p;
	char opcode[5];
	memset(opcode , '\0' , 5);
	if(!strcmp(op, "mov"))
		strcpy(opcode,"0000\0");
	else
	if(!strcmp(op, "cmp"))
		strcpy(opcode,"0001");
	else
	if(!strcmp(op, "add"))
		strcpy(opcode,"0010");
	else
	if(!strcmp(op, "sub"))
		strcpy(opcode,"0011");
	else
	if(!strcmp(op, "not"))
		strcpy(opcode,"0100");
	else
	if(!strcmp(op, "clr"))
		strcpy(opcode,"0101");
	else
	if(!strcmp(op, "lea"))
		strcpy(opcode,"0110");
	else
	if(!strcmp(op, "inc"))
		strcpy(opcode,"0111");
	else
	if(!strcmp(op, "dec"))
		strcpy(opcode,"1000");
	else
	if(!strcmp(op, "jmp"))
		strcpy(opcode,"1001");
	else
	if(!strcmp(op, "bne"))
		strcpy(opcode,"1010");
	else
	if(!strcmp(op, "get"))
		strcpy(opcode,"1011");
	else
	if(!strcmp(op, "prn"))
		strcpy(opcode,"1100");
	else
	if(!strcmp(op, "jsr"))
		strcpy(opcode,"1101");
	else
	if(!strcmp(op, "rts"))
		strcpy(opcode,"1110");
	else
	if(!strcmp(op, "hlt"))
		strcpy(opcode,"1111");
	
	p = opcode;
	return p;
}


int opcode(char op[]) /*Returns the opcode type in decimal base*/
{
  	if(!strcmp(op, "mov"))
    		return 0;
  	if(!strcmp(op, "cmp"))
    		return 1;
  	if(!strcmp(op, "add"))
    		return 2;
  	if(!strcmp(op, "sub"))
    		return 3;
  	if(!strcmp(op, "not"))
    		return 4;
 	 if(!strcmp(op, "clr"))
    		return 5;
  	if(!strcmp(op, "lea"))
    		return 6;
  	if(!strcmp(op, "inc"))
    		return 7;
  	if(!strcmp(op, "dec"))
    		return 8;
  	if(!strcmp(op, "jmp"))
    		return 9;
  	if(!strcmp(op, "bne"))
    		return 10;
  	if(!strcmp(op, "get"))
    		return 11;
  	if(!strcmp(op, "prn"))
    		return 12;
  	if(!strcmp(op, "jsr"))
    		return 13;
  	if(!strcmp(op, "rts"))
    		return 14;
 	if(!strcmp(op, "hlt"))
    	return 15;
 
	return -1;
}




void free_list_codes(Code* list)
{
    	Code* next_node;
    	while(list != NULL)
    	{
        	next_node = list->next;
        	free(list);
		list = next_node;
    	}
}

Code *createCodeNode()
{
    	Code *temp; /* declare a node */
	temp =(Code*) malloc(sizeof(Code)); 
	memset(temp->symbol,'\0',MAX_NAME);
	memset(temp->are,'\0', ARE);
	memset(temp->sAddress,'\0', SOURCE_ADDRESS);
	memset(temp->dAddress,'\0', DESTINATION_ADDRESS);
	memset(temp->opcode,'\0',OPCODE);
	
	temp-> destinationRegisterNumber=0;	
	temp-> sourceRegisterNumber=0;
	temp-> sourceStructNumber=0;
	temp-> destinationStructNumber=0;
	memset(temp->sourceSymbol, '\0' , MAX_NAME);
	memset(temp->destinationSymbol , '\0',MAX_NAME);
	if (temp==NULL)
	{
		printf("error . cannot allocate memory");
		exit(1);
     	}
    	temp->next = NULL;/* make next point to NULL*/
    	return temp;/*return the new node*/
}



