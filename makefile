CC = g++
bc:			symTable.o lex.o topDownParser.o
			$(CC)  -o bc symTable.o lex.o topDownParser.o -lfl -lm

lex.o:		lex.cpp lex.h
			$(CC) -c lex.cpp

topDownParser.o:		topDownParser.cpp topDownParser.h
			$(CC) -c topDownParser.cpp

symTable.o:	symTable.cpp symTable.h
			$(CC) -c symTable.cpp

