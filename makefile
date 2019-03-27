CC = g++
bc:			topDownParser.o lex.o symTable.o general.o
			$(CC) topDownParser.o lex.o symTable.o general.o -o bc

lex.o:		lex.cpp lex.h
			$(CC) -c lex.cpp

topDownParser.o:		topDownParser.cpp topDownParser.h
			$(CC) -c topDownParser.cpp

symTable.o:	symTable.cpp symTable.h
			$(CC) -c symTable.cpp
general.o: general.cpp general.h
			$(CC) -c general.cpp
clean:
<<<<<<< HEAD
			rm a.out lex.o topDownParser.o symTable.o
=======
			rm bc lex.o topDownParser.o symTable.o general.o
>>>>>>> 3c35589c6caf62a2927d83ceafd38594e518cee4
