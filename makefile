myrun:main.o macroFunction.o dataCode.o symbols.o firstCheck.o secondCheck.o
	gcc  -ansi -Wall -pedantic -g main.o macroFunction.o dataCode.o symbols.o firstCheck.o secondCheck.o -lm -o myrun
main.o :main.c  header.h
	gcc -lm -c -ansi -Wall -pedantic -g main.c -o main.o
macroFunction.o :macroFunction.c macroFunction.h
	gcc -lm -c -ansi -Wall -pedantic -g macroFunction.c -o macroFunction.o
dataCode.o: dataCode.c dataCode.h
	gcc -lm -c -Wall -ansi -pedantic -g dataCode.c -o dataCode.o 
symbols.o: symbols.c symbols.h secondCheck.h
	gcc -lm -c -Wall -ansi -pedantic -g symbols.c -o symbols.o 
firstCheck.o: firstCheck.c firstCheck.h 
	gcc -lm -c -Wall -ansi -pedantic -g firstCheck.c -o firstCheck.o 
secondCheck.o: secondCheck.c secondCheck.h firstCheck.h
	gcc -lm -c -Wall -ansi -pedantic -g secondCheck.c -o secondCheck.o 
