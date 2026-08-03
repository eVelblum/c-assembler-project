#include "firstCheck.h"

int isNotSpaceLine(FILE *fpr ,char line[])
{
	int index=0;
	while(isspace(line[index]))
	{
		if(line[index] == '\n')
			return 0;		
		index++;
	}
	return 1;
}


void externSymbol(Symbol* temp, char line[],int lineCounter,int *errorFlag) /*Inserts the label in the extern prompt to the symbol table*/
{
	
	char symbolName[MAX_NAME];
	int index = 0 , symbolIndex = 0;
	memset(symbolName, '\0' , MAX_NAME);
	while(isspace(line[index]))
	      index++;
	while (!isspace(line[index]))
	      index++;
	while(isspace(line[index]))
	{
		if (line[index] == '\n' )
	        {
			printf("extern defination error line %d",lineCounter);	
			*errorFlag =1;
		}
		index++;
	}
	while (!isspace(line[index]) && line[index] != '\n')
	{
		symbolName[symbolIndex] = line[index];
		symbolIndex++;
	     	index++;
	}
	strcpy(temp->symbol,symbolName);
	temp ->value = 0;
	temp ->type[3] = 49;/*.extern flag*/
}

int entryOrExtern(char line[]) /*Checks whether it is extern prompt or entry prompt*/
{
  	int typeIndex = 0, index = 0 ;
  	char type[MAX_NAME];
  	if(line[index] == '\n')
     	return 0;
  	memset(type, '\0' , MAX_NAME);
  	while(isspace(line[index]))
      		index++;
  	while (!isspace(line[index]) && line[index] != '\n')
      	{
      		type[typeIndex] = line[index];
      		typeIndex++;
      		index++;
      	}
   	if(!strcmp(".entry",type))
       		return 2;
    	if(!strcmp(".extern",type))
        	return 1;
    	return 0;
  
}
int dcStruct(char line[] , int index) /*Summarize the number of values in the strcut prompt*/
{
  	int dccounter = 0;
	while(isspace(line[index]))
    		index++;
	if(line[index] ==43 || line[index]==45)
		index++;
	if(line[index] > 47 && line[index] < 58)
	{
		dccounter++;
		index++;
	}	
	while(line[index] > 47 && line[index] < 58)
		index++;
	while(isspace(line[index]))
    		index++;
	if (line[index] == ',')
		index++;
	while(isspace(line[index]))
    		index++;
  	if (line[index] == '"')
  	{
    		index++;
    		while (line[index] != '"' && line[index] != '\n' )
    		{
      			index++;
      			dccounter++;
    		}
  	}
  	return dccounter + 1;
  
}

int dcData(char line[] , int index) /*Summarize the number of values in the data prompt*/
{
  	int dccounter = 1;
  	while (line[index] != '\0' && line[index] != '\n')
  	{
      		if(line[index] == ',')
        		dccounter++;
     		index++;
  	}
  	return dccounter ;
}
int dcString(char line[] , int index) /*Summarize the number of chars in the string prompt*/
{
  	int dccounter = 0;
 	while(isspace(line[index]))
    		index++;
  	if (line[index] == '"')
  	{
    		index++;
    		while (line[index] != '"' && line[index] != '\n' )
    		{
      			index++;
      			dccounter++;
    		}
  	}
  	return dccounter + 1;
  
}
int checkOpcode(char line[], int index ,Code* codeTemp,int lineCounter,int* errorFlag ) /* Return the index of the opcode, and update the funct in the decode table */
{
  	int opcodeIndex = 0;
  	char opcodeName[MAX_NAME];
  	memset(opcodeName, '\0' , MAX_NAME);
   	while(isspace(line[index]))
      		index++;
   	while(!isspace(line[index]))
   	{
      		opcodeName[opcodeIndex] = line[index];
      		opcodeIndex++;
      		index++;
  	 }
   	codingOpcode(codeTemp,opcodeName,lineCounter,errorFlag);
  	return index;
}
int dataOrStringOrStruct(char line[] , int index) /*Checks whether this is a data, string or struct, if so returns the space to be allocated for them*/
{
	int typeIndex = 0;
	char type[MAX_NAME];
	if(line[index] == '\n')
		return 0;
	memset(type, '\0' , MAX_NAME);
	while(isspace(line[index]))
      		index++;
 	while (!isspace(line[index]) && line[index] != '\n')
     	{
      		type[typeIndex] = line[index];
     	 	typeIndex++;
      		index++;
      	}
    	if(!strcmp(".data",type))
       	 	return(dcData(line , index));
    	if (!strcmp(".string",type))
        	return(dcString(line , index));
 	if (!strcmp(".struct",type))
        	return(dcStruct(line , index));
    	return 0;
  
}

int notExistSymbol(Symbol** head , char symbolName[]) /*Checks if the symbol already exists*/
{
	Symbol *temp = NULL;
	temp = *head;
	while (temp != NULL)  /*Run on all the symbols we have already found*/
  	{ 
    		if (!strcmp(temp->symbol , symbolName))
    		{
     			return 0;
    		}
    		temp = temp->next;
  	}
 	return 1;
}
int isValidSymbol(char name[])/*check if the symbol name is vaild*/
{	
	int len;
	char **t;
	char *symbols_invalid_table[]=	{"mov","cmp","add","sub","lea","not","clr","inc","dec","jmp","bne","get","prn","jst",".string",".data",".entry",".struct",".extern","r0","r1","r2","r3","r4","r5","r6","r7",'\0'};
	len=strlen(name);
	if(len>30)
		return 0;
	t=symbols_invalid_table;
   	while(*t!=0)
        {

		if(strcmp(name,*t)==0)
		    return 0;
		t++;
        }
	return 1;
}

int isSymbol(char line[] , Symbol* temp,Symbol** head,Code* dataHead , int lineCounter,int* errorFlag) /*Checks whether a new symbol is being declared*/
{
	int index = 0 , symbolIndex = 0;
	char symbolName[MAX_NAME];
	memset(symbolName, '\0' , MAX_NAME);
	memset(temp->symbol , '\0',MAX_NAME);
  	if(line[index] == '\n' || line[index]==';')
   		return 0;
 	while(isspace(line[index]))
   		index++;
	while (!isspace(line[index]) && line[index] != '\n'  && line[index] != ':')
	{
		
		symbolName[symbolIndex] = line[index];
		symbolIndex++;
		index++;
	
  	}
	if(line[index] == ':')	
	{
		
		if(isValidSymbol(symbolName))
		{
			if (notExistSymbol(head , symbolName))
			{	
				
				{
					strcpy(temp->symbol,symbolName);
					
					
					/*temp->value = dataOrStringOrStruct(line , index);*/
					temp->type[0]=temp->type[0]+dataOrStringOrStruct(line , index+1);
					return 1;
				}
				
				
			}
	     		else
	     		{
	       			printf("error: %s already exist, line number %d \n " , symbolName , lineCounter  );
				*errorFlag=1;
	     		}
		}
		else
		{
	       		printf("error: %s is not valid, line number %d \n " , symbolName , lineCounter  );
			*errorFlag=1;	     	
		}	
	
   	}
	
  return 0;
  
}



void codingOpcode(Code* codeTemp, char theopcode[],int  lineCounter , int* errorFlag) /*Checks the type of opcode using the function we wrote above and then updates the relevant bit in the row*/
{
	 
	int index = opcode(theopcode);
	if (index == -1)
	{
		printf("error. the function %s is not valid. in line %d\n",theopcode , lineCounter);
		*errorFlag=1;
	}
	strcpy(codeTemp->opcode, funct(theopcode));

}


int destinationOperand(char line[], int index ,Code* codeTemp ,int* errorFlag, int lineCounter) /*Checks which address is in the destination*/
{	
	char t[1];
	char num[MAX_NAME],symbol[MAX_NAME];
	int numberIndex = 0, i,symbolIndex=0;
	memset(num, '\0' , MAX_NAME);
	memset(symbol, '\0' , MAX_NAME);	
	while(isspace(line[index]))
		index++;
	if(!strcmp(codeTemp->opcode,"1111") && line[index] =='\n')/*rts function*/
	{
		printf("invalid operator type in line %d\n",lineCounter);
		*errorFlag =1;	
	}
	else
	if(line[index] == '#') /* Immediate address */
	{ 
		if(!strcmp(codeTemp->opcode,"0010") || !strcmp(codeTemp->opcode,"1100"))/*cmp,prn operators*/
		{
			strcpy(codeTemp->dAddress,"00");
			while(!isspace(line[index]))
			   	index++;
			return index;
		}
		else /*if cmp or prn gets # as destination operand*/
		{
			printf("invalid operator type in line %d \n",lineCounter);
			*errorFlag =1;	
		}
				
	}
	else
	if(line[index] == 'r') /*Direct register address*/
	{
		index++;
		while (line[index] > 47 && line[index] < 58)
		{
		  	num[numberIndex] = line[index];
		  	index++;
		  	numberIndex++;
		}
		i = atoi(num);
		if (i < 8)
		{
			
			/*codeTemp->next =temp;*/
			strcpy(codeTemp->dAddress,"11");
			codeTemp-> destinationRegisterNumber = i;
		}

		else
		{
			printf("error, number of register does not exist in line %d \n",lineCounter);
			*errorFlag=1;
		}
		return index;
	}       
	else if(isalpha(line[index]))
	{
		
		while(!isspace(line[index]) && line[index]!='\n' && line[index]!='.')
		{
			symbol[symbolIndex] = line[index];
		  	index++;
		  	symbolIndex++;
		}
		if(line[index]=='.')/*srtuct destination*/
		{
			index++;
			if(line[index] > 47 && line[index] < 58)
			{
				t[0]=line[index];			
				i = atoi(t);
			}
			else
			{
				printf("error, should be number field in the struct in line %d \n",lineCounter);
				*errorFlag=1;
			}
			strcpy(codeTemp->destinationSymbol,symbol);
			strcpy(codeTemp->dAddress,"10");
			codeTemp->destinationStructNumber = i;
			index++;
		}
		else /*data symbol destination*/
		{
			strcpy(codeTemp->dAddress,"01");
			strcpy(codeTemp->destinationSymbol,symbol);
		}
		
		return index;
	}
	return index;
		

}

int sourceOperand(char line[], int index ,Code* codeTemp,int* errorFlag , int lineCounter ) /*Checks which address is in the source*/
{
	char t[1];
	char num[MAX_NAME],symbol[MAX_NAME];
	int numberIndex = 0, i,symbolIndex=0;
	memset(num, '\0' , MAX_NAME);
	memset(symbol, '\0' , MAX_NAME);	
	while(isspace(line[index]))
	     	index++;	
	if(line[index] == '#') /* Immediate address */
	{
		if(!strcmp(codeTemp->opcode,"0110"))/*lea function*/
		{
			printf("invalid operator type in line %d \n",lineCounter);
			*errorFlag =1;	
				
		}
		strcpy(codeTemp->sAddress,"00");
		while(!isspace(line[index]) && line[index] != ',')
		   	index++;
		while(isspace(line[index]))
		   	index++;
		return index;
	}
	else
	if(line[index] == 'r') /*Direct register address*/
	{
		if(!strcmp(codeTemp->opcode,"0110")) /*lea function*/
		{
			printf("invalid operator type in line %d \n",lineCounter);
			*errorFlag =1;	
		}
		index++;
		while (line[index] > 47 && line[index] < 58)
		{
		  	num[numberIndex] = line[index];
		  	index++;
		  	numberIndex++;
		}
		i = atoi(num);
		if (i < 8)
		{
			strcpy(codeTemp->sAddress,"11");
			strcpy(codeTemp->sourceSymbol,"r");
			codeTemp-> sourceRegisterNumber = i;
		}

		else
		{
			printf("error, number of register does not exist in line %d\n",lineCounter);
			*errorFlag=1;
		}			
		while(isspace(line[index]))
			index++;
		return index;
	}       
	else if(isalpha(line[index]))
	{
		while(!isspace(line[index]) && line[index]!='\n'&& line[index]!='.')
		{
			symbol[symbolIndex] = line[index];
		  	index++;
		  	symbolIndex++;
		}
		
		if(line[index]=='.')/*srtuct destination*/
		{
			index++;
			if(line[index] > 47 && line[index] < 58)
			{
				t[0]=line[index];			
				i = atoi(t);
			}
			else
			{
				printf("error, should be number field in the struct in line %d \n",lineCounter);
				*errorFlag=1;
			}
			strcpy(codeTemp->sAddress,"10");
			strcpy(codeTemp->sourceSymbol,symbol);
			codeTemp-> sourceStructNumber = i;
			index++;	
		}
		else/*data symbol source*/
		{
			strcpy(codeTemp->sAddress,"01");
			strcpy(codeTemp->sourceSymbol,symbol);
		}	
		return index;
	}
	return index;
		
}

int instruction(char line[],int index,Code* codeTemp,int* errorFlag,int lineCounter) /* update the address and registers acordding the opcode */
{	
	int wordsCounter=1;
	int j;
	/*memset(sAddress, '\0' , MAX);
	memset(dAddress, '\0' , MAX_NAME);*/
	
	if (!strcmp(codeTemp->opcode,"0000")||!strcmp(codeTemp->opcode,"0001")||!strcmp(codeTemp->opcode,"0010")||!strcmp(codeTemp->opcode,"0011")||!strcmp(codeTemp->opcode,"0110"))	 /*mov, cmp, add, sub and lea functions */
       	{
		j = sourceOperand(line,index,codeTemp,errorFlag,lineCounter);
		while(isspace(line[j])|| line[j]==',')
			j++;	
		j = destinationOperand(line,j,codeTemp,errorFlag,lineCounter);
		if(!isspace(line[j]) && line[j]!='\n')
		{	
			printf("error,the function got to much operators. in line %d\n",lineCounter);
			*errorFlag=1;
		}
		if(!strcmp(codeTemp->sAddress,"00"))
			wordsCounter++;	
		if(!strcmp(codeTemp->sAddress,"01"))
			wordsCounter++;
		if(!strcmp(codeTemp->sAddress,"10"))
			wordsCounter+=2;
		if(!strcmp(codeTemp->sAddress,"11"))
			wordsCounter++;	
		if(!strcmp(codeTemp->dAddress,"00"))
			wordsCounter++;	
		if(!strcmp(codeTemp->dAddress,"01"))
			wordsCounter++;
		if(!strcmp(codeTemp->dAddress,"10"))
			wordsCounter+=2;
		if(!strcmp(codeTemp->dAddress,"11"))
		{
			if(!strcmp(codeTemp->sAddress,"11"));
			else
				wordsCounter++;
		}
		return  wordsCounter;    
	}
	else 
	{	
		if(!strcmp(codeTemp->opcode,"1111")||!strcmp(codeTemp->opcode,"1110"))/*coding rts and hlt operands*/
		{		
			strcpy(codeTemp->are,"00");
			strcpy(codeTemp->sAddress,"00");
			strcpy(codeTemp->dAddress,"00");
			return 1;
		}
		else/*functions without source operands*/
		{
		   	strcpy(codeTemp->sAddress,"00");
			j= destinationOperand(line,index,codeTemp,errorFlag,lineCounter);
			while(isspace(line[j])&&line[j]!='\n')
				j++;
			if(!isspace(line[j]) && line[j]!='\n')
			{
				printf("%c\t",line[j]);
				printf("error,the function got to much operators. in line %d \n",lineCounter);
				*errorFlag=1;
			}
			if(!strcmp(codeTemp->dAddress,"00"))
				wordsCounter++;
			if(!strcmp(codeTemp->dAddress,"01"))
				wordsCounter++;
			if(!strcmp(codeTemp->dAddress,"10"))
				wordsCounter+=2;
			if(!strcmp(codeTemp->dAddress,"11"))
			{
				if(!strcmp(codeTemp->sAddress,"11"));				
				else
					wordsCounter++;
			}			
			return  wordsCounter;
		}
		 
       }
     
      
}

int firstCheck(int i, char *argv[],Symbol** symbolsHead, Code** codeHead, int *ic, int *dc)
{	
	int lineCounter =0;
	int errorFlag=0;
	int value, index = 0;
	int tempDC = 0 , tempIC = 100 ; 
	char line[MAX];
	char fname[MAX_NAME];
	int tempIndex;
	FILE *fpr;
	memset(line, '\0' , MAX);
	strcpy(fname,argv[i]);
	strncat(fname,".am", 3); 
	fpr = fopen(fname,"r");
	if(fpr==NULL)
	{	
		printf("error , the file : %s is not open! ",fname);
		return 1;
	}
	while (fgets(line, MAX, fpr))
	{
		lineCounter++;
		if(isNotSpaceLine(fpr,line))
		{
			Code* codeTemp=createCodeNode();
			Symbol* symbolTemp=createSymbolNode();
			strcpy(codeTemp->symbol,"null");
			if(isSymbol(line,symbolTemp,symbolsHead,codeTemp ,lineCounter,&errorFlag))
			{ 
				strcpy(codeTemp -> symbol, symbolTemp->symbol);
				while(isspace(line[index]))
			 		index++;
				while(!isspace(line[index]))
				   	index++;
				tempIndex=index;
				while(isspace(line[tempIndex]))
				{
					if (line[tempIndex] == '\n' )
	        			{
						printf("symbol defination error line %d\n",lineCounter);	
						errorFlag =1;
					}
					tempIndex++;
				}
				strcpy(codeTemp->are,"00");
				if (dataOrStringOrStruct(line,index))
				{
					symbolTemp ->value = tempDC;
					value = dataOrStringOrStruct(line,index);
					tempDC = tempDC + value;
					addCodeNode(codeTemp,codeHead);   
				}
				else 
				{ 
					symbolTemp ->value = tempIC;
					index = checkOpcode(line,index,codeTemp,lineCounter,&errorFlag);
					tempIC = tempIC + instruction(line,index,codeTemp,&errorFlag,lineCounter);
					addCodeNode(codeTemp,codeHead);
				}
				addSymbolNode(symbolTemp,symbolsHead);
			}
			else if(dataOrStringOrStruct(line , 0))
    			{
				strcpy(codeTemp->are,"00");
      				value = dataOrStringOrStruct(line , 0);
      				addCodeNode(codeTemp,codeHead);
				tempDC = tempDC + value;
      				tempIC = tempIC + value;
    			}
			else if(entryOrExtern(line) == 1)/*extern call*/
			{
				externSymbol(symbolTemp, line , lineCounter , &errorFlag);
				addSymbolNode(symbolTemp,symbolsHead);
			}
	
			else if(!entryOrExtern(line)) /* instruction call  */
   			{
				if(line[index]!=';')
				{
     					while(isspace(line[index]))
        					index++;
      					index = checkOpcode(line,index,codeTemp,lineCounter,&errorFlag);
      					if (index==-1)
      					{
        					printf("\n Invalid instruction in line:  %d \n ", lineCounter);
        	 				errorFlag = 1;   
      					}
				
      					else
      					{
						strcpy(codeTemp->are,"00");
        					tempIC = tempIC + instruction(line,index,codeTemp,&errorFlag,lineCounter);
 			       			addCodeNode(codeTemp,codeHead);
					}
      				}
    			}      
    			index = 0 ;
		}
  	}
  	fclose(fpr);
  	*ic = tempIC;
  	*dc = tempDC;
  	return errorFlag;
}
	











