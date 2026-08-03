#include "secondCheck.h"
#include "firstCheck.h"


Print *createPrintNode()
{
	Print *temp; /* declare a node */
	temp =(Print*) malloc(sizeof(Print)); /* allocate memory using malloc() */
	memset(temp->binary,'\0',BINARY);
	temp->counter=0;	
	if (temp==NULL)
	{
		printf("error . cannot allocate memory");
		exit(1);
     	}
    	temp->next = NULL;/* make next point to NULL*/
    	return temp;/*return the new node*/

}
void free_list_prints(Print * list)
{
    	Print* next_node;
    	while(list != NULL)
    	{
        	next_node = list->next;
        	free(list);
        	list = next_node;
      
    	}
}
	
void addToPrintList(Print *temp,Print **head)
{
	
	Print* node; 
	node =*head;
	if((*head)->binary[0]=='\0')
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

void updateAllDataValue(Symbol** symbolHead,int ic)
{
	Symbol *temp;
	temp = *symbolHead;
  	while (temp != NULL)
      	{	
        	if (temp->type[0]>0)
            		temp->value+=ic;
        	temp = temp->next;  
      	}
}
int ifSymbolInLine(Symbol **symbolHead,char line[])
{
	int index=0;
	int symbolIndex=0;
	Symbol* temp;
	char symbol[MAX_NAME];
	temp=*symbolHead;
	memset(symbol , '\0' ,MAX_NAME);
	while(isspace(line[index]))
		index++;
	while(!isspace(line[index])&& line[index]!=':')
	{		
		symbol[symbolIndex]=line[index];
		symbolIndex++;
		index++;
	}
	while(temp!=NULL)
	{
		if(!strcmp(temp->symbol,symbol))
			return 1;
		temp =temp->next;
	}
	return 0;

}
char *codingDataStringOrStructToBinary(int n,int lineCounter,int* errorFlag)
{	
	if (n<256) /*computer memory*/
	{		
  		int i;
    		char *p;
		char binary[11]="00000000000";
  		for(i=9;n>0;i--)
  		{
     			binary[i]= n%2 +48 ;
     			n=n/2;
  		}
		p=binary;
   		binary[10]='\0';
		return p;
	}	
	else
	{
		printf("error , the number %d in line %d, is to long for memory",n,lineCounter);
		*errorFlag =1;
		return "0000000000";
	}
	
}

 char *codingDecimalToBinary(int n,int lineCounter,int* errorFlag)
{	
	if (n<256) /*computer memory*/
	{		
  		int i;
    		char *p;
		char binary[11]="0000000000";
  		for(i=7;n>0;i--)
  		{
     			binary[i]= n%2 +48 ;
     			n=n/2;
  		}	
		p=binary;
   		binary[10]='\0';
		return p;
	}	
	else
	{
		printf("error , the number %d in line %d, is to long for memory",n,lineCounter);
		*errorFlag =1;
		return "0000000000";
	}
	
}
char *negativeData(int num) /* find the Complementary to 2 for data negative number */
{
	unsigned int u_i = 0;
        int j = 0;
	char* p;
        int b[10];
        char temp[10];
	memset(b,'\0', 10);
        u_i = (unsigned int)num;

        for(j=9;j>=0;j--)
	{
            b[j] = u_i & 0x1;
            u_i  = u_i >> 1;
        }
	for (j=0;j<=9;j++)
                temp[j]= b[j] +'0';
	temp[10]='\0';
	p=temp;
	return p;
}
char *negative(int num) /* find the Complementary to 2 for  negative number */
{
        unsigned int u_i = 0;
        int j = 0;
	char* p;
        int b[8];
        char temp[10];
	memset(b,'\0', 8);
        u_i = (unsigned int)num;

        for(j=7;j>=0;j--)
	{
            b[j] = u_i & 0x1;
            u_i  = u_i >> 1;
        }
	for (j=0;j<=7;j++)
                temp[j]= b[j] +'0';
	temp[8]='\0';
	strncat(temp,"00",2);
	p=temp;	
	return p;
    
}
unsigned binaryTodecimal (char num[])/*convert binary array to decimal number*/
{
    	int i, decimalNum, mul = 0;
    	for ( decimalNum = 0, i = 9; i >= 0; --i, ++mul)
    	{
		decimalNum = decimalNum + (num[i] - 48) * (1 << mul);
	}
        return decimalNum;
}
void toBase32(unsigned n,char* temp)
{
	char base32chars[] = "!@#$%^&*<>abcdefghijklmnopqrstuv";
    	temp[1]=base32chars[n%32];
	n/=32;
	temp[0]=base32chars[n%32];
	temp [2]='\0';
    
}

void printFile(FILE *fpw ,Print **headIc,Print **headDc)  /* insert the line to our output file */
{	
	char counter[3];
	char code[3];
	unsigned n;
	Print *tempIc;
	Print *tempDc;
	tempIc = *headIc;
	tempDc = *headDc;
	while(tempIc!=NULL)
	{
		n=binaryTodecimal(tempIc->binary);
		toBase32(tempIc->counter,counter);
		toBase32(n,code);
		fprintf(fpw , "%s\t%s\n",counter,code);
		tempIc=tempIc->next;
	}
	
	while(tempDc!=NULL)
	{
		n=binaryTodecimal(tempDc->binary);
		toBase32(tempDc->counter,counter);
		toBase32(n,code);
		fprintf(fpw , "%s\t%s\n",counter,code);
		tempDc=tempDc->next;
	}
    
}
char* printfunct(char are[], char opcode[], char sAddress[],char dAddress[]) /* Placement the parts of the line to one. */
{
  	char *p;
  	char binary[10] = "0000000000";
  	binary[9]  = are[1];
  	binary[8]  = are[0];
  	binary[7]  = dAddress[1];
  	binary[6]  = dAddress[0];
  	binary[5]  = sAddress[1];
 	binary[4]  = sAddress[0];
 	binary[3] = opcode[3];
 	binary[2] = opcode[2];
 	binary[1] = opcode[1];
  	binary[0] = opcode[0];

  	p = binary;
  	return p; 
}
int printStructOrData(FILE *fpw,char address[],char symbol[],int structNum,int counter,char fname[],Symbol** symbolHead,int lineCounter, int* errorFlag,Print **headPrintIc) /* print to output file the addrres of the symbol */
{
	char *p;
	int countWords =0;
	Print *tempCode;
 	Symbol* temp = NULL;	
  	char printBinary[10];
	char printBinaryExtern[10];
  	temp = *symbolHead;
  	memset(printBinary, '\0' , 10);
	memset(printBinaryExtern, '0' , 10);
  	while (temp != NULL)
      	{	
        	if (!strcmp(temp->symbol,symbol))
            		break;
        	temp = temp->next;  
      	}
  	if (temp != NULL)
  	{
			if(!strcmp(address,"10"))/*if it is struct symbol*/
			{	
				if (temp->type[3] > 48) /* if it's extern symbol */
				{
       					printBinaryExtern[9]='1';
					tempCode=createPrintNode();
					strcpy(tempCode->binary,printBinaryExtern);
					tempCode->counter = counter;	
					addToPrintList(tempCode,headPrintIc);

					printExternals(fname,temp->symbol,counter);
    					counter++;

					p=codingDecimalToBinary(structNum,lineCounter,errorFlag);
					tempCode=createPrintNode();
					strcpy(tempCode->binary,p);
					tempCode->counter = counter;	
					addToPrintList(tempCode,headPrintIc);

					counter++;
					countWords+=2;
				}				
				else
				{	tempCode=createPrintNode();
					p=codingDecimalToBinary(temp->value,lineCounter,errorFlag);
					strcpy(tempCode->binary,p);
					tempCode->binary[8] ='1';
					tempCode->counter = counter;	
					addToPrintList(tempCode,headPrintIc);			
					
					
					counter++;
					tempCode=createPrintNode();
					p=codingDecimalToBinary(structNum,lineCounter,errorFlag);
					strcpy(tempCode->binary,p);
					tempCode->counter = counter;	
					addToPrintList(tempCode,headPrintIc);
	
					counter++;
					countWords+=2;
				}
				
			}		
			else /*if it is data symbol*/
			{
				if (temp->type[3] > 48) /* if it's extern symbol */
				{
       					printBinaryExtern[9]='1';
					tempCode=createPrintNode();
					strcpy(tempCode->binary,printBinaryExtern);
					tempCode->counter = counter;	
					addToPrintList(tempCode,headPrintIc);

				
					printExternals(fname,temp->symbol,counter);
    					counter++;
					countWords++;
				}				
				else
				{				
					strcpy(printBinary,codingDecimalToBinary(temp->value,lineCounter,errorFlag));
					printBinary[8] ='1';
					tempCode=createPrintNode();
					strcpy(tempCode->binary,printBinary);
					tempCode->counter = counter;	
					addToPrintList(tempCode,headPrintIc);


					counter++;
					countWords++;
				}
			}
		
	}
	else
	{
		printf("error, the symbols %s doenst found . in line %d",symbol,lineCounter);
		*errorFlag=1;
	}
	return countWords;
}
char* registerNumberToBinary(int n) /*Converts the decimal number to a binary number*/
{
	int i;
	char *p;
	char binary[5] = "0000";
	for(i=3;n>0;i--)
	{
		binary[i]=n%2 +48 ;   
	    	n=n/2;
	} 	   
	p = binary;
	return p; 
} 
void printRegisterSource(FILE *fpw,int counter , int registerNumber,Print **headPrintIc)/*print Source register*/
{
	char *p;
	Print *tempCode;
	char buf[10];
	memset(buf,'\0',10);
	p=registerNumberToBinary(registerNumber);
	buf[0]=p[0];
	buf[1]=p[1];
	buf[2]=p[2];
	buf[3]=p[3];
	strncat(buf,"000000",6);
	tempCode=createPrintNode();
	strcpy(tempCode->binary,buf);
	tempCode->counter = counter;	
	addToPrintList(tempCode,headPrintIc);

	

}
void printRegisterDestination(FILE *fpw,int counter , int registerNumber,Print **headPrintIc)/*print Desination register*/
{
	char *p;
	Print *tempCode;
	char buf[10];
	memset(buf,'\0',10);
	p=registerNumberToBinary(registerNumber);
	buf[0]='0';
	buf[1]='0';
	buf[2]='0';
	buf[3]='0';	
	buf[4]=p[0];
	buf[5]=p[1];
	buf[6]=p[2];
	buf[7]=p[3];
	strncat(buf,"00",2);
	tempCode=createPrintNode();
	strcpy(tempCode->binary,buf);
	tempCode->counter = counter;	
	addToPrintList(tempCode,headPrintIc);
	

}
void printBothRegister(FILE *fpw,int counter , int sourceRegisterNumber , int destinationRegisterNumber,Print **headPrintIc)/*print 2 registers in one line */
{
	char *p1 , *p2;
	Print *tempCode;
	char buf1[10],buf2[10];
	memset(buf1,'\0',10);
	memset(buf2,'\0',10);
	
	p1=registerNumberToBinary(sourceRegisterNumber);
	buf1[0]=p1[0];
	buf1[1]=p1[1];
	buf1[2]=p1[2];
	buf1[3]=p1[3];
	p2=registerNumberToBinary(destinationRegisterNumber);
	buf2[0]=p2[0];
	buf2[1]=p2[1];
	buf2[2]=p2[2];
	buf2[3]=p2[3];
	strncat(buf1,buf2,4);
	strncat(buf1,"00",2);
	tempCode=createPrintNode();
	strcpy(tempCode->binary,buf1);
	tempCode->counter = counter;	
	addToPrintList(tempCode,headPrintIc);
}	
int destinationR(char opcode[]) /* if we have destnation to our opcode */
{
	if ((!strcmp(opcode,"0010"))|| !strcmp(opcode,"1100"))
    		return 1;
  	return 0;
  
}
int sourceR(char opcode[]) /* if we have source to our opcode */
{
	if ((!strcmp(opcode,"0001"))|| !strcmp(opcode,"0010")||(!strcmp(opcode,"0011"))|| !strcmp(opcode,"0000"))
   		 return 1;
  	return 0;
  
}
int secondCheck(int j, char *argv[],Symbol** symbolHead, Code ** codeHead ,int *IC , int *DC)
{          
  	int entryFlag = 0, errorFlag=0, counter = 100, numberIndex = 0, index = 0, symbolIndex = 0, dataValue , i,lineCounter =0, minusFlag = 0 ,minusnum;
	int dc=*IC;
	char icBase32[3];
	char dcBase32[3];
	char line[MAX];
  	char symbol[MAX_NAME];
  	char num[MAX_NAME];
  	char fname[MAX];
  	char fname2[MAX];
  	FILE *fpr, *fpw;	
	Print *tempCode;
	Print *headPrintIc;
	Print *headPrintDc;
	Code *lastCodeNode =NULL;
  	Symbol *lastSymbolNode = NULL;
	headPrintIc=createPrintNode();
	headPrintDc=createPrintNode();
	lastCodeNode = *codeHead;
	lastSymbolNode = *symbolHead;
  	memset(line, '\0' , MAX);
  	strcpy(fname,argv[j]);
  	strncat(fname, ".am", 3);
 	strcpy(fname2,argv[j]);
  	strncat(fname2, ".ob", 3);
  	fpr = fopen(fname,"r");
	updateAllDataValue(symbolHead,*IC);/*update all data values to the end of the memory*/
	if(fpr!=NULL)
	{	
		
		fpw = fopen(fname2,"w");
		if(fpw!=NULL)
		{	
  			
  			while (fgets(line, MAX, fpr)) /* read next line from the file */
  			{
				lineCounter++;

				if(line[index]!=';'&&isNotSpaceLine(fpr,line))
				{
					if (ifSymbolInLine(symbolHead,line))/* if we have label define in the line*/
    					{
      						while(!isspace(line[index]))
       							index++;
    					}
					
					dataValue = dataOrStringOrStruct(line,index);
	    				if ( dataValue > 0)   /* if we have a data or string or struct order in the line */
	    				{
						
						
						while(isspace(line[index]))
	        					index++;  
	        				if (line[index + 4] == 'i') /* it's string order */
	        				{
							while(!isspace(line[index]))
	             						index++;
	           					while(isspace(line[index]))
	            						index++;    
	           					index++;
	           					for ( i = 1; i < dataValue; i++)
	           					{
								tempCode=createPrintNode();
	               						strcpy(tempCode->binary,codingDataStringOrStructToBinary(line[index],lineCounter,&errorFlag));
								tempCode->counter = dc;									
								addToPrintList(tempCode,&headPrintDc);	               						
	               						index++;
								dc++;
								
	           					}
							tempCode=createPrintNode();
							strcpy(tempCode->binary,"0000000000");
							tempCode->counter = dc;	
							addToPrintList(tempCode,&headPrintDc);
							dc++;
						}
						else
						{
							 if(line[index + 4] == 'u') /* it's struct order */
							{
								while(!isspace(line[index]))
	             							index++;
	           						while(isspace(line[index]))
	            							index++;
								if (line[index] == 45 )
	            						{
	              							minusFlag = 1;
	              							index++;
	            						}
	          						else if (line[index] == 43 )
	              							index++;
								if(line[index] != 43 && line[index] != 45 && line[index] <= 47 && line[index] >= 58)
								{
									printf("struct definition error in line %d",lineCounter);	
									errorFlag =1;
								}
	          						while(line[index] > 47 && line[index] < 58 && line[index] != '.')
	          						{
	            							num[numberIndex] = line[index];
	            							numberIndex++;
	          							index++;
	         						}
								if(line[index] == '.')
								{
									printf("invald number . not supporting in real numbers only integer numbers. in line %d",lineCounter);	
									errorFlag =1;
								}

	          						if (atoi(num) != 0) 
	          						{
	             							if (!minusFlag)   /* Check the number if it's positive of negative number */
	               							{
										tempCode=createPrintNode();											
										strcpy(tempCode->binary,codingDataStringOrStructToBinary(atoi(num),lineCounter,&errorFlag));
										tempCode->counter = dc;	
										addToPrintList(tempCode,&headPrintDc);
										dc++;
									}
	            							else
									{
										minusnum = atoi(num);
										minusnum = -minusnum;
										tempCode=createPrintNode();
	               								strcpy(tempCode->binary,negativeData(minusnum));
										tempCode->counter = dc;	
										addToPrintList(tempCode,&headPrintDc);
										dc++;
									} 
  								}
								
							
								while(isspace(line[index]))
	             							index++;
								if(line[index]!=',')
								{
									printf("struct definition error in line : %d",lineCounter);
									errorFlag=1;	
								}	
								else 
								{
									index++;
									while(isspace(line[index]))
	            								index++;
									if(line[index]!='"')
									{
									printf("struct definition error in line : %d",lineCounter);
									errorFlag=1;	
									}
									index++;
									for ( i = 2; i < dataValue; i++)
	           							{
										tempCode=createPrintNode();
	               								strcpy(tempCode->binary,codingDataStringOrStructToBinary(line	[index],lineCounter,&errorFlag));
										tempCode->counter = dc;	
										addToPrintList(tempCode,&headPrintDc);
	               								dc++;
										index++;
	               								
	           							}
									tempCode=createPrintNode();
									strcpy(tempCode->binary,"0000000000");	
									tempCode->counter = dc;	
									addToPrintList(tempCode,&headPrintDc);
									dc++;
								}
								if(line[index]!='"')
								{
									printf("struct definition error in line : %d",lineCounter);
									errorFlag=1;	
								}
								index++;
										
							
								
							}
							else  /* It's data order */
							{
	        						while(!isspace(line[index]))
	          							index++;    
	        						for ( i = 0; i < dataValue; i++)
	        						{
	          							memset(num, '\0' , MAX_NAME);
	          							numberIndex = 0;
	          							while(isspace(line[index]))
	          							{
										if (line[index] == '\n' )
	              								{
											printf("data defination error line %d",lineCounter);	
											errorFlag =1;
										}
										index++;
									}
	          							minusFlag = 0;
	          							if (line[index] == 45 )
	            							{
	              								minusFlag = 1;
	              								index++;
	            							}
	          							else if (line[index] == 43 )
	              								index++;
									if (line[index] == ',' )
	              							{
										printf("data defination error line %d",lineCounter);	
										errorFlag =1;
									}
	          							while(line[index] > 47 && line[index] < 58 && line[index] != '.')
	          							{
	            								num[numberIndex] = line[index];
	            								numberIndex++;
	          								index++;
	         							}
									if(line[index] == '.')
									{
										printf("invald number . not supporting in real numbers only integer numbers. in line %d",lineCounter);	
										errorFlag =1;
									}
	          							if (atoi(num) != 0) 
	          							{
	             								if (!minusFlag)   /* Check the number if it's positive of negative number */
	               								{
											tempCode=createPrintNode();											
											strcpy(tempCode->binary,codingDataStringOrStructToBinary(atoi(num),lineCounter,&errorFlag));
											tempCode->counter = dc;	
											addToPrintList(tempCode,&headPrintDc);
											dc++;
										}
	            								else
										{
											minusnum = atoi(num);
											minusnum = -minusnum;
											tempCode=createPrintNode();
	               									strcpy(tempCode->binary,negativeData(minusnum));
											tempCode->counter = dc;	
											addToPrintList(tempCode,&headPrintDc);
											dc++;
										}
										
	           								while(isspace(line[index]))
	              									index++;  
	            								index++; 
	          							}
	       							}
	      						}
						} 
	     					lastCodeNode = lastCodeNode->next; 
						
	    				} 
					else 
					if((!(entryOrExtern(line) == 1)))   /* If it is'nt extern label */
	     				{	
	        				if(entryOrExtern(line) == 2)   /* If it's entry label */
	        				{
	           					memset(symbol, '\0' , MAX_NAME);
	           					index = 0;
	           					symbolIndex = 0;
	           					lastSymbolNode= *symbolHead; 
	           					while(isspace(line[index]))
	           						index++;
	          			 		while(!isspace(line[index]))
	           						index++;
	           					while(isspace(line[index]))
	           						index++;
	           					while(!isspace(line[index]))
	           					{
	              						symbol[symbolIndex] = line[index];
	              						index++;
	              						symbolIndex++;
	           					}
	          					while (lastSymbolNode != NULL && !entryFlag)
	           					{
	             						if (!strcmp(lastSymbolNode->symbol,symbol))
	             						{
	                						lastSymbolNode->type[2]='1';/*entry type*/
	                						entryFlag++;
	             						}
	             					lastSymbolNode =lastSymbolNode->next;  
	           					}
	          					if(!entryFlag)
							{
		             					printf("\n  error! the symbol : %s dosent exist  in line :%d\n",symbol,lineCounter);
								errorFlag=1;				
							}
	          					entryFlag = 0;
	       					}
	       					else   /* If it's instruction line */
	       					{
	          					
	          					if (strcmp(lastCodeNode->opcode,"1111"))/*if its not hlt function*/ 
	         					 {
								tempCode=createPrintNode();
	             						strcpy(tempCode->binary,printfunct(lastCodeNode->are,lastCodeNode->opcode,lastCodeNode->sAddress,lastCodeNode->dAddress));
								tempCode->counter = counter;	
								addToPrintList(tempCode,&headPrintIc);
	              						counter++;   
	          					}
							else /*if its hlt function*/
							{	
								tempCode=createPrintNode();
								strcpy(tempCode->binary,"1111000000");
								tempCode->counter = counter;	
								addToPrintList(tempCode,&headPrintIc);
	              						counter++; 		
							}
							/*Printing words the source needs*/
	      						if(!strcmp(lastCodeNode->sAddress,"10")||!strcmp(lastCodeNode->sAddress,"01"))/*if we have data or struct symbol in source operand*/
							{
								counter=counter+printStructOrData(fpw,lastCodeNode->sAddress,lastCodeNode->sourceSymbol,lastCodeNode->sourceStructNumber,counter,argv[j],symbolHead,lineCounter,&errorFlag,&headPrintIc);
						
							}
							if(!strcmp(lastCodeNode->sAddress,"11"))/*if we have register in source operand*/
							{
								if(!strcmp(lastCodeNode->dAddress,"11"))/*if we have register in destanation operand also*/
								{
									printBothRegister(fpw,counter,lastCodeNode->sourceRegisterNumber,lastCodeNode->destinationRegisterNumber,&headPrintIc);		
									counter++;							
								}
								else
								{
									printRegisterSource(fpw,counter,lastCodeNode->sourceRegisterNumber,&headPrintIc);
									counter++;
								}
							}
							if( !strcmp(lastCodeNode->sAddress,"00") && sourceR(lastCodeNode->opcode))/* If we have direct address */
          						{  
            							minusFlag = 0;
            							memset(num, '\0' , MAX_NAME);
            							numberIndex = 0;
            							while (line[index] != 35)
                							index++;
            							index++;
           							if (line[index] == 45 )
            							{
              								minusFlag = 1;
              								index ++;
            							}
            							else if (line[index] == 43 )
              								index++;
            							while (line[index] > 47 && line[index] < 58)
            							{
              								num[numberIndex] = line[index];
              								index++;
              								numberIndex++;
            							}
            							if (!minusFlag)
								{
               								tempCode=createPrintNode();
									strcpy(tempCode->binary,codingDecimalToBinary(atoi(num),lineCounter,&errorFlag));
									tempCode->counter = counter;	
									addToPrintList(tempCode,&headPrintIc);
            							}
								else
								{
               								minusnum = atoi(num);
									minusnum = -minusnum;
									tempCode=createPrintNode();
               								strcpy(tempCode->binary,negative(minusnum));
									tempCode->counter = counter;	
									addToPrintList(tempCode,&headPrintIc);
					
								}
							
            							counter++;
         						}
							/*Printing words the destination needs*/
							if(!strcmp(lastCodeNode->dAddress,"11")&& strcmp(lastCodeNode->sAddress,"11"))/*if we have register only in destination operand*/
							{
								printRegisterDestination(fpw,counter,lastCodeNode->destinationRegisterNumber,&headPrintIc);
								counter++;
							}
							if(!strcmp(lastCodeNode->dAddress,"10")||!strcmp(lastCodeNode->dAddress,"01"))/*if we have data or struct symbol in destination operand*/
							{
								counter=counter+printStructOrData(fpw,lastCodeNode->dAddress,lastCodeNode->destinationSymbol,lastCodeNode->destinationStructNumber,counter,argv[j],symbolHead,lineCounter,&errorFlag,&headPrintIc);
							}
							if(!strcmp(lastCodeNode->dAddress,"00") && destinationR(lastCodeNode->opcode))
							{  
            							minusFlag = 0;
            							memset(num, '\0' , MAX_NAME);
            							numberIndex = 0;
            							while (line[index] != 35)
                							index++;
            							index++;
           							if (line[index] == 45 )
            							{
              								minusFlag = 1;
              								index ++;
            							}
            							else if (line[index] == 43 )
              								index++;
            							while (line[index] > 47 && line[index] < 58)
            							{
              								num[numberIndex] = line[index];
              								index++;
              								numberIndex++;
            							}
            							if (!minusFlag)
								{
               								tempCode=createPrintNode();	
									strcpy(tempCode->binary,codingDecimalToBinary(atoi(num),lineCounter,&errorFlag));
									tempCode->counter = counter;	
									addToPrintList(tempCode,&headPrintIc);
            							}
								else
               							{
               								minusnum = atoi(num);
									minusnum = -minusnum;
									tempCode=createPrintNode();
               								strcpy(tempCode->binary,negative(minusnum));
									tempCode->counter = counter;	
									addToPrintList(tempCode,&headPrintIc);
								}

            							counter++;
         						}
          						lastCodeNode = lastCodeNode->next; 

      						}
      					}

  				}
				memset(line, '\0' , MAX);
				memset(num, '\0' , MAX);
  				index = 0 ;
				numberIndex=0;
      				minusFlag = 0; 
			}
			if(!errorFlag)
			{
				toBase32((*IC-100),icBase32);
				toBase32(*DC,dcBase32);
  				fprintf(fpw , "  %s  %s \n",icBase32 ,dcBase32);
				printFile(fpw,&headPrintIc,&headPrintDc);
				free_list_prints(headPrintIc);
				free_list_prints(headPrintDc);
			}
		}
		else
			printf("error , the file : %s is not open! ",fname2);
		

	}
	else 
		printf("error , the file : %s is not open! ",fname);
	fclose(fpr);
  	fclose(fpw);
	return errorFlag;



}



