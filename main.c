#include "header.h"


int main(int argc,char *argv[])
{	
	
	int dc =0;
	int ic=0;
	int i,flag;	

	for (i = 1; i < argc; i++)
	{	
		
		Macro *head = createNode();
		Symbol *symbolHead=createSymbolNode();
		Code *codeHead = createCodeNode();
		flag=readMacroInText(i,argv,&head);
		if(!flag)
		{	
			writeMacrosToFile(i,argv,&head);
			
			flag = firstCheck(i,argv,&symbolHead,&codeHead,&ic,&dc);
			
			if(!flag)
				flag=secondCheck(i,argv,&symbolHead,&codeHead,&ic,&dc);
			if(!flag)
				printEntries(i,argv,&symbolHead);
			
		}
		free_list_macro(head);
		free_list_symbols(symbolHead);
		free_list_codes(codeHead);
	}
	
    	return 0;
}


