CC = g++
bc:			symTable.o lex.o topDownParser.o symTable.o
			$(CC) symTable.o lex.o topDownParser.o symTable.o -o bc

lex.o:		lex.cpp lex.h
			$(CC) -c lex.cpp

topDownParser.o:		topDownParser.cpp topDownParser.h
			$(CC) -c topDownParser.cpp

symTable.o:	symTable.cpp symTable.h
			$(CC) -c symTable.cpp

clean:
			rm a.out lex.o topDownParser.o symTable.o